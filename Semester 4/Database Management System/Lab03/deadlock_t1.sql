DBCC CHECKIDENT ('RapBands', RESEED, 1);

DBCC CHECKIDENT ('RapBandFans', RESEED, 1);

INSERT INTO RapBands
	(bandName, foundationDate, breakupDate)
VALUES
	('Controlul Tehnic de Calitate', '1997', null),
	('Parazitii', '1994', null),
	('BUG Mafia', '1993', null),
	('La Familia', '1997', null),
	('Specii', '2008', null);

INSERT INTO RapBandFans 
	(fullName, dateOfBirth,	favouriteSong, hobby)
VALUES
	('Iulian Parvu', '2000/12/15', 'Una din Doua', 'cooking'),
	('Octavian Tanase', '1991/02/24', 'Onoare', 'meditation'),
	('Marian Popescu', '1995/11/03', 'Azi nu', 'reading'),
	('Mihai Bita', '1979/02/08', 'Spune-mi', 'drinking'),
	('Marius Stelian Craciun', '1980/04/19', 'Ambrozie', 'reading');

-- Transaction 1
BEGIN TRANSACTION
UPDATE RapBands SET foundationDate = '2022-01-01' WHERE bandID = 1;

WAITFOR DELAY '00:00:10';

UPDATE RapBandFans SET hobby = 'Dancing' WHERE rapBandFanID = 1;
COMMIT TRANSACTION;


SELECT * FROM RapBands
SELECT * FROM RapBandFans

DELETE FROM RapBands
DELETE FROM RapBandFans

-- how to solve it:
-- using  resource ordering, which ensures that 
-- transactions always request resources in a predefined order