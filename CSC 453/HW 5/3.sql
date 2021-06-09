CREATE OR REPLACE PROCEDURE insertReview (inputString VARCHAR2)
    AS
    
    BEGIN
        DECLARE
            cleansedInputString VARCHAR2(100 BYTE);
            restaurantName VARCHAR2(100 BYTE);
            userName VARCHAR2(100 BYTE);
            ratingString VARCHAR2(100 BYTE);
            rating NUMBER(38, 0);
            ratingDateString VARCHAR2(100 BYTE);
            ratingDate DATE;
            
            userExistsInd NUMBER := 0;
            
            cleanseRegex VARCHAR2(100 BYTE) := '[^a-zA-Z0-9,[:space:]./]';
            splitRegex VARCHAR2(100 BYTE) := '(.*)\, ?(.*)\, ?(.*)\, ?(.*)';
            
        BEGIN   
            --cleanse input to remove irrelevant characters
            cleansedInputString := REGEXP_REPLACE(inputString, cleanseRegex, '');
            
            --split out the pieces into individual variables
            restaurantName := REGEXP_SUBSTR(cleansedInputString, splitRegex, 1, 1, NULL, 1);
            userName := REGEXP_SUBSTR(cleansedInputString, splitRegex, 1, 1, NULL, 2);
            ratingString := REGEXP_SUBSTR(cleansedInputString, splitRegex, 1, 1, NULL, 3);
            ratingDateString := REGEXP_SUBSTR(cleansedInputString, splitRegex, 1, 1, NULL, 4);

            --check if the reviewer exists already
            SELECT COUNT(*)
            INTO userExistsInd
            FROM Reviewer A
            WHERE A.name = userName;
 
            --add them if they don't exist
            IF (userExistsInd != 1) THEN
                INSERT INTO Reviewer VALUES (
                    (SELECT MAX(vID) FROM Reviewer) + 1,
                    userName
                );
            END IF;
            
            --insert the new review
            INSERT INTO Rating VALUES (
                (SELECT rID FROM Restaurant WHERE name = restaurantName),
                (SELECT vID FROM Reviewer WHERE name = userName),
                TO_NUMBER(ratingString),
                TO_DATE(ratingDateString, 'MM/DD/YYYY')
            );
            
        END;
    END;
/

DROP TABLE Top5Restaurants;
CREATE TABLE Top5Restaurants (
    rID INT
);

CREATE OR REPLACE TRIGGER calcuateTop5 
    AFTER INSERT ON Rating
        BEGIN
            DELETE FROM Top5Restaurants;
            
            INSERT INTO Top5Restaurants(rID)
            SELECT rID
            FROM Rating
            GROUP BY rID
            ORDER BY AVG(Stars) DESC
            FETCH FIRST 5 ROWS ONLY;
        END;
        
BEGIN

    insertReview('(''Jade Court'',''Brian B.'', 4, ''08/17/2017'')');
    insertReview('(‘Shanghai Terrace’,`Cameron J.’, 5, ‘08/17/2017’)');
    insertReview('(‘Rangoli’,`Vivek T.’,3,`09/17/2017’)');
    insertReview('(‘Shanghai Inn’,`Audrey M.’,2,`07/08/2017’)');
    insertReview('(‘Cumin’,`Cameron J.’, 2, ‘09/17/2017’)');

END;
                