/*D***********************************************************
 * Modul:		GUI - global profile
 *					handle global profile, read/write to file,
 *             get host/display names
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 * Author:    Administrator
 **************************************************************/
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uprofile.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";

#include <uinclude.h>

/* local function prototypes */
static int  MPUIprofile_readfromfile(char *, MP_GLOBALPROFIL *);
static void MPUIprofile_gethostnames(MP_GLOBALPROFIL *);
static int  MPUIprofile_writetofile(char *, MP_GLOBALPROFIL *);
static XtCallbackProc MPUIprofile_dialogsaveyes(Widget, XtPointer, XtPointer);


/*F---------------------------------------------------------------------
 *	Function:	MPUIprofile_init
 *					-init the MP_GLOBALPROFIL struct
 *	In:			-MP_GLOBALPROFIL pointer
 *	Out:			-MP_GLOBALPROFIL set
 * Return:     -MPOK or MPERROR
 *-----------------------------------------------------------------------*/
int MPUIprofile_init(char *aSetupfile, MP_GLOBALPROFIL *aGlobprof)
{
	extern int DebugFlag;
	int status;

	status = MPUIprofile_readfromfile(aSetupfile, aGlobprof);
	if (status != MPOK)
		{
		PSSYSdebug(NULL, NULL, "read from setup file (%s) error",
		           aSetupfile);
		return(status);
		}
	MPUIprofile_gethostnames(aGlobprof);

	if (DebugFlag)
		{
		PSSYSdebug(NULL, NULL, "db name is:      %s", aGlobprof->database);
		PSSYSdebug(NULL, NULL, "user name is:    %s", aGlobprof->user);
		PSSYSdebug(NULL, NULL, "host name is:    %s", aGlobprof->hostname);
		PSSYSdebug(NULL, NULL, "display name is: %s", aGlobprof->displayname);
		}
	return(status);
}

/*F--------------------------------------------------------------------------
 *  Function:	xUIglobFileSave ()
 *					User wants to save the values of global menu 
 *					ask a question if he is shure ?
 *  In:			-std cb params
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIglobFileSave( Widget w, XtPointer closure, XtPointer data)
{
	extern Widget toplevel;
	extern char  *xuiLabelTable [] [XUILABMAXTEXTS];  

	/*--- Store global data in start-up file ------*/
	xUIdeffrage (LABEL_YES, LABEL_NO, LABEL_GLOBALSAVE, 
               (XtCallbackProc)MPUIprofile_dialogsaveyes, closure, toplevel);
}







/*SF--------------------------------------------------------------------------
 *  Function:	add hostname and display to global profile
 *
 *  In:			-MP_GLOBALPROFIL pointer
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static void MPUIprofile_gethostnames(MP_GLOBALPROFIL *aGlobprof)
{
	char  hostname[_CHAR30+1];
	char *display;
	int   cret;
	int   hostret;

	/* get the workstation hostname */
	/* PSIPCclientinit() muss schon aufgerufen sein ! */
	hostret = PSIPCgetHostname(hostname, _CHAR30, 0);
	(void)strcpy(aGlobprof->hostname, hostname);

	/* get the display name from environment */
	/*!! probably it's better to get it with an X call */
	display = getenv( "DISPLAY" );
	if (display == NULL)
		{
		if (hostret == IPCOK)
			(void)sprintf(aGlobprof->displayname, "%s:0.0", hostname);
		else
			(void)strcpy(aGlobprof->displayname, "localhost:0.0");
		}
	else
		(void)strcpy(aGlobprof->displayname, display);
}


/*SF-------------------------------------------------------------------------
 *  Function:	read the setup configuration parameters and fill struct
 *					of global profile
 *
 *  In:			-file name
 *  out:			-
 *  Return:		-completion code 
 *---------------------------------------------------------------------------
 */
static int MPUIprofile_readfromfile(char *aSetupfile, MP_GLOBALPROFIL *aGlobprof)
{
	extern int DebugFlag;

	FILE *fp;
	char rec[_RECORDLEN], *ptr;
	char deffile[_CHAR30], defdir[_CHAR200];
	char setupfile[_CHAR200];
	int  index;
	char paramtext[_CHAR200+1];
#ifdef ps_unix
	struct stat statbuf;
#endif

	int	status = MPOK;

	/*--- try to find THE setup file or a default one --------*/
#ifdef ps_unix
	if (aSetupfile[0] == NULL)
		{
		(void)sprintf(defdir,   "%s", getenv("HOME"));
		(void)sprintf(deffile, ".%s", MP_SETUPFILE);
		(void)sprintf(setupfile, "%s/%s", defdir, deffile);
		}
	else
		(void)strcpy(setupfile, aSetupfile);

	if (stat(setupfile, &statbuf) == -1)   /*!!! not ANSI C */
		(void)sprintf(setupfile, "/usr/local/etc/%s.pro", MP_SETUPFILE);
#endif

#ifdef ps_win
		(void)sprintf(setupfile, "\\usr\\local\\etc\\%s.pro", MP_SETUPFILE);
#endif

	(void)strcpy(aSetupfile, setupfile);

	/*--- process whole file --------------*/
	fp = fopen(setupfile, _P_READ_);
	if (fp)
		{
		/*--- read all lines  --------------*/
		while (fgets(rec, sizeof(rec), fp)) 
			{
			/*-- force line termination with '\0'  ---------------- */
			/*-- bail out comments and other exotic lines ----------*/
			if ((rec[0] == '1') || (rec[0] =='2') || (rec[0] == '3'))
				{
				/*-- extract switch and text, '\0' is added! ---- */
				paramtext[0] = '\0';                     /* for missing param */			
				(void)sscanf(rec, "%d%*c%[^\r\n]", &index, paramtext); /* CR or CRLF works*/
				switch(index)
					{
					case 1:  /* 1 is DATABASENAME */
						paramtext[_CHAR200] = NULL;
						(void)strcpy(aGlobprof->database, paramtext);
						break;
					case 2:  /* 2 is USERNAME */
						paramtext[_USERLEN] = NULL;
						(void)strcpy(aGlobprof->user, paramtext);
						break;
					case 3:  /* 3 is USERPASSWORD */
						paramtext[_PWDLEN] = NULL;
						(void)strcpy(aGlobprof->password, paramtext);
						break;
					default:
						if (DebugFlag)
							PSSYSdebug(NULL, NULL, "setupfile index %d not supported", index);
						break;
					}
				}
			}
		(void)fclose(fp);
		status = MPOK;
		if (DebugFlag)
			PSSYSdebug(NULL, NULL, "setupfile %s read", setupfile);
		}
	else  /*-- fopen failed */
		status = MPERROR;

	return(status); 
}


/*SF--------------------------------------------------------------------------
 *  Function:	xUIglobFileWrite ()
 *					write the setup file of global data 
 *  In:			-flag if language has changed 
 *  out:			-
 *  Return:		-completion code 
 *---------------------------------------------------------------------------
 */
static int MPUIprofile_writetofile(char *aSetupfile, MP_GLOBALPROFIL *aGlobprof)
{
	extern int DebugFlag;
	int  status = MPOK;
	FILE *fp;

	/*--- Store global data in start-up file ------*/
	fp = fopen(aSetupfile, _P_WRITE_);
	if (fp)
		{
		/*-- 1 line comments is allowed ---------*/
		(void)fprintf(fp, "# MARCO POLO setupfile%s", _P_EOL_);

		/*--- Format and store all members ------*/
		(void)fprintf(fp, "1:%s%s", aGlobprof->database, _P_EOL_);
		(void)fprintf(fp, "2:%s%s", aGlobprof->user, _P_EOL_);
		(void)fclose(fp);
		if (DebugFlag)
			PSSYSdebug(NULL, NULL, "wrote setupfile %s", aSetupfile);
		}
	else  /*-- fopen failed */
		status = MPERROR;

	return(status);
}

/*SF-------------------------------------------------------------------------
 *  Function:	xUIglobFileSaveYes ()
 *					when asking question if he is shure, user said yes 
 *					
 *  In:			-std cb params
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static XtCallbackProc MPUIprofile_dialogsaveyes(Widget w, XtPointer closure, XtPointer data)
{
	extern char setupfile[];
	extern MP_GLOBALPROFIL globprof;

	int status;

	/*--- Store global data in start-up file ------*/
	status = MPUIprofile_writetofile(setupfile, &globprof);
}
