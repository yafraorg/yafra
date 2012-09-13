#!/usr/remote/bin/perl
#----------------------------------------------------------
#
# Program:     get all ARR
#
# Protokoll:   MPNET
#
# copyright:	yafra.org, Switzerland, www.pisoag.com
#
# tag:			$Name:  $
# revision:		$Revision: 1.2 $
# cvs info:    $Id: mpgetarrs.pl,v 1.2 2008-11-02 19:55:51 mwn Exp $
#---------------------------------------------------------------

require 5.003;
use mplib;
use CGI;
#use strict;

my (@recs, @elements);
my ($init, $dbname, $dbuser, $dbpw, $dbhost, $sid);
my ($rec, $query, $cgiinput, $info);

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

mpPrintHtmlHeader("Arrangement�bersicht");
$query = "0\n1\n277\nselect * from root.arr_view where s_id = $sid and arr_id > -1;\f";
($mpresult, @recs) = mpQuery($query);

print "<UL>\n";
foreach $rec (@recs)
	{
	@elements = split(/\t/, $rec);
	print "<LI><A HREF=\"/cgi-perl/touristic/mpto/mpgetarr.pl?mpdb=$dbname&mpuser=$dbuser&mppw=$dbpw&mphost=$dbhost&mpsid=$sid&mparrid=$elements[0]\">$elements[1] $elements[3]</A>\n";
	}
print "</UL>\n";

#
# exit
#
mpOKexit();
