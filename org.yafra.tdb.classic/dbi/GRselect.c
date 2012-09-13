/*D************************************************************
 * Modul:     DBI - graphic modul
 *            start up graphic in show or book mode
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/GRselect.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

int GRselect(int len, char *buffer)
{
	extern MEMOBJ sqlmem;
	extern GRAPHIK gra;
	extern DIENST_TRAEGER dlt;
	extern DIENSTLEISTUNG dtg;
	extern int OldGraID;
	extern unsigned char bm_obj;

	DIENST_ANGEBOT dla;
	DLG_PART dlg;
	DLG_DLG *dl_dlpart = NULL;

	char dltbez[_RECORDLEN];
	char *to_buffers[MAX_MENU_ITEMS];
	char query[_QUERYLEN];

	int anzahl = 0;
	int xdlg;
	int status = MPOK;
	int laenge = 0;
	int id;
	int dlpartid;

	switch(MENUNR)
		{
		case (unsigned char)_BUCHUNG:
			/* hole Eintrage aus dem Menustring der GUI */
			status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
			if (status != MPOK)
				{
				UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
				gra.gra_id = (int)_UNDEF;
				return((int)MPERROR);
				}
			strcpy(dltbez, to_buffers[MBCH_DLT]);
			UtilSplitFreeMenubuffer(to_buffers);
			if (*dltbez != NULL)
				{
				dlt.stufe = (int)1;
				gra.dlt_id = MPAPIselectEntry((int)_DIENST_TRAEGER, dltbez,
		             (char *)&dlt, sizeof(DIENST_TRAEGER), sizeof(gra.dlt_id));
				dlt.dlt_id = gra.dlt_id;
				}
			else
				{
				COMMSTAT = MESSAGEOK;
				COMMTYP = SELECT;
				MENUNR  = (unsigned char)_BUCHUNG;
				FELDNR  = (unsigned char)MBCH_DLT;
				status = DLTselect((long *)&laenge, buffer, &anzahl);
				if (status != (int)MPOK )
					status = (int)MPERROR;
				comm.datalen = laenge;
				return(status);
				}
			break;

		case (unsigned char)_RESERVATION:
			if (dtg.dlg_id < 1)
				{
				dlt.dlt_id = (int)_UNDEF;
				UtilMsg((int)MPE_NODL, MSGTYP_ERROR, NULL);
				status = (int)MPERROR;
				}
			(void)sprintf(query, _SEL_DLDLG, dtg.dlg_id);
			status=MPAPIdb_sqlquery((int)_DLG_DLG, (char **)&sqlmem.buffer,
			       query, &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
			if (status == (int)MPOK && anzahl > 0)
				{
				dl_dlpart = (DLG_DLG *)sqlmem.buffer;
				dlpartid = MPAPIselectOneId((int)_DLG_PART, dl_dlpart[0].dl_id,
	                   (char *)&dlg);
				}
			else
				dlpartid = (int)_UNDEF;

			id = MPAPIselectOneId((int)_DLG_PART, dlpartid, (char *)&dlg);
			if (id != (int)_UNDEF)
				{
				id = MPAPIselectOneId((int)_DIENST_ANGEBOT, dlg.dla_id, (char *)&dla);
				if (id != (int)_UNDEF)
					dlt.dlt_id = dla.dlt_id;
				else
					{
					dlt.dlt_id = (int)_UNDEF;
					UtilMsg((int)MPE_NOGRADLT, MSGTYP_ERROR, NULL);
					status = (int)MPERROR;
					}
				}
			else
				{
				dlt.dlt_id = (int)_UNDEF;
				UtilMsg((int)MPE_NODLG, MSGTYP_ERROR, NULL);
				status = (int)MPERROR;
				}
			break;

		default:
			dlt.dlt_id = (int)_UNDEF;
			UtilMsg((int)MPE_PROTOCOL, MSGTYP_ERROR, NULL);
			status = (int)MPERROR;
			break;
		}

	/* graphic form and graphic regions */
	if (dlt.dlt_id != (int)_UNDEF && status == (int)MPOK)
		{
		id = MPAPIselectOneId((int)_GRAPHIK, dlt.dlt_id, (char *)&gra);
		if (id != (int)_UNDEF)
			{
			/* check if already in memory, cause the last gra is in GUI mem */
			if (gra.dlt_id != OldGraID)
				{
				/* if not, load the new graphic */
				OldGraID = dlt.dlt_id;
				comm.datalen = GRgetRegionsFromDB((GRAPHIK *)&gra);
				if (comm.datalen == (int)0)
					status = (int)MPERROR;
				}
			else
				{
				status = (int)MPOK;
				comm.buffer[0] = NULL;
				comm.datalen = 0;
				}
			}
		else
			{
			gra.gra_id = (int)_UNDEF;
			gra.dlt_id = (int)_UNDEF;
			dlt.dlt_id = (int)_UNDEF;
			UtilMsg((int)MPE_NOGRA, MSGTYP_ERROR, NULL);
			status = (int)MPERROR;
			}
		}

	return(status);
}
