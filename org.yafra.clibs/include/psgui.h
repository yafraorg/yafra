/**************************************************************/
/* Header:    Prototypes fuer das API Utilities               */
/*                                                            */
/* Copyright: Yafra.org     */
/* Autor:     Administrator, Yafra.org                     */
/*                                                            */
/* History:   June 1992 creation                           */
/**************************************************************/

void PSOSFiconCreate(
	Widget,             /* Shellwidget with Icon */
	char *,             /* Bitmapfile            */
	Pixel,              /* Foreground of Icon    */
	Pixel               /* Background of Icon    */
);

Widget PSOSFlabelframCreate(
	Widget,		        /* parent widget                                    */
	char *,		        /* name of widget to be created                     */
	Arg [],	           /* resource argument list                           */
	int,		           /* number of resource arguments                     */
	Widget (*)(),       /* convenience function for working widget creation */
	char *,	           /* name of label widget                             */
	Widget *    		  /* form widget for eventually attachments           */
);

int PSOSFfileEdit(
	char *              /* filename to edit */
);
