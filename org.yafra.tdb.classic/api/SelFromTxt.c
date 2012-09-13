/*D***********************************************************
 * Modul:     DBI - database select                           
 *            read a TEXT segment and put it into 
 *            a string
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlbez.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/SelFromTxt.c,v 1.2 2008-11-02 19:55:49 mwn Exp $";

int SelFromTxt(int textid , int spr , int typ , char *text )
{
	extern TEXTE txt;
	extern MEMOBJ apimem;

	TEXTE *t_ptr;

	char query[_QUERYLEN];
	char record[_RECORDLEN];
	int status=(int)MPOK, anzahl, i;

	if (textid == (int)_UNDEF)
		return((int)_UNDEF);

	(void)sprintf(query, _SELECT_TXT, textid, (short)spr, typ);
	status=MPAPIdb_sqlquery((int)_TEXTE, &apimem.buffer, query, &anzahl,
	                         &apimem.datalen, &apimem.alloclen);

	if (status == (int)MPOK)
		{
		if (anzahl > 0)
			{
			*text=NULL;
			for (i=(int)0; i<anzahl; i++)
				{
				t_ptr=(TEXTE *)&apimem.buffer[i*sizeof(TEXTE)];
				(void)copyTextTo(record, t_ptr->text, _CHAR80);
				if (i == (int)0)
					{
					(void)strcpy(text, record);
					}
				else
					{
					(void)strcat(text, "\n");
					(void)strcat(text, record);
					}
				}
			status=anzahl;
			}
		else
			{
			txt.textid=(int)_UNDEF;
			status=(int)_UNDEF;
			}
		}
	else
		{
		*text=NULL;
		txt.textid=(int)_UNDEF;
		status=(int)_UNDEF;
		}

	return(status);
}
