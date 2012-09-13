/*D***********************************************************
 * Modul:		GUI - Dialog                         umenustr.c
 *                                                            
 *					Strings from/to fields 
 *             DB to menufields or menufields to DB                                               
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************
 */

#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/umenustr.c,v 1.2 2008-11-02 19:55:42 mwn Exp $";


/*F--------------------------------------------------------------------------
 *  Function:	xUImenustr 
 *					Get strings from fields or from twin-list
 *					which exist as long as the menu is popuped                                              
 *					Check memory and write into outcomm buffer                                           
 *					
 *  In:			-the concerned menu
 *  Return:		-number of chars    
 *---------------------------------------------------------------------------
 */
long xUImenustr( MENU *a)
{
	extern	char *outcomm;
	extern	long maxoutcomm;
	extern	ApplicationData app_data;

	int			i, j;
	char			str[_TEXTLEN], *ptr, *beg;
	Boolean		flag = TRUE;
	long			len,  totlen,  effectlen, numberItems, tmplen;
	char			*ptext;

	if (a->anz < 1)
		return(0);

	/*---- Total max length for allocation only -----------------------*/
	totlen = 0;
	for (i=0; i<a->anz; i++)
	{
		if (a->buttontype[i] == TWINSELFIELD)
			{
			tmplen = xUICtwinGetItemsLength();
			if (tmplen < 1)     /* if zero set it to a default for security */
				tmplen = _TEXTLEN;
			totlen += tmplen;
			}
		else if (a->buttontype[i] == MEDITFIELD) 
			totlen += _TEXTLEN * 10 ;
		else
			totlen += _TEXTLEN ;
	}
	outcomm = (char *)xUIalloc( (void *)outcomm, &maxoutcomm, app_data.maxdataout,
										 totlen, sizeof(char) );


	/*--- Write number of fields of menu ----------------------------*/
	effectlen = 0 ; 
	beg = outcomm ;
	len = sprintf( beg, "%d\n", a->anz); 
	beg += len ; 
	effectlen += len ; 

	/*--- Write all fields of menu, count effective len -------------*/
	for ( i=0;  i < a->anz;  i++ )
		{
		/*--- the Twin has its proper storage ---------------*/
		if (a->buttontype[i] == TWINSELFIELD ) 
			{
			len = xUICtwinGetItems(beg);
			if (len == 0)
				{
				/*--- get and copy field stuff ----*/
				ptext = XmTextGetString( a->field[i] );
				len = strlen(ptext);
				if (len > 0)
					{
					for (j=0, ptr=ptext;  j<len;  j++)
						 *beg++ = *ptr++;
					/*--- add separator ---------------*/
					*beg++ = '\t';
					effectlen += len + 1; 
					}
				else
					{
					*beg++ = '\t' ;
					effectlen += 1 ;
					}
				XtFree((void *)ptext);
				}
			else
				{ 
				beg += len ; 
				*beg++ = '\t' ;                         /* replace \0 delim */
				effectlen += len +1 ;
				}
			}
		else   /*--- default or only ONE item is auto-selected */
			{
			/*--- get and copy field stuff ----*/
			ptext = XmTextGetString( a->field[i] );
			len = strlen(ptext);
			for (j=0, ptr=ptext;  j<len;  j++)
				 *beg++ = *ptr++;
			XtFree((void *)ptext);
			/*--- add separator ---------------*/
			*beg++ = '\t';
			effectlen += len + 1; 
			}
	}

	return( effectlen );
}




/*F--------------------------------------------------------------------------
 *  Function:	xUIstrmenu ()
 *					copy the DB data into menu fields 
 *  In:			-the menu, the data to be copied 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUIstrmenu(MENU *a, char *entries)
{
	register int i;
	char		    *str, *atr, *rtr;

	for (str=entries, i=0; i<a->anz; i++)
		{
		atr = str;
		/*--- replace \t with \0 at end of field string-------*/
		while (*str != '\t' && *str!= NULL)
			str++;
		*str = NULL;

		/*--- remove trailing blanks -------------------------*/
		for (rtr=str-1; rtr!=atr-1 && *rtr==' '; rtr--)
			*rtr=NULL;

		XmTextSetString( a->field[i], atr);

		str++;
		}
}

