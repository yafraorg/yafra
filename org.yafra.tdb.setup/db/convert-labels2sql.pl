#!/usr/perl/bin/perl
#-------------------------------------------------------------------------------
# (c) yafra.org, Switzerland, 2004
#
# function:	update-services - updates the windows services file with new entries
#
# argument: no args
#
# author:	mwn
#
# date:		28.05.2002
#-------------------------------------------------------------------------------
#
# last modified:
#	mwn 28.05.2002	initial
#
#-------------------------------------------------------------------------------

my $mp_srcsql = "";
my $mp_destsql = "";
my $mp_destsqld = "";
my $debug = 0;

# init output
$ARGV = @ARGV;
if ($ARGV != 1)
	{
	print "\nplease specify: source label file\n";
	exit;
	}
$mp_srcsql = $ARGV[0];

if ($debug == 1)
	{
	print "debug: starting\n";
	print "debug: opening file $mp_srcsql\n";
	}

$mp_destsql = ">sql_"."$mp_srcsql".".sql";

if ($debug == 1)
	{
	print "debug: writing file to: $mp_destsql\n";
	}

# start conversion
open (DESTSQL,$mp_destsql) || warn "could not open file for writing $mp_destsql";
open (SRCSQL,$mp_srcsql) || warn "could not open file for reading $mp_srcsql";
while (<SRCSQL>)
{
	chomp;

#	general
	/(.{11,11})(.{11,11})(.{11,11})(.{11,11})(.{11,11})(.+)/;

	$lprg = $1;

	$ltyp = $2;
	$lst1 = $3;
	$lst2 = $4;
	$lsid = $5;
	$label = $6;

	$lprg =~ s/\W//g;
	$ltyp =~ s/\W//g;
	$lst1 =~ s/\W//g;
	$lst2 =~ s/\W//g;
	$lsid =~ s/\W//g;
	#$label =~ s/( )$//mg;
	if ($lsid eq '3')
		{
		$lsid = '25';
		}
	print DESTSQL "insert into label values ($lprg, $ltyp, $lst1, $lst2, $lsid, '$label')\n";
}
print DESTSQL "go\n";
close(DESTSQL);
close(SRCSQL);

if ($debug == 1)
	{
	print "debug: done\n";
	}
