-- Transactions
BEGIN TRANSACTION

WAITFOR DELAY '00:00:04'

INSERT INTO RapBands (bandName, foundationDate, breakupDate)
VALUES ('Band A', '2022-01-01', '2023-01-01');

COMMIT TRANSACTION;


BEGIN TRANSACTION

WAITFOR DELAY '00:00:05';

INSERT INTO RapBands (bandName, foundationDate, breakupDate)
VALUES ('Band A', '2022-01-01', '2023-01-01');

COMMIT TRANSACTION;
