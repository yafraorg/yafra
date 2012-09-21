#----------------------------------------------------------
#
# copyright:	yafra.org, Switzerland, 2004
#
# package:     travelDB perl modules
#
# argument:		no args
#
# author:		info@yafra.org
#
#----------------------------------------------------------


package tdbdb;

require 5.006;
use Exporter;
use DBI;
#use strict;

@ISA	= qw(DBI Exporter);
@EXPORT = qw(MP_DBinit MP_DBcheckdbi MP_DBcheckroot MP_DBdroproot MP_DBclose
	MP_DBcreate MP_DBloaddump MP_DBusers MP_DBtdbtest);

# declare vars and init if needed
my $debugflag = 0;
my $dbimodule = "";
my $dbbame = "";
my $dbhost = "";
my $os = "";
my	$logfile = "mapo-dbsetupsql.log";
my $dbversion = 3;
use vars qw($dbh);

#----------------------------------------------------------
#
# Subroutine:  MP_DBinit
#
# Parameters:  DebugFlag, DB name, DB hostname, OS type
#
# Description: load global vars for this module
#              MUST execute before any other function !!!
#
#----------------------------------------------------------
sub MP_DBinit
{
	# read function arguments
	my ($mpdebugflag, $mpdbn, $mpdbhost, $mpos) = @_;

	# set global variables
	$debugflag = $mpdebugflag;
	$dbname = $mpdbn;
	$dbhost = $mpdbhost;
	$os = $mpos;
}

#----------------------------------------------------------
#
# Subroutine:  MP_DBcheckdbi
#
# Parameters:  DBD Driver Name
#
# Description: check to see if the needed DBD driver is installed
#
#----------------------------------------------------------
sub MP_DBcheckdbi
{
	# read function arguments
	my ($dbd) = @_;
	if ($dbd eq "mssql")
		{
		$db ="mssql";
		$dbimodule = "dbi:ODBC:driver={SQL Server};";
		}
	elsif ($dbd eq "oracle")
		{
		$db ="oracle";
		$dbimodule = "dbi:Oracle";
		}
	else
		{
		$db ="mysql";
		$dbimodule = "dbi:mysql";
		}

	# chek DBD driver
	db_debug ("  DBI DBD Driver is $dbimodule");

	return(0);
}

#----------------------------------------------------------
#
# Subroutine:  MP_DBclose
#
# Parameters:  -
#
# Description: close/disconnect DB handler
#
#----------------------------------------------------------
sub MP_DBclose
{
	# chek DBD driver
	db_debug ("  closing db handle");

	# disconnect as SYSTEM user from the DB
	$dbh->disconnect;

	return;
}


#----------------------------------------------------------
#
# Subroutine:  MP_DBcheckroot
#
# Parameters:  dba password
#
# Description: check to see if the root schema is present
#
#----------------------------------------------------------
sub MP_DBcheckroot
{
	# read function arguments
	my ($syspw) = @_;

	# declare vars and init if needed
	my $cret = 0;
	use vars qw($sth $field);
	use vars qw(@results $rootname $rootdate);

	# open db
	db_debug ("  check root on db $dbname as database admin");
	if ($db eq "mssql")
		{
		$dbh = DBI->connect("$dbimodule Server=$dbhost; database=$dbname; uid=sa; pwd=$syspw;");
		}
	elsif ($db eq "oracle")
		{
		$dbh = DBI->connect("$dbimodule:host=$dbhost;sid=$dbname","system",$syspw);
		}
	else # mysql
		{
		$dbh = DBI->connect("$dbimodule:$dbname","root",$syspw);
		}
	if ($DBI::err)
		{
		db_debug ("error opening db: $DBI::errstr");
		return (1);
		}

	# check to see if user root exists
	$sth = $dbh->prepare("select mpid, mpuser from root.mp_profil;");
	$sth->execute();
	if ($DBI::err)
		{
		db_debug ("error select root.mp_profil: $DBI::errstr");
		return (1);
		}
	db_debug ("  content of root.mp_profil:");
	while (($mpid, $mpuser) = $sth->fetchrow)
		{
		if ($DBI::err)
			{
			db_debug ("error fetching $DBI::errstr");
			return (1);
			}
		db_debug ("  UserID: $mpid / Name: $mpuser");
		}

	# if root exists give the user a choice
	#while (($rootname, $rootdate) = $sth->fetchrow)
	#	{
	#	if ($DBI::err)
	#		{
	#		db_debug ("error fetching for ROOT entries in dba_users $DBI::errstr");
	#		return (1);
	#		}
	#	# root exists bring back an error for asking
	#	db_debug ("  User $rootname erstellt am $rootdate");
	#	if ($rootname eq "ROOT")
	#		{
	#		$sth->finish;
	#		$dbh->commit;
	#		return(2);
	#		}
	#	}

	# no ROOT schema is here
	db_debug ("  No ROOT schema present, starting to create travelDB now");
	$sth->finish;
	$dbh->commit;
	# disconnect as SYSTEM user from the DB
	$dbh->disconnect;
	return(2);
}


#----------------------------------------------------------
#
# Subroutine:  MP_DBdroproot
#
# Parameters:  sys pwd, script
#
# Description: drop root schema
#
#----------------------------------------------------------
sub MP_DBdroproot
{
	# read function arguments
	my ($syspw, $script) = @_;

	# declare vars and init if needed
	my $cret = 0;
	my $dbcmd;
	
	# creat empty database
	db_debug ("  drop database and root and demo users by scripts");
	if ($db eq "mssql")
		{
		$dbcmd = sprintf ("$script $syspw >> $logfile");
		}
	elsif ($db eq "mysql")
		{
		}
	else
		{
		$dbcmd = sprintf ("$script $dbname $syspw >> $logfile");
		}
	db_debug (" - starting command $dbcmd");
	$cret = system($dbcmd);

	return (0);
}


#----------------------------------------------------------
#
# Subroutine:  MP_DBcreate
#
# Parameters:  system pwd, root pwd, script filename
#
# Description: create empty database
#
#----------------------------------------------------------
sub MP_DBcreate
{
	# read function arguments
	my ($syspw, $rootpw, $script) = @_;

	# declare vars and init if needed
	my $cret = 0;
	my $dbcmd;
	
	# pre installation - prepare db with basics for loading dump

	# creat empty database
	db_debug ("  create empty database by scripts");
	if ($db eq "mssql")
		{
		$dbcmd = sprintf ("$script $syspw >> $logfile");
		}
	elsif ($db eq "mysql")
		{
		}
	else
		{
		$dbcmd = sprintf ("$script $dbname $syspw >> $logfile");
		}
	db_debug (" - starting command $dbcmd");
	$cret = system($dbcmd);

	# post installation

	return (0);
}

#----------------------------------------------------------
#
# Subroutine:  MP_DBloaddump
#
# Parameters:  system pwd, root pwd, script filename
#
# Description: create database by loading a dump
#
#----------------------------------------------------------
sub MP_DBloaddump
{
	# read function arguments
	my ($syspw, $rootpw, $script) = @_;

	# declare vars and init if needed
	my $cret = 0;
	my $dbcmd;
	
	# pre installation - prepare db with basics for loading dump

	# creat empty database
	db_debug ("  create database by importing a dumpfile");
	if ($db eq "mssql")
		{
		$dbcmd = sprintf ("$script $syspw >> $logfile");
		}
	elsif ($db eq "mysql")
		{
		}
	else
		{
		$dbcmd = sprintf ("$script $dbname $syspw >> $logfile");
		}
	db_debug (" - starting command $dbcmd");
	system($dbcmd);

	# post installation
	#if ($db eq "oracle")
	#	{
		#
		# WORKAROUND for bug in dump for TO Classic for User EU
		# delete this if the bug is corrected in a next dump
		#
	#	$dbh->do("update root.mp_profil set a_zeit = 0, e_zeit = 0 where mpuser = 'eu'");
	#	}

	db_debug ("  loading DONE");
	return (0);
}

#----------------------------------------------------------
#
# Subroutine:  MP_DBusers
#
# Parameters:  system pwd, root pwd, user name, user pwd, user level
#
# Description: set root pwd, create user
#
#----------------------------------------------------------
sub MP_DBusers
{
	# read function arguments
	my ($mpsyspw, $mprootpw, $mpusr, $mpusrpw, $mplevel) = @_;

	# declare vars and init if needed
	my $cret = 0;
	my $seclevel = 1;
	use vars qw($sth);
	use vars qw($user);

	db_debug ("  create users for travelDB now");

	# open db
	db_debug ("  check root on db $dbname as database admin");
	if ($db eq "mssql")
		{
		$dbh = DBI->connect("$dbimodule Server=$dbhost; database=$dbname; uid=sa; pwd=$syspw;");
		}
	elsif ($db eq "oracle")
		{
		$dbh = DBI->connect("$dbimodule:host=$dbhost;sid=$dbname","system",$syspw);
		}
	else # mysql
		{
		$dbh = DBI->connect("$dbimodule:$dbname","root",$syspw);
		}
	if ($DBI::err)
		{
		db_debug ("error opening db: $DBI::errstr");
		return (1);
		}

	if ($db eq "mssql")
		{
		}
	elsif ($db eq "mysql")
		{
		}
	else
		{
		# create user
		$dbh->do("create user $mpusr identified by $mpusrpw profile mapoprof");
		if ($DBI::err)
			{
			db_debug("error inserting new mapo user: $DBI::errstr");
			return(1);
			}
		$cret = $dbh->do("grant $mplevel to $mpusr");
		db_debug ("  granted $mplevel with code $cret");
		if ($DBI::err)
			{
			db_debug("error inserting new mapo user: $DBI::errstr");
			return(1);
			}
		$dbh->commit;

		# insert user into mp_profil
		# set sec level according the mplevel
		# check to see if user already exists
		$cret = $dbh->do("select mpuser from root.mp_profil where mpuser = '$mpusr'");
		if ($DBI::err)
			{
			db_debug ("error prep stmt: $DBI::errstr");
			return (1);
			}
		if ($cret eq "1")
			{
			db_debug ("  User $mpusr will be droped now");
			$cret = $dbh->do("delete from root.mp_profil where mpuser = '$mpusr'");
			if ($DBI::err)
				{
				db_debug ("error prep stmt: $DBI::errstr");
				return (1);
				}
			}

		# insert mp_profil: mpid, mpuser, bchst, seclevel, s_id, land, dltt, dlt, kat, dlat, dlnt, sai, prg, azeit, ezeit, range
		$cret = $dbh->do("insert into root.mp_profil values (mp_profil_seq.nextval,'$mpusr',3,$seclevel,25,756,-1,-1,-1,-1,-1,-1,-1,0,0,0)");
		db_debug ("  new user inserted as often as: $cret");
		if ($DBI::err)
			{
			db_debug("error inserting new mapo user: $DBI::errstr");
			return(1);
			}
		$dbh->commit;
		}


	# insert mp_profil: mpid, mpuser, bchst, seclevel, s_id, land, dltt, dlt, kat, dlat, dlnt, sai, prg, azeit, ezeit, range
	$cret = $dbh->do("insert into root.tdb_version values ($dbversion, '01/01/2005')");
	db_debug ("  db version $dbversion set with return code: $cret");
	if ($DBI::err)
		{
		db_debug("error inserting new db version: $DBI::errstr");
		return(1);
		}
	$dbh->commit;

	# disconnect as SYSTEM user from the DB
	$dbh->disconnect;

	return(0);
}

#----------------------------------------------------------
#
# Subroutine:  MP_DBtdbtest
#
# Parameters:  root pwd
#
# Description: check to see if the db is ready
#
#----------------------------------------------------------
sub MP_DBtdbtest
{
	# read function arguments
	my ($mprootpw) = @_;

	# declare vars and init if needed
	use vars qw($sth);
	use vars qw($bid $ref);

	db_debug("  start the test");

	# open db
	db_debug ("  check root on db $dbname as database admin");
	if ($db eq "mssql")
		{
		$dbh = DBI->connect("$dbimodule Server=$dbhost; database=$dbname; uid=root; pwd=$mprootpw;");
		}
	elsif ($db eq "oracle")
		{
		$dbh = DBI->connect("$dbimodule:host=$dbhost;sid=$dbname","root",$mprootpw);
		}
	else # mysql
		{
		$dbh = DBI->connect("$dbimodule:$dbname","root",$mprootpw);
		}
	if ($DBI::err)
		{
		db_debug ("error opening db: $DBI::errstr");
		return (1);
		}

	# check buchung table
	$sth = $dbh->prepare("select bid, ref from root.buchung where bid > -1");
	if ($DBI::err)
		{
		db_debug ("error prep stmt: $DBI::errstr");
		return (1);
		}
	$sth->execute();
	if ($DBI::err)
		{
		db_debug ("error prep stmt: $DBI::errstr");
		return (1);
		}

	# show all buchungen
	db_debug ("  content of root.buchung (only bid and ref fields):");
	while (($bid, $ref) = $sth->fetchrow)
		{
		if ($DBI::err)
			{
			db_debug ("error fetching $DBI::errstr");
			return (1);
			}
		db_debug ("  Buchungs ID: $bid with Referenz: $ref");
		}
	$sth->finish;
	$dbh->commit;

	# disconnect as ROOT user from the DB
	$dbh->disconnect;

	return(0);
}

#----------------------------------------------------------
#
# INTERNAL functions
#
#----------------------------------------------------------

sub db_debug
{
	# read function arguments
	my ($message) = @_;

	if ($debugflag)
		{
		print "debug: $message\n";
		}
}

1;
