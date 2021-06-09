--This procedure takes in a table name, a list of comma
--delimited attribute names, and a parameter specifying
--the number of attributes passed. It then splits out the 
--attribute names and builds a large SQL query corresponding
--to a ROLLUP grouping which returns the COUNT of rows for 
--each permutation. It prints the text of this query and 
--returns a pointer to cursor containing the result set.

--At the bottom of this .SQL file is an example of a dataset
--used as well as the PL/SQL to run this function on that 
--dataset. It also contains an example output of the 
--constructed SQL query.

--NOTE: This procedure will only work for numeric datasets
--      with positive values as it replaces non-GROUP BY'd 
--      attriutes with a value of -1 (rather than a blank
--      as shown in the Oracle documentation.

CREATE OR REPLACE PROCEDURE myRollup(
        tableName IN VARCHAR2, 
        numberOfAttributes IN NUMBER,
        attributeNames IN VARCHAR2,
        outputCursor OUT SYS_REFCURSOR)  
    AS
        attr1 VARCHAR2(100) := '';
        attr2 VARCHAR2(100) := '';
        attr3 VARCHAR2(100) := '';
        attr4 VARCHAR2(100) := '';
        attr5 VARCHAR2(100) := '';
        
        --Use a different regex to split input values based on number of parameters passed.
        attributeSplitRegex1 VARCHAR2(100) := '^(.*)';
        attributeSplitRegex2 VARCHAR2(100) := '^(.*)\, ?(.*)'; 
        attributeSplitRegex3 VARCHAR2(100) := '^(.*)\, ?(.*)\, ?(.*)'; 
        attributeSplitRegex4 VARCHAR2(100) := '^(.*)\, ?(.*)\, ?(.*)\, ?(.*)'; 
        attributeSplitRegex5 VARCHAR2(100) := '^(.*)\, ?(.*)\, ?(.*)\, ?(.*)\, ?(.*)'; 
        
        selectText VARCHAR2(4000);
        
        invalidAttributeNumberException EXCEPTION;
        
    BEGIN
        
        --gather input attribute names and build query
        CASE (numberOfAttributes)
            WHEN 1 THEN
                attr1 := REGEXP_SUBSTR(attributeNames, attributeSplitRegex1, 1, 1, NULL, 1);
                
                selectText := 'SELECT -1 AS ' || attr1 || ', COUNT(*) ' ||
                              'FROM ' || tableName || ' ' ||  
                              
                              'UNION ' ||
                              
                              'SELECT ' || attr1 || ', COUNT(*) ' ||
                              'FROM ' || tableName || ' ' ||
                              'GROUP BY ' || attr1;
                       
            WHEN 2 THEN
                attr1 := REGEXP_SUBSTR(attributeNames, attributeSplitRegex2, 1, 1, NULL, 1);
                attr2 := REGEXP_SUBSTR(attributeNames, attributeSplitRegex2, 1, 1, NULL, 2);
                
                selectText := 'SELECT -1 AS ' || attr1 || ', -1 AS ' || attr2 || ', COUNT(*) ' ||
                              'FROM ' || tableName || ' ' ||  
                              
                              'UNION ' ||
                              
                              'SELECT ' || attr1 || ', -1 AS ' || attr2 || ', COUNT(*) ' ||
                              'FROM ' || tableName || ' ' ||
                              'GROUP BY ' || attr1 || ' ' ||
                              
                              'UNION ' ||
                              
                              'SELECT ' || attr1 || ', ' || attr2 || ', COUNT(*) ' ||
                              'FROM ' || tableName || ' ' ||
                              'GROUP BY ' || attr1 || ', ' || attr2;
                                                     
            WHEN 3 THEN
                attr1 := REGEXP_SUBSTR(attributeNames, attributeSplitRegex3, 1, 1, NULL, 1);
                attr2 := REGEXP_SUBSTR(attributeNames, attributeSplitRegex3, 1, 1, NULL, 2);
                attr3 := REGEXP_SUBSTR(attributeNames, attributeSplitRegex3, 1, 1, NULL, 3);
                
                selectText := 'SELECT -1 AS ' || attr1 || ', -1 AS ' || attr2 || ', -1 AS ' || attr3 || ', COUNT(*) ' ||
                              'FROM ' || tableName || ' ' ||  
                              
                              'UNION ' ||
                              
                              'SELECT ' || attr1 || ', -1 AS ' || attr2 || ', -1 AS ' || attr3 || ', COUNT(*) ' ||
                              'FROM ' || tableName || ' ' ||
                              'GROUP BY ' || attr1 || ' ' ||
                              
                              'UNION ' ||
                              
                              'SELECT ' || attr1 || ', ' || attr2 || ', -1 AS ' || attr3 || ', COUNT(*) ' ||
                              'FROM ' || tableName || ' ' ||
                              'GROUP BY ' || attr1 || ', ' || attr2 || ' ' ||
                              
                              'UNION ' || 
                              
                              'SELECT ' || attr1 || ', ' || attr2 || ', ' || attr3 || ', COUNT(*) ' ||
                              'FROM ' || tableName || ' ' ||
                              'GROUP BY ' || attr1 || ', ' || attr2 || ', ' || attr3;
            WHEN 4 THEN
                attr1 := REGEXP_SUBSTR(attributeNames, attributeSplitRegex4, 1, 1, NULL, 1);
                attr2 := REGEXP_SUBSTR(attributeNames, attributeSplitRegex4, 1, 1, NULL, 2);
                attr3 := REGEXP_SUBSTR(attributeNames, attributeSplitRegex4, 1, 1, NULL, 3);
                attr4 := REGEXP_SUBSTR(attributeNames, attributeSplitRegex4, 1, 1, NULL, 4);
                
                selectText := 'SELECT -1 AS ' || attr1 || ', -1 AS ' || attr2 || ', -1 AS ' || attr3 || ', -1 AS ' || attr4 || ', COUNT(*) ' ||
                              'FROM ' || tableName || ' ' ||  
                              
                              'UNION ' ||
                              
                              'SELECT ' || attr1 || ', -1 AS ' || attr2 || ', -1 AS ' || attr3 || ', -1 AS ' || attr4 || ', COUNT(*) ' ||
                              'FROM ' || tableName || ' ' ||
                              'GROUP BY ' || attr1 || ' ' ||
                              
                              'UNION ' ||
                              
                              'SELECT ' || attr1 || ', ' || attr2 || ', -1 AS ' || attr3 || ', -1 AS ' || attr4 || ', COUNT(*) ' ||
                              'FROM ' || tableName || ' ' ||
                              'GROUP BY ' || attr1 || ', ' || attr2 || ' ' ||
                              
                              'UNION ' || 
                              
                              'SELECT ' || attr1 || ', ' || attr2 || ', ' || attr3 || ', -1 AS ' || attr4 || ', COUNT(*) ' ||
                              'FROM ' || tableName || ' ' ||
                              'GROUP BY ' || attr1 || ', ' || attr2 || ', ' || attr3 || ' ' ||
                              
                              'UNION ' || 
                              
                              'SELECT ' || attr1 || ', ' || attr2 || ', ' || attr3 || ', ' || attr4 || ', COUNT(*) ' ||
                              'FROM ' || tableName || ' ' ||
                              'GROUP BY ' || attr1 || ', ' || attr2 || ', ' || attr3 || ', ' || attr4;
            WHEN 5 THEN
                attr1 := REGEXP_SUBSTR(attributeNames, attributeSplitRegex5, 1, 1, NULL, 1);
                attr2 := REGEXP_SUBSTR(attributeNames, attributeSplitRegex5, 1, 1, NULL, 2);
                attr3 := REGEXP_SUBSTR(attributeNames, attributeSplitRegex5, 1, 1, NULL, 3);
                attr4 := REGEXP_SUBSTR(attributeNames, attributeSplitRegex5, 1, 1, NULL, 4);
                attr5 := REGEXP_SUBSTR(attributeNames, attributeSplitRegex5, 1, 1, NULL, 5);
                
                selectText := 'SELECT -1 AS ' || attr1 || ', -1 AS ' || attr2 || ', -1 AS ' || attr3 || ', -1 AS ' || attr4 || ', -1 AS ' || attr5 || ', COUNT(*) ' ||
                              'FROM ' || tableName || ' ' ||  
                              
                              'UNION ' ||
                              
                              'SELECT ' || attr1 || ', -1 AS ' || attr2 || ', -1 AS ' || attr3 || ', -1 AS ' || attr4 || ', -1 AS ' || attr5 || ', COUNT(*) ' ||
                              'FROM ' || tableName || ' ' ||
                              'GROUP BY ' || attr1 || ' ' ||
                              
                              'UNION ' ||
                              
                              'SELECT ' || attr1 || ', ' || attr2 || ', -1 AS ' || attr3 || ', -1 AS ' || attr4 || ', -1 AS ' || attr5 || ', COUNT(*) ' ||
                              'FROM ' || tableName || ' ' ||
                              'GROUP BY ' || attr1 || ', ' || attr2 || ' ' ||
                              
                              'UNION ' || 
                              
                              'SELECT ' || attr1 || ', ' || attr2 || ', ' || attr3 || ', -1 AS ' || attr4 || ', -1 AS ' || attr5 || ', COUNT(*) ' ||
                              'FROM ' || tableName || ' ' ||
                              'GROUP BY ' || attr1 || ', ' || attr2 || ', ' || attr3 || ' ' ||
                              
                              'UNION ' || 
                              
                              'SELECT ' || attr1 || ', ' || attr2 || ', ' || attr3 || ', ' || attr4 || ', -1 AS ' || attr5 || ', COUNT(*) ' ||
                              'FROM ' || tableName || ' ' ||
                              'GROUP BY ' || attr1 || ', ' || attr2 || ', ' || attr3 || ', ' || attr4 || ' ' ||
                              
                              'UNION ' || 
                              
                              'SELECT ' || attr1 || ', ' || attr2 || ', ' || attr3 || ', ' || attr4 || ', ' || attr5 || ', COUNT(*) ' ||
                              'FROM ' || tableName || ' ' ||
                              'GROUP BY ' || attr1 || ', ' || attr2 || ', ' || attr3 || ', ' || attr4 || ', ' || attr5;
            ELSE
                RAISE invalidAttributeNumberException;
        END CASE;
            
        IF (attr1 IS NOT NULL) THEN DBMS_OUTPUT.PUT_LINE('attr1: ' || attr1); END IF;
        IF (attr2 IS NOT NULL) THEN DBMS_OUTPUT.PUT_LINE('attr2: ' || attr2); END IF;
        IF (attr3 IS NOT NULL) THEN DBMS_OUTPUT.PUT_LINE('attr3: ' || attr3); END IF;
        IF (attr4 IS NOT NULL) THEN DBMS_OUTPUT.PUT_LINE('attr4: ' || attr4); END IF;
        IF (attr5 IS NOT NULL) THEN DBMS_OUTPUT.PUT_LINE('attr5: ' || attr5); END IF;
        
        --print the resulting query
        DBMS_OUTPUT.PUT_LINE(selectText);
        
        --return a cursor that points to the results of this query
        OPEN outputCursor FOR selectText;
            
    EXCEPTION
        WHEN invalidAttributeNumberException THEN
            RAISE_APPLICATION_ERROR(-20000, 'An invalid number of attributes was entered. Please pass 1 to 5 attribute names, delimited by commas.');
    END;
/

DROP TABLE RollupTest;
CREATE TABLE RollupTest(
    year NUMBER(4),
    month NUMBER(2),
    day NUMBER(2),
    hour NUMBER(2),
    minute NUMBER(2),
    second NUMBER(2)
);

INSERT INTO RollupTest VALUES(2018, 01, 01, 01, 01, 01);
INSERT INTO RollupTest VALUES(2018, 01, 01, 01, 01, 02);
INSERT INTO RollupTest VALUES(2018, 01, 01, 01, 01, 03);
INSERT INTO RollupTest VALUES(2018, 01, 01, 01, 02, 01);
INSERT INTO RollupTest VALUES(2018, 01, 01, 01, 02, 02);
INSERT INTO RollupTest VALUES(2018, 01, 01, 01, 02, 03);
INSERT INTO RollupTest VALUES(2018, 01, 01, 01, 03, 01);
INSERT INTO RollupTest VALUES(2018, 01, 01, 01, 03, 02);
INSERT INTO RollupTest VALUES(2018, 01, 01, 01, 03, 03);
INSERT INTO RollupTest VALUES(2018, 01, 01, 01, 04, 01);
INSERT INTO RollupTest VALUES(2018, 01, 01, 01, 04, 02);
INSERT INTO RollupTest VALUES(2018, 01, 01, 01, 04, 03);

DECLARE
    tableName VARCHAR2(100) := 'RollupTest';
    numberOfAttributes NUMBER := 5;
    attributeNames VARCHAR2(100) := 'month, day, hour, minute, second';
    outputCursor SYS_REFCURSOR;
BEGIN
    myRollup(tableName, numberOfAttributes, attributeNAmes, outputCursor);
END;

--Example output from "myRollup('RollupTest', 3, 'hour, minute, second', outputCursor);" is:
--
--SELECT -1 AS hour, -1 AS minute, -1 AS second, COUNT(*) FROM RollupTest 
--UNION 
--SELECT hour, -1 AS minute, -1 AS second, COUNT(*) FROM RollupTest GROUP BY hour 
--UNION 
--SELECT hour, minute, -1 AS second, COUNT(*) FROM RollupTest GROUP BY hour, minute 
--UNION 
--SELECT hour, minute, second, COUNT(*) FROM RollupTest GROUP BY hour, minute, second
--
--When executed, this query returns:
--      HOUR     MINUTE     SECOND   COUNT(*)
------------ ---------- ---------- ----------
--        -1         -1         -1         12
--         1         -1         -1         12
--         1          1         -1          3
--         1          1          1          1
--         1          1          2          1
--         1          1          3          1
--         1          2         -1          3
--         1          2          1          1
--         1          2          2          1
--         1          2          3          1
--         1          3         -1          3
--         1          3          1          1
--         1          3          2          1
--         1          3          3          1
--         1          4         -1          3
--         1          4          1          1
--         1          4          2          1
--         1          4          3          1
