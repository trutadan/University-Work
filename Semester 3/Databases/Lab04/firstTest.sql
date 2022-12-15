IF NOT EXISTS (SELECT * FROM sysobjects WHERE name='RapPlaylists' and xtype='U')
	CREATE TABLE RapPlaylists (
		playlistID int NOT NULL,
		playlistName varchar(30) NOT NULL,
		numberOfEnjoyers int,
		numberOfSongs smallint,
		duration time,
		referenceLink varchar(100) NOT NULL,

		PRIMARY KEY(playlistID)
	)
GO


EXEC addToTables 'RapPlaylists'


-- a table with a single-column primary key and no foreign keys;
-- a view with a SELECT statement operating on one table;
GO 
	CREATE or ALTER VIEW getRapPlaylistsGroupsBySongsNumber AS
		SELECT playlistName, count(*) as numberOfSongs
    FROM RapPlaylists

    GROUP BY playlistName
GO


EXEC addToViews 'getRapPlaylistsGroupsBySongsNumber'
EXEC addToTests 'firstTest'
EXEC connectTableToTest 'RapPlaylists', 'firstTest', 1000, 1
EXEC connectViewToTest 'getRapPlaylistsGroupsBySongsNumber', 'firstTest'

EXEC runTest 'firstTest'


SELECT * FROM RapPlaylists


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