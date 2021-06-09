DECLARE
    TYPE deptNoList IS TABLE OF NUMBER;
    deptNos deptNoList := deptNoList(10, 20, 30, 40, 50);
    TYPE deptNameList IS TABLE OF VARCHAR2(16);
    deptNames deptNameList := deptNameList('ACCOUNTING', 'RESEARCH', 'SALES', 'OPERATIONS', 'MARKETING');
    TYPE locList IS TABLE OF VARCHAR2(16);
    locs locList := locList('NEW YORK', 'DALLAS', 'CHICAGO', 'DALLAS', 'BOSTON');
BEGIN
    FORALL i IN 1..5
        INSERT INTO dept VALUES (deptNos(i), deptNames(i), locs(i));
END;