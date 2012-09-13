/*D*************************************************************************
 * Modul:			GUI - Dialog		   ulabels.c 
 *            
 * Description:	memory allocation for labels 
 *						DB label string copy function 
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 ***************************************************************************
 */
#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ulabels.c,v 1.2 2008-11-02 19:55:44 mwn Exp $";

/*E------------------------ EXTERNALS --------------------------------------*/
extern char  *xgrLabelTable [] [XGRLABMAXTEXTS];  
extern char  *xuiLabelTable [] [XUILABMAXTEXTS];  
extern char  *xbmLabelTable [] [XBMLABMAXTEXTS];  
extern MENULIST	pulldownlist[];
extern MENULIST	grouplist[][ANZ_MENU];
extern MENU			glob;
extern MENU			menu[];
extern int			objType;             /* cross reference DBobject-UIwindow */								     

/*F----------------------- PROTOTYPES --------------------------------------*/
static void xUIremoveTrailingSpaces(char *, int);

/*F--------------------------------------------------------------------------
 *  Function:	xUIlabelsPointerInit ()
 *					-allocate memory for each label string
 *					-init pointers of label tables
 *  In:			- 
 *  out:			-xgr, xui, xbm LabelTable pointers 
 *  Return:		-success flag 
 *---------------------------------------------------------------------------
 */
int xUIlabelsPointerInit(void)
{
   char   * labelPtr; 
   int      i, j; 
	
	/*-- init graphic labels ---------*/
	for (i=0; i < XGRLABMAXTYPES; i++)
	{
		for (j=0; j < XGRLABMAXTEXTS; j++)
		{
		   labelPtr = (char *)XtMalloc(_LABELLEN+1);
			if (labelPtr)
			{
		      xgrLabelTable[i][j] = labelPtr ;
				*labelPtr++ = '*';	*labelPtr++ = '\0';
			}  
         else
				return( _NOTOK);
		}
	}
	/*-- init User Interface labels ---------*/
	for (i=0; i < XUILABMAXTYPES; i++)
	{
		for (j=0; j < XUILABMAXTEXTS; j++)
		{
		   labelPtr = (char *)XtMalloc(_LABELLEN+1);
			if (labelPtr)
			{
		      xuiLabelTable[i][j] = labelPtr ;  
				*labelPtr++ = '*';	*labelPtr++ = '\0';
			}  
         else
				return( _NOTOK);
		}
	}
	/*-- init Booking Mask labels ---------*/
	for (i=0; i < XBMLABMAXTYPES; i++)
	{
		for (j=0; j < XBMLABMAXTEXTS; j++)
		{
		   labelPtr = (char *)XtMalloc(_LABELLEN+1);
			if (labelPtr)
			{
		      xbmLabelTable[i][j] = labelPtr ;  
				*labelPtr++ = '*';	*labelPtr++ = '\0';
			}  
         else
				return( _NOTOK);
		}
	}
	return( _OK);
}




/*F--------------------------------------------------------------------------
 *  Function:	xUIlabelsFromBank ()
 *					copy normal labels from databank into tables  
 *					format: line must begin with a digit
 *					label string is assumed to have correct length            
 *            
 *  In:       -pBuf to comm.buffer,  prog the program class UI,GR,BM.. 
 *  out:      -label pointer tables are set 
 *  Return:   -
 *---------------------------------------------------------------------------
 */
void xUIlabelsFromBank(char *pBuf, int prog)
{
	extern int DebugFlag;

	int    i;
	char   rec[_RECORDLEN], *ptr ;
	char   labeltext[_LABELLEN+1] ; 
   int    f1, f2, f3, f4 ;                   /* fields */
   char  *labelPtr; 

	if (DebugFlag)
		PSSYSdebug(NULL, NULL, "reading labels from DB");

	/*---- work till end of record -------------------------------*/
	while  ( *pBuf != 0 )
		{
		/*--- read a label bundle -------------*/
		for ( i=0;   *pBuf != '\n';  i++, pBuf++)  
   	   {
			rec[i] = *pBuf ;
			}
		rec[i] = 0 ;										/* force termination '\0' */
		pBuf++ ;												/* skip \n */

		/*--- bail out empty lines ----------*/
		if ( i>0 )
			{
			labeltext[0] = 0;

			/*-- extract destinations and text, '\0' is added! ---- */
			sscanf (rec, "%d\t%d\t%d\t%d\t%[^0]",  &f1, &f2, &f3, &f4, labeltext ); 

			/*-- check prg class labels  ------------ */
			if ((f1 ==_XGR) && (f2>=0))
				strcpy (xgrLabelTable[f2][f3], labeltext); 
			if ((f1 ==_XUI) && (f2>=0))
				strcpy (xuiLabelTable[f2][f3], labeltext); 
			if ((f1 ==_XBM) && (f2>=0))
				strcpy (xbmLabelTable[f2][f3], labeltext); 
			}
		}
}


/*F--------------------------------------------------------------------------
 *  Function:	xUIlabelsDefault ()
 *					read default labels in tables  from app_data.labelfile 
 *					! app_data resources must have been set, DEFlabelfile !
 *					format: line must begin with a digit
 *					example: 181 200 12  0  1  Anfangs - Datum  
 *  In:       -
 *  out:      -label pointer tables are set 
 *  Return:   -
 *---------------------------------------------------------------------------
 */
void xUIlabelsDefault(char* labelFileName)
{
	extern int DebugFlag;

	FILE  *fp;
	int    i = 0;
	char   rec[_RECORDLEN], *ptr;
	char   labeltext[_LABELLEN+1] ; 
   int    f1, f2, f3, f4, f5 ;          /* fields */
   char  *labelPtr; 
	char   tmpbuf[_RECORDLEN];

	if (DebugFlag)
		PSSYSdebug(NULL, NULL, "read default from label file %s", labelFileName);

   /*--- process whole file --------------*/
	fp = fopen( labelFileName, _P_READ_);
	if (fp)
		{
      /*--- read all lines  --------------*/
		while (fgets(rec, sizeof(rec), fp)) 
   	   {

#ifdef COMPILE
         /*-- force line termination with '\0' ---- */
			ptr = &rec[strlen(rec)-1];
#ifdef ps_dos
			if (*ptr == '\n')  *--ptr = 0;         /* cr, lf */
#else
			if (*ptr == '\n')  *ptr = 0;           /* lf */
#endif
#endif


			/*-- extract destinations and text, '\0' is added! ---- */
			sscanf (rec, "%d%*[ ]%d%*[ ]%d%*[ ]%d%*[ ]%d%[^\n\r]",
                       &f1,   &f2,   &f3,   &f4,  &f5, labeltext ); 
			xUIremoveTrailingSpaces(labeltext, (int)41);

			/*-- check prg class labels  ------------ */
			if ((f1==_XGR) && (f2>=0))
				strcpy (xgrLabelTable[f2][f3], labeltext); 
			if ((f1==_XUI) && (f2>=0))
				strcpy (xuiLabelTable[f2][f3], labeltext); 
			if ((f1==_XBM) && (f2>=0))
				strcpy (xbmLabelTable[f2][f3], labeltext); 
			}
		fclose(fp);
		}
	else  /*-- fopen failed ----------*/
		{
		(void)sprintf(tmpbuf, "\nMARCO POLO error: cannot open labelfile %s", labelFileName);
		perror(tmpbuf); 
		}
}

/*F--------------------------------------------------------------------------
 *  Function:	xUIlabelsFree ()
 *					-dis-allocate memory for each label string
 *					-reset pointers of label tables
 *  In:			- 
 *  out:			-xgr, xui, xbm LabelTable pointers 
 *  Return:		-success flag 
 *---------------------------------------------------------------------------
 */
void xUIlabelsFree(void)
{
	extern int DebugFlag;

	char   * labelPtr; 
	int      i, j; 

	if (DebugFlag)
		PSSYSdebug(NULL, NULL, "free up memeory for labels");	

	/*-- init graphic labels ---------*/
	for (i=0; i < XGRLABMAXTYPES; i++)
	{
		for (j=0; j < XGRLABMAXTEXTS; j++)
		{
		   labelPtr = xgrLabelTable[i][j];
			if (labelPtr)
				XtFree(labelPtr); 
		}
	}
	/*-- init User Interface labels ---------*/
	for (i=0; i < XUILABMAXTYPES; i++)
	{
		for (j=0; j < XUILABMAXTEXTS; j++)
		{
		   labelPtr = xuiLabelTable[i][j];
			if (labelPtr)
				XtFree(labelPtr); 
		}
	}
	/*-- init Booking Mask labels ---------*/
	for (i=0; i < XBMLABMAXTYPES; i++)
	{
		for (j=0; j < XBMLABMAXTEXTS; j++)
		{
		   labelPtr = xbmLabelTable[i][j];
			if (labelPtr)
				XtFree(labelPtr); 
		}
	}
}




/*F---------------------------------------------------------------------
 *	Function:	xUIlabelsMenuInit 
 *					-initialize labels for pulldown and normal menus  
 *-----------------------------------------------------------------------
 */
void xUIlabelsMenuInit(void)
{
	extern int DebugFlag;

	int			g, i, j, k ;
	MENULIST		*pML; 		/* used in fast access operations */
	int			labelchars ;

	if (DebugFlag)
		PSSYSdebug(NULL, NULL, "make pulldown and normal menu labels");

	/*-- Initialize pulldown MENULIST labels -----*/ 
	for (i=0; i<ANZGROUPS+1; i++)
		{
		pML = &pulldownlist[i]; 
		pML->titel    = xuiLabelTable[_PULLDOWN][i];
		pML->mnemonic = xuiLabelTable[_PULLDOWN][i][0];
		}

	/*---- init Global menu title + labels ------------------*/
	glob.titel =  xuiLabelTable[_GLOBALMENU][0];
	for (j=0, labelchars=0; j<glob.anz; j++)
		{
		glob.label[j] = xuiLabelTable[_GLOBALMENU][j+1];
		k = strlen(glob.label[j]);
		labelchars = labelchars > k ? labelchars : k ;     /* keep longest */
		}
	/*--- space padding till longest label size ----*/
	for (j=0; j<glob.anz; j++)
		{
		for (k=strlen(glob.label[j]); k<labelchars; k++)
			{
			glob.label[j][k] = ' ';
			}
		glob.label[j][labelchars] = (char)0;
		}

	/*---- init Normal menus Title and Labels ----------------*/
	for (i=0; i<ANZ_MENU; i++)
		{
		/*-- get cross-reference type between DBObject and UIWindow --*/ 
		objType = menu[i].typ;
		/*-- init menu Title --------------------- */ 
		menu[i].titel =  xuiLabelTable[objType][0];

		/*-- init all push-buttons strings for that menu -------*/ 
		for (j=0, labelchars=0; j<menu[i].anz; j++)
			{
			menu[i].label[j] = xuiLabelTable[objType][j+1] ;
			k = strlen(menu[i].label[j]);
			labelchars = labelchars > k ? labelchars : k ;     /* keep longest */
			}
		/*-- space padding till longest label size ------*/ 
		for (j=0; j<menu[i].anz; j++)
			{
			for (k=strlen(menu[i].label[j]); k<labelchars; k++)
				{
				menu[i].label[j][k] = ' ';
				}
			menu[i].label[j][labelchars] = (char)0;
			}
		}
}


/************************ STATIC FUNCTIONS *********************************/

/*F--------------------------------------------------------------------------
 *  Function: xUIremoveTrailingSpaces ()
 *            suppress the trailing blanks in string 
 *            
 *  In:       -Ptr to string
 *  out:      -
 *  Return:   -
 *---------------------------------------------------------------------------
 */
static void xUIremoveTrailingSpaces(char *aString, int maxlen)
{
	size_t  i;

	i = strlen(aString)-1;
	if (i > maxlen)
		i = maxlen;

	/*-- find last char, begin at end, before NULL ------- */
	for (; (i > 0) && (aString[i]== ' ' ); i--)
		{ ; }															  /* find last char */
	/*-- forget spaces ------- */
	aString[i+1] = '\0' ;
}
