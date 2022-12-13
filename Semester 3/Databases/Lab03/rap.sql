use Rap;

set LANGUAGE English;
set DATEFORMAT YMD;


create table RapBands (
	bandID int IDENTITY(1,1) NOT NULL,
	bandName varchar(30) NOT NULL,
	foundationDate date,
	breakupDate date,

	PRIMARY KEY(bandID)
)


create table RapBandConcerts (
	bandConcertID int IDENTITY(1,1) NOT NULL,
	concertLocation varchar(30),
	capacity smallint,

	PRIMARY KEY(bandConcertID)
)


create table RapBandConcertContracts (
	bandID int NOT NULL,
	bandConcertID int NOT NULL,
	concertDatetime datetime NOT NULL,
	duration time,
	price smallint,

	PRIMARY KEY(bandID, bandConcertID),

	FOREIGN KEY(bandID)
		REFERENCES RapBands(bandID)
		ON DELETE CASCADE,

	FOREIGN KEY(bandConcertID)
		REFERENCES RapBandConcerts(bandConcertID)
		ON DELETE CASCADE
)


create table RapBandFans (
	rapBandFanID int IDENTITY(1,1) NOT NULL,
	fullName varchar(30) NOT NULL,
	dateOfBirth date,
	favouriteSong varchar(30),
	hobby varchar(30),

	PRIMARY KEY(rapBandFanID)
)


create table RapBandFanAdoration (
	bandID int NOT NULL,
	rapBandFanID int NOT NULL,
	startingDate date,

	FOREIGN KEY(bandID)
		REFERENCES RapBands(bandID)
		ON DELETE CASCADE,

	FOREIGN KEY(rapBandFanID)
		REFERENCES RapBandFans(rapBandFanID)
		ON DELETE CASCADE
)


create table Rappers (
	rapperID int IDENTITY(1,1) NOT NULL,
	bandID int,
	fullName varchar(30),
	stageName varchar(30),
	dateOfBirth date,
	birthPlace varchar(30),

	PRIMARY KEY (rapperID),

	FOREIGN KEY(bandID)
		REFERENCES RapBands(bandID)
)


create table RapperConcerts (
	rapperConcertID int IDENTITY(1,1) NOT NULL,
	concertLocation varchar(30),
	capacity smallint,

	PRIMARY KEY(rapperConcertID)
)


create table RapperConcertContracts (
	rapperID int NOT NULL,
	rapperConcertID int NOT NULL,
	concertDatetime datetime NOT NULL,
	duration time,
	price smallint,

	PRIMARY KEY(rapperID, rapperConcertID),

	FOREIGN KEY(rapperID)
		REFERENCES Rappers(rapperID)
		ON DELETE CASCADE,

	FOREIGN KEY(rapperConcertID)
		REFERENCES RapperConcerts(rapperConcertID)
		ON DELETE CASCADE
)


create table RapperFans (
	rapperFanID int IDENTITY(1,1) NOT NULL,
	fullName varchar(30) NOT NULL,
	dateOfBirth date,
	favouriteSong varchar(30),
	hobby varchar(30),

	PRIMARY KEY(rapperFanID)
)


create table RapperFanAdoration (
	rapperID int NOT NULL,
	rapperFanID int NOT NULL,
	startingDate date,

	FOREIGN KEY(rapperID)
		REFERENCES Rappers(rapperID)
		ON DELETE CASCADE,

	FOREIGN KEY(rapperFanID)
		REFERENCES RapperFans(rapperFanID)
		ON DELETE CASCADE
)


create table RapperAlbums (
	albumID int IDENTITY(1,1) NOT NULL,
	rapperID int NOT NULL,
	title varchar(40),
	duration time,
	numberOfSongs tinyint NOT NULL,
	releaseDate date,

	PRIMARY KEY(albumID),

	FOREIGN KEY(rapperID)
		REFERENCES Rappers(rapperID)
)


create table RapBandAlbums (
	albumID int IDENTITY(1,1) NOT NULL,
	bandID int NOT NULL,
	title varchar(40),
	duration time,
	numberOfSongs tinyint NOT NULL,
	releaseDate date,

	PRIMARY KEY(albumID),

	FOREIGN KEY(bandID)
		REFERENCES RapBands(bandID)
)


create table RapSongs (
	songID int IDENTITY(1,1) NOT NULL,
	rapperAlbumID int,
	bandAlbumID int,
	title varchar(40) NOT NULL,
	duration time,
	streams int,

	PRIMARY KEY(songID),

	FOREIGN KEY(rapperAlbumID) 
		REFERENCES RapperAlbums(albumID),

	FOREIGN KEY(bandAlbumID) 
		REFERENCES RapBandAlbums(albumID)
)


create table RapPlaylists (
	playlistID int IDENTITY(1,1) NOT NULL,
	playlistName varchar(30) NOT NULL,
	numberOfEnjoyers int,
	numberOfSongs smallint,
	duration time,
	referenceLink varchar(100) NOT NULL,

	PRIMARY KEY(playlistID)
)


create table RapPlaylistSongAddition (
	playlistID int NOT NULL,
	songID int NOT NULL,
	userName varchar(20) NOT NULL,
	additionDate date,

	PRIMARY KEY(playlistID, songID),

	FOREIGN KEY(playlistID)
		REFERENCES RapPlaylists(playlistID)
		ON DELETE CASCADE,

	FOREIGN KEY(songID)
		REFERENCES RapSongs(songID)
		ON DELETE CASCADE
)