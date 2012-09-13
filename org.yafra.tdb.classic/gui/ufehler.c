/**************************************************************
 * Modul:     GUI - Dialog						ufehler.c                 
 *                                                     
 *            Open error file and find message with index
 *            Create an error message popup         
 *                                                     
 * Copyright: yafra.org, Basel, Switzerland 
 **************************************************************/
#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ufehler.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";


/*F--------------------------------------------------------------------------
 *  Function:	xUIfehler ()
 *					Look for a file corresponding to error number
 *
 *  In:			-error number, and parent to build dialog
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUIfehler( char fehlernr, Widget parent)
{
	extern ApplicationData app_data;
	extern char *tempo;
	extern long maxtempo;
	extern int aktmenuz;
	extern int aktmenu[];
	extern Widget	toplevel;
	extern MENU		menu[];
   extern char *	xuiLabelTable[][XUILABMAXTEXTS];  

	FILE		*fp;
	int		len, nr;
	char		rec[_CHAR80+1], *ptr;
	char		numbuf[_CHAR30+1];
	Widget	aktwidget;
	Boolean	found;                     /*true when message nr exists in file */

	/*---- look for a file containing error messages -------*/
	fp = fopen( app_data.errorfile, _P_READ_);
	if (fp)
	{
		len = 0;
		nr = 0;
		found = False; 
		/*--- scan file to find message corresp. to nr ----*/
		while (fgets(rec, sizeof(rec), fp) )
		{
			/*--- check error number ------------------*/
			if (rec[0] == '#')
			{
				if (found)
					 break;                         /* exit >>> text lines copied */
				xBMscan( &rec[1], numbuf, '\n' );
				nr = atoi( numbuf);                /* valid up to non digit*/
			}
			else if (nr == (int)fehlernr)
			{
				/*--- Get one or more lines of text ----*/
				tempo = (char *)xUIalloc((void *)tempo, &maxtempo,
							 app_data.maxdatain, len+strlen(rec)+1, sizeof(char));
				if (!found)
					*tempo = 0;                      /* clear at begin */
				len = strlen(rec);
#ifdef ps_dos
				len -= 2;                           /* cr, lf */
#else
				len -= 1;
#endif
				rec[len] = '\n';
				strncat(tempo, rec, len+1);
				found = True;                      /* exit at next '#' token */
			}
		}
		fclose(fp);
		if (tempo[strlen(tempo)-1] == '\n')      /* at end of text */
			tempo[strlen(tempo)-1] = 0;       
	}
	else	/*--- Error file not found ----------------------------------*/
	{
		/*--- Get default message ---*/
		tempo = (char *)xUIalloc((void *)tempo, &maxtempo,
				app_data.maxdatain, strlen(app_data.noerrorfilemsg), sizeof(char));
		sprintf( tempo, "%s", app_data.noerrorfilemsg);
	}

	/*---- Look for a parent --------*/
	if (parent) {
		aktwidget = parent;
	} else {
		if (aktmenuz >= 0) {
			aktwidget = menu[aktmenu[aktmenuz]].popup;
		} else {
			aktwidget = toplevel;
		}
	}
	/*---- display error message  --------*/
	xUItextshell( aktwidget, _MSG_ERROR, tempo ); 
	xUIbeep( aktwidget, 0, 0, 0);
	return;
}
