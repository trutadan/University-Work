-- Write a query on table Tb with a WHERE clause of the form WHERE b2 = value and analyze its execution plan. 
-- Create a nonclustered index that can speed up the query. Examine the execution plan again.
IF EXISTS (SELECT *
				FROM sys.indexes
			WHERE NAME = 'nonclusteredIndexExample'
			) DROP INDEX nonclusteredIndexExample 
					ON RapBandConcerts

-- COST: 0.0073
SELECT * 
	FROM RapBandConcerts
WHERE capacity = 300000

IF EXISTS (SELECT *
				FROM sys.indexes
			WHERE NAME = 'nonclusteredIndexExample'
			) DROP INDEX nonclusteredIndexExample 
					ON RapBandConcerts

CREATE NONCLUSTERED INDEX nonclusteredIndexExample 
	ON RapBandConcerts(capacity) 
INCLUDE (bandConcertID, concertLocation)

ALTER INDEX nonclusteredIndexExample on RapBandConcerts DISABLE
ALTER INDEX nonclusteredIndexExample on RapBandConcerts REBUILD

-- COST: 0.0032
SELECT * 
	FROM RapBandConcerts
WHERE capacity = 300000