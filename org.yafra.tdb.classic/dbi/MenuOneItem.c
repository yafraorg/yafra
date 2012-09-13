/*D***********************************************************
 * Modul:     DBI - menu
 *            get data/action for fieldtyp ONEITEM
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/MenuOneItem.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

int MenuOneitem(int *len, char *buffer)
{
	extern BUCHUNG	bch;
	extern int AnzParts;        /* im Arrangement */
	extern char userid[];

	char message[_RECORDLEN];
	char tmp_buffer[_RECORDLEN];
	char *to_buffers[MAX_MENU_ITEMS];
	char referenz[_BEZLEN];
	int status=(int)MPOK;
	int anzparts, i, offset;

	status=MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	switch(MENUNR)
		{
		case (unsigned char)_KOLLEKTIV:
			(void)copyTextTo(buffer, bch.ref, (int)_CHAR30);
			break;

		case (unsigned char)_ARRANGEMENT:
			switch(FELDNR)
				{
				case (unsigned char)MARR_TEILNR:
					anzparts=atoi(to_buffers[MARR_TEILNR]);
					if (anzparts < 1)
						anzparts=(int)1;
					else
						anzparts++;
					(void)sprintf(buffer, "%d", anzparts);
					break;
				}
			break;

		case (unsigned char)_DIENSTLEISTUNG:
			switch(FELDNR)
				{
				case (unsigned char)MDL_ORD:
					anzparts=atoi(to_buffers[MDL_ORD]);
					if (anzparts < 1)
						anzparts=(int)1;
					else
						anzparts++;
					(void)sprintf(buffer, "%d", anzparts);
					break;
				}
			break;

		case (unsigned char)_DIENST_ANGEBOT:
			switch(FELDNR)
				{
				case (unsigned char)MDLA_ORD:
					anzparts=atoi(to_buffers[MDLA_ORD]);
					if (anzparts < 1)
						anzparts=(int)1;
					else
						anzparts++;
					(void)sprintf(buffer, "%d", anzparts);
					break;
				}
			break;

		case (unsigned char)_BUCHUNG:
			switch(FELDNR)
				{
				case MBCH_BCHREF:
					sprintf(referenz, "B1*%s", userid);
					(void)copyTextTo(buffer, bch.ref, (int)_CHAR30);
					break;
				}
			break;

		case (unsigned char)_AKTIONSGRP:
			anzparts=atoi(to_buffers[MAKTG_ORD]);
			if (anzparts < 1)
				anzparts=(int)1;
			else
				anzparts++;
			(void)sprintf(buffer, "%d", anzparts);
			break;

		case (unsigned char)_KONT_DETAIL:
			switch(FELDNR)
				{
				case MKOND_MENGE:
					anzparts=atoi(to_buffers[MKOND_MENGE]);
					break;
				case MKOND_MIN:
					anzparts=atoi(to_buffers[MKOND_MIN]);
					break;
				}
			if (anzparts < 1)
				anzparts=(int)1;
			else
				anzparts++;
			(void)sprintf(buffer, "%d", anzparts);
			break;

		case (unsigned char)_KOMM_DETAIL:
			anzparts=atoi(to_buffers[MKOMD_ORD]);
			if (anzparts < 1)
				anzparts=(int)1;
			else
				anzparts++;
			(void)sprintf(buffer, "%d", anzparts);
			break;

		case (unsigned char)_AKTIONS_TYP:
			switch(FELDNR)
				{
				case (unsigned char)MAKTT_PARANR:
					anzparts=atoi(to_buffers[MAKTT_PARANR]);
					if (anzparts < 1)
						anzparts=(int)1;
					else
						anzparts++;
					(void)sprintf(buffer, "%d", anzparts);
					break;
				case (unsigned char)MAKTT_PARAMUSS:
					UtilMsgGet((int)MPI_YES_TRUE, MSGTYP_INFO, message);
					(void)copyTextTo(tmp_buffer, to_buffers[MAKTT_PARAMUSS], (int)_FLAGLEN);
					if (strstr(message, tmp_buffer) != NULL)
						UtilMsgGet((int)MPI_NO_FALSE, MSGTYP_INFO, message);
					(void)strcpy(buffer, message);
					break;
				case (unsigned char)MAKTT_PARAFLAG:
					UtilMsgGet((int)MPI_YES_TRUE, MSGTYP_INFO, message);
					(void)copyTextTo(tmp_buffer, to_buffers[MAKTT_PARAFLAG], (int)_FLAGLEN);
					if (strstr(message, tmp_buffer) != NULL)
						UtilMsgGet((int)MPI_NO_FALSE, MSGTYP_INFO, message);
					(void)strcpy(buffer, message);
					break;
				}
			break;

		case (unsigned char)_DIENST_TRAEGER:
			switch(FELDNR)
				{
				case (unsigned char)MDLT_ANZ:
					anzparts=atoi(to_buffers[MDLT_ANZ]);
					if (anzparts < 1)
						anzparts=(int)1;
					else
						anzparts++;
					(void)sprintf(buffer, "%d", anzparts);
					break;
				}
			break;

		case (unsigned char)_PREIS:
			switch(FELDNR)
				{
				case (unsigned char)MPRE_UNITVON:
					anzparts=atoi(to_buffers[MPRE_UNITVON]);
					if (anzparts < 1)
						anzparts=(int)1;
					else
						anzparts++;
					(void)sprintf(buffer, "%d", anzparts);
					break;
				case (unsigned char)MPRE_UNITBIS:
					anzparts=atoi(to_buffers[MPRE_UNITBIS]);
					if (anzparts < 1)
						anzparts=(int)1;
					else
						anzparts++;
					(void)sprintf(buffer, "%d", anzparts);
					break;
				}
			break;

		case (unsigned char)_SPRACHEN:
			UtilMsgGet((int)MPI_YES_TRUE, MSGTYP_INFO, message);
			switch(FELDNR)
				{
				case (unsigned char)MSPR_DIALOG:
			      (void)copyTextTo(tmp_buffer, to_buffers[MSPR_DIALOG], (int)_FLAGLEN);
			      if (strstr(message, tmp_buffer) != NULL)
				      UtilMsgGet((int)MPI_NO_FALSE, MSGTYP_INFO, message);
			      (void)strcpy(buffer, message);
					break;
				case (unsigned char)MSPR_OUTPUT:
			      (void)copyTextTo(tmp_buffer, to_buffers[MSPR_OUTPUT], (int)_FLAGLEN);
			      if (strstr(message, tmp_buffer) != NULL)
				      UtilMsgGet((int)MPI_NO_FALSE, MSGTYP_INFO, message);
			      (void)strcpy(buffer, message);
					break;
				case (unsigned char)MSPR_GUI:
			      (void)copyTextTo(tmp_buffer, to_buffers[MSPR_GUI], (int)_FLAGLEN);
			      if (strstr(message, tmp_buffer) != NULL)
				      UtilMsgGet((int)MPI_NO_FALSE, MSGTYP_INFO, message);
			      (void)strcpy(buffer, message);
					break;
				}
			break;

		default:
			UtilMsg((int)MPE_NOSELECTTABLE, MSGTYP_ERROR, NULL);
			status=(int)MPERROR;
			break;
		}

	(void)MPAPIdb_committrx();

	UtilSplitFreeMenubuffer(to_buffers);

	return(status);
}
