IF EXISTS (SELECT 1 FROM sys.procedures WHERE Name = 'uspDeleteJudgesForGivenName')
    DROP PROCEDURE dbo.uspDeleteJudgesForGivenName

GO
CREATE or ALTER PROCEDURE uspDeleteJudgesForGivenName (@judgeName varchar(30)) 
AS
	BEGIN
		DECLARE judgeCursor CURSOR FOR
			SELECT judgeID
				FROM Judges
			WHERE judgeName = @judgeName
		OPEN judgeCursor

		DECLARE @judgeID INT

		FETCH judgeCursor INTO @judgeID
		WHILE @@FETCH_STATUS = 0 
			BEGIN
				DELETE FROM Evaluation WHERE judgeID = @judgeID
				DELETE FROM Judges WHERE judgeID = @judgeID

				FETCH judgeCursor INTO @judgeID
			END

		CLOSE judgeCursor
		DEALLOCATE judgeCursor
	END
GO

EXEC uspDeleteJudgesForGivenName 'judge1'

SELECT *
	FROM Judges


IF EXISTS(SELECT 1 FROM sys.views WHERE NAME='showCompetitionsWithAtLeast10SubmittedPoemsWithLessThan5Points' and type='v')
	DROP VIEW showCompetitionsWithAtLeast10SubmittedPoemsWithLessThan5Points

GO
CREATE VIEW showCompetitionsWithAtLeast10SubmittedPoemsWithLessThan5Points 
AS
	SELECT C.competitionYear, C.competitionWeek
		FROM (
	SELECT Co.competitionID 
		FROM Evaluation E INNER JOIN Poems P
						ON E.poemID = P.poemID
						  INNER JOIN InternalCompetitions Co
						ON Co.competitionID = P.competitionID
	WHERE P.poemID IN (
		SELECT poemID 
			FROM Evaluation
		WHERE points < 5
		GROUP BY poemID
	) 
	
	GROUP BY Co.competitionID
	HAVING COUNT(*) >= 10) t
		INNER JOIN InternalCompetitions C ON C.competitionID = t.competitionID
GO

SELECT * 
	FROM showCompetitionsWithAtLeast10SubmittedPoemsWithLessThan5Points


IF OBJECT_ID(N'ufListUsersWithAtLeastGivenNumberOfPoems', N'FN') IS NOT NULL
    DROP FUNCTION ufListUsersWithAtLeastGivenNumberOfPoems

GO 
CREATE OR ALTER FUNCTION ufListUsersWithAtLeastGivenNumberOfPoems (@submittedPoems int) 
RETURNS TABLE AS
	RETURN 
		SELECT poetName, penName
			FROM POETS
		WHERE poetID IN (
				SELECT poetID
					FROM Poems
				GROUP BY poetID
				HAVING COUNT(*) >= @submittedPoems
			)
GO

SELECT * 
	FROM ufListUsersWithAtLeastGivenNumberOfPoems (3)