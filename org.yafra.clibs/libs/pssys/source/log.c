/*D***********************************************************
 * copyright: Yafra.org, Switzerland, www.pisoag.com
 *
 * modul:     create debug and/or log messages
 *            use syslog facility if possible
 *
 * CVS tag:   $Name:  $
 * author:    $Author: mwn $
 * revision:  $Revision: 1.1.1.1 $
 **************************************************************/
static char rcsid[]="$Id: log.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";
static char tagid[]="$Name:  $"; /* tagid is only once in the main() needed */

#ifndef __C2MAN__
#include "version.h"
#endif

/* system includes */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <stdarg.h>

#ifdef ps_unix
#include <syslog.h>
#endif
#ifdef ps_win
#include <windows.h>
#endif

/* piso includes */
#include <pssys.h>
#include <psportable.h>

#define DATETIME_LEN 20

/************************************************************
 * create a debug message and write it to aDebugfile
 *
 * print a message on aDebugfile for debug reason. As default
 * there will be first the word "debug" printed. The aDebugfile
 * has to be a FILE descriptor which is already open ! (like stdout)
 * This function uses variable arguments like printf() !
 * The aMsg should be not longer than PS_MAXMSGLEN.
 *
 * returns     nothing
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator, 1994
 **************************************************************/
PS_DLLAPI void PSSYSdebug(FILE *aDebugfile,  /* debug file */
                char *aPrgname, /* programm name for identify */
                const char *aMsg,    /* message to print */
                ... )
{
	int cret;
	char tmpbuf[2*PS_MAXMSGLEN];
	va_list ap;

	/* if no msg return */
	if (aMsg == NULL)
		return;

	/* manage variable arguments */
	va_start(ap, aMsg);

	cret = vsprintf(tmpbuf, aMsg, ap);
	if (aDebugfile == NULL)
		{
		if (aPrgname == NULL)
			cret = printf("debug: %s%s", tmpbuf, _P_EOL_);
		else
			cret = printf("debug %s: %s%s", aPrgname, tmpbuf, _P_EOL_);
		}
	else
		{
		if (aPrgname == NULL)
			cret = fprintf(aDebugfile, "debug: %s%s", tmpbuf, _P_EOL_);
		else
			cret = fprintf(aDebugfile, "debug %s: %s%s", aPrgname, tmpbuf, _P_EOL_);
		cret = fflush(aDebugfile);
		}

	va_end(ap);
}

/************************************************************
 * log a message to a file
 *
 * log a message to a file. Use first the _PSLOG_OPEN to
 * open the logging file and after work close it with
 * _PSLOG_CLOSE.
 * This function uses variable arguments like printf() !
 * The aMsg should be not longer than PS_MAXMSGLEN.
 *
 * returns     nothing
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator, 1994
 **************************************************************/
PS_DLLAPI void PSSYSlog(int aLogtype,    /* type of log described in pssys.h */
              char *aPrgname,  /* name of programm */
              char *aFile,     /* name of file */
              const char *aMsg,  /* message to log */
              ...	)
{
	static FILE *FPlogfile;

	va_list ap;
	char tmpbuf[2*PS_MAXMSGLEN];

	char datestr[DATETIME_LEN];
	char timestr[DATETIME_LEN];

	int cret;
	char *pret;

	char logbuffer[PS_MAXMSGLEN];
	char filename[PS_FILENAMELEN];

	PSSYSwriteDate((time_t)0,datestr, timestr, (size_t)DATETIME_LEN, PSSYS_DAT_GERMAN);

	switch (aLogtype)
		{
		case _PSLOG_OPEN:
			if (*aFile == NULL)
				(void)strcpy(filename, PS_DEFAULTLOGNAME);
			else
				(void)strcpy(filename, aFile);

			cret = sprintf(logbuffer, "START LOG SESSION %s %s from program %s",
              datestr, timestr, aPrgname);
			FPlogfile = fopen(filename, _P_APPEND_);
			if (FPlogfile == NULL)
				perror("Benutzer-Logdatei konnte nicht geoeffnet werden");
			else
				cret = fprintf(FPlogfile, "%s%s%s", logbuffer, _P_EOL_, _P_EOL_);
			return;

		case _PSLOG_CLOSE:
			cret = sprintf(logbuffer, "END   LOG SESSION %s %s", datestr, timestr);
			if (FPlogfile != NULL)
				{
				cret = fprintf(FPlogfile, "%s%s%s%s", _P_EOL_, logbuffer, _P_EOL_, _P_EOL_);
				cret = fclose(FPlogfile);
				if (cret == EOF)
					perror("Fehler beim schliessen des Benutzerlogs");
				}
			return;

		default:
			break;
		}

	if (FPlogfile != NULL)
		{
		/* if no msg return */
		if (aMsg == NULL)
			return;

		/* manage variable arguments */
		va_start(ap, aMsg);
		cret = vsprintf(tmpbuf, aMsg, ap);

		cret = fprintf(FPlogfile, "%s %s %s%s", datestr, timestr, tmpbuf, _P_EOL_);
		cret = fflush(FPlogfile);

		va_end(ap);
		}
}


/************************************************************
 * log a message to the syslog() or NT Event facility
 *
 * log a message to the syslog() or NT Event facility.
 * This function uses variable arguments like printf() !
 * The aMsg should be not longer than PS_MAXMSGLEN.
 *
 * returns     nothing
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator, 1994
 **************************************************************/
PS_DLLAPI void PSSYSsyslog(int aLogtype,  /* type of log described in pssys.h */
                 char *aPrgname, /* name of programm */
                 const char *aMsg,    /* message to log */
                 ... )
{
	int cret;
	char tmpbuf[2*PS_MAXMSGLEN];
	va_list ap;


#ifdef ps_win
	static HANDLE log_hndl = NULL;
	DWORD	Estrlen = 0;
	WORD priority;
#else
	int priority;
#endif

#ifdef ps_win
	priority = (WORD)0;
	switch (aLogtype)
		{
		case _PSLOG_OPEN:
			log_hndl = RegisterEventSource(NULL, TEXT(aPrgname));
			break;
		case _PSLOG_CLOSE:
			DeregisterEventSource(log_hndl);
			log_hndl = NULL;
			break;
		case _PSLOG_ERROR:
			priority = EVENTLOG_ERROR_TYPE;
			break;
		case _PSLOG_WARNING:
			priority = EVENTLOG_WARNING_TYPE;
			break;
		case _PSLOG_INFO:
			priority = EVENTLOG_INFORMATION_TYPE;
			break;
		default:
			priority = EVENTLOG_INFORMATION_TYPE;
			break;
		}

	if (priority != (WORD)0)
		{
		/* if no msg or loghandle return */
		if (aMsg == NULL || log_hndl == NULL)
			return;
		/* manage variable arguments */
		va_start(ap, aMsg);
		cret = vsprintf(tmpbuf, aMsg, ap);
		Estrlen = strlen(tmpbuf);
		ReportEvent(log_hndl, // handle of event source
		  priority,				  // event type
		  0,                  // event category
		  0,                  // event ID
		  NULL,               // current user's SID
		  1,                  // strings in lpszStrings
		  0,                  // no bytes of raw data
		  tmpbuf,             // array of error strings
		  NULL);              // no raw data
		va_end(ap);
		}
#endif

#ifdef ps_unix
	priority = 0;
	switch (aLogtype)
		{
		case _PSLOG_OPEN:
			openlog(aPrgname, LOG_PID, LOG_USER);
			break;
		case _PSLOG_CLOSE:
			closelog();
			break;
		case _PSLOG_EMERG:
			priority = LOG_EMERG | LOG_USER;
			break;
		case _PSLOG_ERROR:
			priority = LOG_ERR | LOG_USER;
			break;
		case _PSLOG_WARNING:
			priority = LOG_WARNING | LOG_USER;
			break;
		case _PSLOG_INFO:
			priority = LOG_INFO | LOG_USER;
			break;
		case _PSLOG_DEBUG:
			priority = LOG_DEBUG | LOG_USER;
			break;

		default:
			priority = LOG_INFO | LOG_USER;
			break;
		}

	if (priority != 0)
		{
		if (aMsg == NULL)
			return;
		/* manage variable arguments */
		va_start(ap, aMsg);
		cret = vsprintf(tmpbuf, aMsg, ap);
		syslog(priority, "%s", tmpbuf);
		va_end(ap);
		}
#endif
}


/************************************************************
 * print a Posix errno message
 *
 * print a POSIX system errno message. The errno is taken
 * by the argument aErrorno ! The aOutputfile has to be
 * a FILE descriptor which is already open !
 * This function uses variable arguments like printf() !
 * The aMsg should be not longer than PS_MAXMSGLEN.
 *
 * returns     nothing
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator, 1994
 **************************************************************/
PS_DLLAPI void PSSYSerrorlog(int aErrorno,  /* system errorno */
                 FILE *aOutputfile, /* output file descriptor */
                 char *aPrgname, /* name of programm */
                 const char *aMsg,    /* message to log */
                 ... )
{
	int cret;
	char tmpbuf[2*PS_MAXMSGLEN];
	char errormsg[PS_MAXMSGLEN];
	va_list ap;
	FILE *outfile;

	/* if no msg return */
	if (aMsg == NULL)
		return;

	/* if no FILE descr. set to stdout */
	if (aOutputfile == NULL)
		outfile = stdout;
	else
		outfile = aOutputfile;

	/* manage variable arguments */
	va_start(ap, aMsg);

	cret = sprintf(errormsg, "%s", strerror(aErrorno));

	cret = vsprintf(tmpbuf, aMsg, ap);
	if (aPrgname == NULL)
		cret = fprintf(aOutputfile, "system error: %s%s", tmpbuf, _P_EOL_);
	else
		cret = fprintf(aOutputfile, "system error %s: %s%s", aPrgname, tmpbuf, _P_EOL_);
	cret = fprintf(aOutputfile, "  with msg no (%d): %s%s", aErrorno, errormsg, _P_EOL_);
	cret = fflush(aOutputfile);

	va_end(ap);
}
