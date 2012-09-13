#!/usr/bin/perl -w
#-------------------------------------------------------------------------------
# (c) yafra.org, 2002, Switzerland
#
# function:	psclient in perl
#
# needed modules: only standards
#
#-------------------------------------------------------------------------------
require 5.003;

use strict;
use Socket;

my ($remote, $port, $iaddr, $paddr, $proto, $line, $outstr, $instr);
my ($mpnetcmd, $len, $mplenbuf);

$remote  = shift || 'localhost';
$port    = shift || 5001;
if ($port =~ /\D/) { $port = getservbyname($port, 'tcp') }
die "No port" unless $port;

$iaddr   = inet_aton($remote)              or die "no host: $remote";
$paddr   = sockaddr_in($port, $iaddr);
$proto   = getprotobyname('tcp');

print "-> Perl PSclient: $remote $port\n";
socket(SOCK, PF_INET, SOCK_STREAM, $proto) or die "socket: $!";
connect(SOCK, $paddr)                      or die "connect: $!";

print "-> connected now - sending first message\n";
$mpnetcmd = sprintf "%s", "0Hello from Perl";
PSIPCwrite($mpnetcmd);

print "-> send exit now\n";
$mpnetcmd = sprintf "%d", 1;
PSIPCwrite($mpnetcmd);

print "closed socket and exit\n";

close (SOCK) or die "close: $!";

exit;

sub PSIPCwrite
{
	# read function arguments
	my ($message) = @_;

	print "debug: write message $message\n";

	$len = length($message);
	$mplenbuf = sprintf "%d\0     ", $len;
	syswrite(SOCK, $mplenbuf, 4);
	syswrite(SOCK, $mpnetcmd, $len);
}
