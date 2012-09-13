/*D************************************************************
 * Modul:		GRAPHIC                             gtime.c
 *
 *					Read the time of system and display it 	
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/gtime.c,v 1.2 2008-11-02 19:55:43 mwn Exp $

 Log Information:
 $Log: gtime.c,v $
 Revision 1.2  2008-11-02 19:55:43  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:03:08  ja
 general version

 * Revision 1.4  94/02/18  10:38:33  10:38:33  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.3  93/08/21  00:26:13  00:26:13  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gtime.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";


void xGRtime(
)

{
	extern GRAWIDGETS grawidgets;

	char  *str;
	char  daystring[5], month[10], day[3], h[3], min[3], sec[3], year[5];
	char  buffer[50];
	int   i,j;
	long  tloc;
	Arg   args[2];
	static int iday= -1;
	static int ih  = -1;
	static int imin= -1;
	static int isec= -1;
	XmString		xmStr; 	

	time(&tloc);
	str = ctime(&tloc);

	sscanf(str,
	"%[^ ]%*[ ]%[^ ]%*[ ]%[^ ]%*[ ]%[^:]%*[:]%[^:]%*[:]%[^ ]%*[ ]%[0-9]",
	daystring, month, day, h, min, sec, year);

	if(atoi(day)!=iday) {
		strcpy(buffer, daystring);
 		strcat(buffer, " ");
		strcat(buffer, day);
		strcat(buffer, ". ");
		strcat(buffer, month);
		strcat(buffer, " ");
		strcat(buffer, year);
		xmStr = XmStringCreateLtoR( buffer, XmSTRING_DEFAULT_CHARSET);
		XtSetArg(args[0], XmNlabelString, xmStr ); 
 		XtSetValues(grawidgets.datum, args, 1);
		XmStringFree( xmStr); 
	}
	if(atoi(h)!=ih) {
		strcpy(buffer, h);
		xmStr = XmStringCreateLtoR( buffer, XmSTRING_DEFAULT_CHARSET);
		XtSetArg(args[0], XmNlabelString, xmStr ); 
		XtSetValues(grawidgets.stunde, args, 1);
		XmStringFree( xmStr); 
	}
	if(atoi(min)!=imin) {
		strcpy(buffer, min);
		xmStr = XmStringCreateLtoR( buffer, XmSTRING_DEFAULT_CHARSET);
		XtSetArg(args[0], XmNlabelString, xmStr ); 
		XtSetValues(grawidgets.minute, args, 1);
		XmStringFree( xmStr); 
	}
	if(atoi(sec)!=isec) {
		strcpy(buffer, sec);
		xmStr = XmStringCreateLtoR( buffer, XmSTRING_DEFAULT_CHARSET);
		XtSetArg(args[0], XmNlabelString, xmStr ); 
		XtSetValues(grawidgets.sekunde, args, 1);
		XmStringFree( xmStr); 
	}

	iday=atoi(day);
	ih  =atoi(h);
	imin=atoi(min);
	isec=atoi(sec);
}
