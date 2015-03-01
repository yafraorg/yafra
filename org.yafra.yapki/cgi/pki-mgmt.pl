#!/usr/bin/perl
#-------------------------------------------------------------------------------
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
#
# (c) yafra.org, 2002, Switzerland
#
# function:	management of openssl installation
#
# argument: cmd, act
#
# supported commands: info
#
# needed modules: CGI
#
#-------------------------------------------------------------------------------

#
#Die Indexdatei besteht aus sechs Spalten, jeweils getrennt durch einen Tabulator (nicht durch Leerzeichen). Die Eintr�ge in den einzelnen Spalten haben die folgende Bedeutung:
#
#   1. Status des Zertifikats. Einer der Buchstaben R (revoked), E (expired) oder V (valid).
#   2. Ablaufzeitpunkt des Zertifikats. Format ist YYMMDDHHMMSSZ in UTC-Zeit
#   3. Ist in obiger Beispielzeile leer. Die Spalte kann aber ebenfalls einen Ablaufzeitpunkt YYMMDDHHMMSSZ in UTC-Zeit enthalten. Ist hier ein Zeitstempel eingetragen, entspricht er dem Widerrufszeitpunkt des Zertifikats. Dann mu� in der ersten Spalte (statt V) ein R stehen. F�r ein g�ltiges Zertifikat ist diese Spalte leer.
#   4. Hexadezimale Seriennummer des Zertifikats.
#   5. Wo das Zertifikat zu finden ist. Wird derzeit immer mit "unknown" besetzt.
#   6. Der Name des Zertifikatinhabers. �blicherweise der Distinguished Name und die E-Mail-Adresse.
#Grunds�tzlich ist es m�glich, �ber Ver�nderung der Indexdatei eine irrt�mliche Zertifizierung "r�ckg�ngig" zu machen.
#Das wird erreicht, indem die letzte Zeile gel�scht, und der Z�hler in der Datei serial um Eins erniedrigt wird. Das gilt allerdings nur f�r
#das zuletzt herausgegebene Zertifikat, und auch nur, wenn es noch nicht ver�ffentlicht wurde. Grunds�tzlich ist f�r einen ernsthaften CA-Betrieb von solchen Ver�nderungen der Indexdatei abzuraten. Der bessere Weg w�re der Widerruf des betreffenden Zertifikats.

#pending: creation of crls, revoke, renew, expire, view details, view crl
# plus request process update

# print HTML header
$| = 1; # for flushing
print "Content-type: text/html\n\n";

use CGI;

#use Net::FTP;
#my $ftp;
#my $hostname = 'www.yafra.org';
#my $username = 'xx';
#my $pwd = 'yy';
#my $location = '/ssl';


#
# main procedure
#

# openssl locations
my $openssl = '/data/pki';
my $pki = $openssl . '/CA_ROOT';
my $pkicounter = $pki . '/serial';
my $pkicerts = $pki . '/index.txt';
my $config = $openssl . '/openssl.cnf';
my $crldays = 90;
my $pkicrl = $pki . '/crl/cayafra.crl';

my $query = new CGI;
my $fcmd = '';
my $fpwd = '';
my $fsel = '';
$fcmd = $query->param('cmd');
$fpwd = $query->param('pwd');
$fsel = $query->param('sel');
my $output;
if ($^O eq "MSWin32")
	{
	$output = "/data/pki/CA_ROOT/www/systeminfo.txt";	# location for storage
#	$output = "c:/pingout.txt";	# location for storage
	}
else
	{
	$output = "/tmp/systeminfo.txt";	# location for storage
	}
chdir "$openssl" or die "cannot chdir to $openssl: $!";

# print html begin
print "<HTML>\n";
print "<HEADER>\n";
print "<TITLE>yafra.org yet another pki</TITLE>\n";
print "<meta http-equiv=\"content-type\" content=\"text/html;charset=iso-8859-1\">\n";
print "<meta name=\"generator\" content=\"Perl\">\n";
print "<meta name=\"author\" content=\"mwn\">\n";
print "<link rel=\"SHORTCUT ICON\" href=\"http://www.yafra.org/favicon.ico\">\n";
print "<link rel=\"stylesheet\" href=\"/yapki.css\">\n";
print "</HEADER>\n";
print "<BODY>\n";

print "<h2>PKI action starting now!</h2>\n";
if ($fcmd eq "revoke")
	{
	print "Revoke certificate id $fsel<br>\n";
	&Frevoke;
	}
elsif ($fcmd eq "renew")
	{
	print "Renew certificate id $fsel<br>\n";
	&Frenew;
	}
elsif ($fcmd eq "update")
	{
	print "Update database<br>\n";
	&Fupdate;
	}
elsif ($fcmd eq "crl")
	{
	print "Generate CRL<br>\n";
	&Fcrl;
	}
elsif ($fcmd eq "details")
	{
	print "Detailed infos on selected certificate<br>\n";
	&Fdetails;
	}
else
	{
	print "Getting database infos<br>\n";
	&Finfo;
	}

# print html end
print "<P>\n";
print "PKI action done. You can navigate back.<P>\n";
print "Back to the <a href=\"/index.html\">root</A> or <a href=\"/admin/index.html\">admin</A> index.\n";
print "</BODY></HTML>\n";

# end

#
# local functions
#
sub Fcrl
	{
	$systemcall = sprintf ("openssl ca -gencrl -config $config -crldays $crldays -crlexts crl_ext -out $pkicrl -passin pass:\"$fpwd\"");
	system($systemcall);
	$systemcall = sprintf ("openssl crl -in CA_ROOT/crl/cayafra.crl -outform DER -out CA_ROOT/crl/cayafra-der.crl");
	system($systemcall);
	print "CRL done<br>\n";
	# copy file to web page of weblinux or yafra.ch
	$systemcall = sprintf ("cp CA_ROOT/crl/cayafra*.crl ../www/secure/.");
	system($systemcall);
	print "CRL published to https<br>\n";
	#print "Starting to put the crl to yafra.ch by ftp:<br>\n";
	#$ftp = Net::FTP->new($hostname);
	#$ftp->login($username, $pwd);
	#$ftp->cwd($location);
	#$ftp->put(CA_ROOT/crl/cayafra.crl);
	#$ftp->put(CA_ROOT/crl/cayafra-der.crl);
	#$ftp->quit;
	print "CRL published to www.yafra.ch<br>\n";
	}

sub Fupdate
	{
	$systemcall = sprintf ("openssl ca -updatedb -config $config -passin pass:\"$fpwd\"");
	system($systemcall);
	}

# process a new user request here

sub Frenew
	{
	# renew web server or p12
	#
	# needs 2 dates as input
	#
	#$systemcall = sprintf ("openssl ca -in yafra/certs/cert-id$1.csr -out yafra/certs/cert-id$1new.crt -startdate $2 -enddate $3 -policy policy_anything yafra/newcerts/$fsel.pem -config $config -passin pass:\"$fpwd\"");
	#system($systemcall);
	}

sub Frevoke
	{
	$systemcall = sprintf ("openssl ca -revoke CA_ROOT/newcerts/$fsel.pem -config $config -passin pass:\"$fpwd\"");
	system($systemcall);
	}

sub Fdetails
	{
	$systemcall = sprintf ("openssl x509 -in yafra/newcerts/$fsel.pem -noout -text > $output");
	system($systemcall);
	print "<p><b>certificate id $fsel details: ";
	print "<pre>";
	open (DETA,$output) || warn "could not open file $output for reading";
	while (<DETA>)
		{
		chomp;
		print "$_\n";
		}
	close(DETA);
	print "</pre><p>";
	}

sub Finfo
	{
	my $cstate = '';
	my $cexp = '';
	my $cend = '';
	my $cud = '';
	my $cloc = '';
	my $ctxt = '';
	my $date = '';
	
	print "<h3>yafra.org yapki: $pki</h3>\n";

	print "<p><b>next certificate id (hex): ";
	open (CNT,$pkicounter) || warn "could not open file $pkicounter for reading";
	while (<CNT>)
		{
		chomp;
		print "$_</b>\n";
		}
	close(CNT);

	print "<p>list of certificates from database:\n";

	print "<form name=\"mngcerts\" action=\"/perl-run/pki-mgmt.pl\" method=\"get\">\n";
	print "<table border=\"0\" frame=\"border\">\n";
	print "<tr style=\"background-color:CCFFFF;\"><td>select</td><td>id:</td><td>state:</td><td>end/valid till date:</td><td>common name:</td></tr>\n";
	open (IDX,$pkicerts) || warn "could not open file for reading";
	while (<IDX>)
		{
		chomp;
		if (/^R/) # revoked
			{
			($cstate, $cexp, $cend, $cid, $cloc, $ctxt) = split /\t+/, $_, 6;
			$date = &Fdate($cend);
			print "<tr><td>-</td><td>$cid</td><td>revoked</td><td>$date</td><td>$ctxt</td></tr>\n";
			}
		elsif (/^E/) # expired
			{
			($cstate, $cexp, $cid, $cloc, $ctxt) = split /\t+/, $_, 5;
			$date = &Fdate($cexp);
			print "<tr style=\"background-color:FFCCCC;\"><td><input type=\"radio\" name=\"sel\" value=\"$cid\"></td><td>$cid</td><td>expired</td><td>$date</td><td>$ctxt</td></tr>\n";
			}
		else # valid
			{
			($cstate, $cexp, $cid, $cloc, $ctxt) = split /\t+/, $_, 5;
			$date = &Fdate($cexp);
			print "<tr style=\"background-color:FFFFCC;\"><td><input type=\"radio\" name=\"sel\" value=\"$cid\"></td><td>$cid</td><td>valid</td><td>$date</td><td>$ctxt</td></tr>\n";
			}
		}
	close(IDX);
	print "</tr></table>\n";
	print "What to do with selection? <select name=\"cmd\" size=\"1\">";
	print "<option selected value=\"info\">info</option>";
	print "<option value=\"crl\">crl</option>";
	print "<option value=\"update\">update</option>";
	print "<option value=\"revoke\">revoke</option>";
	print "<option value=\"renew\">renew</option>";
	print "</select><br>\n";
	print "CA passphrase: <input type=\"password\" name=\"pwd\" size=\"35\"><br>\n";
	print 'press button to start command <input type="submit" name="commit" value="commit" tabindex="1">';
	print "</form>\n";
	}


sub Fdate
	{
	my ($input) = @_;
	my $output;
	my $yy;
	my $mt;
	my $dd;
	my $hh;
	my $min;
	
	$yy = substr $input, 0, 2;
	$mt = substr $input, 2, 2;
	$dd = substr $input, 4, 2;
	$hh = substr $input, 6, 2;
	$min = substr $input, 8, 2;
	
	$output = "$dd.$mt.20$yy $hh:$min";
	return($output);
	}
