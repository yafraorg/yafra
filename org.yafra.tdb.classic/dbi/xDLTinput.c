/*D***********************************************************
 * Modul:     DBI - database action
 *            Dienstleistungstr�ger
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLTinput.c,v 1.4 2009-01-02 16:51:34 mwn Exp $";

int DLTinput(int len, char *buffer)
{
	extern int sprache;

	extern char glob_dltbez[];
	extern DIENST_TRAEGER dlt; /* DLT    Eintrag als global f�r I/U/D */
	extern TRAEGER_TYP dltt;   /* DLTT   Eintrag */
	extern KATEGORIE kat;
	extern TEXTE txt;
	extern BEZEICHNUNG bez;
	extern STATUS_WERTE sta;

	DIENST_TRAEGER h_dlt;      /* PARENT Eintrag */
	DIENST_TRAEGER host_dlt;   /* HOST   Eintrag */
	char *to_buffers[MAX_MENU_ITEMS];
	char buffer1[RECLAENGE];
	char buffer2[RECLAENGE];
	int status=(int)MPOK;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		dlt.dlt_id = (int)_UNDEF;
		return((int)MPERROR);
		}

	switch (ACTIONTYP)
		{
		case MPDELETE:
			if (*to_buffers[MDLT_BEZ] == NULL || *glob_dltbez == NULL)
				{
				UtilMsg((int)MPE_NODLT, MSGTYP_ERROR, NULL);
				dlt.dlt_id = (int)_UNDEF;
				status = (int)MPERROR;
				}
			else
				{
				if ((strstr(glob_dltbez, TRENNER)) == NULL)
					dlt.stufe = 1; /* Eintrag ist von der obersten Stufe */
				else
					dlt.stufe = 0;
				if (MPAPIselectEntry((int)_DIENST_TRAEGER, glob_dltbez,
				     (char *)&dlt, sizeof(dlt), sizeof(dlt.dlt_id)) == (int)_UNDEF)
					{
					UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
					status = (int)MPERROR;
					}
				}
			break;

		case INSERT:
		case UPDATE:
			if (ACTIONTYP == (unsigned char)INSERT)
				{
				dlt.dlt_id=(int)_UNDEF;
				dlt.h_dlt_id = (int)_UNDEF;
//				dlt.h_bez_id = (int)_UNDEF;
				dlt.textid=(int)_UNDEF;
				txt.textid=(int)_UNDEF;
				}

			/* HOST Eintrag pr�fen (eigentlich nur f�r Input) */
			if (*to_buffers[MDLT_HOST] == (char)NULL)
				host_dlt.dlt_id = (int)_UNDEF;  /* neuer Eintrag ist selbst ein HOST */
			else
				{
				host_dlt.stufe = (int)1;
				if (MPAPIselectEntry((int)_DIENST_TRAEGER, to_buffers[MDLT_HOST], (char *)&host_dlt,
					 sizeof(host_dlt), sizeof(host_dlt.dlt_id)) == (int)_UNDEF)
					{
					UtilMsg((int)MPE_HOSTFIELD, MSGTYP_ERROR, NULL);
					return((int)MPERROR);
					}
				else
					{
					dlt.stufe		= (int)0;  /* Stufe auf 0 setzten */
					h_dlt.stufe		= (int)0;
					dlt.host_id		= host_dlt.dlt_id;
					h_dlt.host_id	= host_dlt.dlt_id;
					}
				}

			/* BEZEICHNUNG vom DLT setzen */
			bez.s_id	= (int)sprache;
			bez.typ	= (int)_DIENST_TRAEGER;
			(void)copyTextTo( bez.bez, to_buffers[MDLT_BEZ], (int)_BEZLEN );
			if ( *bez.bez != NULL )
				{
				if (*to_buffers[MDLT_DLTT] != NULL && (dlt.typ_id = (int)MPAPIselectEntry(
					  (int)_TRAEGER_TYP, to_buffers[MDLT_DLTT], (char *)&dltt,
					  sizeof(TRAEGER_TYP), sizeof(dlt.typ_id))) != (int)_UNDEF)
					{
					/* KATEGORIE */
					if ( *to_buffers[MDLT_KAT] != NULL )
						dlt.kat_id = (int)MPAPIselectEntry((int)_KATEGORIE, to_buffers[MDLT_KAT],
						      (char *)&kat, sizeof(KATEGORIE), sizeof(dlt.kat_id));
					else
						dlt.kat_id = (int)_UNDEF;

					/* STATUS_WERTE  _DLTSTA */
					if (*to_buffers[MDLT_ATTR] != NULL)
						{
						sta.typ = (int)_DLTSTA;
						if (getAttribut((int)_DLTSTA, to_buffers[MDLT_ATTR]) != (int)MPOK)
							{
							UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
							return((int)MPERROR);
							}
						dlt.sta_id = sta.sta_id;
						}
					else
						dlt.sta_id = (int)_UNDEF;

			      /* _UNDEF Code */
			      (void)copyTextTo(dlt.code, to_buffers[MDLT_CODE], (int)_KRZLLEN);

			      /* _UNDEF Max. Anzahl Personen auf Einheit */
				   if (*to_buffers[MDLT_ANZ] == NULL)
					   dlt.anz = (int)_UNDEF;
				   else
					   {
					   status = readInteger(&dlt.anz, to_buffers[MDLT_ANZ]);
					   if (status == (int)MPERROR)
						   dlt.anz = (int)_UNDEF;
					   else
						   if (dlt.anz < (int)1)
							   dlt.anz = (int)_UNDEF;
				      }

					if (*to_buffers[MDLT_HDLT] != NULL)
						{
						if ((strstr(to_buffers[MDLT_HDLT], TRENNER)) == NULL)
							h_dlt.stufe = 1; /* Eintrag ist von der obersten Stufe */
						else
							h_dlt.stufe = 0;
						dlt.h_dlt_id = MPAPIselectEntry((int)_DIENST_TRAEGER, to_buffers[MDLT_HDLT],
							(char *)&h_dlt, sizeof(DIENST_TRAEGER), sizeof(h_dlt.h_dlt_id));
						if (dlt.h_dlt_id == (int)_UNDEF)
							{
							UtilMsg((int)MPE_DLTMISMATCH, MSGTYP_ERROR, NULL);
							return( (int)MPERROR );
							}
						}
					else
						{
						dlt.h_dlt_id = (int)_UNDEF;
						h_dlt.typ_id = (int)_UNDEF;
						}

					if (h_dlt.typ_id == dltt.h_typ_id)
						{
						if (dlt.h_dlt_id == (int)_UNDEF)
							{
							/* Wenn bei MPAPIinsertEntry die host_id _UNDEF gesetzt ist
							   wird automatisch die dlt_id vererbet ! */
							dlt.host_id	= host_dlt.dlt_id;
							dlt.stufe	= (int)1;
							}
						else
							{
							dlt.stufe	 = h_dlt.stufe+(int)1;
							dlt.host_id	 = h_dlt.host_id;
//							dlt.h_bez_id = h_dlt.bez_id;
							}

						txt.typ		= (int)_DIENST_TRAEGER;
						txt.s_id		= (int)sprache;
						txt.textid	= dlt.textid;
						dlt.textid = xTxtWrite( to_buffers[MDLT_TXT] );
						}
					else
						{
						UtilMsg((int)MPE_DLTMISMATCH, MSGTYP_ERROR, NULL);
						dlt.dlt_id = (int)_UNDEF;
						status = (int)MPERROR;
						}
					}
				else
					{
					UtilMsg((int)MPE_NODLTT, MSGTYP_ERROR, NULL);
					dlt.dlt_id = (int)_UNDEF;
					status = (int)MPERROR;
					}
				}
			else
				{
				UtilMsg((int)MPE_NOBEZ, MSGTYP_ERROR, NULL);
				dlt.dlt_id = (int)_UNDEF;
				status = (int)MPERROR;
				}
			break;
		}

	/* F�hre Aktion aus */
	if (status == MPOK)
		{
		status = WriteEntry( (int)_DIENST_TRAEGER, (char *)&dlt, &bez );
		if (status == (int)MPERROR)
			dlt.dlt_id = (int)_UNDEF;
		else
			(void)WriteInfo( (int)_DIENST_TRAEGER, (char *)&dlt, buffer );
		}
	UtilSplitFreeMenubuffer(to_buffers);
	return( status );
}
