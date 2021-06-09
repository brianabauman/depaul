DROP TABLE Restaurant_Locations;
CREATE TABLE Restaurant_Locations (
    rID NUMBER(38,0),
    name VARCHAR(100 BYTE),
    address VARCHAR(50 BYTE),
    city VARCHAR(20 BYTE),
    state CHAR(2),
    zipcode NUMBER(5),
    cuisine VARCHAR(100 BYTE)
);


DECLARE     
    CURSOR c1
    IS 
        SELECT rID
             , name
             , address
             , cuisine
        FROM Restaurant;
        
    restaurantRow Restaurant%ROWTYPE;
    address VARCHAR(50 BYTE);
    city VARCHAR(20 BYTE);
    state CHAR(2);
    zipcode NUMBER(5);
    
BEGIN
    --Clear out whatever currently exists in the Restaurant_Locations table
    DELETE FROM Restaurant_Locations;
            
    OPEN c1;             
    LOOP
        --Fetch the next row from the Restaurant table
        FETCH c1 INTO restaurantRow;
        
        --Proceed only if more data exists
        IF c1%NOTFOUND THEN
            EXIT;
        ELSE
            address := REGEXP_SUBSTR(restaurantRow.address, '(\d* (N|S|E|W) \w* (Ave|St|Rd|Pl|Blvd))');
            city := REGEXP_SUBSTR(restaurantRow.address, '(\w*)\,', 1, 1, NULL, 1);
            state := REGEXP_SUBSTR(restaurantRow.address, '\, (\w{2})', 1, 1, NULL, 1);
            zipcode := REGEXP_SUBSTR(restaurantRow.address, '\, \w{2} (\d{5})', 1, 1, NULL, 1);
            
            INSERT INTO Restaurant_Locations VALUES (
                restaurantRow.rID,
                restaurantRow.name,
                address,
                city,
                state,
                zipcode,
                restaurantRow.cuisine
            );
        END IF;
    END LOOP;
    
    CLOSE c1;
END;
    

