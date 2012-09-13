/*D***********************************************************
 * Modul:     DBI - matrix
 *            send show mode matrix
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/MXbinarysend.c,v 1.2 2008-11-02 19:55:35 mwn Exp $";

int MXbinarysend(int len, char *buffer)
{
	char *ptr;
	int kat_id, dl_id;

	/*!!! in future make difference between MENUNR */

	(void)DLAmatrix(len, buffer);

	return(MPOK);
}
