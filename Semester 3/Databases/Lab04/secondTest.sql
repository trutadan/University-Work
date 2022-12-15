IF NOT EXISTS (SELECT * FROM sysobjects WHERE name='RapBands' and xtype='U')
	CREATE TABLE RapBands (
		bandID int NOT NULL,
		bandName varchar(30) NOT NULL,
		foundationDate date,
		breakupDate date,

		PRIMARY KEY(bandID)
	)
GO

IF NOT EXISTS (SELECT * FROM sysobjects WHERE name='Rappers' and xtype='U')
	CREATE TABLE Rappers (
		rapperID int NOT NULL,
		bandID int,
		fullName varchar(30),
		stageName varchar(30),
		dateOfBirth date,
		birthPlace varchar(30),

		PRIMARY KEY (rapperID),

		FOREIGN KEY(bandID)
			REFERENCES RapBands(bandID)
	)
GO


EXEC addToTables 'RapBands'
EXEC addToTables 'Rappers'


-- a table with a single-column primary key and at least one foreign key;
-- a view with a SELECT statement that operates on at least 2 different tables and contains at least one JOIN operator;
GO
CREATE or ALTER VIEW getOldestRappersFromRapBands AS
    SELECT RB.bandName, R.fullName, R.dateOfBirth
        FROM Rappers R inner join RapBands RB on R.bandID = RB.bandID
    WHERE YEAR(R.dateOfBirth) < 2003
GO


EXEC addToViews 'getOldestRappersFromRapBands'
EXEC addToTests 'secondTest'
EXEC connectTableToTest 'Rappers', 'secondTest', 1000, 2
EXEC connectTableToTest 'RapBands', 'secondTest', 500, 1
EXEC connectViewToTest 'getOldestRappersFromRapBands', 'secondTest'

EXEC runTest 'secondTest'


SELECT * FROM RapBands
SELECT * FROM Rappers


SELECT *
FROM [Views]

SELECT *
FROM [Tables]

SELECT *
FROM [Tests]

SELECT *
FROM [TestTables]

SELECT *
FROM [TestViews]

SELECT *
FROM [TestRuns]

SELECT *
FROM [TestRunTables]

SELECT *
FROM [TestRunViews]