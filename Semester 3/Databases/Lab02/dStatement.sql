-- rappers who have a song which are both on an album and playlist
SELECT DISTINCT R.fullName
	FROM Rappers R
		INNER JOIN RapperAlbums A 
			ON R.rapperID = A.rapperID
		INNER JOIN RapSongs S
			ON S.rapperAlbumID = A.albumID
		INNER JOIN RapPlaylistSongAddition P
			ON P.songID = S.songID;


-- all rap bands and its members
SELECT B.bandName, R.fullName, R.stageName
	FROM Rappers R 
		RIGHT JOIN RapBands B
			ON B.bandID = R.bandID
				ORDER BY B.bandName

-- songs of rappers that belong to an album
SELECT R.fullName, R.stageName, S.title songTitle
	FROM Rappers R
		LEFT JOIN RapperAlbums RA
			ON RA.rapperID = R.rapperID
		LEFT JOIN RapSongs S
			ON S.rapperAlbumID = RA.albumID


-- rap bands with their concerts and their songs and appearances in playlists
SELECT C.bandConcertID concertID, B.bandName, A.title albumTitle, S.title songTitle, SA.playlistID
	FROM RapBands B
		FULL JOIN RapBandConcertContracts C
			ON B.bandID = C.bandID
		FULL JOIN RapBandAlbums A
			ON B.bandID = A.bandID
		FULL JOIN RapSongs S
			ON A.albumID = S.bandAlbumID
		FULL JOIN RapPlaylistSongAddition SA
			ON S.songID = SA.songID
				ORDER BY bandConcertID

