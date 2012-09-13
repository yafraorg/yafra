/*
 * psaudio.h  - audio definitions for audio library
 *   Sep. 6 1991
 *   Spyk Pater HP
 */

#define USER_FORMAT_BASE    0x1000
#define USER_FORMAT_spl     USER_FORMAT_BASE + 1
/* STEP 1. ADD USER-DEFINED FORMAT CODES HERE */

/* prototypes */

/* play a sound [file, host, stereoflag, loop] */
int PSAUDIOplay(char *, char *, int, int);

/* record a sound [] */
int PSAUDIOrecord(char *, char *, int, int);

/* internal function prototypes - don't use them in your progi !!! */
/* it's only here, cause I don't want to include more files ! */
int HPaudio_play(char *, char *, int, int);
int LINUXaudio_play(char *, char *, int, int);
int WINaudio_play(char *, char *, int, int);


#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
/* #include <X11/Xatom.h> */
/* #include <X11/Shell.h> */
/* #include <X11/Xutil.h> */
/* #include <X11/StringDefs.h> */


/* Message codes */
#define MOK            0 /* Alles OK - keine Meldung ausgeben */
#define MOPEN          1 /* Dateioeffnungsfehler */
#define MREAD          2 /* Lese Fehler */
#define MWRITE         3 /* Schreib Fehler */
#define MALLOC         4 /* Allocationsfehler - zu wenig Speicher frei */
#define MOUTOFSCR      5 /* Bild liegt ausserhalb der TRICAD Anzeigeflaeche */
#define MNOIMGNAME     6 /* Kein Bildname vorhanden */
#define MNOMOREIMG     7 /* Kann kein Bild mehr oeffnen */
#define MWRONGIMG      8 /* Falsches Pixelbild Format */
#define MSHOWIMG       9 /* Zeige Bild an */
#define MCOLORALLOC   10 /* color allocation error */
#define MALLG       9999 /* Allgemeiner Fehler */

/* diverse defines */
#define BITMAP  1            /* Bildtyp Definition Bitmap        */
#define ZPIXMAP 2            /*                    Pixmap farbig */
#define FILENAMELENGTH 80    /* LÌnge eines Filenames mit Pfad   */

/* Bildtyp */
#define UNKNOWNIMG 0
#define PBMASCII   1
#define PGMASCII   2
#define PPMASCII   3
#define PBM        4
#define PGM        5
#define PPM        6
#define TRI        9


/* Anzeige Struktur fuer Images */
typedef struct ShowImg
{
	XImage *XImg;                /* XImage Bild                   */
	GC      ImgGC;               /* Graphical Context vom Bild    */
	unsigned int Width;          /* Breite der Raster Daten       */
	unsigned int Height;         /* HÎhe der Raster Daten         */
	unsigned int x;
	unsigned int y;              /* Koordinaten im Original Bild  */
	unsigned int w;
	unsigned int h;
} SHOWIMG;

/* RasterImage Objekt */
typedef struct RasterImage
{
	char Name[FILENAMELENGTH];   /* Name des Bildes               */
	unsigned short int Type;     /* 1: BITMAP  2: ZPIXMAP         */
	unsigned char *Data;         /* Raster Daten im XImage Format */
	unsigned int Width;          /* Original Breite               */
	unsigned int Height;         /* Original HÎhe                 */
	unsigned long int Mstb;      /* Masstab des Bildes            */
	unsigned short int Einheit;  /* Einheit des Plans (m, cm, mm) */
	unsigned int dpi;            /* Punkte pro Inch des Plans     */
	long int NullVerX;           /* Nullpunktverschiebung in X    */
	long int NullVerY;           /* Nullpunktverschiebung in Y    */
	unsigned char saveflag;      /* Ist das Bild schon gesaved    */
	unsigned char mutflag;       /* Wurde Bild veraendert         */
	SHOWIMG Show;                /* Bilddaten fuer aktuelle Anz.  */
	Widget WImg;                 /* Widget to draw image on       */
	Colormap ImageMap;           /* Colormap for picture          */
	Colormap OriginalMap;        /* original colormap of parent   */
} RASTERIMAGE;

/* Window Koordinatenstruktur */
typedef struct Winkoord
{
	unsigned int x1;
	unsigned int y1;
	unsigned int x2;
	unsigned int y2;
} WINKOORD;

/* prototyps for the API */
int ORread(RASTERIMAGE *);
int ORresize(RASTERIMAGE *, unsigned int, unsigned int);
int PBMLoad(RASTERIMAGE *);
int PPMLoad(RASTERIMAGE *);
int PBMPrint(unsigned char *, int, int, int);