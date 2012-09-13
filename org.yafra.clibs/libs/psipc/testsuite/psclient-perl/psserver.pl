#!/usr/bin/perl -Tw
#-------------------------------------------------------------------------------
# (c) yafra.org, 2002, Switzerland
#
# function:	psserver in perl
#
# needed modules: only standards
#
# CVS tag:   $Name:  $
# author:    $Author: mwn $
# revision:  $Revision: 1.1 $
#-------------------------------------------------------------------------------
#require 5.003;
use strict;
BEGIN { $ENV{PATH} = '/usr/ucb:/bin' }
use Socket;
use Carp;

sub logmsg { print "$0 $$: @_ at ", scalar localtime, "\n" } 

my $port = shift || 2345;
my $proto = getprotobyname('tcp');
socket(Server, PF_INET, SOCK_STREAM, $proto) or die "socket: $!";
setsockopt(Server, SOL_SOCKET, SO_REUSEADDR, pack("l", 1))
                                             or die "setsockopt: $!";
bind(Server, sockaddr_in($port, INADDR_ANY)) or die "bind: $!";
listen(Server,SOMAXCONN)                     or die "listen: $!";

logmsg "server started on port $port";

my $paddr;

$SIG{CHLD} = \&REAPER;

for ( ; $paddr = accept(Client,Server); close Client) {
    my($port,$iaddr) = sockaddr_in($paddr);
    my $name = gethostbyaddr($iaddr,AF_INET);

    logmsg "connection from $name [", 
            inet_ntoa($iaddr), "] 
            at port $port";

    print Client "Hello there, $name, it's now ", 
                    scalar localtime, "\n";
} 
