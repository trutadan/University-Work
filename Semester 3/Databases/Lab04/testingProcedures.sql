-- add given table to the Tables table
GO
	CREATE OR ALTER PROCEDURE addToTables (@tableName VARCHAR(50)) AS
BEGIN
	-- check if given table is in the database
	IF @tableName NOT IN (SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES)
		BEGIN
			PRINT @tableName + ' not found in the database!'
			RETURN
		END

	-- check if the given table is in the Tables table
	IF @tableName IN (SELECT [Name] from [Tables]) 
		BEGIN
			PRINT @tableName + ' already present in Tables!'
			RETURN
		END

	-- insert given table in the Tables table
	INSERT INTO [Tables] ([Name]) 
		VALUES (@tableName)
END


-- add given table to the Views table
GO
	CREATE OR ALTER PROCEDURE addToViews (@viewName VARCHAR(50)) AS
BEGIN
	-- check if given table is in the database
	IF @viewName NOT IN (SELECT TABLE_NAME FROM INFORMATION_SCHEMA.VIEWS)
		BEGIN
			PRINT @viewName + ' not present in the database!'
			RETURN
		END

	-- check if the given table is in the Views table
	IF @viewName IN (SELECT [Name] from [Views]) 
		BEGIN
			PRINT @viewName + ' already present in Views!'
			RETURN
		END

	-- insert given table in the Views table
	INSERT INTO [Views] ([Name]) 
		VALUES (@viewName)
END


-- add given table to the Tests table
GO
	CREATE OR ALTER PROCEDURE addToTests (@testName VARCHAR(50)) AS
BEGIN
	-- check if the given table is in the Tests table
	IF @testName IN (SELECT [Name] from [Tests]) 
		BEGIN
			PRINT @testName + ' already present in Tests!'
			RETURN
		END

	-- insert given table in the Tests table
	INSERT INTO [Tests] ([Name]) 
	VALUES (@testName)
END


-- create the connection between a test and a table
GO
	CREATE OR ALTER PROCEDURE connectTableToTest (@tableName VARCHAR(50), @testName VARCHAR(50), @rows INT, @pos INT) AS
BEGIN
	-- check if the given table is in the Tables table
	IF @tableName NOT IN (SELECT [Name] FROM [Tables]) 
		BEGIN
			PRINT @tableName + ' not present in Tables!'
			RETURN
		END

	-- check if the given test is in the Tests table
	IF @testName NOT IN (SELECT [Name] FROM [Tests])
		BEGIN
			PRINT @testName + ' not present in Tests!'
			RETURN
		END

	-- check if the given position already in the TestTables table
	IF EXISTS( 
		SELECT * 
			FROM TestTables T1 JOIN Tests T2 ON T1.TestID = T2.TestID
		WHERE T2.[Name] = @testName AND Position = @pos
	)
		BEGIN
			PRINT 'Position ' + @pos + ' provided conflicts with previous positions!'
			RETURN
		END

	-- get the ID of the test based on its name, the ID of the table based on its name
	-- and insert them in TestTables using the rows and pos passed as parameters
	INSERT INTO [TestTables] (TestID, TableID, NoOfRows, Position) 
	VALUES (
		(SELECT [Tests].TestID FROM [Tests] WHERE [Name] = @testName),
		(SELECT [Tables].TableID FROM [Tables] WHERE [Name] = @tableName),
		@rows,
		@pos
		)
END


-- create the connection between a view and a test
GO
	CREATE OR ALTER PROCEDURE connectViewToTest (@viewName VARCHAR(50), @testName VARCHAR(50)) AS
BEGIN
	-- check if the given view is in the Views table
	IF @viewName NOT IN (SELECT [Name] FROM [Views]) 
		BEGIN
			PRINT @viewName + ' not present in Views!'
			RETURN
		END

	-- check if the given test is in the Tests table
	IF @testName NOT IN (Select [Name] FROM [Tests]) 
		BEGIN
			PRINT @testName + ' not present in Tests!'
			RETURN
		END

	-- get the IDs of the test and view tables and insert them in TestViews table
	INSERT INTO [TestViews] (TestID, ViewID)
	VALUES(
		(SELECT [Tests].TestID FROM [Tests] WHERE [Name] = @testName),
		(SELECT [Views].ViewID FROM [Views] WHERE [Name] = @viewName)
	)
END


-- run testing for a given test
GO
	CREATE or ALTER PROCEDURE runTest (@testName varchar(50)) AS
BEGIN
    -- the test name provided does not belong to Tests table
	IF @testName not in (SELECT Name FROM Tests) BEGIN
        PRINT @testName + ' not in Tests!'
        RETURN
    END

    DECLARE @command varchar(100)
    DECLARE @testStartTime datetime2
    DECLARE @startTime datetime2
    DECLARE @endTime datetime2
    DECLARE @table varchar(50)
    DECLARE @rows int
    DECLARE @pos int
    DECLARE @view varchar(50)
    DECLARE @testId int

	-- get the ID of the test based on its name
    SELECT @testId = TestID 
		FROM Tests 
	WHERE Name = @testName
    
	-- get the index of the last test that was ran
	DECLARE @testRunId int
    SET @testRunId = (SELECT max(TestRunID)+1 FROM TestRuns)

    IF @testRunId is NULL
        SET @testRunId = 0

	-- create a cursor for all the tables that take part into the test(which are contained in TestTables table)
    DECLARE tableCursor CURSOR SCROLL FOR
        SELECT T1.Name, T2.NoOfRows, T2.Position
			FROM Tables T1 join TestTables T2 ON T1.TableID = T2.TableID
        WHERE T2.TestID = @testId
			ORDER BY T2.Position

	-- create a cursor for all the views that take part into the test(which are contained int TestViews table)
    DECLARE viewCursor CURSOR FOR
        SELECT V.Name
			FROM Views V join TestViews TV ON V.ViewID = TV.ViewID
        WHERE TV.TestID = @testId

    SET @testStartTime = sysdatetime()
    OPEN tableCursor

    FETCH LAST FROM tableCursor INTO @table, @rows, @pos

	-- delete the possible existing information from the tables contained in the test
    WHILE @@FETCH_STATUS = 0 
	BEGIN
        EXEC ('DELETE FROM '+ @table)
        FETCH PRIOR FROM tableCursor INTO @table, @rows, @pos
    END

    CLOSE tableCursor
    OPEN tableCursor

	-- if not mentioned, an error saying "Cannot insert ... IDENTITY_INSERT is set to OFF" will be displayed
    SET IDENTITY_INSERT TestRuns ON

	-- insert the initial information about the test that is currently running
    INSERT INTO TestRuns (TestRunID, Description, StartAt) 
		VALUES (@testRunId, 'Tests results for: ' + @testName + '...', @testStartTime)
    
	-- set IDENTITY_INSERT back to OFF after we do not need it anymore
	SET IDENTITY_INSERT TestRuns OFF

    FETCH tableCursor INTO @table, @rows, @pos

	-- generate new data for the tables contained in the test
    WHILE @@FETCH_STATUS = 0 
	BEGIN
		-- check if the procedure that generates random data for a table exists
        IF 'generateRandomDataForTable' not in (SELECT ROUTINE_NAME FROM INFORMATION_SCHEMA.ROUTINES) 
		BEGIN
            PRINT 'generateRandomDataForTable procedure does not exist!'
            RETURN
        END


        SET @startTime = sysdatetime()
        
		-- generate random data for the given number of rows and for the given table
		EXEC generateRandomDataForTable @table, @rows

        SET @endTime = sysdatetime()
        
		INSERT INTO TestRunTables (TestRunID, TableId, StartAt, EndAt) 
			VALUES (@testRunId, (SELECT TableID 
									FROM Tables 
								WHERE Name=@table), 
					@startTime, @endTime)
        
		FETCH tableCursor INTO @table, @rows, @pos
    END

    CLOSE tableCursor
    DEALLOCATE tableCursor


    OPEN viewCursor
    FETCH viewCursor INTO @view

	-- print the results of the view procedure and mark the data into the table
    WHILE @@FETCH_STATUS = 0 
	BEGIN
        SET @command = 'SELECT * FROM ' + @view

        SET @startTime = sysdatetime()

        EXEC (@command)

        SET @endTime = sysdatetime()
        
		-- insert the results into the TestRunViews table (the range of time; the id of the test and of the view)
		INSERT INTO TestRunViews (TestRunID, ViewID, StartAt, EndAt) 
			VALUES (@testRunId, (SELECT ViewID FROM Views WHERE Name = @view), @startTime, @endTime)

        FETCH viewCursor INTO @view
    END

    CLOSE viewCursor
    DEALLOCATE viewCursor

	-- for the current test that was ran, mark the end time of the testing(only the start time was initially marked)
    UPDATE TestRuns
		SET EndAt = sysdatetime()
    WHERE TestRunID = @testRunId
END