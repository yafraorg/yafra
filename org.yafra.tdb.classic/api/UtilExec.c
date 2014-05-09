/*D***********************************************************
 * Modul:     DBI - utilities                     UtilExec.c
 *            execute an action
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */
#include <signal.h>
#include <pssys.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/UtilExec.c,v 1.2 2008-11-02 19:55:49 mwn Exp $";

#define BACKGROUNDPROZ		" &\0"
#define SIZEOFBP				3


/*F--------------------------------------------------------------------------
 *  Function:	UtilExec ()
 *					submit a command to sh 
 *
 *  In:			-command string, execution option code 
 *  out:			-
 *  Return:		-termination status returned by system(3S) 
 *---------------------------------------------------------------------------
 */
int UtilExec(char *command, int code)
{
	char *ptr;
	int cret;

	ptr = command;
	ptr += strlen(command);

	switch (code) 
		{
		case NORMAL:
			*ptr = '\0';
			break; 
		case BACKGROUND:
#ifdef ps_unix
			(void)memcpy(ptr, BACKGROUNDPROZ, (int)SIZEOFBP);
#else
			*ptr = '\0';
#endif
			break; 
		default :
			*ptr = '\0';
			break; 
		}

	/*---let it execute by sh ----*/	
#ifdef ps_unix
#ifdef ps_osx
	signal(SIGCHLD, SIG_IGN);
#else
	signal(SIGCLD, SIG_IGN);
#endif
#endif
	cret = PSSYSexecute(command); /* call to PSSSYLIB */

	/* override the 'cret' till I now what the return of system */
	/* exactly means */
	cret = (int)MPOK;

	return(cret);
}
