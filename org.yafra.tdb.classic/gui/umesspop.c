/*D*************************************************************************
 * Modul:		   GUI - Dialog			umesspop.c
 *
 * 					Create a message popup and/or a pcx popup
 *
 *						
 * Copyright: yafra.org, Basel, Switzerland
 ***************************************************************************
 */

#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/umesspop.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";



/*F--------------------------------------------------------------------------
 *  Function:	xUImessagepopup ()
 *					popup a message whose type is given 
 *					
 *  In:			-art, message and parent 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void xUImessagepopup( unsigned char art, char *message, Widget aktparent)
{
	extern ApplicationData   app_data;                /* xUIappdefaults.h */
	extern GLOBDATA		globdata;
	extern Widget   messagewidget, messageshell;
	extern Widget   toplevel;
   extern char *	 xuiLabelTable[][XUILABMAXTEXTS];  
	extern Boolean		audioflag;

	Arg		 wargs[10];
	int       cret;
	int		 lines, breite;
	XmString	 xmStr;

	if (aktparent == NULL)
		aktparent = toplevel;

	/*--- interpretiere Meldungstyp --------*/
	switch(art)
		{
		case (unsigned char)MESSAGEOK:			/* handled by commtyp INFO */
		case (unsigned char)MESSAGEINFO:
		case (unsigned char)MESSAGEPCX:
		case (unsigned char)MESSAGEINFOPCX:
			/*-- Play audio file -----------*/
			xUIaudioPlay( app_data.audioMessage);  
		break;

		case (unsigned char)MESSAGEWARNING:
			xUItextshell(aktparent, _MSG_WARNING, message ); 
			break;

		case (unsigned char)MESSAGEDBERROR:
		case (unsigned char)MESSAGEERROR:
		default:
			/*-- Play audio file -----------*/
			xUIaudioPlay( app_data.audioError);  
			xUItextshell(aktparent, _MSG_ERROR, message ); 
			xUIbeep( aktparent, 0, 0, 0);
			break;
		}
}
