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
	print "\nplease specify: source abstract sql script\n";
	exit;
	}
$mp_srcsql = $ARGV[0];

if ($debug == 1)
	{
	print "debug: starting\n";
	print "debug: opening file $mp_srcsql\n";
	}

$mp_destsql = ">mssql_"."$mp_srcsql";
$mp_destsqld = ">>mssql_drop.sql";

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

#	general
	s{;}{\nGO};
	s{commit work}{GO};

#	table converting
	s{drop table }{--drop table tdbadmin.};
	s{blob}{image};
	s{create table }{create table tdbadmin.};
	s{ references }{ references tdbadmin.};

#	index converting
	s{clustering }{};
	s{drop index (\w+) from (\w+)}{--drop index $1};
	if ((/^grant/) || (/^revoke/))
		{
		s{ on }{ on };
		}
	else
		{
		s{ on }{ on tdbadmin.};
		}

#	convert views
	s{create view }{create view tdbadmin.};
	s{drop view (\w+)}{--drop view $1};
	s/todate\((\w+).(\w+)\)/CAST\(DATEADD\(second, $1.$2, \'1\/1\/1970\'\) AS DATETIME\)/g;

#	load script convertions (with inserts and deletes)
	s{delete from }{delete from tdbadmin.};
#	if (/delete from/)
#		{
#		print DESTSQLD $_;
#		print DESTSQLD "\ngo\n";
#		}
	s{delete from }{--delete from tdbadmin.};
	s{insert into }{insert into tdbadmin.};

#	grant
	s{revoke all privileges}{revoke select, insert, update, delete};

	print DESTSQL $_;
	print DESTSQL "\n";
}
print DESTSQL "\ngo\n";
close(DESTSQL);
close(SRCSQL);

if ($debug == 1)
	{
	print "debug: done\n";
	}
