-- Create a view that joins at least 2 tables. Check whether existing indexes are helpful; 
-- if not, reassess existing indexes/examine the cardinality of the tables.
GO
CREATE OR ALTER VIEW testViewThatJoinsTheTables AS
	SELECT B.bandName, BC.concertLocation, BCC.price
		FROM RapBandConcertContracts BCC 
			INNER JOIN RapBands B ON B.bandID = BCC.bandConcertID
			INNER JOIN RapBandConcerts BC ON BC.bandConcertID = BCC.bandConcertID
	WHERE price < 10000
GO

-- COST WITHOUT SO FAR EXISTING INDEXES: 0.2331
-- COST WITH SO FAR EXISTING INDEXES: 0.2175
SELECT * 
	FROM testViewThatJoinsTheTables


IF EXISTS (SELECT *
				FROM sys.indexes
			WHERE NAME = 'nonclusteredRapBandIndex'
			) DROP INDEX nonclusteredRapBandIndex
					ON RapBands

CREATE NONCLUSTERED INDEX nonclusteredRapBandIndex
	ON RapBands(bandName)

ALTER INDEX nonclusteredRapBandIndex ON RapBands DISABLE
ALTER INDEX nonclusteredRapBandIndex ON RapBands REBUILD

-- COST WITH SO FAR EXISTING INDEXES: 0.2078
SELECT * 
	FROM testViewThatJoinsTheTables
