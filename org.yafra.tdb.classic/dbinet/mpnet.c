/*D***********************************************************
 * Modul:     DBINET - mpnet main()
 *            travelDB light server in C with own protocol
 *            or XML or WebServices
 *
 * Copyright: yafra.org, Switzerland, 2004
 *
 * PISO SCM:  TAG $Name:  $
 * Author:    $Author: mwn $
 * Revision:  $Revision: 1.8 $
 **************************************************************/

/* RCS static ID */
static char rcsid[]="$Id: mpnet.c,v 1.8 2008-11-23 15:44:38 mwn Exp $";
static char tagid[]="$Name:  $";


/* PROTOKOLL DEFINITION **************************************

each send/receive start with 5 bytes (ANZCOMM comm.typ)
followed by 11 bytes which store the length of the following stream

Client send INIT:
dbname \n username \n password \n clienthostname \n flag \n\0
---------------------------------------------------------------
Client receives:
Resultcode \n mp_profil_fields \n\0

---------------------------------------------------------------

Client send QUERY:
controlcode \n Querytype \n TableID \n Query \f\0
---------------------------------------------------------------
Client receives:
Resultcode \n Rows \n Fields \n records \n\0

records are:
field \t field \t field \t\r
field \t field \t field \t\r

if controlcode is 0 it's a query and wait for next
if controlcode is 1 it's the end and exit immediately

querytype is:  1 dynamic query, 2 sql command, 3 dbi infos, 4 www specials
***********************************************************/

/* MARCO POLO API includes */
#include <mpnet.h>
#include <mpwww.h>
#include <mpvarlib.h>
#include <mpvarapi.h>
#include <mpvardbi.h>
#include <mpvarwww.h>
#include <mpsqlsel.h>

#include <psipc.h>

#ifdef ps_unix
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

#define CHK_CONNECT_OK 0
#define CHK_CONNECT_ERROR 1
#define SERVBUFSIZE 1024
#ifdef ps_unix
#define MPNET_LOGFILENAME "/tmp/MPNET.log"
#else
#define MPNET_LOGFILENAME "C:\\TEMP\\MPNET.log"
#endif

/* global variables */
#ifndef ps_linux
#ifndef ps_cygwin
extern char *sys_errlist[];
#endif
#endif
extern STATUS_WERTE	sta;
extern int dialogsprache;
extern int outputsprache;
extern int DebugFlag;
extern char sqlquery[];
extern MEMOBJ sqlmem;
extern MEMOBJ apimem;           /* defined in api functions.sql */
char   argbuffer[2*_RECORDLEN];
unsigned char bm_obj;
FILE *fdlog;
PSmemobj outputmem;
int MPNETstate;

/* end of global decl. */
int main(int, char *[]);

/*--- local functions -------------------------*/
static int MPNETmain(int argc, char *argv[], int fd);
static int Initialization(int argc, char *argv[]);
static void SetLanguage();
static int UtilSetUser(void);
static int ReadLogin(void);
static int WriteLogin(void);

int MPNETdbToAscii(int, char *, int, PSmemobj *);
int MPNETdbiinfoToWWW(int, char *, PSmemobj *);
int MPNETdbToWWW(int, char *, PSmemobj *);
int KAPAVinfo(char *, PSmemobj *);
int TXTinsert(char *);

char *PSIPCservicename = MPNET_SERVICE;
char *PSIPCservicetitle = "travelDB XML Server";
char *PSIPCprot = "tcp";
char *PSIPCservicedeps = "tcpip\0\0";
int (*PSclient)(int, char**, int);

int main(int argc, char *argv[])
{
	int cret = 0;   /* Returncode von IPC process */

	PSSYSsyslog(_PSLOG_OPEN, "travelDB XML", "");
	PSSYSsyslog(_PSLOG_INFO, "travelDB XML", "Started MPNET service");
	PSSYSsyslog(_PSLOG_CLOSE, "travelDB XML", "");

	PSclient = MPNETmain;
	cret = PSIPCserver(argc, argv);
	if (cret != IPCOK)
		{
		(void)printf("\n MPNET exit with error code %d\n", cret);
		exit(1);
		}

	exit(0);
}

static int MPNETmain(int argc, char *argv[], int fd)
{
	extern MP_GLOBALPROFIL globprof;
	extern int ipcfd;
	extern int MPNETstate;
	extern MP_PROFIL prof;
	extern int FatalError;
	extern char messageBuffer[];
	extern int DebugFlag;

	/* MPNET parameters */
	int MPDBcounter;
	int MPresultcode;
	int MPquerytype;
	int MPtableid;
	int MPnextqry = TRUE;
	int MPdbcount;
	char MPquery[_QUERYLEN];

	/* WORKING parameters */
	int cret; /* code return */
	int cdbret; /* code DB return */
	int i;
	char *Pbuf;
	char *retptr;
	char MPmsgheader[10*_RECORDLEN];
	char msgdat[_DATLEN], msgtime[_DATLEN];
	char msgformat[_RECORDLEN];

	/* INIT */
	(void)MPXMLopen();
	ipcfd = fd; /* has to be set from args */
	cret = Initialization(argc, argv);
	if (DebugFlag)
		PSSYSdebug(MPNET_DBGFILE, NULL, "Init done and now waiting for data");


	/* READ setup information and make connect and read profile data */
	// parse login request feedback
	cret = MPXMLread(STARTMEMCHUNK);
	if (cret == MPOK)
		cret = ReadLogin();
	if (cret == MPOK)
		cret = MPXMLreadEnd();

	/* open DB */
	if (DebugFlag)
		PSSYSdebug(MPNET_DBGFILE, NULL, "got XML request read and do login now for user %s on db: %s", globprof.user, globprof.database);
	cdbret = MPAPIdb_connect(globprof.database, globprof.user,
	                       globprof.password);
	if (DebugFlag)
		PSSYSdebug(MPNET_DBGFILE, NULL, "OPEN DB return code %d", cdbret);
	switch (cdbret)
		{
		case -1017:
			MPNETstate = MPNET_DBCERROR;
			PSSYSsyslog(_PSLOG_DEBUG, "travelDB XML",
			   "Logon denied on %s - SQLERR (%d)", globprof.database, cdbret);
			break;
		case 0:
			PSSYSsyslog(_PSLOG_DEBUG, "travelDB XML",
			   "open DB %s with stat %d", globprof.database, cdbret);
			break;
		default:
			MPNETstate = MPNET_DBCERROR;
			PSSYSsyslog(_PSLOG_DEBUG, "travelDB XML",
			   "DB Error on %s - SQLERR (%d)", globprof.database, cdbret);
		}

	/* SEND LOGIN REQUEST FEEDBACK */
	cret = WriteLogin();
	if (MPNETstate == MPNET_DBCERROR)
		{
		if (DebugFlag)
			PSSYSdebug(MPNET_DBGFILE, NULL, "exit now");
		PSSYSsyslog(_PSLOG_CLOSE, "travelDB XML", "");
		exit(0);
		}

/*** MAIN LOOP ***/

	/* READ queryrequests */
	for (i=0; MPnextqry == TRUE; i++)
		{
		/* read query */
		cret = MPXMLread(DEFMEMCHUNK);
		if (cret == MPOK)
			cret = ReadLogin();
		if (cret == MPOK)
			cret = MPXMLreadEnd();

		if (DebugFlag)
			PSSYSdebug(MPNET_DBGFILE, NULL, "got request with code %d", MPresultcode);
		if (MPresultcode == 1)
			{
			MPnextqry = FALSE;
			break;
			}

		if (DebugFlag)
			PSSYSdebug(MPNET_DBGFILE, NULL, "got query %s", MPquery);
		switch (MPquerytype)
			{
			case MPNET_QUERYDYN:
				/* start transaction in read uncomitted mode */
				(void)MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
				cret = MPAPIdb_sqlquery(MPtableid, &sqlmem.buffer, MPquery,
				    &MPDBcounter, &sqlmem.datalen, &sqlmem.alloclen);
				/* end transaction if error then make rollback */
				if (cret != (int)MPOK)
					MPAPIdb_rollbacktrx();
				else
					{
					MPAPIdb_committrx();
					cret = MPNETdbToAscii(MPtableid, sqlmem.buffer,
					       MPDBcounter, &outputmem);
					}
				break;
			case MPNET_QUERYCMD:
				/* start transaction in write mode */
				(void)MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
				MPdbcount = 0;
				cdbret = MPAPIdb_sqlcommand(MPquery, &MPdbcount);
				cret = sprintf(outputmem.buffer, "%d\n%d\n0\n\n", cret, MPdbcount);
				outputmem.datalen = strlen(outputmem.buffer);
				/* end transaction */
				if (cdbret != (int)MPOK)
					MPAPIdb_rollbacktrx();
				else
					MPAPIdb_committrx();
				break;
			case MPNET_DBIINFO:
				/* start transaction in read uncomitted mode */
				(void)MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
				cret = MPNETdbiinfoToWWW(MPtableid, MPquery, &outputmem);
				/* end transaction */
				if (cdbret != (int)MPOK)
					{
					MPAPIdb_rollbacktrx();
					cret = cdbret;
					}
				else
					MPAPIdb_committrx();
				break;
			case MPNET_WWW:
				cret = MPNETdbToWWW(MPtableid, MPquery, &outputmem);
				break;
			}

		/* ERROR HANDLING */
		if (FatalError == (int)TRUE || cret != (int)MPOK)
			{
			if ((cret == (int)MPWARNING) && (FatalError != (int)TRUE))
				{
				/* W A R N I N G  message */
				/* init for warning message */
				MPmsgheader[0] = (char)NULL;
				COMMSTAT = MESSAGEWARNING;
				}
			else
				{
				/* E R R O R  message */
				/* message header */
				UtilMsgGet((int)MPS_ERRORHEADER, MSGTYP_SYSTEM, msgformat);
				MPdate_makecurrent(msgdat, msgtime);
				(void)sprintf(MPmsgheader, msgformat,
				      msgdat, msgtime, globprof.user, globprof.database, rcsid);
				(void)strcat(MPmsgheader, MSGTRENNER);

				/* message footer */
				UtilMsg((int)MPS_SUPPORT, MSGTYP_SYSTEM, NULL);
				COMMSTAT = MESSAGEERROR;
				}
			/* set message for sending to client */
			(void)sprintf(outputmem.buffer, "%d\n1\n1\f%s%s", cret,
			      MPmsgheader, messageBuffer);
			outputmem.datalen = strlen(outputmem.buffer);
			/*!!! comm.datalen = CleanPipeString(comm.buffer); */
			*messageBuffer = (char)NULL;
			}

		/* SEND query results */
		cret = MPXMLendObject();
		cret = MPXMLsend(MPOK, "OK", DEFMEMCHUNK);
		}

	/* close DB and exit */
	cret = MPAPIdb_release();
	if (DebugFlag)
		PSSYSdebug(MPNET_DBGFILE, NULL, "exit now");
	PSSYSsyslog(_PSLOG_CLOSE, "travelDB XML", "");
	(void)MPXMLclose();
	exit(0);
}

/*--------------------------------------------------------------*/
/* Initialization   - give initial value to variables           */
/*                    for each query to the DB                  */
/*--------------------------------------------------------------*/
static int Initialization(int argc, char *argv[])
{
	extern int MPNETstate;

	int INIstatus;

	/*--- SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen = 0;
	/*-- api -----------*/
	apimem.buffer = NULL;
	apimem.alloclen = 0;
	apimem.datalen = 0;

	/* OUTPUT memory allocation and object init */
	outputmem.buffer = NULL;
	outputmem.alloclen = 0;
	outputmem.datalen = 0;
	outputmem.buffer = (char *)MPalloc(outputmem.buffer, &outputmem.alloclen,
	 (long)SERVBUFSIZE, (long)SERVBUFSIZE*5, sizeof(char));

	/* COMM memory allocation and object init */
	COMMSTAT   = NULL;
	COMMTYP    = NULL;
	ACTIONTYP  = NULL;
	MENUNR     = NULL;
	FELDNR     = NULL;
	comm.buffer = NULL;
	comm.datalen = 0;
	comm.alloclen = 0;
	comm.buffer = (char *)MPalloc(comm.buffer, &comm.alloclen,
	 (long)SERVBUFSIZE, (long)SERVBUFSIZE*5, sizeof(char));

	/*--- init language handling ------*/
	sprache         = DEFAULTLANGUAGE;
	aktuellesprache = DEFAULTLANGUAGE;
	FatalError      = (int)FALSE;

	/*--- Init of arguments --------------------*/
	Clientname[0]       = NULL;

	/*--- language for date, time conversions... set by AKTlanguage() -------*/
	*language = (char)NULL;

	/*--- install signal handlers ----*/
	MPinstall_signals(0);

	/*--- setze System/Prozess User ID -----------------*/
	(void)UtilSetUser();

	/* open log files */
	PSSYSsyslog(_PSLOG_OPEN, "travelDB XML", "");
	PSSYSsyslog(_PSLOG_INFO, "travelDB XML", "Started MPNET child");

	return(INIstatus);
} /* Initialization */

/*SF**********************************************************
 * Function:        set user and userid of current job
 * Return:          the real userid
 *************************************************************/
static int UtilSetUser(void)
{
	extern char userid[];   /* wird durch MPdbi_glob.h definiert */

	int cret;
	int user;

	cret = PSSYSgetUser((int *)&user, userid);

	return((int)user);
}

/*SF**********************************************************
 * Function:      Set right language to communicate with DB
 *************************************************************/
static void SetLanguage()
{
	/* set right language */
	if (outputsprache == (int)_UNDEF)
		aktuellesprache = dialogsprache;
	else
		aktuellesprache = outputsprache;
}


/*SF**********************************************************
 * Function:        set user and userid of current job
 * Return:          the real userid
 *************************************************************/
static int ReadLogin(void)
{
	/* global variables */
	extern int DebugFlag;
	extern MP_GLOBALPROFIL globprof;
	extern int FatalError;
	extern xmlDoc *xml_doc;
	int MPNETflag;

	int cret;
	int len;
	char *Pbuf;
	xmlChar tmp[_CHARMAXLEN];

	MPNETflag = MPOK;

	cret = MPXMLgetElement("DBNAME", tmp);
	len = xmlStrlen(tmp);
	if (len > _CHAR200)
		len = _CHAR200;
	(void)strncpy(globprof.database, tmp, len);

	cret = MPXMLgetElement("USER", tmp);
	len = xmlStrlen(tmp);
	if (len > _USERLEN)
		len = _USERLEN;
	(void)strncpy(globprof.user, tmp, len);

	cret = MPXMLgetElement("PWD", tmp);
	len = xmlStrlen(tmp);
	if (len > _PWDLEN)
		len = _PWDLEN;
	(void)strncpy(globprof.password, tmp, len);

	cret = MPXMLgetElement("CLIENTHOSTNAME", tmp);
	len = xmlStrlen(tmp);
	if (len > _CHAR200)
		len = _CHAR200;
	(void)strncpy(globprof.hostname, tmp, len);

	cret = MPXMLgetElement("FLAG", tmp);
	len = xmlStrlen(tmp);
	if (len > _CHAR200)
		len = _CHAR200;
	MPNETflag = atoi(tmp);
	if (MPNETflag != MPOK)
		cret = MPNETflag;

	if (DebugFlag)
		PSSYSdebug(MPNET_DBGFILE, NULL, "got init from %s with status %d", globprof.hostname, cret);

	return(cret);
}


/*SF**********************************************************
 * Function:        set user and userid of current job
 * Return:          the real userid
 *************************************************************/
static int WriteLogin(void)
{
	/* global variables */
	extern int DebugFlag;
	extern int FatalError;
	extern int MPNETstate;
	extern MP_GLOBALPROFIL globprof;
	extern MP_PROFIL prof;

	GLOBDATA globdata;
	int cret;
	int cdbret;
	int len;
	int MPDBcounter;
	char MPquery[_QUERYLEN];
	char *Pbuf;
	char tmpid[_INTLEN*8];

	globdata.bchst[0] = NULL;
	globdata.sprache[0] = NULL;
	globdata.saison[0] = NULL;
	globdata.programm[0] = NULL;

	cret = MPXMLcreate("login", 1);

	if (MPNETstate != MPOK)
		{
		// set XML LOGIN to db open error and send it back
		cret = MPXMLsend(MPERROR, "error with comm", DEFMEMCHUNK);
		}
	else
		{
		/* start transaction in read uncomitted mode */
		cdbret = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
		(void)sprintf(MPquery, _SEL_PROF_USER, globprof.user);
		cdbret = MPAPIdb_sqlquery(_MP_PROFIL, &sqlmem.buffer, MPquery,
			 &MPDBcounter, &sqlmem.datalen, &sqlmem.alloclen);
		MPAPIdb_committrx();
		if (cdbret == 0 && MPDBcounter == 1)
			{
			(void)memcpy((void *)&prof, (void *)sqlmem.buffer, sizeof(prof));
			cret = GLOBinit(&prof, &globdata);

			cret = MPXMLstartObject("PROFIL");
			(void)sprintf(tmpid, "%d", prof.mpid);
			cret = MPXMLaddElementString("UID", tmpid);

			if (globdata.bchst[0] == NULL)
				(void)sprintf(tmpid, "%s", "-");
			else
				(void)strcpy(tmpid, globdata.bchst);
			cret = MPXMLaddElementString("BCHST", tmpid);
			(void)sprintf(tmpid, "%d", prof.bchst);
			cret = MPXMLaddElementString("BCHSTID", tmpid);

			if (globdata.sprache[0] == NULL)
				(void)sprintf(tmpid, "%s", "-");
			else
				(void)strcpy(tmpid, globdata.sprache);
			cret = MPXMLaddElementString("LANG", tmpid);
			(void)sprintf(tmpid, "%d", prof.s_id);
			cret = MPXMLaddElementString("LANGID", tmpid);

			if (globdata.saison[0] == NULL)
				(void)sprintf(tmpid, "%s", "-");
			else
				(void)strcpy(tmpid, globdata.saison);
			cret = MPXMLaddElementString("SAI", tmpid);
			(void)sprintf(tmpid, "%d", prof.sai_id);
			cret = MPXMLaddElementString("SAIID", tmpid);

			if (globdata.programm[0] == NULL)
				(void)sprintf(tmpid, "%s", "-");
			else
				(void)strcpy(tmpid, globdata.programm);
			cret = MPXMLaddElementString("PRG", tmpid);
			(void)sprintf(tmpid, "%d", prof.prg_id);
			cret = MPXMLaddElementString("PRGID", tmpid);
			cret = MPXMLendObject();
			cret = MPXMLsend(MPOK, "OK", DEFMEMCHUNK);
			}
		else
			{
			cret = MPXMLsend(MPERROR, "login / profile not found", DEFMEMCHUNK);
			}
		}

	return(cret);
}
