#!/usr/perl/bin/perl
#-------------------------------------------------------------------------------
# (c) yafra.org, Switzerland, www.pisoag.com
#
# function:	makempadminconf
#
# argument: config_path_and_filename install_path hostname dbname user password
#
# author:	administrator@yafra.org
#
# date:		28.05.2002
#-------------------------------------------------------------------------------
#
# last modified:
#	mw 28.05.2002	initial
#
#-------------------------------------------------------------------------------

my $mp_conffile = "";
my $mp_instpath = "";
my $mp_hostname = "";
my $mp_dbname = "";
my $mp_user = "";
my $mp_pw = "";
my $debug = 0;


# init output
$ARGV = @ARGV;
if ($ARGV != 6)
	{
	print "\nplease specify: config_path_and_filename install_path hostname dbname user password\n";
	exit;
	}
$mp_conffile = $ARGV[0];
$mp_instpath = $ARGV[1];
$mp_hostname = $ARGV[2];
$mp_dbname = $ARGV[3];
$mp_user = $ARGV[4];
$mp_pw = $ARGV[5];

chdir($mp_instpath);


print "\n\nMARCO POLO TO Admin config file creation\n\n";
print "MAPO TO Admin conf file is: $mp_conffile\n";
print "Install Path: $mp_instpath\n";
print "Hostname: $mp_hostname\n";
print "DB Name: $mp_dbname\n";
print "User: $mp_user\n";
print "User Password: $mp_pw\n";


if ($debug == 1)
	{
	print "\n\ndebug: opening file $winservice\n";
	}

open (WINSERV,">$mp_conffile") || warn "could not open file for reading";

if ($debug == 1)
	{
	print "debug: created conf file and writing now\n";
	}

print WINSERV "Version:	\$Revision: 1.1 $\n";
print WINSERV "<<<<<<<<<<<<<<<<<<<<<<<<<<<< DB PROPERTIES >>>>>>>>>>>>>>>>>>>>>>>>>>>>	\n";
print WINSERV "DB Host name	$mp_hostname\n";
print WINSERV "DB Host port number	1521\n";
print WINSERV "DB S_ID	$mp_dbname\n";
print WINSERV "User Name	$mp_user\n";
print WINSERV "User Password	$mp_pw\n";
print WINSERV "\"DB Language {ENGLISH=25; GERMAN=1; FRENCH=34}\"	25\n";
print WINSERV "<<<<<<<<<<<<<<<<<<< INTERNAL APPLICATION PROPERTIES >>>>>>>>>>>>>>>>>>>	\n";
print WINSERV "\"GUI Language {ENGLISH=25; GERMAN=1; FRENCH=34}\"	25\n";
print WINSERV "ProgressBar at startup {YES, NO}	YES\n";
print WINSERV "Default currency (WHR_ID)	32\n";
print WINSERV "Default country (LAND_ID)	756\n";
print WINSERV "<<<<<<<<<<<<<<<<<<<<<<<<<< LOGGING PROPERTIES >>>>>>>>>>>>>>>>>>>>>>>>>>	\n";	
print WINSERV "Trace SQL query in a logFile {YES, NO}	YES\n";
print WINSERV "Path to the MPAdmin2000.log file	$mp_instpath\n";
print WINSERV "Log strategy {ECONOMICAL_STRATEGY=0, CONSERVATIVE_STRATEGY=1, CONSERVATIVE_STRATEGY_IN_ONE_FILE=2}	0\n";
print WINSERV "View log messages in a logFrame {YES, NO}	NO\n";
print WINSERV "Lowest logTrace level (floor) used to trace messages in the logfile	0\n";
print WINSERV "LogTrace level for any debug informations	-1\n";
print WINSERV "LogTrace level for SQL SELECT statement	0\n";
print WINSERV "LogTrace level for SQL UPDATE statement	1\n";
print WINSERV "LogTrace level for SQL INSERT statement	2\n";
print WINSERV "LogTrace level for SQL DELETE statement	2\n";

close(WINSERV);

print "done\n";
