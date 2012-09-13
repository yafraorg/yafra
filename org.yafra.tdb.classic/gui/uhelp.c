/*D***********************************************************
 * Modul:		GUI - Dialog				uhelp.c
 *                                                            
 *					Get help file and popup a window                                                  
 *             help-About is stored with licence stuff                                               
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************
 */
#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uhelp.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";




/*F--------------------------------------------------------------------------
 *  Function:	xUIhelp ()
 *					-Send a request to DB to get the help text
 *  In:			-std callback parameters  
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIhelp(Widget w, XtPointer closure, XtPointer data)
{
	extern Widget			toplevel;
	extern Boolean			helpPresent; 
	extern unsigned char actiontoggle;
	extern int				aktmenuz;
	extern int				aktmenuobj[];
	extern unsigned char actiontoggle;
	extern int     		bm_ix;

	BOOKMENU		*b;
	MENU				*a;

	/*--- look for a parent ------------------------*/
	a = (MENU *)closure;

	/*--- Check if already present ------------------*/
	if ( !helpPresent)
		{
		/*--- check BM menu ---------------------*/
		b = xBMmenuActive();
		if (b)
			{
			if (bm_ix == _BMCATIX)
				MENUNR  = (unsigned char) _RESERVATION  ;
			else if (bm_ix == _BMDLNIX)
				MENUNR  = (unsigned char) _BMDLN  ;
			else
				MENUNR  = NULL ;
			}
		else if ( a->popup )
			MENUNR    = (unsigned char)aktmenuobj[aktmenuz];
		else 
			MENUNR    = _GLOBALMENU;

		/*--- send a request ---------*/
		COMMTYP   = HELPCALL;
		ACTIONTYP = actiontoggle;
		FELDNR    = NULL;
		(void)xUItalkto(SEND, 0, 0);
		} 
	else
		xUIbeep( toplevel, 0, 0, 0);
}


/*F---------------------------------------------------------------------
 *	Function:	xUIhelpQuit 
 *					-Remove help text shell 
 *					-reset presence flag
 *
 *	In:			-std CB params: closure is the shell 
 *					-
 *-----------------------------------------------------------------------
 */
XtCallbackProc xUIhelpQuit( Widget w, XtPointer closure, XtPointer data)
{
	extern Boolean helpPresent; 

	XtDestroyWidget( (Widget)closure);
	helpPresent = False; 
}

/*F---------------------------------------------------------------------
 *	Function:	xUIhelpQuit 
 *					-Remove help text shell 
 *					-reset presence flag
 *
 *	In:			-std CB params: closure is the shell 
 *					-
 *-----------------------------------------------------------------------
 */
void xUIopenHelp(char *entries)
{
	extern ApplicationData app_data; /* MARCO POLO app-defaults */
	extern GLOBDATA globdata;        /* MARCO POLO globals */
	extern Boolean helpPresent; 
	extern int DebugFlag;
	char mphelp_url[2048];
	char helppage[1024];
	int cret;

	(void)strcpy(helppage, entries);
	cret = sprintf(mphelp_url, "%s%s/%s", app_data.mpurlprefix, globdata.sprache, helppage);

	if (DebugFlag)
		PSSYSdebug(NULL, NULL, "popup HELP window with URL %s", mphelp_url);

	PSSYShelp(mphelp_url);
	helpPresent = False; 
}





#ifdef COMPILE
/*F--------------------------------------------------------------------------
 *  Function:	xUIhelpfromfile ()
 *					-get the help text from DB 
 *					-build a popup to display content
 *					-
 *  In:			-std callback parameters  
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUIhelpfromfile( Widget w, XtPointer closure, XtPointer data )
{
	extern Widget toplevel;
	extern MENU	menu[];
	extern MENU	glob;
	extern GLOBDATA globdata;
	extern ApplicationData app_data;
	extern char   *tempo;
	extern long		maxtempo;
   extern char *	xuiLabelTable[][XUILABMAXTEXTS];  
	extern Boolean helpPresent; 

	Arg 		wargs[10];
	int  		lines, breite, c;
	FILE		*fp;
	char		helpfile[_CHAR200], *ptr;
	struct stat		stbuf;
	Boolean			ok;
	XmString			text;
	Widget			aktparent;
	MENU				*a;

	ok = True;
	a = (MENU *)closure;

	/*---- Look for help file ---------------*/
/*	(void)sprintf(helpfile, "%s/%s", globdata.helppath, a->helpfile);   */
(void)sprintf(helpfile, "%s/%s", "/users/softech/mapo/help/deutsch", a->helpfile);   
	if (stat(helpfile, &stbuf) != -1)
		{
		if ((fp = fopen(helpfile, "r")))
			{
			tempo = (char *)xUIalloc((void *)tempo, &maxtempo,
										app_data.maxdatain, stbuf.st_size+1, sizeof(char));
			/*-- copy content of file --*/
			ptr = tempo;
			while ((c = fgetc(fp)) != EOF)
				*ptr++ = (unsigned char)c;
			*ptr = 0;
			(void)fclose(fp);
			}
		else
			ok = False;
		}
	else
		ok = False;

	/*---- verify parent ----------------*/
	if ( a->popup )
		aktparent = a->popup;
	else
		aktparent = toplevel;

	/*---- messages calls ---------------*/
	if (ok)
	{
		if ( !helpPresent)
		{
			xUItextshell( aktparent, _MSG_HELP, tempo ); 
			helpPresent = True;
		} 
	}
	else
		xUIfehler( XUINOHELPFILE, 0);
}
#endif


