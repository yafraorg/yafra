/*D***********************************************************
 * Modul:     DBI - database delete
 *            Statuswerte
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/

#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xSTAdelete.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

#define MSG1	(int)268
#define MSG2	(int)269
#define MSG3	(int)270
#define MSG4	(int)128
#define MSG5	(int)130

int STAdelete(void)
{
	extern STATUS_WERTE sta;
	extern BEZEICHNUNG bez;
	extern int sprache;

	char message[RECLAENGE];
	int status=(int)MPOK, table, table1=(int)_UNDEF;

	switch(sta.typ)
		{
		case	(int)_PRIO	:
			if (MPAPIid_count((int)_STATUS_WERTE, (int)_ARR_DLG,
			    (char *)&sta) != (int)EMPTY)
				{
				UtilMsg((int)MSG2, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				}
			break;
		case	(int)_K_STA	:
			if (MPAPIid_count((int)_STATUS_WERTE, (int)_KOMM_DETAIL,
			    (char *)&sta) != (int)EMPTY)
				{
				UtilMsg((int)MSG2, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				}
			break;
		case	(int)_SEX	:
			if (MPAPIid_count((int)_STATUS_WERTE, (int)_REISENDER,
			    (char *)&sta) != (int)EMPTY)
				{
				UtilMsg((int)MSG2, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				}
			break;
		case	(int)_NAMEN	:
		case	(int)_GA	:
		case	(int)_BSTA	:
		case	(int)_A_FLG	:
		case	(int)_R_STA	:
		case	(int)_RES_F	:
			break;
		default:
			break;
		}

	status=MPAPIdeleteEntry((int)_STATUS_WERTE, (char *)&sta);
	if (status == (int)MPOK)
		{
		bez.s_id=(int)sprache;
		bez.typ=sta.typ;
		bez.bez_id=sta.bez_id;
		if (MPAPIid_count((int)_BEZEICHNUNG,(int)_STATUS_WERTE, (char *)&bez) == (int)EMPTY)
			{
			if (MPAPIdeleteEntry((int)_BEZEICHNUNG, (char *)&bez) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOBEZDEL, MSGTYP_ERROR, NULL);
				status=(int)MPERROR;
				}
			}
		}
	else
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
		status=(int)MPERROR;
		}
	
	return(status);
}
