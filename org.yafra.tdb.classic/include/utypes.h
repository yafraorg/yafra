/*IH***********************************************************
 * Header:        User Interface
 * Description:   Structure definitions for UI
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
*/
/* RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/utypes.h,v 1.2 2008-11-02 19:55:33 mwn Exp $
*/


/*-- Farbe pro Objekt */
typedef struct
{
	Pixel      bg, fg, top, bottom, select;
} OBJCOLORS;

/* MENULIST */
typedef struct _MENULIST
{
   XtCallbackProc        (*func)();
   XtPointer              data;
   struct _MENULIST      *submenu;
   Widget                *button;
   int                    anz_subitems;
   char                  *submenutitle;
   char                  *name;
   char                  *titel;
   char                   mnemonic;
   Boolean                status;
   Boolean                menu;
} MENULIST;

typedef struct _MENUDIM
{
   Widget				Wgscroll;				/* scrolled window              */
   Widget				Wgwork;					/* work widget in scrolled win  */
   Dimension			obligHeight;			/* when oblig field only        */
   Dimension			obligWidth;
   Dimension			optionalHeight;		/* when oblig + optional        */
   Dimension			optionalWidth;
} MENUDIM;


typedef struct {
   int       typ;                /* Window f�r welches Objekt */
   XtCallbackProc (*action)();  /* Aktionsfunktion */
   XtCallbackProc (*help)();    /* Helpfunktion */
   int       anz;               /* Anzahl Pushbuttons */
   int      *buttontype;        /* Typ jedes Pushbuttons */
   int      *suchfields;        /* Typ der Update-Suchfelder */
   int      *inpfields;         /* Typ der Input-Felder */
   int      *anzlines;          /* Anz zu editierende Linien */
   int      *anzcolumns;        /* Anz Kolonnen */
   int      *vonglobal;         /* Zuordnung zu glob. Daten */
   int      *zuobutton;         /* Zuordnung Buutons */
   int       zuogruppe;         /* Zuordnung zu Menugruppe */
   int       zuonumber;         /* Zuordnung int. Darstellung */
   char     *helpfile;          /* Helpfilenamen */
   char     *bez;               /* Name des Menues */         /* no more used */
   char     *titel;             /* Titel des Menues */
   char    **label;             /* Name des Pushbuttons */
   Widget    button;            /* Menubutton des Hauptmenues */
   Widget    popup;             /* Popup des Menues */
   Widget    buttonhelp;        /* Helpbutton des Menues */
   Widget    buttonact;         /* Actionbutton des Menues */
   Widget    buttonquit;        /* Quitbutton des Menues */
   Widget   *pushbutton;        /* Pushbuttons des Menues */
   Widget   *field;             /* Editor des Menues */
   Widget    toggleinsert;      /* Insert-Toggle */
   Widget    toggleupdate;      /* Update-Toggle */
   Widget    toggledelete;      /* Delete-Toggle */
   Widget    optional;          /* optional fields toggle */
   Widget    buttonmenu;        /* Delete-Menu-Button */
   Widget    buttondel;         /* Delete-Field-Button */
   Widget    buttonnext;        /* Next-Field-Button */
   Widget    buttonlast;        /* Last-Field-Button */
   Widget    buttonend;         /* End-Field-Button */
   Boolean   alreadywrite;   
   Boolean   enter;   
   Boolean   flags;   
   Boolean   openedmenu;   
   Boolean   editfeld;   
} MENU;
