#
# OUTfaktura Aktion exec script
#
# -m Medium (6 Datei, 1 Drucker)
# -S execution 4 manuell
# -t aktionstyp        (akttid)   20=Festival actions 
#                                  6=Festival Rechnung
# -c teil dl           (tdlid)    529=Griechen Ven-Ven
#                                 39 =Nr 6 
#                                  1 =Insel festival 
# -g gruppe kollektiv  (kolid)
#
echo @
echo Start OUTfaktura test 
echo 
#/work/bin/OUTfaktura -d demodb -m 5 -S 4 -t 20 -c 529 2> /tmp/OUT_fakgrp


#echo " Booking number?: "
#read ANSWER
#/work/bin/OUTfaktura  -f 1 -d demodb -m 5 -S 4 -t 6 -c 39 -b $ANSWER

/work/bin/OUTfaktura -f 1 -X -L 1 -d /database/mapodemodb/DEMO -m 1 -S 4 -t 6 -H mips -z 8 -Z 7 -c 1
#/work/bin/OUTfaktura  -f 1 -d /database/festivaldb/FESTIVAL -m 5 -S 4 -t 6 -c 1 -b 138


# Tests
#=========================================
#--- Kreuzfarht mit Unterbruch 

#--- Dynamic Hotel 

#--- French Kunde 

#--- Commissioned normal Kom 

#--- Commissioned %

#--- Ubersteurung dynamic hotel 10 days

#--- Gruppe Schweitzer  
#/usr/local/bin/OUTfaktura -d /usr/local/demodb/DEMO -m 5 -S 4 -t 6 -g 1 -c 529
