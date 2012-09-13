#
# OUTstatistik Aktion exec script
#
# -m Medium (6 Datei, 1 Drucker)
# -S execution 4 manuell
# -t aktionstyp
# -A dla
# -E start time
# -e end time
#
echo @
echo start OUTstatistik
echo @
echo /usr/local/bin/OUTstatistik -d /usr/local/testdb2/DEMO -m 6 -S 4 -t 21 -A 240 -E 01.01.94 -e 31.12.94
echo @
/usr/local/bin/OUTstatistik -d /usr/local/testdb2/DEMO -m 1 -S 4 -t 21 -A 240 -E 01.01.94 -e 31.12.94
