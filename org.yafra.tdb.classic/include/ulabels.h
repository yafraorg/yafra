/************************************************************** 
 * Header:      GUI - dialog                          ulabels.h
 *                                                              
 *            Labels definitions                                    
 *            Gui, Booking mask and Graphic                                                  
 * 
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/



/*???  #define    MAXLABELS     600	*/
/*???  #define    MAINLABEL     39	*/
/*--- Definitions of indexes related with label file --------------*/



/*********************** BOOKING MASK ***********************************/

/*-- Window, global, general... definitions ----------------------*/
#define LABEL_APPLICATION				xuiLabelTable[_GLOBALOBJ][0]
#define LABEL_ICONAPPLICATION			xuiLabelTable[_GLOBALOBJ][1]
#define LABEL_GLOBALVALUES				xuiLabelTable[_GLOBALOBJ][2]  
#define LABEL_GLOBAL						xuiLabelTable[_GLOBALOBJ][3]  
#define LABEL_INFOWINDOW				xuiLabelTable[_GLOBALOBJ][4] 
#define LABEL_HELPWINDOW				xuiLabelTable[_GLOBALOBJ][5] 
#define LABEL_ERRORWINDOW				xuiLabelTable[_GLOBALOBJ][6] 
#define LABEL_SELECTLISTWINDOW		xuiLabelTable[_GLOBALOBJ][7] 
#define LABEL_SEARCHMASKWINDOW		xuiLabelTable[_GLOBALOBJ][8] 
#define LABEL_QUESTIONWINDOW			xuiLabelTable[_GLOBALOBJ][9] 
#define LABEL_FRAMESOURCETWIN			xuiLabelTable[_GLOBALOBJ][10] 
#define LABEL_FRAMEDESTTWIN			xuiLabelTable[_GLOBALOBJ][11] 
#define LABEL_BANNER						xuiLabelTable[_GLOBALOBJ][12] 
#define LABEL_WARNINGWINDOW			xuiLabelTable[_GLOBALOBJ][13] 

/*--- Options menu title and frame labels ( xUIoptionpopup.c ) ---*/
#define LABEL_OPTIONTITLE				xuiLabelTable[_OPTIONMENU][0]
#define LABEL_OPTIONFRAME_1			xuiLabelTable[_OPTIONMENU][1]
#define LABEL_OPTIONFRAME_2			xuiLabelTable[_OPTIONMENU][2]
#define LABEL_OPTIONFRAME_3			xuiLabelTable[_OPTIONMENU][3]
#define LABEL_OPTIONFRAME_4			xuiLabelTable[_OPTIONMENU][4]
#define LABEL_OPTIONFRAME_5			xuiLabelTable[_OPTIONMENU][5]
#define LABEL_OPTIONFRAME_6			xuiLabelTable[_OPTIONMENU][6]
#define LABEL_OPTIONERASE				xuiLabelTable[_OPTIONMENU][7]
#define LABEL_OPTIONLABELFILE			xuiLabelTable[_OPTIONMENU][8]

/*--- Options menu title and frame labels ( xUIoptionpopup.c ) ---*/
#define LABEL_OPTIONTOGGLE				xuiLabelTable[_OPTIONTOGGLE][0]

/*-- message window definitions (xUIpopdown.c, xUIcomm.c ) -------*/
#define LABEL_YES							xuiLabelTable[_MESSAGEWIN][0]
#define LABEL_NO							xuiLabelTable[_MESSAGEWIN][1]
#define LABEL_MENUEND					xuiLabelTable[_MESSAGEWIN][2]
#define LABEL_DELETEENTRY				xuiLabelTable[_MESSAGEWIN][3]
#define LABEL_UPDATEENTRY				xuiLabelTable[_MESSAGEWIN][4]
#define LABEL_OK							xuiLabelTable[_MESSAGEWIN][5]
#define LABEL_CANCEL						xuiLabelTable[_MESSAGEWIN][6]
#define LABEL_PRINT						xuiLabelTable[_MESSAGEWIN][7]
#define LABEL_SEARCHNEXT            xuiLabelTable[_MESSAGEWIN][8]
#define LABEL_SEARCHPREVIOUS        xuiLabelTable[_MESSAGEWIN][9]
#define LABEL_MAINQUIT					xuiLabelTable[_MESSAGEWIN][10]
#define LABEL_GLOBALSAVE				xuiLabelTable[_MESSAGEWIN][11]

/*-- action bar definitions ! 2 lines (sUIactionbar.c) -----------*/
#define LABEL_HELP_1						xuiLabelTable[_ACTIONBAR][0]
#define LABEL_HELP_2						xuiLabelTable[_ACTIONBAR][1]
#define LABEL_NEXTITEM_1				xuiLabelTable[_ACTIONBAR][2]
#define LABEL_NEXTITEM_2				xuiLabelTable[_ACTIONBAR][3]
#define LABEL_LASTITEM_1				xuiLabelTable[_ACTIONBAR][4]
#define LABEL_LASTITEM_2				xuiLabelTable[_ACTIONBAR][5]
#define LABEL_DELETEITEM_1				xuiLabelTable[_ACTIONBAR][6]
#define LABEL_DELETEITEM_2				xuiLabelTable[_ACTIONBAR][7]
#define LABEL_ENDEDIT_1					xuiLabelTable[_ACTIONBAR][8]
#define LABEL_ENDEDIT_2					xuiLabelTable[_ACTIONBAR][9]
#define LABEL_COMMIT_1					xuiLabelTable[_ACTIONBAR][10]
#define LABEL_COMMIT_2					xuiLabelTable[_ACTIONBAR][11]
#define LABEL_DELETEMENU_1				xuiLabelTable[_ACTIONBAR][12]
#define LABEL_DELETEMENU_2				xuiLabelTable[_ACTIONBAR][13]
#define LABEL_QUITMENU_1				xuiLabelTable[_ACTIONBAR][14]
#define LABEL_QUITMENU_2				xuiLabelTable[_ACTIONBAR][15]

/*-- frame  definitions  (xUIpopup.c) ----------------------------*/
#define LABEL_FRAMEOBLIG				xuiLabelTable[_FRAME][0]
#define LABEL_FRAMEOPTION				xuiLabelTable[_FRAME][1]
#define LABEL_FRAMEACTION				xuiLabelTable[_FRAME][2]
#define LABEL_FRAMETOGGLE				xuiLabelTable[_FRAME][3]

/*-- Toggles DB mode in popup Menus (xUIpopup.c) -----------------*/
#define LABEL_CHANGEMODE				xuiLabelTable[_DBMODE][0]
#define LABEL_INSERTMODE				xuiLabelTable[_DBMODE][1] 
#define LABEL_UPDATEMODE				xuiLabelTable[_DBMODE][2]
#define LABEL_DELETEMODE				xuiLabelTable[_DBMODE][3]




/*********************** BOOKING MASK ***********************************/

/*--- DLN menu title and frame labels ( xBMdln.c ) ---------------*/
#define LABEL_DLNTITLE					xbmLabelTable[_DLN_FRAME][0]
#define LABEL_DLNFRAME					xbmLabelTable[_DLN_FRAME][1]
#define LABEL_DLNMENU					xbmLabelTable[_DLN_MENU][0]

/*--- CAT menu title and frame labels ( xBMcat.c ) ---------------*/
#define LABEL_CATTITLE					xbmLabelTable[_CAT_FRAME][0]
#define LABEL_CATFRAME					xbmLabelTable[_CAT_FRAME][1]
#define LABEL_CATRECALL					xbmLabelTable[_CAT_RECALL][0]
#define LABEL_CATHEADER					xbmLabelTable[_CAT_HEADER][0]
#define LABEL_CATMENU					xbmLabelTable[_CAT_MENU][0]

/*--- CAB menu title and frame labels ( xBMcabine.c ) ------------*/
#define LABEL_DLTTITLE					xbmLabelTable[_DLT_FRAME][0]
#define LABEL_DLTFRAME					xbmLabelTable[_DLT_FRAME][1]
#define LABEL_DLTMENU					xbmLabelTable[_DLT_MENU][0]

/*************************** PLANNING BOARD ******************************/
#define LABEL_BOARDTITLE				xbmLabelTable[_BOARD_MENU][0]
#define LABEL_BOARDMENU					xbmLabelTable[_BOARD_MENU][1]


/*************************** GRAPHIC *************************************/

/*------- main Labels for Graphik ---------------------------------*/
#define LABEL_GRAPHIshELL				xgrLabelTable[_GR_MAIN][0]
#define LABEL_GRAPHIKICON				xgrLabelTable[_GR_MAIN][1]
#define LABEL_GRAPHIKDATEILABEL		xgrLabelTable[_GR_MAIN][2]
#define LABEL_GRAPHIKTEXTFELD			xgrLabelTable[_GR_MAIN][3]
#define LABEL_GRAPHIKTEXTFELDQUIT	xgrLabelTable[_GR_MAIN][4]
#define LABEL_GRAPHIKLISTLABEL		xgrLabelTable[_GR_MAIN][5]
#define LABEL_GRAPHIKSELECT			xgrLabelTable[_GR_MAIN][6]
#define LABEL_GRAPHIKFILESELECTION	xgrLabelTable[_GR_MAIN][7]
#define LABEL_GRAPHIKPALETTE			xgrLabelTable[_GR_MAIN][8]
#define LABEL_GRAPHIKAKTREGION		xgrLabelTable[_GR_MAIN][9]
#define LABEL_GRAPHIKBOOKING			xgrLabelTable[_GR_MAIN][10]


/*---- Options ( Fonts,Colors,Linewidth,Pattern,Linestyle,Snap -----*/
#define LABEL_GRAPHIKOPTION			xgrLabelTable[_GR_OPTION][0]

/*---- Pulldown  ---------------------------------------------------*/
#define LABEL_XGRPULLDOWNSTART		xgrLabelTable[_GR_MENU_FILE][0]

/*---- Questions, miscelleanous ------------------------------------*/
#define LABEL_REGIONDEFINED         xgrLabelTable[_GR_QUESTION][0]
#define LABEL_REGIONUNDEFINED       xgrLabelTable[_GR_QUESTION][1]
#define LABEL_DELETEALL             xgrLabelTable[_GR_QUESTION][2]
#define LABEL_QUIT                  xgrLabelTable[_GR_QUESTION][3]
#define LABEL_GO                    xgrLabelTable[_GR_QUESTION][4]


/*---- Texts on Dialogwindows -------------------------------------*/
#define FRAGE_LINE0						xgrLabelTable[_GR_DIALOG_TEXT][0]
#define FRAGE_LINE1						xgrLabelTable[_GR_DIALOG_TEXT][1]
#define FRAGE_POINT0						xgrLabelTable[_GR_DIALOG_TEXT][2]
#define FRAGE_RECTANGLE0				xgrLabelTable[_GR_DIALOG_TEXT][3]
#define FRAGE_RECTANGLE1				xgrLabelTable[_GR_DIALOG_TEXT][4]
#define FRAGE_ARC0						xgrLabelTable[_GR_DIALOG_TEXT][5]
#define FRAGE_ARC1						xgrLabelTable[_GR_DIALOG_TEXT][6]
#define FRAGE_ARC2						xgrLabelTable[_GR_DIALOG_TEXT][7]
#define FRAGE_CIRCLE0					xgrLabelTable[_GR_DIALOG_TEXT][8]
#define FRAGE_CIRCLE1					xgrLabelTable[_GR_DIALOG_TEXT][9]
#define FRAGE_ELLIPSE0					xgrLabelTable[_GR_DIALOG_TEXT][10]
#define FRAGE_ELLIPSE1					xgrLabelTable[_GR_DIALOG_TEXT][11]
#define FRAGE_TEXT0						xgrLabelTable[_GR_DIALOG_TEXT][12]
#define FRAGE_TEXT1						xgrLabelTable[_GR_DIALOG_TEXT][13]
#define FRAGE_GRID0						xgrLabelTable[_GR_DIALOG_TEXT][14]
#define FRAGE_PICKBOX0					xgrLabelTable[_GR_DIALOG_TEXT][15]
#define FRAGE_DRAWAREA0					xgrLabelTable[_GR_DIALOG_TEXT][16]
#define FRAGE_POINTS0					xgrLabelTable[_GR_DIALOG_TEXT][17]
#define FRAGE_MOVE0						xgrLabelTable[_GR_DIALOG_TEXT][18]
#define FRAGE_MOVE1						xgrLabelTable[_GR_DIALOG_TEXT][19]
#define FRAGE_COPY0						xgrLabelTable[_GR_DIALOG_TEXT][20]
#define FRAGE_COPY1						xgrLabelTable[_GR_DIALOG_TEXT][21]
#define FRAGE_DELETE0					xgrLabelTable[_GR_DIALOG_TEXT][22]
#define FRAGE_ZOOM0						xgrLabelTable[_GR_DIALOG_TEXT][23]
#define FRAGE_ZOOM1						xgrLabelTable[_GR_DIALOG_TEXT][24]
#define FRAGE_REGION0					xgrLabelTable[_GR_DIALOG_TEXT][25]
#define FRAGE_REGION1					xgrLabelTable[_GR_DIALOG_TEXT][26]


/*---- Menu buttons in graphik shell --------------------------------*/
#define LABEL_MINIMENU					xgrLabelTable[_GR_MINI_MENU][0]

