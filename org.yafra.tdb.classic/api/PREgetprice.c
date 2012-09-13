/*D***********************************************************
 * Modul:     DBI - Preis
 *            get a price for an object and print it to a
 *            buffer with currency signs
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/PREgetprice.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";

#define _SEL_PRE_KAT_DLA "SELECT * FROM TDBADMIN.PREIS P \
	WHERE P.KAT_ID = %d AND P.DLA_ID = %d;"
#define _SEL_PRE_KAT_DLA_DL "SELECT * FROM TDBADMIN.PREIS P \
	WHERE (P.KAT_ID = %d OR P.KAT_ID = -1) \
	AND (P.DL_ID = %d OR P.DLA_ID = %d) \
	ORDER BY P.DLA_ID, P.KAT_ID DESC;"
#define _SEL_PRE_KAT_DL "SELECT * FROM TDBADMIN.PREIS P \
	WHERE P.KAT_ID = %d AND P.DL_ID = %d;"
#define _SEL_PRE_KAT "SELECT * FROM TDBADMIN.PREIS P \
	WHERE P.KAT_ID = %d;"


#define _SEL_PRE_KAT_DLNT_DLA "SELECT * FROM TDBADMIN.PREIS P \
	WHERE P.KAT_ID = %d AND P.RKR_ID = %d AND P.DLA_ID = %d;"
#define _SEL_PRE_KAT_DLNT_DLA_DL "SELECT * FROM TDBADMIN.PREIS P \
	WHERE (P.KAT_ID = %d OR P.KAT_ID = -1) AND P.RKR_ID = %d \
	AND (P.DL_ID = %d OR P.DLA_ID = %d) \
	ORDER BY P.DLA_ID, P.KAT_ID DESC;"
#define _SEL_PRE_KAT_DLNT_DL "SELECT * FROM TDBADMIN.PREIS P \
	WHERE P.KAT_ID = %d AND P.RKR_ID = %d AND P.DL_ID = %d;"
#define _SEL_PRE_KAT_DLNT "SELECT * FROM TDBADMIN.PREIS P \
	WHERE P.KAT_ID = %d AND P.RKR_ID = %d;"

int MPAPIpre_getprice(int typ, int typid, PREIS *precntrl, PREIS *prefound, char *preistxt)
{
	extern int sprache;
	extern MEMOBJ apimem;
	extern WAEHRUNG whr;

	PREIS *Ppre = NULL;
	int status = (int)MPOK;
	int id;
	int precnt;
	int buflen;
	char query[_QUERYLEN];
	char text[_RECORDLEN];
	char *ptr;
	unsigned long dlen, alen;

	/* init */
	(void)strcpy(text, "-");
	prefound->pre_id = (int)_UNDEF;
	prefound->apr = 0;
	prefound->epr = 0;
	prefound->vpr = 0;

	switch(typ)
		{
		case (int)_KATEGORIE:
			if (precntrl->kar_id == (int)_UNDEF)
				{
				if (precntrl->rkr_id == (int)_UNDEF)
					{
					if (precntrl->dla_id == (int)_UNDEF &&
					    precntrl->dl_id != (int)_UNDEF)
						sprintf(query, _SEL_PRE_KAT_DL, typid, precntrl->dl_id);
					else if (precntrl->dl_id == (int)_UNDEF &&
					    precntrl->dla_id != (int)_UNDEF)
						sprintf(query, _SEL_PRE_KAT_DLA, typid, precntrl->dla_id);
					else if (precntrl->dl_id == (int)_UNDEF &&
					    precntrl->dla_id == (int)_UNDEF)
						sprintf(query, _SEL_PRE_KAT, typid);
					else
						sprintf(query, _SEL_PRE_KAT_DLA_DL, typid, precntrl->dl_id,
						        precntrl->dla_id);
					}
				else
					{
					if (precntrl->dla_id == (int)_UNDEF &&
					    precntrl->dl_id != (int)_UNDEF)
						sprintf(query, _SEL_PRE_KAT_DLNT_DL, typid, precntrl->rkr_id, precntrl->dl_id);
					else if (precntrl->dl_id == (int)_UNDEF &&
					    precntrl->dla_id != (int)_UNDEF)
						sprintf(query, _SEL_PRE_KAT_DLNT_DLA, typid, precntrl->rkr_id, precntrl->dla_id);
					else if (precntrl->dl_id == (int)_UNDEF &&
					    precntrl->dla_id == (int)_UNDEF)
						sprintf(query, _SEL_PRE_KAT_DLNT, typid, precntrl->rkr_id);
					else
						sprintf(query, _SEL_PRE_KAT_DLNT_DLA_DL, typid, precntrl->rkr_id, precntrl->dl_id,
						        precntrl->dla_id);
					}
				}
			else
				{
				}
			/* get all PRE */
			alen = dlen = 0;
			status=MPAPIdb_sqlquery((int)_PREIS, &apimem.buffer, query,
			             &precnt, &apimem.datalen, &apimem.alloclen);
			if (status == (int)MPOK && precnt > 0)
				{
				Ppre = (PREIS *)apimem.buffer;
				(void)memcpy(prefound, &Ppre[0], sizeof(PREIS));
				id = MPAPIselectOneId((int)_WAEHRUNG, prefound->whr_id, (char *)&whr);
				if (id != (int)_UNDEF && whr.krzl[0] != NULL)
					(void)sprintf(text, "%5.5s %8.2f", whr.krzl, prefound->vpr);
				else
					(void)sprintf(text, " %8.2f", prefound->vpr);
				}
			break;
		}

	(void)strcpy(preistxt, text);

	return((int)MPOK);
}

