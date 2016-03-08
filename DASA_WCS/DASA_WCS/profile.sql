CREATE TABLE [dbo].[Table]
(
	[ProfileID] INT NOT NULL PRIMARY KEY IDENTITY, 
    [ProfileName] NVARCHAR(50) NOT NULL, 
    [Password] NVARCHAR(50) NOT NULL, 
    [Temperature] DECIMAL NULL, 
    [ShowerMode] NVARCHAR(50) NULL, 
    [ShowerPositionX] INT NULL, 
    [ShowerPositionY] INT NULL, 
    [ShowerPositionZ] INT NULL, 
    [AccountId] INT NULL
)
