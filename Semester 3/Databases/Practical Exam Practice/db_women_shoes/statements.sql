IF OBJECT_ID('uspAddShoeToPresentationShop', 'P') IS NOT NULL
	DROP PROCEDURE uspAddShoeToPresentationShop

GO
CREATE OR ALTER PROCEDURE uspAddShoeToPresentationShop (@shoeID int, @shopID int, @numberOfShoes int) 
AS
	IF @shoeID IS NULL OR @shopID IS NULL OR @numberOfShoes IS NULL
	BEGIN
		RAISERROR('Arguments need to be non-null values!', 12, 1)
		RETURN
	END

	IF NOT EXISTS (SELECT shoeID FROM Shoes WHERE shoeID = @shoeID)
	BEGIN
		RAISERROR('No shoe has been found for the given ID!', 12, 1)
		RETURN
	END

	IF NOT EXISTS (SELECT shopID FROM PresentationShops WHERE shopID = @shopID)
	BEGIN
		RAISERROR('No shop has been found for the given ID!', 12, 1)
		RETURN
	END

	IF EXISTS (SELECT * FROM Stock WHERE shoeID = @shoeID AND shopID = @shopID)
	BEGIN
		RAISERROR('There already exists a stock for the given IDs!', 12, 1)
		RETURN
	END

	INSERT INTO Stock(shoeID, shopID, numberOfAvailableShoes)
		VALUES (@shoeID, @shopID, @numberOfShoes)
GO

EXEC uspAddShoeToPresentationShop 1, 2, 3

SELECT *
	FROM Stock


IF OBJECT_ID('showWomenWithAtLeast2ShoesBoughtFromGivenModel', 'V') IS NOT NULL
	DROP VIEW showWomenWithAtLeast2ShoesBoughtFromGivenModel


GO
CREATE VIEW showWomenWithAtLeast2ShoesBoughtFromGivenModel
AS
	SELECT *
		FROM Women
	WHERE womanID IN (
		SELECT W.womanID
			FROM Women W INNER JOIN Receipt R 
								ON W.womanID = R.womanID
						 INNER JOIN PresentationShops PS
								ON R.shopID = PS.shopID
						 INNER JOIN Stock St
								ON St.shopID = PS.shopID
						 INNER JOIN Shoes Sh
								ON Sh.shoeID = St.shoeID
						 INNER JOIN ShoeModels Sm
								ON Sm.modelID = Sh.modelID
		WHERE Sm.modelID = 4
			GROUP BY W.womanID, Sm.modelID
		HAVING COUNT(*) >= 1
	)
GO

SELECT *
	FROM showWomenWithAtLeast2ShoesBoughtFromGivenModel


IF OBJECT_ID('ufListShoesFoundInAtLeastGivenNumberOfPresentationShops', 'FN') IS NOT NULL
	DROP FUNCTION ufListShoesFoundInAtLeastGivenNumberOfPresentationShops

GO
CREATE OR ALTER FUNCTION ufListShoesFoundInAtLeastGivenNumberOfPresentationShops (@presentationShops int)
RETURNS TABLE AS
	RETURN
		SELECT *
			FROM Shoes
		WHERE shoeID IN (
				SELECT shoeID 
					FROM Stock
				GROUP BY shoeID
				HAVING COUNT(*) >= @presentationShops
			)
GO

SELECT *
	FROM ufListShoesFoundInAtLeastGivenNumberOfPresentationShops(2)