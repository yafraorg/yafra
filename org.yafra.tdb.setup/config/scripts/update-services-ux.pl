#!/usr/bin/perl
#-------------------------------------------------------------------------------
# (c) yafra.org, 2004
#
# function:	update-services - updates the windows services file with new entries
#
# argument: no args
#
# author:	Administrator@yafra.org
#
# date:		28.02.2004
#-------------------------------------------------------------------------------
#
# last modified:
#	mw 28.02.2005	converted to unix
#
#-------------------------------------------------------------------------------

my $winservice = "/etc/services";
my $addwinservice = ">>/etc/services";
my $setmapo = 0;
my $setmpnet = 0;
my $setpiso = 0;
my $debug = 0;

if ($debug == 1)
	{
	print "debug: starting\n";
	print "debug: opening file $winservice\n";
	}

if ($debug == 1)
	{
	print "debug: Service File is: $winservice\n";
	print "debug: add Service File is: $addwinservice\n";
	}

open (WINSERV,$winservice) || warn "could not open file for reading $winservice";
while (<WINSERV>)
{
	chomp;

	if ($debug == 2)
		{
		print "debug: comparing $_\n";
		}

	if (/marcopolo/)
		{
		$setmapo = 1;
		}
	if (/mpnet/)
		{
		$setmpnet = 1;
		}
	if (/psserver/)
		{
		$setpiso = 1;
		}
}
close(WINSERV);

if ($debug == 1)
	{
	print "debug: add entries if value is zero: marcopolo: $setmapo, psserver $setpiso, mpnet: $setmpnet\n";
	}

if ($setmapo == 0)
	{
	open (WINSERV,$addwinservice) || warn "could not open file for reading $addwinservice";
	print WINSERV "marcopolo        5000/tcp\n";
	close(WINSERV);
	}

if ($setmpnet == 0)
	{
	open (WINSERV,$addwinservice) || warn "could not open file for reading $addwinservice";
	print WINSERV "mpnet            5002/tcp\n";
	close(WINSERV);
	}

if ($setpiso == 0)
	{
	open (WINSERV,$addwinservice) || warn "could not open file for reading $winservice";
	print WINSERV "psserver         5001/tcp\n";
	close(WINSERV);
	}

if ($debug == 1)
	{
	print "debug: done\n";
	}
