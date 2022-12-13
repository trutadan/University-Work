GO
	CREATE OR ALTER PROCEDURE setNumberOfSongsFromRapPlaylistsToInt
AS
	ALTER TABLE RapPlaylists ALTER COLUMN numberOfSongs int

GO
	CREATE OR ALTER PROCEDURE setNumberOfSongsFromRapPlaylistsToSmallInt
AS
	ALTER TABLE RapPlaylists ALTER COLUMN numberOfSongs smallint

GO
	CREATE OR ALTER PROCEDURE addDateOfDeathToRappers
AS	
	ALTER TABLE Rappers ADD dateOfDeath date

GO
	CREATE OR ALTER PROCEDURE removeDateOfDeathFromRappers
AS	
	ALTER TABLE Rappers DROP COLUMN dateOfDeath

GO 
	CREATE OR ALTER PROCEDURE addDefaultConstraintToStreamsFromRapSongs
AS
	ALTER TABLE RapSongs ADD CONSTRAINT defaultStreams DEFAULT(0) FOR streams

GO 
	CREATE OR ALTER PROCEDURE removeDefaultConstraintFromStreamsFromRapSongs
AS
	ALTER TABLE RapSongs DROP CONSTRAINT defaultStreams

GO
	CREATE OR ALTER PROCEDURE addRapFestivals
AS
	CREATE TABLE RapFestivals (
		festivalID int NOT NULL,
		festivalLocation varchar(30) NOT NULL,
		maximumCapacity int,
		startingDatetime datetime NOT NULL,
		endDatetime datetime NOT NULL,
)

GO
	CREATE OR ALTER PROCEDURE removeRapFestivals
AS
	DROP TABLE RapFestivals

GO 
	CREATE OR ALTER PROCEDURE addPrimaryKeyToFestivalIDFromRapFestivals
AS
	ALTER TABLE RapFestivals
		ADD CONSTRAINT FESTIVAL_PRIMARY_KEY PRIMARY KEY(festivalID)

GO 
	CREATE OR ALTER PROCEDURE removePrimaryKeyFromFestivalIDFromRapFestivals
AS
	ALTER TABLE RapFestivals
		DROP CONSTRAINT FESTIVAL_PRIMARY_KEY

GO 
	CREATE OR ALTER PROCEDURE addCandidateKeyToRapFestivals
AS
	ALTER TABLE RapFestivals
		ADD CONSTRAINT FESTIVAL_CANDIDATE_KEY UNIQUE(festivalLocation, startingDatetime)

GO 
	CREATE OR ALTER PROCEDURE removeCandidateKeyFromRapFestivals
AS
	ALTER TABLE RapFestivals
		DROP CONSTRAINT FESTIVAL_CANDIDATE_KEY

GO 
	CREATE OR ALTER PROCEDURE addForeignKeyToRapperConcerts
AS
	ALTER TABLE RapperConcerts
		ADD CONSTRAINT FESTIVAL_FOREIGN_KEY FOREIGN KEY(festivalID) REFERENCES RapFestivals(festivalID)

GO 
	CREATE OR ALTER PROCEDURE removeForeignKeyFromRapperConcerts
AS
	ALTER TABLE RapperConcerts
		DROP CONSTRAINT FESTIVAL_FOREIGN_KEY
