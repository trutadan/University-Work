-- songs of the rappers that are members of a band
SELECT S.title
	FROM RapSongs S
WHERE S.rapperAlbumID IN (
	SELECT A.albumID
		FROM RapperAlbums A
	WHERE A.albumID IN (
		SELECT R.rapperID
			FROM Rappers R
	)
)


-- playlists that contain songs which are from albums
SELECT p.playlistName
	FROM RapPlaylists P
WHERE P.playlistID IN (
	SELECT PA.playlistID
		FROM RapPlaylistSongAddition PA
	WHERE PA.songID IN (
		SELECT S.rapperAlbumID
			FROM RapSongs S
		WHERE S.rapperAlbumID IS NOT NULL
	)
)