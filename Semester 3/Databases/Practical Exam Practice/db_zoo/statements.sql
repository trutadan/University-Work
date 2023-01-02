IF OBJECT_ID('uspDeleteAllFoodQuotasForGivenAnimals ', 'P') IS NOT NULL
	DROP PROCEDURE uspDeleteAllFoodQuotasForGivenAnimals 

GO
CREATE OR ALTER PROCEDURE uspDeleteAllFoodQuotasForGivenAnimals (@animalID int)
AS
	IF @animalID IS NULL
	BEGIN
		RAISERROR('Animal ID must be non-null value!', 12, 1)
		RETURN
	END

	DELETE 
		FROM Eat
	WHERE animalID = @animalID
GO

EXEC uspDeleteAllFoodQuotasForGivenAnimals 6

SELECT * 
	FROM Eat


IF OBJECT_ID('getIDsOfZoosWithSmallestNumberOfVisits', 'V') IS NOT NULL
	DROP VIEW getIDsOfZoosWithSmallestNumberOfVisits

GO
CREATE VIEW getIDsOfZoosWithSmallestNumberOfVisits
AS
	SELECT zooID
		FROM Zoos
	WHERE zooID IN (
			SELECT zooID
				FROM Visits
			GROUP BY zooID
			HAVING COUNT(*) = (SELECT MIN(t.zooCount) FROM (SELECT COUNT(zooID) zooCount FROM Visits GROUP BY zooID) t)
		)

GO

SELECT * 
	FROM getIDsOfZoosWithSmallestNumberOfVisits 


IF OBJECT_ID('ufListIDsOfVisitorsOfZoosWithAtLeastGivenNumberOfAnimals', 'FN') IS NOT NULL
	DROP FUNCTION ufListIDsOfVisitorsOfZoosWithAtLeastGivenNumberOfAnimals

GO
CREATE OR ALTER FUNCTION ufListIDsOfVisitorsOfZoosWithAtLeastGivenNumberOfAnimals (@numberOfAnimals int)
RETURNS TABLE AS
	RETURN
		SELECT visitorID
			FROM Visits
		WHERE zooID IN (
			SELECT zooID	
				FROM Animals
			GROUP BY zooID
			HAVING COUNT(*) >= @numberOfAnimals
		)

GO

SELECT *
	FROM ufListIDsOfVisitorsOfZoosWithAtLeastGivenNumberOfAnimals(3)