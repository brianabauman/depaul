DROP TABLE ZipCode;
CREATE TABLE ZipCode (
    zip NUMBER(5),
    city VARCHAR(20),
    state CHAR(2),
    latitude FLOAT(38),
    longitude FLOAT(38),
    timezone NUMBER(2),
    dst NUMBER(1)
);