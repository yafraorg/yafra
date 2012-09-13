#----------------------------------------------------------
#
# Package:     MARCO POLO lib functions for PERL
#
# File:        mplib.pm
#
# Protokoll:   MPNET
#
# copyright:	yafra.org, Switzerland, www.pisoag.com
#
# tag:			$Name:  $
# revision:		$Revision: 1.2 $
#
#Client send INIT:
#dbname \n username \n password \n clienthostname \n flag \n\0
#---------------------------------------------------------------
#Client receives:
#Resultcode \n mp_profil_fields \n\0
#
#---------------------------------------------------------------
#
#Client send QUERY:
#controlcode \n Querytype \n TableID \n Query \n\0
#---------------------------------------------------------------
#Client receives:
#Resultcode \n Rows \n Fields \n records \f\0
#
#records are:
#field \t field \t field \t\r
#field \t field \t field \t\r
#
#if controlcode is 0 it's a query and wait for next
#if controlcode is 1 it's the end and exit immediately
#
#----------------------------------------------------------

package mplib;

require 5.003;
use Socket;
use Exporter;

@ISA	= qw(Socket Exporter);
@EXPORT = qw(mpConnect mpSend mpQuery mpDisconnect mpReceive mpInitHtml mpPrintHtmlHeader mpPrintHtmlFooter mpOKexit mpERRORexit mpDBCexit mpInfo);

#use vars
#use subs


#
# SOCKET INTERFACE
#

#----------------------------------------------------------
#
# Subroutine:  mpConnect
#
# Parameters:  remote server name
#
# Description: create socket connexion to server
#
#----------------------------------------------------------
sub mpConnect { 
	# init Socket vars
	$remote	= shift || 'pswww.yafra.org';

	$port	= 5002;  # MARCO POLO NET
	$port	= getservbyname($port, 'tcp') or die "No port" unless $port;
	$iaddr	= inet_aton($remote) or die "no host: $remote";
	$paddr	= sockaddr_in($port, $iaddr);
	$proto	= getprotobyname('tcp');
	socket(SOCK, AF_INET, SOCK_STREAM, $proto) or die "socket : $!";
	connect(SOCK, $paddr);

	# DEBUG
	print "<!-- connect to MPNET on host = $remote -->\n";
}

#----------------------------------------------------------
#
# Subroutine:  mpReceive
#
# Parameters:  message string
#
# Description: Receive the message string to the server
#
#----------------------------------------------------------
sub mpReceive {
	my ($line, $len, $mplenbuf);

	sysread(SOCK, $line, 5);
	sysread(SOCK, $mplenbuf, 11);
	$len = 0 + ($mplenbuf);
	sysread(SOCK, $line, $len);
	
	# DEBUG ATTENTION THIS CONTAIS PLAIN PASSWORD !!
	#print "<!-- receiving <$line> -->\n";

	return $line;
}

#----------------------------------------------------------
#
# Subroutine:  mpSend
#
# Parameters:  message string
#
# Description: send the message string to the server
#
#----------------------------------------------------------
sub mpSend {
	my ($mpnetcmd) = @_;
	my ($len, $mplenbuf);
	
	# DEBUG ATTENTION THIS CONTAIS PLAIN PASSWORD !!
	#print "<!-- sending <$mpnetcmd> -->\n";

	$len = length($mpnetcmd);
	$mplenbuf = sprintf "%d\0            ", $len;
	syswrite(SOCK, "00000", 5);
	syswrite(SOCK, $mplenbuf, 11);
	syswrite(SOCK, $mpnetcmd, $len);
}

#----------------------------------------------------------
#
# Subroutine:  mpQuery
#
# Parameters:  message string
#
# Returns:     array 
#
# Description: send message string to server and wait for 
#              response
#
#----------------------------------------------------------
sub mpQuery {
	my ($query) = @_;
	my ($line, $strlen, $len);
	my (@fields, @records);
	my ($mpnetcmd, $mprows, $mpcols, $mprec, $mpresult);

	# DEBUG
	# print "<!-- send the query: <$query> -->\n";

	&mpSend($query);
	$line = &mpReceive();

	# DEBUG
	print "<!-- received record from daemon <$line> -->\n";

	@fields = split(/\n/, $line);
	$mpresult = $fields[0];
	$mprows = $fields[1];
	$mpcols = $fields[2];
	if ($mpresult != 0)
		{
		print "<!-- ERROR -->\n";
		@records = split (/\f/, $line);
		}
	else
		{
		print "<!-- OK -->\n";
		$mprec = $fields[3];
		@records = split (/\r/, $mprec);
		}

	return ($mpresult, @records);
}

#----------------------------------------------------------
#
# Subroutine:  mpInfo
#
# Parameters:  Info string
#
# Returns:     array 
#
# Description: send message string to server and wait for 
#              response
#
#----------------------------------------------------------
sub mpInfo {
	my ($query) = shift;
	my ($line);

	# DEBUG
	# print "<!-- the query is <$query> -->\n";

	&mpSend($query);
	$line = &mpReceive();

	# DEBUG
	# print "<!-- received record from daemon <$line> -->\n";

	return $line;
}


#----------------------------------------------------------
#
# Subroutine:  mpDisconnect
#
# Parameters:  none
#
# Description: close the socket connexion to server
#
#----------------------------------------------------------
sub mpDisconnect {
	syswrite(SOCK, "00000", 5);
	syswrite(SOCK, "7          ", 11);
	syswrite(SOCK, "1\n0\n0\n\n", 7);
	close(SOCK) or die "close: $!";
}



#
# HTML INTERFACE
#

#----------------------------------------------------------
#
# Subroutine:  mpInitHtml
#
# Parameters:  -
#
# Description: sends HTTP init message for HTML MIME type
#
#----------------------------------------------------------
sub mpInitHtml { 
	# $| = 1; # for flushing
	print "Content-type: text/html\n\n";
	print '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2//EN">';
	print "\n\n";
	print "<HTML>\n";
}

#----------------------------------------------------------
#
# Subroutine:  mpPrintHtmlHeader 
#
# Parameters:  two strings (message1, message2)
#
# Description: printout the HTML header
#
#----------------------------------------------------------
sub mpPrintHtmlHeader { 
	my ($message1) = @_;
	
	print <<END;
<HEAD>
END
	print "<TITLE>MARCO POLO: $message1</TITLE>\n";
	print <<END;
</HEAD>
<BODY>
<IMG ALIGN=MIDDLE SRC="/psexticons/psmapo.gif">
END
}

#----------------------------------------------------------
#
# Subroutine:  mpPrintHtmlFooter
#
# Parameters:  none
#
# Description: printout the HTML footer
#
#----------------------------------------------------------
sub mpPrintHtmlFooter {
	print <<END;
<HR>
<ADDRESS>
This service is brought to you by MARCO POLO TO !
<BR>
&copy yafra.org Switzerland, 1997
<BR>
For infos contact us by e-mail <A HREF="mailto:info\@yafra.org">info\@yafra.org</A>
</ADDRESS>
</BODY>
</HTML>
END
}


#
# Exit handling INTERFACE
#

#----------------------------------------------------------
#
# Subroutine:  mpOKexit
#
# Parameters:  none
#
# Description: ends programm OK
#
#----------------------------------------------------------
sub mpOKexit
{
	&mpPrintHtmlFooter();
	&mpDisconnect();
	exit;
}

#----------------------------------------------------------
#
# Subroutine:  mpERRORexit
#
# Parameters:  none
#
# Description: ends programm cause of an ERROR
#
#----------------------------------------------------------
sub mpERRORexit
{
	my ($errmsg) = @_;

	print("<P>$errmsg<P>\n");

	&mpPrintHtmlFooter();
	exit;
}

#----------------------------------------------------------
#
# Subroutine:  mpDBCexit
#
# Parameters:  error message string
#
# Description: ends programm cause of an DB connect error
#
#----------------------------------------------------------
sub mpDBCexit
{
	my ($errmsg) = @_;

	&mpPrintHtmlHeader("Errormessage/Fehlermeldung");

	print("<P>$errmsg<P>\n");

	&mpPrintHtmlFooter();
	exit;
}

1;
