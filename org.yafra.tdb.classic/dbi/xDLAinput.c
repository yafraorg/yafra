/*D***********************************************************
 * Modul:     DBI - database action
 *            Dienstleistungsangebot
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLAinput.c,v 1.3 2009-01-02 16:51:35 mwn Exp $";

int DLAinput(int len, char *buffer)
{
	extern DIENST_ANGEBOT dla;
	extern BEZEICHNUNG bez;
	extern ANGEBOTS_TYP dlat;
	extern DIENST_TRAEGER dlt;
	extern AKTIONEN akt;
	extern TEXTE txt;
	extern STATUS_WERTE sta;
	extern int sprache;
	extern ORT ort;

	DIENST_ANGEBOT h_dla;

	struct tm DateTime;
	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK, h_dla_id;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		dla.dla_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	if (ACTIONTYP == (unsigned char)INSERT)
		{
		dla.dla_id=(int)_UNDEF;
		dla.textid=(int)_UNDEF;
		txt.textid=(int)_UNDEF;
		}

	bez.s_id=sprache;
	bez.typ=(int)_DIENST_ANGEBOT;
	(void)copyTextTo(bez.bez, to_buffers[MDLA_BEZ], (int)_BEZLEN);
	if (*bez.bez != NULL)
		{
		if (*to_buffers[MDLA_DLAT] != NULL && (dla.art_id=MPAPIselectEntry((int)_ANGEBOTS_TYP, to_buffers[MDLA_DLAT],
			 (char *)&dlat, sizeof(ANGEBOTS_TYP), sizeof(dla.art_id))) != (int)_UNDEF)
			{
			if (*to_buffers[MDLA_DLAHOST] != NULL &&
				 (h_dla_id = MPAPIselectEntry((int)_DIENST_ANGEBOT, to_buffers[MDLA_DLAHOST],
				 (char *)&h_dla, sizeof(DIENST_ANGEBOT), sizeof(dla.dla_id))) != (int)_UNDEF)
				{
				dla.h_dla_id = h_dla_id;
				if (*to_buffers[MDLA_ORD] == NULL)
					dla.ord=MPAPIid_max((int)_DIENST_ANGEBOT, (int)_ORD, (char *)&dla) + (int)1;
				else
					{
					status=readInteger(&dla.ord, to_buffers[MDLA_ORD]);
					if (status == (int)MPERROR)
						dla.ord=MPAPIid_max((int)_DIENST_ANGEBOT, (int)_ORD,
								(char *)&dla) + (int)1;
					else
						{
						if (dla.ord < (int)1)
							dla.ord=MPAPIid_max((int)_DIENST_ANGEBOT, (int)_ORD,
											(char *)&dla) + (int)1;
						}
					}
				}
			else
				{
				dla.h_dla_id=(int)_UNDEF;
				h_dla.dla_id=(int)_UNDEF;
				dla.ord = (int)0;
				}

			dlt.stufe = (int)1;
			if (*to_buffers[MDLA_DLT] != NULL && (dla.dlt_id = MPAPIselectEntry((int)_DIENST_TRAEGER, to_buffers[MDLA_DLT],
				 (char *)&dlt, sizeof(DIENST_TRAEGER), sizeof(dla.dlt_id))) != (int)_UNDEF)
				{
				if (dlt.stufe == (int)1)
					{
					/* nur HOST Aktionen erlaubt */
					akt.a_typ_id = _UNDEF;
					if (*to_buffers[MDLA_AKT] != NULL)
						dla.akt_id = MPAPIselectEntry((int)_AKTIONEN, to_buffers[MDLA_AKT],
						   (char *)&akt, sizeof(AKTIONEN), sizeof(dla.akt_id));
					else
						dla.akt_id = (int)_UNDEF;

					dla.dau = _MP_NODATE;
					(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
					DateTime.tm_mday=(int)_UNDEF;
					DateTime.tm_hour=(int)_UNDEF;
					DateTime.tm_min =(int)_UNDEF;
					if (ReadTime(&DateTime, (time_t *)&dla.dau,
						 to_buffers[MDLA_DAU]) == (int)MPOK)
						{
						if (*to_buffers[MDLA_ORT] == NULL)
							(void)copyTextTo(dla.ort, "undefined", (int)_BEZLEN);
						else
							(void)copyTextTo(dla.ort, to_buffers[MDLA_ORT],	(int)_BEZLEN);

						/* Code */
						(void)copyTextTo(dla.code, to_buffers[MDLA_CODE],	(int)_KRZLLEN);

						if (*to_buffers[MDLA_VON] != NULL &&
							 MPAPIselectEntry(_ORT, to_buffers[MDLA_VON], (char *)&ort,
							 sizeof(ort), sizeof(ort.ort_id)) != (int)_UNDEF)
							dla.von = ort.ort_id;
						else
							dla.von=(int)_UNDEF;

						if (*to_buffers[MDLA_NACH] != NULL &&
							 MPAPIselectEntry(_ORT, to_buffers[MDLA_NACH], (char *)&ort,
							 sizeof(ort), sizeof(ort.ort_id)) != (int)_UNDEF)
							dla.nach = ort.ort_id;
						else
							dla.nach=(int)_UNDEF;

						txt.typ    = (int)_DIENST_ANGEBOT;
						txt.s_id   = sprache;
						txt.textid = dla.textid;
						dla.textid = xTxtWrite(to_buffers[MDLA_TXT]);

						status=WriteEntry((int)_DIENST_ANGEBOT, (char *)&dla, &bez);
						if (status == (int)MPERROR)
							dla.dla_id=(int)_UNDEF;
						}
					else
						{
						UtilMsg((int)MPE_TIMEWRONG, MSGTYP_ERROR, NULL);
						dla.dla_id=(int)_UNDEF;
						status=(int)MPERROR;
						}

					}
				else
					{
					UtilMsg((int)MPE_NODLT, MSGTYP_ERROR, NULL);
					dla.dla_id=(int)_UNDEF;
					status=(int)MPERROR;
					}
				}
			else
				{
				UtilMsg((int)MPE_NODLT, MSGTYP_ERROR, NULL);
				dla.dla_id=(int)_UNDEF;
				status=(int)MPERROR;
				}
			}
		else
			{
			UtilMsg((int)MPE_NODLAT, MSGTYP_ERROR, NULL);
			dla.dla_id=(int)_UNDEF;
			status=(int)MPERROR;
			}
		}
	else
		{
		UtilMsg((int)MPE_NOBEZ, MSGTYP_ERROR, NULL);
		dla.dla_id=(int)_UNDEF;
		status=(int)MPERROR;
		}

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
