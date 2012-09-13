#
# OUTorder control Aktion exec script
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
echo start OUTorder
echo @

echo " Source Status?: "
read ANSWER1
echo " Target Status?: "
read ANSWER2

/work/bin/OUTorder  -X -L 1 -d /database/festivaldb/FESTIVAL -m 5 -S 4 -t 31 -H mips -Z $ANSWER1 -z $ANSWER2

#/work/bin/OUTorder -X -L 1 -d demodb -m 5 -S 4 -t 31 -H lisa -Z $ANSWER1 -z $ANSWER2
