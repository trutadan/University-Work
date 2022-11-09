-- top 50% birth locations with at least 2 rappers
SELECT TOP 50 PERCENT R.birthPlace, COUNT(*) AS rappers
	FROM Rappers R
WHERE R.birthPlace IS NOT NULL
	GROUP BY R.birthPlace
		HAVING COUNT(*) > 1



-- birth year of the rappers' fans togheter with the number of fans of each year multiplied by 2, given the estimation that in the future the number of fans will double
SELECT YEAR(dateOfBirth) AS yearOfBirth, COUNT(*) * 2 AS numberOfFans 
	FROM RapperFans
GROUP BY YEAR(dateOfBirth)


-- rap bands that earn the most, given that they will receive a bonus of 10% of their income as a gift
SELECT B.bandName, tt.totalEarnings + tt.totalEarnings * 0.1 AS totalEarnings 
	FROM RapBands B, (
SELECT C.bandID, SUM(C.price) AS totalEarnings
	FROM RapBandConcertContracts C
GROUP BY C.bandID
	HAVING SUM(C.price) = (
		SELECT MAX(t.earnings)
			FROM (
		SELECT SUM(CC.price) earnings
			FROM RapBandConcertContracts CC
		GROUP BY CC.bandID
		) t
	)
)tt
WHERE B.bandID = tt.bandID 

-- top 3 rappers that are younger than the average age of all rappers but are closest to that age and their corresponding age, for the next year
SELECT TOP 3 R.fullName, R.stageName, t.age + 1 AS age
	FROM Rappers R, (
SELECT R.rapperID, DATEDIFF(year, R.dateOfBirth, GETDATE()) AS age
	FROM Rappers R	
GROUP BY R.rapperID, DATEDIFF(year, R.dateOfBirth, GETDATE()) 
	HAVING DATEDIFF(year, R.dateOfBirth, GETDATE()) < (
		SELECT AVG(DATEDIFF(year, RR.dateOfBirth, GETDATE()))
			FROM Rappers RR
		)
) t
WHERE t.rapperID = R.rapperID
ORDER by age DESC