use Rap;

-- all members from Controlul Tehnic de Calitate and Parazitii are from Bucuresti
UPDATE Rappers
	SET birthPlace = 'Bucuresti'
WHERE bandID IN (1, 2);


-- no stage name is specified 
UPDATE Rappers
	SET	stageName = fullName
WHERE stageName IS NULL;


-- the price of concerts is decreased because in november is black friday
UPDATE RapperConcertContracts
	SET price = price - 0.2 * price
WHERE CONVERT(VARCHAR(25), concertDatetime, 126) LIKE '%-11-%';


-- due to covid restrictions
UPDATE RapBandConcertContracts
	SET duration = '00:30:00'
WHERE concertDatetime between '2019/12/01' and '2021/02/01';