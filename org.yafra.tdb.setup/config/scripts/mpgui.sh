#! /bin/sh
#-------------------------------------------------------------------------------
# yafra.org, Switzerland, www.pisoag.com
#
# Function: shell script fuer MARCO POLO
#
# Author:   Administrator
#
# Date:     21.11.94
#-------------------------------------------------------------------------------
#
# Last Modified:
# mw 11.3.2002 updated for final v5.00 release
#-------------------------------------------------------------------------------

#
# setup .mpgui or /etc/mpgui.pro with your database connect string and user/pwd
#
# setup X11 environment for MAPO Classic
#
# setup /etc/services with 5000/tcp marcopolo for daemon
#
# arguments:
# -D		debug on
# -s servername	where is the MARCO POLO mpdbi server located
# -G		enable graphic module
# -A		enable sound module
# -p		preload menus into memory for fast execution
# +g no		enable menu number (1-6)
# -a
# -o no		set options for startup

MAPOBIN=/work/mapo/v5.00/bin
MAPODBI=yourserver

$MAPOBIN/mpgui -s $MAPODBI  -G -o 1 -o 2 -o 3 -o 4 -o 6
