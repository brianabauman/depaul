--(1)
SELECT name FROM restaurant WHERE cuisine = 'Indian';

--(2)
SELECT name, stars FROM restaurant A, rating B WHERE B.rID = A.rID AND B.stars > 3 ORDER BY stars;

--(3)
SELECT name FROM restaurant A WHERE NOT EXISTS (SELECT * FROM rating B WHERE B.rID = A.rID);

--(4)
SELECT name FROM reviewer A, rating B WHERE B.vID = A.vID AND B.ratingdate IS NULL;

--(5)
SELECT C.name, D.name FROM rating A, rating B, reviewer C, restaurant D WHERE B.vID = A.vID AND B.rID = A.rID AND B.stars > A.stars
AND C.vID = B.vID AND D.rID = B.rID; 

--(6)
SELECT A.name, MAX(B.stars) FROM restaurant A, rating B WHERE EXISTS (SELECT * FROM rating WHERE rID = A.rID) AND B.rID = A.rID GROUP BY A.name ORDER BY A.name;

--(7)
SELECT A.name, (MAX(B.stars) - MIN(B.stars)) FROM restaurant A, rating B WHERE B.rID = A.rID GROUP BY A.name ORDER BY (MAX(B.stars) - MIN(B.stars)) DESC, A.name;

--(8)
SELECT (indian.avgStars - chinese.avgStars) --get difference between indian average and chinese average
FROM (SELECT AVG(avgScore) as avgStars --get average rating of all indian restaurants
      FROM (SELECT A.name --get average rating of each indian restaurant
                 , A.cuisine
                 , AVG(B.stars) AS avgScore 
            FROM restaurant A
               , rating B 
            WHERE B.rID = A.rID 
              AND A.cuisine = 'Indian'
            GROUP BY A.name
                   , A.cuisine) 
      GROUP BY cuisine) indian
   , (SELECT AVG(avgScore) as avgStars --get average rating of all chinese restaurants
      FROM (SELECT A.name --get average rating of each chinese restaurant
                 , A.cuisine
                 , AVG(B.stars) AS avgScore 
            FROM restaurant A
               , rating B 
            WHERE B.rID = A.rID 
              AND A.cuisine = 'Chinese'
            GROUP BY A.name
                   , A.cuisine) 
      GROUP BY cuisine) chinese