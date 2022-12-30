IF OBJECT_ID('Contracts', 'U') IS NOT NULL
	DROP TABLE Contracts

IF OBJECT_ID('Productions', 'U') IS NOT NULL
	DROP TABLE Productions

IF OBJECT_ID('Movies', 'U') IS NOT NULL
	DROP TABLE Movies
	
IF OBJECT_ID('Companies', 'U') IS NOT NULL
	DROP TABLE Companies

IF OBJECT_ID('Actors', 'U') IS NOT NULL
	DROP TABLE Actors

IF OBJECT_ID('StageDirectors', 'U') IS NOT NULL
	DROP TABLE StageDirectors


CREATE TABLE Companies (
	companyID int primary key identity,

	companyName varchar(30)
)

INSERT INTO Companies(companyName)
	VALUES ('company1'),
	('company2'),
	('company3')

SELECT * 
	FROM Companies


CREATE TABLE StageDirectors (
	directorID int primary key identity,

	directorName varchar(30),
	numberOfAwards int
)

INSERT INTO StageDirectors(directorName, numberOfAwards)
	VALUES ('director1', 12),
	('director2', 3),
	('director3', 0)

SELECT * 
	FROM StageDirectors


CREATE TABLE Movies (
	movieID int primary key identity,

	companyID int references Companies(companyID),
	directorID int references StageDirectors(directorID),

	unique (companyID, directorID),

	movieName varchar(30),
	releaseDate date
)

INSERT INTO Movies(companyID, directorID, movieName, releaseDate)
	VALUES (1, 2, 'movie1', '2017-02-05'),
	(1, 3, 'movie2', '2019-12-11'),
	(3, 1, 'movie3', '2020-03-09')

SELECT *
	FROM Movies


CREATE TABLE Productions (
	productionID int primary key identity,

	title varchar(30),

	movieID int references Movies(movieID)
)

INSERT INTO Productions(title, movieID)
	VALUES ('production1', 1),
	('production2', 3),
	('production3', 2),
	('production4', 3)

SELECT * 
	FROM Productions


CREATE TABLE Actors (
	actorID int primary key identity,

	actorName varchar(30),
	ranking int
)

INSERT INTO Actors(actorName, ranking)
	VALUES ('actor1', 3),
	('actor2', 14),
	('actor3', 1)

SELECT *
	FROM Actors


CREATE TABLE Contracts (
	productionID int references Productions(productionID),
	actorID int references Actors(actorID),

	primary key (productionID, actorID),

	entryMoment time
)

INSERT INTO Contracts(productionID, actorID, entryMoment)
	VALUES (1, 3, '01:02:34'),
	(2, 3, '00:02:05'),
	(1, 1, '00:21:43')

SELECT * 
	FROM Contracts