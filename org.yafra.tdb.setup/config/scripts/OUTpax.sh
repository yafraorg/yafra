#
# OUTpassagier Aktion exec script
#
# -L dialogsprache
# -l outputsprache (forcing)
# -m Medium ( 1 Drucker, 5 Bilschirm, 6 Datei, 9 Drucker4 )
# -H Host fuer display Umlenkung
# -S execution 4 manuell
# -t aktionstyp
# -c teil dl  (39 Nr 6 Syrien Turkei)
# -s dl       (39 Nr 6 Syrien Turkei)
# -a arrgt    
#
echo @
echo start OUTpassagier
echo @
#echo " -L 1 -l 3 -d demodb -m 5 -S 4 -t 3 -H lisa -a 3 -Z 6 "
#/work/bin/OUTpassagier -L 1 -l 3 -d /usr/local/demodb/DEMO -m 5 -S 4 -t 3 -H lisa -a 3 -Z 6


echo " -L 1 -l 3 -d /database/festivaldb/FESTIVAL -m 5 -S 4 -t 3 -H lisa -a 48 -Z 6"
/work/bin/OUTpassagier -L 1 -l 3 -d /database/festivaldb/FESTIVAL -m 5 -S 4 -t 3 -H mips -a 1 -Z 6

# /work/bin/OUTpassagier -X -l 3 -L 1 -d mapo -m 5 -S 4 -t 3 -H cure -z 5 -Z 1 -a 2
