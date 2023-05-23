DBCC CHECKIDENT ('RapBands', RESEED, 1);

INSERT INTO RapBands (bandName, foundationDate, breakupDate)
VALUES ('Band A', '2022-01-01', '2023-01-01');


WAITFOR DELAY '00:00:05'

BEGIN TRANSACTION
UPDATE RapBands SET foundationDate = '2022-01-01' WHERE bandID = 1

WAITFOR DELAY '00:00:05'

COMMIT TRANSACTION


DELETE FROM RapBands


-- when an update statement encounters a conflict due to locks held by another transaction, 
-- it will not modify any rows and return a specific code or indication that can be used to 
-- identify the conflict