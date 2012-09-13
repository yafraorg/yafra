/*IH***********************************************************
 * File:       GUI Dialog                              uctwin.h
 *
 * Description:   Definition and Prototypes (ANSI C)
 *                for a Twin class (list with extended selection)
 *                All users of a Select must include this file.
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 *
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/uctwin.h,v 1.2 2008-11-02 19:55:32 mwn Exp $

 */


/*T------------------------ TYPE DEFINITIONS --------------------------------*/
typedef struct {
	Widget		Wgpopup;								/* shell parent                */
	Widget		Wgform;								/* form containing src and dst */
	Widget		Wgsource;							/* source list of items        */
	Widget		Wgdest;								/* destination list of items   */
	Boolean		chosenFlag;							/* user has chosen something   */
} TWINLIST ;


/*P------------------------ PROTOTYPES --------------------------------------*/
void		xUICtwinPopup( Widget parent, char * entries );
long		xUICtwinGetItems( char * pBuf);
long		xUICtwinGetItemsLength();
void		xUICtwinDeleteItems( TWINLIST *aList);
void		xUICtwinDestroy( TWINLIST *aList);




