#!/usr/bin/env perl
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
#
# function:	update-services - updates the windows services file with new entries
#
# argument: no args
#
# date:		28.05.2002
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

open (WINSERV,$winservice) || warn "could not open file for reading";
while (<WINSERV>)
{
	chomp;

	if ($debug == 1)
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
	print "debug: act on mapo $setmapo and piso $setpiso\n";
	}

if ($setmapo == 0)
	{
	open (WINSERV,$addwinservice);
	print WINSERV "marcopolo        5000/tcp\n";
	close(WINSERV);
	}

if ($setmpnet == 0)
	{
	open (WINSERV,$addwinservice);
	print WINSERV "mpnet            5002/tcp\n";
	close(WINSERV);
	}

if ($setpiso == 0)
	{
	open (WINSERV,$addwinservice);
	print WINSERV "psserver         5001/tcp\n";
	close(WINSERV);
	}

if ($debug == 1)
	{
	print "debug: done\n";
	}
