--Brian Bauman
--CSC 452

--This SQL file creates all prodcedures that
--will be used within the Auction DB. They
--are stored within a single package
--called auction_db.

DROP PACKAGE auction_db;
/

--auction_db package
CREATE PACKAGE auction_db AS
    PROCEDURE verify_user (
        inpUserName IN MEMBERS.USERID%TYPE, 
        outpUserTakenInd OUT NUMBER);
    
    PROCEDURE register_user (
        inpUserName IN MEMBERS.USERID%TYPE,
        inpPassword IN MEMBERS.password%TYPE,
        inpName IN MEMBERS.name%TYPE,
        inpAddress IN MEMBERS.address%TYPE,
        inpPhoneNumber IN MEMBERS.phone%TYPE,
        inpEmail IN MEMBERS.email%TYPE);
    
    PROCEDURE verify_login (
        inpUserName IN MEMBERS.USERID%TYPE,
        inpPassword IN MEMBERS.USERID%TYPE,
        outpLoginValidInd OUT NUMBER);

    PROCEDURE add_item (
        inpSellerUserName IN MEMBERS.USERID%TYPE,
        inpTitle IN ITEMS.title%TYPE,
        inpCategory IN ITEMS.category%TYPE,
        inpDescription IN ITEMS.description%TYPE,
        inpQuantity IN ITEMS.quantity%TYPE,
        inpStartPrice IN ITEMS.startPrice%TYPE,
        inpBidIncrement IN ITEMS.bidIncrement%TYPE,
        inpCloseTimeHours IN DECIMAL);
        
    PROCEDURE search_items (
        inpArgument IN VARCHAR,
        outpCursor OUT SYS_REFCURSOR);
        
    PROCEDURE verify_bid (
        inpINO IN ITEMS.INO%TYPE,
        inpBidPrice IN BID.PRICE%TYPE,
        inpQuantity IN BID.QTYWANTED%TYPE,
        outpRtnCd OUT NUMBER);
        
    PROCEDURE place_bid (
        inpBuyerUserName IN MEMBERS.USERID%TYPE,
        inpINO IN ITEMS.INO%TYPE,
        inpBidPrice IN BID.PRICE%TYPE,
        inpQuantity IN BID.QTYWANTED%TYPE);
END auction_db;
/

--auction_db package body
CREATE PACKAGE BODY auction_db AS
    PROCEDURE verify_user (
        inpUserName IN MEMBERS.USERID%TYPE,
        outpUserTakenInd OUT NUMBER)
    IS
    BEGIN
        SELECT COUNT(*) INTO outpUserTakenInd
        FROM MEMBERS
        WHERE USERID = inpUserName;
    END verify_user;
        
    PROCEDURE register_user (
        inpUserName IN MEMBERS.USERID%TYPE,
        inpPassword IN MEMBERS.password%TYPE,
        inpName IN MEMBERS.name%TYPE,
        inpAddress IN MEMBERS.address%TYPE,
        inpPhoneNumber IN MEMBERS.phone%TYPE,
        inpEmail IN MEMBERS.email%TYPE)
    IS
    BEGIN
        INSERT INTO MEMBERS
        VALUES (inpUserName, inpPassword, inpName, inpAddress, inpPhoneNumber, inpEmail);
        
        COMMIT;
    END register_user;
    
    PROCEDURE verify_login (
        inpUserName IN MEMBERS.USERID%TYPE,
        inpPassword IN MEMBERS.USERID%TYPE,
        outpLoginValidInd OUT NUMBER)
    IS
    BEGIN
        SELECT 1 INTO outpLoginValidInd
        FROM MEMBERS
        WHERE USERID = inpUserName
          AND password = inpPassword;
    END verify_login;
    
    PROCEDURE add_item (
        inpSellerUserName IN MEMBERS.USERID%TYPE,
        inpTitle IN ITEMS.title%TYPE,
        inpCategory IN ITEMS.category%TYPE,
        inpDescription IN ITEMS.description%TYPE,
        inpQuantity IN ITEMS.quantity%TYPE,
        inpStartPrice IN ITEMS.startPrice%TYPE,
        inpBidIncrement IN ITEMS.bidIncrement%TYPE,
        inpCloseTimeHours IN DECIMAL)
    IS
        nextINO ITEMS.INO%TYPE;
    BEGIN
        SELECT MAX(INO) + 1 INTO nextINO
        FROM ITEMS;
        
        IF nextINO IS NULL THEN nextINO := 1; END IF;
        
        INSERT INTO ITEMS
        VALUES (nextINO, inpCategory, inpTitle, inpDescription, inpSellerUserName, inpQuantity, inpStartPrice, inpBidIncrement, inpStartPrice, SYSDATE + (1/24*inpCloseTimeHours));
        COMMIT;
    END add_item;
    
    PROCEDURE search_items (
        inpArgument IN VARCHAR,
        outpCursor OUT SYS_REFCURSOR)
    IS
    BEGIN
        OPEN outpCursor FOR 
            SELECT * FROM ITEMS
            WHERE LOWER(title) LIKE inpArgument
            UNION
            SELECT * FROM ITEMS
            WHERE LOWER(category) LIKE inpArgument
            UNION
            SELECT * FROM ITEMS
            WHERE LOWER(description) LIKE inpArgument;
    END search_items;
    
    PROCEDURE verify_bid (
        inpINO IN ITEMS.INO%TYPE,
        inpBidPrice IN BID.PRICE%TYPE,
        inpQuantity IN BID.QTYWANTED%TYPE,
        outpRtnCd OUT NUMBER)
    IS
        itemExistsInd NUMBER := 0;
        bidEndTime TIMESTAMP := SYSDATE - 1;
        currentPrice DECIMAL(9,2);
        bidIncrement DECIMAL(9,2);
        quantityLeft NUMBER := 0;
    BEGIN
        
        SELECT COUNT(*) INTO itemExistsInd FROM ITEMS
        WHERE INO = inpINO;
        
        IF (itemExistsInd > 0) THEN
            SELECT closeTime, lastBidReceived, bidIncrement, quantity
                INTO bidEndTime, currentPrice, bidIncrement, quantityLeft FROM ITEMS
            WHERE INO = inpINO;
        END IF;
    
        IF (itemExistsInd = 0) THEN
            outpRtnCd := 1;
        ELSIF (SYSDATE > bidEndTime) THEN
            outpRtnCd := 2;
        ELSIF (currentPrice + bidIncrement >= inpBidPrice) THEN
            outpRtnCd := 3;
        ELSIF (quantityLeft < inpQuantity) THEN
            outpRtnCd := 4;
        ELSE
            outpRtnCd := 5;
        END IF;
    END verify_bid;
    
    PROCEDURE place_bid (
        inpBuyerUserName IN MEMBERS.USERID%TYPE,
        inpINO IN ITEMS.INO%TYPE,
        inpBidPrice IN BID.PRICE%TYPE,
        inpQuantity IN BID.QTYWANTED%TYPE)
        
    IS
        itemExistsInd NUMBER := 0;
        bidEndTime TIMESTAMP := SYSDATE - 1;
        currentPrice DECIMAL(9,2);
        bidIncrement DECIMAL(9,2);
    BEGIN
        INSERT INTO BID 
        VALUES(inpBuyerUserName, inpINO, inpBidPrice, inpQuantity, SYSDATE);
        
        UPDATE ITEMS
        SET lastBidReceived = inpBidPrice
        WHERE INO = inpINO;
        
        COMMIT;
    END place_bid;
END auction_db;