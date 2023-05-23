use Rap;


GO
CREATE OR ALTER PROCEDURE addRowRapBands @bandName VARCHAR(30), @foundationDate DATE, @breakupDate DATE AS
BEGIN
	SET NOCOUNT ON
	DECLARE @error VARCHAR(max)
	SET @error = ''

	IF(@bandName IS NULL)
	BEGIN
		SET @error = 'Band name must be non null'
		RAISERROR('Band name must be non null', 16, 1);
	END
	
	IF(@foundationDate IS NULL)
	BEGIN
		SET @error = 'Foundation date must be non null'
		RAISERROR('Foundation date must be non null', 16, 1);
	END
	
	IF(@breakupDate IS NULL)
	BEGIN
		SET @error = 'Breakup date must be non null'
		RAISERROR('Breakup date must be non null', 16, 1);
	END
	
	IF(@foundationDate > @breakupDate)
	BEGIN 
		SET @error = 'Foundation date must be before breakup date'
		RAISERROR('Foundation date must be before breakup date', 16, 1);
	END

	INSERT INTO RapBands(bandName, foundationDate, breakupDate)
	VALUES (@bandName, @foundationDate, @breakupDate)

	EXEC sp_log_changes '', @bandName, 'Add row to rap bands', @error
END


GO
CREATE OR ALTER PROCEDURE addRowRapBandFans @fullName VARCHAR(30), @dateOfBirth DATE, @favouriteSong VARCHAR(30), @hobby VARCHAR(30) AS
BEGIN
	SET NOCOUNT ON
	DECLARE @error VARCHAR(max)
	SET @error = ''

	IF(@fullName IS NULL)
	BEGIN
		SET @error = 'Full name must be non null'
		RAISERROR('Full name must be non null', 16, 1);
	END

	IF(@dateOfBirth IS NULL)
	BEGIN
		SET @error = 'Date of birth must be non null'
		RAISERROR('Date of birth must be non null', 16, 1);
	END

	IF(@favouriteSong IS NULL)
	BEGIN
		SET @error = 'Favourite song must be non null'
		RAISERROR('Favourite song must be non null', 16, 1);
	END

	IF(@hobby IS NULL)
	BEGIN
		SET @error = 'Hobby must be non null'
		RAISERROR('Hobby must be non null', 16, 1);
	END

	INSERT INTO RapBandFans(fullName, dateOfBirth, favouriteSong, hobby) 
	VALUES (@fullName, @dateOfBirth, @favouriteSong, @hobby)

	EXEC sp_log_changes '', @fullName, 'Add row to rap band fans', @error
END


GO
CREATE OR ALTER PROCEDURE addRowRapBandFanAdoration @bandName VARCHAR(30), @fullName VARCHAR(30), @startingDate DATE AS
BEGIN
	SET NOCOUNT ON

	DECLARE @error VARCHAR(max)
	SET @error = ''

	IF(@bandName IS NULL)
	BEGIN
		SET @error = 'Band name must be non null'
		RAISERROR(@error, 16, 1);
	END

	IF(@fullName IS NULL)
	BEGIN
		SET @error = 'Full name must be non null'
		RAISERROR(@error, 16, 1);
	END

	IF(@startingDate IS NULL)
	BEGIN
		SET @error = 'Starting date must be non null'
		RAISERROR(@error, 16, 1);
	END

	DECLARE @bandID INT
	SET @bandID = (SELECT bandID FROM RapBands WHERE bandName = @bandName)

	DECLARE @fanID INT
	SET @fanID = (SELECT rapBandFanID FROM RapBandFans WHERE fullName = @fullName)

	IF(@bandID IS NULL)
	BEGIN
		SET @error = 'No band with the given name'
		RAISERROR(@error, 16, 1);
	END

	IF(@fanID IS NULL)
	BEGIN
		SET @error = 'No fan with the given name'
		RAISERROR(@error, 16, 1);
	END

	INSERT INTO RapBandFanAdoration VALUES (@bandID, @fanID, @startingDate)

	DECLARE @newData VARCHAR(100)
	SET @newData = @bandName + ' - ' + @fullName
	EXEC sp_log_changes '', @newData, 'Connect fan to rap band', @error
END


EXEC addRowRapBands 'N.W.A', '1986-06-29', '1991-05-27'
EXEC addRowRapBandFans 'Eminem', '1972-10-17', 'Lose Yourself', 'Rapping'
EXEC addRowRapBandFanAdoration 'N.W.A', 'Eminem', '1998-03-12'


SELECT * FROM RapBands
SELECT * FROM RapBandFans
SELECT * FROM RapBandFanAdoration
SELECT * FROM LogChanges

DELETE FROM RapBandFanAdoration
DELETE FROM RapBandFans
DELETE FROM RapBands
DELETE FROM LogChanges


GO
CREATE OR ALTER PROCEDURE successfulAddRollback AS
BEGIN
	BEGIN TRAN

	BEGIN TRY 
		EXEC addRowRapBands 'N.W.A', '1986-06-29', '1991-05-27'
		EXEC addRowRapBandFans 'Eminem', '1972-10-17', 'Lose Yourself', 'Rapping'
		EXEC addRowRapBandFanAdoration 'N.W.A', 'Eminem', '1998-03-12'
	END TRY

	BEGIN CATCH
		ROLLBACK TRAN
		EXEC sp_log_changes '', '', 'rolledback all data', ''
		RETURN
	END CATCH

	COMMIT TRAN
END


GO 
CREATE OR ALTER PROCEDURE failAddRollback AS
BEGIN
	BEGIN TRAN

	BEGIN TRY
		EXEC addRowRapBands 'N.W.A', '1986-06-29', '1991-05-27'
		EXEC addRowRapBandFans 'Eminem', '1972-10-17', 'Lose Yourself', 'Rapping'
		EXEC addRowRapBandFanAdoration 'N.W.A', 'Eminescu', '1998-03-12'
	END TRY

	BEGIN CATCH
		ROLLBACK TRAN
		EXEC sp_log_changes '', '', 'rolledback all data', ''
		RETURN
	END CATCH

	COMMIT TRAN
END


EXEC successfulAddRollback
EXEC failAddRollback