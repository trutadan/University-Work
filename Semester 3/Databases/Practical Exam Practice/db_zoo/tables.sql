IF OBJECT_ID('Visits', 'U') IS NOT NULL
	DROP TABLE Visits

IF OBJECT_ID('Eat', 'U') IS NOT NULL
	DROP TABLE Eat

IF OBJECT_ID('Animals', 'U') IS NOT NULL
	DROP TABLE Animals

IF OBJECT_ID('Zoos', 'U') IS NOT NULL
	DROP TABLE Zoos

IF OBJECT_ID('Visitors', 'U') IS NOT NULL
	DROP TABLE Visitors

IF OBJECT_ID('Food', 'U') IS NOT NULL
	DROP TABLE Food


CREATE TABLE Food (
	foodID int primary key identity,

	foodName varchar(30)
)

INSERT INTO Food(foodName)
	VALUES ('food4'), ('food9'), ('food23'),
	('food1'), ('food54'), ('food12'), ('food65')

SELECT * 
	FROM Food


CREATE TABLE Visitors (
	visitorID int primary key identity,

	visitorName varchar(30),
	age int
)

INSERT INTO Visitors(visitorName, age)
	VALUES ('visitor12', 16), ('visitor1', 45), ('visitor5', 34),
	('visitor23', 22), ('visitor9', 32), ('visitor143', 33), ('visitor0', 11)

SELECT *
	FROM Visitors


CREATE TABLE Zoos (
	zooID int primary key identity,

	zooAdmin varchar(30),
	zooName varchar(30)
)

INSERT INTO Zoos(zooAdmin, zooName)
	VALUES ('admin34', 'zoo11'), ('admin11', 'zoo26'), ('admin67', 'zoo7'),
	('admin5', 'zoo2'), ('admin3', 'zoo32'), ('admin55', 'zoo87'), ('admin234', 'zoo90')

SELECT *
	FROM Zoos


CREATE TABLE Visits (
	zooID int references Zoos(zooID),
	visitorID int references Visitors(visitorID),

	primary key (zooID, visitorID),

	visitDay int,
	price int
)

INSERT INTO Visits(zooID, visitorID, visitDay, price)
	VALUES (1, 5, 4, 12), (3, 4, 1, 65), (5, 2, 23, 25), (2, 3, 31, 12),
	(2, 6, 17, 25), (1, 3, 6, 12), (5, 3, 3, 65), (6, 6, 2, 53), (4, 5, 1, 36)

SELECT * 
	FROM Visits


CREATE TABLE Animals (
	animalID int primary key identity,

	animalName varchar(30),
	dateOfBirth date,

	zooID int references Zoos(zooID)
)

INSERT INTO Animals(animalName, dateOfBirth, zooID)
	VALUES ('animal1', '02-03-2005', 1), ('animal2', '11-10-2018', 5), ('animal6', '01-05-2019', 6),
	('animal3', '11-12-2017', 7), ('animal11', '04-09-2016', 1), ('animal16', '05-07-2021', 7), 
	('animal21', '11-03-2009', 2), ('animal99', '07-06-2019', 1)


SELECT *
	FROM Animals


CREATE TABLE Eat (
	animalID int references Animals(animalID),
	foodID int references Food(foodID),

	primary key (animalID, foodID),

	dailyQuota int
)

INSERT INTO Eat(animalID, foodID, dailyQuota)
	VALUES (2, 5, 3), (6, 1, 1), (5, 7, 6), 
	(3, 1, 7), (6, 7, 3), (7, 3, 4), (1, 4, 5)

SELECT *
	FROM Eat