use Rap;

-- all rap fans that are also rappers (using intersect)
SELECT fullName 
	FROM Rappers

INTERSECT

SELECT fullName
	FROM RapperFans

-- all rap fans that are also rappers (using in)
SELECT fullName 
	FROM Rappers 
WHERE fullName IN (
	SELECT fullName
		FROM RapperFans
);