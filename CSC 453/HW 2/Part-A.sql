--(1)
SELECT name FROM products WHERE price <= 200;

--(2)
SELECT * FROM products WHERE price > 60 AND price < 120;

--(3)
SELECT name, price * 100 FROM products;

--(4)
SELECT A.name, price, B.name FROM products A, manufacturers B WHERE B.code = A.manufacturer;

--(5)
SELECT name FROM manufacturers A WHERE NOT EXISTS (SELECT manufacturer FROM products B WHERE B.manufacturer = A.code);

--(6)
SELECT A.name, B.name, B.price FROM manufacturers A, products B WHERE B.manufacturer = A.code AND B.price = (SELECT MAX(price) FROM products WHERE manufacturer = A.code);

--(7)
SELECT B.name, AVG(price) FROM products A, manufacturers B WHERE A.manufacturer = B.code GROUP BY B.name HAVING AVG(price) >= 150;