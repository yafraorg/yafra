/*D***********************************************************
 * File:      cmdmain.c
 * Module:    Command-server daemon process main function
 *                                                            
 * Copyright: yafra.org     
 **************************************************************/
static char rcsid[]="$Header: see github.com yafra $";

#include <stdio.h>

#ifdef ps_hpux
#include <sys/stat.h>
#include <sys/types.h>
#endif

#ifdef ps_linux
#include <sys/stat.h>
#include <sys/types.h>
#endif

#ifdef ps_cygwin
#include <sys/stat.h>
#include <sys/types.h>
#endif

#include <pscmd.h>
#include "cmd.h"

/*F--------------------------------------------------------------------------
 *  Function:	CMDlogOpen()
 *					Open the CMD log file 
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void CMDlogOpen(void)
{
	extern FILE *fplog;

	char log_date[10];
	char log_time[10];
	char logbuffer[1024];

	/*--- Open log file --------*/
	fplog = fopen(CMDLOGNAME, "a");
	if (fplog == NULL)
		perror("\npsfifo: cannot open logfile ");
	else 
		{
		(void)chmod(CMDLOGNAME, PERMS);  /*!!! UNIX specific */

		/*--- Get date and time of start ----*/
		PSSYSwriteDate(0, log_date, log_time);
		(void)fprintf(fplog, "\n\n%s %s %s START LOG SESSION\n", log_date, log_time, PRGNAME);
		}
}


/*F--------------------------------------------------------------------------
 *  Function:	CMDlogWrite()
 *					Write and append to opened log file
 *  In:			-the message
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void CMDlogWrite(char *msg)
{
	extern FILE *fplog;
	char date[10];
	char time[10];

	/*--- Write the message ------------*/
	PSSYSwriteDate(0, date, time);
	(void)fprintf(fplog, "%s %s %s %s\n", date, time, PRGNAME, msg);
	(void)fflush(fplog);
}


/*F--------------------------------------------------------------------------
 *  Function:	CMDlogClose()
 *					Close the CMD log file 
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void CMDlogClose(void)
{
	extern FILE *fplog;
	char	log_date[10];
	char	log_time[10];
	char	logbuffer[1024];
	int	cret;

	/*--- write log close entry ---------------*/
	PSSYSwriteDate(0, log_date, log_time);
	(void)fprintf(fplog, "%s %s %s END LOG SESSION\n", log_date, log_time, PRGNAME);

	/*--- Close log file --------*/
	cret = fclose(fplog);
	if (cret == EOF)
		perror("\npsfifo: cannot close logfile ");
}
