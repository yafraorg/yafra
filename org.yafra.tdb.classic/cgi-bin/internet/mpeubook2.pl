#!/usr/remote/bin/perl
require 5.003;
use mplib;
use CGI;
#use strict;

my ($rec);
my ($bid, $dbname, $dbuser, $dbpw, $dbhost, $sid, $dlid, $arrid, $katid);
my ($kunname, $kunvor, $kunstr, $kunplz, $kunort, $anzrei);
my ($kuntel, $kunfax, $kunmail, $reis, $bchtxt, $mpresult);
my (@recs, @elements);

$bid = 0;
$mpresult = 0;

$cgiinput = new CGI;
$dbname = $cgiinput->param(mpdb);
$dbuser = $cgiinput->param(mpuser);
$dbpw = $cgiinput->param(mppw);
$dbhost = $cgiinput->param(mphost);
$sid = $cgiinput->param(mpsid);
$dlid = $cgiinput->param(mpdlid);
$arrid = $cgiinput->param(mparrid);
$katid = $cgiinput->param(mpkatid);
$kunname = $cgiinput->param(mpkun_name);
$kunvor = $cgiinput->param(mpkun_vor);
$kunstr = $cgiinput->param(mpkun_str);
$kunplz = $cgiinput->param(mpkun_plz);
$kunort = $cgiinput->param(mpkun_ort);
$kunfax = $cgiinput->param(mpkun_fax);
$kuntel = $cgiinput->param(mpkun_tel);
$kunmail = $cgiinput->param(mpkun_mail);
$dlvon = $cgiinput->param(mpdl_von);
$dlbis = $cgiinput->param(mpdl_bis);
$anzrei = $cgiinput->param(mpanzrei);
$reis = $cgiinput->param(mpreis);
$bchtxt = $cgiinput->param(mpbchtxt);

#
# HTML Head
#
mpInitHtml();
print <<END;
<HEAD>
<TITLE>MARCO POLO TO Internet: Buchungsdaten</TITLE>
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

print "<!-- connect to MPNET with DB $dbname as USER $dbuser -->\n";

#
# Write BUCHUNG to MPNET server
#
$query = sprintf "0\n4\n46\n%d\b%d\b%d\b%s\b%s\b%s\b%s\b%s\b%s\b%s\b%s\b%s\b%s\b%d\b%s\b%s\f", $arrid, $dlid, $katid, $kunname, $kunvor, $kunstr, $kunplz, $kunort, $kunfax, $kuntel, $kunmail, $dlvon, $dlbis, $anzrei, $reis, $bchtxt;
($mpresult, @recs) = mpQuery($query);
if ($mpresult != 0)
	{
	print "<H2>Buchungs Fehlermeldung</H2>\n";
	print "<P>Ihre Buchung wies einen Fehler auf !\n";
	print "<BR>Die Buchung kann nicht bearbeitet werden, bitte versuchen\n";
	print "Sie es nochmals indem Sie auf den ZURUECK Knopf in Ihrem\n";
	print "Browser drücken\n";
	print "<P>Zusätzliche Meldungen: (Fehlercode: $mpresult)\n";
	print "<PRE>\n";
	print "$recs[1]";
	print "</PRE>\n";
	mpDisconnect();
	mpERRORexit();
	}

#
# body
#
$bid = $recs[0];

print <<END;
<H2>Buchungsbestätigung</H2>
Ihre Buchung wurde erfolgreich erfasst und wird so rasch als moeglich
verarbeitet. Sie können den Status Ihrer Buchung jederzeit unter dem
Menupunkt "Buchungsstatus" ansehen und zwar mit folgender Kennung/ID:
<P>
<B>$bid</B>
<P>
Falls Sie noch weitere Fragen haben, wenden Sie sich doch am besten
direkt via e-mail an Ihre Buchungsstelle. Besten Dank !
END

#
# disconnect and exit
#
mpOKexit();
