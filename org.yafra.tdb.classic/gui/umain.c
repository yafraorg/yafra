/**************************************************************
 * Modul:	GUI - dialog			umain.c 
 *
 *				Main procedure
 *				Public declaration, Basic checks
 *				-
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/umain.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";

#define XUIMAIN

#ifdef ps_unix
#include <sys/utsname.h> /* include for system call uname  */
#include <pwd.h>
#endif

#include <locale.h>
#include <uinclude.h>    /* GUI global include             */
#include <umenu.h>       /* menu definitions               */
#include <mpvarlib.h>    /* variables for memory alloc     */
#include <ginclude.h>    /* Graphic global include         */
#include <mpmenlev.h>    /* menu new level definitions     */
#include <mplizenz.h>    /* licence infos                  */
#include <psmodul.h>     /* security infos                 */
#include <psmume.h>      /* Pixelimage library             */
#include "version.h"

#undef XUIMAIN

#ifdef ps_win
#include <stdlib.h>

#ifdef ps_humm
#include <X11/XlibXtra.h>
int errno;
double _HUGE;
unsigned short *_pctype;
int __mb_cur_max;
#endif

#endif

#ifdef ps_hpux
#define XmSTRING_DEFAULT_CHARSET XmSTRING_ISO8859_1
char Error[128];
#endif

char *PSIPCservicename = "mpgui dummy";
char *PSIPCprot = "tcp";
int (*PSclient)(int, char**, int);
#ifdef ps_win
char *PSIPCservicetitle = "mpgui dummy";
char *PSIPCservicedeps = "tcpip\0\0";
#endif

/* local PROTOTYPES */
static int  xUIcheckArguments(Cardinal argc, char** argv);
static void xUIinitMenuMembers();

/*P--------------------- PUBLIC VARIABLES -------------------------------*/
ApplicationData   app_data;						/* xUIappdefaults.h */
DatabaseData      db_data;

/* MARCO POLO global profile data */
GLOBDATA				globdata;
MP_GLOBALPROFIL	globprof; /* the main profile */
Boolean				setupcleanflag = False;
char					setupfile[_CHAR200+1];

/* communication flags */
char databasenotok = XUIDBOK;
int  ipcfd;
int  winsockflag;

/* options flags */
int  ipcargument;             /* which argument no is the -s */
int  ipcflag = 0;             /* set to SOCKETS if -s is used */
char dbhostname[_CHAR30];     /* -s option */
char displayfile[_CHAR30];    /* -d option */
Boolean audioflag = False;    /* -A flag */
Boolean graphikflag = False;  /* -G flag */

/* license check flags */
char	graphikallowed;   /* PS modul + graphic allowed  */
char	allowed;				/* PS modul has allowed        */

/*--- General data --------*/
Boolean		allmenuflag;				/* true generates all menu stuff at init phase*/
Boolean		undraw;
long			maxtablist = 0;            /* aktuelle Anzahl Zeilen (LISTWIDGET) */
unsigned char actiontoggle = INSERT; /* Defaulteinstellung f�r toggles     */
char           rec[RECLAENGE];
long    maxentries = 0;   /* aktuelle Anzahl Characters  (INPUT)    */
char    *entries;         /* INPUT Eintrag                          */
long    maxoutcomm = 0;   /* aktuelle anzahl Characters (OUTPUT)    */
char    *outcomm;         /* OUTPUT                                 */
long    maxtempo = 0;     /* aktuelle Anzahl Characters temp buffer */
char    *tempo;           /* temp texts                             */
char mp_version[200];     /* version string */
char mp_verinfo[200];     /* version string */
char mp_guivers[200];     /* version string */


/*--- Menu data -----------*/
MENULIST  pulldownlist[ANZGROUPS+2];
MENULIST  grouplist[ANZGROUPS+1][ANZ_MENU];
MENU     *suchzuo;					   /* MENU zur SUCHMASKE */
int		aktmenuz = -1;             /* Anzahl des aktuell aktiven Menus    */
int		aktmenu[ANZ_MENU];         /* aktuell aktive Menus                */
int		aktmenuobj[ANZ_MENU];      /* aktuelles MENU Objekt f�r COMM      */
int		menutypzuo[ANZ_MENU];		/* Zuordnung Typ zu MENU               */
/* MENUDIM	menudim[ANZ_MENU];			menu dimensions used for scrollwin  */

int		aktfield[ANZ_MENU];        /* aktuell aktive Felder der Menus     */
int		zufield[ANZ_MENU];         /* zuzuordnende Felder beim Popdown    */
int		globfield = -1;            /* aktuell aktives globales Feld       */
int		suchfield = -1;            /* aktuell aktives Suchfeld            */
int		holdfield;                 /* aktuell aktives internes Feld       */
int		feldnr;                    /* aktuelles Feld                      */

/*--- Selection -----------*/
Widget		selectpopup ;
XmString		*tab;							/* table of strings in scrolled list   */
char			selectRec[RECLAENGE];	/* selected text                       */
Boolean		chosenflag;					/* true means user has selected        */

/*--- Question  -----------*/
Widget		questionshell, questionbox;
XtCallbackProc (*funcquestion)();		/* execute in xUIquestion callback  */
XtPointer	adrptr;							/* closure                          */

/*--- Help ----------------*/
Widget  helpshell, helpwidget;
Boolean helpPresent = False;

/* option menu Widgets */
int			optionNr; 
int			optionSelect[_MAXBUTTONS_]; 		/* option toggle selections      */
Widget		Woption = 0;							/* main option widget            */ 
Boolean		openedoption = False;				/* true when mapped              */
Widget		WoptionButtonQuit = 0;				/* button Quit, used in softkey  */ 
Widget		WoptionButtonHelp = 0;				/* button Help, used in softkey  */ 
 
/*--- Global widgets ------*/
Widget  globalboard, bannerboard, bannertext, globalmenu;
Widget  messageshell, messagewidget;
Widget  text;
Widget  infoshell, infotext;
Widget  faultshell, faulttext;
Widget  masshell, rcfield, rcbutton;
Widget  toplevel, mainwindow;
Widget  licence;                              /* licence dialog             */
Widget  bookingMask;                          /* globale Buchungsmakenshell */
XtAppContext mpx_appcontext;

XtPointer      para;								    /* ??? purpose?  */
Atom           wm_delete_window;
Cursor         cursorwait;
Display       *display;


/*--- color daten f�r INSERT/UPDATE+DELETE switch */
unsigned char	getcolor;			/* TRUE: hole def. Farb;  FALSE: nop */
OBJCOLORS		orgcol;				/* Original Colorset */
OBJCOLORS		keycol;				/* Key Colorset */
OBJCOLORS		nextmenucol;		/* NextMenu Colorset */
OBJCOLORS		gracol;				/* Graphic Colorset */
OBJCOLORS		boardcol;			/* Matrix board Colorset */

/*----- globale Graphikdaten -----------*/
long			grajobflag = 0;       /* Graphic mode                             */
GRAGLOB		graglob;              /* Graphic parameters                       */
GRACAT		gracat;               /* graphic parameters for categories colors */
GRAWIDGETS	grawidgets;
GRAWINDOWS	grawindows;
GRAFOBJ		*grafObj;
long			anzgrafObj;
REGOBJ		*regObj;
long			anzregObj;
REGIONPOINT		*regionPoints;
unsigned long	anzregionPoints;
XPoint			punkt[10];         /* working points ??? was POINT      */
int			anzZoom;              /* number of zoom steps              */
ZOOM			zoom[MAXZOOM];        /* zoom steps list                   */
ZOOM			*aktzoom;             /* ptr to active zoom step           */ 
Boolean		zoomingflag;          /* inhibition of booking during zoom */
char			*aktgraphikfile;


/*A----------- Our Actions look-up table used later in Translations -----*/
XtTranslations    transedit, transnoedit, edit, fielddelete, softkeytrans;
static XtActionsRec newactions[] = {    
	{"editstart",(XtActionProc)xUIreadwrite    },
	{"editquit", (XtActionProc)xUIwritetoread  },
	{"selquit",  (XtActionProc)xUIselectpopdown},
	{"selnew",   (XtActionProc)xUIselnewmenu   },
	{"beep",     (XtActionProc)xUIbeep         },
	{"delfield", (XtActionProc)xUIfielddel     },
	{"softkey",  (XtActionProc)xUIsoftkey      }   };
static String edittrans   = "<Btn3Up>: editquit()";
static String noedittrans = "<Btn3Up>: beep()";
static String deletefield = "<Btn3Up>: delfield()";

static String fieldtrans  = "<Btn1Up>: editstart()\n<LeaveWindow>: editquit()";
/* static String fieldtrans  = "<Btn1Up>: editstart()"; */

/*---- Object: Label tables -------------------------*/
char	*xgrLabelTable [XGRLABMAXTYPES] [XGRLABMAXTEXTS];  
char	*xuiLabelTable [XUILABMAXTYPES] [XUILABMAXTEXTS];  
char	*xbmLabelTable [XBMLABMAXTYPES] [XBMLABMAXTEXTS];  
int	objType;							/* cross reference DBobject-UIwindow */								     

/*---- Object: pixel images -------------------------*/
int		ImageCnt = -1;           /* Bildz�hler / -pointer */
int		ImageCurr = -1;          /* Aktuelles Bild */
RASTERIMAGE *RI[MAXIMAGES];
GC			WImgGC;
Colormap	localCmap = 0; 

/*P--------------------BM - PUBLIC VARIABLES -----------------------------*/
XtTranslations		BMtransedit, BMtransnoedit, BMedit, BMfielddelete ;




/*FN---------------------------------------------------------------------
 *	Function:	main()
 *					-determines nb of labels and allocate memory 
 *					-check licence and graphic 
 *					-init X stuff
 *					-get standard resources, or defaults if problem
 *						defaults  reside in xUIappdefaults.h
 *					-init labels and menus 
 *					-end with mainloop
 *-----------------------------------------------------------------------
 */
void main(int argc, char** argv)
{
	extern int (*MPfunction_exit)();
	extern int	DebugFlag;
	extern MP_GLOBALPROFIL globprof;
	extern char setupfile[];
	extern char mp_version[];
	extern char mp_verinfo[];
	extern char mp_guivers[];

	MENU			*a;
	MENULIST		*pML; 		/*used in fast access operations */
	Widget		menubar;
	char			*fehler, *ptr;
	int			g, i, j, k, z ;
	int			anzlabels, aktlabel;
	Arg			wargs[5];
	int			ac;
	long			len;
	int         cret;
	char			labelprg[6];
	XtAppContext	 app_con; 
	char *makecore = NULL;

	/* UNIX user/passwd fields */
#ifdef ps_winplain
	typedef int uid_t;
#endif
	uid_t				userid;
	struct passwd *userpasswd;

	/*-------------------- DEFAULT INITS -------------------------------*/
	anzregObj = 0;
	anzregionPoints = 0;
	anzgrafObj = 0;
	graphikflag = False;					/* set by cmdline or option */
	grawidgets.shell = 0;
	getcolor = (unsigned char)TRUE;
	allmenuflag = False;
	glob.openedmenu = False;         /* no widget present */
	DebugFlag = (int)FALSE;          /* no debugging      */
	setupfile[0] = NULL;             /* init setupfile string to NULL */

	(void)memset((void *)&globdata, NULL, sizeof(GLOBDATA));
	(void)memset((void *)&globprof, NULL, sizeof(MP_GLOBALPROFIL));

#ifdef ps_win

#ifdef ps_humm
	HCLXmInit();
#endif

	(void)setlocale(LC_ALL, "swiss");
#endif

#ifdef ps_hpux
	(void)setlocale(LC_ALL, "de_DE.iso88591");
#endif

	/* init PSIPC functions */
	cret = PSIPCsocketinit();

	/* init global version string */
	(void)sprintf(mp_version, "%s %s ", PSVERSION, LIZSHELL);
	(void)sprintf(mp_verinfo, "%s", PSVERINFO);
	(void)sprintf(mp_guivers, "%s", PSVERSION);

	/* Pulldown list is defaultly disabled, but not HELP */
	for (i=0; i<ANZGROUPS+1; i++)
		pulldownlist[i].status = False;
	pulldownlist[ANZGROUPS+1].status = True;   /*help*/

	/*--- Set default options -------------------*/
	xUIoptionSetDefaults();

	/* Check Licence for GUI and Graphics */
#ifdef PSLICENSE
	allowed = PSmodul(MARCOPOLO);
	if (!allowed)
		{
		databasenotok = XUIDBLIZENZ;
		perror( GUI_ERROR_LICENSE ); 
		exit(1);                         /* >>>>>>>>>> exit here >>>>>>*/
		}
	graphikallowed = PSmodul(MARCOPOLOGRAPHIK);
#else
	/*!!!--- skip the test temporary for dos port ---*/
	allowed = (char)1;
	graphikallowed = (char)1;
#endif

	/*--- Check Cmd-line arguments --------------*/
	cret = xUIcheckArguments(argc, argv);
	if (cret != _OK)
		{
		perror( GUI_ERROR_ARGUMENTS); 
		exit(1);	                       /* >>>>>>>>>> exit here >>>>>>*/
		}
	if (DebugFlag)
		{
		PSSYSdebug(NULL, NULL, "MARCO POLO GUI debugmode enabled");
		PSSYSdebug(NULL, NULL, "UI allowed %d, GRA allowed %d",
		        allowed, graphikallowed);
		}

	/* init profile */
	cret = MPUIprofile_init(setupfile, &globprof);
	if (cret != MPOK)
		{
		perror( GUI_ERROR_SETUP ); 
		exit(1);                         /* >>>>>>>>>> exit here >>>>>>*/
		}

	/* set signal handling */
	MPfunction_exit = xUImainStop;   /* set exit function for signalhandling */
	MPinstall_signals(0);

	/*-------------------- X-WINDOW INIT ---------------------------------*/

	/* initialize X11 system */
	/* argv[0] = mp_version; */
	toplevel = XtAppInitialize(&mpx_appcontext, MAINCLASS, NULL, 0,
	   (int *)&argc, argv, NULL, NULL, 0);
	display = XtDisplay(toplevel);

	/*--- Resouces -------------------------------*/
	XtGetApplicationResources(toplevel, &app_data, resources,
			XtNumber(resources), 0, 0);

#ifdef ps_unix
	/*--- Iconpixmap for Toplevelshell -----------*/
	xUIiconpixmap(toplevel, app_data.iconbitmapmain);
#endif

	/*----- set OSF/Motif standard close ---------*/
	wm_delete_window = XmInternAtom(display, "WM_DELETE_WINDOW", False);
	XmAddWMProtocolCallback(toplevel, wm_delete_window,
			(XtCallbackProc)xUImainClose, (XtPointer)True);

	/*----- Actions Translations -----------------*/
	XtAppAddActions(mpx_appcontext, newactions, XtNumber( newactions));
	transedit		= XtParseTranslationTable( edittrans);
	transnoedit		= XtParseTranslationTable( noedittrans);
	fielddelete		= XtParseTranslationTable( deletefield);
	edit				= XtParseTranslationTable( fieldtrans);
	softkeytrans	= XtParseTranslationTable( app_data.softkeytranslations);
	/*--- init BM Translations ----*/
	xBMinitTranslations();

	/*-------------------- COMMUNICATION WITH DB -----------------------*/
	if (!databasenotok)
		{
		char *default_host;
		size_t array_size;

		switch (ipcflag)
			{
			case XUISOCKET:
				if (DebugFlag)
					PSSYSdebug(NULL, NULL, "socket server host is %s", dbhostname);
				ipcfd = (int)PSIPCclient(dbhostname, SERVICE, PROT);
				break;
			default:
				perror(GUI_ERROR_IPC);
				databasenotok = XUIIPCNOHOST;
				break;
			}
		/* check status from ipc_client call */
		if (ipcflag == XUISOCKET)
			switch (ipcfd)
				{
				case IPCNOSERVICE:
					databasenotok = XUIIPCNOSERVICE;
					break;
				case IPCNOHOST:
					databasenotok = XUIIPCNOHOST;
					break;
				case IPCNOSOCKET:
					databasenotok = XUIIPCNOSOCKET;
					break;
				case IPCNOCONNECT:
					databasenotok = XUIIPCNOCONNECT;
					break;
				}
		}
	if (DebugFlag && databasenotok)
		PSSYSdebug(NULL, NULL, "communication with daemon NOT OK (code %d)!",
		        databasenotok);

#ifdef ps_unix
	/*------ Get the user id of this process */
	userid = getuid();
	userpasswd = (struct passwd *)getpwuid(userid);
	(void)strcpy((char *)globprof.user, (char *)userpasswd->pw_name);   
#endif
	if (DebugFlag)
		PSSYSdebug(NULL, NULL, "user from passwd is now %s", globprof.user);

	/*------ Global init between the two processes + color liste ----------*/
	comm.buffer = NULL;		/*----- init comm structur */
	comm.alloclen = 0;
	comm.datalen = 0;
	if (!databasenotok)
		{
		COMMSTAT  = MESSAGEOK;
		COMMTYP   = GLOBAL;
		ACTIONTYP = NULL;
		MENUNR    = NULL;
		FELDNR    = NULL;
		len = xUItalkto(SEND, (char *)&globprof, sizeof(MP_GLOBALPROFIL));

		/* receive GLOBDATA struct from DBI */
		len = xUItalkto(RECV, 0, 0);
		if (COMMSTAT == MESSAGEERROR)
			{
			if (DebugFlag)
				PSSYSdebug(NULL, NULL, "init error of DBI (perhaps user profile not correct, see DBI log files)");
			databasenotok = XUIDBCONNECT;
			xUImainStop(MPERROR);
			}

		if ((len - sizeof(globdata) > 0) && (!databasenotok)) 
			{
			memcpy((void *)&globdata, (void *)comm.buffer, sizeof(globdata));
			db_data.colorListe = (char *)XtMalloc(len-sizeof(globdata));
			strcpy((void *)db_data.colorListe, (void *)(entries+sizeof(globdata)));
			}
		else
			db_data.colorListe = NULL;
		}
	else
		db_data.colorListe = NULL;

	/*--- Replace app_data colors with DB's colors ---*/
	if (db_data.colorListe)
		app_data.colorListe = db_data.colorListe;   

	/*---------------------- LABELS ------------------------------------- */
	cret = xUIlabelsPointerInit();			/* allocate mem */
	if (cret != _OK)
		{
		if (DebugFlag)
			PSSYSdebug(NULL, NULL, "problems with label init - exit");
		perror( GUI_ERROR_LABELS ); 
		xUImainStop(MPERROR);
		}

	/*---- get labels ----------------------*/
	if (!databasenotok)
		{
		(void)sprintf(labelprg, "%d", _XUI);
		COMMSTAT  = MESSAGEOK;
		COMMTYP   = GLOBAL;
		ACTIONTYP = LABELINIT;
		MENUNR    = NULL;
		FELDNR    = NULL;
		len = xUItalkto(SEND, labelprg, strlen(labelprg));
		len = xUItalkto(RECV, 0, 0);
		if (!databasenotok && COMMSTAT == MESSAGEOK)
			xUIlabelsFromBank( comm.buffer, _XUI);       /* load from DB buffer */ 
		else
			xUIlabelsDefault( app_data.labelfile);       /* load from file      */ 
		}
	else
		{
		/*--- load labels from file -----*/
		xUIlabelsDefault (app_data.labelfile); 
		}

	/*--- Label Application and Icon  -------*/
	ac=0;
	XtSetArg(wargs[0], XmNtitle,             mp_version);              ac++;
	XtSetArg(wargs[1], XmNiconName,          LABEL_ICONAPPLICATION );  ac++;
	XtSetArg(wargs[2], XmNmwmFunctions, MWM_FUNC_MOVE|MWM_FUNC_MINIMIZE|MWM_FUNC_CLOSE); ac++;
	XtSetValues(toplevel, wargs, ac);

	/*--- init pulldown, global and normal menus labels ------*/
	xUIlabelsMenuInit ();


	/*---------------------- MAIN WINDOW --------------------------------- */
	if (DebugFlag)
		PSSYSdebug(NULL, NULL, "labels done - creating main window");
	/*--- Cursor pixmap ------------------*/
	cursorwait = xUIcursor( display, app_data.bitmapcommitforeground,
		app_data.bitmapcommitbackground, app_data.bitmapcommitforegroundcolor,
		app_data.bitmapcommitbackgroundcolor);

	/*--- Main window creation -----------*/
	mainwindow = XmCreateMainWindow(toplevel, MAINWINDOW, 0, 0);
	XtManageChild(mainwindow);  
	menubar = XmCreateMenuBar(mainwindow, MAINBAR, 0, 0);
	XtManageChild(menubar);
	globalboard  = xUIglobBoardCreate( mainwindow);
	XmMainWindowSetAreas( mainwindow, menubar, 0, 0, 0, globalboard);
 
	/*--- Select list shell --------------*/
	if (DebugFlag)
		PSSYSdebug(NULL, NULL, "creating global select list");
	selectRec[0]= '\0';
	xUIlistshell( LISTSHELL, toplevel, LABEL_SELECTLISTWINDOW,
						SELECTSHELL, SELECTTEXT, &selectpopup, &text);
	XtAddCallback(text, XmNsingleSelectionCallback, (XtCallbackProc)xUIchooseitem,
																	(XtPointer)0);
	XtAddCallback(text, XmNdefaultActionCallback, (XtCallbackProc)xUIchoosedown,
	          													(XtPointer)0);


	/*----------------------PULLDOWN & MENUS ------------------------------- */
	if (DebugFlag)
		PSSYSdebug(NULL, NULL, "creating pulldowns and menus");
	(void)xUIinitMenuMembers();
	(void)xUIpulldown(0, menubar, pulldownlist, ANZGROUPS+1);
	(void)xUIoptionCreatePopup(); 


	/*---------------------- OPTIONS and GLOBAL MENU -----------------------*/
	if (!databasenotok)
		{
		if (DebugFlag)
			PSSYSdebug(NULL, NULL, "init of toggle options and globmem");

		/*-- Initialize options (TOGDBLOG, ...) ---*/
		xUIoptionSendAll();
		}

	/*---------------------- GRAPHIC shell ---------------------------------*/
	if (graphikallowed)
		{
		xGRinit_graphic();
		if (DebugFlag)
			PSSYSdebug(NULL, NULL, "GUI graphic init done");
		}

	/*-- Set Eventhandler for Input over Pipe or Socket --------*/
	if (!databasenotok)
		if (ipcfd >= 0)
			{
#			ifdef ps_humm
			winsockflag = 9;
			XtAppAddInput(mpx_appcontext, ipcfd, (XtPointer)XtInputReadWinsock,
			           (XtInputCallbackProc)xUIinput, (XtPointer)0);
#			else
			winsockflag = 0;
			XtAppAddInput(mpx_appcontext, ipcfd, (XtPointer)XtInputReadMask,
			           (XtInputCallbackProc)xUIinput, (XtPointer)0);
#			endif
			}
		else
			XtAppAddInput(mpx_appcontext, 0, (XtPointer)XtInputReadMask,
			           (XtInputCallbackProc)xUIinput, (XtPointer)0);

	/*-- Information and Licence Widget -------------------------*/
	xUIlicenceCreatePopup(toplevel);
	XmAddWMProtocolCallback(XtParent(licence), wm_delete_window,
			(XtCallbackProc)xUImainClose, (XtPointer)True);

	if (DebugFlag)
		PSSYSdebug(NULL, NULL, "main init done - going to XtMainLoop");

	XtAppMainLoop(mpx_appcontext);
}



/*SF--------------------------------------------------------------------
 *	Function:	xUIcheckArguments 
 *					check the arguments entered by user 
 *					Enable pulldown and menu sensitivity
 *	In:			-arguments
 *					-
 *-----------------------------------------------------------------------
 */
static int xUIcheckArguments(Cardinal argc, char** argv)
{
	extern int	DebugFlag;
	extern char setupfile[];

	int     g, i, j, k, z, typ;

	/*-----  Command-line arguments check --------   */
	for (i=1;  i<argc;  i++)
		{
		if ((strcmp(argv[i], "-v") == 0) || (strcmp(argv[i], "-h") == 0))
			{
			(void)printf( "\n%s\n",  PSIDENT);
			(void)printf( "\n%s", " -A           : enable audio play            " );
			(void)printf( "\n%s", " -G           : enable graphic               " );
			(void)printf( "\n%s", " -a           : prepare popup at init phase  " );
			(void)printf( "\n%s", " -d display   : display device (X Terminal)  " );
			(void)printf( "\n%s", " -D           : debugging mode (all with *)  " );
			(void)printf( "\n%s", " -f filename  : file for global setup        " );
			(void)printf( "\n%s", " +g menugroup : enable a menu group          " );
			(void)printf( "\n%s", " -m menunr    : disable a single menu        " );
			(void)printf( "\n%s", " +m menunr    : enable  a single menu        " );
			(void)printf( "\n%s", " -o option    : set this option              " );
			(void)printf( "\n%s", "       0  DB log                            *" );
			(void)printf( "\n%s", "       1  User log                          *" );
			(void)printf( "\n%s", "       2  Automatic info                     " );
			(void)printf( "\n%s", "       3  Graphic enabled (same like -G)     " );
			(void)printf( "\n%s", "       4  Reisenden then Reservat.          *" );
			(void)printf( "\n%s", "       5  Global menu show                  *" );
			(void)printf( "\n%s", "       6  Data ordering 1=Date 0=Alpha      *" );
			(void)printf( "\n%s", "       7  Audio enable (same like -A)        " );
			(void)printf( "\n%s", "       8  Debug enable (same like -D)       *" );
			(void)printf( "\n%s", "       9  Read from temp table or DB        *" );
			(void)printf( "\n%s", " -p           : enable all pulldown menus   *" );
			(void)printf( "\n%s", " -s hostname  : communication over IPC      *" );
			(void)printf( "\n%s", " -v  or  -h   : print this text you read     " );
			(void)printf( "\n\n" );
			exit(0);                         /* >>>>>>>>>> exit here >>>>>>*/
			}

		optionSelect[_TOGGLOBAL]   = 1 ;
		if (strcmp(argv[i], "-D") == 0)		/* enable debugging mode  */
			{
			/*-- set main debugging flag -----*/
			DebugFlag  = (int)TRUE;
			/*-- parameter "-s localhost" ----*/
			ipcflag = XUISOCKET;
			(void)sprintf(dbhostname, "%s", "localhost" );
			/*-- parameters "-o ?" -----------*/
			optionSelect[_TOGDBLOG]    = 1 ;
			optionSelect[_TOGUSERLOG]  = 1 ;
			optionSelect[_TOGDLN]      = 1 ;
			optionSelect[_TOGGLOBAL]   = 1 ;
			optionSelect[_TOGDATORDER]	= 1 ;   /* Select Order Date=1/Alpha=0 */
			optionSelect[_TOGDEBUG]    = 1 ;
			optionSelect[_TOGSELFROMTMP] = 1 ;
			/*-- parameter "-p "--------------*/
			for (k=0;  k<ANZGROUPS+1;  k++)
				pulldownlist[k].status = True ;
			for (k=0;  k<ANZ_MENU;  k++)
				menu[k].flags = True;
			continue;
			}

		if (strcmp(argv[i], "-s") == 0)     /* enable communication over IPC */
			{
			ipcflag = XUISOCKET;
			i++;
			ipcargument = i;
			(void)sprintf(dbhostname, "%s", argv[i]);
			continue;
			}

		if (strcmp(argv[i], "-f") == 0)		/* file for glob setup */
			{
			i++;
			if (i == argc)
				return(_NOTOK);                              /*>>>>> return >>> */
			(void)sprintf(setupfile, "%s", argv[i]);
			continue;
			}

		if (strcmp(argv[i], "-o") == 0)		/* Options can only be set */
			{
			i++;
			if (i == argc)
				return(_NOTOK);                              /*>>>>> return >>> */
			j = sscanf(argv[i], "%d", &optionNr);
			optionSelect[optionNr] = 1;
			continue;
			}

		if (strcmp(argv[i], "-d") == 0)		/* file for display */
			{
			i++;
			if (i == argc)
				return(_NOTOK);                              /*>>>>> return >>> */
			(void)sprintf(displayfile, "%s", argv[i]);
			continue;
			}

		if (strcmp(argv[i], "-a") == 0)		/* xUIpopup at init phase */
			{
			allmenuflag = True;
			continue;
			}

		if (strcmp(argv[i], "-G") == 0)		/* enable graphic module  */
			{
			if (graphikallowed)
				{
				graphikflag = True;
				optionSelect[_TOGGRAPHIC] = 1 ;
				}
			continue;
			}

		if (strcmp(argv[i], "-p") == 0)		/* all menu groups enable   */
			{
			for (k=0;  k<ANZGROUPS+1;  k++)
				pulldownlist[k].status = True ;
			for (k=0;  k<ANZ_MENU;  k++)
				menu[k].flags = True;
			continue;
			}

		if (strcmp(argv[i], "-A") == 0)		/* audio enabled */
			{
			audioflag = True;
			optionSelect[_TOGAUDIO] = 1 ;
			continue;
			}

		typ = 0;
		if (strcmp(argv[i], "+g") == 0)		/* one menu group enable    */
			typ = 1;
		if (strcmp(argv[i], "-m") == 0)		/* single menu disable      */
			typ = 2;
		if (strcmp(argv[i], "+m") == 0)		/* single menu enable       */
			typ = 3;
		if (typ > 0 && typ <= 3)            /* menu validations       */
			{
			i++;
			if (i == argc)
				return(_NOTOK);                              /*>>>>> return >>> */
			j = sscanf(argv[i], "%d", &z);
			if (j==1)  switch(typ)
				{
				case 1:           /* enable group 'z' */
					pulldownlist[z].status = True ;
					for (k=0; k<ANZ_MENU; k++)
						{
						if (menu[k].zuogruppe == z)
							menu[k].flags = True;
						}
					break;
				case 2:          /* disable menu 'z' */
					if (z>=0 && z<ANZ_MENU) 
						menu[z].flags = False;
					break;
				case 3:          /* enable menu 'z' */
					if (z>=0 && z<ANZ_MENU) 
						menu[z].flags = True;
					break;
				}
			}
		}

	return(MPOK);
}



/*F---------------------------------------------------------------------
 *	Function:	xUIinitMenuMembers 
 *					-initialize  pulldown and grouplist menus  
 *-----------------------------------------------------------------------
 */
static void xUIinitMenuMembers()
{
	extern int	DebugFlag;

	int			g, i, j, k ;
	MENU			*a;
	MENULIST		*pML; 		/*used in fast access operations */

	/*-- pulldown fields ------------*/ 
	for (i=0; i<ANZGROUPS+1; i++)
		{
		pML = &pulldownlist[i]; 
		pML->func = 0;
		pML->data = 0;
		pML->menu = False;
		pML->submenu = grouplist[i];
		pML->submenutitle = 0;
		}
	/*--- Dispatch menus in grouplists, update subitems in pulldowns --*/
	for (i=0; i<ANZ_MENU; i++)
		{
		a = &menu[i];
		g = a->zuogruppe;
		j = a->zuonumber;
		pulldownlist[g].anz_subitems++;			/* update pulldown */

		pML = &grouplist[g][j];						/* update members of grouplist */ 
		pML->titel = a->titel;
		pML->func  = xUIbeeping;
		pML->data  = (XtPointer)a;
		pML->menu  = True;
		pML->mnemonic = a->titel[0];
		if (a->flags)
			{
			if (allowed && allmenuflag)
				a->popup = xUIpopup(i);				/* create at init, get a widget*/
			else
				a->popup = NULL;
			if (allowed != 0)
				{
				pML->func = xUIcallpopup;
				pML->data = (XtPointer)a;
				}
			pML->status = True;		/*sensitive*/
			}
		else
			pML->status = False;		/*insensitive*/
		}
	/*------- Special menus -------------------*/
	pML = &grouplist[0][1];						/* store global values     */ 
	pML->func = xUIglobFileSave;
	pML = &grouplist[0][2];						/* Option/Einstellungen    */ 
	pML->func = xUIoption;
	pML = &grouplist[0][3];						/* Quit menu               */ 
	pML->func = xUImainMenuQuit;
	pML = &grouplist[ANZGROUPS][0];			/* help Application        */ 
	pML->func = xUIhelp;
	pML = &grouplist[ANZGROUPS][1];			/* help About licence text */ 
	pML->func = xUIlicenceDisplay;
}


/*F--------------------------------------------------------------------------
 *  Function:	xUImainStop ()
 *					User or programm has decided to stop the application
 *  In:			-a code for perror
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
int xUImainStop(int exitcode)
{
	extern int	DebugFlag;
	extern char databasenotok;

	if (!databasenotok)
		{
		/*--- Talk to DBI that he can shut the store ----*/
		COMMSTAT  = MESSAGEOK;
		COMMTYP   = GLOBAL;
		ACTIONTYP = QUIT;
		MENUNR    = NULL;
		FELDNR    = NULL;
		(void)xUItalkto(SEND, 0, 0);
		}

	(void)PSIPCsocketclose(ipcfd);

	/*--- free all labels texts and pointers ---*/
	xUIlabelsFree();   

	if (DebugFlag)
		PSSYSdebug(NULL, NULL, "GUI exit with code %d", exitcode);
	
	exit(exitcode);
}


/*F--------------------------------------------------------------------------
 *  Function:	xUImainClose ()
 *					programm has decided to stop the application
 *					Store global data in setup file, special clean if language changes
 *  In:			-std cb params
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUImainClose( Widget w, XtPointer closure, XtPointer data)
{
	/*-- Play audio file --------------------------*/
	xUIaudioPlay( app_data.audioQuit);  

	/*--- stop the application --------------------*/
	xUImainStop(0); 
}


/*F--------------------------------------------------------------------------
 *  Function:	xUImainMenuQuit ()
 *					User has decided to quit the application
 *					ask a question if he is shure ?
 *  In:			-std cb params
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUImainMenuQuit( Widget w, XtPointer closure, XtPointer data)
{
	/*--- Store global data in start-up file ------*/
	xUIdeffrage (LABEL_YES, LABEL_NO, LABEL_MAINQUIT, 
               (XtCallbackProc)xUImainClose, closure, toplevel);
}

