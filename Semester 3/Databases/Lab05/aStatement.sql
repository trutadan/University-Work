-- Write queries on Ta such that their execution plans contain the operators below.

-- clustered index scan;
SELECT * 
	FROM RapBands
WHERE YEAR(foundationDate) = 2022

-- clustered index seek;
SELECT * 
	FROM RapBands
WHERE YEAR(foundationDate) > 2010 AND YEAR(foundationDate) <= 2020

-- nonclustered index scan;
SELECT numberOfFollowers
	FROM RapBands
ORDER BY numberOfFollowers

-- nonclustered index seek;
SELECT numberOfFollowers
	FROM RapBands
WHERE numberOfFollowers BETWEEN 10000000 AND 100000000

-- key lookup.
SELECT bandName, numberOfFollowers
	FROM RapBands
WHERE numberOfFollowers = 20000