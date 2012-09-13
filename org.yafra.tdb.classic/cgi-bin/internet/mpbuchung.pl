#!/usr/remote/bin/perl
#----------------------------------------------------------
#
# Program:     ask for a reservation to show details
#
# Protokoll:   MPNET
#
# copyright:	yafra.org, Switzerland, www.pisoag.com
#
# tag:			$Name:  $
# revision:		$Revision: 1.2 $
# cvs info:    $Id: mpbuchung.pl,v 1.2 2008-11-02 19:55:52 mwn Exp $
#---------------------------------------------------------------

require 5.003;
use mplib;
use cgi;
#use strict;



my ($init, $dbname, $dbuser, $dbpw, $dbhost, $sid);
my ($cgiinput);

$cgiinput = new CGI;
$dbname = $cgiinput->param(mpdb);
$dbuser = $cgiinput->param(mpuser);
$dbpw = $cgiinput->param(mppw);
$dbhost = $cgiinput->param(mphost);
$sid = $cgiinput->param(mpsid);

#
# connect
#
mpInitHtml();
print <<END;
<HEAD>
<TITLE>MARCO POLO TO Internet: Buchungsstatus</TITLE>
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
	var e = f.mpbchref;

	if ((e.value == null) || (e.value == "") || isblank(e.value))
		{
		msg = "MARCO POLO TO Internet - Bitte geben Sie eine Buchungs ID ein";
		alert(msg);
		return false;
		}
	return true;
}
// --->
</SCRIPT>
</HEAD>
<BODY bgcolor="#FFFFFF">
<IMG ALIGN=MIDDLE SRC="/icons/mptoi.gif">
END

#
# Bodytitle
#
print <<END;
<FORM onSubmit="return verify(this);" METHOD="POST" ACTION="/cgi-perl/touristic/mpto/mpeubookstat.pl">
<INPUT TYPE="hidden" NAME="mpdb" VALUE="$dbname">
<INPUT TYPE="hidden" NAME="mpuser" VALUE="$dbuser">
<INPUT TYPE="hidden" NAME="mppw" VALUE="$dbpw">
<INPUT TYPE="hidden" NAME="mphost" VALUE="$dbhost">
<INPUT TYPE="hidden" NAME="mpsid" VALUE="$sid">
<B>Buchungs ID:</B> <INPUT TYPE="text" NAME="mpbchref" SIZE=8>
<INPUT TYPE="submit" VALUE="OK">
</FORM>
END

#
# footer and exit
#
mpPrintHtmlFooter();
exit;
