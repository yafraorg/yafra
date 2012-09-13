/*D***********************************************************
 * Modul:     DBI - database delete
 *            Aktionstyp
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xAKTTdelete.c,v 1.2 2008-11-02 19:55:35 mwn Exp $

 Log Information:
 $Log: xAKTTdelete.c,v $
 Revision 1.2  2008-11-02 19:55:35  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:42  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:34:35  mw
 update to new DB release 2.0

 * Revision 1.3  94/02/16  16:14:05  16:14:05  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.2  94/01/26  14:00:30  14:00:30  mw (Administrator)
 * delete all paras if para section is clean
 * 
 * Revision 1.1  93/09/02  23:04:37  23:04:37  mw (Administrator)
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xAKTTdelete.c,v 1.2 2008-11-02 19:55:35 mwn Exp $";

int AKTTdelete(void)
{
	extern MEMOBJ sqlmem;
	extern AKTIONS_TYP aktt;
	extern AKTIONSPARA para;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	extern int sprache;

	AKTIONSPARA *paraptr;
	int status=(int)MPOK;
	int anzahl, i;
	char query[_QUERYLEN];

	if (aktt.a_typ_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist AKTT noch in AKT vorhanden ? */
	if (MPAPIid_count((int)_AKTIONS_TYP, (int)_AKTIONEN, (char *)&aktt) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NOAKTTDEL_AKT, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist AKTT noch in AKTDEATIL vorhanden ? */
	if (MPAPIid_count((int)_AKTIONS_TYP, (int)_AKT_DETAIL, (char *)&aktt) != (int)EMPTY)
		{
		UtilMsg((int)MPE_NOAKTTDEL_AD, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Ist AKTT noch in AKTPARA vorhanden ? */
	if (MPAPIid_count((int)_AKTIONS_TYP, (int)_AKTIONSPARA, (char *)&aktt) != (int)EMPTY)
		{
		/* loesche hier alle paras */
		sprintf(query, _SEL_PARA_AKTT, aktt.a_typ_id);
		status = MPAPIdb_sqlquery((int)_AKTIONSPARA, &sqlmem.buffer, query,
                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
		if (status != MPOK)
			{
			UtilMsg((int)MPE_NOAKTTDEL_AKTP, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		if (anzahl > 0)
			{
			for (i=0; i<anzahl && status == (int)MPOK; i++)
				{
				paraptr = (AKTIONSPARA *)sqlmem.buffer;
				(void)memcpy((void *)&para, (void *)&paraptr[i], sizeof(AKTIONSPARA));
				status = AKTPdelete();
				}
			if (status != MPOK)
				return(status);
			}
		}

	status = MPAPIdeleteEntry((int)_AKTIONS_TYP, (char *)&aktt);
	if (status == (int)MPOK)
		{
		bez.s_id=(int)sprache;
		bez.typ=(int)_AKTIONS_TYP;
		bez.bez_id=aktt.bez_id;
		if (MPAPIid_count((int)_BEZEICHNUNG,(int)_AKTIONS_TYP, (char *)&bez) == (int)EMPTY)
			{
			if (MPAPIdeleteEntry((int)_BEZEICHNUNG, (char *)&bez) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOBEZDEL, MSGTYP_ERROR, NULL);
				status=(int)MPERROR;
				}
			}
		if (aktt.textid != (int)_UNDEF)
			{
			txt.typ=(int)_AKTIONS_TYP;
			txt.textid=aktt.textid;
			if (MPAPIdeleteEntry((int)_TEXTE, (char *)&txt) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOTXTDEL, MSGTYP_ERROR, NULL);
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
