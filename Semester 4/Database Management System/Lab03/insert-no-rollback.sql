use Rap;


GO
CREATE OR ALTER PROCEDURE addRowRapBandsRecover @bandName VARCHAR(30), @foundationDate DATE, @breakupDate DATE AS
BEGIN
	SET NOCOUNT ON
	BEGIN TRAN

	BEGIN TRY
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
		COMMIT TRAN

	END TRY
	BEGIN CATCH

		ROLLBACK TRAN
		EXEC sp_log_changes '', '', 'rolledback song data', ''

	END CATCH
END


GO
CREATE OR ALTER PROCEDURE addRowRapBandFansRecover @fullName VARCHAR(30), @dateOfBirth DATE, @favouriteSong VARCHAR(30), @hobby VARCHAR(30) AS
BEGIN
	SET NOCOUNT ON
	BEGIN TRAN

	BEGIN TRY
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
		COMMIT TRAN
	END TRY

	BEGIN CATCH
		ROLLBACK TRAN
		EXEC sp_log_changes '', '', 'rolledback fans data', ''
	END CATCH
END


GO
CREATE OR ALTER PROCEDURE addRowRapBandFanAdorationRecover @bandName VARCHAR(30), @fullName VARCHAR(30), @startingDate DATE AS
BEGIN
	SET NOCOUNT ON
	BEGIN TRAN

	BEGIN TRY
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
		COMMIT TRAN
	END TRY

	BEGIN CATCH
		ROLLBACK TRAN
		EXEC sp_log_changes '', '', 'rolledback fan from rap band adoration', ''
	END CATCH
END


GO
CREATE OR ALTER PROCEDURE successfulAddNoRollback AS
BEGIN
	EXEC addRowRapBandsRecover 'N.W.A', '1986-06-29', '1991-05-27'
	EXEC addRowRapBandFansRecover 'Eminem', '1972-10-17', 'Lose Yourself', 'Rapping'
	EXEC addRowRapBandFanAdorationRecover 'N.W.A', 'Eminem', '1998-03-12'
END


GO 
CREATE OR ALTER PROCEDURE failAddNoRollback AS
BEGIN
	EXEC addRowRapBandsRecover 'N.W.A', '1986-06-29', '1991-05-27'
	EXEC addRowRapBandFansRecover 'Eminem', '1972-10-17', 'Lose Yourself', 'Rapping'
	EXEC addRowRapBandFanAdorationRecover 'N.W.A', 'Eminescu', '1998-03-12'
END


EXEC successfulAddNoRollback
EXEC failAddNoRollback


SELECT * FROM RapBands
SELECT * FROM RapBandFans
SELECT * FROM RapBandFanAdoration
SELECT * FROM LogChanges

DELETE FROM RapBandFanAdoration
DELETE FROM RapBandFans
DELETE FROM RapBands
DELETE FROM LogChanges