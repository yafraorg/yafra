/*D***********************************************************
 * Modul:     GUI - dialog   			uinput.c
 *
 *            Receive data from the database daemon (DBI)
 *            The wrapped action depends on COMMTYP
 *
 * Copyright: yafra.org, Basel, Switzerland
 *************************************************************
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uinput.c,v 1.3 2008-11-02 19:55:44 mwn Exp $";


/*F--------------------------------------------------------------------------
 *  Function:	xUIinput
 *					-input wrapper for DBI messages
 *					-
 *  In:			-input params
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtInputCallbackProc xUIinput( XtPointer closure, int *fid, XtInputId *id)
{
	extern Display		*display;
	extern Boolean		openedoption;
	extern Boolean		chosenflag;
	extern Boolean		setupcleanflag;
	extern int        feldnr;
	extern XtPointer  para;
	extern long       grajobflag;
	extern int        aktmenu[];
	extern int        aktmenuobj[];
	extern int        aktmenuz;
	extern int        aktfield[];
	extern int        zufield[];
	extern int        globfield;
	extern MENU       glob, menu[];
	extern Widget     selectpopup, text;
	extern GRAWIDGETS grawidgets;
	extern GLOBDATA   globdata;
	extern char       *entries;
	extern char       *outcomm;
	extern long       maxentries;
	extern Widget     toplevel;
	extern Widget     selectList;
	extern BOOKMENU 	bm_menu[];		/* BM menus */
	extern int			bm_aktfield;
	extern Boolean keepDlnFlag ;
	extern char		keepDlnBuffer[];
	extern Boolean helpPresent;
	extern int        DebugFlag;

	int			antfeldnr;			/* antwort feld nr */
	int			i, j, n, f, cret;
	unsigned char	menuNr ;
	long			laenge;
	Arg			wargs[5];
	Widget		aktparent;
	char			*ptext, *ptr, *title;
	MENU			*a;
	BOOKMENU		*b;

	/*--- inits and checks -------------------------------------------------*/
	feldnr  = antfeldnr  = FELDNR;
	/*--- which menu is active -----------------*/
	if ((MENUNR == _GLOBALMENU) && (globfield != -1))
		{
		a = 0;
		menuNr = _GLOBALMENU;
		}
	else if ((openedoption) && (aktmenuz == -1) )     /* no normal menu exists */
		{
		a = 0;
		}
	else
		{
		a = &menu[aktmenu[aktmenuz]];
		menuNr =	(unsigned char)aktmenuobj[aktmenuz];
		}
	/*--- get BM menu --------------------------*/
	b = xBMmenuActive();

	/*--- set actual parent --------------------*/
	if (b)
		aktparent = b->Wgpopup;			/* BM menu */
	else if (a)
		aktparent = a->popup;			/* UI menu */
	else
		aktparent = toplevel;			/* global or default */


	/*--- read DBI data and check if error --------------------------------*/
	laenge = xUItalkto(RECV, 0, 0);

	/*--- Communcation status check --------------*/
	if (COMMSTAT != MESSAGEOK)
		{														/* exit funct >>>>>>> */
		if (comm.datalen <=0)
			xUIbeep( aktparent, 0, 0, 0);
		else
			xUImessagepopup( COMMSTAT, entries, aktparent);
		return;														/* exit funct >>>>>>> */
		}

	switch (COMMTYP)
		{
		/*--- choosed an item on the global menu -----------------------*/
		case GLOBAL:
			if (ACTIONTYP == GLOBSEND)
				{
				if (DebugFlag)
					PSSYSdebug(NULL, NULL, "GLOBSEND action");
				memcpy((void *)&globdata, (void *)entries, sizeof(globdata));
				for (j=0; j<ANZ_MENU; j++)
					{
					a = &menu[j];     /* lookup each menu if global is in it */
					if (a->flags)
						{
						for (i=0; i<a->anz; i++)
							{
							if (a->vonglobal[i] != -1)
								{
								/*--- copy from glob-MENU field --------*/
								ptext = XmTextGetString( glob.field[a->vonglobal[i]]) ;
								XtSetArg( wargs[0], XmNvalue, ptext );
								if (a->field)
									XtSetValues(a->field[i], wargs, 1);
								XtFree( (void *)ptext);
								}
							}
						/*-- enable normal menus -----*/
						xUImenufeld(a, 0, TRUE, TRUE, FALSE, TRUE);
						}
					}

				/*--- Sprache has changed set a flag to clean setup ------*/
				if (globfield == 2)
					setupcleanflag = True;

				/*-- enable pulldown menus, global is already done by choosedown ---*/
				xUIpulldownSensitive( True );
				globfield = -1;
				}
			if (ACTIONTYP == MAKELABELFILE)
				{
				// call funtion to create a label_xx file
				}
			break;

		case HELPCALL:
			xUIopenHelp(entries);
			break;

		/*--- create a list of possible items to choose -----------------*/
		case SELECT:
			chosenflag = FALSE;
			if (laenge == 0)
				{
				xUIbeep( toplevel, 0, 0, 0);
				return;
				}
			if (b)		/*--- BM select -------*/
				{
				/*--- use bm_aktfield because Classic booking simulation */
				globfield = -1;
				b->enter = FALSE;
				b->editfeld = FALSE;
				b->alreadywrite = TRUE;
				xBMmenufeld( b, b->Wgfields[bm_aktfield], FALSE, TRUE, TRUE, FALSE);
				/*--- check for single or twin selection list ----*/
				if (b->fieldtype[bm_aktfield] == TWINSELFIELD)
					xUICtwinPopup( aktparent, entries );
				else
					xUICselectPopup( aktparent, entries );		/* Select Object */
				}
			else if (menuNr == _GLOBALMENU )					/* list for the global menu */
				{
				/*--- disable all pulldown menus ---*/
				xUIpulldownSensitive( False );
				xUImenufeld( &glob, glob.field[feldnr], FALSE, TRUE, TRUE, FALSE);
				globfield = feldnr;
				xUItostrtable( entries, text);
				XtManageChild( text);
				XtManageChild( XtParent(XtParent(text)));		/* resize form */
				XtPopup( selectpopup, XtGrabNone);
			}
			else 			/*--- UI select -------*/
			{
				globfield = -1;
				aktfield[aktmenuz] = feldnr;
				a->enter = FALSE;
				a->editfeld = FALSE;
				a->alreadywrite = TRUE;
				/*--- set menu disable and color during select --*/
				xUImenufeld(a, a->field[feldnr], FALSE, TRUE, TRUE, FALSE);
				/*--- check for single or twin selection list ----*/
				if (a->buttontype[feldnr] == TWINSELFIELD)
				{
					xUICtwinPopup( a->popup, entries );
				}
				else
				{
					xUItostrtable( entries, text);
					XtManageChild( text);
					XtManageChild( XtParent(XtParent(text)));		/* resize form */
					XtPopup( selectpopup, XtGrabNone);
				}
			}
			break;

		/*--- a whole mask is to update -------------------------------*/
		case SELECTITEM:
			if (menuNr == _OUTPUT )
				xUIoutputnew( a);
			else
				xUIstrmenu( a, comm.buffer);	/* copy buffer to edit field menu */
			break;

		/*--- update only a single field and not the whole mask -------*/
		case CHOOSE:
			if ((menuNr == _OUTPUT) && (feldnr == 0) )
				xUIoutputnew( a);
			else
			{
				/*--- copy buffer into field in menu (overwrite) ----*/
				XtSetArg(wargs[0], XmNvalue, (XtArgVal)comm.buffer);
				if (b)
					XtSetValues( b->Wgfields[bm_aktfield], wargs, 1);
				else if (globfield == -1)
					XtSetValues( menu[aktmenu[aktmenuz]].field[feldnr], wargs, 1);
				else
					XtSetValues(glob.field[globfield], wargs ,1);
			}
			break;

		/*--- insert/update/delete is done ----------------------------*/
		case ACTION:
			a->enter = TRUE;
			break;

		/*--- Info text and/or pcx -----------------------------------*/
		case INFO:
			if (DebugFlag)
				PSSYSdebug(NULL, NULL, "popup INFO window");
			/*--- re-parenting for booking mask --*/
			if (a->typ == _BUCHUNG )
				aktparent = toplevel;

			if (ACTIONTYP == INFOTXT)
				xUItextshell( aktparent, _MSG_INFO, entries );       /*text*/
			if (ACTIONTYP == INFOPCX)
				cret = xUIpcxpopup( aktparent, entries);             /*filename*/
			if (ACTIONTYP == INFOTXTANDPCX)
			{
				for( ptr=entries;  *ptr != '\n';  ptr++);
				  *ptr++ = '\0';
				xUItextshell( aktparent, _MSG_INFO, ptr );           /*text*/
				cret = xUIpcxpopup( aktparent, entries);             /*filename*/
			}
			break;


		/*---- Planning Board ----------------------------------------*/
		/*---- NOT SUPPORTED BY HP_UX_400 ------*/

		case MATRIXSELECT:
			/*--- Get field content for title ---*/

#if defined(_HPUX400)
			if (DebugFlag)
				PSSYSdebug(NULL, NULL, "no matrix board on this architecture available");
			xUIbeep( aktparent, 0, 0, 0);
#else
			if (DebugFlag)
				PSSYSdebug(NULL, NULL, "popup matrix board");
			title = XmTextGetString( a->field[feldnr] );
			xBMboardPopup( ACTIONTYP, entries, title );
			XtFree( (void *)title);
#endif

			break;

		/*--- BOOKING PROCESS ----------------------------------------------*/
		/*--- Booking-mask dln short mask */
		case BMDLN:
			xBMdlnPopup( toplevel);
			break;

		/*--- build a select widget for dienstleistung */
		case BMOBJCHOOSE:
			xUICselectPopup( aktparent, entries );					/* Select Object */
			break;

		/*--- booking category choice */
		case BMBOOK:
			/*--- disable previous BM menu ---*/
			if (b)
				xBMmenudown( 0, (XtPointer)b, (XtPointer)0);    /*close last BM menu*/
			xBMcatPopup( toplevel);
			xBMdlnKeeptextReset();
			break;

		/*--- Dlt-cabine is demanded */
		case BMDLTCHOOSE:
			xBMdltPopup( toplevel);
			break;

		/*--- booking is OK, close windows */
		case BMEND:
/*!!!**** auto info initiated by DBI *****************************
			if ((ACTIONTYP == INFOTXT) && (laenge != 0) )
				xUItextshell( aktparent, _MSG_INFO, entries );
******/
			xUIinfo( 0, (XtPointer)0, (XtPointer)0 );  /* ??????? provisorisch */

			/*--- disable previous BM menu ---*/
			if (b)
				xBMmenudown( 0, (XtPointer)b, (XtPointer)0);    /*close last BM menu*/
			xBMdlnKeeptextReset();
			break;

		/*--- immediat call feature - is only a dialog popup */
		case IMMEDIATCALL:
			if (DebugFlag)
				PSSYSdebug(NULL, NULL, "immediatcall");
			if (!comm.datalen)
				comm.buffer = 0;
			xUIimmediatCall(comm.buffer, aktparent);
			break;

		/*--- clean a field or a whole mask */
		case DELETEFIELD:
		case DELETEMENU:
			break;

		/*--- Select to write for one item (like order-no in arrangement) */
		case ONEITEM:
			XtSetArg(wargs[0], XmNvalue, entries);
			XtSetValues(a->field[feldnr], wargs, 1);
			break;

		case NEXTMENU:
			aktfield[aktmenuz] = feldnr;
			a->enter = FALSE;
			a->editfeld = FALSE;
			a->alreadywrite = TRUE;
			/*--- set menu disable and color during select --*/
			xUImenufeld(a, a->field[feldnr], FALSE, FALSE, FALSE, FALSE);
			xUInewlevel(a->field[feldnr], 0, 0);
			break;


		/*--- GRAPHIC -----------------------------------------------------*/
		case GRACHOOSE:
			if (b)
			{
				f = bm_aktfield;
				XmTextSetString( b->Wgfields[f], outcomm);
			}
			else if (a)
			{
				f = aktfield[aktmenuz];
				XmTextSetString( a->field[f], outcomm);
			}
			break;

		case GRAREFRESH:
			(void)xGRread_regions_zustand();
			break;

		case GRASELECT:
		case GRAINPUT:
			if (b)
			{
				/*--- disable current BM menu ---------------*/
				bm_aktfield = feldnr;
				b->enter = FALSE;
				b->editfeld = FALSE;
				b->alreadywrite = TRUE;
				xBMmenufeld( b, b->Wgfields[bm_aktfield], FALSE, FALSE, FALSE, FALSE);
			}
			else if (a)
			{
				aktfield[aktmenuz] = feldnr;
				a->enter = FALSE;
				a->editfeld = FALSE;
				a->alreadywrite = TRUE;
				/*--- set menu disable and color during select --*/
				xUImenufeld( a, a->field[feldnr], FALSE, FALSE, FALSE, FALSE);
			}
			XFlush(display);
			xGRchangetyp( grajobflag );
			break;

		case GRASEND:           /*--- quit after acknoledge of DB ---*/
			xGRquit_graphic();
			break;

		case OPTIONTOGGLE: 		/*--- quit after acknoledge of DB ---*/
			break;

		default:
/*			xUIfehler(XUINOCOMM, 0);  ???? count inputs to avoid overrun !*/
			break;

		}/*end switch*/
}
