/*D*************************************************************************
 * Modul:     GUI - BM dialog                                    binclude.h  
 *            
 *            Includes of all callback functions declarations
 * 
 * 
 * Copyright: yafra.org, Basel, Switzerland
 ***************************************************************************
 */



/*P------------------------ BM GENERAL --------------------------------------*/
/* some common definitions can also be found in MPdef.h */


/*--- BM general definitions -------------*/
#define	_BMBUFFERMAX			2048		/* buffer size for results */
#define	_BMLABELLEN				80			/* len max of scroll buttons labels */


/*--- Menu array subscripts --------------*/
#define	ANZ_BMMENU				3
#define	_BMDLNIX					0
#define	_BMCATIX					1
#define	_BMDLTIX					2


/*--- Scrolled list of items -------------*/
#define	_SCROLL_NBVISIBLE		6		/* nb of visible items in scrollw   */
#define	_SCROLL_SPACE			1		/* spacing btw. buttons in scroll   */
#define	_SCROLL_HEADER			" Description Header .......... "



/*---------------- BMMENUS ------------------------------------*/
typedef struct {
	int			typ;									/*   */
	XtCallbackProc (*action)();					/* Aktions function            */
	XtCallbackProc (*help)();						/* Help function               */
	int			nbitems;								/* number of items             */
	int			olditems;							/* previous number of items    */
   int			*select;								/* selected items              */
	int			*fieldtype;							/* select, sedit or medit...   */
	int			*suchfields;						/* search fields (true/false)  */
	int			*inpfields;							/* input fields (true/false)   */
	int			*lines;								/* nb of lines                 */
	int			*columns;							/* nb of cols                  */
	char			**labels;							/* array of labels             */
	Widget		Wgpopup;								/* popup when created          */
	Widget		Wglink;								/* widget link to parent       */
	Widget		*Wgbuttons;							/* created buttons or toggles  */
	Widget		*Wgfields;							/* created edit fields         */
	Widget		Wgtoggleinsert;					/* db mode insert in DBI       */
	Widget		Wgtogglesearch;					/* db mode search in DBI       */
	Widget		Wgtoggledelete;					/* db mode delete from DBI     */

	Widget		Wgbuttonhelp;						/* action bar widgets          */
	Widget		Wgbuttonmenu;
	Widget		Wgbuttonact;
	Widget		Wgbuttonquit;
	
	Boolean		alreadywrite; 						/* Edition flags               */
	Boolean		enter; 
	Boolean		flags; 
	Boolean		openedmenu; 
	Boolean		editfeld; 
} BOOKMENU ;


/*--- Menu selection AREA ----------------*/
typedef struct {
	int			nbitems;								/* number of items             */
	int			olditems;							/* previous or max nb of items */
   int			*select;								/* selected items              */
	char			**labels;							/* array of labels             */
	Widget		Wglink;								/* widget link to parent items */
	Widget		Wglink2;								/* second link if necessary    */
	Widget		*Wgbuttons;							/* created buttons or toggles  */
} MENUAREA ;


/*--- Scrolled window AREA ----------------*/
typedef struct {
	int			nbitems;								/* number of items             */
	int			olditems;							/* previous or max nb of items */
   int			*select;								/* selected items              */
	char			*headlabel;							/* array of labels             */
	char			**catid;								/* key string for DBI answer   */
	char			**labels;							/* array of labels             */
	char			**colors;							/* array of color strings      */
	Widget		Wgarea;								/* area manager                */
	Widget		Wghead;								/* header of scrolled window   */
	Widget		Wgscroll;							/* scrolled window widget      */
	Widget		Wglink;								/* widget link to parent items */
	Widget		*Wgbuttons;							/* created buttons or toggles  */
} SCROLLAREA ;


/*--- AREA CALLBACK ----------------*/
typedef struct {
	int			index;								/* selected item of area       */
	SCROLLAREA	*pArea;								/* pointer to area             */
} AREACALLBACK ;


/*--------------------- MAIN menu ------------------------------------------*/
/* Has GUI normal structure ! */


/*--------------------- DLN menu -------------------------------------------*/
#define	_DLN_AREAS					6		/* number of framed areas         */
#define	_DLN_NBBUTTONS				6		/* number of menu pushbuttons       */
#define	_DLN_ITEMS					20		/* limit for widgets in areas     */
#define	_DLN_COLUMNSIZE			5		/* number of items in one column  */

#define	_DLN_SEX						1		/* Selectors from DBI for areas   */
#define	_DLN_BUTTONS				2
#define	_DLN_REDUC1					3
#define	_DLN_TYPE					4
#define	_DLN_TOGGLES				5



/*--------------------- CAT menu -------------------------------------------*/
#define	_CAT_AREAS					4		/* number of framed areas           */
#define	_CAT_NBBUTTONS				9		/* number of menu pushbuttons       */
#define	_CAT_NBRECALL				6		/* number of recall labels          */
#define	_CAT_COLUMNSIZE			7		/* wraparound packing after columns */

/*-- Selectors for DBI data parsing ---*/
#define	_CAT_RECALLAB				1		/* recall current booking params    */
#define	_CAT_SCROLL					2		/* scrolled Categories              */
#define	_CAT_FIELDS					3		/* reservation status text          */



/*--------------------- DLT menu -------------------------------------------*/
#define	_DLT_AREAS					2		/* number of framed areas           */
#define	_DLT_NBBUTTONS				1		/* number of menu pushbuttons       */
#define	_DLT_FIELD_DLT				0		/* index first field                */

/*-- Selectors for DBI data parsing ---*/
#define	_DLT_RECALLAB				1		/* recall current booking params    */
#define	_DLT_BESTOF					2		/* list of DLTs                     */

#define	_DLT_COLOR					"grey"		/* color of buttons           */




/*E------------------------ PROTOTYPES -------------------------------------*/
void			xBMmenuActiveAdd( int menuIndex);
void			xBMmenuActiveRemove();
BOOKMENU *	xBMmenuActive();
void			xBMmenufeld( BOOKMENU *b, Widget feld, Boolean sensedit, Boolean sensnextlast,
					 									 Boolean sensendedit, Boolean sensactquit);

/*---- Menu button -------*/
XtCallbackProc xBMfieldnext( Widget w, XtPointer closure, XtPointer wdata);
int				xBMfeldnr(BOOKMENU *b, Widget field);
long				xBMmenustr( BOOKMENU *b);


void		xBMmenuDestroy( BOOKMENU *b );
void		xBMinitTranslations();
Widget	xBMactionbar( Widget parent, BOOKMENU *b);
void		xBMcreatetoggle( Widget parent, BOOKMENU *dlnMenu);


/*---- Class Butfield ----*/
void		xBMbutfieldCreate(Widget parent, BOOKMENU *b, int nbItems, int labelIx );
void		xBMbutfieldClear( BOOKMENU *b );
long		xBMbutfieldGetText( BOOKMENU *b, char *buffer);
void		xBMbutfieldDestroy(BOOKMENU *b );

/*---- Class Radio -------*/
int		xBMradioSize( int nbItems, MENUAREA *anArea, Boolean oneFlag);
void		xBMradioCreate( Widget parent, MENUAREA *anArea, int nr, Boolean oneFlag);
void		xBMradioUpdate( MENUAREA *anArea, int nr,
							XtCallbackProc (*cbFunc)(Widget, XtPointer, XtPointer) );
void		xBMradioReset( MENUAREA *anArea );
void		xBMradioDestroy(MENUAREA *anArea );

/*---- Class n-of-many ------*/
int		xBMnofmanySize( int nbItems, MENUAREA *anArea);
void		xBMnofmanyCreate( Widget parent, MENUAREA *anArea, int nr);
void		xBMnofmanyUpdate( MENUAREA *anArea, int nr,
							XtCallbackProc (*cbFunc)(Widget, XtPointer, XtPointer) );
void		xBMnofmanyReset( MENUAREA *anArea );
void		xBMnofmanyDestroy(MENUAREA *anArea );


/*---- DLN ------*/
void		xBMdlnPopup( Widget parent);
Widget	xBMdlnPopupCreate( Widget parent);
void		xBMdlnPopupUpdate();
void		xBMdlnPopupDestroy();
void		xBMdlnPopdown();

void		xBMdlnSelectionReset();		

int		xBMdlnSexSize( int nbItems, MENUAREA *anArea);
void		xBMdlnSexCreate( Widget parent, MENUAREA *anArea);
void		xBMdlnSexUpdate( MENUAREA *anArea );
void		xBMdlnSexReset (MENUAREA *anArea);
void		xBMdlnSexDestroy( MENUAREA *anArea );

int		xBMdlnButtonsSize( int nbItems, BOOKMENU *anArea);
void		xBMdlnButtonsCreate( Widget parent, BOOKMENU *anArea);
void		xBMdlnButtonsUpdate( BOOKMENU *anArea);
void		xBMdlnButtonsDestroy( BOOKMENU *b );

int		xBMdlnReducSize( int nbItems, MENUAREA *anArea);
void		xBMdlnReducCreate( Widget parent, MENUAREA *anArea );
void		xBMdlnReduc1Update( MENUAREA *anArea);
void		xBMdlnReduc2Update( MENUAREA *anArea);
void		xBMdlnReduc1Reset( MENUAREA *anArea);
void		xBMdlnReduc1Destroy( MENUAREA *anArea);
void		xBMdlnReduc2Destroy( MENUAREA *anArea);

int		xBMdlnTypeSize( int nbItems, MENUAREA *anArea );
void		xBMdlnTypeCreate( Widget parent, MENUAREA *anArea);
void		xBMdlnTypeUpdate( MENUAREA *anArea);
void		xBMdlnTypeReset (MENUAREA *anArea);
void		xBMdlnTypeDestroy( MENUAREA *anArea);

void		xBMdlnKeeptextReset();


/*---- CAT ------*/
void		xBMcatPopup( Widget parent);
Widget	xBMcatPopupCreate( Widget parent);
void		xBMcatPopupUpdate();
void		xBMcatPopdown();
void		xBMcatPopupDestroy();
int		xBMcatGetResults();

void		xBMcatSelectionReset();

int		xBMcatRecallSize( int nb, MENUAREA *anArea );
void		xBMcatRecallCreate( Widget parent, MENUAREA *anArea );
void		xBMcatRecallUpdate( MENUAREA *anArea);
void		xBMcatRecallDestroy( MENUAREA *anArea );

int		xBMscrollerSize( int nb, SCROLLAREA *anArea );
void		xBMscrollerCreate( Widget parent, SCROLLAREA *anArea, Boolean headerFlag );
void		xBMscrollerUpdate( SCROLLAREA *anArea);
void		xBMscrollerDestroy( SCROLLAREA *anArea );


/*---- DLT ------*/
void		xBMdltPopup( Widget parent);
Widget	xBMdltPopupCreate( Widget parent);
void		xBMdltPopupUpdate();
void		xBMdltPopdown();
void		xBMdltPopupDestroy();
void		xBMdltClearSlection();
int		xBMdltGetResults(); 

/*---- Board Matrix  ------*/
void xBMboardPopup(	unsigned char mode, char *inputstring, char *title );


/*E------------------------ CALLBACKS ---------------------------------------*/
XtCallbackProc xBMmenudown(Widget w, XtPointer closure, XtPointer data);
XtCallbackProc xBMmenubutton(Widget w, XtPointer closure, XtPointer wdata);
XtCallbackProc xBMmenuAction(Widget w, XtPointer closure, XtPointer data);
XtCallbackProc xBMmenuCommit( Widget w, XtPointer closure, XtPointer data);
XtCallbackProc xBMpopdown(Widget w, XtPointer b, XtPointer wdata);

XtCallbackProc xBMreadtowrite(Widget w, XtPointer closure, XtPointer wdata);
XtCallbackProc xBMselpopup(Widget w, XtPointer closure, XtPointer data);
XtCallbackProc xBMseltowrite(Widget w, XtPointer closure, XtPointer data);
XtCallbackProc xBMfieldDeleteAll(Widget w, XtPointer b, XtPointer wdata);
XtCallbackProc xBMnewlevel(Widget w, XtPointer closure, XtPointer data);
XtCallbackProc xBMselmenu( Widget w, XtPointer closure, XtPointer data);
XtCallbackProc xBMselgrafic( Widget w, XtPointer closure, XtPointer data);
XtCallbackProc xBMscrollerSelect(Widget w, XtPointer toggleIndex, XtPointer wdata);

XtCallbackProc xBMdlnReduc1Select(Widget w, XtPointer toggleIndex, XtPointer wdata);
XtCallbackProc xBMdlnReduc2Select(Widget w, XtPointer toggleIndex, XtPointer wdata);
XtCallbackProc xBMdlnTest(Widget w, XtPointer closure, XtPointer wdata );

XtCallbackProc xBMcatExtraSelect(Widget w, XtPointer toggleIndex, XtPointer wdata);
XtCallbackProc xBMcatTest(Widget w, XtPointer closure, XtPointer wdata );

XtCallbackProc xBMdltTest(Widget w, XtPointer closure, XtPointer wdata );
XtCallbackProc xBMdltok(Widget w, XtPointer closure, XtPointer wdata );
XtCallbackProc xBMdltCancel( Widget w, XtPointer closure, XtPointer data);


/*A------------------------ ACTIONS -----------------------------------------*/
XtActionProc xBMbeep(Widget w, XEvent* event, String* s, Cardinal* n);
XtActionProc xBMreadwrite(Widget w, XEvent* event, String* s, Cardinal* m);
XtActionProc xBMwritetoread(Widget w, XEvent* event, String* s, Cardinal* m);
XtActionProc xBMselectpopdown(Widget w, XEvent* event, String* s, Cardinal* m);
XtActionProc xBMdelfield(Widget w, XEvent* event, String* s, Cardinal* n);

