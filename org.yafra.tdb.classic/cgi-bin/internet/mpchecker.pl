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
<TITLE>MARCO POLO TO Internet : Check for Company or Booker</TITLE> 
</HEAD>
END

print <<END;
<BODY BGCOLOR="#FFFFFF">
END
print <<END;

<SCRIPT>
function cButton() {
	document.checker.method="POST"
   document.checker.action="../mpto/mpcompany.pl"
   document.checker.submit()
}
function pButton() {
   document.checker.method="POST"                	
   document.checker.action="../mpto/mpprivate.pl" 
   document.checker.submit()                     
}
</SCRIPT>

<FONT FACE="Arial"><P ALIGN="CENTER"><BR><BR><BR><BR></P>                         
<FORM NAME="checker">
<P ALIGN="CENTER"><CENTER>                                                     
<TABLE BORDER=10 CELLSPACING=1 BORDERCOLOR="#000000" CELLPADDING=15 WIDTH=420> 
   <TR><TD VALIGN="MIDDLE" COLSPAN=4 HEIGHT=26>                                
      <P ALIGN="CENTER"><FONT FACE="Arial">Are You</FONT></TD>                 
   </TR>                                                                       
   <TR><TD WIDTH="50%" VALIGN="MIDDLE" COLSPAN=2 HEIGHT=26>                    
      <P ALIGN="CENTER">                                                       
      <INPUT TYPE="radio" NAME="checkButton" VALUE="company" onClick="cButton()">             
      <FONT FACE="Arial">A Retailer ?</FONT></TD>                               
      <TD WIDTH="50%" VALIGN="MIDDLE" COLSPAN=2 HEIGHT=26>                     
      <P ALIGN="CENTER">                                                       
      <INPUT TYPE="radio" NAME="checkButton" VALUE="private" onClick="pButton()">                     
      <FONT FACE="Arial">A Private Person ?</FONT></TD>                                
   </TR>                                                                       
</TABLE><BR><BR><BR>                                                           
</FROM>
<BR><BR><BR>
Select/click your choice with the radio button
</CENTER></P>                                                                     

END

print "\n<HTML>\n";
exit










