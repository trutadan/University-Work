SET DEADLOCK_PRIORITY HIGH

-- Transaction 2
BEGIN TRANSACTION
UPDATE RapBandFans SET hobby = 'Singing' WHERE rapBandFanID = 1;

WAITFOR DELAY '00:00:10';

UPDATE RapBands SET foundationDate = '2023-01-01' WHERE bandID = 1;
COMMIT TRANSACTION;


SELECT * FROM RapBands
SELECT * FROM RapBandFans

DELETE FROM RapBands
DELETE FROM RapBandFans


-- The deadlock occurs because both transactions acquire locks in a different order. 
-- Transaction 1 first acquires a lock on the RapBands table, 
-- while Transaction 2 first acquires a lock on the RapBandFans table. 
-- This order of lock acquisition creates a circular dependency and leads to a deadlock.