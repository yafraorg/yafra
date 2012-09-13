/**************************************************************/
/* Modul:     editiere eine beliebige Datei                   *
/*                                                            */
/* Uebergabe: Toplevel Widget                                 */
/*            Bitmap File / Bitmap Buffer                     */
/*            Vorder- und Hintergrund als Pixel               */
/*                                                            */
/* Copyright: Yafra.org     */
/* Autor:     Administrator, Yafra.org                     */
/*                                                            */
/* History:   June 1992 mw Erstellung                         */
/**************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/psgui/source/editfile.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

#ifdef ps_unix

/* INCLUDES */
#include <X11/Xlib.h>        /* Xlib header */
#include <X11/Intrinsic.h>   /* X Toolkit prototypes */
#include <X11/Shell.h>       /* Xt Shell Class */
#include <Xm/Xm.h>           /* OSF/Motif Resources */

#include <Xm/CascadeB.h>
#include <Xm/Text.h>
#include <Xm/LabelG.h>
#include <Xm/PushBG.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/MainW.h>
#include <Xm/PanedW.h>
#include <Xm/FileSB.h>
#include <Xm/Separator.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <psgui.h>          /* Prototypes of Utilities */

Widget text_w, search_w, replace_w, text_output;

void open_file(Widget, int, caddr_t);
void file_cb(Widget, int, XmAnyCallbackStruct *);
void search_cb(Widget, int, XmAnyCallbackStruct *);
void cut_paste(Widget, int);
void read_file(char *filename);

int OSFEditFile(char *filename)
{
	Arg     args[10];
	register int ac;
	XmString      new, save, quit, quit_acc, file, edit, cut,
	              clear, copy, paste, search, next, find, replace;

	Widget topdialog;
	Widget mainwin;
	Widget menubar, pulldown, pane, rowcol, pb;
	Widget button;
	Widget separator;
	Widget label;
	Widget cascade;

	topdialog = XtCreateApplicationShell("edit", topLevelShellWidgetClass, NULL, 0);
	mainwin = XmCreateMainWindow(topdialog, "editmainwin", NULL, 0);

	/* Create a simple MenuBar that contains three menus */
	menubar = XmCreateMenuBar(mainwin, "menubar", NULL, 0);
	
	/* First menu is the File menu -- callback is file_cb() */
	pulldown = XmCreatePulldownMenu(menubar, "filemenu", NULL, 0);
	button = XmCreatePushButton(pulldown, "new", NULL, 0);
	XtAddCallback(button, XmNactivateCallback, (XtCallbackProc)file_cb, 0);
	XtManageChild(button);
	button = XmCreatePushButton(pulldown, "save", NULL, 0);
	XtAddCallback(button, XmNactivateCallback, (XtCallbackProc)file_cb, 1);
	XtManageChild(button);
	separator = XmCreateSeparator(pulldown, "separator", NULL, 0);
	XtManageChild(separator);
	button = XmCreatePushButton(pulldown, "quit", NULL, 0);
	XtAddCallback(button, XmNactivateCallback, (XtCallbackProc)file_cb, 2);
	XtManageChild(button);
	ac = 0;
	XtSetArg (args[ac], XmNsubMenuId, pulldown);  ac++;
	cascade = XmCreateCascadeButton(menubar, "File", args, ac);
	XtManageChild(cascade);
	
	/* ...create the "Edit" menu --  callback is cut_paste() */
	pulldown = XmCreatePulldownMenu(menubar, "editmenu", NULL, 0);
	button = XmCreatePushButton(pulldown, "cut", NULL, 0);
	XtAddCallback(button, XmNactivateCallback, (XtCallbackProc)cut_paste, NULL);
	XtManageChild(button);
	button = XmCreatePushButton(pulldown, "copy", NULL, 0);
	XtAddCallback(button, XmNactivateCallback, (XtCallbackProc)cut_paste, NULL);
	XtManageChild(button);
	button = XmCreatePushButton(pulldown, "paste", NULL, 0);
	XtAddCallback(button, XmNactivateCallback, (XtCallbackProc)cut_paste, NULL);
	XtManageChild(button);
	separator = XmCreateSeparator(pulldown, "separator", NULL, 0);
	XtManageChild(separator);
	button = XmCreatePushButton(pulldown, "cleat", NULL, 0);
	XtAddCallback(button, XmNactivateCallback, (XtCallbackProc)cut_paste, NULL);
	XtManageChild(button);
	ac = 0;
	XtSetArg(args[ac], XmNsubMenuId, pulldown);  ac++;
	cascade = XmCreateCascadeButton(menubar, "Edit", args, ac);
	XtManageChild(cascade);

	/* create the "Search" menu -- callback is search_cb() */
	pulldown = XmCreatePulldownMenu(menubar, "searchmenu", NULL, 0);
	button = XmCreatePushButton(pulldown, "next", NULL, 0);
	XtAddCallback(button, XmNactivateCallback, (XtCallbackProc)search_cb, NULL);
	XtManageChild(button);
	button = XmCreatePushButton(pulldown, "find", NULL, 0);
	XtAddCallback(button, XmNactivateCallback, (XtCallbackProc)search_cb, NULL);
	XtManageChild(button);
	button = XmCreatePushButton(pulldown, "replace", NULL, 0);
	XtAddCallback(button, XmNactivateCallback, (XtCallbackProc)search_cb, NULL);
	XtManageChild(button);
	separator = XmCreateSeparator(pulldown, "separator", NULL, 0);
	XtManageChild(separator);
	button = XmCreatePushButton(pulldown, "cleat", NULL, 0);
	XtAddCallback(button, XmNactivateCallback, (XtCallbackProc)search_cb, NULL);
	XtManageChild(button);
	ac = 0;
	XtSetArg(args[ac], XmNsubMenuId, pulldown);  ac++;
	cascade = XmCreateCascadeButton(menubar, "Search", args, ac);
	XtManageChild(cascade);

	/* Help Menu */
	ac = 0;
	XtSetArg(args[ac], XmNacceleratorText, 
	         XmStringCreateLtoR("F1", XmSTRING_DEFAULT_CHARSET)); ac++;
	XtSetArg(args[ac], XmNaccelerator, "<Key>F1:"); ac++;
	cascade = XmCreateCascadeButton(menubar, "Help", args, ac);
/*	XtAddCallback(cascade, XmNactivateCallback, HelpCB, HELP_MAIN); */
	XtManageChild(cascade);
	ac = 0;
	XtSetArg (args[ac], XmNmenuHelpWidget, cascade);  ac++;
	XtSetValues(menubar, args, ac);

	XtManageChild(menubar);
	
	/* create a standard vertical PanedWindow... */
	pane = XmCreatePanedWindow(mainwin, "pane", NULL, 0);
	
	/* create horizontal RowColumn inside the pane... */
	ac = 0;
	XtSetArg(args[ac], XmNorientation, XmHORIZONTAL); ac++;
	XtSetArg(args[ac], XmNpacking, XmPACK_TIGHT); ac++;
	rowcol = XmCreateRowColumn(pane, "rowcol", args, ac);

	/* Create two Text widgets with Labels... */
	label = XmCreateLabelGadget(rowcol, "searchlabel", NULL, 0);
	XtManageChild(label);
	search_w = XmCreateText(rowcol, "search_text", NULL, 0);
	XtManageChild(search_w);
	label = XmCreateLabelGadget(rowcol, "replacelabel", NULL, 0);
	XtManageChild(label);
	replace_w = XmCreateText(rowcol, "replace_text", NULL, 0);
	XtManageChild(replace_w);
	XtManageChild(rowcol);
	
	ac = 0;
	XtSetArg(args[ac], XmNeditable, False); ac++;
	XtSetArg(args[ac], XmNcursorPositionVisible, False); ac++;
	XtSetArg(args[ac], XmNshadowThickness, 0); ac++;
	XtSetArg(args[ac], XmNsensitive, False); ac++;
	text_output = XmCreateText(pane, "text_out", args, ac);
	XtManageChild(text_output);

	ac = 0;
	XtSetArg(args[ac], XmNrows,      10); ac++;
	XtSetArg(args[ac], XmNcolumns,   80); ac++;
	XtSetArg(args[ac], XmNeditMode,  XmMULTI_LINE_EDIT); ac++;
	text_w = XmCreateScrolledText(pane, "text_w", args, ac);
	XtManageChild(text_w);
	
	XtManageChild(pane);
	XtManageChild(mainwin);
	
	XtRealizeWidget(topdialog);

	read_file(filename);
}



/*
 * callback routine for "Ok" button in FileSelectionDialogs
 */
void open_file(Widget dialog, int save, caddr_t data)
{
	char buf[BUFSIZ], *filename, *text;
	XmFileSelectionBoxCallbackStruct *cbs =
		(XmFileSelectionBoxCallbackStruct *)data;
	struct stat statb;
	long len;
	FILE *fp;
		
	if (!XmStringGetLtoR(cbs->value,	XmSTRING_DEFAULT_CHARSET, &filename))
		return; /* must have been an internal error */
		
	if (!*filename)
		{
		XtFree(filename);
		XBell(XtDisplay(text_w), 50);
		XmTextSetString(text_output, "Choose a file.");
		return; /* nothing typed */
		}
		
	if (save)
		{
		if (!(fp = fopen(filename, "w")))
			{
			perror(filename);
			sprintf(buf, "Can't save to %s.", filename);
			XmTextSetString(text_output, buf);
			XtFree(filename);
			return;
			}

		/* saving -- get text from Text widget... */
		text = XmTextGetString(text_w);
		len = XmTextGetLastPosition(text_w);
		/* write it to file (check for error) */
		if (fwrite(text, sizeof(char), len, fp) != len)
			strcpy(buf, "Warning: did not write entire file!");
		else
			{
			/* make sure a newline terminates file */
			if (text[len-1] != '\n')
				fputc('\n', fp);
			sprintf(buf, "Saved %ld bytes to %s.", len, filename);
			}
		}
	else
		{
		/* make sure the file is a regular text file and open it */
		if (stat(filename, &statb) == -1 || (statb.st_mode & S_IFMT) != S_IFREG ||
			!(fp = fopen(filename, "r")))
			{
			perror(filename);
			sprintf(buf, "Can't read %s.", filename);
			XmTextSetString(text_output, buf);
			XtFree(filename);
			return;
			}

		/* put the contents of the file in the Text widget by
		 * allocating enough space for the entire file, reading the
		 * file into the space, and using XmTextSetString() to show
		 * the file.
		 */
		len = statb.st_size;
		if (!(text = XtMalloc((unsigned)(len+1)))) /* +1 for NULL */
            sprintf(buf, "%s: XtMalloc(%ld) failed", len, filename);
		else
			{
			if (fread(text, sizeof(char), len, fp) != len)
				sprintf(buf, "Warning: did not read entire file!");
			else
				sprintf(buf, "Loaded %ld bytes from %s.", len, filename);
			text[len] = 0; /* NULL-terminate */
			XmTextSetString(text_w, text);
			}
		}
	XmTextSetString(text_output, buf); /* purge output message */
		
	/* free all allocated space. */
	XtFree(text);
	XtFree(filename);
	fclose(fp);
}

/*
 * a menu item from the "File" pulldown menu was selected
 */
void file_cb(Widget w, int item_no, XmAnyCallbackStruct *cbs)
{
	static Widget open_dialog, save_dialog;
	Widget        dialog = NULL;
	XmString      str, title;
		
	if (item_no == 2)
		exit(0);
	
	if (item_no == 0 && open_dialog)
		dialog = open_dialog;
	else if (item_no == 1 && save_dialog)
		dialog = save_dialog;
		
	if (dialog)
		{
		XtManageChild(dialog);
		/* make sure that dialog is raised to top of window stack */
		XMapRaised(XtDisplay(dialog), XtWindow(XtParent(dialog)));
		return;
		}

	dialog = XmCreateFileSelectionDialog(text_w, "Files", NULL, 0);
	XtAddCallback(dialog, XmNcancelCallback, (XtCallbackProc)XtUnmanageChild, NULL);
	XtAddCallback(dialog, XmNokCallback, (XtCallbackProc)open_file, item_no);
	XtManageChild(dialog);
}

/*
 * a menu item from the "Search" pulldown menu was selected
 */
void search_cb(Widget w, int item_no, XmAnyCallbackStruct *cbs)
{
#define FIND_NEXT 0
#define FIND_ALL  1
#define REPLACE   2
#define CLEAR     3
	char *search_pat, *p, *string, *new_pat, buf[32];
	XmTextPosition pos = 0;
	int len, nfound = 0;
	int search_len, pattern_len;
	enum {XmHIGHLIGHT_NORMAL, XmHIGHLIGHT_SELECTED,
	      XmHIGHLIGHT_SECONDARY_SELECTED} HighlightMode;


    if (item_no == CLEAR) {
        pos = XmTextGetLastPosition(text_w);
        XmTextSetHighlight(text_w, 0, pos, XmHIGHLIGHT_NORMAL);
        return;
    }

    if (!(string = XmTextGetString(text_w)) || !*string) {
        XmTextSetString(text_output, "No text to search.");
        return;
    }
    if (!(search_pat = XmTextGetString(search_w)) || !*search_pat) {
        XmTextSetString(text_output, "Specify a search pattern.");
        XtFree(string);
        return;
    }

    new_pat = XmTextGetString(replace_w);
    search_len = strlen(search_pat);
    pattern_len = strlen(new_pat);

    /* start searching at current cursor position + 1 */
    if (item_no == FIND_NEXT)
/* V4        pos = XmTextGetCursorPosition(text_w) + 1; */
    for (p = &string[pos]; p = index(p, *search_pat); p++)
        if (!strncmp(p, search_pat, search_len)) {
            nfound++;
            /* get the position where pattern was found */
            pos = (XmTextPosition)(p-string);
            if (item_no == REPLACE) {
                /* replace the text position + strlen(new_pat) */
                XmTextReplace(text_w, pos, pos + search_len, new_pat);
                /* "string" has changed -- get the new value */
		XtFree(string);
		string = XmTextGetString(text_w);
                /* continue search -after- replacement */
                p = &string[pos + pattern_len];
            } else if (item_no == FIND_ALL)
                XmTextSetHighlight(text_w, pos, pos+search_len,
                    XmHIGHLIGHT_SELECTED);
            else
                break;
        }
    if (item_no == FIND_NEXT && nfound == 0) {
        /* search from beginning till we've passed "pos" */
        for (p = string; p = index(p, *search_pat); p++)
            if (p - string > pos ||
                    !strncmp(p, search_pat, search_len)) {
                nfound++;
                break;
            }
    }
    if (nfound == 0)
        XmTextSetString(text_output, "Pattern not found.");
    else {
        switch (item_no) {
            case FIND_NEXT :
                pos = (XmTextPosition)(p - string);
                sprintf(buf, "Pattern found at position %ld.", pos);
                XmTextSetInsertionPosition(text_w, pos);
                break;
            case FIND_ALL :
                sprintf(buf, "Found %d occurrences.", nfound);
                break;
            case REPLACE :
            default :
                sprintf(buf, "Made %d replacements.", nfound);
        }
        XmTextSetString(text_output, buf);
    }
    XtFree(string);
    XtFree(search_pat);
    XtFree(new_pat);
}

/*
 * the callback routine for the items in the edit menu
 */
void cut_paste(Widget widget, int num)
{
    Boolean result = True;

    switch (num) {
/* V4        case 0 : result = XmTextCut(text_w, CurrentTime); break;
        case 1 : result = XmTextCopy(text_w, CurrentTime); break;
        case 2 : result = XmTextPaste(text_w); */
        case 3 : XmTextClearSelection(text_w, CurrentTime); break;
    }
    if (result == False)
        XmTextSetString(text_output, "There is no selection.");
    else
        XmTextSetString(text_output, NULL);
}

/*
 * Read the file (the first parameter of EditFile) into the textwidget 
 */
void read_file(char *filename)
{
	char buf[BUFSIZ], *text;
	struct stat statb;
	long len;
	FILE *fp;

	/* make sure the file is a regular text file and open it */
	if (stat(filename, &statb) == -1 || (statb.st_mode & S_IFMT) != S_IFREG ||
		!(fp = fopen(filename, "r")))
		{
		perror(filename);
		sprintf(buf, "Can't read %s.", filename);
		XmTextSetString(text_output, buf);
		XtFree(filename);
		return;
		}

	/* put the contents of the file in the Text widget by
	 * allocating enough space for the entire file, reading the
	 * file into the space, and using XmTextSetString() to show
	 * the file.
	 */
	len = statb.st_size;
	if (!(text = XtMalloc((unsigned)(len+1)))) /* +1 for NULL */
           sprintf(buf, "%s: XtMalloc(%ld) failed", len, filename);
	else
		{
		if (fread(text, sizeof(char), len, fp) != len)
			sprintf(buf, "Warning: did not read entire file!");
		else
			sprintf(buf, "Loaded %ld bytes from %s.", len, filename);
		text[len] = 0; /* NULL-terminate */
		XmTextSetString(text_w, text);
		}
}

#endif
