--(a)
SELECT A.fac_name   
     , B.std_name
FROM FACULTY A LEFT OUTER JOIN STUDENT B
       ON B.advisor_id = A.faculty_id
       
--(b)
SELECT std_name
     , home_phone
FROM STUDENT

MINUS

SELECT std_name
     , home_phone
FROM STUDENT A
   , ENROLLMENT B
WHERE B.student_id = A.student_id

--(c)
SELECT A.std_name
     , B.total_credits
     , B.gpa
FROM STUDENT A,
     (SELECT A.total_credits
           , MAX(A.gpa) AS gpa
      FROM STUDENT A
      GROUP BY A.total_credits) B
WHERE B.gpa = A.gpa
  AND B.total_credits = A.total_credits
ORDER BY B.total_credits DESC

--(d)
SELECT C.std_name
     , D.course#
FROM (SELECT student_id
           , MIN(grade) AS grade
      FROM ENROLLMENT A
      GROUP BY student_id) A
   , ENROLLMENT B
   , STUDENT C
   , COURSE D
WHERE B.student_id = A.student_id
  AND B.grade = A.grade
  AND C.student_id = A.student_id
  AND D.course# = B.course#
     
--(e)
SELECT fac_name
FROM FACULTY
WHERE faculty_id NOT IN (SELECT advisor_id FROM STUDENT)