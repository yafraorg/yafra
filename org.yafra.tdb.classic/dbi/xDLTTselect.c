/**************************************************************/
/* Modul:     DBI - database select                           */
/*            Diensttraegertyp                                */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLTTselect.c,v 1.3 2009-01-02 16:51:34 mwn Exp $";

/**************************************************************/
/* Function:  Select                                          */
/**************************************************************/
int DLTTselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern DIENST_TRAEGER globDLT;
	extern int sprache;
	extern int *NewLevel[];

   TTYP_VIEW *Pdltt;

	register int i;
	int loop;
	int status = (int)MPOK;

	int value;

	char *str, *cptr, *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	char query[RECLAENGE];
	char message[RECLAENGE];
	size_t buffersize;

	switch(MENUNR)
		{
		case (unsigned char)_DIENST_TRAEGER:
			(void)sprintf(query, _SEL_BEZ_TTYP, sprache, sprache);
			break;

		default:
			(void)sprintf(query, _SEL_BEZ_TTYP, sprache, sprache);
		}

	status=MPAPIdb_sqlquery((int)_TTYP_VIEW, &sqlmem.buffer, query,
                         anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if ( status == (int)MPOK )
		{
		if ( *anzahl > (int)0 )
			{
			Pdltt=(TTYP_VIEW *)sqlmem.buffer;
			*len = (int)0;
			for ( i=0, buffer_ptr = buffer; i < *anzahl; i++ )
				{
				(void)copyTextTo(tmp_buffer, (char *)Pdltt[i].bez, (int)_BEZLEN);
				buffersize = strlen( tmp_buffer );
				(void)memcpy( (void *)buffer_ptr, (void *)tmp_buffer, buffersize+(size_t)1 );
				buffer_ptr += buffersize;

				(void)memcpy((void *)buffer_ptr, (void *)TRENNER, (size_t)TRENNERLEN);
				buffer_ptr += (size_t)TRENNERLEN;

				(void)copyTextTo(tmp_buffer, (char *)Pdltt[i].hbez, (int)_BEZLEN);
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
			*buffer = NULL;
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

	*len = (int)strlen( buffer );
	if (*anzahl == 1)
		buffer[(*len - 1)] = NULL;

	return(status);
}


/**************************************************************/
/* Function:  Choose                                          */
/**************************************************************/
int DLTTchoose(int table, char *buffer)
{
	extern int sprache;
	extern TRAEGER_TYP	dltt;
	extern TTYP_VIEW		ttyp;

	char	bezeichnung[RECLAENGE];
	char	buffer1[RECLAENGE];
	char	buffer2[RECLAENGE];
	char	message[RECLAENGE];
	int	id;
	int   status;

	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	(void)memset((void *)buffer2, NULL, sizeof(buffer2));
	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MDLTT_BEZ:                   /* Tr�gertyp */
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/*
	 * F�lle das Menu so viel wie m�glich               Output: 1 Menu
	 */

	/* TRAEGER_TYP  effektiver Tr�gertyp */
	status = MPAPIselectEntry(table, buffer, (char *)&dltt, sizeof(dltt), sizeof(dltt.typ_id));
	if (status == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return(MPERROR);
		}
	(void)sscanf(buffer, "%[^=]%*3c%31c", buffer1, buffer2);
	buffer1[strlen(buffer1)-1] = '\0';
	(void)strcpy(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* TRAEGER_TYP  �bergeordneter Tr�gertyp */
	id = MPAPIselectOneId((int)_TTYP_VIEW, (int)dltt.h_typ_id, (char *)&ttyp);
	if (id != (int)_UNDEF)
		{
		(void)copyTextTo(bezeichnung, ttyp.bez, (int)_BEZLEN);
		(void)strcat(buffer, bezeichnung);
		}
	else
		(void)strcat(buffer, UNDEFSYMB);
	(void)strcat(buffer, "\t");

	/* TEXTE */
	status = SelFromTxt(dltt.textid, sprache, (int)_TRAEGER_TYP, buffer1);
	if(status == (int)_UNDEF)
		(void)strcat(buffer, "\t");
	else
		{
		(void)strcat(buffer, buffer1);
		(void)strcat(buffer, "\t");
		}

	COMMTYP = SELECTITEM;
	return(MPOK);
}
