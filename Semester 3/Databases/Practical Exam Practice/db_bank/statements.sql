IF EXISTS(SELECT 1 FROM sys.views WHERE NAME='getCardNumbersUsedInTransactionsAtAllATMs' and type='v')
DROP VIEW getCardNumbersUsedInTransactionsAtAllATMs

GO
CREATE VIEW getCardNumbersUsedInTransactionsAtAllATMs AS
	SELECT Ca.cardNumber
		FROM Cards Ca INNER JOIN BankAccounts BA
					ON Ca.bankAccountID = BA.bankAccountID
					  INNER JOIN Customers Cu
					ON BA.customerID = Cu.customerID
					  INNER JOIN Transactions T
					ON Cu.customerID = T.customerID
					  INNER JOIN ATMs A
					ON T.atmID = A.atmID
		GROUP BY Ca.cardNumber
	HAVING COUNT(Ca.cardNumber) = (SELECT COUNT(Ac.atmID) 
						FROM ATMs Ac)
GO

SELECT *
	FROM getCardNumbersUsedInTransactionsAtAllATMs


IF OBJECT_ID(N'ufListCardsWithTotalSumGreaterThanGivenSum', N'FN') IS NOT NULL
    DROP FUNCTION ufListCardsWithTotalSumGreaterThanGivenSum 

GO
CREATE OR ALTER FUNCTION ufListCardsWithTotalSumGreaterThanGivenSum (@givenSum int)
RETURNS TABLE AS
	RETURN
		SELECT C.cardNumber, C.codeCVV
			FROM Cards C INNER JOIN BankAccounts BA
						ON BA.bankAccountID = C.bankAccountID
						 INNER JOIN Customers Cu
						ON Cu.customerID = BA.customerID
						 INNER JOIN (SELECT customerID
										FROM Transactions
									GROUP BY customerID
										HAVING SUM(sumMoney) > @givenSum) t
						ON t.customerID = Cu.customerID
GO

SELECT * 
	FROM ufListCardsWithTotalSumGreaterThanGivenSum(2000)


IF EXISTS (SELECT 1 FROM sys.procedures WHERE Name = 'uspDeleteAllTransactionsForGivenCard')
    DROP PROCEDURE dbo.uspDeleteAllTransactionsForGivenCard

GO
CREATE OR ALTER PROCEDURE uspDeleteAllTransactionsForGivenCard @cardID int
AS
	BEGIN
		IF @cardID = NULL
		BEGIN
			RAISERROR('Card ID must be a non-null value!', 12, 1)
			RETURN
		END

		IF NOT EXISTS (SELECT * FROM Cards WHERE cardID = @cardID)
		BEGIN
			RAISERROR('No card was found for the given ID!', 12, 1)
			RETURN
		END

		DELETE
			FROM Transactions
		WHERE customerID IN (
			SELECT DISTINCT T.customerID
				FROM Transactions T INNER JOIN Customers Cu 
						ON T.customerID = Cu.customerID
									INNER JOIN BankAccounts BA
						ON BA.customerID = Cu.customerID
									INNER JOIN Cards Ca
						ON CA.bankAccountID = BA.bankAccountID
		)
	END
GO

EXEC uspDeleteAllTransactionsForGivenCard 1

SELECT *
	FROM Transactions