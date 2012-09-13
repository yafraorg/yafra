/*D***********************************************************
 * copyright: yafra.org, Switzerland, 2004
 *
 * modul:     travelDB GTK user interface
 * GTK func:  callback
 * describe:  pressed OK and CANCEL
 *
 * CVS tag:   $Name:  $
 * author:    $Author: mwn $
 * revision:  $Revision: 1.8 $
 **************************************************************/
static char rcsid[]="$Id: cb-logon.c,v 1.8 2008-11-23 15:44:38 mwn Exp $";

#include <gtk/gtk.h>
#include <stdio.h>

#ifdef ps_unix
#ifndef ps_cygwin
#include <unistd.h>
#endif
#include <sys/types.h>
#include <pwd.h>
#endif

#include "callbacks.h"
#include "interface.h"
#include "support.h"

/* travelDB GTK GUI includes (includes mpnet.h with libXML as well) */
#include <mpgtk.h>

#define CHK_CONNECT_OK 0
#define CHK_CONNECT_ERROR 1
#define SERVBUFSIZE 1024

/* global variables */
// extern int errno;
// extern char *sys_errlist[];
extern int dialogsprache;
extern int outputsprache;
extern int sprache;
extern int aktuellesprache;
extern char   argbuffer[2*_RECORDLEN];
extern char   messageBuffer[8*_RECORDLEN];
extern char sqlquery[];
extern unsigned char bm_obj;
extern PSmemobj outputmem;

/*--- local functions -------------------------*/
static void Initialization(void);
int MPXMLcreateLogin(void);

/*--- IPC client data init ---*/
char *PSIPCservicename = MPNET_SERVICE;
char *PSIPCservicetitle = "MARCO POLO TO WWW Server";
char *PSIPCprot = MPNET_PROT;
int (*PSclient)(int, char**, int);


void on_logon_clicked(GtkButton *button, gpointer user_data)
{
	extern int ipcfd;

	extern MP_GLOBALPROFIL globprof;
	extern MP_PROFIL prof;
	extern int MPNETstate;
	extern int FatalError;
	extern char messageBuffer[];
	extern int DebugFlag;

	/* MPNET parameters */
	int MPnextqry = TRUE;

	/* WORKING parameters */
	int cret; /* code return */
	int len;
	char *Pbuf;

	xmlDoc *doc = NULL;
	xmlChar *docmem = NULL;

	GtkWidget *text;
	GtkWidget *logon;
	GtkWidget *main1;
	gchar *user;
	gchar *db;
	gchar *pwd;
	gchar *host;

	logon = lookup_widget( GTK_WIDGET(button), "tdb_login");
	text = lookup_widget( GTK_WIDGET(logon), "e_logon_host");
	host = gtk_entry_get_text(text);
	text = lookup_widget( GTK_WIDGET(logon), "e_logon_db");
	db = gtk_entry_get_text(text);
	text = lookup_widget( GTK_WIDGET(logon), "e_logon_user");
	user = gtk_entry_get_text(text);
	text = lookup_widget( GTK_WIDGET(logon), "e_logon_pw");
	pwd = gtk_entry_get_text(text);

	(void)strcpy(globprof.database, db);
	(void)strcpy(globprof.hostname, host);
	(void)strcpy(globprof.user, user);
	(void)strcpy(globprof.password, pwd);

	/* INIT */
	Initialization();
	(void)PSIPCsocketinit();

	/* start connection to the server */
	if (DebugFlag)
		PSSYSdebug(MPGTK_DBGFILE, MPGTK_PRGNAME, "socket server host is %s", db);
	ipcfd = (int)PSIPCclient(host, MPNET_SERVICE, MPNET_PROT);
	if (ipcfd == -1)
		MPGTKexit(MPS_IPCERROR);

	// SEND created login request
	cret = MPXMLcreateLogin();

	/* create main user interface */
	main1 = create_tdb_main();
	gtk_widget_hide(logon);
	gtk_widget_show(main1);
	//	gtk_widget_destroy(logon);
}


void on_logon_cancel_clicked(GtkButton *button, gpointer user_data)
{
	extern int DebugFlag;

	if (DebugFlag)
		PSSYSdebug(MPGTK_DBGFILE, NULL, "pressed cancel");
	gtk_main_quit();
}


/*--------------------------------------------------------------*/
/* Initialization   - give initial value to variables           */
/*                    for each query to the DB                  */
/*--------------------------------------------------------------*/
static void Initialization(void)
{
	extern int FatalError;

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

	/*--- init flags ---*/
	FatalError      = (int)FALSE;

	/*--- install signal handlers ----*/
	MPinstall_signals(0);

}


/*--------------------------------------------------------------
 * create login xml request to send to the server
 *--------------------------------------------------------------*/
int MPXMLcreateLogin()
{
	extern int DebugFlag;
	extern int MPNETstate;
	extern MP_GLOBALPROFIL globprof;
	char tmp[_CHARMAXLEN];
	int cret = MPOK;

	cret = MPXMLcreate("login", 1);
	if (cret == MPOK)
		cret = MPXMLstartObject("LOGIN");
	if (cret == MPOK)
		cret = MPXMLaddElementString("DBNAME", globprof.database);
	if (cret == MPOK)
		cret = MPXMLaddElementString("USER", globprof.user);
	if (cret == MPOK)
		cret = MPXMLaddElementString("PWD", globprof.password);
	if (cret == MPOK)
		cret = MPXMLaddElementString("CLIENTHOSTNAME", globprof.hostname);
	if (cret == MPOK)
		{
		(void)sprintf(tmp, "%d", MPNETstate);
		cret = MPXMLaddElementString("FLAG", "0");
		}
	if (cret == MPOK)
		cret = MPXMLendObject();
	MPNETstate = cret;
	if (cret == MPOK)
		cret = MPXMLsend(MPNETstate, "OK", DEFMEMCHUNK);

	if (DebugFlag)
		PSSYSdebug(MPGTK_DBGFILE, MPGTK_PRGNAME, "login xml send with cret %d and status %d", cret, MPNETstate);

	return(cret);
}
