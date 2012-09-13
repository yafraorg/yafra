/**************************************************************
 * modul:     Internet Tools Interfaces for Unix and Windows
 *
 * tools:     WWW Browser start with URL
 *            Mail Reader start for reading and sending purposes
 *            Sending e-mail in background
 *            News Reader start for reading and posting
 *
 * copyright: Yafra.org, Switzerland
 **************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssys/source/inettools.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

/* piso includes */
#include <stdlib.h>
#include <pssys.h>

#ifdef ps_win
#include <windows.h>
#include <process.h>
#include <ddeml.h>
static void WIN_WWW(char *, int);
static void WIN_Mail(char *, char *, int, int);
static int WIN_SendMail(char *, char *, char *, char *, int, int);
static void WIN_News(char *, int);
#else
static void UNIX_WWW(char *, int);
static void UNIX_Mail(char *, char *, int, int);
static int UNIX_SendMail(char *, char *, char *, char *, int, int);
static void UNIX_News(char *, int);
#endif

/************************************************************
 * WWW starter
 *
 * starts a WWW browser with an URL
 *
 * returns     nothing
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1997
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI void PSSYSwww(char *aURL, int aTyp)
{
#ifdef ps_win
	WIN_WWW(aURL, aTyp);
#elif ps_unix
	UNIX_WWW(aURL, aTyp);
#endif
}

/************************************************************
 * start a e-mail Reader
 *
 * help is integrated over WWW Browsers. So the page string
 * has to be an URL with help infos in it.
 *
 * returns     nothing
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI void PSSYSmail(char *aUser, char *aTO, int aTyp, int aFlag)
{
#ifdef ps_win
	WIN_Mail(aUser, aTO, aTyp, aFlag);
#elif ps_unix
	UNIX_Mail(aUser, aTO, aTyp, aFlag);
#endif
}

/************************************************************
 * send an e-mail to one person
 *
 * help is integrated over WWW Browsers. So the page string
 * has to be an URL with help infos in it.
 *
 * returns     nothing
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1997
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI int PSSYSsendmail(char *aUser, char *aTO, char *aSubject, char *aMail, int aTyp, int aFlag)
{
	int cret;
#ifdef ps_win
	cret = WIN_SendMail(aUser, aTO, aSubject, aMail, aTyp, aFlag);
#elif ps_unix
	cret = UNIX_SendMail(aUser, aTO, aSubject, aMail, aTyp, aFlag);
#endif
	return(cret);
}

/************************************************************
 * start a UseNet Reader
 *
 * help is integrated over WWW Browsers. So the page string
 * has to be an URL with help infos in it.
 *
 * returns     nothing
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI void PSSYSnews(char *aServer, int aTyp)
{
#ifdef ps_win
	WIN_News(aServer, aTyp);
#elif ps_unix
	UNIX_News(aServer, aTyp);
#endif
}





/************************************************************************/
/**           STATIC/LOCAL FUNCTIONS                                  ***/
/************************************************************************/

#ifdef ps_win
static void WIN_WWW(char *page, int typ)
{
	DWORD idInst = 0;
	HCONV hConv;         /* conversation handle            */
	HSZ hszServName;     /* service name string handle     */
	HSZ hszSysTopic;     /* System topic string handle     */
	HSZ hszURLname;
	BOOL cret;
	UINT dderet;
	HDDEDATA ddetrxret;

	char browsercmd[1024];
	char activecmd[1024];
	int csysret;

	if (page == NULL)
		return;

	/* check string len of page here */
	(void)sprintf(browsercmd, "%s,,0xFFFFFFFF,0x4", page);
	(void)strcpy(activecmd, "0xFFFFFFFF,0x0");

	/* DDE stuff */
	dderet = DdeInitialize(&idInst, (PFNCALLBACK) NULL, NULL, 0);

	/* activate current browser windows */
	hszSysTopic = DdeCreateStringHandle(idInst, "WWW_Activate", CP_WINANSI);
	hszURLname = DdeCreateStringHandle(idInst, activecmd, CP_WINANSI);
	hConv = DdeConnect(idInst, hszServName, hszSysTopic, (PCONVCONTEXT) NULL);
	if (hConv != NULL)
		{
		ddetrxret = DdeClientTransaction(NULL, 0, hConv, hszURLname, 0, XTYP_REQUEST, TIMEOUT_ASYNC, NULL);
		cret = DdeDisconnect(hConv);
		}

	hszServName = DdeCreateStringHandle(idInst, "NETSCAPE", CP_WINANSI);
	hszSysTopic = DdeCreateStringHandle(idInst, "WWW_OpenURL", CP_WINANSI);
	hConv = DdeConnect(idInst, hszServName, hszSysTopic, (PCONVCONTEXT) NULL);
	if (hConv == NULL)
		{
		/* Start Netscape browser with desired URL here */
		(void)sprintf(browsercmd, "%s %s", PSSYS_WWW_NS_CMD, page);
		csysret = PSSYSexecute(browsercmd);
		}

	hszURLname = DdeCreateStringHandle(idInst, browsercmd, CP_WINANSI);
	ddetrxret = DdeClientTransaction(NULL, 0, hConv, hszURLname, 0, XTYP_REQUEST, TIMEOUT_ASYNC, NULL);

	cret = DdeDisconnect(hConv);

	cret = DdeUninitialize(idInst);
}
#elif ps_unix
/*************************************************************
 * start a UNIX WWW browser with a URL
 *
 * start a WWW browser or display a page in an existing WWW
 * browser as help from your application
 *
 * returns     nothing
 *
 * library:    PSINETTOOLS
 *
 * include:    pssys.h
 *
 * copyright:  Yafra.org, Switzerland
 *
 * author:     Administrator, 1997
 **************************************************************/
static void UNIX_WWW(char *page /* URL */,
                     int typ /* Which Browser */)
{
	char browsercmd[1024];
	int cret = 0;

	if (page == NULL)
		return;

	/* check string len of page here */
	(void)sprintf(browsercmd, "%s -remote 'openURL(%s)'", PSSYS_WWW_NS_CMD, page);
	cret = PSSYSexecute(browsercmd);
	if (cret != 0)
		{
		(void)sprintf(browsercmd, "%s %s &", PSSYS_WWW_NS_CMD, page);
		cret = PSSYSexecute(browsercmd);
		}
}
#endif


#ifdef ps_win
static void WIN_Mail(char *user, char *to, int typ, int flag)
{
	DWORD idInst = 0;
	HCONV hConv;         /* conversation handle            */
	HSZ hszServName;     /* service name string handle     */
	HSZ hszSysTopic;     /* System topic string handle     */
	HSZ hszURLname;
	BOOL cret;
	UINT dderet;
	HDDEDATA ddetrxret;

	char browsercmd[1024];
	char initcmd[1024];
	int csysret;

	/* make init here */
	if (to == NULL || *to == NULL)
		*initcmd = NULL;
	else
		(void)strcpy(initcmd, "0xFFFFFFFF,0x0");
	(void)sprintf(browsercmd, "mailto:%s,,0xFFFFFFFF,0x4", to);

	/* DDE stuff */
	dderet = DdeInitialize(&idInst, (PFNCALLBACK) NULL, NULL, 0);
	hszServName = DdeCreateStringHandle(idInst, "NETSCAPE", CP_WINANSI);

	/* activate current browser windows */
	if (*initcmd == NULL)
		hszSysTopic = DdeCreateStringHandle(idInst, "WWW_Exit", CP_WINANSI);
	else
		hszSysTopic = DdeCreateStringHandle(idInst, "WWW_Activate", CP_WINANSI);
	hszURLname = DdeCreateStringHandle(idInst, initcmd, CP_WINANSI);
	hConv = DdeConnect(idInst, hszServName, hszSysTopic, (PCONVCONTEXT) NULL);
	if (hConv != NULL)
		{
		ddetrxret = DdeClientTransaction(NULL, 0, hConv, hszURLname, 0, XTYP_REQUEST, TIMEOUT_ASYNC, NULL);
		cret = DdeDisconnect(hConv);
		}

	/* load URL to active browser */
	hszSysTopic = DdeCreateStringHandle(idInst, "WWW_OpenURL", CP_WINANSI);
	hConv = DdeConnect(idInst, hszServName, hszSysTopic, (PCONVCONTEXT) NULL);
	if (hConv == NULL)
		{
		/* Start Netscape browser with desired URL here */
		(void)sprintf(browsercmd, "%s -mail", PSSYS_WWW_NS_CMD);
		csysret = PSSYSexecute(browsercmd);
		}

	hszURLname = DdeCreateStringHandle(idInst, browsercmd, CP_WINANSI);
	ddetrxret = DdeClientTransaction(NULL, 0, hConv, hszURLname, 0, XTYP_REQUEST, TIMEOUT_ASYNC, NULL);

	cret = DdeDisconnect(hConv);

	cret = DdeUninitialize(idInst);
}
#elif ps_unix
static void UNIX_Mail(char *user, char *to, int typ, int flag)
{
	char browsercmd[1024];
	char mailcmd[128];
	int cret = 0;


/*************** old style mailx workaround ************
	(void)sprintf(cmd, "mailx -e && psedit -f /usr/mail/%s",
						user);
	(void)PSSYSexecute(cmd);
********************************************************/

	/* set sendmail program */
	if (typ == PSSYS_WWWTYPUNIXMAIL)
		{
		(void)sprintf(mailcmd, PSSYS_WWW_UNIXMAIL_CMD);
		/* check string len of page here */
		if (to == NULL || *to == NULL)
			(void)sprintf(browsercmd, PSSYS_WWW_UNIXMAIL_CMD, "");
		else
			(void)sprintf(browsercmd, PSSYS_WWW_UNIXMAIL_CMD, to);
		}
	else /* TYPNS */
		{
		(void)sprintf(mailcmd, "%s", PSSYS_WWW_NS_CMD);
		/* check string len of page here */
		if (to == NULL || *to == NULL)
			(void)sprintf(browsercmd, "%s -remote 'mailto()'", mailcmd);
		else
			(void)sprintf(browsercmd, "%s -remote 'mailto(%s)'", mailcmd, to);
		}

	cret = PSSYSexecute(browsercmd);
	if (cret != 0)
		{
		(void)strcat(browsercmd, " &");
		cret = PSSYSexecute(browsercmd);
		}
}
#endif

#ifdef ps_win
static int WIN_SendMail(char *user, char *to, char *subject, char *mail, int typ, int flag)
{
	int cret;
	cret = PSOK;
	return(cret);
}
#elif ps_unix
static int UNIX_SendMail(char *user, char *to, char *subject, char *mail, int typ, int flag)
{
	int cret = 0;
	char browsercmd[1024];
	char mailcmd[128];

	if (to == NULL || *to == NULL)
		return(PSERROR);

	/* set sendmail program */
	if (typ == PSSYS_WWWTYPUNIXMAIL)
		{
		(void)sprintf(mailcmd, PSSYS_WWW_UNIXMAIL_CMD);
		/* check string len of page here */
		(void)sprintf(browsercmd, PSSYS_WWW_UNIXMAIL_CMD, to);
		}
	else /* TYPNS */
		{
		(void)sprintf(mailcmd, "%s", PSSYS_WWW_NS_CMD);
		/* check string len of page here */
		(void)sprintf(browsercmd, "%s -remote 'mailto(%s)'", mailcmd, to);
		}

	cret = PSSYSexecute(browsercmd);
	if (cret != 0)
		{
		(void)strcat(browsercmd, " &");
		cret = PSSYSexecute(browsercmd);
		}
	return(cret);
}
#endif

#ifdef ps_win
static void WIN_News(char *server, int typ)
{
	DWORD idInst = 0;
	HCONV hConv;         /* conversation handle            */
	HSZ hszServName;     /* service name string handle     */
	HSZ hszSysTopic;     /* System topic string handle     */
	HSZ hszURLname;
	BOOL cret;
	UINT dderet;
	HDDEDATA ddetrxret;

	char browsercmd[1024];
	int csysret;

	if (server == NULL)
		return;

	/* check string len of page here */
	(void)sprintf(browsercmd, "news://%s/,,0xFFFFFFFF,0x4", server);

	/* DDE stuff */
	dderet = DdeInitialize(&idInst, (PFNCALLBACK) NULL, NULL, 0);

	hszServName = DdeCreateStringHandle(idInst, "NETSCAPE", CP_WINANSI);
	hszSysTopic = DdeCreateStringHandle(idInst, "WWW_OpenURL", CP_WINANSI);
	hConv = DdeConnect(idInst, hszServName, hszSysTopic, (PCONVCONTEXT) NULL); /* use default context        */
	if (hConv == NULL)
		{
		/* Start Netscape browser with desired URL here */
		(void)sprintf(browsercmd, "%s -news", PSSYS_WWW_NS_CMD);
		csysret = PSSYSexecute(browsercmd);
		}

	hszURLname = DdeCreateStringHandle(idInst, browsercmd, CP_WINANSI);
	ddetrxret = DdeClientTransaction(NULL, 0, hConv, hszURLname, 0, XTYP_REQUEST, TIMEOUT_ASYNC, NULL);

	cret = DdeDisconnect(hConv);

	cret = DdeUninitialize(idInst);
}
#elif ps_unix
static void UNIX_News(char *server, int typ)
{
	char browsercmd[1024];
	int cret = 0;

	if (server == NULL || *server == NULL)
		return;

	/* check string len of page here */
	(void)sprintf(browsercmd, "%s -remote 'openURL(news:%s)'", PSSYS_WWW_NS_CMD, server);
	cret = PSSYSexecute(browsercmd);
	if (cret != 0)
		{
		(void)sprintf(browsercmd, "%s -remote 'openURL(news:%s)' &", PSSYS_WWW_NS_CMD, server);
		cret = PSSYSexecute(browsercmd);
		}
}
#endif
