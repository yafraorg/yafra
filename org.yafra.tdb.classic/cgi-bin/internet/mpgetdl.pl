#!/usr/remote/bin/perl
#----------------------------------------------------------
#
# Program:     show details about a DL
#
# Protokoll:   MPNET
#
# copyright:	yafra.org, Switzerland, www.pisoag.com
#
# tag:			$Name:  $
# revision:		$Revision: 1.2 $
# cvs info:    $Id: mpgetdl.pl,v 1.2 2008-11-02 19:55:51 mwn Exp $
#---------------------------------------------------------------

require 5.003;
use mplib;
use CGI;
#use strict;

my ($init, $dbname, $dbuser, $dbpw, $dbhost, $sid);
my ($cgiinput, $query);
my ($len, $kapa, $rec);
my (@kapas, @recs, @elements);

$cgiinput = new CGI;
$dbname = $cgiinput->param(mpdb);
$dbuser = $cgiinput->param(mpuser);
$dbpw = $cgiinput->param(mppw);
$dbhost = $cgiinput->param(mphost);
$sid = $cgiinput->param(mpsid);
$dlid = $cgiinput->param(mpdlid);

#
# HTML Head
#
mpInitHtml();
print <<END;
<HEAD>
<TITLE>MARCO POLO TO Internet: Dienstleistung buchen</TITLE>
<SCRIPT LANGUAGE="JavaScript">
<!---
function isblank(s)
{
   for (var i = 0; i < s.length; i++)
      {
      var c = s.charAt(i);
      if (c != ' ') return false;
      }
   return true;
}

function verify(f)
{
   var msg = "";
   var e = f.mpkatid;

   for (var i = 0; i < e.length; i++)
      {
      if (e[i].checked) return true;
      }
   msg = "MARCO POLO TO Internet - Bitte waehlen Sie ein Kategorie";
   alert(msg);
   return false;
}
// --->
</SCRIPT>
</HEAD>
<BODY background="/icons/mptoi-bg.jpeg">
END


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

#
# get DL title
#
$query = "0\n1\n275\nselect * from root.dtg_view where dlg_id = $dlid and s_id = $sid;\f";
($mpresult, @recs) = mpQuery($query);
@elements = split(/\t/, $recs[0]);
print "<H2>MARCO POLO Dienstleistung: $elements[1]</H2>\n";
print "Beginn: $elements[5]<BR>\n";

#
# get KAPA of DL
#
$query = "0\n4\n284\n$dlid\f";
$info = mpInfo($query);
@elements = split(/\n/, $info);
@kapas = split(/\r/, $elements[3]);

print <<END;
<FORM onSubmit="return verify(this);" METHOD="POST" ACTION="/cgi-perl/touristic/mpto/mpeubook1.pl">
<INPUT TYPE="hidden" NAME="mpdb" VALUE="$dbname">
<INPUT TYPE="hidden" NAME="mpuser" VALUE="$dbuser">
<INPUT TYPE="hidden" NAME="mppw" VALUE="$dbpw">
<INPUT TYPE="hidden" NAME="mphost" VALUE="$dbhost">
<INPUT TYPE="hidden" NAME="mpsid" VALUE="$sid">
<INPUT TYPE="hidden" NAME="mpdlid" VALUE="$dlid">
<INPUT TYPE="hidden" NAME="mparrid" VALUE="-1">

<TABLE BORDER=1>
<TR>
<TD><B>Kategorie</B></TD>
<TD><B>Preis</B></TD>
<TD><B>Verfuegbare Einheiten</B></TD>
<TD><B>Buchen</B></TD>
</TR>
END

foreach $rec (@kapas)
   {
   @recs = split(/\t/, $rec);

	print "<TR><TD>$recs[1]</TD><TD>$recs[2]</TD><TD>$recs[3]</TD>\n";
	print "<TD><INPUT TYPE='radio' NAME='mpkatid' VALUE='$recs[0]'></TD>\n";
	print "</TR>\n";
   }

print <<END;
</TABLE>
<INPUT TYPE="submit" VALUE="Next">
</FORM>
END

#
# disconnect and exit
#
mpOKexit();
