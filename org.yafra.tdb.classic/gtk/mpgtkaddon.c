/*D***********************************************************
 * Modul:     GTK GUI support functions
 *            travelDB light server in C with own protocol
 *            or XML or WebServices
 *
 * Copyright: yafra.org, Switzerland, 2004
 *
 * PISO SCM:  TAG $Name:  $
 * Author:    $Author: mwn $
 * Revision:  $Revision: 1.3 $
 **************************************************************/

/* RCS static ID */
static char rcsid[]="$Id: mpgtkaddon.c,v 1.3 2008-11-23 15:44:38 mwn Exp $";
static char tagid[]="$Name:  $";


/* MARCO POLO API includes */
#include <mpgtk.h>

/* finish */
void MPGTKexit(int exitcode)
{
	extern int DebugFlag;
	extern int MPNETstate;
	extern int ipcfd;

	if (DebugFlag)
		PSSYSdebug(MPGTK_DBGFILE, NULL, "exit confirmed with code %d and MPNETstate %d", exitcode, MPNETstate);

	(void)PSIPCsocketclose(ipcfd);

	gtk_main_quit();

	(void)MPXMLclose();

	exit(exitcode);
}
