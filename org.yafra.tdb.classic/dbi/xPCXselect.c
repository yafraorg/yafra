/*D************************************************************/
/* Modul:     DBI - database select                           */
/*            get a pixel image                               */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xPCXselect.c,v 1.2 2008-11-02 19:55:40 mwn Exp $

 Log Information:
 $Log: xPCXselect.c,v $
 Revision 1.2  2008-11-02 19:55:40  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:36:53  mw
 update to new DB release 2.0

 * Revision 1.3  94/02/16  18:20:53  18:20:53  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.2  93/08/23  13:54:32  13:54:32  mw (Administrator)
 * remove begin/end trx
 * 
 * Revision 1.1  93/07/14  17:45:32  17:45:32  mw (Administrator)
 * Initial revision
 * 
*/

#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xPCXselect.c,v 1.2 2008-11-02 19:55:40 mwn Exp $";

/*F***********************************************************
 * Function:  Select                                         
 *************************************************************/
int PCXselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern int *NewLevel[];
	extern char glob_typ_pcx[];

	BEZEICHNUNG localbez;
   BEZEICHNUNG *bez_ptr;
	int i;
	int status = (int)MPOK;
	int objecttyp;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	char query[RECLAENGE];
	size_t buffersize;

	if (MENUNR == (unsigned char)_PCX_FILES && FELDNR == MPCX_TYPCODE)
		{
		localbez.s_id=(int)sprache;
		localbez.typ=(int)_UNDEF;
		(void)strcpy(localbez.bez, glob_typ_pcx);
		if (MPAPIselectEntry((int)_BEZEICHNUNG, glob_typ_pcx, (char *)&localbez,
		    sizeof(BEZEICHNUNG), sizeof(localbez.bez_id)) != (int)_UNDEF)
			objecttyp = localbez.typ;
		else
			objecttyp = (int)_UNDEF;
		(void)sprintf(query, _SEL_BEZ_TYP_PCX, sprache, objecttyp);
		}
	else
		(void)sprintf(query, _SEL_BEZ_PCX, sprache, (int)_PCX_FILES);

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
			for ( i=0, buffer_ptr = comm.buffer; i < *anzahl; i++ )
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


/*F***********************************************************
 * Function:  Choose                                          
 *************************************************************/
int PCXchoose(int table, char *buffer)
{
	extern int sprache;
	extern PCX_FILES		pcx;
	extern TRAEGER_VIEW	trv;
	extern char glob_typ_pcx[];

	char	bezeichnung[RECLAENGE];
	char	buffer1[RECLAENGE];
	int	id;

	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MPCX_BEZ:
			break;
		case MPCX_TYP:
			(void)strcpy(glob_typ_pcx, buffer);
			return((int)MPOK);
			break;
		default:
			return((int)MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* PCX_FILES */
	if (MPAPIselectEntry(table, buffer, (char *)&pcx, sizeof(pcx),
						 sizeof(pcx.pcx_id)) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, "\t");

	/* UNDEF  PCX Filename */
	(void)copyTextTo(bezeichnung, pcx.filename, (int)_FILELEN);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* _BEZEICHNUNG  PCX Typ */
	if (pcx.typ != (int)_UNDEF)
		{
		id = SelectBez(pcx.typ, sprache, (int)_TYPENBEZID, bezeichnung);
		if (id != UNDEF)
			strcat(buffer, bezeichnung);
		}
	(void)strcat(buffer, "\t");

	/* UNDEF  Objekt Auswahl innerhalb des Typs */

	/* _BEZEICHNUNG  PCX Typ */
	if (pcx.typcode != (int)_UNDEF)
		{
		id = SelectBez(pcx.typ, sprache, pcx.typcode, bezeichnung);
		if (id != UNDEF)
			strcat(buffer, bezeichnung);
		}
	(void)strcat(buffer, "\t");

	/* UNDEF  PCX Nummer */
	(void)sprintf(bezeichnung, "%d", pcx.folge);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  PCX X Koord */
	(void)sprintf(bezeichnung, "%d", pcx.x);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  PCX Y Koord */
	(void)sprintf(bezeichnung, "%d", pcx.y);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}

