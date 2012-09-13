#
# OUTstatdlt Aktion exec script
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
# -h dlt
# -K kat
# -c tdl
#
echo @
echo start OUTstatdlt
echo @
echo /usr/local/bin/OUTdltusage -L 1 -d /usr/local/testdb2/DEMO -m 6 -S 4 -t 23 -h 11515 -K 96
echo @
/usr/local/bin/OUTdltusage -L 1 -d /usr/local/testdb2/DEMO -m 6 -S 4 -t 23 -h 11515
