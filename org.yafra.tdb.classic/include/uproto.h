/*IH***********************************************************
 * Header:      User Interface
 * Description: ANSI C prototypes
 *
 * Copyright: yafra.org, Basel, Switzerland
 * Author:    Administrator
 ***************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/uproto.h,v 1.2 2008-11-02 19:55:32 mwn Exp $
*/


/* Main objects */
void main(int, char **);
int  xUImainStop(int);
XtCallbackProc       xUImainClose			(Widget, XtPointer, XtPointer);
XtCallbackProc       xUImainMenuQuit		(Widget, XtPointer, XtPointer);
XtCallbackProc       xUIbeeping				(Widget, XtPointer, XtPointer);
XtActionProc         xUIbeep					(Widget, XEvent*, String*, Cardinal*);
XtCallbackProc			xUIprintText			(Widget, XtPointer, XtPointer);
Boolean					xUIiconpixmap			(Widget, char*);
Pixmap					xUIpixmap				(Display*, char*, unsigned long*, unsigned long*);
Cursor					xUIcursor				(Display*, char*, char*, char*, char*);

/* global profile prototypes */
int MPUIprofile_init(char *, MP_GLOBALPROFIL *);
XtCallbackProc	xUIglobFileSave(Widget, XtPointer, XtPointer);

/* General communication Object */
XtInputCallbackProc xUIinput(XtPointer, int *, XtInputId *);
long xUItalkto(int, char *, long);
void xUItalkingModalityOn(Widget *wid, int nbWidgets);
void xUItalkingModalityOff(int nbWidgets);
void xUIwindows(Window, int*, Window*, int, Boolean, Boolean*);
Widget xUIexitBar(Widget, char *, XtCallbackProc, XtPointer, char *, XtCallbackProc, XtPointer);
XtActionProc xUIsoftkey(Widget, XEvent*, String*, Cardinal*);

/*--- Licence ---------------------------*/
void						xUIlicenceCreatePopup(Widget aktparent );
XtCallbackProc       xUIlicenceDisplay		(Widget, XtPointer, XtPointer);

/*--- Functions -------------------------*/
int						xUIwidgets				(Widget *);
int						xUIpcxpopup				(Widget, char *);
void						xUIoutputnew			(MENU *a);
Widget					xUIframelabel			(Widget, Widget *, char *, char *);

/*---- Global board ----------------------*/
Widget					xUIglobBoardCreate	( Widget mainwindow);

/*---- Banner above global menu ----------*/
Widget					xUIbannerCreate		(Widget mainwindow);
XtCallbackProc			xUIselBanner			(Widget w, XtPointer, XtPointer );
void						xUIbannerDisplay		(char *text);

/*---- Global menu -----------------------*/
Widget 					xUIglobmenuCreate		(Widget);
void						xUIglobmenuSensitive	(Boolean);
void						xUIglobmenuPresence	(Boolean);
char						*xUIglobmember			(int);

/*--- Help/info objects -----------------*/
void                 xUIopenHelp          (char *);
XtCallbackProc       xUIhelp					(Widget, XtPointer, XtPointer);
XtCallbackProc       xUIhelpQuit				(Widget, XtPointer, XtPointer);
XtActionProc         xUIhelppopdown			(Widget, XEvent*, String*, Cardinal*);
XtCallbackProc       xUIinfo					(Widget, XtPointer, XtPointer);
XtActionProc         xUIinfopopdown			(Widget, XEvent*, String*, Cardinal*);
XtActionProc         xUImessagepopdown		(Widget, XEvent*, String*, Cardinal*);
XtCallbackProc       xUIquestion				(Widget, XtPointer, XtPointer);
XtCallbackProc       xUIdestroy				(Widget, XtPointer, XtPointer);
void						xUIfehler				(char, Widget);
void						xUIdeffrage				(char*, char*, char*, XtCallbackProc, XtPointer, Widget);


/*--- Label object ----------------------*/
int						xUIlabelsPointerInit	(void); 
void						xUIlabelsMenuInit		();
void						xUIlabelsFromBank		(char * pBuf, int prog ); 
void						xUIlabelsDefault		(char* labelFileName );
void						xUIlabelsFree			();


/*--- Pulldown objects ------------------*/
void						xUIpulldownSensitive	(Boolean sensitivity );
Widget 					*xUIpulldown			(char*, Widget, MENULIST*, int);


/*--- Menu behaviour object -------------*/
MENU						* xUImenuActive      ();
XtCallbackProc			xUIpopdown				(Widget, XtPointer, XtPointer);
XtCallbackProc			xUImenudown 			(Widget, XtPointer, XtPointer);
XtCallbackProc			xUIcallpopup			(Widget, XtPointer, XtPointer);
XtActionProc			xUIselnewmenu			(Widget, XEvent*, String*, Cardinal*);
XtCallbackProc			xUInewlevel				(Widget, XtPointer, XtPointer);
Widget					xUIpopup					(int);
XtCallbackProc			xUImenuButtonError	(Widget, XtPointer, XtPointer);
XtCallbackProc			xUImenubutton			(Widget, XtPointer, XtPointer);
void						xUImenufeld				(MENU*, Widget, Boolean, Boolean, Boolean, Boolean);
long						xUImenustr				(MENU*);
void						xUIstrmenu				(MENU*, char*);
void						xUIoutmenudown			(MENU	*a);


/*--- Field object ----------------------*/
XtActionProc			xUIfielddel    		(Widget, XEvent*, String*, Cardinal*);
XtCallbackProc			xUIfieldlast			(Widget, XtPointer, XtPointer);
XtCallbackProc			xUIfieldnext			(Widget, XtPointer, XtPointer);
int						xUIfeldnr				(MENU*, Widget);
int						xUIfindhold				(MENU*, int);
XtCallbackProc			xUIfieldDeleteAll		(Widget, XtPointer, XtPointer);


/*--- Editor object ---------------------*/
Widget					xUIeditor      		(char*, Widget, int, int, char*, Position*, short, XtTranslations);
XtCallbackProc			xUIeditpurge   		(Widget, XtPointer, XtPointer);
XtCallbackProc			xUIeditend     		(Widget, XtPointer, XtPointer);
void						xUIeditnext   			(MENU*, int);


/*--- Edit/field objects ----------------*/
XtCallbackProc       xUIselglob				(Widget, XtPointer, XtPointer);
XtCallbackProc       xUIseltowrite			(Widget, XtPointer, XtPointer);
XtCallbackProc       xUIselpopup				(Widget, XtPointer, XtPointer);
XtCallbackProc       xUIselgrafic			(Widget, XtPointer, XtPointer);
XtCallbackProc       xUIshowgrafic			(Widget, XtPointer, XtPointer);
XtCallbackProc       xUIinpgrafic			(Widget, XtPointer, XtPointer);
XtCallbackProc       xUIreadtowrite			(Widget, XtPointer, XtPointer);
XtActionProc         xUIreadwrite			(Widget, XEvent*, String*, Cardinal*);
XtActionProc         xUIwritetoread			(Widget, XEvent*, String*, Cardinal*);


/*--- DB objects ------------------------*/
XtCallbackProc       xUItoggle				(Widget, XtPointer, XtPointer);
XtCallbackProc       xUIcomm					(Widget, XtPointer, XtPointer);
void						xUIactionbar			(MENU*, Widget);


/*--- Selection box/dialog object -------*/
void						xUIlistshell			(int, Widget, char*, char*, char*, Widget*, Widget*);
void						xUItextshell			(Widget , int, char * );
XtActionProc			xUIselectpopdown		(Widget, XEvent*, String*, Cardinal*);
Widget					xUImask					(Widget, char*, int);
void						xUImessagepopup		(unsigned char, char*, Widget);
Widget					xUIdialog				(unsigned char, Widget, char*, char*, XtCallbackProc,
															XtPointer, XtCallbackProc, XtPointer);
XtCallbackProc			xUIchooseitem			(Widget, XtPointer, XtPointer);
XtCallbackProc			xUIchoosedown			(Widget, XtPointer, XtPointer);
XtCallbackProc			xUIchoosecancel		(Widget, XtPointer, XtPointer);
void						xUItostrtable			(char*, Widget);
int						xUIlines					(char*, int*, int*);
void						xUIimmediatCall		(char *, Widget);


/*--- Option menu -----------------------*/
XtCallbackProc			xUIoption				(Widget, XtPointer, XtPointer);
XtCallbackProc			xUIoptionPopdown		(Widget, XtPointer, XtPointer);
Widget					xUIoptionTest			(Widget);
void						xUIoptionCreatePopup	(void);
void						xUIoptionSetDefaults	(void);
void						xUIoptionSendAll		(void);	


/*--- Color objects ---------------------*/
void						xUIinitcolors			(Widget);
void						xUIsetwidgetcolor		(Widget, OBJCOLORS *);
void						xUIcolorNormal			(Widget);
void						xUIcolorInverse		(Widget);
void						xUIsetSelectColor		(Widget);
void						xUIsetUnselectColor	(Widget);
void						xUIsetBestForeground	(Widget);
XtCallbackProc			xUIcolorHelpTest		(Widget, XtPointer, XtPointer);


/*--- General functions -----------------*/
void						*xUIalloc				(void*, long*, long, long, long);
int						geradeschnitt			(double, double, double, double, double, double,
                 							 		double *, double *);
void						geradegl					(double, double, double, double, double *, double *, double *);
int						punktkla					(double *, double *, int, double *, double *, double, double,
														double, double);

/* Audio and sound objects */
void xUIaudioPlay(char *);
