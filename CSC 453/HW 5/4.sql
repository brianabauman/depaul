CREATE OR REPLACE TRIGGER NewContract
    BEFORE INSERT ON CONTRACT
    FOR EACH ROW
        DECLARE
            contractCount NUMBER(1);
            taskFullException EXCEPTION;
    
        BEGIN
            SELECT ContractCount
            INTO contractCount
            FROM TASK
            WHERE TaskID = :NEW.TaskID;
            
            IF (contractCount < 3) THEN
                --allow the insert to continue 
                UPDATE TASK
                SET ContractCount = ContractCount + 1
                WHERE TaskID = :NEW.TaskID;
                
            ELSE
                RAISE taskFullException;
            END IF;
        EXCEPTION
            WHEN taskFullException THEN
                RAISE_APPLICATION_ERROR(-20000, 'The task is full.');
        END;
/

CREATE OR REPLACE TRIGGER EndContract
    AFTER DELETE ON CONTRACT
    FOR EACH ROW
        DECLARE
            contractCount NUMBER(1);
            
        BEGIN
            SELECT ContractCount
            INTO contractCount
            FROM TASK
            Where TaskID = :OLD.TaskID;
            
            UPDATE TASK
            SET ContractCount = ContractCount - 1
            WHERE TaskID = :OLD.TaskID;
        
        END;
/

CREATE OR REPLACE TRIGGER NoChanges
    BEFORE UPDATE ON CONTRACT
        DECLARE 
            noUpdatesException EXCEPTION;
        
        BEGIN
            RAISE noUpdatesException;
        
        EXCEPTION 
            WHEN noUpdatesException THEN
                RAISE_APPLICATION_ERROR(-20001, 'No updates allowed to the CONTRACT table.');
        END;
/

INSERT INTO CONTRACT VALUES (333, 1, 1.0); --succeeds
INSERT INTO CONTRACT VALUES (333, 2, 1.0); --succeeds
INSERT INTO CONTRACT VALUES (333, 3, 1.0); --succeeds
INSERT INTO CONTRACT VALUES (333, 4, 1.0); --fails

DELETE FROM CONTRACT WHERE TaskID = 333 AND WorkerID IN (2,3);

UPDATE CONTRACT SET TaskID = 0; --fails