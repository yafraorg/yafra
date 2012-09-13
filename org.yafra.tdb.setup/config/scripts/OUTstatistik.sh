#
# OUTstatnew Aktion exec script
#
# -m Medium (6 Datei, 1 Drucker)
# -S execution 4 manuell
# -t aktionstyp
# -A dla
# -E start time
# -e end time
#
echo @
echo start OUTstatnew
echo @
echo /usr/local/bin/OUTstatistik -d /usr/local/testdb2/DEMO -m 5 -S 4 -t 21 -A 240 -E 01.01.94 -e 31.12.94 -H rx700
echo @
/usr/local/bin/OUTstatistik -d /usr/local/testdb2/DEMO -m 5 -S 4 -t 21 -A 240 -E 01.10.94 -e 31.12.94 -H rx700
