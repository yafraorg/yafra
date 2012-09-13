/*D***********************************************************
 * Modul:     DBI - database insert                           
 *            Texte
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xTXTwrite.c,v 1.2 2008-11-02 19:55:40 mwn Exp $";

int xTxtWrite(char *buffer)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern TEXTE txt;
	SPRACHEN *sprachen;

	char query[_QUERYLEN];
	char *ptr, *oldptr;

	int anzahl, anzchar, i;
	int status=(int)MPOK;
	int first = (int)TRUE;

	if (ACTIONTYP == (unsigned char)MPDELETE)
		{
		/* delete TEXTE and return */
		if (txt.textid != (int)_UNDEF)
			{
			status = MPAPIdeleteEntry((int)_TEXTE, (char *)&txt);
			txt.textid = (int)_UNDEF;
			}
		return((int)_UNDEF);
		}
	else if (txt.textid != (int)_UNDEF && *buffer != NULL)
		{
		/*	delete old one and insert a new one */
		status = MPAPIdeleteEntry( (int)_TEXTE, (char *)&txt );
		}
	else if (txt.textid == (int)_UNDEF && *buffer != NULL)
		{
		/*	get new id for new insert */
		txt.textid = MPAPIid_new((int)_TEXTE, sprache, (int)txt.typ);
		}
	else
		{
		txt.textid = (int)_UNDEF;
		return((int)_UNDEF);
		}

	/* make security check finaly */
	if (txt.textid == (int)_UNDEF || *buffer == NULL)
		{
		txt.textid = (int)_UNDEF;
		return((int)_UNDEF);
		}

	if (ACTIONTYP == (unsigned char)UPDATE)
		(void)sprintf( query, _SEL_ONE_SPRACHE, sprache );
	else
		(void)sprintf( query, _SEL_ALL_SPR );

	status = MPAPIdb_sqlquery(_SPRACHEN, &sqlmem.buffer, query, &anzahl,
	                           &sqlmem.datalen, &sqlmem.alloclen);
	sprachen = (SPRACHEN *)sqlmem.buffer;
	if (status != (int)MPOK)
		{
		txt.textid = (int)_UNDEF;
		return(txt.textid);
		}

	/*	Den Text in der Default Sprache
	 *	in alle vorhandenen Sprachen eintragen */
	for ( i=0; i < anzahl; i++ )
		{
		/* sprachen ohne Helppath ueberspringen (wie bei InsertBEZ) */
		if (sprachen[i].dialog == (int)FALSE)
			continue;
		txt.s_id   = sprachen[i].s_id;
		txt.textnr = (int)0;

		for ( oldptr=ptr=buffer, anzchar=(int)0; ;ptr++ )
			{
			if ( *ptr == '\n'  || *ptr == '\t' || *ptr == NULL )
				{
				txt.textnr++;
				(void)memcpy( (void *)txt.text, (void *)oldptr, (size_t)anzchar );
				txt.text[anzchar]=(char)NULL;
				status = WriteEntry( (int)_TEXTE, (char *)&txt, (BEZEICHNUNG *)NULL );
				if (status == (int)MPERROR)
					{
					txt.textid=(int)_UNDEF;
					break;
					}
				oldptr = ptr+1;
				anzchar = (int)0;
				}
			else
				anzchar++;
			if ( *ptr == (char)NULL )
				break;
			}
		}

	return(txt.textid);
}
