#
# OUTmanifest Aktion exec script
#
# -m Medium (6 Datei, 1 Drucker)
# -S execution 4 manuell
# -t aktionstyp
# -c teil dl
#
echo @
echo start OUTmanifest
echo @
echo /usr/local/bin/OUTmanifest -d /usr/local/testdb2/DEMO -m 6 -S 4 -t 9 -c 529
echo @
/usr/local/bin/OUTmanifest -d /usr/local/testdb2/DEMO -m 6 -S 4 -t 9 -c 529
