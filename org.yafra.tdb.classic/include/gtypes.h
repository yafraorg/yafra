/*IH***********************************************************
 * File:        GRAPHIC
 *
 * Description:   Structure definitions for graphic objects
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
*/

/* RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/gtypes.h,v 1.2 2008-11-02 19:55:32 mwn Exp $
*/

typedef struct {
	Widget shell;          /* Graphishell                                */
	Widget main;           /* Vaterwidget: shell                          */
	Widget menubar;        /* Vaterwidget: main                           */
	Widget form;           /* Vaterwidget: main                           */
	Widget **menubutton;   /* Vaterwidget: pulldown von menubar           */
	Widget status;         /* Vaterwidget: form                           */
	Widget optionmenu;     /* Vaterwidget: form                           */
	Widget aktfont;        /* Vaterwidget: optionmenu                     */
	Widget aktcolor;       /* Vaterwidget: optionmenu                     */
	Widget aktlinewidth;   /* Vaterwidget: optionmenu                     */
	Widget aktpattern;     /* Vaterwidget: optionmenu                     */
	Widget aktlinestyle;   /* Vaterwidget: optionmenu                     */
	Widget aktsnap;        /* Vaterwidget: optionmenu                     */
	Widget *optfont;       /* Vaterwidget: pulldown von optionmenu        */
	Widget *optcolor;      /* Vaterwidget: pulldown von optionmenu        */
	Widget *optlinewidth;  /* Vaterwidget: pulldown von optionmenu        */
	Widget *optpattern;    /* Vaterwidget: pulldown von optionmenu        */
	Widget *optlinestyle;  /* Vaterwidget: pulldown von optionmenu        */
	Widget *optsnap;       /* Vaterwidget: pulldown von optionmenu        */
	Widget textfeld;       /* Vaterwidget: form                           */
	Widget selectregion;   /* Vaterwidget: form                           */
	Widget listregion;     /* Vaterwidget: form                           */
	Widget scrolledgraphik;/* Vaterwidget: form                           */
	Widget koord;          /* Vaterwidget: status                         */
	Widget dateilabel;     /* Vaterwidget: status                         */
	Widget dateiname;      /* Vaterwidget: status                         */
	Widget aktregion;      /* Vaterwidget: status                         */
	Widget textfeldlabel;  /* Vaterwidget: textfeld                       */
	Widget textfeldquit;   /* Vaterwidget: textfeld                       */
	Widget antwort;        /* Vaterwidget: textfeld                       */
	Widget frage;          /* Vaterwidget: textfeld                       */
	Widget graphik;        /* Vaterwidget: scrolledgraphik                */
	Widget clock;          /* Vaterwidget: listregion                     */
	Widget datum;          /* Vaterwidget: clock                          */
	Widget stunde;         /* Vaterwidget: clock                          */
	Widget minute;         /* Vaterwidget: clock                          */
	Widget sekunde;        /* Vaterwidget: clock                          */
	Widget listlabel;      /* Vaterwidget: listregion                     */
	Widget booking;        /* Vaterwidget: listregion                     */
	Widget go;             /* Vaterwidget: listregion                     */
	Widget selectlabel;    /* Vaterwidget: selectregion                   */
	Widget select;         /* Vaterwidget: selectregion                   */
	Widget filebox;        /* Vaterwidget: shell                          */
	Widget palette;				/*  */
	Widget aktregionlabel;		/*  */
	Widget bookmain;				/*  */
	Widget booking2;				/*  */
	Widget booking3;				/*  */
	Widget booking4;				/*  */
} GRAWIDGETS;

typedef struct {
	Window graphik;
} GRAWINDOWS;

typedef struct {
	int box;
	int tog;
} ACTCALLBACK;

typedef float WCVALUE;

typedef unsigned long PKTNR;

typedef struct {
	XPoint p;
	PKTNR n;
} REGIONPOINT;

typedef struct {
	WCVALUE x;
	WCVALUE y;
} MP_POINT;

typedef struct {
	MP_POINT p;
	PKTNR n;
} REGIONPOINTDISC;

typedef struct {
	int *xpoints;
	REGIONPOINT *regionPoint;
	unsigned char gc1;
	unsigned char gc2;
	unsigned char gc3;
	unsigned was:4;
	unsigned anzRegionPoints:4;
	char *text;
} GRAFOBJ;

typedef struct {
	MP_POINT graVal[MAXGRAVALUES];
	REGIONPOINTDISC regionPoint[MAXREGOBJ];
	unsigned char gc1;
	unsigned char gc2;
	unsigned char gc3;
	unsigned was:4;
	unsigned anzRegionPoints:4;
	char *text;
} GRAFOBJDISC;

typedef struct _REGOBJ{
	char *Regionname;
	unsigned long anzEckpunkte;
	XPoint *Eckpunkte;
	PKTNR  *Eckpunktnum;
	Region region;
	long indVater;
	unsigned char color;
	unsigned char zustand;
	Boolean temp;
} REGOBJ;

typedef struct {
	XPoint	p[2];
	WCVALUE	faktor;
} ZOOM;

typedef struct {
	int           mode;
	int           eingabe;
	int           bookingMode;        /* one only or multiple with list */
	int           aktbox;
	int           akttog;
	int           anzFonts;
	int           anzColors;
	int           anzLinewidth;
	int           anzPattern;
	int           anzLinestyle;
	int           anzSnap;
	XFontStruct   **fonts;
	Cursor        wait;
	Cursor        work;
	GC            gc_grid;
	GC            gc_cursor;
	GC            ***GCZ;
	GC            **GCP;
	GC            **GCF;
	GC            *GCR;
	GC            *gcz;
	GC            *gcp;
	GC            *gcf;
	GC            *gcr;
	GRAFOBJ       *tempObj;
	WCVALUE       xfak;
	WCVALUE       yfak;
	WCVALUE       zoomfaktor;
	short         griddist;
	short         Limitx;
	short         Limity;
	short         RadiusPoints;
	char          *antwort;
	char          *fileselected;
	XPoint        cursor_data;
	XPoint        pickbox;
	REGOBJ        *aktregion;
	unsigned char indcolor;
	unsigned char indwidth;
	unsigned char indstyle;
	unsigned char indpattern;
	unsigned char indfont;
	unsigned char indsnap;
	unsigned char Tempfarbe;
	unsigned char Buchungsfarbe[MAXBUCHUNG];
	Boolean       showPoints;
	Boolean       showPickbox;
	Boolean       showGrid;
	XtIntervalId  timer;
	Boolean       openedshell;
	Boolean       openedpalette;
	Boolean       openedbookmain;
} GRAGLOB;

typedef int (*IntSearchProc)(void*, void*); 


typedef struct {
	int           anzColors;
	GC            *GCR;
	GC            *gcr;
	unsigned char indcolor;
	unsigned char Tempfarbe;
	unsigned char Buchungsfarbe[MAXBUCHUNG];
} GRACAT;


