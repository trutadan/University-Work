-- procedure to generate a random positive tinyint
GO 
	CREATE OR ALTER PROCEDURE generateRandomPositiveTinyint @tinyintValue TINYINT OUTPUT AS
BEGIN
	SET @tinyintValue = floor(rand() * 256)
END


-- procedure to generate a random positive smallint
GO 
	CREATE OR ALTER PROCEDURE generateRandomPositiveSmallint @smallintValue SMALLINT OUTPUT AS
BEGIN
	SET @smallintValue = floor(rand() * 32768)
END


-- procedure to generate a random positive int
GO 
	CREATE OR ALTER PROCEDURE generateRandomPositiveInt @intValue INT OUTPUT AS
BEGIN
	SET @intValue = floor(rand() * 2147483648)
END


--procedure to generate a random string with a limited length
GO 
	CREATE OR ALTER PROCEDURE generateRandomString @stringValue VARCHAR(10) OUTPUT AS
BEGIN
	DECLARE @length INT
	DECLARE @possibleCharsPool VARCHAR(55)
	DECLARE @charPoolLength INT

	
	SET @stringValue = ''

	-- maximum length of the string must be 9
	SET @length = FLOOR(RAND() * 10)
	SET @possibleCharsPool = 'abcdefghijkmnopqrstuvwxyzABCDEFGHIJKLMNPQRSTUVWXYZ .-_'
	SET @charPoolLength = LEN(@possibleCharsPool)
	
	WHILE @length > 0
		BEGIN
			SET @stringValue = @stringValue + SUBSTRING(@possibleCharsPool, CONVERT(INT, RAND() * @charPoolLength) + 1, 1)
			SET @length = @length - 1
		END
END


-- procedure to generate a random date
GO 
	CREATE OR ALTER PROCEDURE generateRandomDate @dateValue DATE OUTPUT AS
BEGIN
	SET @dateValue = dateAdd(day, abs(checksum(newID()) % 3650), '2000-01-01')
END


-- procedure to generate a random time
GO 
	CREATE OR ALTER PROCEDURE generateRandomTime @timeValue TIME OUTPUT AS
BEGIN
	SET @timeValue = dateAdd(s, ABS(CHECKSUM(NewId()) % 43201), CAST('08:00:00' AS Time))
END


-- procedure to generate a random datetime
GO 
	CREATE OR ALTER PROCEDURE generateRandomDatetime @datetimeValue DATETIME OUTPUT AS
BEGIN
	SET @datetimeValue = dateAdd(day, ROUND(DATEDIFF(day, '2000-01-01', '2022-12-12') * RAND(CHECKSUM(NEWID())), 5),DATEADD(second, abs(CHECKSUM(NEWID())) % 86400, '2000-01-01'))
END


-- generate random data for a table
GO
	CREATE OR ALTER PROCEDURE generateRandomDataForTable @tableName VARCHAR(50), @numberOfRows INT AS
BEGIN
	-- create a cursor to iterate through the names of the column and their types
	DECLARE dataCursor SCROLL CURSOR FOR
		SELECT COLUMN_NAME, DATA_TYPE
			FROM INFORMATION_SCHEMA.COLUMNS
		WHERE TABLE_NAME = @tableName

	-- query for the insert in tables
	DECLARE @insertQuery VARCHAR(MAX)

	DECLARE @columnName VARCHAR(200)
	DECLARE @dataType VARCHAR(10)
	DECLARE @intValue INT
	DECLARE @smallintValue SMALLINT
	DECLARE @tinyintValue TINYINT
	DECLARE @stringValue VARCHAR(50)
	DECLARE @dateValue DATE
	DECLARE @timeValue TIME
	DECLARE @datetimeValue DATETIME
	DECLARE @checkIfPKQuery NVARCHAR(2000)
	DECLARE @hasPK INT

	OPEN dataCursor

	-- generate data for the number of times mentioned in numberOfRows
	WHILE @numberOfRows > 0
	BEGIN
		SET @hasPK = 0
		SET @insertQuery = 'INSERT INTO ' + @tableName + ' VALUES('
		SET @checkIfPKQuery = N'SELECT @outputPK = COUNT(*) FROM ' + @tableName + ' WHERE '

		FETCH FIRST FROM dataCursor INTO @columnName, @dataType

		WHILE @@FETCH_STATUS = 0
		BEGIN
			IF COLUMNPROPERTY(OBJECT_ID(@tableName), @columnName, 'IsIdentity') = 0
			BEGIN
				-- check if the current column has a foreign key property and if it has, take its values from the referenced table
				IF EXISTS(
					SELECT *
						FROM INFORMATION_SCHEMA.CONSTRAINT_COLUMN_USAGE C
					WHERE C.CONSTRAINT_NAME like 'FK%' AND @columnName = C.COLUMN_NAME AND @tableName = C.TABLE_NAME)
					
					BEGIN
						-- get the name of the referenced table and the name of the referenced column
						DECLARE @referencedTable VARCHAR(50)
						DECLARE @referencedColumn VARCHAR(50)
						DECLARE @result TABLE([tableName] VARCHAR(50), [columnName] VARCHAR(50))

						INSERT INTO @result 
							SELECT OBJECT_NAME (f.referenced_object_id) AS referenced_table_name,
									COL_NAME(fc.referenced_object_id, fc.referenced_column_id) AS referenced_column_name
										FROM sys.foreign_keys AS f
										INNER JOIN sys.foreign_key_columns AS fc 
										ON f.object_id = fc.constraint_object_id
								WHERE fc.parent_object_id = OBJECT_ID(@tableName) AND COL_NAME(fc.parent_object_id, fc.parent_column_id) = @columnName

						SET @referencedTable = (SELECT TOP 1 [tableName] FROM @result)
						SET @referencedColumn = (SELECT TOP 1 [columnName] FROM @result)
						
						-- empty the table, otherwise it will always have at the top the first table and column found
						DELETE FROM @result

						-- get a random value from the referenced table (we considered the only type possible for keys to be int)
						DECLARE @getRandomFK NVARCHAR(1000)
						-- NEWID() argument sorts the query randomly
						SET @getRandomFK = N'SELECT TOP 1 @intValue = [' + @referencedColumn + '] FROM ' + @referencedTable + ' ORDER BY NEWID()'
						-- sp_executesql is used because the statement has been built dynamically
						EXEC sp_executesql @getRandomFK, N'@intValue INT OUTPUT', @intValue OUTPUT
						SET @insertQuery = @insertQuery + CAST(@intValue AS NVARCHAR(30)) + ','

					END

				ELSE
					-- not a foreign key, does not depend on another table
					BEGIN
						IF @dataType = 'int'
							BEGIN
								-- generate a random positive int
								EXEC generateRandomPositiveInt @intValue OUTPUT
								SET @insertQuery = @insertQuery + CAST (@intValue AS NVARCHAR(30)) + ','
							END

						ELSE
							IF @dataType = 'smallint'
								BEGIN
									-- generate a random positive smallint
									EXEC generateRandomPositiveSmallint @smallintValue OUTPUT
									SET @insertQuery = @insertQuery + '''' + CAST (@smallintValue AS NVARCHAR(30)) + '''' + ','
								END

						ELSE
							IF @dataType = 'tinyint'
								BEGIN
									-- generate a random positive tinyint
									EXEC generateRandomPositiveTinyint @tinyintValue OUTPUT
									SET @insertQuery = @insertQuery + '''' + CAST (@tinyintValue AS NVARCHAR(30)) + '''' + ','
								END

						ELSE
							IF @dataType = 'varchar'
								BEGIN
									-- generate a random string
									EXEC generateRandomString @stringValue OUTPUT
									SET @insertQuery = @insertQuery + '''' + @stringValue + '''' + ','
								END

						ELSE
							IF @dataType = 'date'
								BEGIN
									-- generate a random date
									EXEC generateRandomDate @dateValue OUTPUT
									SET @insertQuery = @insertQuery + '''' + CAST(@dateValue AS NVARCHAR(30)) + '''' + ','
								END
						
						ELSE
							IF @dataType = 'time'
								BEGIN
									-- generate a random time
									EXEC generateRandomTime @timeValue OUTPUT
									SET @insertQuery = @insertQuery + '''' + CAST(@timeValue AS NVARCHAR(30)) + '''' + ','
								END

						ELSE
							IF @dataType = 'datetime'
								BEGIN
									-- generate a random datetime
									EXEC generateRandomDatetime @datetimeValue OUTPUT
									SET @insertQuery = @insertQuery + '''' + CAST(@datetimeValue AS NVARCHAR(30)) + '''' + ','
								END

						ELSE
							BEGIN
								SET @insertQuery = @insertQuery + 'NULL' + ','
							END
					END

				-- if the column has a primary key, create a query and check its validity
				-- this will also check for multicolumn primary keys
				IF EXISTS(SELECT *
								FROM INFORMATION_SCHEMA.CONSTRAINT_COLUMN_USAGE
							WHERE TABLE_NAME = @tableName AND COLUMN_NAME = @columnName AND CONSTRAINT_NAME LIKE 'PK%')
					

					BEGIN
						SET @hasPK = 1

						-- we considered the only type possible for keys to be int
						SET @checkIfPKQuery = @checkIfPKQuery + @columnName + '=' + CAST(@intValue AS VARCHAR(10)) + ' AND '
					END

			END

			FETCH NEXT FROM dataCursor INTO @columnName, @dataType
		END

		-- insert only if the primary key is valid
		IF @hasPK = 1
			BEGIN
				SET @checkIfPKQuery = LEFT(@checkIfPKQuery, LEN(@checkIfPKQuery) - 4)
				DECLARE @outputPK INT
				EXEC sp_executesql @checkIfPKQuery, N'@outputPK INT OUTPUT', @outputPK OUTPUT

				IF @outputPK = NULL OR @outputPK = 0
					BEGIN
						-- delete the comma from the end and add the closing parenthese instead
						SET @insertQuery = LEFT(@insertQuery, LEN(@insertQuery) - 1) + ')'
						EXEC (@insertQuery)
					END
			END

		ELSE
			-- in this case column is not primary key
			BEGIN 
				-- delete the comma from the end and add the closing parenthese instead
				SET @insertQuery = LEFT(@insertQuery, LEN(@insertQuery) - 1) + ')'
				EXEC (@insertQuery)
			END


		SET @numberOfRows = @numberOfRows - 1
	END

	CLOSE dataCursor
	DEALLOCATE dataCursor
END