/*IH***********************************************************
 * File:        GUI dialog                           ucselect.h
 *
 * Description:   Definition and Prototypes (ANSI C)
 *                for a Select class (list with single selection)
 *                All users of a Select must include this file.
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 *
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/ucselect.h,v 1.2 2008-11-02 19:55:33 mwn Exp $

 Log Information:
 $Log: ucselect.h,v $
 Revision 1.2  2008-11-02 19:55:33  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:22:49  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/29 13:08:01  mw
 new database release 2

 * Revision 1.3  94/02/18  14:43:21  14:43:21  ja (Jean-Marc Adam)
 * DOS name conversion
 * 
 * Revision 1.2  93/08/21  00:30:15  00:30:15  ja (Jean-Marc Adam)
 * update menu struct
 * 
 * Revision 1.1  93/05/11  13:27:34  13:27:34  ja (Jean-Marc Adam)
 * Initial revision
 * 
 * 
 */


/*T------------------------ TYPE DEFINITIONS --------------------------------*/
typedef struct {
	XmString		*tab;									/* table of items              */
   int			*select;								/* selected items              */
   char			selectRec[RECLAENGE];			/* selected text               */
	Widget		Wgpopup;								/* shell parent                */
	Widget		Wglist;								/* list of items               */
	Boolean		chosenFlag;							/* user has chosen something   */
} SELECTLIST ;


/*P------------------------ PROTOTYPES --------------------------------------*/
void				xUICselectPopup( Widget parent, char * entries );
void				xUICselectDestroy( SELECTLIST *aList);


