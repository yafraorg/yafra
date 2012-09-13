#
# OUTkomm Aktion exec script
#
# -L dialogsprache
# -l outputsprache (forcing)
# -m Medium    (1 Drucker, 5 Bilschirm, 6 Datei, 9 Drucker4 )
# -H Host fuer display Umlenkung
# -S execution 4 manuell
# -t aktionstyp
# -c teil dl   (39 Nr 6 Syrien Turkei)
# -s dl        (39 Nr 6 Syrien Turkei)
# -a arrgt  
#
echo @
echo start OUTkomm
echo @
# echo " -L 1 -d demodb -m 5 -S 4 -t 33 -H lisa -a 3"
# /work/bin/OUTkomm -L 1 -d demodb -m 5 -S 4 -t 33 -H lisa -a 3


echo " -L 1 -d /database/festivaldb/FESTIVAL -m 5 -S 4 -t 33 -H lisa -a 48"
/work/bin/OUTkomm -L 1  -d /database/festivaldb/FESTIVAL -m 5 -S 4 -t 33 -H lisa -a 48
