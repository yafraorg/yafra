/*D***********************************************************
 * Modul:     DBI - database action
 *            STATUS_WERTE a higher form for
 *            getting STATUS_WERTE over a BEZEICHNUNG and STATYP
 *
 *            attribut is the typ of STATUS_WERTE
 *            name is a state of the typ from above
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xSTAgetattribut.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

int getAttribut(int attribut, char *name)
{
	extern STATUS_WERTE sta;

	int id;
	int status = (int)MPOK;

	/* set typ of status from argument */
	sta.typ = attribut;

	if (*name != NULL)
		{
		id = MPAPIselectEntry((int)_STATUS_WERTE, name, (char *)&sta,
		                 sizeof(STATUS_WERTE), (int)sizeof(sta.sta_id));
		if (id == (int)_UNDEF)
			{
			UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
			sta.sta_id=(int)_UNDEF;
			status=(int)MPERROR;
			}
		}
	else
		{
		sta.sta_id = (int)1;
		id = MPAPIselectOneId((int)_STATUS_WERTE, (int)1, (char *)&sta);
		if (id == (int)_UNDEF)
			{
			UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
			sta.sta_id=(int)_UNDEF;
			status=(int)MPERROR;
			}
		else
			status=(int)MPWARNING;  /*!!! this could cause problems - find better solution !!!*/
		}
		
	return(status);
}
