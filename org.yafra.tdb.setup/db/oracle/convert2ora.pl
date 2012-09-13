#!/usr/bin/perl
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
	print "\nplease specify: source abstract sql script\n";
	exit;
	}
$mp_srcsql = $ARGV[0];

if ($debug == 1)
	{
	print "debug: starting\n";
	print "debug: opening file $mp_srcsql\n";
	}

$mp_destsql = ">ora_"."$mp_srcsql";
$mp_destsqld = ">>ora_drop.sql";

if ($debug == 1)
	{
	print "debug: writing file to: $mp_destsql and $mp_destsqld\n";
	}

# start conversion
open (DESTSQL,$mp_destsql) || warn "could not open file for writing $mp_destsql";
open (DESTSQLD,$mp_destsqld) || warn "could not open file for writing $mp_destsqld";
open (SRCSQL,$mp_srcsql) || warn "could not open file for reading $mp_srcsql";
while (<SRCSQL>)
{
	chomp;

#	table converting
	if (/drop table/)
		{
		print DESTSQLD $_;
		print DESTSQLD "\ncommit work;\n";
		}
	s{drop table}{--drop table};
#	s{blob}{image};
	s{datetime}{date};

#	index converting
	s{clustering }{};
	if (/drop index/)
		{
		print DESTSQLD $_;
		print DESTSQLD "\ncommit work;\n";
		}
	s{drop index (\w+) from (\w+)}{--drop index $1};

#	convert views
	if (/drop view/)
		{
		print DESTSQLD $_;
		print DESTSQLD "\ncommit work;\n";
		}
	s{drop view (\w+)}{--drop view $1};

#	load script convertions (with inserts and deletes)
	s{delete from }{delete from root.};
	if (/delete from/)
		{
		print DESTSQLD $_;
		print DESTSQLD "\ncommit work;\n";
		}
	s{delete from}{--delete from};
	s{insert into }{insert into root.};

	print DESTSQL $_;
	print DESTSQL "\n";
}
print DESTSQLD "\ncommit work;\n";
print DESTSQL "\ncommit work;\n";
close(DESTSQL);
close(DESTSQLD);
close(SRCSQL);

if ($debug == 1)
	{
	print "debug: done\n";
	}
