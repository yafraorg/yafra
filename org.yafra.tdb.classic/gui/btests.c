/*D************************************************************
 * Modul:		GUI - BM dialog		xBMtest.c
 *					test function of BM parts
 *
 * Functions:	
 * Callbacks:	
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/btests.c,v 1.2 2008-11-02 19:55:42 mwn Exp $

 Log Information:
 $Log: btests.c,v $
 Revision 1.2  2008-11-02 19:55:42  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:07  ja
 general version

 * Revision 1.4  94/02/18  10:35:40  10:35:40  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.3  93/08/20  23:54:05  23:54:05  ja (Jean-Marc Adam)
 * update
 * 
 * Revision 1.2  93/05/04  18:05:17  18:05:17  ja (Jean-Marc Adam)
 * "rev"
 * 
 * Revision 1.1  93/03/11  16:32:46  16:32:46  ja ()
 * Initial revision
 * 
 * 
*/

#include <uinclude.h>


static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/btests.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";




/*E------------------------ EXTERNAL  --------------------------------------*/


/*P------------------------ PROTOTYPES --------------------------------------*/
static void  getFileBuffer ( char *filename, char *pBuf );



/*G------------------------ GLOBAL VARIABLES --------------------------------*/

/*------- DLN ------------------------------*/
char dlnTestBuffer[_BMBUFFERMAX] ="\
1\n3\nlabel_A\tlabel_B\tlabel_C\t\n\
2\n6\n\
3\n3\n_AHV_\t_jung_\t_jung_\t\n\
4\n2\nlabel_A\tlabel_B\t\n\
5\n5\nAAAAaaaabbbb\tBBBBBBBBBbbbb\tCCCCCCCCCCCCCCCC\tDDDDDDDDDD\tEEEEEEEEE\t\n\
\0" ;	


/*------- CAT -----------------------------*/
char catTestBuffer[_BMBUFFERMAX] ="\
1\n2\nDienstleistungXX\tB_nummerYY\t\n\
\0" ;

/*	
#ifdef COMPILE
1\nColorA\tKat 1 Description\t Preis 3400.-\n\
2\nColorB\tKat 2 Description\t Preis 2400.-\n\
3\nColorC\tKat 3 Description\t Preis 1400.-\n\
\0" ;	
#endif
*/

/*------- CABI -----------------------------*/
char cabiTestBuffer[_BMBUFFERMAX] ="\
1\n3\nCABINE-1\tCABINE-2\tCABINE-3\t\n\
\0" ;



/*FT-----------------------------------------------------------------TEST----
 *  Function:	xBMdlnTest ()
 *					-test dln features 
 *					-cb function can be called from test menu if existent
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMdlnTest(Widget w, XtPointer b, XtPointer wdata)
{
	extern Widget toplevel; 

	/*-- read description file and update buffer  ----------*/
	getFileBuffer( "testdln.des", dlnTestBuffer);
 
/* printf( "DLN Buffer: %s \n", dlnTestBuffer ); */
	xBMdlnPopup( toplevel );
}




/*FT-----------------------------------------------------------------TEST----
 *  Function:	xBMcatTest ()
 *					-test cat features 
 *					-cb function can be called from test menu if existent
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMcatTest(Widget w, XtPointer b, XtPointer wdata)
{
	extern Widget toplevel; 

	/*-- read description file and update buffer  ----------*/
	getFileBuffer( "testcat.des",   catTestBuffer);
 
/* printf( "KAT-Buffer: %s \n", catTestBuffer );  */
	xBMcatPopup( toplevel );
}



/*FT-----------------------------------------------------------------TEST----
 *  Function:	xBMdltTest ()
 *					-test cat features 
 *					-cb function can be called from test menu if existent
 *  In:			-
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
XtCallbackProc xBMdltTest(Widget w, XtPointer b, XtPointer wdata)
{
	extern Widget toplevel; 

	/*-- read description file and update buffer  ----------*/
/*	getFileBuffer( "testdlt.des",   dltTestBuffer);  */
 
/* printf( "DLT-Buffer: %s \n", dltTestBuffer );   */

	xBMdltPopup( toplevel );
}





/*S----------------------- STATIC FUNCTIONS --------------------------------*/

/*FT--------------------------------------------------------------------------
 *  Function:	getFileBuffer()
 *					-get user choices from a config file
 *  In:			-filename, buffer to fill 
 *  out:			-
 *  Return:		-status 
 *---------------------------------------------------------------------------
 */
static void  getFileBuffer ( char *filename, char *pBuf )
{
	FILE  *fp;
	int		c ;

   /*--- process whole file --------------*/
	fp = fopen( filename, "r");
	if (fp)
	{
      /*--- read all lines  --------------*/
		while ( (c=fgetc(fp)) != EOF) 
			*pBuf++ = c; 

		*pBuf = '\0'; 
		fclose(fp);
	}
	else  /*-- fopen failed ----------*/
	{
		printf ( "\n BMTest: getFileBuffer cannot open file %s ", filename ); 
	}
}/**/
