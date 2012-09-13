#
# OUToption control Aktion exec script
#
# -m Medium (6 Datei, 1 Drucker)
# -S execution 4 manuell
# -Z source reservation state
# -z target reservation state
# -t aktionstyp
# -s dl
# -b buchung
#

echo @
echo start OUToption
echo @

/work/bin/OUToption -L 1 -d /database/mapodemodb/DEMO -m 5 -S 4 -t 33 -H mips -Z 6 -z 6

#/work/bin/OUToption -X -L 1 -d demodb -m 5 -S 4 -t 31 -H lisa -Z $ANSWER1 -z $ANSWER2
