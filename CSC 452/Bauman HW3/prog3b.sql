SET SERVEROUTPUT ON;
SET VERIFY OFF;

DECLARE
    invalid_length EXCEPTION;
    word_too_long EXCEPTION;
    
    inputText VARCHAR2(2000);
    lineLength NUMBER;
    
    PROCEDURE wrap_text (
        inputText IN VARCHAR2,
        lineLength IN NUMBER
    )
    IS       
        totalSpaces NUMBER;
        tempText VARCHAR2(2000);
        currentSpacePosition NUMBER;
        previousSpacePosition NUMBER;
        spaceCount NUMBER;
    BEGIN
        IF lineLength > 80 THEN
            RAISE invalid_length;
        END IF;

        tempText := inputText;     
        spaceCount := 1;
        
        WHILE LENGTH(tempText) > 0 LOOP
            currentSpacePosition := INSTR(tempText, ' ', 1, spaceCount);    
            IF currentSpacePosition - 1 > lineLength OR 
               (currentSpacePosition = 0 AND spaceCount > 1) THEN
                --the word needs to wrap or is too long to fit
                IF spaceCount = 1 THEN
                    RAISE word_too_long;
                END IF;
                
                previousSpacePosition := INSTR(tempText, ' ', 1, spaceCount - 1);

                DBMS_OUTPUT.PUT_LINE(SUBSTR(tempText, 1, previousSpacePosition - 1));
                tempText := SUBSTR(tempText, previousSpacePosition + 1);
                spaceCount := 1;
                
            ELSIF currentSpacePosition - 1 = lineLength THEN   
                --the word barely fits, lose the space
                DBMS_OUTPUT.PUT_LINE(SUBSTR(tempText, 1, currentSpacePosition - 1));
                tempText := SUBSTR(tempText, currentSpacePosition + 1);
                spaceCount := 1;
                
            ELSIF currentSpacePosition = 0 THEN
                --no spaces left!
                IF LENGTH(tempText) <= lineLength THEN
                    DBMS_OUTPUT.PUT_LINE(tempText);
                    tempText := '';
                ELSE
                    RAISE word_too_long;
                END IF;
                
            ELSE 
                --the word completely fits, find next space
                spaceCount := spaceCount + 1;              
            END IF;
            
        END LOOP;        
    END wrap_text;
    
BEGIN
    --Get input from substitution variable
    inputText := '&inputText';
    lineLength := &lineLength;
    
    --Break name into components
    wrap_text(inputText, lineLength);
EXCEPTION
    WHEN invalid_length THEN
        DBMS_OUTPUT.PUT_LINE('Invalid length, please try again (the max is 80)...');
    WHEN word_too_long THEN
        DBMS_OUTPUT.PUT_LINE('A word is longer than the specified line length...');    
END;

