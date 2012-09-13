#
# OUTrequest Aktion exec script
#
#
# -m Medium     (1 Drucker, 2 Fax, 3 Telex, 4 Modem, 5 Bildschirm, 6 Datei )
# -S execution  (4 manuell)
# -z target reservation state
# -t aktionstyp       2 Anfrage
#                    28 Modifikation
# 
# -s dl            17 = Nr 6
# 
# -b buchung
#

#define SUB_REQUEST	    1
#define SUB_MODIF	       2
#define SUB_RECONF	    3
#define SUB_CANCEL	    4

echo @
echo start OUTrequest 
echo @
echo " Parameter?: 1=request,  2=modif,  3=reconf,  4=cancel "
read ANSWER

/work/bin/OUTrequest -X -d /database/festivaldb/FESTIVAL -f $ANSWER -m 5 -S 4 -t 28 -s 17 -b 139

#/work/bin/OUTrequest -X -d demodb -f $ANSWER -m 5 -S 4 -t 28 -s 17 -b 139


#--- automatic
#/usr/local/bin/OUTrequest -D -b 999 -s 999 [-R] [-D]
