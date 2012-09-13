/* drop any old database first */
DROP DATABASE [traveldb]
GO

/* create database */
CREATE DATABASE [traveldb]
GO

exec sp_dboption N'traveldb', N'autoclose', N'true'
exec sp_dboption N'traveldb', N'bulkcopy', N'false'
exec sp_dboption N'traveldb', N'trunc. log', N'true'
exec sp_dboption N'traveldb', N'torn page detection', N'true'
exec sp_dboption N'traveldb', N'read only', N'false'
exec sp_dboption N'traveldb', N'dbo use', N'false'
exec sp_dboption N'traveldb', N'single', N'false'
exec sp_dboption N'traveldb', N'autoshrink', N'true'
exec sp_dboption N'traveldb', N'ANSI null default', N'false'
exec sp_dboption N'traveldb', N'recursive triggers', N'false'
exec sp_dboption N'traveldb', N'ANSI nulls', N'false'
exec sp_dboption N'traveldb', N'concat null yields null', N'false'
exec sp_dboption N'traveldb', N'cursor close on commit', N'false'
exec sp_dboption N'traveldb', N'default to local cursor', N'false'
exec sp_dboption N'traveldb', N'quoted identifier', N'false'
exec sp_dboption N'traveldb', N'ANSI warnings', N'false'
exec sp_dboption N'traveldb', N'auto create statistics', N'true'
exec sp_dboption N'traveldb', N'auto update statistics', N'true'
GO
