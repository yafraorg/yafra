#
# OUTcontrol Aktion exec script
#
# _DEVPRINTER           1  /* Druckerausgabe                */
# _DEVFAX               2  /* FAX-Ausgabe                   */
# _DEVTELEX             3  /* Telexausgabe                  */
# _DEVMODEM             4  /* MODEM-Ausgabe                 */
# _DEVSCREEN            5  /* Bildschirmausgabe via psedit  */
# _DEVFILE              6  /* Ausgabe in Datei              */
#
# -d databank location 
# -m Medium      (6 Datei, 1 Drucker)
# -S execution   (4 manuell )
# -t aktionstyp  (a_typ_id)
#
# -z target reservation state
# -s dl
# -b buchung
#

echo @
echo start OUTcontrol
echo @

echo " Source Status?: "
read ANSWER1
echo " Target Status?: "
read ANSWER2

#/usr/local/bin/OUTcontrol -X -L 1 -d /usr/local/festivaldb/FESTIVAL -m 5 -S 4 -t 10 -H lisa -z 10 -Z 2 -c 39 -b $ANSWER
/usr/local/bin/OUTcontrol -X -L 1 -d /usr/local/demodb/DEMO -m 5 -S 4 -t 10 -H lisa -Z $ANSWER1 -z $ANSWER2
