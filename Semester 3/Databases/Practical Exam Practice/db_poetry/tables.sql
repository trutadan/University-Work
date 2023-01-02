IF OBJECT_ID('Evaluation', 'U') IS NOT NULL
	DROP TABLE Evaluation

IF OBJECT_ID('Poems', 'U') IS NOT NULL
	DROP TABLE Poems

IF OBJECT_ID('InternalCompetitions', 'U') IS NOT NULL
	DROP TABLE InternalCompetitions

IF OBJECT_ID('Judges', 'U') IS NOT NULL
	DROP TABLE Judges

IF OBJECT_ID('ExternalAwards', 'U') IS NOT NULL
	DROP TABLE ExternalAwards

IF OBJECT_ID('Poets', 'U') IS NOT NULL
	DROP TABLE Poets



CREATE TABLE Poets (
	poetID int primary key identity,

	poetName varchar(30),
	penName varchar(30) unique,
	birthYear int
)

INSERT INTO Poets(poetName, penName, birthYear)
	VALUES ('poet1', 'pen12', 1994),
	('poet2', 'pen5', 1950),
	('poet6', 'pen2', 1968),
	('poet61', 'pen42', 1997),
	('poet5', 'pen21', 1995),
	('poet7', 'pen65', 2001),
	('poet9', 'pen6', 2001),
	('poet56', 'pen89', 1968),
	('poet34', 'pen11', 1956),
	('poet10', 'pen32', 1949),
	('poet34', 'pen66', 1989),
	('poet17', 'pen9', 1967)

SELECT *
	FROM Poets


CREATE TABLE ExternalAwards (
	awardID int primary key identity,

	awardName varchar(30),

	poetID int references Poets(poetID)
)

INSERT INTO ExternalAwards(awardName, poetID)
	VALUES ('award53', 3),
	('award6', 1),
	('award2', 2)

SELECT * 
	FROM ExternalAwards


CREATE TABLE Judges (
	judgeID int primary key identity,

	judgeName varchar(30)
)

INSERT INTO Judges(judgeName)
	VALUES ('judge1'),
	('judge5'),
	('judge0')

SELECT * 
	FROM Judges


CREATE TABLE InternalCompetitions (
	competitionID int primary key identity,

	competitionYear int,
	competitionWeek int check(competitionWeek >= 1 and competitionWeek <= 12),

	unique (competitionYear, competitionWeek)
)

INSERT INTO InternalCompetitions(competitionYear, competitionWeek)
	VALUES (2021, 3),
	(2022, 1),
	(2022, 12)

SELECT * 
	FROM InternalCompetitions


CREATE TABLE Poems (
	poemID int primary key identity,

	poemTitle varchar(30),
	poemText varchar(30),

	poetID int references Poets(poetID),
	competitionID int references InternalCompetitions(competitionID)
)

INSERT INTO Poems(poemTitle, poemText, poetID, competitionID)
	VALUES ('poem4', 'text2', 1, 3),
	('poem7', 'text11', 3, 2),
	('poem1', 'text0', 2, 2), 
	('poem31', 'text50', 5, 2), 
	('poem23', 'text30', 4, 2), 
	('poem15', 'text10', 6, 2), 
	('poem9', 'text07', 8, 2), 
	('poem444', 'text603', 7, 2),
	('poem24', 'text86', 7, 2),
	('poem16', 'text26', 7, 2),
	('poem78', 'text46', 7, 2),
	('poem00', 'text656', 7, 2),
	('poem5', 'text346', 7, 2)

SELECT *
	FROM Poems


CREATE TABLE Evaluation (
	judgeID int references Judges(judgeID),
	poemID int references Poems(poemID),

	primary key (judgeID, poemID),

	points int check(points > 0 and points <= 10)
)

INSERT INTO Evaluation(judgeID, poemID, points)
	VALUES (1, 2, 1),
	(2, 3, 4),
	(1, 3, 8),
	(3, 13, 3),
	(3, 11, 4),
	(1, 4, 1),
	(2, 8, 2),
	(1, 5, 4),
	(3, 7, 3),
	(2, 6, 4),
	(2, 9, 1),
	(1, 10, 2),
	(3, 12, 1),
	(3, 3, 2),
	(1, 6, 1), 
	(3, 2, 3)

SELECT *
	FROM Evaluation