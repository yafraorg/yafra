 #
# OUTprognew  Aktion exec script
#
# _DEVPRINTER           1  /* Druckerausgabe                */
# _DEVFAX               2  /* FAX-Ausgabe                   */
# _DEVTELEX             3  /* Telexausgabe                  */
# _DEVMODEM             4  /* MODEM-Ausgabe                 */
# _DEVSCREEN            5  /* Bildschirmausgabe via devedit */
# _DEVFILE              6  /* Ausgabe in Datei              */
# _DEVPRINTER2          7  /* Drucker 2                    */
# _DEVPRINTER3          8  /* Drucker 3                    */
# _DEVPRINTER4          9  /* Drucker 4                    */

#
# -m Medium      (6 Datei, 1 Drucker)
# -S execution   (4 manuell )
# -t aktionstyp  (a_typ_id)
# -b buchung
# -c teil_dl     (547 Novatour bus, 529 Griechenland) 
#
# 
echo @
echo start OUTprogram
echo @
#/usr/local/bin/OUTprogram -d /usr/local/testdb2/DEMO -m 5 -S 4 -t 4 -c 529 -b 1

#--- Kreuzfarht mit Unterbruch 
#/usr/local/bin/OUTprogram -d /usr/local/testdb2/DEMO -m 5 -S 4 -t 4 -c 529 -b 20

#--- Gruppe Schweitzer  NOT OK !!
#/usr/local/bin/OUTprogram -d /usr/local/testdb2/DEMO -m 5 -S 4 -t 4 -c 529 -g 1


# force languages to french
#/usr/local/bin/OUTprogram -L 2 -l 2 -d /usr/local/testdb2/DEMO -m 5 -S 4 -t 4 -b 1 -c 529 -H Flop

echo " Booking number?: "
read ANSWER
/usr/local/bin/OUTprogram -d /usr/local/festivaldb/FESTIVAL -m 5 -S 4 -t 4  -c 1 -b $ANSWER






