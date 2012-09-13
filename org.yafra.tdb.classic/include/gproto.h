/*IH***********************************************************
 * File:       GRAPHIC                                 gproto.h		
 *
 * Description:   Functions and Callback prototypes
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 *
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/gproto.h,v 1.2 2008-11-02 19:55:32 mwn Exp $
 */

Widget     xGRwidget_shell           (Widget);
Widget     xGRwidget_shell_menu      (Widget);
Widget     xGRwidget_menubar         (Widget);
Widget     xGRwidget_menubar_mini    (Widget);
Widget     xGRwidget_status          (Widget);
Widget     xGRwidget_optionmenu      (Widget);
Widget     xGRwidget_textfeld        (Widget);
Widget     xGRwidget_selectregion    (Widget);
Widget     xGRwidget_listregion      (Widget);
Widget     xGRwidget_graphik         (Widget);
Widget     xGRwidget_palette         (Widget);		   
Widget     xGRwidget_palettehead     (Widget);
Widget     xGRwidget_booking         (Widget);
void       xGRwidget_status_clear    (void);
void       xGRwidget_graphik_resize  (Boolean);		   
void       xGRwidget_graphik_getsize (XPoint *);		   
void       xGRwidget_graphik_scrollpos(int, int);		   
void       xGRwidget_menubar_sensitive(void); 


XmString   xGRregion_name         (REGOBJ *, int);
long       xGRfind_regionchildren (REGOBJ *, long **, int);
long       xGRfind_region_koord   (int, int);
long       xGRfind_region_name    (char *);
GRAFOBJ   *xGRfind_object_koord   (short, short, short, short);

void       xGRtime                (void);
void       xGRstringpos           (char*, int, int);
void       xGRchangetyp           (int);
void       xGRzoomstack           (ZOOM*, int*, int, int);
void       xGRlocate              (Widget, int, int, int, int);
void       xGRinit_graphic        (void);
void       xGRinit_factors        (void); 
void       xGRinit_context        (void); 
void       xGRcreate_regionpoint  (REGIONPOINT*);
void       xGRcreate_regionpoint_file(void);
void       xGRcreate_regobj_file  (void);
void       xGRfind_regionpoint    (REGIONPOINT*, int);
void       xGRfind_point          (XPoint*);
void       xGRselect_changestatus (REGOBJ*, Boolean);
void       xGRquit_graphic        (void);

void       xGRcreate_line         (XEvent*, int);
void       xGRcreate_point        (XEvent*, int);
void       xGRcreate_rectangle    (XEvent*, int);
void       xGRcreate_arc          (XEvent*, int);
void       xGRcreate_circle       (XEvent*, int);
void       xGRcreate_ellipse      (XEvent*, int);
void       xGRcreate_text         (XEvent*, int);
void       xGRfile                (XEvent*, int);
void       xGRzoom                (XEvent*, int);
void       xGRzoom_reset          (void); 
void       xGRzoom_regions        (void);
void       xGRzoom_graphik        (void); 
void       xGRhelp                (XEvent*, int);
void       xGRmove                (XEvent*, int);
void       xGRcopy                (XEvent*, int);
void       xGRdelete              (XEvent*, int);
void       xGRask                 (XEvent*, int);
void       xGRbook                (XEvent*, int);
void       xGRbook_temp_reset     (void);

void       xGRselect_region       (XtPointer, int);

void       xGRobjkoord_rectangle  (XRectangle*);

void       xGRget_point           (int, int, XPoint*);
void       xGRcopy_object         (XPoint, XPoint, GRAFOBJ*, int);
void       xGRdelete_object       (GRAFOBJ*);
void       xGRcreate_region       (REGOBJ*);

void       xGRdraw_region         (REGOBJ*);
void       xGRdraw_object         (GRAFOBJ*);
void       xGRdraw_tempobject     (void);
void       xGRdraw_grid           (void);
void       xGRdraw_regionpoints   (void);

WCVALUE    xGRzoomfaktor          (ZOOM*);

Boolean    xGRwrite_graphik       (char *);
long       xGRwrite_graphikdata   (void);
Boolean    xGRread_graphik        (char *);
long       xGRread_graphikdata    (char *);
void       xGRread_graphikdata_default(void);
Boolean    xGRset_filename        (char *);
Boolean    xGRwrite_regions       (char *);
long       xGRwrite_regions_len   (void);
Boolean    xGRread_regions        (char *);
Boolean    xGRread_regions_zustand(void);
void       xGRwait_for_zustand    (void);

XtTimerCallbackProc xGRread_booking (XtPointer);

Boolean    xGRget_koord           (XEvent*, XPoint*);
Boolean    xGRget_arc             (XPoint*, XArc*);
Boolean    xGRvalues              (short*, char*, int);
Boolean    xGRfind_object         (XPoint, GRAFOBJ**);
Boolean    xGRfind_regiongraf     (GRAFOBJ*);
Boolean    xGRcheck_rectangle     (void);

int        xGRint_gerundet        (WCVALUE);
int        xGRanz_strings         (char*, char***);
int        xGRcomp_regionpoint_kor(void*, void*);
int        xGRcomp_regionpoint_num(void*, void*);
int        xGRcomp_regionpoint_num_b(const void*, const void*);

XtCallbackProc   xGRaction        (Widget, XtPointer, XtPointer);
void             xGRaction_initialize(void);

XtCallbackProc   xGRdelete_region (Widget, XtPointer, XtPointer);
XtCallbackProc   xGRsend          (Widget, XtPointer, XtPointer);
XtCallbackProc   xGRunbook        (Widget, XtPointer, XtPointer);
XtCallbackProc   xGRgetfilename   (Widget, XtPointer, XtPointer);
XtCallbackProc   xGRdeleteall     (Widget, XtPointer, XtPointer);
XtCallbackProc   xGRquit          (Widget, XtPointer, XtPointer);
XtCallbackProc   xGRdraw          (Widget, XtPointer, XtPointer);
XtCallbackProc   xGRupdate_cursor (Widget, XtPointer, XtPointer);
XtCallbackProc   xGRfile_handling (Widget, XtPointer, XtPointer);


XtActionProc xGRbook_one     (Widget, XEvent *, String *, Cardinal *);
XtActionProc xGRbook_andquit (Widget, XEvent *, String *, Cardinal *);
XtActionProc xGRbook_clear   (Widget, XEvent *, String *, Cardinal *);

void xGRinit_cat_colors(void);   /* init Graphic Contexts */
