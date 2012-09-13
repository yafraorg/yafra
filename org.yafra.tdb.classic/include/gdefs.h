/*IH***********************************************************
 * Header:        GRAPHIC
 * Description:   Constants, menu positions and general limits
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 *
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/gdefs.h,v 1.3 2008-11-29 21:56:38 mwn Exp $
 */

#define GRAPHIshELL                   "graphishell"
#define GRAPHIKMAIN                    "graphikmain"
#define GRAPHIKMENUBAR                 "graphikmenubar"
#define GRAPHIKFORM                    "graphikform"
#define GRAPHIKSTATUS                  "graphikstatus"
#define GRAPHIKTEXTFELD                "graphiktextfeld"
#define GRAPHIKSELECTREGION            "graphikselectregion"
#define GRAPHIKLISTREGION              "graphiklistregion"
#define GRAPHIK                        "graphik"
#define GRAPHIKMENUBUTTON              "graphikmenubutton"
#define GRAPHIKSTATUSZEILE             "graphikstatuszeile"
#define GRAPHIKKOORD                   "graphikkoord"
#define GRAPHIKDATEINAME               "graphikdateiname"
#define GRAPHIKAKTREGIONLABEL          "graphikaktregionlabel"
#define GRAPHIKAKTREGION               "graphikaktregion"
#define GRAPHIKDATEILABEL              "graphikdateilabel"
#define GRAPHIKTEXTFELDLABEL           "graphiktextfeldlabel"
#define GRAPHIKTEXTFELDQUIT            "graphiktextfeldquit"
#define GRAPHIKFRAGE                   "graphikfrage"
#define GRAPHIKANTWORT                 "graphikantwort"
#define GRAPHIKSCROLLEDGRAPHIK         "graphikscrolledgraphik"
#define GRAPHIKDRAWINGAREA             "graphikdrawingarea"
#define GRAPHIKLISTREGION              "graphiklistregion"
#define GRAPHIKCLOCK                   "graphikclock"
#define GRAPHIKDATUM                   "graphikdatum"
#define GRAPHIKSTUNDE                  "graphikstunde"
#define GRAPHIKMINUTE                  "graphikminute"
#define GRAPHIKSEKUNDE                 "graphiksekunde"
#define GRAPHIKTRENN                   "graphiktrenn"
#define GRAPHIKLISTLABEL               "graphiklistlabel"
#define GRAPHIKBOOKING                 "graphikbooking"
#define GRAPHIKGO                      "graphikgo"
#define GRAPHIKSELECTLABEL             "graphikselectlabel"
#define GRAPHIKSELECT                  "graphikselect"
#define GRAPHIKOPTIONMENU              "graphikoptionmenu"
#define GRAPHIKOPTION                  "graphikoption"
#define GRAPHIKOPTIONPULLDOWN          "graphikoptionpulldown"
#define FILESELECTIONBOX               "fileselectionbox"
#define GRAPHIKROWCOL	               "graphikrowcol"
#define GRAPHIKFRAME		               "graphikframe"
#define GRAPHIKPUSHBUTTON              "graphikpushbutton"


#define BUTTONNONE                    -1

/*--- Callback Qualifier --------------------*/
#define BUTTONFILE                     0
#define BUTTONFILE_LOAD                  0
#define BUTTONFILE_SAVE                  1
#define BUTTONFILE_SAVEAS                2
#define BUTTONFILE_DELETEALL             3
#define BUTTONFILE_CANCEL                4
#define BUTTONFILE_QUIT                  5

#define BUTTONCREATE                   1
#define BUTTONCREATE_TEXT                0
#define BUTTONCREATE_POINT               1
#define BUTTONCREATE_LINE                2
#define BUTTONCREATE_RECTANGLE           3
#define BUTTONCREATE_CIRCLE              4
#define BUTTONCREATE_ARC                 5
#define BUTTONCREATE_ELLIPSE             6
#define BUTTONCREATE_FILLEDRECTANGLE     7
#define BUTTONCREATE_FILLEDCIRCLE        8
#define BUTTONCREATE_FILLEDARC           9
#define BUTTONCREATE_FILLEDELLIPSE      10

#define BUTTONEDIT                     2
#define BUTTONEDIT_MOVE                  0
#define BUTTONEDIT_COPY                  1
#define BUTTONEDIT_DELETE                2

#define BUTTONDEFINE                   3
#define BUTTONDEFINE_GRID                0
#define BUTTONDEFINE_PICKBOX             1
#define BUTTONDEFINE_DRAWAREA            2
#define BUTTONDEFINE_POINTS              3

#define BUTTONZOOM                     4
#define BUTTONZOOM_START                 0
#define BUTTONZOOM_ZOOM                  1
#define BUTTONZOOM_LAST                  2
#define BUTTONZOOM_NEXT                  3
#define BUTTONZOOM_RESIZE                4
#define BUTTONZOOM_SCROLL                5

#define BUTTONHILFE                    5
#define BUTTONHILFE_GRAPHIK               0
#define BUTTONHILFE_MENUGLOBAL            1
#define BUTTONHILFE_MENUNUMMER            2
#define BUTTONHILFE_APPLICATION           3

#define BUTTONTEXTFELDQUIT             6

#define BUTTONTEXTFELDANTWORT          7

#define BUTTONGRAPHIK                  8

#define BUTTONSELECT                   9
#define BUTTONSELECT_DEFINE               0
#define BUTTONSELECT_DELETE               1

#define BUTTONLINESTYLE               10
#define BUTTONLINESYLE_SOLID              0
#define BUTTONLINESYLE_DASHED             1
#define BUTTONLINESYLE_DOTDASHED          2

#define BUTTONSNAP                    11
#define BUTTONSNAP_GRID                   0
#define BUTTONSNAP_POINT                  1
#define BUTTONSNAP_NONE                   2

#define BUTTONFONT                    12
#define BUTTONLINEWIDTH               13
#define BUTTONPATTERN                 14
#define BUTTONCOLOR                   15

#define BUTTONDOUBLECLICK             16



/*--- Maxima values ---------------------------------*/
#define MAXANTWORT                      100
#define MAXZOOM                          30
#define MAXPIXELMMRATIO                  20
#define MAXREGPOINTS                    100
#define MAXBUCHUNG                      256

#define READONLY                        0
#define READORUPDATE                    1

#define PICKBOXOFF                      0
#define PICKBOXON                       1

#define MAXGRAVALUES            3
#define MAXREGOBJ               6

#define OBJ_LINE                0
#define OBJ_POINT               1
#define OBJ_RECTANGLE           2
#define OBJ_FILLEDRECTANGLE     3
#define OBJ_ARC                 4
#define OBJ_FILLEDARC           5
#define OBJ_CIRCLE              6
#define OBJ_FILLEDCIRCLE        7
#define OBJ_ELLIPSE             8
#define OBJ_FILLEDELLIPSE       9
#define OBJ_TEXT               10
#define OBJ_DRAWINGAREA        11
#define TEMP_TEXT              12
#define TEMP_LINE              13
#define TEMP_RECTANGLE         14
#define TEMP_CIRCLE            15


/*--- Error messages indexes in  app-default/errors file ---------------*/
#define XGRREGIONDEFINED               100
#define XGRGRAFORMAT                   101
#define XGRGRAFILE                     102
#define XGRGRAFILEOPEN                 103
#define XGRSCHONDATEI                  104
#define XGRIDENTOBJECT                 105
#define XGRIDENTSNAP                   106
#define XGRREGIONNOTDEFINED            107
#define XGRNOTINVATERREGION            108
#define XGRNOREGION                    109
#define XGRNOTAREGION                  110
#define XGRREGIONALREADYDEFINED        111
#define XGRNOFILEDEFINED               112
#define XGRREGIONALREADYUNDEFINED      113
#define XGRTOOMUCHBOOKED               114
#define XGRREGIONHASCHILDREN           115
#define XGRNOREGIONPOINTFOUND          116
#define XGRNOPOINTFOUND                117
#define XGRZOOMLIMITREACHED            118


#define SELECTTRENNER           " : "
#define NOVATER                -1

#define EPS                     0.01

#define MODE_KOR               0
#define MODE_NUM               1

#define REGDEF                 0
#define REGALL                 1

#define XGRMM                  0
#define XGRPIXEL               1

#define XGRLEER1               30
#define XGRLEER2               20
#define XGRLEER3               65

#define XGRFILENAMELEN         30

// TODO issue with BEZLEN of mpdbi and the change of BEZ from 30 to 1024 - one of them caused an issue not sure which one, so I increased both
// #define XGRCOORDLEN            20
// #define XGRREGIONLEN           40
#define XGRCOORDLEN            1024
#define XGRREGIONLEN           1024

#define XGR_LINE_LEN           200

#define XGRRIGHT               0
#define XGRLEFT                1
#define XGRCENTER              2

/*--- Booking mode ----------------------*/
#define XGRBOOK_ONE            0
#define XGRBOOK_MANY           1

