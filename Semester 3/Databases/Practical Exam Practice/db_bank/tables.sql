IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = N'Cards')
		DROP TABLE Cards

IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = N'BankAccounts')
		DROP TABLE BankAccounts
	
IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = N'Transactions')
		DROP TABLE Transactions

IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = N'Customers')
		DROP TABLE Customers

IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = N'ATMs')
		DROP TABLE ATMs


CREATE TABLE Customers (
	customerID int primary key identity,
	
	customerName varchar(30),
	dateOfBirth date,
)

INSERT INTO Customers(customerName, dateOfBirth)
	VALUES ('customer1', '2001-06-15T13:45:30'),
	('customer2', '1998-02-11T14:25:30'),
	('customer3', '2002-09-04T23:40:00')

SELECT *
	FROM Customers


CREATE TABLE ATMs (
	atmID int primary key identity,

	atmAddress varchar(30)
)

INSERT INTO ATMs(atmAddress)
	VALUES ('address1'),
	('address2'),
	('address3')

SELECT *
	FROM ATMs


CREATE TABLE Transactions (
	customerID int references Customers(customerID),
	atmID int references ATMs(atmID),

	primary key (customerID, atmID),

	sumMoney int,
	transactionDatetime datetime
)

INSERT INTO Transactions(sumMoney, transactionDatetime, customerID, atmID)
	VALUES (1263, '2021-06-01T10:35:20', 1, 3),
	(453, '2022-01-03T23:00:00', 2, 1),
	(1453, '2020-03-15T03:15:30', 1, 1),
	(1453, '2021-12-12T23:15:30', 1, 2),
	(100, '2021-05-22T22:05:10', 2, 3),
	(5000, '2022-02-24T10:50:33', 3, 1)

SELECT *
	FROM Transactions


CREATE TABLE BankAccounts (
	bankAccountID int primary key identity,
	
	codeIBAN varchar(30),
	currentBalance int,

	customerID int references Customers(customerID)
)

INSERT INTO BankAccounts(codeIBAN, currentBalance, customerID)
	VALUES ('RO49AAAA1B31007593840000', 4000, 1),
	('BE71096123456769', 4324, 1),
	('FI1410093000123458', 20324, 2),
	('NO8330001234567', 8931, 3)

SELECT * 
	FROM BankAccounts


CREATE TABLE Cards (
	cardID int primary key identity,

	cardNumber varchar(30),
	codeCVV varchar(3),

	bankAccountID int references BankAccounts(bankAccountID)
)

INSERT INTO Cards(cardNumber, codeCVV, bankAccountID)
	VALUES ('4532299961446587', '135', 2),
	('5193583456052779', '943', 1),
	('342587031818613', '290', 3)

SELECT * 
	FROM Cards