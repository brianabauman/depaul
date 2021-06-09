--Brian Bauman
--CSC 452

--This SQL file creates all tables that will
--be used in the Auction DB application. It
--also populates those tables with some
--default values so that the auction house
--isn't empty!

DROP TABLE BID;
/
DROP TABLE ITEMS;
/
DROP TABLE MEMBERS;
/

--MEMBERS table
CREATE TABLE MEMBERS
(
    USERID VARCHAR(20) PRIMARY KEY,
    password VARCHAR2(16),
    name VARCHAR2(64),
    address VARCHAR(128),
    phone VARCHAR(12),
    email VARCHAR2(64)
);
/

--ITEMS table
CREATE TABLE ITEMS
(
    INO NUMBER PRIMARY KEY,
    category VARCHAR2(32),
    title VARCHAR2(128),
    description VARCHAR2(256),
    sellerID VARCHAR(20),
    quantity NUMBER,
    startPrice DECIMAL(9,2),
    bidIncrement DECIMAL(9,2),
    lastBidReceived DECIMAL(9,2),
    closeTime TIMESTAMP,
    
    CONSTRAINT fk_sellerID
    FOREIGN KEY (sellerID)
    REFERENCES MEMBERS (USERID)
);
/

--BID table
CREATE TABLE BID
(
    BUYERID VARCHAR(20),
    INO NUMBER,
    PRICE DECIMAL(9,2),
    QTYWANTED NUMBER,
    BIDTIME TIMESTAMP,
    
    CONSTRAINT fk_BUYERID
    FOREIGN KEY (BUYERID)
    REFERENCES MEMBERS (USERID),
    
    CONSTRAINT fk_INO_BID
    FOREIGN KEY (INO)
    REFERENCES ITEMS(INO)
);

--populate tables
INSERT INTO MEMBERS
VALUES ('admin', 'admin', 'Administrator', '123 Admin Ave.', '123-456-7890', 'admin@admin.com');
/
INSERT INTO MEMBERS
VALUES ('brian', 'test', 'Brian Bauman', '2322 W Augusta Blvd.', '281-796-2559', 'bbauman5@mail.depaul.edu');
/
INSERT INTO MEMBERS
VALUES ('moneybags', 'ca$h0ut', 'Oliver Higgenbotham', '8 Ferrari Dr.', '999-999-9999', 'ohiggenbotham@chiggcorp.com');
/
INSERT INTO ITEMS
VALUES (1, 'Art', 'Starry Night', 'A famous landscape from renowned artist Vincent Van Gogh.', 'moneybags', 1, 2500000.00, 100000.00, 2500000.00, SYSDATE + 12/24);
/
INSERT INTO ITEMS
VALUES (2, 'Precious Gems', 'The Queen Opal', 'This 1700 carat opal mined from the junlges of Bolivia is said to be one-of-a-kind.', 'moneybags', 1, 500000.00, 50000.00, 500000.00, SYSDATE + 18/24);
/
INSERT INTO ITEMS
VALUES (3, 'Memorabilia', 'Autographed Babe Ruth Rookie card', 'After decades saying none survived, another was discovered. And now, it can be yours!', 'admin', 1, 30000.00, 1000.00, 32000.00, SYSDATE + 12/24);
/
INSERT INTO BID
VALUES ('brian', 3, 32000.00, 1, SYSDATE);
/
COMMIT;