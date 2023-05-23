SET TRANSACTION ISOLATION LEVEL READ COMMITTED
-- SET TRANSACTION ISOLATION LEVEL REPEATABLE READ

BEGIN TRAN
SELECT * FROM RapBands

WAITFOR DELAY '00:00:05'

SELECT * FROM RapBands
COMMIT TRAN


-- how to solve it?
-- using a higher isolation level, instead of READ COMMITTED, 
-- you can use a higher isolation level like REPEATABLE READ or SERIALIZABLE
