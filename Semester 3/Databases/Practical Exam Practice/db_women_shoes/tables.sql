IF OBJECT_ID('Receipt', 'U') IS NOT NULL
	DROP TABLE Receipt

IF OBJECT_ID('Stock', 'U') IS NOT NULL
	DROP TABLE Stock

IF OBJECT_ID('PresentationShops', 'U') IS NOT NULL
	DROP TABLE PresentationShops

IF OBJECT_ID('Shoes', 'U') IS NOT NULL
	DROP TABLE Shoes

IF OBJECT_ID('ShoeModels', 'U') IS NOT NULL
	DROP TABLE ShoeModels

IF OBJECT_ID('Women', 'U') IS NOT NULL
	DROP TABLE Women


CREATE TABLE Women (
	womanID int primary key identity,

	womanName varchar(30),
	maxAmount int
)

INSERT INTO Women(womanName, maxAmount)
	VALUES ('woman1', 300), ('woman11', 650), 
	('woman6', 1000), ('woman3', 100), ('woman2', 235)

SELECT * 
	FROM Women


CREATE TABLE ShoeModels (
	modelID int primary key identity,

	modelName varchar(30),
	season varchar(30)
)

INSERT INTO ShoeModels(modelName, season)
	VALUES ('model4', 'season1'), ('model1', 'season3'), ('model5', 'season1'), 
	('model6', 'season2'), ('model32', 'season4'), ('model7', 'season2'), ('model321', 'season3')

SELECT *
	FROM ShoeModels


CREATE TABLE Shoes (
	shoeID int primary key identity,

	price int,

	modelID int references ShoeModels(modelID)
)

INSERT INTO Shoes(price, modelID)
	VALUES (60, 2), (120, 1), (65, 3), (50, 5), (34, 4), (203, 2),
	(90, 4), (105, 7), (200, 6), (40, 2), (300, 3), (210, 5)

SELECT *
	FROM Shoes


CREATE TABLE PresentationShops (
	shopID int primary key identity,

	shopName varchar(30),
	city varchar(30)
)

INSERT INTO PresentationShops(shopName, city)
	VALUES ('shop4', 'city1'), ('shop32', 'city6'), ('shop22', 'city11'), 
	('shop1', 'city2'), ('shop6', 'city3'), ('shop7', 'city76'), ('shop543', 'city124')

SELECT *
	FROM PresentationShops

	
CREATE TABLE Stock (
	shoeID int references Shoes(shoeID),
	shopID int references PresentationShops(shopID),

	primary key (shoeID, shopID),

	numberOfAvailableShoes int
)

INSERT INTO Stock(shoeID, shopID, numberOfAvailableShoes)
	VALUES (1, 3, 5), (2, 4, 2), (6, 3, 6), 
	(3, 5, 12), (5, 4, 1), (5, 5, 11), (2, 3, 3)

SELECT * 
	FROM Stock


CREATE TABLE Receipt (
	womanID int references Women(womanID),
	shopID int references PresentationShops(shopID),

	primary key (womanID, shopID),

	numberOfShoesBought int,
	amountSpent int
)

INSERT INTO Receipt(womanID, shopID, numberOfShoesBought, amountSpent)
	VALUES (1, 2, 2, 600), (3, 5, 1, 120), (1, 6, 4, 453), 
	(5, 1, 2, 764), (4, 3, 1, 654), (1, 4, 3, 907), (2, 7, 5, 877)

SELECT *
	FROM Receipt