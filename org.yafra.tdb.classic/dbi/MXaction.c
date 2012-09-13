/*D***********************************************************
 * Modul:     DBI - matrix
 *            perform an action from a cell of the matrix
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/MXaction.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

int MXaction(int len, char *buffer)
{
	extern BUCHUNG bch;

	int status = (int)MPOK;
	int tdlid, katid, bchid, kontid;
	char bez[_RECORDLEN];
	char *ptr;

	/* init */
	ptr = buffer;

	/*!!! in future make difference between MENUNR */

	/* process DLA detailed info */
	/* cut buffer here and get all needed infos (tdl,kat,bch,kont) */

	/* TDL */
	*bez = NULL;
	(void)sscanf(ptr, "%[^\t]", bez);
	ptr += (strlen(bez) + 1);

	/* KAT */
	*bez = NULL;
	(void)sscanf(ptr, "%[^\t]", bez);
	ptr += (strlen(bez) + 1);

	/* BCH and KONT */
	*bez = NULL;
	(void)sscanf(ptr, "%[^\t]", bez);
	if (*bez != NULL)
		{
		bchid = atoi(bez);
		(void)MPAPIselectOneId((int)_BUCHUNG, bchid, (char *)&bch);
		if (bch.bid == (int)_UNDEF)
			{
			UtilMsg((int)MPE_NOBCH, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}

		/* print res info: */
		status = RESinfo(len, buffer);
		COMMTYP = (unsigned char)INFO;
		}

	return(status);
}
