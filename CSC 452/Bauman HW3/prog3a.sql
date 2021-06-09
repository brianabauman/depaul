SET SERVEROUTPUT ON;
SET VERIFY OFF;

DECLARE
    invalid_input EXCEPTION;
        
    fullName VARCHAR(100);
    firstName VARCHAR(100);
    lastName VARCHAR(100);
    title VARCHAR(100);
    
    PROCEDURE parse_name (
        fullName IN VARCHAR2,
        firstName OUT VARCHAR2,
        lastName OUT VARCHAR2,
        title OUT VARCHAR2
    )
    IS       
        commaPosition NUMBER;
        firstSpacePosition NUMBER;
        secondSpacePosition NUMBER;        
    BEGIN
        commaPosition := INSTR(fullName, ',');
        firstSpacePosition := INSTR(fullName, ' ');
        secondSpacePosition := INSTR(fullName, ' ', 1, 2);
        
        --Validate format
        IF secondSpacePosition = 0 THEN
            RAISE invalid_input;
        ELSIF LENGTH(fullName) <= secondSpacePosition THEN
            RAISE invalid_input;
        ELSIF firstSpacePosition < commaPosition THEN
            RAISE invalid_input;
        END IF;
           
        IF commaPosition > 0 THEN
            lastName := SUBSTR(fullName, 0, commaPosition - 1);
            firstName := SUBSTR(fullName, firstSpacePosition + 1, secondSpacePosition - firstSpacePosition - 1);
            title := SUBSTR(fullName, secondSpacePosition + 1, LENGTH(fullName));
        ELSE
            firstName := SUBSTR(fullName, 1, firstSpacePosition - 1);
            lastName := SUBSTR(fullName, firstSpacePosition + 1, secondSpacePosition - firstSpacePosition - 1);
            title := SUBSTR(fullName, secondSpacePosition + 1, LENGTH(fullName));
        END IF;
        
    END parse_name;
    
BEGIN
    --Get input from substitution variable
    fullName := '&inputFullName';
    
    --Break name into components
    parse_name(fullName, firstName, lastName, title);
    
    --Print formatted name
    DBMS_OUTPUT.PUT_LINE(title || ' ' || firstName || ' ' || lastName);
EXCEPTION
    WHEN invalid_input THEN
        DBMS_OUTPUT.PUT_LINE('Invalid input, please try again...');
END;

