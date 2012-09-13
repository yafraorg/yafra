#!/usr/remote/bin/perl
#----------------------------------------------------------
#
# Program:     get all DL
#
# Protokoll:   MPNET
#
# copyright:	yafra.org, Switzerland, www.pisoag.com
#
# tag:			$Name:  $
# revision:		$Revision: 1.2 $
# cvs info:    $Id: mpgetdls.pl,v 1.2 2008-11-02 19:55:52 mwn Exp $
#---------------------------------------------------------------

require 5.003;
use mplib;
use CGI;
#use strict;

my ($init, $dbname, $dbuser, $dbpw, $dbhost, $sid);
my ($rec, $query, $cgiinput, $info);
my ($rec);
my (@recs, @elements);

$cgiinput = new CGI;
$dbname = $cgiinput->param(mpdb);
$dbuser = $cgiinput->param(mpuser);
$dbpw = $cgiinput->param(mppw);
$dbhost = $cgiinput->param(mphost);
$sid = $cgiinput->param(mpsid);

mpInitHtml();

#
# connect
#
mpConnect($dbhost);
$init = "$dbname\n$dbuser\n$dbpw\n$dbhost\n0\n";
mpSend($init);
$rec = mpReceive();
@elements = split(/\n/, $rec);
if ($elements[0] != 0)
	{
	mpDBCexit($elements[1]);
	}

mpPrintHtmlHeader("Dienstleistungs�bersicht");
$query = "0\n1\n275\nselect * from root.dtg_view where s_id = $sid and dlg_id > -1;\f";
($mpresult, @recs) = mpQuery($query);

print "<H1>Dienstleistungen</H1>\n";
print "<UL>\n";
foreach $rec (@recs)
	{
	@elements = split(/\t/, $rec);
	print "<LI><A HREF=\"/cgi-perl/touristic/mpto/mpgetdl.pl?mpdb=$dbname&mpuser=$dbuser&mppw=$dbpw&mphost=$dbhost&mpsid=$sid&mpdlid=$elements[0]\">$elements[1] $elements[5]</A>\n";
	#print @elements;
	#print "\n";
	}
print "</UL>\n";

#
# disconnect and exit
#
mpOKexit();
