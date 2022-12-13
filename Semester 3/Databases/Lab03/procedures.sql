use Rap;


-- a. modify the type of a column;

SELECT COLUMN_NAME, DATA_TYPE 
	FROM INFORMATION_SCHEMA.COLUMNS 
WHERE TABLE_NAME = 'RapPlaylists';

-- set numberOfSongs from RapPlaylists to tinyint
GO
	CREATE OR ALTER PROCEDURE setNumberOfSongsFromRapPlaylistsToInt
AS
	ALTER TABLE RapPlaylists ALTER COLUMN numberOfSongs int

EXECUTE setNumberOfSongsFromRapPlaylistsToInt

-- revert the operation
GO
	CREATE OR ALTER PROCEDURE setNumberOfSongsFromRapPlaylistsToSmallInt
AS
	ALTER TABLE RapPlaylists ALTER COLUMN numberOfSongs smallint

EXECUTE setNumberOfSongsFromRapPlaylistsToSmallInt


-- b. add / remove a column;

SELECT COLUMN_NAME, DATA_TYPE 
	FROM INFORMATION_SCHEMA.COLUMNS 
WHERE TABLE_NAME = 'Rappers'

-- add a dateOfDeath column to Rappers table
GO
	CREATE OR ALTER PROCEDURE addDateOfDeathToRappers
AS	
	ALTER TABLE Rappers ADD dateOfDeath date

EXECUTE addDateOfDeathToRappers

-- remove the dateOfDeath column to Rappers table
GO
	CREATE OR ALTER PROCEDURE removeDateOfDeathFromRappers
AS	
	ALTER TABLE Rappers DROP COLUMN dateOfDeath

EXECUTE removeDateOfDeathFromRappers


-- c. add / remove a DEFAULT constraint;

-- add default number of streams constraint to RapSongs table
GO 
	CREATE OR ALTER PROCEDURE addDefaultConstraintToStreamsFromRapSongs
AS
	ALTER TABLE RapSongs ADD CONSTRAINT defaultStreams DEFAULT(0) FOR streams

EXECUTE addDefaultConstraintToStreamsFromRapSongs

-- remove the default number of streams constraint from RapSongs table 
GO 
	CREATE OR ALTER PROCEDURE removeDefaultConstraintFromStreamsFromRapSongs
AS
	ALTER TABLE RapSongs DROP CONSTRAINT defaultStreams

EXECUTE removeDefaultConstraintFromStreamsFromRapSongs


-- let's first create a table and then alter its content based on the statements
-- g. create / drop a table.

SELECT * FROM RapFestivals

-- create a RapFestival table
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

EXECUTE addRapFestivals

-- drop the RapFestival table
GO
	CREATE OR ALTER PROCEDURE removeRapFestivals
AS
	DROP TABLE RapFestivals

EXECUTE removeRapFestivals


-- d. add / remove a primary key;

SELECT CONSTRAINT_NAME, CONSTRAINT_TYPE
	FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS
WHERE TABLE_NAME = 'RapFestivals';

-- add a primary key to RapFestival table
GO 
	CREATE OR ALTER PROCEDURE addPrimaryKeyToFestivalIDFromRapFestivals
AS
	ALTER TABLE RapFestivals
		ADD CONSTRAINT FESTIVAL_PRIMARY_KEY PRIMARY KEY(festivalID)

EXECUTE addPrimaryKeyToFestivalIDFromRapFestivals

-- remove the primary key from RapFestival table
GO 
	CREATE OR ALTER PROCEDURE removePrimaryKeyFromFestivalIDFromRapFestivals
AS
	ALTER TABLE RapFestivals
		DROP CONSTRAINT FESTIVAL_PRIMARY_KEY

EXECUTE removePrimaryKeyFromFestivalIDFromRapFestivals


-- e. add / remove a candidate key;

SELECT CONSTRAINT_NAME, CONSTRAINT_TYPE
	FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS
WHERE TABLE_NAME = 'RapFestivals';

-- add a candidate key to RapFestival table
GO 
	CREATE OR ALTER PROCEDURE addCandidateKeyToRapFestivals
AS
	ALTER TABLE RapFestivals
		ADD CONSTRAINT FESTIVAL_CANDIDATE_KEY UNIQUE(festivalLocation, startingDatetime)

EXECUTE addCandidateKeyToRapFestivals

-- remove the candidate key from RapFestival table
GO 
	CREATE OR ALTER PROCEDURE removeCandidateKeyFromRapFestivals
AS
	ALTER TABLE RapFestivals
		DROP CONSTRAINT FESTIVAL_CANDIDATE_KEY

EXECUTE removeCandidateKeyFromRapFestivals

-- f. add / remove a foreign key;

SELECT CONSTRAINT_NAME, CONSTRAINT_TYPE
	FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS
WHERE TABLE_NAME = 'RapperConcerts';

ALTER TABLE RapperConcerts
	ADD festivalID int

SELECT * FROM RapperConcerts;

-- add a foreign key to RapperConcerts table
GO 
	CREATE OR ALTER PROCEDURE addForeignKeyToRapperConcerts
AS
	ALTER TABLE RapperConcerts
		ADD CONSTRAINT FESTIVAL_FOREIGN_KEY FOREIGN KEY(festivalID) REFERENCES RapFestivals(festivalID)

EXECUTE addForeignKeyToRapperConcerts

-- remove the foreign key from RapperConcerts table
GO 
	CREATE OR ALTER PROCEDURE removeForeignKeyFromRapperConcerts
AS
	ALTER TABLE RapperConcerts
		DROP CONSTRAINT FESTIVAL_FOREIGN_KEY

EXECUTE removeForeignKeyFromRapperConcerts


-- Create a new table that holds the current version of the database schema. Simplifying assumption: the version is an integer number.
-- Write a stored procedure that receives as a parameter a version number and brings the database to that version.
CREATE TABLE VersionTable (
	version int
)

INSERT INTO VersionTable 
VALUES
	(1) 


SELECT * FROM VersionTable

-- a table that contains the initial version, the version after the execution of the procedure and the procedure that changes the table in this way
CREATE TABLE ProceduresTable (
	initialVersion int,
	finalVersion int,
	PRIMARY KEY (initialVersion, finalVersion),
	procedureName varchar(MAX)
)

INSERT INTO ProceduresTable
VALUES
	(1, 2, 'setNumberOfSongsFromRapPlaylistsToInt'),
	(2, 1, 'setNumberOfSongsFromRapPlaylistsToSmallInt'),

	(2, 3, 'addDateOfDeathToRappers'), 
	(3, 2, 'removeDateOfDeathFromRappers'),

	(3, 4, 'addDefaultConstraintToStreamsFromRapSongs'),
	(4, 3, 'removeDefaultConstraintFromStreamsFromRapSongs'),

	(4, 5, 'addRapFestivals'),
	(5, 4, 'removeRapFestivals'),

	(5, 6, 'addPrimaryKeyToFestivalIDFromRapFestivals'),
	(6, 5, 'removePrimaryKeyFromFestivalIDFromRapFestivals'),

	(6, 7, 'addCandidateKeyToRapFestivals'),
	(7, 6, 'removeCandidateKeyFromRapFestivals'),

	(7, 8, 'addForeignKeyToRapperConcerts'),
	(8, 7, 'removeForeignKeyFromRapperConcerts')


SELECT * FROM ProceduresTable


GO
	CREATE OR ALTER PROCEDURE goToVersion(@newVersion int) 
AS
    DECLARE @currentVersion int
    DECLARE @procedure varchar(max)

    SELECT @currentVersion = version FROM VersionTable

    IF @newVersion > (SELECT max(finalVersion) FROM ProceduresTable) OR @newVersion < 1
        RAISERROR('Version provided out of range!', 10, 1)
		RETURN -1

    WHILE @currentVersion > @newVersion 
		BEGIN
			SELECT @procedure = procedureName FROM ProceduresTable WHERE initialVersion = @currentVersion and finalVersion = @currentVersion - 1
			PRINT('Executing ' + @procedure + '...')
			EXECUTE (@procedure)
			SET @currentVersion = @currentVersion - 1
		END

    WHILE @currentVersion < @newVersion 
		BEGIN
			SELECT @procedure = procedureName FROM ProceduresTable WHERE initialVersion = @currentVersion and finalVersion = @currentVersion + 1
			PRINT('Executing ' + @procedure + '...')
			EXECUTE (@procedure)
			SET @currentVersion = @currentVersion + 1
		END

    UPDATE VersionTable SET version = @newVersion


EXECUTE goToVersion 3

EXECUTE goToVersion 1

EXECUTE goToVersion 100