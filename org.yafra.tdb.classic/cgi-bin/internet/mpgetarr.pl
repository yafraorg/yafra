#!/usr/remote/bin/perl
#----------------------------------------------------------
#
# Program:     show an ARR detail
#
# Protokoll:   MPNET
#
# copyright:	yafra.org, Switzerland, www.pisoag.com
#
# tag:			$Name:  $
# revision:		$Revision: 1.2 $
# cvs info:    $Id: mpgetarr.pl,v 1.2 2008-11-02 19:55:51 mwn Exp $
#---------------------------------------------------------------

require 5.003;
use mplib;
use CGI;
#use strict;

my ($init, $query, $rec, $mparrid);
my (@recs, @elements);

# init CGI params
$cgiinput = new CGI;
$dbname = $cgiinput->param(mpdb);
$dbuser = $cgiinput->param(mpuser);
$dbpw = $cgiinput->param(mppw);
$dbhost = $cgiinput->param(mphost);
$sid = $cgiinput->param(mpsid);
$mparrid = $cgiinput->param(mparrid);

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

mpPrintHtmlHeader("Angebotsdetail");

#
# get ARRANGEMENT
#
$query = "0\n1\n277\nselect * from root.arr_view where s_id = $sid and arr_id = $mparrid;\f";
($mpresult, @recs) = mpQuery($query);
@elements = split(/\t/, $recs[0]);
print "<H2>MARCO POLO Arrangement: $elements[1]</H2>\n";
print "Beginn: $elements[3]<P>\n";

#
# get ARR_DL
#
$query = "0\n1\n276\nselect * from root.arr_dl_view where s_id = $sid and arr_id = $mparrid order by teil, prio;\f";
($mpresult, @recs) = mpQuery($query);
print "<UL>\n";
foreach $rec (@recs)
	{
	@elements = split(/\t/, $rec);
	print "<LI>Teilnummer $elements[5]: $elements[3] mit Priorit�t $elements[6]\n";
	}
print "</UL>\n";

#
# exit
#
mpOKexit();
