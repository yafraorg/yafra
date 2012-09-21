#!/usr/bin/perl -w
#-------------------------------------------------------------------------------
# copyright:	yafra.org, Switzerland, 2004
#
# function:		travelDB setup GUI
#					Windows DBD-ODBC, DBD-Oracle and DBD-MySQL
#					Linux DBD-Oracle and DBD-MySQL
#					create db by scripts or by dump
#					1) check db if root schema already present -> drop if present
#					2) create root schema sceleton (no tables or so)
#					3) create db
#					4) test db
#
# argument:		no args
#
# author:		info@yafra.org
#
# tag:			$Name:  $
# revision:		$Revision: 2.2 $
# cvs info:    $Id: mapo-dbsetup.pl,v 2.2 2008-07-27 17:01:47 mwn Exp $
#-------------------------------------------------------------------------------

require 5.006;

#use strict;
use Tk;
use Tk::Dialog;
use Tk::DialogBox;
use Tk::JComboBox;
use Tk::NoteBook;
use Tk::LabEntry;
use Tk::ProgressBar;
use Tk::Scale;
use Cwd;
use File::Basename;

use tdbdb;

# application variables
my $mp_ver = '$Revision: 2.2 $';
my $mp_debugflag = 0;

# global variables
my $mp_dbflag = "NULL";    # values mssql, mysql and ora
my $mp_dbname = "NULL";    # value: name of database (oracle sid)
my $mp_dbhost = "NULL";    # value: name of host where db is running on
my $mp_dbsyspwd = "NULL";  # dba user password (mssql SA, ora SYSTEM, mysql ???)
my $mp_dataflag = "NULL";  # values dump and new
my $mp_user ="NULL";       # name of tdb user
my $mp_userlevel = "dba";  # role of tdb user
my $mp_userpw = "NULL";    # password of tdb user
my $mp_rootpw = "NULL";    # password of ROOT
my $mp_progress = 0;
my $mp_status = "OK";      # values OK, ERROR, DONE, CANCEL
my $mp_dbdir = "db";
my $mp_os = "win32"; # values win32, linux
my $mp_dbdelfile = "NULL";
my $mp_dbgenfile = "NULL";
my $mp_dbdumpfile = "NULL";
my $mp_genfile = "NULL";

# TK widget variables
use vars qw($TKtop);
use vars qw($TKstat_frm);
use vars qw($TKbody_frm);
use vars qw($TKmenu_frm);
use vars qw($TKprog_bar);
use vars qw($TKstat_lab);
use vars qw($TKprogbar);
use vars qw($TKdb);
use vars qw($TKscripts);
use vars qw($TKuser);
use vars qw($TKdbinit);
use vars qw($TKhelp);
use vars qw($TKabout);
use vars qw($TKprint);
use vars qw($TKcolor);
use vars qw($TKdropdialog);
use vars qw($TKstartbutton);

# init output
#$ARGV = @ARGV;
#if ($ARGV == 0)
#	{
#	print "\nplease specify the db files directory as argument\n";
#	exit;
#	$ARGV[0] = "oracle";
#	}
#$mp_dbdir = $ARGV[0];
print "\n\ntravelDB database setup wizard\n\n";
#print "DB files directory is: $mp_dbdir\n";
#chdir($mp_dbdir);

# check OS
if ($^O eq 'MSWin32')
	{
	$mp_os = "win32";
	}
else
	{
	$mp_os = "linux";
	}
#print "OS type: $mp_os\n";

# create main windows TKtopLEVEL
$TKtop = MainWindow->new;
$TKtop->title("travelDB database setup");
$TKcolor = "green";
#$TKcolor = $TKtop->cget(-bg);

# create menu on TKtopLEVEL
$TKmenu_bar = $TKtop->Frame(-relief => 'ridge', -bd => 2);
$TKmenu_bar->pack(-side => 'top', -anchor => 'n', -expand => 1, -fill => 'x');

# menu entry FILE
$TKfile_mb = $TKmenu_bar->Menubutton(-text => 'File');
$TKfile_mb->pack(-side => 'left');
$TKfile_mb->command(-label => 'Print values', -underline => 0,
	-command => \&MP_DATAprint);
$TKfile_mb->command(-label => 'Exit', -underline => 0,
	-command => sub {exit});
# menu entry travelDB
$TKtdb_mb = $TKmenu_bar->Menubutton(-text => 'Setup');
$TKtdb_mb->pack(-side => 'left');
$TKtdb_mb->command(-label => 'DB typ', -underline => 0,
	-command => \&MP_DBchoose);
$TKtdb_mb->command(-label => 'DB scripts', -underline => 0,
	-command => \&MP_DBscripts);
$TKtdb_mb->command(-label => 'DB settings', -underline => 0,
	-command => \&MP_INITdo);
$TKtdb_mb->command(-label => 'Users', -underline => 0,
	-command => \&MP_USERconf);
# menu entry HELP
$TKhelp_mb = $TKmenu_bar->Menubutton(-text => 'Help');
$TKhelp_mb->pack(-side => 'right');
$TKhelp_mb->command(-label => 'Howto use', -underline => 0,
	-command => \&MP_HELPshow);
$TKhelp_mb->checkbutton(-label  => 'Debugging',
	-variable => \$mp_debugflag);
$TKhelp_mb->command(-label => 'About', -underline => 0,
	-command => \&MP_ABOUTshow);

# BODY
$TKbody_frm = $TKtop->Frame(-relief => 'flat', -bd => 0);
$TKbody_frm->pack(-side => 'top', -anchor => 'nw', -expand => 1, -fill => 'x');
$TKbody_frm->Label(-text => "travelDB database setup wizard")->pack(-side => 'top');
$TKbody_frm->Label(-text => "Database setup wizard.\nPlease choose from the menu")->pack(-side => 'top');

# STATUS
$TKstat_frm = $TKtop->Frame(-relief => 'ridge', -bd => 2, -height => 10);
$TKstat_frm->pack(-side => 'bottom', -anchor => 'sw', -expand => 0, -fill => 'both');

$TKstat_frm->Label(-text => "Status: ")->pack(-side => 'left', -anchor => 'w');
$TKstat_lab = $TKstat_frm->Label(-textvariable => \$mp_status)->pack(-side => 'left', -anchor => 'w');
$TKprog_bar = $TKstat_frm->ProgressBar(-borderwidth => 0, -relief => 'sunken', -width => 15,
	-padx => 0, -pady => 0, -variable => \$mp_progress,
	-colors => [0 => 'green', 50 => 'yellow' , 80 => 'red'],);
$TKprog_bar->pack(-padx => 5, -pady => 2, -side => 'bottom', -anchor => 'sw', -fill => 'both', -expand => 1);

#$TKtop->Scale(-from => 0, -to => 100, -variable => \$status_var)->pack;
#my $dl  = $TKtop->Scrolled('DirTree')->pack(-expand => 1 , -fill => 'both');

MainLoop;


#
# choose Database Vendor
#
sub MP_DBchoose
{
	if (not defined $TKdb)
		{
		$TKdb = $TKtop->DialogBox(-title => "Choose a DB Vendor:", -buttons => ["OK", "Cancel"]);
		$TKdb->Radiobutton(-text => "Oracle", -value => "oracle", -variable => \$mp_dbflag)->pack(-side => 'left');
		$TKdb->Radiobutton(-text => "MS SQL Server", -value => "mssql", -variable => \$mp_dbflag)->pack(-side => 'left');
		$TKdb->Radiobutton(-text => "MySQL", -value => "mysql", -variable => \$mp_dbflag)->pack(-side => 'left');
		}
    my $result = $TKdb->Show;
    if ($result =~ /OK/)
    	{
		if ($mp_dbflag eq "NULL")
			{
			$mp_status = "ERROR";
			$TKstat_lab->configure(-bg => "red");
			}
		else
			{
			$mp_progress = 10;
			$mp_status = "OK";
			$TKstat_lab->configure(-bg => $TKcolor);
			}
		}
	else
		{
		$mp_status = "CANCEL";
		$TKstat_lab->configure(-bg => "yellow");
		}
}

#
# select batch and sql scripts
#
sub MP_DBscripts
{
	if ($mp_os eq 'win32')
		{
		$mp_genfile = "generate.bat";
		}
	else
		{
		$mp_genfile = "generate.sh";
		}

	if (not defined $TKscripts)
		{
		$TKscripts = $TKtop->DialogBox(-title => "Choose scripts (deletion and generate OR dump):", -buttons => ["OK", "Cancel"]);
		$TKscripts->Button(-text => "deletion script", -command => [ \&MP_DBdelfile ])->pack(-side => 'left');
		$TKscripts->Button(-text => "generate script", -command => [ \&MP_DBgenfile ])->pack(-side => 'left');
		$TKscripts->Button(-text => "dump script", -command => [ \&MP_DBdumpfile ])->pack(-side => 'left');
		}
    my $result = $TKscripts->Show;
    if ($result =~ /OK/)
    	{
		if (($mp_dbdelfile ne "NULL") && (($mp_dbgenfile ne "NULL") || ($mp_dbdumpfile ne "NULL")))
			{
			$mp_progress = 20;
			$mp_status = "OK";
			$TKstat_lab->configure(-bg => $TKcolor);
			}
		else
			{
			$mp_status = "ERROR";
			$TKstat_lab->configure(-bg => "red");
			}
		}
	else
		{
		$mp_status = "CANCEL";
		$TKstat_lab->configure(-bg => "yellow");
		}
}
sub MP_DBdelfile
{

$mp_dbdelfile = $TKtop->getOpenFile(-defaultextension => ".*",
		-initialdir => Cwd::cwd(), -initialfile => $mp_genfile, -title => "travelDB deletion script");
}
sub MP_DBgenfile
{
$mp_dbgenfile = $TKtop->getOpenFile(-defaultextension => ".*",
		-initialdir => Cwd::cwd(), -initialfile => $mp_genfile, -title => "travelDB generate batch");
}
sub MP_DBdumpfile
{
$mp_dbdumpfile = $TKtop->getOpenFile(-defaultextension => ".*",
		-initialdir => Cwd::cwd(), -initialfile => $mp_genfile, -title => "travelDB generate with dump batch");
}

#
# DB Init
#
sub MP_INITdo
{
	if (not defined $TKdbinit)
		{
		$TKdbinit = $TKtop->DialogBox(-title => "Database Init",
			-buttons => ["OK", "Cancel"]);
		my $TKnb_init = $TKdbinit->add('NoteBook', -ipadx => 6, -ipady => 6);
		my $dbconn_p = $TKnb_init->add("dbconn", -label => "DB connection settings", -underline => 0);
		my $dbdata_p = $TKnb_init->add("dbdata", -label => "travelDB data", -underline => 0);

		$mp_dbname = "";
		$mp_dbsyspwd = "";
		$mp_dbhost = "";
		$dbconn_p->LabEntry(-label => "DB name:          ", -bg => 'white',
	     -labelPack => [-side => "left", -anchor => "w"],
	     -width => 20,
	     -textvariable => \$mp_dbname)->pack(-side => "top", -anchor => "nw");
		$dbconn_p->LabEntry(-label => "DB hostname:          ", -bg => 'white',
	     -labelPack => [-side => "left", -anchor => "w"],
	     -width => 20,
	     -textvariable => \$mp_dbhost)->pack(-side => "top", -anchor => "nw");
		$dbconn_p->LabEntry(-label => "SYSTEM user password:", -bg => 'white', -show => '*',
	     -labelPack => [-side => "left", -anchor => "w"],
	     -width => 15,
	     -textvariable => \$mp_dbsyspwd)->pack(-side => "top", -anchor => "nw");

		$dbdata_p->Radiobutton(-text => "fresh setup (without dump)", -value => "new",
			-variable => \$mp_dataflag)->pack(-side => 'left');
		$dbdata_p->Radiobutton(-text => "DB Dump import (demo)", -value => "dump",
			-variable => \$mp_dataflag)->pack(-side => 'left');

		$TKnb_init->pack(-expand => "yes", -fill => "both", -padx => 5, -pady => 5, -side => "top");
	
		}
	my $result = $TKdbinit->Show;
	if ($result =~ /OK/)
		{
		if ($mp_dbflag eq "" || $mp_dataflag eq "NULL")
			{
			$mp_status = "ERROR";
			$TKstat_lab->configure(-bg => "red");
			}
		else
			{
			$mp_progress = 30;
			$mp_status = "OK";
			$TKstat_lab->configure(-bg => $TKcolor);
			}
		}
	else
		{
		$mp_status = "CANCEL";
		$TKstat_lab->configure(-bg => "yellow");
		}
}

#
# configure MARCO POLO Users
#
sub MP_USERconf
{
	if (not defined $TKuser)
		{
		$TKuser = $TKtop->DialogBox(-title => "travelDB user configurations:", -buttons => ["OK", "Cancel"]);
		my $TKnb_user = $TKuser->add('NoteBook', -ipadx => 6, -ipady => 6);
		my $a_p = $TKnb_user->add("dbconn", -label => "ROOT User Info", -underline => 0);
		my $b_p = $TKnb_user->add("dbdata", -label => "Other User Info", -underline => 0);
		$mp_rootpw = "";
		$a_p->LabEntry(-label => "ROOT password:          ", -bg => 'white', -show => '*',
	     -labelPack => [-side => "left", -anchor => "w"], -width => 20,
	     -textvariable => \$mp_rootpw)->pack(-side => "top", -anchor => "nw");

		$mp_user = "";
		$mp_userpw = "";
		$b_p->LabEntry(-label => "User Name:          ", -bg => 'white',
			-labelPack => [-side => "left", -anchor => "w"], -width => 20,
			-textvariable => \$mp_user)->pack(-side => "left", -anchor => "nw");
		$b_p->LabEntry(-label => "User Passwort:      ", -bg => 'white', -show => '*',
			-labelPack => [-side => "left", -anchor => "w"], -width => 20,
			-textvariable => \$mp_userpw)->pack(-side => "left", -anchor => "nw");
		$b_p->Label(-text => "Berechtigungslevel: ")->pack(-side => 'left', -anchor => 'w');
		my $b_cb = $b_p->JComboBox(-textvariable => \$mp_userlevel,
			-relief => 'raised', -validate => 'none',
			)->pack(-side => "left", -anchor => "w");
	   $b_cb->addItem("dba", -selected => 1); 
	   $b_cb->addItem("mpadmin", -selected => 0); 
	   $b_cb->addItem("mpuser", -selected => 0); 
	   $b_cb->addItem("mpbooker", -selected => 0); 
	   $b_cb->addItem("mpreadonly", -selected => 0); 
		$TKnb_user->pack(-expand => "yes", -fill => "both", -padx => 5, -pady => 5, -side => "top");
		}
    my $result = $TKuser->Show;
    if ($result =~ /OK/)
    	{
		if ($mp_rootpw eq "")
			{
			$mp_status = "ERROR";
			$TKstat_lab->configure(-bg => "red");
			}
		else
			{
			$mp_progress = 40;
			$mp_status = "OK";
			$TKstat_lab->configure(-bg => $TKcolor);
			if (not defined $TKstartbutton)
				{
				$TKbody_frm->Label(-text => "\nNOW PRESS THE START BUTTON\n")->pack(-side => 'top');
				$TKstartbutton = $TKbody_frm->Button(-text => 'Start Installation',
					-command => [ \&MP_DBdosetup, $mp_debugflag ]);
				$TKstartbutton->pack(-side => 'top');
				}
			}
		}
	else
		{
		$mp_status = "CANCEL";
		$TKstat_lab->configure(-bg => "yellow");
		}
}

#
# PRINT Data
#
sub MP_DATAprint
{
	$TKprint = $TKtop->DialogBox(-title => "Drucken:", -buttons => ["OK"]);
	$TKprint->Label(-text => "current values:\n")->pack(-side => 'top', -anchor => 'nw');
	$TKprint->Label(-text => "DB typ:        $mp_dbflag")->pack(-side => 'top', -anchor => 'nw');
	$TKprint->Label(-text => "DB name:       $mp_dbname")->pack(-side => 'top', -anchor => 'nw');
	$TKprint->Label(-text => "DB datasource: $mp_dataflag")->pack(-side => 'top', -anchor => 'nw');
	$TKprint->Label(-text => "DB hostname:   $mp_dbhost")->pack(-side => 'top', -anchor => 'nw');
	$TKprint->Label(-text => "travelDB user:     $mp_user")->pack(-side => 'top', -anchor => 'nw');
	$TKprint->Label(-text => "travelDB user level: $mp_userlevel")->pack(-side => 'top', -anchor => 'nw');
	$TKprint->Label(-text => "deletion file: $mp_dbdelfile")->pack(-side => 'top', -anchor => 'nw');
	$TKprint->Label(-text => "generate file: $mp_dbgenfile")->pack(-side => 'top', -anchor => 'nw');
	$TKprint->Label(-text => "dump file: $mp_dbdumpfile")->pack(-side => 'top', -anchor => 'nw');
	$TKprint->Label(-text => "------------------------\n")->pack(-side => 'top', -anchor => 'nw');
	$TKprint->Label(-text => "state:        $mp_status\n")->pack(-side => 'top', -anchor => 'nw');
	$TKprint->Label(-text => "progress:   $mp_progress%\n")->pack(-side => 'top', -anchor => 'nw');
	$TKprint->Label(-text => "debug flag:    $mp_debugflag\n")->pack(-side => 'top', -anchor => 'nw');
	$TKprint->Show;

	mpdebug("\n\n");
	mpdebug("progress: $mp_progress%\n");
	mpdebug("values:");
	mpdebug("DB typ:        $mp_dbflag");
	mpdebug("DB name:       $mp_dbname");
	mpdebug("datasource:    $mp_dataflag");
	mpdebug("DB hostname:   $mp_dbhost");
	mpdebug("travelDB user: $mp_user");
	mpdebug("travelDB user Lvl: $mp_userlevel");
	mpdebug("deletion file: $mp_dbdelfile");
	mpdebug("generate file: $mp_dbgenfile");
	mpdebug("dump file: $mp_dbdumpfile");
}

#
# HELP
#
sub MP_HELPshow
{
	if (not defined $TKhelp)
		{
		$TKhelp = $TKtop->DialogBox(-title => "Help:", -buttons => ["OK"]);
		$TKhelp->Label(-text => "This is the wizard to setup/create your travel database.")->pack(-side => 'top');
		$TKhelp->Label(-text => "Fill out all wizards and start the installation.")->pack(-side => 'top');
		$TKhelp->Label(-text => "On oracle you need a proper oracle client and an net/SID name, plus the DBD:Oracle module")->pack(-side => 'top');
		$TKhelp->Label(-text => "On MS SQL Server you need to run the script where the database is installed (localhost)")->pack(-side => 'top');
		}
	$TKhelp->Show;
}

#
# ABOUT
#
sub MP_ABOUTshow
{
	if (not defined $TKabout)
		{
		$TKabout = $TKtop->DialogBox(-title => "About:", -buttons => ["OK"]);
		$TKabout->Label(-text => "travelDB              \n\n")->pack(-side => 'top', -anchor => 'nw');
		$TKabout->Label(-text => "database setup wizard\nversion: $mp_ver")->pack(-side => 'top', -anchor => 'nw');
		}
	$TKabout->Show;
	$mp_status = "DONE";
}


#
# DB SETUP wizard
#
sub MP_DBdosetup
{
	# read function arguments
	my ($debug) = @_;

	# declare vars and init if needed
	my $status = 0;
	my $scriptdir = "";
	my $ret = "NO";

	if ($mp_progress != 40)
		{
		$mp_progress = 0;
		$mp_status = "ERROR";
		$TKstat_lab->configure(-bg => "red");
		return;
		}

	# init travelDB perl module
	$scriptdir = dirname($mp_dbdelfile);
	chdir($scriptdir);
	$status = &MP_DBinit($mp_debugflag, $mp_dbname, $mp_dbhost, $mp_os);
	mpdebug("INIT - init done, changed dir to $scriptdir");

	# verify the correct DBI/DBD driver is available
	mpdebug("Starting to check the DBD driver availability for the DBI module");
	$status = &MP_DBcheckdbi($mp_dbflag);
	mpdebug("  returnvalue of checkdbi: $status");
	$mp_progress += 10;

	# check if a db is already present and drop it if so
	mpdebug("Starting to check and optionaly drop the current ROOT");
	$status = &MP_DBcheckroot($mp_dbsyspwd);
	mpdebug("  returnvalue of checkroot: $status");
	if ($status == 2)
		{
		if (not defined $TKdropdialog)
			{
			$TKdropdialog = $TKtop->Dialog(-text => 'Drop current travelDB ?',
				-bitmap => 'question', -title => 'Delete travelDB', -default_button => 'NO',
				-buttons => [qw/YES NO/]);
			}
		$ret = $TKdropdialog->Show;
		if ($ret eq "NO")
			{
			$mp_progress = 0;
			$mp_status = "ERROR";
			$TKstat_lab->configure(-bg => "red");
			&MP_DBclose();
			return;
			}
		else
			{
			mpdebug("  Drop user ROOT now");
			$status = &MP_DBdroproot($mp_dbsyspwd, $mp_dbdelfile);
			mpdebug("  returnvalue of droping ROOT: $status");
			}
		}
	if ($status != 0)
		{
		$mp_progress -= 10;
		$mp_status = "ERROR";
		$TKstat_lab->configure(-bg => "red");
		return;
		}
	$mp_progress += 10;

	return;

	# create db either with scripts or by loading a dump
	if ($mp_dataflag ne "dump")
		{
		mpdebug("Starting creation of db - pure init");
		$status = &MP_DBcreate($mp_dbsyspwd, $mp_rootpw, $mp_dbgenfile);
		mpdebug("  returnvalue of load classic data: $status");
		if ($status != 0)
			{
			$mp_progress -= 20;
			$mp_status = "ERROR";
			$TKstat_lab->configure(-bg => "red");
			return;
			}
		}
	else
		{
		mpdebug("Starting creation of db - including loading a dump");
		$status = &MP_DBloaddump($mp_dbsyspwd, $mp_rootpw, $mp_dbdumpfile);
		mpdebug("  returnvalue of create tdb users: $status");
		if ($status != 0)
			{
			$mp_progress -= 20;
			$mp_status = "ERROR";
			$TKstat_lab->configure(-bg => "red");
			return;
			}
		}
	$mp_progress += 20;

	# set root pwd and add user
	mpdebug("Starting setting root pwd and adding new user");
	$status = &MP_DBusers($mp_dbsyspwd, $mp_rootpw, $mp_user, $mp_userpw, $mp_userlevel);
	mpdebug("  returnvalue of setting users: $status");
	if ($status != 0)
		{
		$mp_progress -= 40;
		$mp_status = "ERROR";
		$TKstat_lab->configure(-bg => "red");
		return;
		}
	$mp_progress += 10;

	# test the database
	mpdebug("Starting test the installed database");
	$status = &MP_DBtdbtest($mp_rootpw);
	mpdebug("  returnvalue of tdb test: $status");
	if ($status != 0)
		{
		$mp_progress -= 50;
		$mp_status = "ERROR";
		$TKstat_lab->configure(-bg => "red");
		return;
		}
	$mp_progress += 10;

	$TKstartbutton->destroy();
	$mp_status = "DONE";
}

sub mpdebug
{
	# read function arguments
	my ($message) = @_;

	if ($mp_debugflag)
		{
		print "debug: $message\n";
		}
}
