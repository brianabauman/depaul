SET SERVEROUTPUT ON;
SET VERIFY OFF;

DECLARE
    inpOldZipCode NUMBER(5) := &inpOldZipCode;
    inpNewZipCode NUMBER(5) := &inpNewZipCode;
    
    zip_code_dne EXCEPTION;
    dup_zip_code EXCEPTION;
    
    oldZipCodeExists NUMBER := 0;
    newZipCodeExists NUMBER := 0;
    
    oldCity VARCHAR2(20);
    
    CURSOR c_employee(zipCode NUMBER) IS SELECT ENO FROM EMPLOYEES WHERE ZIP = zipCode;
    CURSOR c_customer(zipCode NUMBER) IS SELECT CNO FROM CUSTOMERS WHERE ZIP = zipCode;
BEGIN
    --validate input
    SELECT COUNT(*) INTO oldZipCodeExists FROM ZIPCODES WHERE ZIP = inpOldZipCode;
    SELECT COUNT(*) INTO newZipCodeExists FROM ZIPCODES WHERE ZIP = inpNewZipCode;
    
    IF oldZipCodeExists <> 1 THEN
        RAISE zip_code_dne;
    ElSIF newZipCodeExists <> 0 THEN
        RAISE dup_zip_code;
    END IF;
    
    SELECT CITY INTO oldCity FROM ZIPCODES WHERE ZIP = inpOldZipCode;
    
    INSERT INTO ZIPCODES
    VALUES (inpNewZipCode, oldCity);
    
    FOR r_employee IN c_employee(inpOldZipCode) LOOP
        UPDATE EMPLOYEES SET ZIP = inpNewZipCode WHERE ENO = r_employee.ENO;
    END LOOP;
    
    FOR r_customer IN c_customer(inpOldZipCode) LOOP
        UPDATE CUSTOMERS SET ZIP = inpNewZipCode WHERE CNO = r_customer.CNO;
    END LOOP;
    
    DELETE FROM ZIPCODES
    WHERE ZIP = inpOldZipCode;
    
    DBMS_OUTPUT.PUT_LINE('Successfully updated zip code ' || inpOldZipCode || ' to ' || inpNewZipCode || '.');
    
EXCEPTION
    WHEN zip_code_dne THEN
        DBMS_OUTPUT.PUT_LINE('The ZIP code to be changed does not exist in the system!');
    WHEN dup_zip_code THEN
        DBMS_OUTPUT.PUT_LINE('The new ZIP code already exists in the system!');
    WHEN OTHERS THEN 
        DBMS_OUTPUT.PUT_LINE('Unexpected database error: ' || SQLERRM);
END;