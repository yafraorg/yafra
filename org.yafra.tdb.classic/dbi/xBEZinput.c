/*D***********************************************************
 * Modul:     DBI - database action
 *            Bezeichnung
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xBEZinput.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

int BEZinput(int len , char *buffer )
{
	extern BEZEICHNUNG bez;
	extern STATUS_WERTE sta;
	extern int sprache;

	BEZEICHNUNG frombez, tobez, typbez;
	SPRACHEN fromspr;
	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;
	int anzahl;

	/* only UPDATE mode is possible */
	if (ACTIONTYP == (unsigned char)MPDELETE || ACTIONTYP == (unsigned char)INSERT)
		return((int)MPOK);
	/*!!! add an error message here - don't send back an OK */

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		bez.bez_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	/* evaluate the FROM SPRACHE */
	if (*to_buffers[MBEZ_SPR] == NULL)
		{
		UtilMsg((int)MPE_NOSPR, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}
	fromspr.s_id = MPAPIselectEntry((int)_SPRACHEN, to_buffers[MBEZ_SPR],
	           (char *)&fromspr, sizeof(SPRACHEN), sizeof(fromspr.s_id));

	/* evaluate the TYP of the changing BEZEICHNUNG */
	if (*to_buffers[MBEZ_BEZTYP] == NULL)
		{
		UtilMsg((int)MPE_NOUNIQUEBEZ, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}
	typbez.s_id = fromspr.s_id;
	typbez.typ  = (int)_UNDEF;
	(void)strcpy(typbez.bez, to_buffers[MBEZ_BEZTYP]);
	typbez.bez_id = MPAPIselectEntry((int)_BEZEICHNUNG, to_buffers[MBEZ_BEZTYP],
	    (char *)&typbez, sizeof(BEZEICHNUNG), sizeof(typbez.bez_id));
	/*!!! check return and make error if needed (MPE_NOTYP) */

	/* evaluate the FROM BEZEICHNUNG */
	if (*to_buffers[MBEZ_BEZ] == NULL)
		{
		UtilMsg((int)MPE_NOBEZ, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}
	frombez.typ = typbez.typ;
	frombez.s_id = fromspr.s_id;
	(void)strcpy(frombez.bez, to_buffers[MBEZ_BEZ]);
	frombez.bez_id = MPAPIselectEntry((int)_BEZEICHNUNG, to_buffers[MBEZ_BEZ],
	   (char *)&frombez, sizeof(BEZEICHNUNG), sizeof(frombez.bez_id));

	/* set TO BEZEICHNUNG */
	tobez.s_id = fromspr.s_id;
	tobez.typ = frombez.typ;
	tobez.bez_id = frombez.bez_id;
	(void)strcpy(tobez.bez, to_buffers[MBEZ_UEBERBEZ]);

	/* free up menu strings */
	UtilSplitFreeMenubuffer(to_buffers);

	/* security check */
	if (tobez.bez_id < 1 || tobez.s_id < 1)
		{
		UtilMsg((int)MPE_NOBEZ, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* update */
	status=MPAPIupdateEntry((int)_BEZEICHNUNG, (char *)&tobez, (BEZEICHNUNG *)NULL);
	if (status == (int)MPE_NOINSUPDDEL)
		status = (int)MPOK;
	else if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_ERROR, NULL);
		status = (int)MPERROR;
		bez.bez_id=(int)_UNDEF;
		}

	return(status);
}
