/*D***********************************************************
 * desc:      mainfunction to include             AKTmain.c
 *
 *            This main() is the 'all data from db' version
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/AKTmain.h,v 1.4 2008-11-02 19:55:33 mwn Exp $
*/


/* Include or define globals */
#include <mpvarlib.h>
#include <mpvarapi.h>
#include <mpvaract.h>

/*--- local functions -------------------------*/
static int UtilSetGlobals(int, char *[]);
#ifndef ps_win
static int UtilSetUserAndPassword(char *);
#endif

int main(int, char *[]);

/*P--- MACROS -------------------------------------------------------------*/
#define EXIT_WITH_ERROR				{status = (int)MPERROR; goto exit;}
#define EXIT_WITH_STATUS(s)		{status = (int)(s); goto exit;}
#define EXIT_COMMIT_WITH_STATUS(s)		{status = (int)(s); \
		(void)MPAPIdb_committrx(); goto exit;}

#define TEST_STATUS(s)				{status = (int)(s);\
		if ( status != (int)MPOK ) {\
		goto exit; }\
		}
#define TEST_STATUS_COMMIT(s)				{status = (int)(s);\
		if ( status != (int)MPOK ) {       \
		(void)MPAPIdb_committrx(); goto exit;} \
		}

#define TEST_STATUS_MSG(s, msg)	{status = (int)(s);\
		if ( status != (int)MPOK ) {\
		AKTmsg( ACT_ERROR, msg, NULL);\
		goto exit; }\
		}
#define TEST_STATUS_MSG_COMMIT(s, msg)	{status = (int)(s);\
		if ( status != (int)MPOK ) {       \
		AKTmsg( ACT_ERROR, msg, NULL);         \
		(void)MPAPIdb_committrx(); goto exit;} \
		}

/*F************************************************************
 * Function:  main
 *            function main necessary for all standalone actions
 *
 * in:
 * out:
 * return:    success code
 **************************************************************/
int main(int argc, char *argv[])
{
	extern MEMOBJ apimem;           /* defined in api functions.sql */
	extern char userid[];
	extern char userpassword[];

	char passwd[RECLAENGE];
	char MailFile[RECLAENGE];
	int (*actionfunc)();
	int status, count;

	/*--- SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen = 0;
	/*-- api -----------*/
	apimem.buffer = NULL;
	apimem.alloclen = 0;
	apimem.datalen = 0;

	/*--- init language handling ------*/
	sprache         = DEFAULTLANGUAGE;
	aktuellesprache = DEFAULTLANGUAGE;
	FatalError      = (int)FALSE;

	/*--- Init of arguments --------------------*/
	dlaid               = (int)_UNDEF;
	arrid               = (int)_UNDEF;
	bchid               = (int)_UNDEF;
	ActionNumber        = (int)_UNDEF;
	dlgid = tdlid       = (int)_UNDEF;
	DebugFlag           = (int)FALSE;
	DBname[0]           = (char)NULL;
	abdate = time_start = (int)_UNDEF;
	time_end            = (int)UNDEF;
	kolid               = (int)_UNDEF;
	guiHostname[0]      = (char)NULL;
	dltid               = (int)_UNDEF;
	debitorflag         = (int)FALSE;
	kunid               = (int)_UNDEF;
	katid               = (int)_UNDEF;
	dialogsprache       = DEFAULTLANGUAGE;
	outputsprache       = (int)UNDEF; /* is tested to check flag presence */
	device_id           = _DEVFILE;
	reinitflag          = (int)FALSE;
	exectyp             = _AKT_MAN;
	dlid                = (int)_UNDEF;
	akttid              = (int)_UNDEF;
	dlnid               = (int)_UNDEF;
	kuntypid            = (int)_UNDEF;
	targetsta           = (int)_UNDEF;
	sourcesta           = (int)_UNDEF;
	specificflag        = (int)_UNDEF;
	LockAction          = (int)FALSE;
	LWlandid            = (int)_UNDEF;
	LWwhrid             = (int)_UNDEF;

	/*--- language for date, time conversions... set by AKTlanguage() -------*/
	*language = (char)NULL;

	/*--- count nb of languages ----------------------*/
	count = AKTlanguageCount();
	if (count == (int)_UNDEF)
	{
		if (DebugFlag)                                /* DEBUG *************/
			(void)fprintf(stderr, "\nError counting the nb of languages \n" );
		exit((int)MPERROR);
	}
	NbSupportedLang = count;

	/*--- install signal handlers ----*/
	MPinstall_signals(0);

	/*--- setze globale Werte aus den Argumenten ------*/
	status = UtilSetGlobals(argc, argv);
	if (status != (int)MPOK)
		exit((int)MPERROR);

/*DEBUG*****************/
	if (DebugFlag)                                     /*DEBUG*****************/
		{
		char argbuffer[2*_RECORDLEN];
		int i;
		argbuffer[0] = (char)NULL;
		for (i=0;i<argc;i++)
			{
			strcat(argbuffer, argv[i]);
			strcat(argbuffer, " ");
			}
		printf("\n\ndebug: %s\n\n", argbuffer);
		}

	/*--- falls Ausfuehrungsart auf NOEXEC, dann nichts tun */
	if (exectyp == _AKT_NOEXEC)
		exit((int)MPOK);

	/*--- check if AKTIONS_TYP is present --------------*/
	if (akttid == (int)_UNDEF)
		if (DebugFlag)                                /* DEBUG *************/
			fprintf(stderr, "\nWARNING: AKTIONS_TYP flag -t is not set\n");

	/*--- Device initialisation ------------------------*/
	status = AKTdeviceInit(device_id, exectyp);
	if (status != (int)MPOK)
		exit((int)MPERROR);
	if (DebugFlag)                                /* DEBUG *************/
		(void)printf("debug: init of action devices done\n");

	/*--- Layout initialisation lines, forms ...--------*/
	AKTlayoutInit();

	/*--- setze System/Prozess User ID and Password -----------------*/
#ifndef ps_win
	(void)UtilSetUserAndPassword(passwd);
	if (DebugFlag)                                /* DEBUG *************/
		(void)printf("debug: init user and passwd strings\n");
#else
	(void)strcpy(passwd, userpassword);
#endif

	/*--- Datenbank opening ----------------------------*/
	status = MPAPIdb_connect(DBname, userid, passwd);
	if (status != (int)MPOK)
		{
		if (DebugFlag)                                /* DEBUG *************/
			(void)fprintf(stderr, "\nError opening the DB %s\n", DBname);
		exit(status);
		}

	/*--- set DB lock for this AKTION ------------------*/
	if (LockAction)
		{
		status = UtilSetAKTlock();
		if (status != (int)MPOK)
			{
			FatalError = (int)TRUE;
			if (DebugFlag)                                /* DEBUG *************/
				(void)fprintf(stderr, "\nError locking the DB for this AKTION\n");
			}
		if (DebugFlag)                                /* DEBUG *************/
			(void)printf("debug: action lock done\n");
		}

	/*--- open mail file in right language ---------------*/
	if (FatalError != (int)TRUE)
		{
		FPmail = MailOpen(MailFile, akttid, dialogsprache);
		if (FPmail == NULL)
			FatalError = (int)TRUE;
		if (DebugFlag)                                /* DEBUG *************/
			(void)printf("debug: mail opened\n");
		}

	/*--- init message ---*/
	if (FatalError != (int)TRUE)
		{
		status = AKTmsginit();
		if (status != (int)MPOK)
			{
/*DEBUG*****************/
			if (DebugFlag)
				(void)fprintf(stderr, "\nError reading messages from DB %s\n", DBname);
			FatalError = (int)TRUE;
			}
		}

	/*------------------------------------------------------------------------*/
	/*     ACTION CORE  Effective Activation                                  */
	/*------------------------------------------------------------------------*/
	if (FatalError != (int)TRUE)
		{
		actionfunc = ACTIONFUNCTION;
		status = actionfunc(argc, argv);
		if (status != (int)MPOK)
			{
/*DEBUG*****************/
			if (DebugFlag)
				(void)fprintf(stderr, "\nError %d in function %s\n", status, argv[0]);
/*DEBUG*****************/
			}
		}


	/*--- free messages -------------------------------*/
	status = AKTmsgfree();
	if (status != (int)MPOK)
		if (DebugFlag)                                /* DEBUG *************/
			(void)fprintf(stderr, "\nError freeing messages from memory\n");

	/*--- versende Mail und loesche temp. Mailfile */
	status = MailSend(userid, FPmail, MailFile);
	(void)MailClose(FPmail, MailFile);
	if (status != (int)MPOK)
		if (DebugFlag)                                /* DEBUG *************/
			(void)fprintf(stderr, "\nError sending mail\n");

	/*--- unset DB lock for this AKTION ----------------*/
	if (LockAction)
		{
		status = UtilUnsetAKTlock();
		if (status != (int)MPOK)
			if (DebugFlag)                                /* DEBUG *************/
				(void)fprintf(stderr, "\nError removing lock for this AKTION\n");
		}

	/*--- free memory buffers --------------------------*/
	MPfree((void *)sqlmem.buffer);
	MPfree((void *)apimem.buffer);

	/*--- close DB */
	status = MPAPIdb_release();
	if (status != (int)MPOK)
		if (DebugFlag)                                /* DEBUG *************/
	 		(void)fprintf(stderr, "\nError closing the DB %s\n", DBname);

	/*--- Beende */
	if (status == MPOK)
		exit(MPOK);
	else
		exit(status);
}



/*F***********************************************************
 * Function:   UtilSetGlobals
 *             set globals with commandline arguments
 *
 * Known arguments:
 *     -A   DIENST_ANGEBOT
 *     -a   ARRANGEMENT
 *     -b   BUCHUNG
 *     -C   Action Number
 *     -c   DLG_PARTS
 *     -D   debug flag
 *     -d   database path/name
 *     -E   start date/time AZEIT
 *     -e   end date/time EZEIT
 *     -f   hardcoded flag (int) action specific (e.g. Bill)
 *     -g   KOLLEKTIV
 *     -H   hostname of gui workstation
 *     -h   DIENST_TRAEGER
 *     -J   create Debitor Journal Record
 *     -k   KUNDEN
 *     -K   KATEGORIE
 *     -L   SPRACHEN (output dialog language)
 *     -l   SPRACHEN (output print language)
 *     -M   maximalanzahl
 *     -m   STATUS_WERTE: output device
 *     -N   HOST_KONT
 *     -n   KONTINGENT
 *     -R   re-init of z_flag of akt_detail
 *     -S   STATUS_WERTE: execution typ
 *     -s   DIENSTLEISTUNG
 *     -t   AKTIONS_TYP
 *     -u   REISENDER / DL-NEHMER
 *     -U   username,password
 *     -X   locking of action
 *     -y   KUNDEN_TYP
 *     -Z   STATUS_WERTE: source reservationstate
 *     -z   STATUS_WERTE: target reservationstate
 *************************************************************/
#define OPTIONEN "A:a:b:C:c:Dd:E:e:f:g:H:h:Jk:K:L:l:M:m:N:n:RS:s:t:u:U:Xy:Z:z:"
static int UtilSetGlobals(int argc, char *argv[])
{
	extern char *optarg;
	extern int opterr;
	extern char userid[];   /* wird durch MPdbi_glob.h definiert */
	extern char userpassword[];

	int c;
	int status = MPOK;
	int device = _DEVFILE;
	struct tm DateTime;
	char time_string[_RECORDLEN];

	/* getopt(3) selbst soll keine Fehlermeldung auf den  */
	/* Bildschirm ausgeben, wenn ungueltige Option */
	opterr = 0;

	while ( ( c = getopt( argc, argv, OPTIONEN ) ) != EOF )
		{
		switch ( c )
			{
			/* Dienstleistungsangebot */
			case 'A':
				dlaid = atoi(optarg);
				break;

			case 'a':
				arrid = atoi(optarg);
				break;

			case 'b':
				bchid = atoi(optarg);
				break;

			case 'C':
				ActionNumber = atoi(optarg);
				break;

			case 'c':
				tdlid = atoi(optarg);
				dlgid = tdlid;                       /* ????? will be obsolete */
				break;

			case 'D':
				DebugFlag = (int)TRUE;
				break;

			case 'd':
				strcpy(DBname, optarg);
				break;

			/* Anfangsdatum */
			case 'E':
				strcpy( time_string, optarg );
				abdate = atoi(optarg);
				(void)memset((void *)&DateTime, (int)NULL, sizeof(DateTime));
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				(void)ReadDate(&DateTime, (time_t *)&time_start, time_string);
				break;

			/* Enddatum */
			case 'e':
				strcpy( time_string, optarg );
				(void)memset((void *)&DateTime, (int)NULL, sizeof(DateTime));
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				(void)ReadDate(&DateTime, (time_t *)&time_end, time_string);
				break;

			/* Hardcoded Flag which is specific to each action */
			case 'f':
				specificflag = atoi(optarg);
				break;

			/* Grupp/Kollektiv KOL */
			case 'g':
				kolid = atoi(optarg);
				break;

			/* Host workstation */
			case 'H':
				strcpy(guiHostname, optarg);
				break;

			/* Dienstleistungstr�ger DLT */
			case 'h':
				dltid = atoi(optarg);
				break;

			/* Debitor Journal Entry */
			case 'J':
				debitorflag = (int)TRUE;
				break;

			case 'k':
				kunid = atoi(optarg);
				break;

			/* KATEGORIE */
			case 'K':
				katid = atoi(optarg);
				break;

			case 'L':
				dialogsprache = atoi(optarg);
				break;

			case 'l':
				outputsprache = atoi(optarg);
				break;

			case 'M':
				break;

			case 'm':
				/* setze Filepointer and device index  */
				device = atoi(optarg);
				break;

			/* HOST_KONT */
			case 'N':
				hostkontid = atoi(optarg);
				break;

			/* KONTINGENT */
			case 'n':
				kontid = atoi(optarg);
				break;

			case 'R':
				reinitflag = (int)TRUE;
				break;

			case 'S':
				/* execution typ - spooled/direct */
				exectyp = atoi(optarg);
				break;

			case 's':
				dlid = atoi(optarg);
				break;

			case 't':
				akttid = atoi(optarg);
				break;

			/* DL-Nehmer DLN */
			case 'u':
				dlnid = atoi(optarg);
				break;

			/* Username,Password temporarily in the string userid */
			case 'U':
				strcpy(userid, optarg);
				break;

			/* locking of action */
			case 'X':
				LockAction = (int)TRUE;
				break;

			/* Kundentyp KUNT */
			case 'y':
				kuntypid = atoi(optarg);
				break;

			case 'Z':
				/* source reservation state */
				sourcesta = atoi(optarg);
				break;

			case 'z':
				/* target reservation state */
				targetsta = atoi(optarg);
				break;

			default:
				break;
			}
		}
	device_id = device;

	return(status);
}


#ifndef ps_win
/*SF**********************************************************
 * Function:        set user and userid of current job
 * Return:          the real userid
 *************************************************************/
static int UtilSetUserAndPassword(char *passwd)
{
	extern char userid[];
	extern char userpassword[];

	int cret;
	uid_t user;
	char sysuserid[_RECORDLEN];
	char *passwordptr;

#define MP_DELIMITER	','
	int del = (int)MP_DELIMITER;
#undef MP_DELIMITER

	/* Find first occurence of delimiter character    */
	/* Delimiter character cannot be part of username */
	passwordptr = strchr(userid, del);
	if (passwordptr)
		{
		*passwordptr = (char)NULL;
		passwordptr++;
		strcpy(passwd, passwordptr);
#ifdef ps_winplain
		cret = PSSYSgetUser(&user, sysuserid);
#endif
		}
	else
		*passwd = (char)NULL;

	return((int)user);
}
#endif