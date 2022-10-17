use Rap;

-- a festival hosts multiple rap fans
-- a festival consists of multiple concerts
-- a festival hosts several rappers
create table RapFestival (
	festivalID int NOT NULL,
	festivalLocation varchar(30) NOT NULL,
	maximumCapacity int,
	startingDatetime datetime NOT NULL,
	endDatetime datetime NOT NULL,

	PRIMARY KEY(festivalID)
)

-- a rap fan can take part in several festivals
create table RapFan (
	rapFanID int NOT NULL,
	fullName varchar(20) NOT NULL,
	age tinyint,
	hobby varchar(20),

	PRIMARY KEY(rapFanID),
)

-- m:n relation between festivals and fans
create table RapFestivalTicket (
	rapFanID int NOT NULL,
	festivalID int NOT NULL,
	price int,
	buyDatetime datetime,

	PRIMARY KEY(rapFanID, festivalID),
	
	FOREIGN KEY(rapFanID)
		REFERENCES RapFan(rapFanID)
		ON DELETE CASCADE,

	FOREIGN KEY(festivalID)
		REFERENCES RapFestival(festivalID)
		ON DELETE CASCADE
)

-- a concert hosts multiple rapper fans
-- several concerts take part during a festival
-- festivalID may be NULL since a concert can not belong to a festival
create table RapConcert (
	concertID int NOT NULL,
	festivalID int,
	concertLocation varchar(30) NOT NULL,
	concertDatetime datetime NOT NULL,
	duration smallint,

	PRIMARY KEY(concertID),

	FOREIGN KEY(festivalID)
		REFERENCES RapFestival(festivalID)
)

-- a band consists of several rappers
-- 1:n relation between a band and rappers
create table RapBand (
	bandID int NOT NULL,
	bandName varchar(20) NOT NULL,
	foundationDate date NOT NULL,
	breakupDate date,

	PRIMARY KEY(bandID)
)

-- a rapper has many fans
-- a rapper can take part in several festivals
-- several rappers create a band
-- concertID may be NULL since a rapper can choose not to have any concert
create table Rapper (
	rapperID int NOT NULL,
	concertID int,
	bandID int,
	fullName varchar(30) NOT NULL,
	age tinyint,
	numberOfSongs tinyint,
	birthPlace varchar(30),

	PRIMARY KEY(rapperID),

	FOREIGN KEY(concertID)
		REFERENCES RapConcert(concertID),

	FOREIGN KEY(bandID)
		REFERENCES RapBand(bandID),
)

-- 1:n relation between concert and rapper's fans
-- 1:n relation between rapper his fans
-- concertID may be NULL since a rapper fan can choose not to take part to any concert
create table RapperFan (
	rapperFanID int NOT NULL,
	concertID int,
	rapperID int NOT NULL,
	fullName varchar(30) NOT NULL,
	age tinyint,
	favouriteSong varchar(30),
	hobby varchar(30),

	PRIMARY KEY(rapperFanID),

	FOREIGN KEY(rapperID)
		REFERENCES Rapper(rapperID)
		ON DELETE CASCADE,

	FOREIGN KEY(concertID)
		REFERENCES RapConcert(concertID)
)

-- m:n relation between festivals and rappers
create table RapFestivalContract (
	festivalID int NOT NULL,
	rapperID int NOT NULL,
	conclusionDatetime datetime NOT NULL,

	PRIMARY KEY(festivalID, rapperID),
	
	FOREIGN KEY(festivalID)
		REFERENCES RapFestival(festivalID)
		ON DELETE CASCADE,

	FOREIGN KEY(rapperID)
		REFERENCES Rapper(rapperID)
		ON DELETE CASCADE
)

-- an album contains many rap songs
-- 1:n relation between an album and its consisting songs
create table RapAlbum (
	albumID int NOT NULL,
	rapperID int NOT NULL,
	title varchar(20),
	duration smallint,
	numberOfSongs tinyint NOT NULL,
	releaseDate date,

	PRIMARY KEY(albumID),

	FOREIGN KEY(rapperID)
		REFERENCES Rapper(rapperID)
		ON DELETE CASCADE
)

-- a song can be added to multiple playlists
-- albumID may be NULL since a song can not belong to an album
create table RapSong (
	songID int NOT NULL,
	albumID int,
	title varchar(20) NOT NULL,
	duration smallint,
	streams int,

	PRIMARY KEY(songID),

	FOREIGN KEY(albumID) 
		REFERENCES RapAlbum(albumID)
)

-- a playlist contains several songs
create table RapPlaylist(
	playlistID int NOT NULL,
	playlistName varchar(20) NOT NULL,
	numberOfFollowers int,
	duration smallint,

	PRIMARY KEY(playlistID)
)

-- m:n relation between playlist and songs
create table RapPlaylistSongAddition (
	playlistID int NOT NULL,
	songID int NOT NULL,
	userName varchar(20) NOT NULL,
	additionDate date,

	PRIMARY KEY(playlistID, songID),

	FOREIGN KEY(playlistID)
		REFERENCES RapPlaylist(playlistID)
		ON DELETE CASCADE,

	FOREIGN KEY(songID)
		REFERENCES RapSong(songID)
		ON DELETE CASCADE
)