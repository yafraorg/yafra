require 5.003;
use mplib;
use cgi;
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
$arrid = $cgiinput->param(mparrid);                           

#                                                            
# HTML Head                                                  
#                                                            
mpInitHtml(); 
print <<END;
<HEAD>
<TITLE>MARCO POLO TO Internet : private data</TITLE>
</HEAD>
END


#
# HTML Text and Registration
#

print <<END;
<H2>Enter data</H2>

END

print "\n<BR>\n";

print <<END;

<FORM NAME="myForm" METHOD="POST" ACTION="../mpto/mptraveller.pl"> 
<INPUT TYPE="hidden" NAME="mpdb" VALUE="$dbname">                                   
<INPUT TYPE="hidden" NAME="mpuser" VALUE="$dbuser">                                 
<INPUT TYPE="hidden" NAME="mppw" VALUE="$dbpw">                                     
<INPUT TYPE="hidden" NAME="mphost" VALUE="$dbhost">                                 
<INPUT TYPE="hidden" NAME="mpsid" VALUE="$sid">                                    
<INPUT TYPE="hidden" NAME="mpdlid" VALUE="$dlid">                                  
<INPUT TYPE="hidden" NAME="mparrid" VALUE="-1">                                    
<INPUT TYPE="hidden" NAME="mpkatid" VALUE="$katid">
<INPUT TYPE="hidden" NAME="sentinel_name" VALUE="">
<INPUT TYPE="hidden" NAME="sentinel_vor" VALUE="">
<PRE>
Please select you desired correspondence language   <SELECT NAME="language">   
<OPTION VALUE="english">English
<OPTION VALUE="french">French
<OPTION VALUE="german">German
<OPTION VALUE="spanish">Spanish
</SELECT><BR>
    
Company's name:     <INPUT NAME="mpkun_name" TYPE=TEXT SIZE=32 MAX=32>    
Company's address:  <INPUT NAME="mpkun_str" TYPE=TEXT SIZE=32 MAX=32>
Zip:     <INPUT NAME="mpkun_plz" TYPE=TEXT SIZE=6 MAX=6>  Place: <INPUT NAME="mpkun_ort" TYPE=TEXT SIZE=15 MAX 15>  Country: <SELECT NAME="mpkun_land" SIZE=1 ALIGN=CENTER WIDTH=10>
<OPTION SELECTED>Algeria
<OPTION>Andorra
<OPTION>Angola
<OPTION>Anguilla
<OPTION>Antigua
<OPTION>Argentina
<OPTION>Aruba
<OPTION>Australia
<OPTION>Austria
<OPTION>Azerbaijan
<OPTION>Bahamas
<OPTION>Bahrain
<OPTION>Bangladesh
<OPTION>Barbados
<OPTION>Belgium
<OPTION>Belize
<OPTION>Benin
<OPTION>Bermuda
<OPTION>Bhutan
<OPTION>Bolivia
<OPTION>Bonaire
<OPTION>Bosnia-Hercegovina
<OPTION>Botswana
<OPTION>Brazil
<OPTION>Brunei
<OPTION>Bulgaria
<OPTION>Burkina Faso
<OPTION>Burma
<OPTION>Burundi
<OPTION>Cameroon
<OPTION>Canada
<OPTION>Cayman Islands
<OPTION>Central African Rep
<OPTION>Chad
<OPTION>Chile
<OPTION>China
<OPTION>Colombia
<OPTION>Congo
<OPTION>Cook Islands
<OPTION>Costa Rica
<OPTION>Croatia
<OPTION>Cuba
<OPTION>Curacao
<OPTION>Cyprus
<OPTION>Czech Republic
<OPTION>Denmark
<OPTION>Djibouti
<OPTION>Dominica
<OPTION>Dominican Republic
<OPTION>Ecuador
<OPTION>Egypt
<OPTION>El Salvador
<OPTION>Estonia
<OPTION>Ethiopia
<OPTION>Fiji
<OPTION>Finland
<OPTION>France
<OPTION>French Guiana
<OPTION>French Polynesia
<OPTION>Gabon
<OPTION>Gambia
<OPTION>Georgia
<OPTION>Germany
<OPTION>Ghana
<OPTION>Gibraltar
<OPTION>Greece
<OPTION>Grenada
<OPTION>Guadeloupe
<OPTION>Guam
<OPTION>Guatemala
<OPTION>Guinea
<OPTION>Guinea Bissau
<OPTION>Guyana
<OPTION>Haiti
<OPTION>Honduras
<OPTION>Hong Kong
<OPTION>Hungary
<OPTION>Iceland
<OPTION>India
<OPTION>Indonesia
<OPTION>Iran
<OPTION>Iraq
<OPTION>Ireland
<OPTION>Israel
<OPTION>Italy
<OPTION>Ivory Coast
<OPTION>Jamaica
<OPTION>Japan
<OPTION>Jordan
<OPTION>Kazakhstan
<OPTION>Kenya
<OPTION>Kiribati/Gilbert Isl.
<OPTION>Kuwait
<OPTION>Kyrgyzstan
<OPTION>Latvia
<OPTION>Lebanon
<OPTION>Lesotho
<OPTION>Liberia
<OPTION>Libya
<OPTION>Liechtenstein
<OPTION>Lithuania
<OPTION>Luxembourg
<OPTION>Macau
<OPTION>Macedonia
<OPTION>Madagascar
<OPTION>Malawi
<OPTION>Malaysia
<OPTION>Maldives Islands
<OPTION>Mali
<OPTION>Malta
<OPTION>Martinique
<OPTION>Mauritania
<OPTION>Mauritius
<OPTION>Mexico
<OPTION>Micronesia/Marianas
<OPTION>Moldova
<OPTION>Monaco
<OPTION>Monserrat
<OPTION>Morocco
<OPTION>Mozambique
<OPTION>Namibia
<OPTION>Nepal
<OPTION>Netherlands
<OPTION>New Caledonia
<OPTION>New Zealand
<OPTION>Nicaragua
<OPTION>Niger
<OPTION>Nigeria
<OPTION>Norway
<OPTION>Pakistan
<OPTION>Palau (UN Territory)
<OPTION>Panama
<OPTION>Papua New Guinea
<OPTION>Paraguay
<OPTION>Peru
<OPTION>Philippines
<OPTION>Poland
<OPTION>Portugal
<OPTION>Puerto Rico
<OPTION>Qatar
<OPTION>Reunion Island
<OPTION>Romania
<OPTION>Russia
<OPTION>Rwanda
<OPTION>Saba
<OPTION>Samoa (USA)
<OPTION>Samoa (Western)
<OPTION>Sao Tome/Principe
<OPTION>Saudi Arabia
<OPTION>Senegal
<OPTION>Seychelles
<OPTION>Sierra Leone
<OPTION>Singapore
<OPTION>Slovakia
<OPTION>Slovenia
<OPTION>Solomon Islands
<OPTION>Somalia
<OPTION>South Africa
<OPTION>South Africa-Bophutha
<OPTION>South Africa-Transkei
<OPTION>South Korea
<OPTION>Spain
<OPTION>Sri Lanka
<OPTION>St Barthelemy
<OPTION>St Eustatius
<OPTION>St Helena
<OPTION>St Kitts-Nevis
<OPTION>St Lucia
<OPTION>St Maarten
<OPTION>St Martin
<OPTION>St Vincent &amp; Grenadines
<OPTION>Sudan
<OPTION>Surinam
<OPTION>Swaziland
<OPTION>Sweden
<OPTION>Switzerland
<OPTION>Syria
<OPTION>Taiwan
<OPTION>Tanzania
<OPTION>Thailand
<OPTION>Togo
<OPTION>Tonga
<OPTION>Trinidad/Tobago
<OPTION>Tunisia
<OPTION>Turkey
<OPTION>Turks/Caicos Islands
<OPTION>Uganda
<OPTION>Ukraine
<OPTION>United Arab Emirates
<OPTION>United Kingdom
<OPTION>Uruguay
<OPTION>USA
<OPTION>Uzbekistan
<OPTION>Vanuatu
<OPTION>Venezuela
<OPTION>Vietnam
<OPTION>Virgin Islands (UK)
<OPTION>Virgin Islands (USA)
<OPTION>Yemen
<OPTION>Yemen Arab Republic
<OPTION>Yugoslavia
<OPTION>Zaire
<OPTION>Zambia
<OPTION>Zimbabwe
</SELECT>
Phone:   <INPUT NAME="mpkun_tel" TYPE=TEXT SIZE=10 MAX=10>   Fax: <INPUT NAME="mpkun_fax" TYPE=TEXT SIZE=10 MAX=10>  e-mail: <INPUT NAME="mpkun_mail" TYPE=TEXT SIZE=15 MAX=15>

                                                day     month  year                             
Our client wants to travel from approximately : <SELECT Name="fday" SIZE= 1 ALIGN=CENTER WIDTH=2>
<OPTION VALUE=1>01 <OPTION VALUE=2>02 <OPTION VALUE=3>03 <OPTION VALUE=4>04     
<OPTION VALUE=5>05 <OPTION VALUE=6>06 <OPTION VALUE=7>07 <OPTION VALUE=8>08     
<OPTION VALUE=9>09 <OPTION VALUE=10>10 <OPTION VALUE=11>11 <OPTION VALUE=12>12  
<OPTION VALUE=13>13 <OPTION VALUE=14>14 <OPTION VALUE=15>15 <OPTION VALUE=16>16 
<OPTION VALUE=17>17 <OPTION VALUE=18>18 <OPTION VALUE=19>19 <OPTION VALUE=20>20 
<OPTION VALUE=21>21 <OPTION VALUE=22>22 <OPTION VALUE=23>23 <OPTION VALUE=24>24 
<OPTION VALUE=25>25 <OPTION VALUE=26>26 <OPTION VALUE=27>27 <OPTION VALUE=28>28 
<OPTION VALUE=29>29 <OPTION VALUE=30>30 <OPTION VALUE=31>31                     
</SELECT>  <SELECT Name="fmonth" SIZE= 1 ALIGN=CENTER WIDTH=2>                   
<OPTION VALUE=1>01 <OPTION VALUE=2>02 <OPTION VALUE=3>03 <OPTION VALUE=4>04     
<OPTION VALUE=5>05 <OPTION VALUE=6>06 <OPTION VALUE=7>07 <OPTION VALUE=8>08     
<OPTION VALUE=9>09 <OPTION VALUE=10>10 <OPTION VALUE=11>11 <OPTION VALUE=12>12  
</SELECT>  <SELECT Name="fyear" SIZE= 1 ALIGN=CENTER WIDTH=4>                    
<OPTION VALUE=1998>1998 <OPTION VALUE=1999>1999 <OPTION VALUE=2000>2000 <OPTION VALUE=2001>2001
</SELECT>
                                             
                        to stay approximately : <SELECT Name="tday" SIZE=1 ALIGN=CENTER WIDTH=2>
<OPTION VALUE=1>01 <OPTION VALUE=2>02 <OPTION VALUE=3>03 <OPTION VALUE=4>04                    
<OPTION VALUE=5>05 <OPTION VALUE=6>06 <OPTION VALUE=7>07 <OPTION VALUE=8>08                    
<OPTION VALUE=9>09 <OPTION VALUE=10>10 <OPTION VALUE=11>11 <OPTION VALUE=12>12                 
<OPTION VALUE=13>13 <OPTION VALUE=14>14 <OPTION VALUE=15>15 <OPTION VALUE=16>16                
<OPTION VALUE=17>17 <OPTION VALUE=18>18 <OPTION VALUE=19>19 <OPTION VALUE=20>20                
<OPTION VALUE=21>21 <OPTION VALUE=22>22 <OPTION VALUE=23>23 <OPTION VALUE=24>24                
<OPTION VALUE=25>25 <OPTION VALUE=26>26 <OPTION VALUE=27>27 <OPTION VALUE=28>28                
<OPTION VALUE=29>29 <OPTION VALUE=30>30 <OPTION VALUE=31>31  </SELECT> days                                  
                                             
                                                              <INPUT TYPE="submit" VALUE="Next"> 
</FORM>

<SCRIPT>
var today = new Date()
document.myForm.fday.selectedIndex=today.getDate()-1 
document.myForm.fmonth.selectedIndex=today.getMonth()
</SCRIPT>                                            



</PRE>
END

print "\n<HTML>\n";
exit;



