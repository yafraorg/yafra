/*D***********************************************************
 * Modul:     DBI - database delete
 *            PCX
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xPCXdelete.c,v 1.2 2008-11-02 19:55:36 mwn Exp $

 Log Information:
 $Log: xPCXdelete.c,v $
 Revision 1.2  2008-11-02 19:55:36  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:36:49  mw
 update to new DB release 2.0

 * Revision 1.2  94/02/16  18:20:50  18:20:50  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.1  93/07/16  00:15:22  00:15:22  mw (Administrator)
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xPCXdelete.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

#define MSG1	(int)20
#define MSG2	(int)128
#define MSG3	(int)130

int PCXdelete(void)
{
	extern PCX_FILES pcx;
	extern BEZEICHNUNG bez;

	extern int sprache;

	char message[RECLAENGE];
	int status=(int)MPOK;

	if(pcx.pcx_id != (int)_UNDEF) {
		status=MPAPIdeleteEntry((int)_PCX_FILES, (char *)&pcx);

		if (status == (int)MPOK) {

			bez.s_id=(int)sprache;
			bez.typ=(int)_PCX_FILES;
			bez.bez_id=pcx.bez_id;
			if(MPAPIid_count((int)_BEZEICHNUNG,(int)_PCX_FILES, (char *)&bez) == (int)EMPTY) {
				if(MPAPIdeleteEntry((int)_BEZEICHNUNG, (char *)&bez) == (int)MPERROR) {
					(void)find_text_nr((int)MSG3, message);
					xSqlMessage(message);
					status=(int)MPERROR;
				}
			}
		} else {
			(void)find_text_nr((int)MSG2, message);
			xSqlMessage(message);
			status=(int)MPERROR;
		}
	} else {
		(void)find_text_nr((int)MSG1, message);
		xSqlMessage(message);
		status=(int)MPERROR;
	}
	
	return(status);
}
