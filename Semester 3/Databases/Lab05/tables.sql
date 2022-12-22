IF 'generateRandomDataForTable' not in (SELECT ROUTINE_NAME FROM INFORMATION_SCHEMA.ROUTINES) 
		BEGIN
            PRINT 'generateRandomDataForTable procedure does not exist!'
            RETURN
        END

-- Ta(aid, a2, …)
-- aid is primary key
-- aid, a2 are integers
-- a2 is unique in Ta
if OBJECT_ID('RapBands', 'U') is null
	begin
		create table RapBands (
			bandID int IDENTITY(1,1) NOT NULL,
			numberOfFollowers int UNIQUE, 
			bandName varchar(30) NOT NULL,
			foundationDate date,
			breakupDate date,

			PRIMARY KEY(bandID)
		)

		EXEC generateRandomDataForTable 'RapBands', 5000
	end

-- Tb(bid, b2, …)
-- bid is primary key
-- bid, b2 are integers
if OBJECT_ID('RapBandConcerts', 'U') is null
	begin
		create table RapBandConcerts (
			bandConcertID int IDENTITY(1,1) NOT NULL,
			capacity int,
			concertLocation varchar(30),

			PRIMARY KEY(bandConcertID)
		)

		EXEC generateRandomDataForTable 'RapBandConcerts', 10000
	end

-- Tc(cid, aid, bid, …)
-- cid is primary key
-- cid is an integer
-- aid and bid are foreign keys in Tc, referencing the primary keys in Ta and Tb, respectively.
if OBJECT_ID('RapBandConcertContracts', 'U') is null
	begin 
		create table RapBandConcertContracts (
			contractID int NOT NULL,
			bandID int,
			bandConcertID int,
			concertDatetime datetime,
			duration time,
			price smallint,

			PRIMARY KEY(contractID),

			FOREIGN KEY(bandID)
				REFERENCES RapBands(bandID),

			FOREIGN KEY(bandConcertID)
				REFERENCES RapBandConcerts(bandConcertID)
		)

		EXEC generateRandomDataForTable 'RapBandConcertContracts', 2500
	end


SELECT * FROM RapBands
SELECT * FROM RapBandConcerts
SELECT * FROM RapBandConcertContracts