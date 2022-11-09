use Rap;

-- all fans of rap bands which are not rappers
SELECT fullName
	FROM RapBandFans

EXCEPT

SELECT fullName
	FROM Rappers;


-- all fans of rap bands which are rappers
SELECT fullName
	FROM Rappers
WHERE fullName 
	NOT IN (
		SELECT fullName
		FROM RapBandFans
	);
