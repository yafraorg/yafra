#
# OUTrevenu Aktion exec script
#
# -m Medium (6 Datei, 1 Drucker)
# -S execution 4 manuell
# -t aktionstyp
# -c teil dl       39 :  Nr 6 Syrien Tuerkei     (b 22)
#                  77 :  Nr 8 Ostern
#                   1 :  17 Insel Festival
#                 230 :  21 Insel Festival
#

echo @
echo start OUTrevenu
echo @

#echo " Buchung?: "
#read ANSWER

#echo "-d demodb -l 1 -m 5 -S 4 -t 5 -b 7 -c 39 -H lisa"
#/work/bin/OUTrevenu -d demodb -l 1 -m 5 -S 4 -t 5 -b 7 -c 39 -H lisa

echo "-d /database/festivaldb/FESTIVAL -l 1 -m 5 -S 4 -t 5 -b 138 -c 230 -H lisa"
/work/bin/OUTrevenu -d /database/festival/FESTIVAL -l 1 -m 5 -S 4 -t 5 -c 230 -g 25 -H mips
#/work/bin/OUTrevenu -d /database/mapodemodb/DEMO -l 1 -m 5 -S 4 -t 5 -c 60 -H mips
