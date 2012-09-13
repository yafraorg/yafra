#
# OUTticket Aktion exec script
#
# -m Medium (6 Datei, 1 Drucker)
# -S execution 4 manuell
# -t aktionstyp
# -c teil dl       39 :  Nr 6 Syrien Tuerkei     (b 22)
#                  77 :  Nr 8 Ostern
#                   1 :  17 Insel Festival
#

echo @
echo start OUTticket
echo @

#echo " Buchung?: "
#read ANSWER

#echo "-d demodb -l 1 -m 5 -S 4 -t 5 -b 7 -c 39 -H lisa"
#/work/bin/OUTticket -d demodb -l 1 -m 5 -S 4 -t 5 -b 7 -c 39 -H lisa

# echo "-d /database/festivaldb/FESTIVAL -m 5 -S 4 -t 5 -b 138 -c 1 -Z 1 -H lisa"
# /work/bin/OUTticket -d /database/festivaldb/FESTIVAL -m 5 -S 4 -t 5 -b 138 -c 1 -Z 1 -H lisa

echo "-d /database/festivaldb/FESTIVAL -m 5 -S 4 -t 5 -b 139 -c 39 -Z 1 -H lisa"
/work/bin/OUTticket -d /database/festivaldb/FESTIVAL -m 5 -S 4 -t 5 -b 138 -c 39 -Z 1-H lisa
