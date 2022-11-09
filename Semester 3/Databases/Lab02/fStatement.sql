-- find the songs that belong both to an album and a playlist
SELECT S.title as popularSongs
	FROM RapSongs S
WHERE EXISTS (
		SELECT * 
			FROM RapPlaylistSongAddition SA
		WHERE SA.songID = S.songID
		) AND S.rapperAlbumID IS NOT NULL;


-- the bands that already had concerts in the past
SELECT B.bandName
	FROM RapBands B
WHERE EXISTS (
		SELECT *
			FROM RapBandConcertContracts CC
		WHERE CC.bandID = B.bandID AND DATEDIFF(day, GETDATE(), CC.concertDatetime) < 0
	)