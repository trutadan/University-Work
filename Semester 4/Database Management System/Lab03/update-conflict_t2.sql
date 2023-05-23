SET TRAN ISOLATION LEVEL SNAPSHOT

BEGIN TRANSACTION

WAITFOR DELAY '00:00:03'

UPDATE RapBands SET foundationDate = '2023-01-01' WHERE bandID = 1

COMMIT TRANSACTION

-- how to solve it?
-- set the transaction isolation level to SERIALIZABLE in Transaction 2 
-- to ensure that the transaction executes in a serialized manner