/*D***********************************************************
 * Modul:     DBI - database action
 *            Grafik
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xGRAinput.c,v 1.2 2008-11-02 19:55:38 mwn Exp $";

int GRAinput(int len , char *buffer )
{
	extern GRAPHIK gra;
	extern DIENST_TRAEGER dlt;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	extern int sprache;

	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;
	int id;

	/* init */
	if (ACTIONTYP == (unsigned char)INSERT )
		{
		gra.gra_id=(int)_UNDEF;
		gra.textid=(int)_UNDEF;
		txt.textid=(int)_UNDEF;
		}

	/* get menu */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL );
	if (status != (int)MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		gra.gra_id = (int)_UNDEF;
		return((int)MPERROR);
		}

	/* check up BEZEICHNUNG */
	if (*to_buffers[MGRA_BEZ] == NULL)
		{
		UtilMsg((int)MPE_NOGRA, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* manage */
	switch(ACTIONTYP)
		{
		case (unsigned char)INSERT:
		case (unsigned char)UPDATE:
			bez.s_id=(int)sprache;
			bez.typ=(int)_GRAPHIK;
			(void)copyTextTo(bez.bez, to_buffers[MGRA_BEZ], (int)_BEZLEN);
			if (*to_buffers[MGRA_DLT] != NULL)
				{
				dlt.stufe = (int)1;
				gra.dlt_id = MPAPIselectEntry((int)_DIENST_TRAEGER, to_buffers[MGRA_DLT],
		         (char *)&dlt, sizeof(DIENST_TRAEGER), sizeof(gra.dlt_id));
				if (gra.dlt_id != (int)_UNDEF)
					{
					id = MPAPIselectOneId((int)_GRAPHIK, gra.dlt_id, (char *)&gra);
					if (ACTIONTYP == (unsigned char)INSERT && id != (int)_UNDEF)
						gra.dlt_id = (int)_UNDEF;
					}
				}
			if (gra.dlt_id == (int)_UNDEF || dlt.stufe != (int)1)
				{
				UtilMsg((int)MPE_HOSTFIELD, MSGTYP_ERROR, NULL);
				gra.gra_id = (int)_UNDEF;
				status = (int)MPERROR;
				}
			break;
		case (unsigned char)MPDELETE:
			if (MPAPIselectEntry(_GRAPHIK, to_buffers[MGRA_BEZ], (char *)&gra,
			    sizeof(gra), sizeof(gra.gra_id)) == (int)_UNDEF)
				{
				UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
				status = (int)MPERROR;
				}
			break;
		}

	if (status == (int)MPOK)
		{
		/* write text or delete it */
		txt.typ		=	(int)_GRAPHIK;
		txt.s_id		=	(int)sprache;
		txt.textid	=	gra.textid;
		gra.textid = xTxtWrite(to_buffers[MGRA_TEXT]);

		/* write entry or delete entry */
		status = WriteEntry( (int)_GRAPHIK, (char *)&gra, &bez);
		if (status != (int)MPOK)
			gra.gra_id=(int)_UNDEF;
		else
			(void)WriteInfo((int)_GRAPHIK, (char *)&gra, buffer);
		}

	UtilSplitFreeMenubuffer(to_buffers);

	return(status);
}
