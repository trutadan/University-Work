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

IF NOT EXISTS (SELECT * FROM sysobjects WHERE name='RapperAlbums' and xtype='U')
	CREATE TABLE RapperAlbums (
		albumID int NOT NULL,
		rapperID int NOT NULL,
		title varchar(40),
		duration time,
		numberOfSongs tinyint NOT NULL,
		releaseDate date,

		PRIMARY KEY(albumID),

		FOREIGN KEY(rapperID)
			REFERENCES Rappers(rapperID)
	)
GO

IF NOT EXISTS (SELECT * FROM sysobjects WHERE name='RapBandAlbums' and xtype='U')
	CREATE TABLE RapBandAlbums (
		albumID int NOT NULL,
		bandID int NOT NULL,
		title varchar(40),
		duration time,
		numberOfSongs tinyint NOT NULL,
		releaseDate date,

		PRIMARY KEY(albumID),

		FOREIGN KEY(bandID)
			REFERENCES RapBands(bandID)
	)
GO

IF NOT EXISTS (SELECT * FROM sysobjects WHERE name='RapSongs' and xtype='U')
	CREATE TABLE RapSongs (
		songID int NOT NULL,
		rapperAlbumID int,
		bandAlbumID int,
		title varchar(40) NOT NULL,
		duration time,
		streams int,

		PRIMARY KEY(songID),

		FOREIGN KEY(rapperAlbumID) 
			REFERENCES RapperAlbums(albumID),

		FOREIGN KEY(bandAlbumID) 
			REFERENCES RapBandAlbums(albumID)
	)
GO

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


IF NOT EXISTS (SELECT * FROM sysobjects WHERE name='RapPlaylistSongAddition' and xtype='U')
	CREATE TABLE RapPlaylistSongAddition (
		playlistID int NOT NULL,
		songID int NOT NULL,
		userName varchar(20) NOT NULL,
		additionDate date,

		PRIMARY KEY(playlistID, songID),

		FOREIGN KEY(playlistID)
			REFERENCES RapPlaylists(playlistID)
			ON DELETE CASCADE,

		FOREIGN KEY(songID)
			REFERENCES RapSongs(songID)
			ON DELETE CASCADE
	)
GO


EXEC addToTables 'RapBands'
EXEC addToTables 'Rappers'
EXEC addToTables 'RapperAlbums'
EXEC addToTables 'RapBandAlbums'
EXEC addToTables 'RapSongs'
EXEC addToTables 'RapPlaylists'
EXEC addToTables 'RapPlaylistSongAddition'


-- a table with a multicolumn primary key;
-- a view with a SELECT statement that has a GROUP BY clause, operates on at least 2 different tables and contains at least one JOIN operator;
GO
CREATE or ALTER VIEW getRappersWithSongsOnBothAlbumAndPlaylist AS
	SELECT R.fullName
		FROM Rappers R
			INNER JOIN RapperAlbums A 
				ON R.rapperID = A.rapperID
			INNER JOIN RapSongs S
				ON S.rapperAlbumID = A.albumID
			INNER JOIN RapPlaylistSongAddition P
				ON P.songID = S.songID
			GROUP BY R.fullName
GO


EXEC addToViews 'getRappersWithSongsOnBothAlbumAndPlaylist'
EXEC addToTests 'thirdTest'
EXEC connectTableToTest 'RapBands', 'thirdTest', 100, 1
EXEC connectTableToTest 'Rappers', 'thirdTest', 100, 2
EXEC connectTableToTest 'RapperAlbums', 'thirdTest', 100, 3
EXEC connectTableToTest 'RapBandAlbums', 'thirdTest', 100, 4
EXEC connectTableToTest 'RapSongs', 'thirdTest', 100, 5
EXEC connectTableToTest 'RapPlaylists', 'thirdTest', 100, 6
EXEC connectTableToTest 'RapPlaylistSongAddition', 'thirdTest', 100, 7
EXEC connectViewToTest 'getRappersWithSongsOnBothAlbumAndPlaylist', 'thirdTest'

EXEC runTest 'thirdTest'


SELECT * FROM RapBands
SELECT * FROM Rappers
SELECT * FROM RapperAlbums
SELECT * FROM RapBandAlbums
SELECT * FROM RapSongs
SELECT * FROM RapPlaylists
SELECT * FROM RapPlaylistSongAddition


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