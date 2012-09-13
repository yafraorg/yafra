/*D***********************************************************
 * Modul:     DBI - database info                           
 *            show all bookings of a DLN and all KOLLEKTIV
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLNinfo.c,v 1.2 2008-11-02 19:55:38 mwn Exp $";

#define _SEL_BD_DLN "SELECT * FROM TDBADMIN.BCH_DLN \
	WHERE DLN_ID = %d;"

#define _SEL_KOL_DLN "SELECT * FROM TDBADMIN.KOLLEKTIV \
	WHERE DLN_ID = %d;"

int DLNinfo(int len, char *buffer)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern char sqlquery[];
	extern KOLLEKTIV kol;
	extern PERSONEN pers;
	extern REISENDER rei;

	BUCHUNG *Pbch;
	BCH_DLN *Pbd;
	char *to_buffers[MAX_MENU_ITEMS];
	char tmp_buffer[RECLAENGE];
	char tmp_bez[_RECORDLEN];
	char kolbez[_BEZLEN+1];
	int status=(int)MPOK;
	int i, id, anzahl, anzchar, last_id=(int)_UNDEF;

	/* init */
	kol.k_id = (int)_UNDEF;

	/* set info to text */
	ACTIONTYP = INFOTXT;

	/* get menu strings */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL );
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		kol.k_id = (int)_UNDEF;
		return((int)MPERROR);
		}
	(void)copyTextTo(kolbez, to_buffers[MKOL_BEZ], _BEZLEN);
	UtilSplitFreeMenubuffer(to_buffers);

	/* KOLLEKTIV */
	if (MPAPIselectEntry((int)_KOLLEKTIV, kolbez, (char *)&kol,
	    sizeof(kol), sizeof(kol.k_id)) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	(void)sprintf(sqlquery, _SEL_BD_DLN, kol.k_id);
	status = MPAPIdb_sqlquery((int)_BCH_DLN, &sqlmem.buffer, sqlquery,
		                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if ( anzahl > (int)0 )
		{
		Pbd = (BCH_DLN *)sqlmem.buffer;
		*buffer = NULL;
		anzchar=(int)_BEZLEN;
		(void)strcpy(buffer, kolbez);
		(void)strcat(buffer, "\n");
		for(i=0; i<anzchar; i++) strcat(buffer, "=");
			(void)strcat(buffer, "\n\n");

		for ( i=0; i<anzahl; i++ )
			{
			(void)copyTextTo(tmp_bez, Pbch[i].ref, _BEZLEN);
			/*!!! hardcoded */
			(void)sprintf(tmp_buffer, "Buchung: %s\n", tmp_bez);
			(void)strcat(buffer, tmp_buffer);
			}
		}
	else
		{
		UtilMsg((int)MPE_NOBCH, MSGTYP_ERROR, NULL);
		status = (int)MPERROR;
		}

	return(status);
}
