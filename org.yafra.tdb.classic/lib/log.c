/*D************************************************************/
/* Modul:     log an operation                                */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/lib/log.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <pssys.h>
#include <mpobjdef.h>
#include <mpmsg.h>
#include <mpdef.h>
#include <mpprolib.h>
#include <psportable.h>

#ifdef ps_unix
#include <syslog.h>
#endif

#ifdef ps_win
#define NAMELOGBOOKING "\\temp\\MPbookinglog%s.txt"
#define NAMELOGUSER    "\\temp\\MPuserlog%s.txt"
#define NAMELOGMP      "\\temp\\MPintlog%s.txt"
#define NAMELOGSQL     "\\temp\\MPSQLlog%s.txt"
#else
#define NAMELOGBOOKING "/tmp/MPbookinglog%s"
#define NAMELOGUSER    "/tmp/MPuserlog%s"
#define NAMELOGMP      "/tmp/MPintlog%s"
#define NAMELOGSQL     "/tmp/MPSQLlog%s"
#endif

extern FILE *fplogBooking;
extern FILE *fplogUser;
extern FILE *fplogMP;
extern FILE *fplogSQL;
/* extern int errno; */

/*F************************************************************
 * Function:  MPlog                                           
 *                                                            
 * Parameter: logtyp   Log Typ  (_LOGUSER,_LOGMP,_LOGSQL)     
 *            msgtyp   typ of message (MSGTYP_MSG, MSGTYP_SQL 
 *            msg      Message to print in Logfile            
 *                     im OPEN Fall ist es die USERID
 *************************************************************/
void MPlog(int logtyp, int msgtyp, char *msg, char *file)
{
	char log_date[25];
	char log_time[20];
	FILE *filepointer = NULL;
	int cret;
	char logbuffer[1024];
	char filename[256];

	MPdate_makecurrent(log_date, log_time);

	switch (logtyp)
		{
		case _LOGBOOKING:
			filepointer = fplogBooking;
			break;
		case _LOGUSER:
			filepointer = fplogUser;
			break;
		case _LOGMP:
			filepointer = fplogMP;
			break;
		case _LOGSQL:
			filepointer = fplogSQL;
			break;
		case _LOGOPEN:
			(void)sprintf(logbuffer, "%s%sSTART LOG SESSION %s %s", _P_EOL_,
			_P_EOL_, log_date, _P_EOL_);

			(void)sprintf(filename, NAMELOGBOOKING, msg);
			fplogBooking=fopen(filename, _P_APPEND_);
			if (fplogBooking == NULL)
				perror("MARCO POLO Buchungslog konnte nicht ge�ffnet werden");

			(void)sprintf(filename, NAMELOGUSER, msg);
			fplogUser=fopen(filename, _P_APPEND_);
			if (fplogUser == NULL)
				perror("MARCO POLO Benutzer-Logdatei konnte nicht ge�ffnet werden");

			(void)sprintf(filename, NAMELOGMP, msg);
			fplogMP=fopen(filename, _P_APPEND_);
			if (fplogMP == NULL)
				perror("MARCO POLO interne Logdatei konnte nicht ge�ffnet werden");
			else
				(void)fprintf(fplogMP, "%s", logbuffer);

			(void)sprintf(filename, NAMELOGSQL, msg);
			fplogSQL=fopen(filename, _P_WRITE_);
			if (fplogSQL == NULL)
				perror("MARCO POLO SQL Logdatei konnte nicht ge�ffnet werden");
			else
				(void)fprintf(fplogSQL, "%s", logbuffer);
			return;
		case _LOGCLOSE:
			(void)sprintf(logbuffer, "END LOG SESSION %s %s", log_date,
			 _P_EOL_);
			if (fplogBooking != NULL)
				{
				cret = fclose(fplogBooking);
				if (cret == EOF)
					perror("MARCO POLO Fehler beim schliessen des Buchungslog");				
				}
			if (fplogUser != NULL)
				{
				cret = fclose(fplogUser);
				if (cret == EOF)
					perror("MARCO POLO Fehler beim schliessen des Benutzerlogs");				
				}
			if (fplogMP != NULL)
				{
				(void)fprintf(fplogMP, "%s", logbuffer);
				cret = fclose(fplogMP);
				if (cret == EOF)
					perror("MARCO POLO Fehler beim schliessen des internen Log");				
				}
			if (fplogSQL != NULL)
				{
				(void)fprintf(fplogSQL, "%s", logbuffer);
				cret = fclose(fplogSQL);
				if (cret == EOF)
					perror("MARCO POLO Fehler beim schliessen des SQL log");
				}
			return;
		default:
			return;
		}

	if (filepointer != NULL)
		{
		switch(logtyp)
			{
			case _LOGBOOKING:
			case _LOGUSER:
				(void)fprintf(filepointer, "%s: %s%s", log_date, msg, _P_EOL_);
				break;
			case _LOGMP:
				(void)fprintf(filepointer, "%s %d: %s%s", log_date,
				              msgtyp, msg, _P_EOL_);
				break;
			case _LOGSQL:
				(void)fprintf(filepointer, "----%s %s %d%s", log_date, log_time, msgtyp, _P_EOL_);
				(void)fprintf(filepointer, "%s%s", msg, _P_EOL_);
				break;
			}
		(void)fflush(filepointer);
		}
}

void MPsyslog(int logtyp, int msgtyp, char *msg)
{
	switch (logtyp)
		{
		case _LOGOPEN:
			PSSYSsyslog(_PSLOG_OPEN, PROGRAMNAME, msg);
			break;
		case _LOGCLOSE:
			PSSYSsyslog(_PSLOG_CLOSE, PROGRAMNAME, msg);
			break;
		default:
			switch (msgtyp)
				{
				case MPDBERROR:
				case MPERROR:
					PSSYSsyslog(_PSLOG_ERROR, PROGRAMNAME, msg);
					break;
				case MPWARNING:
					PSSYSsyslog(_PSLOG_WARNING, PROGRAMNAME, msg);
					break;
				case MPINFO:
					PSSYSsyslog(_PSLOG_INFO, PROGRAMNAME, msg);
					break;
				case MPDEBUG:
					PSSYSsyslog(_PSLOG_DEBUG, PROGRAMNAME, msg);
					break;
				case MPEMERG:
					PSSYSsyslog(_PSLOG_EMERG, PROGRAMNAME, msg);
					break;
				}
			break;
		}
}
