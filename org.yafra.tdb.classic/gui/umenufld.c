/*D************************************************************
 * Modul:		GUI - BM dialog                     umenufld.c
 *
 *					Menu-level behaviour functions 
 *					Set sensitivity of pushbuttons, action bar, color
 *
 *
 * Functions:	
 * Callbacks:	
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/umenufld.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";


/*F---------------------------------------------------------------------
 *	Function:	xUImenufeld 
 *					change behaviour/color of a menu button, fields sensitivity
 *					
 *	In:			-std CB parameters 
 *					-
 *-----------------------------------------------------------------------
 */
void xUImenufeld( MENU *menu, Widget feld, Boolean sensedit, Boolean sensnextlast, Boolean sensendedit, Boolean sensactquit)
{
	Pixel           fg, bg;
	int		i;
	Arg		wargs[2];

	if (menu->pushbutton) {
		/*--- pb sensitivity -------------------------------*/
		for (i=0; i<menu->anz; i++) {
			XtSetSensitive(menu->pushbutton[i], sensedit);
		}
		/*--- action bar sensitivity -----------------------*/
		if (menu->buttonact)
			XtSetSensitive(menu->buttonact,  sensactquit);
		if (menu->buttonquit)
			XtSetSensitive(menu->buttonquit, sensactquit);
		if (menu->buttonmenu)
			XtSetSensitive(menu->buttonmenu, sensactquit);
		if (menu->buttondel)
			XtSetSensitive(menu->buttondel, sensendedit);
		if (menu->buttonend)
			XtSetSensitive(menu->buttonend, sensendedit);
		if (menu->buttonnext)
			XtSetSensitive(menu->buttonnext, sensnextlast);
		if (menu->buttonlast)
			XtSetSensitive(menu->buttonlast, sensnextlast);
		/*--- DB mode and optional toggle not always present -------*/
		if (menu->toggleinsert)
		{
			XtSetSensitive( menu->toggleinsert, sensedit);
			XtSetSensitive( menu->toggleupdate, sensedit);
			XtSetSensitive( menu->toggledelete, sensedit);
		}
		if (menu->optional)
			XtSetSensitive( menu->optional, sensedit);  
	}

	/*--- field color -----------------*/
	if (feld)
	{
		if (sensedit) {
			/*xUIcolorNormal(feld);*/
			xUIreverseColor(feld);
		} else {
			/*xUIcolorInverse(feld);*/
			xUIreverseColor(feld);
		}
	}
}


