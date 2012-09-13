#!/usr/perl/bin/perl
#-------------------------------------------------------------------------------
# (c) yafra.org, Switzerland, www.pisoag.com
#
# function:	makempproperties - make the MP2000Properties for the TO Booker
#
# argument: config_path_and_filename install_path hostname dbname
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
my $mp_pluginpath = "";
my $debug = 0;


# init output
$ARGV = @ARGV;
if ($ARGV != 4)
	{
	print "\nplease specify: config_path_and_filename install_path hostname dbname\n";
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


if ($debug == 1)
	{
	print "\n\ndebug: opening file $winservice\n";
	}

open (WINSERV,">$mp_conffile") || warn "could not open file for reading";

if ($debug == 1)
	{
	print "debug: created conf file and writing now\n";
	}

$mp_pluginpath = $mp_instpath;
$mp_pluginpath =~ s/\\/\\\\/g;

print WINSERV "#--- server running mod ---\n";
print WINSERV "# Here is the way to fill these parameters :\n";
print WINSERV "# trace, showsql, showdata, debug, showmemory are to 'true' or 'false'\n";
print WINSERV "# output is 'System' or a file path whith doubled separator, for ex. c:\\temp,\n";
print WINSERV "# or output=c:\\opt\\Iona\\OrbixWeb3.1c\\MP2000Log\n";
print WINSERV "# timeout is to 'infinite', 'default', or a number in milliseconds\n";
print WINSERV "# database_host is to 'localhost' or to a remote host name, for ex. test.yafra.org\n";
print WINSERV "# database_name is normally to orcl\n";
print WINSERV "#Thu Jun 06 22:52:32 CEST 2002\n";
print WINSERV "debug=false\n";
print WINSERV "statusinguilanguage=true\n";
print WINSERV "travelertypeinguilanguage=true\n";
print WINSERV "output=c:\\\\temp\n";
print WINSERV "database_shortcut=$mp_dbname\n";
print WINSERV "plugins=$mp_pluginpath\\\\plugins\n";
print WINSERV "countriesinguilanguage=true\n";
print WINSERV "tmp=c:\\\\temp\n";
print WINSERV "trace=false\n";
print WINSERV "showsql=false\n";
print WINSERV "database_host=$mp_hostname\n";
print WINSERV "timeout=infinite\n";
print WINSERV "database_name=$mp_dbname\n";
print WINSERV "showdata=true\n";
print WINSERV "languagesinguilanguage=true\n";

close(WINSERV);

print "done\n";
