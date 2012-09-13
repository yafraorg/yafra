/*D***********************************************************
 * Modul:     DBI - database select                           
 *            Dienstleistungstraeger
 *            get numbers of DLN in a DLT element
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xDLTnumofdln.c,v 1.2 2008-11-02 19:55:34 mwn Exp $

 Log Information:
 $Log: xDLTnumofdln.c,v $
 Revision 1.2  2008-11-02 19:55:34  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:42  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:35:24  mw
 update to new DB release 2.0

 * Revision 1.2  94/02/16  18:20:12  18:20:12  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.1  93/09/17  13:01:02  13:01:02  mw (Administrator)
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLTnumofdln.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

/*************************************************************
 * function:  DLTnum_of_dln
 * typ:       public
 * desc:      get number of space for dln's on a dlt and
 *            their direct sub-dlt's
 * input:     dlt-id
 * output:    count of dln's 
 *************************************************************/
int DLTnum_of_dln(int dlt_id, int *countofplaces)
{
	int count;
	int id;
	DIENST_TRAEGER dlt;

	id = MPAPIselectOneId((int)_DIENST_TRAEGER, dlt_id, (char *)&dlt);
	if (id == (int)_UNDEF)
		return((int)MPERROR);

	count = MPAPIid_count((int)_DIENST_TRAEGER, (int)_DIENST_TRAEGER,
	                (char *)&dlt);
	if (count < 1)
		count = 1;

	*countofplaces = count;

	return((int)MPOK);
}
