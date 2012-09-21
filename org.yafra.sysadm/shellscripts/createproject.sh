#
# creation script for programs or libraries
# shell script for sh
#
# autor: Administrator, yafra.org
#

# title
echo ' '
echo 'create new project'
echo ' '

# ask for name
echo 'enter name (use ascii letters only and no blanks):'
read PRJNAME
if [ "$PRJNAME" = "" ];
	then exit
fi
echo ' '
echo 'project name is org.yafra.$PRJNAME'

# ask for type (prg or lib)
echo 'type of project (p -> prg | l -> lib/jar/module):'
read PRJTYP
if [ "$PRJTYP" = "" ];
	then exit
fi
echo ' '

# setting up
echo "Project $PRJNAME of type $PRJTYP will created"
echo ' '
PRJPATH=$BASENODE/$PRJNAME
echo "create sub directories within $PRJPATH"
mkdir $PRJPATH
mkdir $PRJPATH/source
mkdir $PRJPATH/include
echo 'copy templates'
if [ "$PRJTYP" = "p" ];
	then
		cp $SYSADM/defaults/makefile.prg $PRJPATH/makefile
	else
		cp $SYSADM/defaults/makefile.lib $PRJPATH/makefile
	fi
fi

# send e-mail to yafraorg
echo 'Project creation' > /tmp/creatprjmail
echo '=================' >> /tmp/creatprjmail
echo "Name: $PRJNAME" >> /tmp/creatprjmail
echo "Type:  $PRJTYP" >> /tmp/creatprjmail
echo "User: $USER" >> /tmp/creatprjmail
#mail root < /tmp/creatprjmail
rm /tmp/creatprjmail
echo ' '
echo 'mail sent'
