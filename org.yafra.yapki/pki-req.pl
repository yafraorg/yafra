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
# function:	manage request from client
#
# argument: cmd, act
#
# supported commands: info
#
# needed modules: CGI
#
# CVS tag:   $Name:  $
# author:    $Author: mwn $
# revision:  $Revision: 1.4 $
#-------------------------------------------------------------------------------

use strict;
use CGI;
use File::Temp qw/ :mktemp  /;

#use Mime::Lite;
#my $endMail = new MIME::Lite;

my $certfile = mktemp("yafra-certXXXXX");
my $req_file = "$certfile.req";
my $req_info_file = "$certfile.txt";
my $req_bat_file = "$certfile.sh";

my $query = new CGI;

my $femail = $query->param('emailAddress');
my $fcn = $query->param('commonName');
my $fou = $query->param('organizationalUnitName');
my $fo = $query->param('organizationName');
my $fl = $query->param('localityName');
my $fs = $query->param('stateOrProvinceName');
my $fc = $query->param('countryName');
my $ftype = $query->param('enroll_track');
my $req = $query->param('public_key');

#process request
unless($req) { fail("No Certificate Request Provided"); }
if ($ftype eq "Netscape")
	{
	# control M's replacing with newline and backslash
	$req =~ s/\r/\\/g ;

	# save the certificate request to a file, as received
	open(REQ, ">$req_file") or fail("Could no save certificate request to file");
#	my $result = 1;
#	while($result)
#		{
#		$result = substr($req, 0, 72);
#		if($result)
#			{
#			print REQ "$result\n";
#			$req = substr($req, 72);
#			}
#		}
	print REQ "SPKAC=$req\n";
	print REQ "CN=$fcn\n";
	print REQ "emailAddress=$femail\n";
	print REQ "0.OU=$fou\n";
	print REQ "O=$fo\n";
	print REQ "L=$fl\n";
	print REQ "S=$fs\n";
	print REQ "C=$fc";
	close(REQ);

	# create batch file to process
	open(PKIBAT, ">$req_bat_file") or fail("Could not generate batch file");
	print PKIBAT "#!/bin/sh\n";
	print PKIBAT "# (c) yafra.org - netscape style\n";
	print PKIBAT "# openssl spkac -in $certfile.req -verify\n";
	print PKIBAT "# openssl ca -config openssl.cnf -spkac $certfile.req -out $certfile.crt -startdate 050620085410Z -enddate 060620085410Z -policy policy_anything\n";
	print PKIBAT "openssl ca -config openssl.cnf -spkac $certfile.req -out $certfile.crt -days 720 -policy policy_anything\n";
	print PKIBAT "openssl crl2pkcs7 -nocrl -certfile $certfile.crt -outform DER -out $certfile.cer\n";
	close(PKIBAT);
	}
else
	{
	# control M's replacing with newline and backslash
	$req =~ s/\r//g ;
#	$req =~ s/([^\n]{72,72})\n([^\n]{1,71})\n([^\n]{1,71})$/$1\n$2$3/ ;
#	$req =~ tr/
#	//d;
#	$req =~ tr/\n//d;

	# save the certificate request to a file, as received
	open(REQ, ">$req_file") or fail("Could no save certificate request to file");
	print REQ "-----BEGIN CERTIFICATE REQUEST-----\n";
	print REQ "$req";
	print REQ "-----END CERTIFICATE REQUEST-----\n";
	close(REQ);

	# create batch file to process
	open(PKIBAT, ">$req_bat_file") or fail("Could not generate batch file");
	print PKIBAT "#!/bin/sh\n";
	print PKIBAT "# (c) yafra.org - msie style\n";
	print PKIBAT "# openssl req -in $certfile.req -text -verify\n";
	print PKIBAT "# openssl ca -config openssl.cnf -in $certfile.req -out $certfile.crt -startdate 050620085410Z -enddate 060620085410Z -policy policy_anything\n";
	print PKIBAT "openssl ca -config openssl.cnf -in $certfile.req -out $certfile.crt -days 720 -policy policy_anything\n";
	print PKIBAT "openssl crl2pkcs7 -nocrl -certfile $certfile.crt -outform DER -out $certfile.cer\n";
	close(PKIBAT);
	}

# print HTML header
$| = 1; # for flushing
print "Content-type: text/html\n\n";


# create info file to store some meta data
open(REQI, ">$req_info_file") or fail("Could no save certificate info to file");
print REQI "---------- CERTIFICATE INFO --------------\n";
print REQI "CN: $fcn\n";
print REQI "Email address: $femail\n\n";
print REQI "OU: $fou\n";
print REQI "O: $fo\n";
print REQI "L: $fl\n";
print REQI "S: $fs\n";
print REQI "C: $fc\n\n";
print REQI "Original sequence no: $certfile\n";
print REQI "This file name: $req_info_file\n";
print REQI "Browser: $ftype\n";
print REQI "-----------END CERTIFICATE INFO -----\n";
close(REQI);

print <<_END_TEXT_;
<HTML>
<HEAD>
<title>Your certificate for yafra.org</title>
<link rel="stylesheet" href="http://www.yafra.org/yafra.css">
</HEAD>
<BODY>
Your certificate request is in progress. You will receive your certificate as
soon as it is verified. Browser used $ftype
<BR>
Your certificate request is stored as: $req_file
<BR>
It will be sent to the following email address: $femail
<P>
Dein Zertifikat wird gepr&uuml;ft! Du erh&auml;lst das Zertifikat für Outlook und InternetExplorer
sobald es verifiziert wurde.
<BR>
Dein Zertifikat ist mit folgender ID gespeichert: $req_file
<BR>
Es wird an folgende email gesendet: $femail
<p>
<a href="/ssl/index.html">BACK / ZURUECK</a>
</BODY>
</HTML>
_END_TEXT_

#my $tomail="info\@yafra.org" ;
#open(MAIL , "| /usr/sbin/sendmail -t");
#$mailmsg = build MIME::Lite
#        From    => $tomail,
#        To      => $tomail,
#        Subject => "Certificate Request",
#        Type    => 'TEXT',
#        Data    => "Es liegt ein neuer cert request vor von $fcn !";
#$msg->print(\*MAIL);
#close(MAIL);
#open (MAIL, "¦ /usr/sbin/sendmail -t");
#print MAIL "Content-Type: text/html\n";
#print MAIL "To: $tomail\n";
#print MAIL "From: info\@yafra.org\n";
#print MAIL "Subject: cert req\n\n";
#print MAIL "Ein cert liegt vor\n";
#close MAIL;

exit(0);
#
# END
#

sub fail
{
	my($msg, $errs) = @_;

	print $query->header;
	print $query->start_html(-title => "Certificate Request Failure"); 
	print "<H2>Certificate request failed</H2>$msg<P>";
	print $query->dump();
	print $query->end_html();
	exit(0);
}
#
#1;
