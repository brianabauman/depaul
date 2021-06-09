SET SERVEROUTPUT ON;

DECLARE
    new_salary NUMBER(9,2);
BEGIN
    new_salary := &starting_salary * (1 + &raise_percentage / 100);
    DBMS_OUTPUT.PUT_LINE('Your new salary is ' || new_salary);
END;