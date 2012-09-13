/*D***********************************************************
 * Modul:     DBI - database insert/update/delete                           
 *            Dienstleistungsteile DLG_PARTS
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xTDLinput.c,v 1.2 2008-11-02 19:55:39 mwn Exp $";

int DLGinput(int len, char *buffer)
{
	extern DLG_PART dlg;
	extern BEZEICHNUNG bez;
	extern KUNDEN kun;
	extern DIENST_ANGEBOT dla;
	extern SAISON sai;
	extern TEXTE txt;
	extern STATUS_WERTE sta;
	extern int sprache;

	DLG_PART h_dlg;

	struct tm DateTime;
	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;
	int h_dlg_id=(int)_UNDEF;
	int datestat = (int)MPOK;

	if (ACTIONTYP == (unsigned char)INSERT)
		{
		dlg.dl_id=(int)_UNDEF;
		dlg.textid=(int)_UNDEF;
		txt.textid=(int)_UNDEF;
		}

	/* get menu buffer and split it */
	status = UtilSplitMenubuffer(buffer, to_buffers, '~' );
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Bezeichnung - ev. vererbe DLA Bezeichnung */
	bez.s_id = sprache;
	bez.typ  = (int)_DLG_PART;
	if ( *to_buffers[MTDL_BEZ] == (char)NULL )
		(void)copyTextTo(bez.bez, to_buffers[MTDL_DLA], (int)_BEZLEN); 
	else
		(void)copyTextTo(bez.bez, to_buffers[MTDL_BEZ], (int)_BEZLEN);
	if ( *bez.bez != (char)NULL )
		{
		if (*to_buffers[MTDL_DLA] != (char)NULL &&
		    (dlg.dla_id = MPAPIselectEntry((int)_DIENST_ANGEBOT, to_buffers[MTDL_DLA],
		    (char *)&dla, sizeof(DIENST_ANGEBOT), sizeof(dlg.dla_id))) != (int)_UNDEF)
			{
			dlg.ord=dla.ord;
			if (*to_buffers[MTDL_HOSTTDL] != (char)NULL )
				h_dlg_id = MPAPIselectEntry((int)_DLG_PART, to_buffers[MTDL_HOSTTDL],
				  (char *)&h_dlg,	sizeof(DLG_PART), sizeof(dlg.dl_id));
			if (h_dlg_id != (int)_UNDEF)
				dlg.h_dl_id=h_dlg_id;
			else
				dlg.h_dl_id=(int)_UNDEF;

	      /* Code */
		   (void)copyTextTo(dlg.code, to_buffers[MTDL_CODE], (int)_KRZLLEN);

			sta.typ = (int)_RES_F;
			if (*to_buffers[MTDL_RESSTAT] != (char)NULL &&
			    getAttribut((int)_RES_F, to_buffers[MTDL_RESSTAT]) != (int)MPERROR)
				{
				dlg.res_f = sta.sta_id;
				if (*to_buffers[MTDL_SAI] != (char)NULL &&
				    (dlg.sai_id = MPAPIselectEntry((int)_SAISON,
				     to_buffers[MTDL_SAI], (char *)&sai, sizeof(SAISON),
					  sizeof(dlg.sai_id))) != (int)_UNDEF)
					{
					dlg.a_zeit=(int)_MP_NODATE;
					dlg.e_zeit=(int)_MP_NODATE;
					if ( *to_buffers[MTDL_ADAT] != (char)NULL )
						{
						(void)memset( (void *)&DateTime, (int)NULL, sizeof( DateTime ) );
						DateTime.tm_mday = (int)_UNDEF;
						DateTime.tm_mon  = (int)_UNDEF;
						DateTime.tm_year = (int)_UNDEF;
						DateTime.tm_hour = (int)_UNDEF;
						DateTime.tm_min  = (int)_UNDEF;
						datestat = ReadDate(&DateTime, (time_t *)&dlg.a_zeit,
						    to_buffers[MTDL_ADAT]);
						if (datestat != (int)MPOK)
							dlg.a_zeit = (int)_MP_NODATE;
						}

					if ( *to_buffers[MTDL_EDAT] != (char)NULL )
						{
						(void)memset( (void *)&DateTime, (int)NULL, sizeof( DateTime ) );
						DateTime.tm_mday = (int)_UNDEF;
						DateTime.tm_mon  = (int)_UNDEF;
						DateTime.tm_year = (int)_UNDEF;
						DateTime.tm_hour = (int)_UNDEF;
						DateTime.tm_min  = (int)_UNDEF;
						datestat=ReadDate(&DateTime, (time_t *)&(dlg.e_zeit),
						     to_buffers[MTDL_EDAT] );
						if (datestat != (int)MPOK)
							dlg.e_zeit = (int)_MP_NODATE;
						}
					else
						{
						if (dlg.a_zeit != (int)_MP_NODATE && dla.dau != (int)_MP_NODATE)
							dlg.e_zeit = dlg.a_zeit + dla.dau;
						}

					/* check up time with host dl entry and from/to date */
					if (dlg.a_zeit != (int)_MP_NODATE && dlg.e_zeit != (int)_MP_NODATE)
						{
						if (dlg.a_zeit > dlg.e_zeit)
							datestat = (int)MPERROR;
						else
							{
							if (dlg.h_dl_id != (int)_UNDEF) 
								{
								if (dlg.a_zeit < h_dlg.a_zeit ||
								    dlg.a_zeit >= h_dlg.e_zeit ||
								    dlg.e_zeit <= h_dlg.a_zeit ||
								    dlg.e_zeit > h_dlg.e_zeit )
									datestat=(int)MPERROR;
								}
							}
						}

					if (datestat == (int)MPOK)
						{
						if ( *to_buffers[MTDL_KUN] != (char)NULL )
							dlg.kid = MPAPIselectEntry( (int)_KUNDEN, to_buffers[MTDL_KUN],
							    (char *)&kun, sizeof( KUNDEN ), sizeof( dlg.kid ) );
						else
							dlg.kid = (int)_UNDEF;

						if ( *to_buffers[MTDL_RECHST] != (char)NULL )
							dlg.rechst = MPAPIselectEntry( (int)_KUNDEN, to_buffers[MTDL_RECHST],
							    (char *)&kun, sizeof( KUNDEN ), sizeof( dlg.rechst ) );
						else
							dlg.rechst = (int)_UNDEF;

						txt.typ		=	(int)_DLG_PART;
						txt.s_id		=	sprache;
						txt.textid	=	dlg.textid;
						dlg.textid = xTxtWrite( to_buffers[MTDL_TXT] );

						if ( *to_buffers[MTDL_KUNKTO] != (char)NULL )
							(void)copyTextTo( dlg.konto, to_buffers[MTDL_KUNKTO],
							     (int)_CHAR10 );
						else
							{
							if ( h_dlg_id != _UNDEF && *h_dlg.konto != (char)NULL )
								(void)copyTextTo(dlg.konto, h_dlg.konto, (int)_CHAR10);
							else
								*dlg.konto = (char)NULL;
							}

						status = WriteEntry( (int)_DLG_PART, (char *)&dlg, &bez );
						if ( status == (int)MPERROR )
							dlg.dl_id = (int)_UNDEF;
						else
							(void)WriteInfo((int)_DLG_PART, (char *)&dlg, buffer);
						}
					else
						{
						UtilMsg((int)MPE_DATEFROMTO, MSGTYP_ERROR, NULL);
						dlg.dl_id=(int)_UNDEF;
						status=(int)MPERROR;
						}
					}
				else
					{
					UtilMsg((int)MPE_NOSAI, MSGTYP_ERROR, NULL);
					dlg.dl_id=(int)_UNDEF;
					status=(int)MPERROR;
					}
				}
			else
				{
				UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
				dlg.dl_id=(int)_UNDEF;
				status=(int)MPERROR;
				}
			}
		else
			{
			UtilMsg((int)MPE_NODLA, MSGTYP_ERROR, NULL);
			dlg.dl_id=(int)_UNDEF;
			status=(int)MPERROR;
			}
		}
	else
		{
		UtilMsg((int)MPE_NOBEZ, MSGTYP_ERROR, NULL);
		dlg.dl_id=(int)_UNDEF;
		status=(int)MPERROR;
		}

	UtilSplitFreeMenubuffer( to_buffers );
	return( status );
}
