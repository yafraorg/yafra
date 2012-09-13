#!/usr/remote/bin/perl 
require 5.003;         
use mplib;             
use cgi;               
#use strict;

$cgiinput = new CGI;

$dbsex = $cgiinput->param(sex);

#
#  Test Test-Ausgabe
#

print "Content-type: text/html\n\n";                         
print '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2//EN">';   
print "\n\n";                                                
print "<HTML>\n";    

print  <<END;
<H2>Test</H2>
Das Geschlecht ist <B>$dbsex</B>
END

print "</HTML>";

exit;

