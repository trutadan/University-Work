IF EXISTS (SELECT 1 FROM sys.procedures WHERE Name = 'uspAddNewActorToCinemaProduction')
    DROP PROCEDURE dbo.uspAddNewActorToCinemaProduction

GO
CREATE or ALTER PROCEDURE uspAddNewActorToCinemaProduction (@actorID int, @entryMoment time, @productionID int) 
AS
	BEGIN
		IF @actorID = NULL OR @productionID = NULL
		BEGIN
			RAISERROR('IDs must have non-null values!', 12, 1)
			RETURN
		END

		IF NOT EXISTS (SELECT * FROM Actors WHERE actorID = @actorID)
		BEGIN
			RAISERROR('No actor found for the given ID!', 12, 1)
			RETURN
		END

		IF NOT EXISTS (SELECT * FROM Productions WHERE productionID = @productionID)
		BEGIN
			RAISERROR('No production found for the given ID!', 12, 1)
			RETURN
		END

		IF EXISTS (SELECT * FROM Contracts WHERE actorID = @actorID AND productionID = @productionID)
		BEGIN
			RAISERROR('There already exists Contract for given Actor ID and Production ID!', 12, 1)
			RETURN
		END

		INSERT INTO Contracts(productionID, actorID, entryMoment)
			VALUES (@productionID, @actorID, @entryMoment)
	END
GO

EXEC uspAddNewActorToCinemaProduction @actorID=1, @entryMoment='02:03:01', @productionID=4

EXEC uspAddNewActorToCinemaProduction @actorID=1, @entryMoment='00:03:51', @productionID=2

EXEC uspAddNewActorToCinemaProduction @actorID=1, @entryMoment='01:22:30', @productionID=3

SELECT *
	FROM Contracts


IF EXISTS(SELECT 1 FROM sys.views WHERE NAME='getActorNamesAppearingInAllProductions' and type='v')
	DROP VIEW getActorNamesAppearingInAllProductions

GO
CREATE VIEW getActorNamesAppearingInAllProductions
AS
	SELECT A.actorName
		FROM Actors A
	WHERE A.actorID IN (
		SELECT actorID
			FROM Contracts
		GROUP BY actorID
		HAVING COUNT(*) = (SELECT COUNT(*) FROM Productions)
	)
GO

SELECT * 
	FROM getActorNamesAppearingInAllProductions


IF OBJECT_ID(N'ufListMoviesWithReleaseDateAfterGivenDateAndAtLeastGivenProductions', N'FN') IS NOT NULL
    DROP FUNCTION ufListMoviesWithReleaseDateAfterGivenDateAndAtLeastGivenProductions  

GO 
CREATE OR ALTER FUNCTION ufListMoviesWithReleaseDateAfterGivenDateAndAtLeastGivenProductions (@releaseDate date, @productionsNumber int) 
RETURNS TABLE AS
	RETURN 
		SELECT * 
			FROM Movies
		WHERE releaseDate > @releaseDate AND movieID IN (
			SELECT movieID 
				FROM Productions
			GROUP BY movieID
			HAVING COUNT(*) >= @productionsNumber
		)
GO

SELECT * FROM ufListMoviesWithReleaseDateAfterGivenDateAndAtLeastGivenProductions ('2018-01-01', 2)