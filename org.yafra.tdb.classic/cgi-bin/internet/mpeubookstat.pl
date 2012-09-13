#!/usr/remote/bin/perl
#----------------------------------------------------------
#
# Program:     show detailed info about reservation
#
# Protokoll:   MPNET
#
# copyright:	yafra.org, Switzerland, www.pisoag.com
#
# tag:			$Name:  $
# revision:		$Revision: 1.2 $
# cvs info:    $Id: mpeubookstat.pl,v 1.2 2008-11-02 19:55:51 mwn Exp $
#---------------------------------------------------------------

require 5.003;
use mplib;
use cgi;
#use strict;

my ($init, $rec, $query, $cgiinput, $info);
my (@recs, @elements, @inforecs);

$cgiinput = new CGI;
$dbname = $cgiinput->param(mpdb);
$dbuser = $cgiinput->param(mpuser);
$dbpw = $cgiinput->param(mppw);
$dbhost = $cgiinput->param(mphost);
$sid = $cgiinput->param(mpsid);
$bchid = $cgiinput->param(mpbchref);

mpInitHtml();
print <<END;
<HEAD>
<TITLE>MARCO POLO TO Internet: Buchungsstatus</TITLE>
</HEAD>
<BODY bgcolor="#FFFFFF">
<IMG ALIGN=MIDDLE SRC="/icons/apache_pb.gif">
END


#
# connect
#
mpConnect("$dbhost");
$init = "$dbname\n$dbuser\n$dbpw\n$dbhost\n0\n";
mpSend($init);
$rec = mpReceive();
@elements = split(/\n/, $rec);
if ($elements[0] != 0)
	{
	mpDBCexit($elements[1]);
	}

$query = "0\n3\n41\n$bchid\f";
$info = mpInfo($query);
@inforecs = split(/\r/, $info);

#
# Bodytitle
#
print <<END;
<HR>
<H2>Buchungsstatus</H2>

Ihr Status fuer Ihre Buchung mit der Kennung/ID <B>$bchid</B> ist:
<P>
<PRE>
END

print $inforecs[1];
print "\n";

print <<END;
</PRE>
<P>
END

# next release check for outputs
#
#<HR>
#<H2>Aktionen</H2>
#Folgende Aktionen stehen Ihnen zur Verfuegung:
#<UL>
#<LI>Sie koennen Ihre Rechnung abrufen
#</UL>

#
# write a back to the index menu button
#
print <<END;
<HR>
<IMG ALIGN=MIDDLE SRC="../../../icons/back.xbm">
<A HREF="../../../tointernet/site.html">
Zur�ck zum MARCO POLO TO Internet Menu</A>
END

print <<END;
<IMG ALIGN=MIDDLE SRC="../../../icons/an1.gif" WIDTH=50 HEIGHT=32>
<A HREF="../../../tointernet/search/search.html">Eine weitere Dienstleistung</A>
END

#
# disconnect and exit
#
mpOKexit();
