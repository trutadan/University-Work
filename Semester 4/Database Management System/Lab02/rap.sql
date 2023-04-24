use Rap;

set LANGUAGE English;
set DATEFORMAT YMD;


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
	bandID int NOT NULL,
	bandName varchar(30) NOT NULL,
	foundationDate date,
	breakupDate date,

	PRIMARY KEY(bandID)
)


create table RapBandAlbums (
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
