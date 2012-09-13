#!/usr/bin/perl
#-------------------------------------------------------------------------------
# (c) yafra.org, Switzerland, 2004
#
# function:	convert abstract sql scripts to mysql sql scripts
#
# argument: no args
#
# author:	mwn
#
# date:		28.05.2005
#-------------------------------------------------------------------------------
#
# last modified:
#	mwn 28.05.2005	initial
# comment out the mpv_kontingent view because of sub selects
#-------------------------------------------------------------------------------

my $mp_srcsql = "";
my $mp_destsql = "";
my $mp_destsqld = "";
my $debug = 0;

# init output
$ARGV = @ARGV;
if ($ARGV != 1)
	{
	print "\nplease specify: source abstract sql script\n";
	exit;
	}
$mp_srcsql = $ARGV[0];

if ($debug == 1)
	{
	print "debug: starting\n";
	print "debug: opening file $mp_srcsql\n";
	}

$mp_destsql = ">mysql_"."$mp_srcsql";
$mp_destsqld = ">>mysql_drop.sql";

if ($debug == 1)
	{
	print "debug: writing file to: $mp_destsql and $mp_destsqld\n";
	print "debug: from file $mp_srcsql\n";
	}

# start conversion
open (DESTSQL,$mp_destsql) || warn "could not open file for writing $mp_destsql";
open (DESTSQLD,$mp_destsqld) || warn "could not open file for writing $mp_destsqld";
open (SRCSQL,$mp_srcsql) || warn "could not open file for reading $mp_srcsql";
while (<SRCSQL>)
{
	chomp;

#	general converting
	s{commit work}{commit};

#	table converting
	if (/drop table/)
		{
		print DESTSQLD $_;
		print DESTSQLD "\ncommit;\n";
		}
	s{drop table}{#drop table};
#	s{blob}{image};
#	s{datetime}{date};
	s{unique,}{,};
	if ($mp_srcsql eq "dbe_tables.sql")
		{
		if (/\);/)
			{
			#s{\);}{\) type = InnoDB;};
			}
		}

#	index converting
	s{clustering }{};
	if (/drop index/)
		{
		print DESTSQLD $_;
		print DESTSQLD "\ncommit;\n";
		}
	s{drop index (\w+) from (\w+)}{#drop index $1};

#	convert views
	if (/drop view/)
		{
		print DESTSQLD $_;
		print DESTSQLD "\ncommit;\n";
		}
	s{drop view (\w+)}{#drop view $1};
	s/todate\((\w+).(\w+)\)/FROM_UNIXTIME\($1.$2\)/g;

#	load script convertions (with inserts and deletes)
	s{delete from }{delete from root.};
	if (/delete from/)
		{
		print DESTSQLD $_;
		print DESTSQLD "\ncommit;\n";
		}
	s{delete from}{#delete from};
#	s{insert into }{insert into root.};

	print DESTSQL $_;
	print DESTSQL "\n";
}
print DESTSQLD "\ncommit;\n";
print DESTSQL "\ncommit;\n";
close(DESTSQL);
close(DESTSQLD);
close(SRCSQL);

if ($debug == 1)
	{
	print "debug: done\n";
	}
