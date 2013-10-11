/*************************************************************
 * Modul:     travelDB DBI main procedure
 *
 * Copyright: yafra.org, 2004, switzerland
 *************************************************************/

#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes for ANSI-C */

/* globals */
#include <mpmenlev.h>
#include <mpvardbi.h>
#include <mpvarapi.h>
#include <mpvarlib.h>
#ifdef ps_hpux
#include <locale.h>
#endif
#ifdef ps_linux
#include <locale.h>
#endif
#include "version.h"

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/MainMarco.c,v 1.3 2008-11-17 10:42:51 mwn Exp $";

int MainMarco(int argv, char **argc, int fd)
{
	extern MP_GLOBALPROFIL globprof;
	extern MP_PROFIL prof;
	extern GLOBDATA glob_buffer;
	extern char userid[];
	extern int (*MPfunction_exit)();
	extern FILE *MP_DBIDEBUGFILE;

	extern MEMOBJ sqlmem;
	extern MEMOBJ apimem;           /* defined in api functions.sql */
	extern MEMOBJ dl_mem;           /* dl mem for MATRIX/Planungsboard */
	extern MEMOBJ tdl_mem;          /* tdl mem for MATRIX/Planungsboard */
	extern MEMOBJ dlt_mem;          /* dlt mem for general purpose */
	extern MEMOBJ bm_kommem;        /* kom mem for BM */

	extern MEMOBJ globDLT_MEM;
	extern DLT_VIEW *globDLT_VIEW;

	extern COLORTAB *colorTab;
	extern int OldGraID;

	extern unsigned char bm_dlnatonce;
	extern unsigned char bm_arrkom;
	extern int           bm_lastbid;
	extern unsigned char logging_booking;
	extern unsigned char logging_user;
	extern unsigned char logging_mp;
	extern unsigned char logging_sql;
	extern unsigned char logging_sqltm;
	extern unsigned char alphaordering;
	extern unsigned char selectfromtemp;

	int status;
	int mpusernumber;
	int colorLen;
	char *colorListe;
	char *tmpPtr;

	/* init */
	(void)memset((void *)&glob_buffer, (int)NULL, sizeof(GLOBDATA));
	(void)memset((void *)&globprof, (int)NULL, sizeof(MP_GLOBALPROFIL));
	status        = MPOK;
	OldGraID      = (int)_UNDEF;
	FatalError	  = (int)FALSE;
	/* DebugFlag	  = (int)FALSE; - this is done by PSIPC */
	selectfromtemp = (int)TRUE;
	logging_booking  = (unsigned char)FALSE;
	logging_user  = (unsigned char)FALSE;
	logging_mp    = (unsigned char)TRUE;
	logging_sql   = (unsigned char)FALSE;
	logging_sqltm = (unsigned char)FALSE;
	bm_dlnatonce  = (unsigned char)TRUE;
	bm_lastbid    = (int)_UNDEF;
	bm_arrkom     = (unsigned char)FALSE;
	alphaordering = (unsigned char)TRUE;
	ipcfd         = fd;
	colorTab      = NULL;

	/* MEMOBJ init */
	dl_mem.buffer = NULL;
	dl_mem.alloclen = 0;
	dl_mem.datalen = 0;
	tdl_mem.buffer = NULL;
	tdl_mem.alloclen = 0;
	tdl_mem.datalen = 0;
	dlt_mem.buffer = NULL;
	dlt_mem.alloclen = 0;
	dlt_mem.datalen = 0;
	bm_kommem.buffer = NULL;
	bm_kommem.alloclen = 0;
	bm_kommem.datalen = 0;
	globDLT_MEM.buffer = NULL;
	globDLT_MEM.alloclen = 0;
	globDLT_MEM.datalen = 0;
	globDLT_VIEW = NULL;

#ifdef ps_hpux
	setlocale(LC_ALL, "de_DE.iso88591");
#endif
#ifdef ps_linux
	setlocale(LC_ALL, "en_US.utf8");
#endif

	/* GLOBINIT lesen */
	COMMSTAT   = (char)NULL;
	COMMTYP    = (char)NULL;
	ACTIONTYP  = (char)NULL;
	MENUNR     = (char)NULL;
	FELDNR     = (char)NULL;
	comm.buffer = NULL;
	comm.datalen = 0;
	comm.alloclen = 0;
	(void)MPcomm(RECV, (STARTMEMCHUNK));
	(void)sprintf(MPversiontext, "%s", MAINVERSION);

	/* SQL Memorypointer auf NULL initialisieren */
	sqlmem.buffer = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen = 0;
	apimem.buffer = NULL;
	apimem.alloclen = 0;
	apimem.datalen = 0;

	/* set global profile given from GUI */
	if (comm.datalen == sizeof(MP_GLOBALPROFIL))
		(void)memcpy((void *)&globprof, (void *)comm.buffer, sizeof(MP_GLOBALPROFIL));
	else
		status = MPE_GLOBPROF;

	/* get UID and check it with UNIX UID */
	if (status == MPOK)
		{
		status = PSSYSsetUser(&mpusernumber, globprof.user);
		if (status != MPOK)
			status = MPE_PASSWD;
		}

	/* open logs and DATABASE */
	if (status == MPOK)
		{
		/* local string for log entries */
		char tmp_txt[_CHAR80];

		/* open log file */
		MPlog(_LOGOPEN, 0, globprof.user, __FILE__);

		/* write init infos into internal logfile */
		(void)sprintf(tmp_txt, "DBI daemon process started with PID %d", (int)getpid());
		MPlog(_LOGMP, MSGTYP_INFO, tmp_txt, __FILE__);
		if ( fd >=0 )
			MPlog(_LOGMP, MSGTYP_INFO, "start Berkley Socket IPC", __FILE__);
		else
			MPlog(_LOGMP, MSGTYP_INFO, "start Unix Pipe IPC", __FILE__);
		(void)sprintf(tmp_txt, "user (%s) started from host: %s with display: %s",
		      globprof.user, globprof.hostname, globprof.displayname);
		MPlog(_LOGMP, MSGTYP_INFO, tmp_txt, __FILE__);

		/* open syslog */
		MPsyslog(_LOGOPEN, 0, (char *)NULL);
		MPsyslog(_LOGMP, MPINFO, "TDB: user connected - starting");

		/* open debug files */
		if (MP_DBIDEBUGFILENAME != (char *)NULL)
			{
			MP_DBIDEBUGFILE = fopen(MP_DBIDEBUGFILENAME, _P_APPEND_);
			if (MP_DBIDEBUGFILE == NULL)
				perror("TDB DBI debug file open error");
			}

		/* open database */
		logging_sql = (unsigned char)TRUE;
		MPlog(_LOGMP, MSGTYP_INFO, "Connecting to database ... ", __FILE__);
		status = MPAPIdb_connect(globprof.database, globprof.user, globprof.password);
		MPlog(_LOGMP, MSGTYP_INFO, " connect done !", __FILE__);
		logging_sql = (unsigned char)FALSE;
		}

	/* print debug infos of DB open */
	/* debugflag is only set if daemon is started with -debug flag ! */
	/* so enable logging also already at this point */
	if (DebugFlag)
		{
		logging_sql = (unsigned char)TRUE;
		logging_user  = (unsigned char)TRUE;
		PSSYSdebug(MP_DBIDEBUGFILE, PROGRAMNAME, "%s", MPversiontext);
		PSSYSdebug(MP_DBIDEBUGFILE, PROGRAMNAME, "DB opened with %d", status);
		PSSYSdebug(MP_DBIDEBUGFILE, PROGRAMNAME, "Setting SQL logging - see log files", status);
		}

	/* set signal handling */
	MPfunction_exit = MPDBImain_exit;
	MPinstall_signals(0);

	/* init the userprofile */
	if (status == MPOK)
		{
		status = MPAPIprofile_init(globprof.user, &prof);
		if (status != MPOK)
			MPlog(_LOGMP, MSGTYP_ERROR, "profile init error - no permission", __FILE__);
		}

	/* set globals on GLOB menu */
	if (status == MPOK)
		status = GLOBinit(&prof, &glob_buffer);

	/* init the messages */
	if (status == MPOK)
		status = UtilMsgInit();

	/* get the init colors for graphics */
	if (status == MPOK)
		{
		/* color init */
		colorLen = 0;
		colorListe = NULL;
		status = GRcolorInit(&colorListe, &colorLen);
		}

	/* send global menu strings plus color matrix to GUI */
	if (status == MPOK)
		{
		(void)memcpy((void *)comm.buffer, (void *)&glob_buffer, sizeof(glob_buffer));
		comm.datalen = sizeof(glob_buffer);
		tmpPtr = strcpy((void *)&comm.buffer[comm.datalen], (void *)colorListe);
		comm.datalen = comm.datalen + colorLen;
		COMMSTAT = MESSAGEOK;
		MPfree((void *)colorListe);
		}
	else
		COMMSTAT = MESSAGEERROR;

	/* send feedback to GUI process */
	(void)MPcomm(SEND, DEFMEMCHUNK);

	/******************************************************/
	/* start of main DBI process or end with initerror    */
	/******************************************************/
	if (status == MPOK)               /* Falls kein Fehler aufgetreten          */
		{
		if (DebugFlag)
			PSSYSdebug(MP_DBIDEBUGFILE, PROGRAMNAME, "Start MainLoop now");
		MainLoop(fd);                  /* go to main loop and wait for GUI  */

		(void)MPDBImain_exit(MPOK);    /* clean up and exit                 */
		}
	else                              /* if init errors occured            */
		{
		char logbuf[_RECORDLEN];
		sprintf(logbuf, "initial error - daemon stops with state %d", status);
		MPlog(_LOGMP, MSGTYP_ERROR, logbuf, __FILE__);
		if (DebugFlag)
			PSSYSdebug(MP_DBIDEBUGFILE, PROGRAMNAME, "Error and Exit");

		(void)MPDBImain_exit(MPERROR);    /* clean up and exit                 */
		}
}

int MPDBImain_exit(int aCode)
{
	int status;
	char tmp_txt[_CHAR80];

	extern MEMOBJ sqlmem;
	extern MEMOBJ apimem;           /* defined in api functions.sql */
	extern MEMOBJ dl_mem;           /* dl mem for MATRIX/Planungsboard */
	extern MEMOBJ tdl_mem;          /* tdl mem for MATRIX/Planungsboard */
	extern MEMOBJ dlt_mem;          /* dlt mem for general purpose */
	extern MEMOBJ bm_kommem;        /* kom mem for BM */
	extern MEMOBJ globDLT_MEM;
	extern DLT_VIEW *globDLT_VIEW;
	extern COLORTAB *colorTab;

	if (DebugFlag)
		PSSYSdebug(MP_DBIDEBUGFILE, PROGRAMNAME, "Clean up and exit now with code %d", aCode);

	MPfree((void *)sqlmem.buffer); /* free SQL buffer                        */
	MPfree((void *)apimem.buffer); /* free API memory                        */
	MPfree((void *)globDLT_VIEW);  /* free global DLT memory                 */
	MPfree((void *)comm.buffer);   /* free comm buffer                       */
	MPfree((void *)colorTab);      /* free color array                       */
	MPfreeobj(&dl_mem);            /* free dl mem for MATRIX                 */
	MPfreeobj(&tdl_mem);           /* free tdl mem for MATRIX                */
	MPfreeobj(&dlt_mem);           /* free dlt mem                           */
	MPfreeobj(&bm_kommem);         /* free bm_kom mem                        */
	UtilMsgFree();		             /* free message buffers                   */

	status = MPAPIdb_release();	 /* close db session                       */

	(void)sprintf(tmp_txt, "Database released with status %d", status);
	MPlog(_LOGMP, MSGTYP_INFO, tmp_txt, __FILE__);

	MPlog(_LOGCLOSE, 0, NULL, __FILE__);  /* close log files                 */
	MPsyslog(_LOGCLOSE, 0, NULL);  /* close syslog                           */
	if (MP_DBIDEBUGFILE != NULL)
		(void)fclose(MP_DBIDEBUGFILE); /* close debug files                      */
	exit(aCode);
}
