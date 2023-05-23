DBCC CHECKIDENT ('RapBands', RESEED, 1);

INSERT INTO RapBands
	(bandName, foundationDate, breakupDate)
VALUES
	('Controlul Tehnic de Calitate', '1997', null)

-- Transaction 1
BEGIN TRAN

WAITFOR DELAY '00:00:05'

UPDATE RapBands SET bandName = 'CTC'
WHERE bandName = 'Controlul Tehnic de Calitate'

COMMIT TRAN


DELETE FROM RapBands


-- Transaction 2 reads the RapBands table with the READ COMMITTED isolation level
-- Transaction 1 modifies the band names in the RapBands table and commits the changes
-- Transaction 2 re-reads the RapBands table after the modifications made by Transaction 1
-- The re-read shows different data compared to the initial read, resulting in a non-repeatable read. 
-- The band names have been updated, and Transaction 2 sees the updated values.