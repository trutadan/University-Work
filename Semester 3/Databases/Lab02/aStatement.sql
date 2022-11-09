use Rap;

-- union of the first rapper and its albums
SELECT fullName from Rappers R
	WHERE R.rapperID = 1

UNION 

SELECT title from RapperAlbums A
	WHERE A.rapperID = 1;


-- rappers who have been born in the most popular counties in the most popular times
SELECT fullName from Rappers
	WHERE (birthPlace = 'Bucuresti' AND YEAR(dateOfBirth) < 1980) OR (birthPlace = 'Constanta' AND YEAR(dateOfBirth) < 1985);