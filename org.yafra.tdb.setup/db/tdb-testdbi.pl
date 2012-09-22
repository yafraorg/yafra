#!/usr/bin/perl -w
#-------------------------------------------------------------------------------
#  Copyright 2002 yafra.org
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#-------------------------------------------------------------------------------
#
# Purpose:      test database perl script
#
# argument:		no args
#
# tag:			$Name:  $
# revision:		$Revision: 1.2 $
#-------------------------------------------------------------------------------

require 5.006;

#use strict;
#use Exporter;
use DBI;

# application variables
my $mp_ver = "";

my $dbddriver = "mssql";
my $dbname = "traveldb";
my $dbhost = "localhost";
my $tdbowner ="tdbadmin";

#my $dbddriver = "mysql";
#my $dbname = "traveldb";
#my $dbhost = "localhost";

#my $dbddriver = "oracle";
#my $dbname = "mydb";
#my $dbhost = "localhost";

my $curos = "win32"; # values win32, linux
my $debugflag = 1;
my $dbimodule = "";
my $dbiconn = "";
use vars qw($dbh);
use vars qw($sth $field);
use vars qw(@results $rootname $rootdate);

#
# START
#
$num_args = $#ARGV + 1;
if ($num_args != 3) {
  print "\nUsage: 1:dbname, 2:servername, 3:dbtype\n";
  exit;
}
$mp_ver =  $ENV{'YAFRAVER'}; 
# (2) we got two command line args, so assume they are the
# first name and last name
$dbname=$ARGV[0];
$dbhost=$ARGV[1];
$dbddriver=$ARGV[2];
dbdebug("travelDB database DBI test version $mp_ver");
dbdebug("DBD driver:    $dbddriver");
dbdebug("DB name:       $dbname");
# check OS
if ($^O eq 'MSWin32')
	{
	$curos = "win32";
	}
else
	{
	$curos = "linux";
	}
dbdebug("OS type: $curos");

# init travelDB perl module
dbdebug("Starting now to connect by DBI DBD !");
if ($dbddriver eq "mssql")
	{
	$dbimodule = "dbi:ODBC:driver={SQL Server};";
	}
elsif ($dbddriver eq "oracle")
	{
	$dbimodule = "dbi:Oracle";
	}
else
	{
	$dbimodule = "dbi:mysql";
	}
dbdebug ("  DBI DBD Driver is $dbimodule");

# open db
dbdebug ("  check root on db $dbname as database admin");
if ($dbddriver eq "mssql")
	{
	$dbiconn = "$dbimodule Server=$dbhost; database=$dbname; uid=root; pwd=root;";
	$dbh = DBI->connect($dbiconn);
	}
elsif ($dbddriver eq "oracle")
	{
	$dbiconn = "$dbimodule:host=$dbhost;sid=$dbname";
	$dbh = DBI->connect($dbiconn, $tdbowner, "yafra");
	}
else # mysql
	{
	$dbiconn = "$dbimodule:database=$dbname;host=$dbhost";
	$dbh = DBI->connect($dbiconn, $tdbowner, "yafra");
	}
dbdebug ("  connecting with $dbiconn");
if ($DBI::err)
	{
	dbdebug ("error opening db: $DBI::errstr");
	exit(1);
	}

# check to see if user root exists
$sth = $dbh->prepare("select mpid, mpuser from $tdbowner.mp_profil");
$sth->execute();
if ($DBI::err)
	{
	dbdebug ("error select $tdbowner.mp_profil: $DBI::errstr");
	exit(1);
	}
dbdebug ("  content of $tdbowner.mp_profil:");
while (($mpid, $mpuser) = $sth->fetchrow)
	{
	if ($DBI::err)
		{
		dbdebug ("error fetching $DBI::errstr");
		exit(1);
		}
	dbdebug ("  UserID: $mpid / Name: $mpuser");
	}

# if root exists give the user a choice
#while (($rootname, $rootdate) = $sth->fetchrow)
#	{
#	if ($DBI::err)
#		{
#		dbdebug ("error fetching for ROOT entries in dba_users $DBI::errstr");
#		exit(1);
#		}
#	# root exists bring back an error for asking
#	dbdebug ("  User $rootname erstellt am $rootdate");
#	if ($rootname eq "ROOT")
#		{
#		$sth->finish;
#		$dbh->commit;
#		exit(2);
#		}
#	}

# closure
dbdebug ("  close travelDB now and exit");
$sth->finish;
#if ($dbddriver eq "mysql")
#	{
#	$dbh->commit;
#	}
$dbh->disconnect;
exit(0);

#----------------------------------------------------------
#
# INTERNAL functions
#
#----------------------------------------------------------

sub dbdebug
{
	# read function arguments
	my ($message) = @_;

	if ($debugflag)
		{
		print "debug: $message\n";
		}
}
