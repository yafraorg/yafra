#!/usr/remote/bin/perl
require 5.003;
use mplib;
use CGI;
#use strict;

my ($init, $rec, $cgiinput);
my (@recs, @elements);

$cgiinput = new CGI;
$dbname = $cgiinput->param(mpdb);
$dbuser = $cgiinput->param(mpuser);
$dbpw = $cgiinput->param(mppw);
$dbhost = $cgiinput->param(mphost);
$sid = $cgiinput->param(mpsid);
$dlid = $cgiinput->param(mpdlid);
$arrid = $cgiinput->param(mparrid);
$katid = $cgiinput->param(mpkatid);

#
# HTML Head
#
mpInitHtml();
print <<END;
<HEAD>
<TITLE>MARCO POLO TO Internet: Kapazitaet der Dienstleistung</TITLE>
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
   msg = "MARCO POLO TO Internet - Sind Sie sicher, dass Sie buchen wollen ?";
   if (confirm(msg))
      return true;
   else
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
# test only
#
print <<END;
<H2>Buchungsdaten</H2>
<UL>
END

$query = "0\n1\n275\nselect * from root.dtg_view where dlg_id = $dlid and s_id = $sid;\f";
($mpresult, @recs) = mpQuery($query);
@elements = split(/\t/, $recs[0]);
print "<LI>Dienstleistung: $elements[1] - $elements[5]</LI>\n";

$query = "0\n1\n275\nselect * from root.kat_view where kat_id = $katid and s_id = $sid;\f";
($mpresult, @recs) = mpQuery($query);
@elements = split(/\t/, $recs[0]);
print "<LI>Kategorie: $elements[1]</LI>\n";

print "</UL>\n";

# sex und sprache noch setzten

print <<END;
<FORM onSubmit="return verify(this);" METHOD="POST" ACTION="../mpto/mpeubook2.pl">
<INPUT TYPE="hidden" NAME="mpdb" VALUE="$dbname">
<INPUT TYPE="hidden" NAME="mpuser" VALUE="$dbuser">
<INPUT TYPE="hidden" NAME="mppw" VALUE="$dbpw">
<INPUT TYPE="hidden" NAME="mphost" VALUE="$dbhost">
<INPUT TYPE="hidden" NAME="mpsid" VALUE="$sid">
<INPUT TYPE="hidden" NAME="mpdlid" VALUE="$dlid">
<INPUT TYPE="hidden" NAME="mparrid" VALUE="-1">
<INPUT TYPE="hidden" NAME="mpkatid" VALUE="$katid">


Name: <INPUT NAME="mpkun_name" TYPE=TEXT SIZE=30 MAX=30><BR>
Vorname: <INPUT NAME="mpkun_vor" TYPE=TEXT SIZE=20 MAX=20><BR>
Strasse: <INPUT NAME="mpkun_str" TYPE=TEXT SIZE=30 MAX=30><BR>
PLZ: <INPUT NAME="mpkun_plz" TYPE=TEXT SIZE=8 MAX=8>
Ort: <INPUT NAME="mpkun_ort" TYPE=TEXT SIZE=15 MAX=15><BR>
Telefon: <INPUT NAME="mpkun_tel" TYPE=TEXT SIZE=15 MAX=15>
FAX: <INPUT NAME="mpkun_fax" TYPE=TEXT SIZE=15 MAX=15><BR>
e-mail: <INPUT NAME="mpkun_mail" TYPE=TEXT SIZE=15 MAX=15>
<HR>
Bitte geben Sie hier das Von/Bis Datum ein (TT.MM.JJ):<BR>
Von: <INPUT NAME="mpdl_von" TYPE=TEXT SIZE=10 MAX=10>
Bis: <INPUT NAME="mpdl_bis" TYPE=TEXT SIZE=10 MAX=10>
<HR>
Anzahl Personen: <INPUT NAME="mpanzrei" TYPE=INT SIZE=3>
Geben Sie bitte pro Reisender auf einer Zeile &quot;Name, Vorname, Alter, Nationalit&auml;t&quot; ein: <BR>
<TEXTAREA NAME="mpreis" ROWS=4 COLS=80></TEXTAREA></P>
<P>
Falls n&ouml;tig k&ouml;nnen Sie im folgenden Feld noch spezielle Bemerkungen
eingeben, z.B. falls Sie einen Unterbruch in einem Hotel oder
eine spezielle Kabinennummer w&uuml;nschen. <BR>
<TEXTAREA NAME="mpbchtxt" ROWS=6 COLS=80></TEXTAREA>
<HR><B>Buchung &uuml;bermitteln mit diesem Knopf:</B>
<INPUT TYPE="submit" VALUE="Buchen">
</FORM>

END


#
# disconnect and exit
#
mpOKexit();
