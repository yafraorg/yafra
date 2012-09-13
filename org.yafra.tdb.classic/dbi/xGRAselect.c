/*D************************************************************
/* Modul:     DBI - database select
/*            Grafik
/*
/* Copyright: yafra.org, Basel, Switzerland
/**************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xGRAselect.c,v 1.2 2008-11-02 19:55:41 mwn Exp $

 Log Information:
 $Log: xGRAselect.c,v $
 Revision 1.2  2008-11-02 19:55:41  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:42  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:35:36  mw
 update to new DB release 2.0

 * Revision 1.7  94/02/16  18:20:20  18:20:20  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.6  93/08/23  13:28:39  13:28:39  mw (Administrator)
 * remove begin/end trx
 * 
 * Revision 1.5  93/07/19  15:10:38  15:10:38  mw (Administrator)
 * "update"
 * 
 * Revision 1.4  93/03/30  19:48:28  19:48:28  mw (Administrator)
 * "maintenance"
 * 
 * Revision 1.3  92/11/26  20:36:08  20:36:08  mw ()
 * "new handling and dynamic_sql function"
 * 
 * Revision 1.2  92/09/25  01:28:36  01:28:36  mw ()
 * "new select handling"
 * 
*/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xGRAselect.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

int GRAselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern int *NewLevel[];

   BEZEICHNUNG *bez_ptr;
	int i;
	int status = (int)MPOK;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	char query[RECLAENGE];
	size_t buffersize;

	(void)sprintf(query, _SEL_BEZ_GRA, sprache, _GRAPHIK);
	status=MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, query,
                         anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if ( status == (int)MPOK )
		{
		if (*anzahl > (int)0 )
			{
			*len = (int)0;
			if (sqlmem.alloclen > comm.alloclen)
				{
				comm.buffer = (char *)MPalloc((void *)comm.buffer, &comm.alloclen,
		                    DEFMEMCHUNK, sqlmem.alloclen, sizeof(char));
				buffer = comm.buffer;
				}
			for (i=0, buffer_ptr = comm.buffer; i < *anzahl; i++ )
				{
				bez_ptr = (BEZEICHNUNG *)&sqlmem.buffer[i*sizeof(BEZEICHNUNG)];
				(void)copyTextTo(tmp_buffer, (char *)bez_ptr->bez, (int)_CHAR30);
				buffersize = strlen( tmp_buffer );
				(void)memcpy( (void *)buffer_ptr, (void *)tmp_buffer, buffersize+(size_t)1 );
				buffer_ptr += buffersize;
				(void)memset( (void *)buffer_ptr, '\n', sizeof( char ) );
				buffer_ptr++;
				(void)memset( (void *)buffer_ptr, NULL, sizeof( char ) );
				}
			}
		else
			{
			*comm.buffer = NULL;
			if (MENUNR == NewLevel[MENUNR][FELDNR])
				{
				UtilMsg((int)MPE_NOCHOOSE, MSGTYP_ERROR, NULL);
				status = (int)MPERROR;
				}
			}
		}
	else
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		status = (int)MPERROR;
		}

	*len = (int)strlen(comm.buffer);
	if (*anzahl == 1)
		comm.buffer[(*len - 1)] = NULL;

	return(status);
}

int GRAchoose(int table, char *buffer)
{
	extern int sprache;
	extern DIENST_TRAEGER	dlt;
	extern GRAPHIK				gra;

	DLT_VIEW dltv;
	char	bezeichnung[RECLAENGE];
	char	buffer1[RECLAENGE];
	char	message[RECLAENGE];
	int	id;

	(void)memset( (void *)buffer1, NULL, sizeof(buffer1) );
	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MGRA_BEZ:
			break;
		default:
			return((int)MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* GRAPHIK */
	if (MPAPIselectEntry((int)_GRAPHIK, buffer, (char *)&gra, sizeof(gra),
	    sizeof(gra.gra_id)) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, "\t");

	/* DIENST_TRAEGER */
	id = MPAPIselectOneId((int)_DLT_VIEW, gra.dlt_id, (char *)&dltv);
	if (id != (int)_UNDEF)
		{
		(void)copyTextTo(bezeichnung, dltv.bez, (int)_BEZLEN);
		(void)strcat(buffer, bezeichnung);
		}
	(void)strcat(buffer, "\t");

	/* TEXTE */
	if (SelFromTxt(gra.textid, sprache, (int)_GRAPHIK, buffer1) == (int)_UNDEF)
		(void)strcat( buffer, "\t" );
	else
		{
		(void)strcat(buffer, buffer1);
		(void)strcat(buffer, "\t");
		}

	COMMTYP = SELECTITEM;
	return(MPOK);
}
