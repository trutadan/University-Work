use Rap;


DECLARE @Sql NVARCHAR(500) DECLARE @Cursor CURSOR

SET @Cursor = CURSOR FAST_FORWARD FOR
SELECT DISTINCT sql = 'ALTER TABLE [' + tc2.TABLE_SCHEMA + '].[' +  tc2.TABLE_NAME + '] DROP [' + rc1.CONSTRAINT_NAME + '];'
FROM INFORMATION_SCHEMA.REFERENTIAL_CONSTRAINTS rc1
LEFT JOIN INFORMATION_SCHEMA.TABLE_CONSTRAINTS tc2 ON tc2.CONSTRAINT_NAME =rc1.CONSTRAINT_NAME

OPEN @Cursor FETCH NEXT FROM @Cursor INTO @Sql

WHILE (@@FETCH_STATUS = 0)
BEGIN
Exec sp_executesql @Sql
FETCH NEXT FROM @Cursor INTO @Sql
END

CLOSE @Cursor DEALLOCATE @Cursor
GO

EXEC sp_MSforeachtable 'DROP TABLE ?'
GO


create table RapBands (
	bandID int IDENTITY(1,1) NOT NULL,
	bandName varchar(30) NOT NULL,
	foundationDate date,
	breakupDate date,

	PRIMARY KEY(bandID)
)


create table RapBandFans (
	rapBandFanID int IDENTITY(1,1) NOT NULL,
	fullName varchar(30) NOT NULL,
	dateOfBirth date,
	favouriteSong varchar(30),
	hobby varchar(30),

	PRIMARY KEY(rapBandFanID)
)


create table RapBandFanAdoration (
	bandID int NOT NULL,
	rapBandFanID int NOT NULL,
	startingDate date,

	FOREIGN KEY(bandID)
		REFERENCES RapBands(bandID)
		ON DELETE CASCADE,

	FOREIGN KEY(rapBandFanID)
		REFERENCES RapBandFans(rapBandFanID)
		ON DELETE CASCADE
)


CREATE TABLE LogLocks(
	currentTime DATETIME,
	info VARCHAR(100),
	resource_type VARCHAR(100),
	request_mode VARCHAR(100),
	request_type VARCHAR(100),
	request_status VARCHAR(100),
	request_session_id INT
)


CREATE TABLE LogChanges(
	currentTime DATETIME,
	info VARCHAR(100),
	old_data VARCHAR(100),
	new_data VARCHAR(100),
	error VARCHAR(100)
)


IF EXISTS (SELECT 1 FROM sys.objects WHERE object_id = OBJECT_ID(N'sp_log_locks') AND type = N'P')
    DROP PROCEDURE sp_log_locks
GO

GO
CREATE OR ALTER PROCEDURE sp_log_locks @info VARCHAR(100) AS
BEGIN
	INSERT INTO LogLocks(currentTime, info, resource_type, request_mode, request_type, request_status, request_session_id)
	SELECT GETDATE(), @info, resource_type, request_mode, request_type, request_status, request_session_id
	FROM sys.dm_tran_locks
	WHERE request_owner_type = 'TRANSACTION'
END


IF EXISTS (SELECT 1 FROM sys.objects WHERE object_id = OBJECT_ID(N'sp_log_changes') AND type = N'P')
    DROP PROCEDURE sp_log_changes
GO

GO
CREATE OR ALTER PROCEDURE sp_log_changes @oldData VARCHAR(100), @newData VARCHAR(100), @info VARCHAR(100), @error VARCHAR(100) AS
BEGIN
	INSERT INTO LogChanges (currentTime, info, old_data, new_data, error) VALUES
	(GETDATE(), @info, @oldData, @newData, @error)
END