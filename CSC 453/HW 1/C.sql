--(1)
SELECT RentalCompany FROM ByCar WHERE Mileage >= 27;

--(2)
SELECT TID FROM Trips WHERE TravelMode = 'Train' AND Fare > 150;

--(3)
SELECT TID, Fare FROM Trips WHERE TripState = 'Non-US';

--(4)
SELECT TID FROM Trips NATURAL JOIN ByPlane WHERE Class = 'Business' AND Fare > 1000;

--(5)
SELECT A.TID FROM Trips A CROSS JOIN Trips B WHERE A.TravelMode = 'Car' AND B.TravelMode = 'Train' AND A.Fare > B.Fare;

--(6)
SELECT A.TID, B.TID FROM ByCar A CROSS JOIN ByCar B WHERE B.Mileage = A.Mileage AND B.TID > A.TID;

--(7)
SELECT A.TID, B.TID FROM ByTrain A CROSS JOIN ByTrain B WHERE B.TrainSpeed <> A.TrainSpeed AND B.TID > A.TID;

--(8)
SELECT A.TID, B.TID FROM Trips A CROSS JOIN Trips B WHERE B.TripState = A.TripState AND B.TravelMode = A.TravelMode AND B.TID > A.TID;

--(9)
SELECT A.TripState FROM Trips A CROSS JOIN Trips B CROSS JOIN Trips C WHERE A.TripState = B.TripState AND B.TripState = C.TripState 
   AND A.TravelMode = 'Car' AND B.TravelMode = 'Train' AND C.TravelMode = 'Plane';
   
--(10a)
SELECT * FROM Trips WHERE Fare = (SELECT MAX(Fare) FROM Trips);

--(10b)
SELECT * FROM Trips WHERE Fare = (SELECT MIN(Fare) FROM Trips);
