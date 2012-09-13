/*D***********************************************************
 * Modul:     API - get a KONTINGENT from dl/dla/dlt/kat
 *
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */
#include <mpsqlsel.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/SelectRECHST.c,v 1.2 2008-11-02 19:55:49 mwn Exp $";

int MPAPIselectRECHST(int bch_id, PERSONEN *Prechst)
{
	extern DIENST_ANGEBOT dla;
	extern DIENST_TRAEGER dlt;
	extern MEMOBJ apimem;
	extern char sqlquery[];

	int status=(int)MPOK;
	int anzahl;
	BUCHUNG bch;

	(void)MPAPIselectOneId((int)_BUCHUNG, bch_id, (char *)&bch);
	if (bch.bid == (int)_UNDEF)
		{
		return((int)MPE_NOBCH);
		}

	Prechst->pers_id = bch.kid;

	return(status);
}
