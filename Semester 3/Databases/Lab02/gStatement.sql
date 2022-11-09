--  rappers that have at least one fan
SELECT DISTINCT t.fullName, t.stageName
	FROM (
		SELECT R.fullName, R.stageName, FA.rapperFanID
			FROM Rappers R
				INNER JOIN RapperFanAdoration FA 
					ON FA.rapperID = R.rapperID
	) t
		ORDER BY t.fullName DESC 


-- rap bands that organise concerts with over 2000 capacity and a price less than 2000
SELECT DISTINCT t.bandName, t.concertLocation
	FROM (
		SELECT B.bandName, C.concertLocation, C.capacity, CC.price
			FROM RapBands B
				INNER JOIN RapBandConcertContracts CC
					ON CC.bandID = B.bandID
				INNER JOIN RapBandConcerts C
					ON C.bandConcertID = CC.bandConcertID
	) t
WHERE t.capacity >= 2000 AND t.price <= 2000
