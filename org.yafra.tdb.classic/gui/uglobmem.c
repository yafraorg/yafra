/*D***********************************************************
 * Modul:		GUI - dialog				uglobmem.c                                    
 *                                                            
 *					Given and index, return pointer to a member 
 *					of globdata struct.
 *                                                            
 *             Send global data members to DB                                               
 *
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************
*/
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uglobmem.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";

#include <uinclude.h>

/*F---------------------------------------------------------------------
 *	Function:	xUIglobmember 
 *					-find the pointer corresponding to index of parameter
 *					-
 *	In:			-index of parameter
 *	Out:			-pointer to parameter string
 *-----------------------------------------------------------------------
 */
char *xUIglobmember(int aIndex)
{
	extern MP_GLOBALPROFIL globprof;
	extern GLOBDATA globdata;

	char    *ptr;

	switch (aIndex)
		{
		case  0: ptr = globprof.database;	break;
		case  1: ptr = globprof.user;			break;
		case  2: ptr = globdata.bchst;		break;
		case  3: ptr = globdata.sprache;		break;
		case  4: ptr = globdata.land;			break;
		case  5: ptr = globdata.dltt;			break;
		case  6: ptr = globdata.kat;			break;
		case  7: ptr = globdata.dlt;			break;
		case  8: ptr = globdata.dlat;			break;
		case  9: ptr = globdata.dlnt;			break;
		case 10: ptr = globdata.saison;		break;
		case 11: ptr = globdata.programm;	break;
		case 12: ptr = globdata.a_zeit;		break;
		case 13: ptr = globdata.e_zeit;		break;
		case 14: ptr = globdata.p_range;		break;
		default: ptr = NULL;						break;
		}

	return(ptr);
}
