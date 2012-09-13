/*D***********************************************************
 * Modul:     DBI - database insert
 *            Bezeichnungen
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/InsertBez.c,v 1.3 2008-11-23 15:44:38 mwn Exp $";

#define _SEL_BEZ_FORINSERT "SELECT * FROM TDBADMIN.BEZEICHNUNG \
	WHERE BEZ = \'%s\' AND S_ID=%d AND TYP=%d AND BEZ_ID > 0 \
	ORDER BY BEZ_ID;"


int InsertBEZ(BEZEICHNUNG *bez)
{
	extern MEMOBJ apimem;

	BEZEICHNUNG tmp_bez;
	BEZEICHNUNG *bez_ptr;
	SPRACHEN *sprache;
	char query[_QUERYLEN];
	int bez_id, status=(int)MPOK;
	int anzahl, i;
	int bezlen, bezok = (int)FALSE;

	/* check that's not a NULL pointer */
	if (bez == (char)NULL)
		return((int)_UNDEF);

	/* check that's for minimum there's a single alphnum char */
	bezlen = strlen(bez->bez);
	if (bezlen > (int)_BEZLEN+1)
		bezlen = (int)_BEZLEN+1;
	for (i=0;i<bezlen;i++)
		{
		if (isalnum(bez->bez[i]))
			{
			bezok = TRUE;
			break;
			}
		}
	if (bezok == (int)FALSE)
		{
		bez->bez_id = (int)_UNDEF;
		return(bez->bez_id);
		}

	/* manage BEZEICHNUNG */
	bez->bez_id = MPAPIid_new((int)_BEZEICHNUNG, (int)0, (int)0);
	if (bez->bez_id > 0)
	      {
		(void)sprintf(query, _SEL_ALL_DIALOGSPR, (int)TRUE);
		status = MPAPIdb_sqlquery((int)_SPRACHEN, &apimem.buffer, query,
		                  &anzahl, &apimem.datalen, &apimem.alloclen);
		if (status == (int)MPOK)
			{
			sprache = (SPRACHEN *)apimem.buffer;
			for (i=0; i < anzahl; i++)
				{
				bez->s_id = sprache[i].s_id;
				status = MPAPIinsertEntry( (int)_BEZEICHNUNG, (char *)bez,
				                     (BEZEICHNUNG *)NULL );
				}
			}
		else
			bez->bez_id=(int)_UNDEF;
		  }
	else
		bez->bez_id=(int)_UNDEF;

	return(bez->bez_id);
}
