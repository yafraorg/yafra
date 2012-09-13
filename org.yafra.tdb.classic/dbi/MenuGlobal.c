/*D************************************************************/
/* Modul:     get global data's from the db                   */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/MenuGlobal.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

static int LABmake_file(void);

int MenuGlobal(GLOBDATA *aGlob_buffer)
{
	extern MP_PROFIL prof;

	int status = (int)MPOK;

	switch(ACTIONTYP)
		{
		/* re/initialize all objects of the daemon */
		case GLOBINIT:
			InitGlobal(aGlob_buffer);
			break;

		case LABELINIT:
			status = InitLAB(atoi(comm.buffer));
			break;

		case MAKELABELFILE:
			status = LABmake_file();
			break;

		/* user made changes on the global mask - process it and save it */
		case GLOBSEND:
			status = GLOBsave(&prof, aGlob_buffer);
			break;
		}

	return(status);
}


static int LABmake_file(void)
{
	extern char sqlquery[];

	int status = (int)MPOK;

	return(status);
}
