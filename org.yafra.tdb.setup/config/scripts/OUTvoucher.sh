#
# OUTvoucher Aktion exec script
#
# -m Medium (6 Datei, 1 Drucker)
# -S execution 4 manuell
# -t aktionstyp
# -c teil dl    (529 Griechenland, 543 Transferbus)
#
echo @
echo start OUTvoucher
echo @
echo /usr/local/bin/OUTvoucher -d /usr/local/testdb2/DEMO -m 6 -S 4 -t 22 -c 529
echo @
#/usr/local/bin/OUTvoucher -d /usr/local/testdb2/DEMO -m 5 -S 4 -t 22 -c 529 -H flop

# /usr/local/bin/OUTvoucher -d /usr/local/testdb2/DEMO -m 5 -S 4 -t 22 -c 542 -H flop
/usr/local/bin/OUTvoucher -d /usr/local/testdb2/DEMO -m 5 -S 4 -t 22 -c 529 -H flop

# /usr/local/bin/OUTvoucher -d /usr/local/testdb2/DEMO -m 5 -S 4 -t 22 -c 543 
