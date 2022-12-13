-- not working as expected
-- still working on it...
CREATE TABLE CurrentVersion (
	currentVersion int
)

INSERT INTO CurrentVersion 
VALUES
	(0)


CREATE TABLE DatabaseVersions (
	version int IDENTITY(1,1) NOT NULL,
	executedProcedureName varchar(max),
	reversedProcedureName varchar(max),

	PRIMARY KEY(version)
)

GO
	CREATE OR ALTER PROCEDURE removeVersions 
AS
	DECLARE @currentVersion int
	SELECT @currentVersion = currentVersion FROM CurrentVersion

	DELETE FROM DatabaseVersions WHERE @currentVersion < version



GO
	CREATE OR ALTER PROCEDURE setNumberOfSongsFromRapPlaylistsToInt
AS
	ALTER TABLE RapPlaylists ALTER COLUMN numberOfSongs int
	EXECUTE removeVersions
	INSERT INTO DatabaseVersions VALUES ('setNumberOfSongsFromRapPlaylistsToInt', 'setNumberOfSongsFromRapPlaylistsToSmallInt')
	UPDATE CurrentVersion SET currentVersion = currentVersion + 1 


GO
	CREATE OR ALTER PROCEDURE setNumberOfSongsFromRapPlaylistsToSmallInt
AS
	ALTER TABLE RapPlaylists ALTER COLUMN numberOfSongs smallint
	EXECUTE removeVersions

GO
	CREATE OR ALTER PROCEDURE addDateOfDeathToRappers
AS	
	ALTER TABLE Rappers ADD dateOfDeath date
	EXECUTE removeVersions
	INSERT INTO DatabaseVersions VALUES ('addDateOfDeathToRappers', 'removeDateOfDeathFromRappers')
	UPDATE CurrentVersion SET currentVersion = currentVersion + 1

GO
	CREATE OR ALTER PROCEDURE removeDateOfDeathFromRappers
AS	
	ALTER TABLE Rappers DROP COLUMN dateOfDeath
	EXECUTE removeVersions

GO 
	CREATE OR ALTER PROCEDURE addDefaultConstraintToStreamsFromRapSongs
AS
	ALTER TABLE RapSongs ADD CONSTRAINT defaultStreams DEFAULT(0) FOR streams
	EXECUTE removeVersions
	INSERT INTO DatabaseVersions VALUES ('addDefaultConstraintToStreamsFromRapSongs', 'removeDefaultConstraintFromStreamsFromRapSongs')
	UPDATE CurrentVersion SET currentVersion = currentVersion + 1

GO 
	CREATE OR ALTER PROCEDURE removeDefaultConstraintFromStreamsFromRapSongs
AS
	ALTER TABLE RapSongs DROP CONSTRAINT defaultStreams
	EXECUTE removeVersions

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
	EXECUTE removeVersions
	INSERT INTO DatabaseVersions VALUES ('addRapFestivals', 'removeRapFestivals')
	UPDATE CurrentVersion SET currentVersion = currentVersion + 1

GO
	CREATE OR ALTER PROCEDURE removeRapFestivals
AS
	DROP TABLE RapFestivals
	EXECUTE removeVersions

GO 
	CREATE OR ALTER PROCEDURE addPrimaryKeyToFestivalIDFromRapFestivals
AS
	ALTER TABLE RapFestivals
		ADD CONSTRAINT FESTIVAL_PRIMARY_KEY PRIMARY KEY(festivalID)
	EXECUTE removeVersions
	INSERT INTO DatabaseVersions VALUES ('addPrimaryKeyToFestivalIDFromRapFestivals', 'removePrimaryKeyFromFestivalIDFromRapFestivals')
	UPDATE CurrentVersion SET currentVersion = currentVersion + 1

GO 
	CREATE OR ALTER PROCEDURE removePrimaryKeyFromFestivalIDFromRapFestivals
AS
	ALTER TABLE RapFestivals
		DROP CONSTRAINT FESTIVAL_PRIMARY_KEY
	EXECUTE removeVersions

GO 
	CREATE OR ALTER PROCEDURE addCandidateKeyToRapFestivals
AS
	ALTER TABLE RapFestivals
		ADD CONSTRAINT FESTIVAL_CANDIDATE_KEY UNIQUE(festivalLocation, startingDatetime)
	EXECUTE removeVersions
	INSERT INTO DatabaseVersions VALUES ('addCandidateKeyToRapFestivals', 'removeCandidateKeyFromRapFestivals')
	UPDATE CurrentVersion SET currentVersion = currentVersion + 1

GO 
	CREATE OR ALTER PROCEDURE removeCandidateKeyFromRapFestivals
AS
	ALTER TABLE RapFestivals
		DROP CONSTRAINT FESTIVAL_CANDIDATE_KEY
	EXECUTE removeVersions

GO 
	CREATE OR ALTER PROCEDURE addForeignKeyToRapperConcerts
AS
	ALTER TABLE RapperConcerts
		ADD CONSTRAINT FESTIVAL_FOREIGN_KEY FOREIGN KEY(festivalID) REFERENCES RapFestivals(festivalID)
	EXECUTE removeVersions
	INSERT INTO DatabaseVersions VALUES ('addForeignKeyToRapperConcerts', 'removeForeignKeyFromRapperConcerts')
	UPDATE CurrentVersion SET currentVersion = currentVersion + 1

GO 
	CREATE OR ALTER PROCEDURE removeForeignKeyFromRapperConcerts
AS
	ALTER TABLE RapperConcerts
		DROP CONSTRAINT FESTIVAL_FOREIGN_KEY
	EXECUTE removeVersions


GO
	CREATE OR ALTER PROCEDURE goToGivenVersion(@newVersion int) 
AS
    DECLARE @currVersion int
    DECLARE @procedureName varchar(max)

    SELECT @currVersion = currentVersion FROM CurrentVersion

    WHILE @currVersion > @newVersion 
		BEGIN
			SELECT @procedureName = reversedProcedureName FROM DatabaseVersions WHERE version = @currVersion 
			PRINT('Executing ' + @procedureName + '...')
			EXECUTE (@procedureName)
			SET @currVersion = @currVersion - 1
		END

    WHILE @currVersion < @newVersion 
		BEGIN
			SELECT @procedureName = executedProcedureName FROM DatabaseVersions WHERE version = @currVersion 
			PRINT('Executing ' + @procedureName + '...')
			EXECUTE (@procedureName)
			SET @currVersion = @currVersion + 1
		END

    UPDATE CurrentVersion SET currentVersion = @newVersion


EXECUTE addDateOfDeathToRappers

SELECT * FROM CurrentVersion
SELECT * FROM DatabaseVersions

SELECT COLUMN_NAME, DATA_TYPE 
	FROM INFORMATION_SCHEMA.COLUMNS 
WHERE TABLE_NAME = 'Rappers'

EXECUTE addRapFestivals

SELECT * FROM CurrentVersion
SELECT * FROM DatabaseVersions

SELECT * FROM RapFestivals

EXECUTE addCandidateKeyToRapFestivals

SELECT * FROM CurrentVersion
SELECT * FROM DatabaseVersions

SELECT CONSTRAINT_NAME, CONSTRAINT_TYPE
	FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS
WHERE TABLE_NAME = 'RapFestivals';

EXECUTE goToGivenVersion 1

SELECT * FROM CurrentVersion
SELECT * FROM DatabaseVersions
