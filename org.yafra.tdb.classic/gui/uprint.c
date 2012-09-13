/*D*************************************************************************
 * Modul:			GUI - Dialog				uprint.c   
 *            
 * 					Create a text file
 *						Invoke the print order set in appdefault
 *            		
 * Functions:	   
 * 
 * Copyright: yafra.org, Basel, Switzerland
 ***************************************************************************
 */
#include <uinclude.h>
#include <fcntl.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uprint.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";

static void write_l(int, char *);

/*F---------------------------------------------------------------------
 *	Function:	xUIprintText 
 *					-create a file and write text 
 *					-Print the file with command  
 *					-
 *	In:			-std callback param, closure=scrolled text
 *					-
 *-----------------------------------------------------------------------
 */
XtCallbackProc xUIprintText( Widget w, XtPointer closure, XtPointer wdata)
{
	extern ApplicationData app_data;
	extern int DebugFlag;

	extern int errno;

	FILE	*fp;
	int   cret;
	int	len;
	int	word;
	char	*theText; 
	char	*command; 
	char	dde_buff[128];

	/*--- Open for writing ---------*/
	if ((fp = fopen(app_data.printfilename, _P_WRITE_)) == NULL)
		{
		xUIfehler( XUIPRINT, w);
		return;
		}

   /*--- Get text widget and write --------------*/
	theText = XmTextGetString( (Widget)closure); 
	len = strlen( theText);
	fwrite( theText, sizeof(char), len, fp);

	/*--- Close the file ----------------*/
	if (fclose(fp) != NULL)
		{
		xUIfehler( XUIPRINT, w);
		return;
		}
	XtFree(theText); 

#ifdef ps_unix
	/*--- Don't start immediately HP400 has speed problems ----*/
	sleep(2);
	/*--- Malloc space for command (size of names + null */
	command = XtMalloc( strlen(app_data.printcommand)
							 + strlen(app_data.printfilename) + 4);
	sprintf(command, "%s %s\0", app_data.printcommand, app_data.printfilename);
	/*--- Execute command by using the FIFO piserver ----------*/
	(void)PSSYSexecute( command);
	XtFree(command);
#endif

#ifdef ps_winnt
	if (DebugFlag)
		printf("debug: start opening the dde device\n");

	cret = PSSYSddeOpen("/dev/dde/WinWord/system", &word, 1);
	if (cret == PSOK)
		{
		if (DebugFlag)
			printf("debug: word device opened\n");
		cret = PSSYSddeWrite(word, "[AppRestore]");
		cret = PSSYSddeWrite(word, "[FileOpen.name = \"%s\"]", app_data.printfilename);
		cret = PSSYSddeWrite(word, "[StartOfDocument]");
		cret = PSSYSddeWrite(word, "[Insert \"Output von MARCO POLO GUI\"]");
		cret = PSSYSddeWrite(word, "[InsertPara]");
		cret = PSSYSddeClose(word);
		}
	else
		{
		if (DebugFlag)
			printf("debug: DDE open error");
		}
#endif

}
