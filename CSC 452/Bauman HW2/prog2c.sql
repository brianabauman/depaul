SET SERVEROUTPUT ON;

DECLARE 
    x NUMBER(3) := 0;
BEGIN    
    IF &N IS NOT NULL THEN
        x := &N;
    END IF;
    
    FOR i IN 1..x
    LOOP
        CASE MOD(i, 2)
        WHEN 0 THEN 
            DBMS_OUTPUT.PUT_LINE(i || ' is even.');
        WHEN 1 THEN
            DBMS_OUTPUT.PUT_LINE(i || ' is odd.');
        END CASE;
    END LOOP;
END;