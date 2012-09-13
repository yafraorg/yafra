/*D*********************************************************** 
 * Modul:     GUI - dialog        uoutmenu.c                 
 *                                                             
 *            Modify, restore the output menu (popup)          
 *                                                             
 *
 *                                                             
 * Copyright: yafra.org, Basel, Switzerland      
 *************************************************************
 */
#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uoutmenu.c,v 1.2 2008-11-02 19:55:43 mwn Exp $";

/*------------------------ EXTERNALS- -------------------------------------*/
extern	MENU		menu[];
extern	int		OUTtype[], OUTupdt[], OUTinpt[], OUTline[] ;
extern	int		OUTcols[], OUTglob[], OUTzuob[] ;
extern	char *	OUTlab[] ;


/*------------------------ PROTOTYPES -------------------------------------*/
static void		xUIoutmenu( MENU *a, char *pBuf);
static void		xUIsaveFieldTexts( MENU *a);
static void		xUIrestoreFieldTexts( MENU *a);
static int		xUIinitFieldTexts( MENU *a, char *pBuf );


/*------------------------ GLOBALS ----------------------------------------*/
int		*NEWLevel, *NEWtype, *NEWupdt, *NEWinpt;	
int		*NEWline , *NEWcols, *NEWglob, *NEWzuob;	
char		**NEWlab; 
int		savedAnz = 0;		/* saved nb of push buttons */ 
char		**savedField; 


/*------- DLN ------------------------------*/
char outputTestBuffer[200] ="\
1\n4\nRechnung\tDatei\tAnfrage\tOption\t\
2\n2\n1\tBuchung\t2\t1\n\
2\tGruppe\t3\t0\n\
\0" ;	






/*F--------------------------------------------------------------------------
 *  Function:	xUIoutputnew ()
 *					-Save field text for later restore
 *					-Update normal output menu by closing old and popup a new
 *  In:			-the output menu
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void  xUIoutputnew( MENU *a)
{
	char		rec[RECLAENGE];
	char		*ptext;
	int		len; 


	/*--- get strings of Oblig fields -------*/
	len = xUIinitFieldTexts( a, comm.buffer) ;    

	/*---- check first call ---------*/
	if (savedAnz == 0)  								/* original anz saved once   */
		savedAnz = a->anz ; 							/* nothing to remove at init */
	/*---- save things --------------*/
	xUIsaveFieldTexts(a);  

	xUIoutmenudown( a);								/* remove added items if any */
	xUImenudown(0, (XtPointer)a, 0 );		 	/* close output menu         */
	if ((comm.datalen - len) != 1)
		xUIoutmenu( a, comm.buffer + len );    	/* add  new buttons          */
	xUIcallpopup(0, (XtPointer)a, 0 );			/* raise new output          */ 

	/*---- restore ------------------*/
	xUIrestoreFieldTexts(a);   
}



/*F--------------------------------------------------------------------------
 *  Function:	xUIoutmenudown ()
 *					-destroy variable output menu if any
 *					-free memory 
 *					-restore original OUTxxx pointers 
 *  In:			-the output menu
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void  xUIoutmenudown( MENU *a)
{
	int		j; 

	/*--- restore only when revamped --------------*/
	if (savedAnz > 0)
	{
		/*--- free added part of out menu --------------*/
		for  (j=savedAnz;  j<a->anz;  j++)
		{
			XtFree((void *)NEWlab[j] );
		}
		/*--- something added --------------*/
		if (a->anz > savedAnz)
		{
			XtFree((void *)NEWlab );	NEWlab = 0;
			XtFree((void *)NEWtype);	NEWtype = 0;
			XtFree((void *)NEWupdt);	NEWupdt = 0;
			XtFree((void *)NEWinpt);	NEWinpt= 0;
			XtFree((void *)NEWline);	NEWline = 0;
			XtFree((void *)NEWglob);	NEWglob = 0;
			XtFree((void *)NEWcols);	NEWcols = 0;
			XtFree((void *)NEWzuob);	NEWzuob = 0;

			/*--- restore menu members ----------*/
			a->anz			= savedAnz ;
			a->buttontype	= OUTtype ;	
			a->suchfields	= OUTupdt ;
			a->inpfields	= OUTinpt ;
			a->anzlines		= OUTline ;
			a->anzcolumns	= OUTcols ;
			a->vonglobal	= OUTglob ;
			a->zuobutton	= OUTzuob ;
			a->label			= OUTlab ;
		}
	}
}



/* *********************** STATIC FUNCTIONS *********************************/

/*F--------------------------------------------------------------------------
 *  Function:	xUIsaveFieldTexts ()
 *					-sve the current texts of the output fields
 *  In:			-the output menu
 *---------------------------------------------------------------------------
 */
static void  xUIsaveFieldTexts( MENU *a)
{
	int		j; 
	char		*ptext; 

	/*--- allocate mem for text ptrs -----*/
	savedField  = (char **)XtMalloc( savedAnz * sizeof(char *));
	for  (j=0; j<savedAnz; j++)
	{
		ptext = XmTextGetString( a->field[j] );
		savedField[j] = (char *)XtMalloc( (strlen(ptext)+1) * sizeof(char));
		strcpy( savedField[j], ptext ); 
		XtFree( (void *)ptext); 
	}
}


/*F--------------------------------------------------------------------------
 *  Function:	xUIrestoreFieldTexts ()
 *					-sve the current texts of the output fields
 *  In:			-the output menu
 *---------------------------------------------------------------------------
 */
static void  xUIrestoreFieldTexts( MENU *a)
{
	int		j; 

	/*--- restore texts ----*/
	for  (j=0; j<savedAnz; j++)
	{
		XmTextSetString(a->field[j], savedField[j] );
		XtFree( (void *)savedField[j]); 
	}
	XtFree( (void *)savedField);
}



/*F--------------------------------------------------------------------------
 *  Function:	xUIinitFieldTexts()
 *					-init the output fields with DB strings 
 *  In:			-the output menu
 *---------------------------------------------------------------------------
 */
static int  xUIinitFieldTexts( MENU *a, char *pBuf )
{
	int		i, j; 
   int 	   f1;                    /* fields */
	char		rec[_CHAR80];
	char	   *pBegin, *pField;

	pBegin = pBuf;
	/*--- get protocol index ----------------*/
	for ( i=0;  *pBuf != '\n';  i++, pBuf++)
		rec[i] = *pBuf ;
	rec[i] = *pBuf ;
	sscanf (rec, "%d[^\n]", &f1 );
	pBuf++;													/* skip \n */

	/*--- get nb of fields ------------------*/
	for ( i=0;  *pBuf != '\n';  i++, pBuf++) 
		rec[i] = *pBuf ;
	rec[i] = *pBuf ;
	sscanf (rec, "%d[^\n]", &f1 );
	pBuf++;													/* skip \n */

	/*--- jump to end of field strings ---------*/
	for ( i=0;  i<f1;  i++)
	{  
		pField = pBuf;
		while (*pBuf != '\t' )
			pBuf++;                 
		*pBuf = NULL;                                
		XmTextSetString(a->field[i], pField);
		pBuf++;                                   /* skip null */           
	}
                                     /* skip \n */
	/*--- get next protocol index ----------------*/
	for ( i=0;  *pBuf != '\n';  i++, pBuf++)
		rec[i] = *pBuf ;
	rec[i] = *pBuf ;
	sscanf (rec, "%d[^\n]", &f1 );
	pBuf++;													/* skip \n */

	return( pBuf - pBegin); 
}



/*F--------------------------------------------------------------------------
 *  Function:	xUIoutmenu ()
 *					-create variable menu layout with x DB buttons  
 *					-Get x, number of bundles
 *					-a bundle is: nr \t label \t fieldtyp \t updt \n
 *					-Alocate memory for x bundles
 *					-Keep label etc.. for the first existant button
 *					-Revamp to new arrays 
 *					-Normalize the length of the labels to longest
 *					-
 *  In:			-the output menu a
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
static void  xUIoutmenu( MENU *a, char *pBuf)
{
	int		i, j, k, nbButtons, nbTotal, labelchars ;
	char	   labeltext[_LABELLEN+1] ; 
   int 	   f1, f2, f3 ;                    /* fields */
	char	   *labelPtr ;
	char		rec[_CHAR80];

	if (pBuf == NULL || *pBuf == NULL)
		return;

	/*---- get number of fields ------------*/
	for ( i=0;  *pBuf != '\n';  i++, pBuf++)  
	{
		rec[i] = *pBuf ;
	}
	rec[i] = *pBuf ;
	pBuf++;													/* skip \n */
	sscanf (rec, "%d[^\n]", &f1 );
	nbButtons = f1 ; 
	nbTotal = nbButtons + savedAnz ;							/* add button 0 */

	/*---- allocations for members ---------------------*/
	NEWlab  = (char **)XtMalloc( nbTotal * sizeof(char *));
	NEWtype = (int *)XtMalloc( nbTotal * sizeof(int));
	NEWupdt = (int *)XtMalloc( nbTotal * sizeof(int));	
	NEWinpt = (int *)XtMalloc( nbTotal * sizeof(int));
	NEWline = (int *)XtMalloc( nbTotal * sizeof(int));
	NEWglob = (int *)XtMalloc( nbTotal * sizeof(int));
	NEWcols = (int *)XtMalloc( nbTotal * sizeof(int));
	NEWzuob = (int *)XtMalloc( nbTotal * sizeof(int));

	/*---- copy stuff from existent buttons ------------*/
	for  (j=0; j<savedAnz; j++)
	{
		NEWlab[j]  = OUTlab[j] ; 
		NEWtype[j] = OUTtype[j] ; 
		NEWupdt[j] = OUTupdt[j] ; 
		NEWinpt[j] = OUTinpt[j] ; 
		NEWline[j] = OUTline[j] ; 
		NEWcols[j] = OUTcols[j] ; 
		NEWglob[j] = OUTglob[j] ; 
		NEWzuob[j] = j ; 			/* MUST be 0 */
	}

	/*---- get all members BUT the first button --------*/
	for  (j=savedAnz; j<nbTotal; j++)
	{
		/*--- read a bundle -------------*/
		for ( i=0; *pBuf != '\n' ; i++, pBuf++)  
		{
			rec[i] = *pBuf ;
		}
		rec[i] = *pBuf ;									/* copy \n for sscanf */
		pBuf++ ;												/* skip \n */

		/*-- extract params and label, '\0' is added! ---- */
		sscanf (rec, "%d\t%[^\t]%d\t%d%[^\n]",  &f1, labeltext, &f2, &f3 ); 

		/*-- set new Button label ------------ */
		labelPtr = (char *)XtMalloc(_LABELLEN+1);
		if (labelPtr)
			NEWlab[j] = labelPtr ;  
		else
			xUImainStop( -1);
		strcpy ( NEWlab[j] , labeltext);

		/*-- set new menu stuff ------------ */
		NEWtype[j] = f2 ; 
		NEWupdt[j] = FALSE ; 
		NEWinpt[j] = f3 ; 
		NEWline[j] = 1 ; 
		NEWcols[j] = 60 ; /* mw 2.3.94 set it to this instead of 30 */
		NEWglob[j] = -1 ; 
		NEWzuob[j] = j  ; /*next after first */
	}/*for*/

	/*--- revamp old menu elements to new ----------*/
	a->anz			= nbTotal ;                           /* new anz */
	a->buttontype	= NEWtype ;
	a->suchfields	= NEWupdt ;
	a->inpfields	= NEWinpt ;
	a->anzlines		= NEWline ;
	a->anzcolumns	= NEWcols ;
	a->vonglobal	= NEWglob ;
	a->zuobutton	= NEWzuob ;
	a->label			= NEWlab ;

	/*-- find longest pushbutton label string -------*/ 
	for (j=0, labelchars=0; j<a->anz; j++)
		{
		k = strlen(NEWlab[j]);
		labelchars = labelchars > k ? labelchars : k ;
		}
	/*-- space padding till longest label ------*/ 
	for (j=0; j<a->anz; j++)
		{
		for (k=strlen(NEWlab[j]); k<labelchars; k++)
			{
			NEWlab[j][k] = ' ';
			}
		NEWlab[j][labelchars] = (char)0;
		}
}





/* *********************** TEST FUNCTIONS *********************************/

/*F--------------------------------------------------------------------------
 *  Function:	xUIoutputtest ()
 *					-simulate a DB data expedition
 *     			-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xUIoutputtest( Widget w, XtPointer b, XtPointer wdata)
{
	extern int        aktmenu[];
	extern int        aktmenuz;
	extern MENU       menu[];

	MENU *a;

	a = &menu[aktmenu[aktmenuz]];

	xUIoutputnew( a); 

}


