/*D***********************************************************
 * Modul:     DBI - database delete
 *            Kategorie
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKATdelete.c,v 1.2 2008-11-02 19:55:35 mwn Exp $";

#define MSG1	(int)134
#define MSG2	(int)135
#define MSG3	(int)137
#define MSG4	(int)138
#define MSG5	(int)139

static int KATdeleteOneEntry(KATEGORIE *);

int KATdelete(void)
{
	extern KATEGORIE kat;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	extern int sprache;

	int status=(int)MPOK;

	if (kat.kat_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_IDXISUNDEF, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_KATEGORIE, (int)_PREIS, (char *)&kat) != (int)EMPTY)
		{
		UtilMsg((int)MSG3, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_KATEGORIE, (int)_RESERVATION, (char *)&kat) != (int)EMPTY)
		{
		UtilMsg((int)MSG4, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_KATEGORIE, (int)_KONT_DETAIL, (char *)&kat) != (int)EMPTY)
		{
		UtilMsg((int)MSG5, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_KATEGORIE, (int)_DIENST_TRAEGER, (char *)&kat) != (int)EMPTY)
		{
		UtilMsg((int)MSG1, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MPAPIid_count((int)_KATEGORIE, (int)_KATEGORIE, (char *)&kat) != (int)EMPTY)
		{
		UtilMsg((int)MSG2, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	status = KATdeleteOneEntry(&kat);
	
	return(status);
}

/*************************************************************
 * Function:  KATdeleteOneEntry
 * Typ:       private for KATdelete
 * Desc:      delete one KAT with TXT and BEZ
 *************************************************************/
static int KATdeleteOneEntry(KATEGORIE *localkat)
{
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	KAPA localkapa;
	int status = MPOK;

	/* L�sche nun KAPA der KAT */
	localkapa.kat_id = localkat->kat_id;
	localkapa.tdl_id = (int)_UNDEF;
	(void)MPAPIdeleteEntry((int)_KAPA, (char *)&localkapa);

	/* L�sche nun KAT */
	status = MPAPIdeleteEntry((int)_KATEGORIE, (char *)localkat);
	if (status == (int)MPOK)
		{
		/* L�sche Bezeichnung und Texte */
		bez.bez_id=localkat->bez_id;
		status = MPAPIid_count((int)_BEZEICHNUNG, (int)_KATEGORIE, (char *)&bez);
		if (status == EMPTY && localkat->bez_id != _UNDEF)
			{
			bez.typ=(int)_KATEGORIE;
			if (MPAPIdeleteEntry((int)_BEZEICHNUNG, (char *)&bez) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOBEZDEL, MSGTYP_ERROR, NULL);
				status=(int)MPERROR;
				}
			}
		if (localkat->textid != _UNDEF)
			{
			txt.typ=(int)_KATEGORIE;
			txt.textid=localkat->textid;
			if (MPAPIdeleteEntry((int)_TEXTE, (char *)&txt) == (int)MPERROR)
				{
				UtilMsg((int)MPE_NOTXTDEL, MSGTYP_ERROR, NULL);
				status=(int)MPERROR;
				}
			}
		}
	else /* konnte Objekt nicht l�schen */
		{
		UtilMsg((int)MPE_NODEL, MSGTYP_ERROR, NULL);
		status=(int)MPERROR;
		}

	return(status);
}
