#
# OUTauftrag Aktion exec script
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
# -c teil dl
#
echo @
echo start OUTauftrag
echo @
echo /usr/local/bin/OUTfaktura -d /usr/local/testdb2/DEMO -m 5 -S 4 -t 7 -b 21
echo @
#/usr/local/bin/OUTauftrag -d /usr/local/testdb2/DEMO -m 6 -S 4 -t 7 -c 529

/usr/local/bin/OUTfaktura -d /usr/local/testdb2/DEMO -m 5 -S 4 -t 7 -b 21 
