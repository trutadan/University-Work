-- bands that are newer than the birth date of all its fans with a hobby (using ALL)
SELECT B.bandName
	FROM RapBands B
WHERE B.foundationDate > ALL (
    SELECT F.dateOfBirth
		FROM RapBandFans F
    WHERE F.hobby IS NOT NULL
);


-- bands that are newer than the birth date of all its fans with a hobby (using MAX aggregator operator)
SELECT B.bandName
	FROM RapBands B
WHERE B.foundationDate > (
    SELECT MAX(F.dateOfBirth)
		FROM RapBandFans F
    WHERE F.hobby IS NOT NULL
);


-- print rappers with fans 2 times younger than them (using ANY)
SELECT R.fullName
	FROM Rappers R
WHERE DATEDIFF(day, GETDATE(), R.dateOfBirth) / 2 > ANY (
	SELECT DATEDIFF(day, GETDATE(), F.dateOfBirth)
		FROM RapperFans F
	WHERE F.rapperFanID = R.rapperID
);


-- print rappers with fans 2 times younger than them (using MIN aggregator operator)
SELECT R.fullName
	FROM Rappers R
WHERE DATEDIFF(day, GETDATE(), R.dateOfBirth) / 2 > (
	SELECT DATEDIFF(day, GETDATE(), MIN(F.dateOfBirth))
		FROM RapperFans F
	WHERE F.rapperFanID = R.rapperID
);


-- songs that belong to rap bands which did not breakup (using ANY)
SELECT S.title
	FROM RapSongs S
WHERE S.bandAlbumID = ANY (
	SELECT A.albumID
		FROM RapBandAlbums A
			INNER JOIN RapBands B
		ON A.bandID = B.bandID
);


-- songs that belong to rap bands which did not breakup (using IN aggregator operator)
SELECT S.title
	FROM RapSongs S
WHERE S.bandAlbumID IN (
	SELECT A.albumID
		FROM RapBandAlbums A
			INNER JOIN RapBands B
		ON A.bandID = B.bandID
);


-- the band albums with the most songs after the year 2001 (using ALL)
SELECT A1.title, A1.numberOfSongs
	FROM RapBandAlbums A1 
WHERE A1.numberOfSongs = ANY (
	SELECT A2.numberOfSongs
		FROM RapBandAlbums A2
	WHERE 2001 < YEAR(A2.releaseDate)
);


-- the band albums with the most songs that got released after the year 2001 (using IN aggregator operator)
SELECT A1.title, A1.numberOfSongs
	FROM RapBandAlbums A1 
WHERE A1.numberOfSongs IN (
	SELECT A2.numberOfSongs
		FROM RapBandAlbums A2
	WHERE 2001 < YEAR(A2.releaseDate)
);