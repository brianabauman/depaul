SET SERVEROUTPUT ON;
SET VERIFY OFF;

BEGIN

    EXECUTE IMMEDIATE 'CREATE TABLE dept
    ( 
        DEPTNO NUMBER(3) PRIMARY KEY,
        DNAME VARCHAR2(16),
        LOC VARCHAR2(16)
    )';

    EXECUTE IMMEDIATE 'CREATE TABLE emp
    ( 
        EMPNO NUMBER(4) PRIMARY KEY,
        ENAME VARCHAR2(16),
        JOB VARCHAR2(16),
        MGR NUMBER(4),
        HIREDATE DATE,
        SAL NUMBER(7, 2),
        COMM NUMBER(7, 2),
        DEPTNO NUMBER(3) NOT NULL REFERENCES DEPT(DEPTNO)
    )';

    BEGIN
    
        EXECUTE IMMEDIATE('INSERT INTO dept
        VALUES(10, ''ACCOUNTING'', ''NEW YORK'')');
        SAVEPOINT deptSavePoint;
    
        EXECUTE IMMEDIATE('INSERT INTO dept
        VALUES(20, ''RESEARCH'', ''DALLAS'')');
        SAVEPOINT deptSavePoint;
        
        EXECUTE IMMEDIATE('INSERT INTO dept
        VALUES(30, ''SALES'', ''CHICAGO'')');
        SAVEPOINT deptSavePoint;
    
        EXECUTE IMMEDIATE('INSERT INTO dept
        VALUES(40, ''OPERATIONS'', ''WASHINGTON (D.C.)'')');
        SAVEPOINT deptSavePoint;
    
        EXECUTE IMMEDIATE('INSERT INTO dept
        VALUES(50, ''MARKETING'', ''BOSTON'')');
        COMMIT;
    EXCEPTION
        WHEN OTHERS THEN
            DBMS_OUTPUT.PUT_LINE('Database error encountered: ' || SQLERRM);
            DBMS_OUTPUT.PUT_LINE('Committing previous changes...');
            ROLLBACK TO deptSavePoint;
            COMMIT;
    END;

    BEGIN
    
        EXECUTE IMMEDIATE('INSERT INTO emp
        VALUES (7839, ''KING'', ''PRESIDENT'', NULL, ''17-NOV-81'', 5000, NULL, 10)');
        SAVEPOINT empSavePoint;
        
        EXECUTE IMMEDIATE('INSERT INTO emp
        VALUES (7698, ''BLAKE'', ''MANAGER'', 7839, ''01-MAY-81'', 2850, NULL, 30)');
        SAVEPOINT empSavePoint;
    
        EXECUTE IMMEDIATE('INSERT INTO emp
        VALUES (7782, ''CLARK'', ''MANAGER'', 7839, ''09-JUN-81'', 2450, NULL, 10)');
        SAVEPOINT empSavePoint;
    
        EXECUTE IMMEDIATE('INSERT INTO emp
        VALUES (7566, ''JONES'', ''MANAGER'', 7839, ''02-APR-81'', 2975, NULL, 20)');
        SAVEPOINT empSavePoint;
    
        EXECUTE IMMEDIATE('INSERT INTO emp
        VALUES (7654, ''MARTIN'', ''SALESMAN'', 7698, ''28-SEP-81'', 1250, 1400, 30)');
        SAVEPOINT empSavePoint;
    
        EXECUTE IMMEDIATE('INSERT INTO emp
        VALUES (7499, ''ALLEN'', ''SALESMAN'', 7698, ''20-FEB-81'', 1600, 300, 30)');
        SAVEPOINT empSavePoint;
    
        EXECUTE IMMEDIATE('INSERT INTO emp
        VALUES (7844, ''TURNER'', ''SALESMAN'', 7698, ''08-SEP-81'', 1500, NULL, 30)');
        SAVEPOINT empSavePoint;
    
        EXECUTE IMMEDIATE('INSERT INTO emp
        VALUES (7900, ''JAMES'', ''CLERK'', 7698, ''03-DEC-81'', 950, NULL, 30)');
        SAVEPOINT empSavePoint;
    
        EXECUTE IMMEDIATE('INSERT INTO emp
        VALUES (7521, ''WARD'', ''SALESMAN'', 7698, ''22-FEB-81'', 1250, 500, 30)');
        SAVEPOINT empSavePoint;
    
        EXECUTE IMMEDIATE('INSERT INTO emp
        VALUES (7902, ''FORD'', ''ANALYST'', 7566, ''03-DEC-81'', 3000, NULL, 20)');
        SAVEPOINT empSavePoint;
    
        EXECUTE IMMEDIATE('INSERT INTO emp
        VALUES (7369, ''SMITH'', ''CLERK'', 7902, ''17-DEC-81'', 800, NULL, 20)');
        SAVEPOINT empSavePoint;
    
        EXECUTE IMMEDIATE('INSERT INTO emp
        VALUES (7788, ''SCOTT'', ''ANALYST'', 7566, ''09-DEC-82'', 4000, NULL, 20)');
        SAVEPOINT empSavePoint;
    
        EXECUTE IMMEDIATE('INSERT INTO emp
        VALUES (7876, ''ADAMS'', ''CLERK'', 7788, ''12-JAN-83'', 1100, NULL, 20)');
        SAVEPOINT empSavePoint;
    
        EXECUTE IMMEDIATE('INSERT INTO emp
        VALUES (7934, ''MILLER'', ''CLERK'', 7782, ''22-JAN-82'', 1300, NULL, 10)');
        SAVEPOINT empSavePoint;
    
        EXECUTE IMMEDIATE('INSERT INTO emp
        VALUES (7698, ''BLAKE'', ''MANAGER'', 7839, ''01-MAY-81'', 2850, NULL, 30)');
        SAVEPOINT empSavePoint;
    
        EXECUTE IMMEDIATE('INSERT INTO emp
        VALUES  (7935, ''JONES'', ''ACCOUNT'', 7782, ''22-JAN-82'', 1700, NULL, 10)');
        COMMIT;
            
    EXCEPTION
        WHEN OTHERS THEN
            DBMS_OUTPUT.PUT_LINE('Database error encountered: ' || SQLERRM);
            DBMS_OUTPUT.PUT_LINE('Committing previous changes...');
            ROLLBACK TO empSavePoint;
            COMMIT;
    END;
END;