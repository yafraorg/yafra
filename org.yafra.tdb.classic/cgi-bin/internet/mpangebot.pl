#!/usr/remote/bin/perl
#----------------------------------------------------------
#
# program:     generate HTML page with get arrangement or dl
#
# protokoll:   MPNET
#
# copyright:	yafra.org, Switzerland, www.pisoag.com
#
# tag:			$Name:  $
# revision:		$Revision: 1.2 $
# cvs info:    $Id: mpangebot.pl,v 1.2 2008-11-02 19:55:51 mwn Exp $
#---------------------------------------------------------------

require 5.003;
use mplib;
use CGI;
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
mpPrintHtmlHeader("MARCO POLO Angebotsmaske", "MARCO POLO Angebotsmaske");

#
# Bodytitle
#
print <<END;
<UL>
<!--- <LI><A HREF="mpangebot-suchen.html">Angebote suchen</A> --->

<LI>
<FORM METHOD="POST" ACTION="/cgi-perl/touristic/mpto/mpgetarrs.pl">
<INPUT TYPE="hidden" NAME="mpdb" VALUE="$dbname">
<INPUT TYPE="hidden" NAME="mpuser" VALUE="$dbuser">
<INPUT TYPE="hidden" NAME="mppw" VALUE="$dbpw">
<INPUT TYPE="hidden" NAME="mphost" VALUE="$dbhost">
<INPUT TYPE="hidden" NAME="mpsid" VALUE="$sid">
<INPUT TYPE="submit" VALUE="Arrangements">
</FORM>

<LI>
<FORM METHOD="POST" ACTION="/cgi-perl/touristic/mpto/mpgetdls.pl">
<INPUT TYPE="hidden" NAME="mpdb" VALUE="$dbname">
<INPUT TYPE="hidden" NAME="mpuser" VALUE="$dbuser">
<INPUT TYPE="hidden" NAME="mppw" VALUE="$dbpw">
<INPUT TYPE="hidden" NAME="mphost" VALUE="$dbhost">
<INPUT TYPE="hidden" NAME="mpsid" VALUE="$sid">
<INPUT TYPE="submit" VALUE="Dienstleistungen">
</FORM>
</UL>
END

#
# footer and exit
#
mpPrintHtmlFooter();
exit;
