#
# OUTpaxbus Aktion exec script
#
# -L dialogsprache
# -l outputsprache (forcing)
# -m Medium ( 1 Drucker, 5 Bilschirm, 6 Datei, 9 Drucker4 )
# -H Host fuer display Umlenkung
# -S execution 4 manuell
# -t aktionstyp
# -c teil dl   (39 Nr 6 Syrien Turkei)
# -s dl        (39 Nr 6 Syrien Turkei)
# -a arrgt     ( 3 Nr 6 Syrient Turkey)
#
echo @
echo start OUTpaxbus
echo @
# echo " -L 1 -d demodb -m 5 -S 4 -t 32 -H lisa -a 3 -s 24 "
# /usr/local/bin/OUTpaxbus -L 1 -d demodb -m 5 -S 4 -t 32 -a 3 -s 24 -H lisa


echo " -L 1 -d /database/festivaldb/FESTIVAL -m 5 -S 4 -t 34 -H lisa -a 3 -s 42 "
/work/bin/OUTpaxbus -L 1 -d /database/festivaldb/FESTIVAL -m 5 -S 4 -t 34 -a 3 -s 42 -H lisa
