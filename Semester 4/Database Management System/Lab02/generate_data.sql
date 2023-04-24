IF 'generateRandomDataForTable' not in (SELECT ROUTINE_NAME FROM INFORMATION_SCHEMA.ROUTINES) 
BEGIN
    PRINT 'generateRandomDataForTable procedure does not exist!'
    RETURN
END

-- generate random data for the given number of rows and for the given tables
EXEC generateRandomDataForTable 'RapBands', 10

EXEC generateRandomDataForTable 'RapBandAlbums', 20

EXEC generateRandomDataForTable 'RapBandAlbums', 40
