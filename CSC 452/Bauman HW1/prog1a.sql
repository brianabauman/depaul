CREATE TABLE STUDENT
(
    student_id VARCHAR(25) PRIMARY KEY, 
    std_name VARCHAR(25),
    home_phone CHAR(12),
    total_credits NUMBER,
    gpa NUMBER(3, 2),
    advisor_id VARCHAR(25)
);

CREATE TABLE COURSE
(
    course# CHAR(12) PRIMARY KEY,
    credit_hours NUMBER,
    time NUMBER,
    location VARCHAR(25),
    faculty_id VARCHAR(25)
);

CREATE TABLE ENROLLMENT 
(
    student_id VARCHAR(25),
    course# CHAR(12),
    grade NUMBER(5, 2),
    CONSTRAINT enrollment_pk PRIMARY KEY (student_id, course#)
);

CREATE TABLE FACULTY
(
    faculty_id VARCHAR(25) PRIMARY KEY,
    fac_name VARCHAR(25),
    office VARCHAR(25),
    salary NUMBER(10, 2)
);