use Rap;


INSERT INTO RapBands
	(bandName, foundationDate, breakupDate)
VALUES
	('Controlul Tehnic de Calitate', '1997', null),
	('Parazitii', '1994', null),
	('BUG Mafia', '1993', null),
	('La Familia', '1997', null),
	('Specii', '2008', null);


INSERT INTO RapBandConcerts
	(concertLocation, capacity)
VALUES
	('Bucuresti, Wave Club', 3000),
	('Timisoara, Heaven', 1500),
	('Bucuresti, ONE Club', 2000);


INSERT INTO RapBandConcertContracts
	(bandID, bandConcertID, concertDatetime, duration, price)
VALUES
	(4, 2, '2020-06-16T22:00:00', '01:00:00', 1500),
	(2, 1, '2022-11-12T23:00:00', '00:50:00', 2300),
	(2, 2, '2022-12-17T19:00:00', '00:50:00', 2500),
	(5, 3, '2022-11-26T21:00:00', '01:20:00', 1800),
	(5, 1, '2022-09-16T23:00:00', '01:15:00', 1700);


INSERT INTO RapBandFans 
	(fullName, dateOfBirth,	favouriteSong, hobby)
VALUES
	('Iulian Parvu', '2000/12/15', 'Una din Doua', 'cooking'),
	('Octavian Tanase', '1991/02/24', 'Onoare', 'meditation'),
	('Marian Popescu', '1995/11/03', 'Azi nu', 'reading'),
	('Mihai Bita', '1979/02/08', 'Spune-mi', 'drinking'),
	('Marius Stelian Craciun', '1980/04/19', 'Ambrozie', 'reading');


INSERT INTO RapBandFanAdoration 
	(bandID, rapBandFanID, startingDate)
VALUES
	(3, 2, '2016/04/13'),
	(5, 3, '2019/01/10'),
	(2, 5, '2018/05/16'),
	(1, 1, '2017/07/02'),
	(2, 5, '2009/06/11'),
	(4, 4, '2018/11/03'),
	(1, 2, '2015/12/26');


INSERT INTO Rappers
	(bandID, fullName, stageName, dateOfBirth, birthPlace)
VALUES
	(2, 'Stefan Ion', 'Cheloo', '1978/03/24', 'Bucuresti'),
	(1, 'Razvan Eremia', 'Deliric', '1982/08/16', null),
	(1, 'Vlad Munteanu', 'Doc', null, 'Bucuresti'),
	(2, 'Bogdan Ionut Pastaca', 'Ombladon', '1979/04/06', null),
	(null, 'Vlad Flueraru', null, null, null),
	(3, 'Adrian Alin Demeter', 'Uzzi', null, 'Bucuresti'),
	(1, 'Vlad Dobrescu', null, '8 august 1980', 'Bucuresti'),
	(null, 'Laurentiu Mocanu', 'Guess Who', '1986/06/02', 'Bucuresti'),
	(null, 'Marius Stelian Craciun', 'Cedry2k', '1980/04/19', 'Bucuresti'),
	(3, 'Vlad Irimia', 'Tata Vlad', '1976/10/17', 'Sebes'),
	(null, 'Mihai Bita', 'Bitza', '1979/02/08', 'Bucuresti'),
	(null, null, 'Jamie aka Crack Sinatra', null, 'Bucuresti'),
	(5, 'Dragos Tudorache', 'Dragonu AK47', '1985/10/13', 'Barlad'),
	(null, 'Dragos Nichifor', 'Grasu XXL', '1981/08/11', 'Buhusi'),
	(null, null, 'Tomi Marfa', null, null),
	(3, 'Adrian Alin Demeter', 'Uzzi', '1978/03/26', 'Bucuresti'),
	(null, 'Paul Maracine', 'Spike', '1985/04/21', 'Bucuresti'),
	(5, 'Mihai Adamescu', 'Chimie', null, 'Constanta'), 
	(null, 'Bogdan Vlasceanu', 'F. Charm', '1981/05/09', 'Bucuresti');


INSERT INTO RapperConcerts
	(concertLocation, capacity)
VALUES
	('Aby Stage Bar � R�mnicu V�lcea', 1500),
	('Ploiesti, Irish Pub', 1700);


INSERT INTO RapperConcertContracts 
	(rapperID, rapperConcertID,	concertDatetime, duration, price)
VALUES
	(9, 1, '2022-11-04T19:00:00', '01:00:00', 900),
	(9, 2, '2022-11-05T19:00:00', '01:10:00', 1000);


INSERT INTO RapperFans
	(fullName, dateOfBirth, favouriteSong, hobby)
VALUES
	('Andrei Ion', '1997/07/12', 'Vorbeste Vinul', 'boxing'),
	('Paul Oprean', '2001/10/22', 'Un Anonim Celebru', 'fishing'),
	('Stefan Ion', '1978/03/24', 'Scandal', 'rally'),
	('Laurentiu Ursu', '2001/03/12', 'Ambrozie', 'running'),
	('Mihai Bita', '1979/02/08', 'Unu', 'drinking');


INSERT INTO RapperFanAdoration 
	(rapperID, rapperFanID, startingDate)
VALUES
	(3, 1, '2006/03/23'),
	(5, 5, '2019/11/30'),
	(2, 4, '2014/05/12'),
	(17, 1, '2015/12/30'),
	(2, 3, '2011/03/21'),
	(14, 1, '2008/10/03'),
	(1, 2, '2015/12/26');
	

INSERT INTO RapperAlbums
	(rapperID, title, duration, numberOfSongs,	releaseDate)
VALUES 
	(7, 'In Sfarsit', '00:48:35', 14, '2013/12/08'),
	(1, 'Killing The Classics', '00:34:12', 8, '2021/12/08'),
	(3, 'Eu', '00:51:47', 16, '2018/05/31'),
	(2, 'Deliric x Silent Strike II', '00:48:18', 16, '2019/09/27'),
	(4, 'Cel mai prost din curtea scolii', '00:50:05', 17, '2007/05/24'),
	(13, 'Drumul spre succes', '00:42:33', 13, null),
	(8, 'Tot Mai Sus', '00:47:25', 15, '2011/09/20');


INSERT INTO RapBandAlbums
	(bandID, title,	duration, numberOfSongs, releaseDate)
VALUES
	(1, 'Secretul din Atom', '00:26:24', 9, '2002/03/01'),
	(3, 'Inapoi in Viitor', '01:14:00', 22, '2011/09/01'),
	(2, 'Slalom printre cretini', '01:04:00', 21, '2007/11/22'),
	(3, 'Baietii Buni', '01:12:00', 22, '2003/12/07'),
	(4, 'Codul Bunelor Maniere', '00:50:47', 18, '2017/06/09'),
	(2, 'Arma Secreta', '00:33:34', 11, '2019/05/24');


INSERT INTO RapSongs 
	(rapperAlbumID, bandAlbumID, title, duration, streams)
VALUES 
	(3, null, 'Unu', '00:02:34', 185852),
	(1, null, 'Astia Mici', '00:05:04', 256783),
	(null, null, 'Unde se termina visele', '00:03:01', 1682387),
	(null, 1, 'Terapie De Soc', '00:04:15', 22103),
	(null, null, 'Din inima', '00:03:00', 22762),
	(null, 3, 'Mesaj Pentru Europa', '00:03:05', 952179),
	(null, null, 'Turbofin', '00:03:51', 46030458),
	(null, 6, 'Lacrimi de Ceara', '00:02:22', 1307689),
	(null, null, 'Scandal', '00:03:17', 974085),
	(null, 2, 'Inainte Sa Plec', '00:04:09', 915456),
	(null, 4, 'Romaneste', '00:04:17', 349531),
	(null, 5, 'Portret De Politician', '00:03:14', 734658),
	(1, null, 'Insomnii', '00:03:14', 561234);


INSERT INTO RapPlaylists
	(playlistName, numberOfEnjoyers, numberOfSongs, duration, referenceLink)
VALUES
	('The Sound of Romanian Rap', 279, 221, '13:00:00', 'https://open.spotify.com/playlist/5xxIhwNhCZlkyFKpA8hxRj'),
	('Top 100 melodii - Rap Romanesc', null, 140, '08:43:29', 'https://www.youtube.com/playlist?list=PLTX0cyWqF3DrGPd0VIp5F-Nnfmi-cTlMO'),
	('romanian rap', 2, 404, '23:59:59', 'https://open.spotify.com/playlist/11kec6qOjgHa8eVgtuK9F5'),
	('Rap romanesc 2000-2018', 1098, 164, '10:52:00', 'https://open.spotify.com/playlist/5yC1y2GPODXgyKZuwJ90bt?si=4af981df9a094f60');


INSERT INTO RapPlaylistSongAddition
	(playlistID, songID, userName, additionDate)
VALUES
	(4, 3, 'adrian.r907', '2020/12/29'),
	(2, 5, 'Emilian Vlasceanu', '2020/12/08'),
	(1, 7, 'The Sound of Spotify', '2021/12/10'),
	(3, 1, 'trutadanalexandru', '2022/08/06'),
	(4, 1, 'adrian.r907', '2020/12/29'),
	(3, 6, 'trutadanalexandru', '2022/08/06');