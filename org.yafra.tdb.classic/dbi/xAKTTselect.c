/*D***********************************************************
 * Modul:     DBI - database select
 *            AKTIONS-TYP
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xAKTTselect.c,v 1.4 2009-01-02 21:30:21 mwn Exp $";

static int loc_parachoose;

/*F***********************************************************
 * Function:  Select
 *************************************************************/
int AKTTselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern AKTIONSPARA para;
	extern char glob_bez_aktt[];
	extern int sprache;
	extern int *NewLevel[];

   BEZEICHNUNG *bez_ptr;
	AKTIONSPARA *apara_ptr;
	AKTIONS_TYP aktt;
	int i;
	int selecttable = _BEZEICHNUNG;
	int status = (int)MPOK;
	int nr;
	char *buffer_ptr;
	char tmp_buffer[_CHARMAXLEN];
	char buffer1[_CHARMAXLEN];
	char query[_QUERYLEN];
	char message[RECLAENGE];
	size_t buffersize;

	switch(MENUNR)
		{
		case (unsigned char)_AKTIONS_TYP:
			if (FELDNR == MAKTT_PARANR)
				{
				if (*glob_bez_aktt != NULL)
					(void)MPAPIselectEntry((int)_AKTIONS_TYP, glob_bez_aktt, (char *)&aktt,
			          sizeof(aktt), sizeof(aktt.a_typ_id));

				if (ACTIONTYP != INSERT)
					{
					loc_parachoose = TRUE;
					if (aktt.a_typ_id != UNDEF)
						{
						(void)sprintf(query, _SEL_PARA_AKTT, aktt.a_typ_id);
						selecttable = _AKTIONSPARA;
						}
					else
						{
						*buffer = NULL;  /* keine Auswahl bringen */
						*anzahl = 1;
						return(MPOK);
						}
					}
				else
					{
					*anzahl = 1;
					if (aktt.a_typ_id != UNDEF)
						nr = (int)MPAPIid_max((int)_AKTIONS_TYP, (int)_ORD, (char *)&para) + (int)1;
					else
						nr = 1;
					(void)sprintf(buffer, "%d", nr);
					return(MPOK);
					}
				}
			else
				(void)sprintf(query, _SEL_BEZ_AKTT, sprache, (int)_AKTIONS_TYP);
			break;

		default:
			(void)sprintf(query, _SEL_BEZ_AKTT, sprache, (int)_AKTIONS_TYP);
			break;
		}

	status=MPAPIdb_sqlquery(selecttable, &sqlmem.buffer, query,
	                         anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if ( status == (int)MPOK )
		{
		if (*anzahl > (int)0 )
			{
			*len = (int)0;
			for ( i=0, buffer_ptr = buffer; i < *anzahl; i++ )
				{
				if (selecttable == _AKTIONSPARA)
					{
					apara_ptr = (AKTIONSPARA *)&sqlmem.buffer[i*sizeof(AKTIONSPARA)];
					(void)copyTextTo(buffer1, apara_ptr->bez, (int)_PARALEN);
					(void)sprintf(tmp_buffer, "%d%s%s", apara_ptr->nr, TRENNER,
					                                    buffer1);
					}
				else
					{
					bez_ptr = (BEZEICHNUNG *)&sqlmem.buffer[i*sizeof(BEZEICHNUNG)];
					(void)copyTextTo(tmp_buffer, (char *)bez_ptr->bez, (int)_BEZLEN);
					}
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

	*len = (int)strlen(buffer);
	if (*anzahl == 1)
		buffer[(*len - 1)] = NULL;
	return(status);
}


/*F***********************************************************
 * Function:  Choose
 *************************************************************/
int AKTTchoose(int table, char *buffer)
{
	extern int				sprache;
	extern AKTIONS_TYP	aktt;
	extern AKTIONSPARA   para;
	extern char glob_bez_aktt[];
	extern int glob_para_aktt;

	char bez[_BEZLEN];
	char	buffer1[_CHARMAXLEN];
	char	buffer2[_CHARMAXLEN];
	char	message[RECLAENGE];
	unsigned char paraset = FALSE;
	int   id;

	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	(void)memset((void *)buffer2, NULL, sizeof(buffer2));
	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MAKTT_BEZ:
			(void)strcpy(glob_bez_aktt, buffer);
			break;
		case MAKTT_PARANR:
			(void)sscanf(buffer, "%[^=]%*3c%31c", buffer1, buffer2);
			buffer1[strlen(buffer1)-1] = '\0';
			glob_para_aktt = (int)atoi(buffer1);
			if (loc_parachoose == TRUE)
				{
				(void)memcpy((void *)buffer, (void *)glob_bez_aktt, (size_t)_BEZLEN);
				loc_parachoose = FALSE;
				}
			else
				return(MPOK);
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* AKTIONS_TYP */
	if (MPAPIselectEntry(table, buffer, (char *)&aktt, sizeof(aktt),
		 sizeof(aktt.a_typ_id)) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, "\t");

	/* UNDEF  Prozess */
	(void)copyTextTo(buffer1, aktt.proz, (int)_PROZLEN);
	(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* TEXTE */
	id = SelFromTxt(aktt.textid, sprache, (int)_AKTIONS_TYP, buffer1);
	if (id != (int)_UNDEF)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* PARAMETER Sektion */
	if (glob_para_aktt != (int)NULL)
		{
		para.a_typ_id = aktt.a_typ_id;
		para.nr = glob_para_aktt;
		id = MPAPIselectOneId((int)_AKTIONSPARA, (int)aktt.a_typ_id, (char *)&para);
		if (id != UNDEF)
			{
			paraset = TRUE;

			/* UNDEF Parameternummer */
			(void)sprintf(buffer1, "%d\t", para.nr);
			(void)strcat(buffer, buffer1);

			/* UNDEF Parametertyp */
			if (para.typ != UNDEF)
				{
				id = SelectBez(para.typ, sprache, (int)_TYPENBEZID, bez);
				if (id != UNDEF)
					strcat(buffer, bez);
				}
			(void)strcat(buffer, "\t");

			/* UNDEF Parameter */
			(void)copyTextTo(buffer1, para.bez, (int)_PARALEN);
			(void)strcat(buffer, buffer1);
			(void)strcat(buffer, "\t");

			/* UNDEF Mussparameter */
			if (para.muss == TRUE)
				UtilMsgGet((int)MPI_YES_TRUE, MSGTYP_INFO, message);
			else
				UtilMsgGet((int)MPI_NO_FALSE, MSGTYP_INFO, message);
			(void)strcat(buffer, message);
			(void)strcat(buffer, "\t");

			/* UNDEF FLAGparameter */
			if (para.flag == TRUE)
				UtilMsgGet((int)MPI_YES_TRUE, MSGTYP_INFO, message);
			else
				UtilMsgGet((int)MPI_NO_FALSE, MSGTYP_INFO, message);
			(void)strcat(buffer, message);
			(void)strcat(buffer, "\t");

			/* UNDEF Parametertext */
			id = SelFromTxt(para.textid, sprache, (int)_AKTIONSPARA, buffer1);
			if (id != (int)_UNDEF)
				(void)strcat(buffer, buffer1);
			(void)strcat(buffer, "\t");
			}
		}

	if (!paraset)
		(void)strcat(buffer, "\t\t\t\t\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}
