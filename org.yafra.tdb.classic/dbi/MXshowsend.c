/*D***********************************************************
 * Modul:     DBI - matrix
 *            send show mode matrix
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/MXshowsend.c,v 1.2 2008-11-02 19:55:40 mwn Exp $";

int MXshowsend(int len, char *buffer)
{
	int status = (int)MPOK;

	/*!!! in future make difference between MENUNR */

	status = DLAmatrix(len, buffer);

	return(status);
}
