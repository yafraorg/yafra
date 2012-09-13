#!/bin/sh
#------------------------------------------------------------------------------
# yafra.org      Langenhagstrasse 1     CH-4147 Aesch   +41(0)61 7564444
# info@yafra.org
#
# Function:   bytes
#
# Descripton: 1. bdf 2. du -ks ueber das Homeverzeichnis exkl. softech
#             3. du -ks ueber das Softechverzeichnis. Die gesamten
#             Informationen werden in ein File umgeleitet.
#
# Author:     Roland Haas
#
# Date:       10.01.1997
#
#
#------------------------------------------------------------------------------

echo "Free disk space"
echo "==============="
bdf

#
echo "\n\nHome-Directory"
echo "=============="
cd /home
for i in `ls`
	do
	if [ $i != "softech" ]
	then
		du -ks $i/.
	fi
done

echo "\n\nSoftech-Directory"
echo "================="
cd /home/softech
for i in `ls`
    do
    du -ks $i
done

