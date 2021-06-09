DROP TABLE Loan;

CREATE TABLE Loan (
    Amount NUMBER(5),
    Loan_Date DATE,
    Loan_Title VARCHAR(100),
    Risk_Score NUMBER(3),
    Debt_To_Income_Ratio FLOAT,
    Zipcode NUMBER(5),
    State VARCHAR(2),
    Employment_Length NUMBER(1),
    Policy_Code NUMBER(1),
    
    PRIMARY KEY (Loan_Title, Loan_Date));