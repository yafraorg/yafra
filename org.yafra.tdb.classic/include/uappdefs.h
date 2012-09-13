/*IH***********************************************************
 * File:       GUI Dialog                            uappdefs.h
 *
 * Description:   Contents private resource definitions
 *                for xUI modules
 *                - ApplicationData typedef
 *                - DEFxxx values
 *                - Xt Resources stuctures
 *
 *	Note:				The default resources are used if the application
 *						cannot find the one in standard X11 places.
 *						Partial match is possible if the standard file is
 *						corrupted.
 *
 * Author:    mw, pi, ja
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


// TODO Achtung mit dem #ifdef !!! Der typedef muss ueberall bekannt sein ! mw 28.12.92 17.20

/**************************************************************/
/* MARCO POLO private resources/appl-defaults                 */
/**************************************************************/
typedef struct {
	char     *bitmapcommitforeground;
	char     *bitmapcommitbackground;
	char     *bitmapcommitforegroundcolor;
	char     *bitmapcommitbackgroundcolor;
	int      scroll_maxlines;
	int      scroll_maxbreite;
	long     updateBookingTime;
	long     maxdataout;
	long     maxdatain;
	long     maxtablist;
	char     *softkeytranslations;
	char     *labelfile;
	char     *errorfile;
	char     *noerrorfilemsg;
	char     *printfilename;
	char     *printcommand;
	char     *iconbitmapmain;           /* Icon Bitmap f�r Mainprogramm */
	char     *iconbitmapgraphik;        /* Icon Bitmap f�r Grafik       */
   char     *gridcolor;
	int      gridwidth;
	int      gridlinestyle;
	int      cursorlinestyle;
	int      cursorlinewidth;
	int      breite;
	int      hoehe;
	int      optionPixmapWidth;
	int      optionPixmapHeight;
	int      optionProz;
	Pixel    optionPixmapforeground;
	Pixel    optionPixmapbackground;
	char     *fontListe;
	char     *colorListe;
	char     *linewidthListe;
	char     *patternListe;
	char     *linestyleListe;
	char     *snapListe;
	Pixel    ColReq;                  /* Farbe der Menubuttons obligat.  */
	Pixel    ColKey;                  /* Farbe der Suchbuttons auf Menu  */
	Pixel    ColNextMenu;             /* Farbe des Menubuttons next Menu */
	Pixel    ColCommit;               /* Frabe des Commitbuttons         */
	Pixel    ColQuit;                 /* Farbe des Quitbuttons           */
	Pixel    ColHelp;                 /* Farbe des Helpbuttons           */
	Pixel    ColInfo;                 /* Farbe des Infobuttons           */
	Pixel    ColGra;                  /* Farbe der Grafikbuttons         */
	Pixel    ColBoard;                /* Farbe der Matrix board          */
	char     *audioWelcome;           /* whelcome at application start   */
	char     *audioQuit;              /* when leaving application        */
	char     *audioToggle;            /* when switching audio on         */
	char     *audioMessage;           /* when attention is requested     */
	char     *audioError;             /* when error occurs               */
	char		*mpurlprefix;            /* default URL prefix for Helppages */
} ApplicationData, *ApplicationDataPtr;


typedef struct {
	char				*colorListe;
} DatabaseData, *DatabaseDataPtr;


#ifdef  XUIMAIN

/*-- Defaultwerte */
#ifdef ps_unix
#define DEFbitmapcommitforeground      "/mapo/curscomm.bm"
#define DEFbitmapcommitbackground      "/mapo/cursback.bm"
#define DEFlabelfile                   "/mapo/labels_d"
#define DEFerrorfile                   "/mapo/errors"
#define DEFprintfilename               "/tmp/printpos"
#define DEFprintcommand                "lp"
#define DEFiconbitmapmain              "/mapo/holliday.bm"
#define DEFiconbitmapgraphik           "/mapo/holliday.bm"
#define DEFaudioWelcome                "/mapo/welcome.wav"
#define DEFaudioQuit                   "/mapo/quit.wav"
#define DEFaudioToggle                 "/mapo/toggle.wav"
#define DEFaudioMessage                "/mapo/message.wav"
#define DEFaudioError                  "/mapo/error.wav"
#else
#define DEFbitmapcommitforeground      "c:\\mapo\\curscomm.bm"
#define DEFbitmapcommitbackground      "c:\\mapo\\cursback.bm"
#define DEFlabelfile                   "c:\\mapo\\labels_d"
#define DEFerrorfile                   "c:\\mapo\\errors"
#define DEFprintfilename               "c:\\tmp\\printpos"
#define DEFprintcommand                "type > c:\\tmp\\xxx"
#define DEFiconbitmapmain              "c:\\mapo\\holliday.bm"
#define DEFiconbitmapgraphik           "c:\\mapo\\holliday.bm"
#define DEFaudioWelcome                "c:\\mapo\\welcome.wav"
#define DEFaudioQuit                   "c:\\mapo\\quit.wav"
#define DEFaudioToggle                 "c:\\mapo\\toggle.wav"
#define DEFaudioMessage                "c:\\mapo\\message.wav"
#define DEFaudioError                  "c:\\mapo\\error.wav"
#endif

#define DEFbitmapcommitforegroundcolor "red"
#define DEFbitmapcommitbackgroundcolor "white"
#define DEFscroll_maxlines             "15"
#define DEFscroll_maxbreite            "40"
#define DEFupdateBookingTime           "600"
#define DEFmaxdataout                  "10000"
#define DEFmaxdatain                   "10000"
#define DEFmaxtablist                  "10000"
#define DEFsoftkeytranslations         "#override\n\
					Shift<Key>osfHelp:    softkey()\n\
					Shift<Key>F2:         softkey()\n\
					Shift<Key>F3:         softkey()\n\
					Shift<Key>osfMenu:    softkey()\n\
					Shift<Key>F5:         softkey()\n\
					Shift<Key>F6:         softkey()\n\
					Shift<Key>F7:         softkey()\n\
					Shift<Key>F8:         softkey()\n\
					<Key>osfHelp:         softkey()\n\
					<Key>F2:              softkey()\n\
					Shift<Key>Return:     softkey()\n\
					<Key>F3:              softkey()\n\
					<Key>osfMenu:         softkey()\n\
					<Key>F5:              softkey()\n\
					<Key>F6:              softkey()\n\
					<Key>F7:              softkey()\n\
					<Key>F8:              softkey()"
#define DEFnoerrorfilemsg              "There is no file with error messages!"
#define DEFgridcolor                   "black"
#define DEFgridwidth                   "1"
#define DEFgridlinestyle               "0"
#define DEFcursorlinestyle             "0"
#define DEFcursorlinewidth             "1"
#define DEFbreite                      "1189"
#define DEFhoehe                       "841"
#define DEFoptionPixmapWidth           "60"
#define DEFoptionPixmapHeight          "42"
#define DEFoptionProz                  "15"
#define DEFoptionPixmapforeground      "white"
#define DEFoptionPixmapbackground      "black"
#define DEFpatternListe                "foreground background 25_foreground 50_foreground 75_foreground slant_right slant_left horizontal vertical"
#define DEFfontListe                   "fixed timR14 timR18 timR24 ncenR18 courBO10 courBO12 courBO14 courBO18 courBO24 helvBO14 helvBO18 helvBO24"
#define DEFcolorListe                  "red green blue yellow magenta black"
#define DEFlinewidthListe              "0.5mm 1.0mm 1.5mm 2.0mm"
#define DEFsnapListe                   "0 1 2"
#define DEFlinestyleListe              "0 1 2"
#define DEFColReq                      0
#define DEFColKey                      "RoyalBlue3"
#define DEFColNextMenu                 "gray40"
#define DEFColCommit                   0
#define DEFColQuit                     0
#define DEFColHelp                     0
#define DEFColInfo                     "pink"
#define DEFColGra                      "DarkKhaki"
#define DEFColBoard                    "LightCoral"
#define DEFWWWURL                      "https://www.yafra.org/marcopolo/mptohelp/"


/*R---------- resource (X11/app-defaults  or  xUIinclude) --------------*/
static XtResource resources[] = {
	{"bitmapcommitforeground", MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, bitmapcommitforeground), XmRString,
	 DEFbitmapcommitforeground},
	{"bitmapcommitbackground", MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, bitmapcommitbackground), XmRString,
	 DEFbitmapcommitbackground},
	{"bitmapcommitforegroundcolor", MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, bitmapcommitforegroundcolor), XmRString,
	 DEFbitmapcommitforegroundcolor},
	{"bitmapcommitbackgroundcolor", MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, bitmapcommitbackgroundcolor), XmRString,
	 DEFbitmapcommitbackgroundcolor},
	{"scroll_maxlines", MAINCLASS, XmRInt, sizeof(int),
	 XtOffset(ApplicationDataPtr, scroll_maxlines), XmRString,
	 DEFscroll_maxlines},
	{"scroll_maxbreite", MAINCLASS, XmRInt, sizeof(int),
	 XtOffset(ApplicationDataPtr, scroll_maxbreite), XmRString,
	 DEFscroll_maxbreite},
	{"updateBookingTime", MAINCLASS, XmRInt, sizeof(int),
	 XtOffset(ApplicationDataPtr, updateBookingTime), XmRString,
	 DEFupdateBookingTime},
	{"maxdataout", MAINCLASS, XmRInt, sizeof(int),
	 XtOffset(ApplicationDataPtr, maxdataout), XmRString,
	 DEFmaxdataout},
	{"maxdatain", MAINCLASS, XmRInt, sizeof(int),
	 XtOffset(ApplicationDataPtr, maxdatain), XmRString,
	 DEFmaxdatain},
	{"maxtablist", MAINCLASS, XmRInt, sizeof(int),
	 XtOffset(ApplicationDataPtr, maxtablist), XmRString,
	 DEFmaxtablist},
	{"softkeytranslations", MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, softkeytranslations), XmRString,
	 DEFsoftkeytranslations},
	{"labelfile", MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, labelfile), XmRString,
	 DEFlabelfile},
	{"errorfile", MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, errorfile), XmRString,
	 DEFerrorfile},
	{"printfilename", MAINCLASS, XmRString, sizeof(String),
		 XtOffset(ApplicationDataPtr, printfilename), XmRString,
		 DEFprintfilename},
	{"printcommand", MAINCLASS, XmRString, sizeof(String),
		 XtOffset(ApplicationDataPtr, printcommand), XmRString,
		 DEFprintcommand},
	{"noerrorfilemsg", MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, noerrorfilemsg), XmRString,
	 DEFnoerrorfilemsg},
	{"iconbitmapmain", MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, iconbitmapmain), XmRString,
	 DEFiconbitmapmain},
	{"iconbitmapgraphik", MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, iconbitmapgraphik), XmRString,
	 DEFiconbitmapgraphik},
	{"gridcolor", MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, gridcolor), XmRString,
	 DEFgridcolor},
	{"gridwidth", MAINCLASS, XmRInt, sizeof(int),
	 XtOffset(ApplicationDataPtr, gridwidth), XmRString,
	 DEFgridwidth},
	{"gridlinestyle", MAINCLASS, XmRInt, sizeof(int),
	 XtOffset(ApplicationDataPtr, gridlinestyle), XmRString,
	 DEFgridlinestyle},
	{"cursorlinestyle", MAINCLASS, XmRInt, sizeof(int),
	 XtOffset(ApplicationDataPtr, cursorlinestyle), XmRString,
	 DEFcursorlinestyle},
	{"cursorlinewidth", MAINCLASS, XmRInt, sizeof(int),
	 XtOffset(ApplicationDataPtr, cursorlinewidth), XmRString,
	 DEFcursorlinewidth},
	{"breite", MAINCLASS, XmRInt, sizeof(int),
	 XtOffset(ApplicationDataPtr, breite), XmRString,
	 DEFbreite},
	{"hoehe", MAINCLASS, XmRInt, sizeof(int),
	 XtOffset(ApplicationDataPtr, hoehe), XmRString,
	 DEFhoehe},
	{"optionPixmapWidth", MAINCLASS, XmRInt, sizeof(int),
	 XtOffset(ApplicationDataPtr, optionPixmapWidth), XmRString,
	 DEFoptionPixmapWidth},
	{"optionPixmapHeight", MAINCLASS, XmRInt, sizeof(int),
	 XtOffset(ApplicationDataPtr, optionPixmapHeight), XmRString,
	 DEFoptionPixmapHeight},
	{"optionProz", MAINCLASS, XmRInt, sizeof(int),
	 XtOffset(ApplicationDataPtr, optionProz), XmRString,
	 DEFoptionProz},
	{"optionPixmapforeground", MAINCLASS, XmRPixel, sizeof(Pixel),
	 XtOffset(ApplicationDataPtr, optionPixmapforeground), XmRString,
	 DEFoptionPixmapforeground},
	{"optionPixmapbackground", MAINCLASS, XmRPixel, sizeof(Pixel),
	 XtOffset(ApplicationDataPtr, optionPixmapbackground), XmRString,
	 DEFoptionPixmapbackground},
	{"fontListe", MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, fontListe), XmRString,
	 DEFfontListe},
	{"colorListe", MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, colorListe), XmRString,
	 DEFcolorListe},
	{"linewidthListe", MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, linewidthListe), XmRString,
	 DEFlinewidthListe},
	{"patternListe", MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, patternListe), XmRString,
	 DEFpatternListe},
	{"linestyleListe", MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, linestyleListe), XmRString,
	 DEFlinestyleListe},
	{"snapListe", MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, snapListe), XmRString,
	 DEFsnapListe},
	{"ColReq", MAINCLASS, XmRPixel, sizeof(Pixel),
	 XtOffset(ApplicationDataPtr, ColReq), XmRString,
	 DEFColReq},
	{"ColKey", MAINCLASS, XmRPixel, sizeof(Pixel),
	 XtOffset(ApplicationDataPtr, ColKey), XmRString,
	 DEFColKey},
	{"ColNextMenu", MAINCLASS, XmRPixel, sizeof(Pixel),
	 XtOffset(ApplicationDataPtr, ColNextMenu), XmRString,
	 DEFColNextMenu},
	{"ColCommit", MAINCLASS, XmRPixel, sizeof(Pixel),
	 XtOffset(ApplicationDataPtr, ColCommit), XmRString,
	 DEFColCommit},
	{"ColQuit", MAINCLASS, XmRPixel, sizeof(Pixel),
	 XtOffset(ApplicationDataPtr, ColQuit), XmRString,
	 DEFColQuit},
	{"ColHelp", MAINCLASS, XmRPixel, sizeof(Pixel),
	 XtOffset(ApplicationDataPtr, ColHelp), XmRString,
	 DEFColHelp},
	{"ColInfo", MAINCLASS, XmRPixel, sizeof(Pixel),
	 XtOffset(ApplicationDataPtr, ColInfo), XmRString,
	 DEFColInfo},
	{"ColGra", MAINCLASS, XmRPixel, sizeof(Pixel),
	 XtOffset(ApplicationDataPtr, ColGra), XmRString,
	 DEFColGra},
	{"ColBoard", MAINCLASS, XmRPixel, sizeof(Pixel),
	 XtOffset(ApplicationDataPtr, ColBoard), XmRString,
	 DEFColBoard},
	{"audioWelcome", MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, audioWelcome), XmRString,
	 DEFaudioWelcome},
	{"audioQuit",     MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, audioQuit), XmRString,
	 DEFaudioQuit},
	{"audioToggle",   MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, audioToggle), XmRString,
	 DEFaudioToggle},
	{"audioMessage",  MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, audioMessage), XmRString,
	 DEFaudioMessage},
	{"audioError",    MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, audioError), XmRString,
	 DEFaudioError},
	{"mpurlprefix", MAINCLASS, XmRString, sizeof(String),
	 XtOffset(ApplicationDataPtr, mpurlprefix), XmRString,
	 DEFWWWURL}
   };

#endif

