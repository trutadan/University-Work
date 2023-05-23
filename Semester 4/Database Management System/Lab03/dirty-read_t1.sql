DBCC CHECKIDENT ('RapBands', RESEED, 1);

INSERT INTO RapBands
	(bandName, foundationDate, breakupDate)
VALUES
	('Controlul Tehnic de Calitate', '1997', null),
	('Parazitii', '1994', null),
	('BUG Mafia', '1993', null),
	('La Familia', '1997', null),
	('Specii', '2008', null);

-- Transaction 1
BEGIN TRANSACTION

UPDATE RapBands SET foundationDate = '2022-01-01' WHERE bandName = 'Parazitii';
WAITFOR DELAY '00:00:10';

ROLLBACK TRANSACTION;


-- Transaction 1 starts and updates the RapBands table
-- Transaction 1 introduces a delay with WAITFOR DELAY '00:00:10'
-- Transaction 1 rolls back the changes made in the transaction
-- Transaction 2 starts with the READ UNCOMMITTED isolation level
-- Transaction 2 executes the first SELECT * FROM RapBands statement and reads the uncommitted changes made by Transaction 1. 
-- It will see the updated foundationDate for the 'Parazitii' band.
-- Transaction 2 introduces a delay with WAITFOR DELAY '00:00:15'.
-- Transaction 2 executes the second SELECT * FROM RapBands statement and still reads the uncommitted changes. 
-- However, in this case, it will not see the modified data since Transaction 1 has rolled back.