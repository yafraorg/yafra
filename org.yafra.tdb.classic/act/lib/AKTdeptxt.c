/**************************************************************
 * Modul:     AKT - dependent language txt/bez  AKTdeptext.c
 *            get action language-dependend texts
 *            if ok anzzus > 0 else -1
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/

/* MarcoPolo API includes */
#include <mpact.h>         /* Standart Includefile   */
#include <mpproact.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/lib/AKTdeptxt.c,v 1.3 2009-01-02 16:51:35 mwn Exp $";


/*-------------------- PROTOTYPES ------------------------------------------*/
static int SelectAktionsText(int, int, int, char *, char *);


/*-------------------- STATIC FUNCTIONS ------------------------------------*/

#define	_SELECT_AKTIONSTXT "SELECT * FROM TDBADMIN.AKTIONSTEXTE \
	WHERE TEXTID = %d AND S_ID = %d AND TYP = %d ORDER BY TEXTNR;"

#define	_SELECT_TXT "SELECT * FROM TDBADMIN.TEXTE \
	WHERE TEXTID = %d AND S_ID = %d AND TYP = %d ORDER BY TEXTNR;"



/*SF-------------------------------------------------------------------------
 *  function:	AKTobjtxt
 *  				get text from database in correct language
 *
 *  In:			-action_typ, text id, buffer for text, margin
 *  out:			-
 *  Return:		-completion code
 *---------------------------------------------------------------------------
 */
int AKTobjtxt( int typ, int textid, char *buffer, char *leftmargin)
{
	extern int aktuellesprache;

	int anzzus;
	int status = MPOK;

	*buffer = '\0';
	anzzus = (int)UNDEF;
	anzzus = SelectAktionsText(textid, aktuellesprache, typ, buffer, leftmargin);
	if ( anzzus <= (int)0 )
		anzzus = SelectAktionsText(textid, DEFAULTLANGUAGE, typ, buffer, leftmargin);
	return(anzzus);
}


/*SF-------------------------------------------------------------------------
 *  function:	AKTobjtxtFormat
 *  				get text AND format from database in correct language
 *					FORM_SEPAR ($) separates the text from the format
 *  In:			-action_typ, text id
 *  out:			-buffer for text, margin, format
 *  Return:		-completion code
 *---------------------------------------------------------------------------
 */
int AKTobjtxtFormat( int typ, int textid, char *buffer, char *format)
{
	extern int aktuellesprache;

	int anzzus;
	int status = MPOK;
	char		*ptr ;

	/*-- init -------*/
	*buffer = '\0';
	*format = '\0';
	anzzus = (int)UNDEF;

	/*-- Get text from db ----*/
	anzzus = SelectAktionsText(textid, aktuellesprache, typ, buffer, NOMARGIN);
	if ( anzzus <= (int)0 )
		anzzus = SelectAktionsText(textid, DEFAULTLANGUAGE, typ, buffer, NOMARGIN);

	/*-- Check if format information is in text -----*/
	if ((ptr = strchr( buffer, FORM_SEPAR)) != NULL)
	{
		*ptr++ = '\0';
		strcpy(format, ptr);
	}

	return(anzzus);
}




/*F--------------------------------------------------------------------------
 *  Function:	SelectAktionsText ()
 *					get texts in specified language
 *
 *  In:			-textid, type of table, dialogsprache, aktuellesprache, buffer
 *  out:			-
 *  Return:		-nb of texts
 *---------------------------------------------------------------------------
 */
static int SelectAktionsText(int textid, int spr, int typ,
                             char *text, char *leftmargin)
{
	/*!!! danger !!*/
	extern MEMOBJ sqlmem;

	TEXTE txt;
	TEXTE *t_ptr;
	AKTIONSTEXTE atxt;
	AKTIONSTEXTE *at_ptr;

	char query[RECLAENGE];
	char record[RECLAENGE];
	char message[RECLAENGE];
	int status=(int)MPOK, anzahl, i;

	if (textid == (int)_UNDEF || text == NULL)
		return((int)_UNDEF);

	*text=NULL;

	if (typ >= (int)_AUFTRAG_TYP && typ <= (int)_COMMON_TYP)
		{
		(void)sprintf(query, _SELECT_AKTIONSTXT, textid, spr, typ);
		status = MPAPIdb_sqlquery((int)_AKTIONSTEXTE, &sqlmem.buffer, query,
		         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
		if (status != (int)MPOK || anzahl < 0)
			{
			atxt.textid=(int)UNDEF;
			return((int)_UNDEF);                                /* >>>> exit */
			}
		/*--- get and concatenate texts -------------*/
		for (i=(int)0; i<anzahl; i++)
			{
			at_ptr = (AKTIONSTEXTE *)&sqlmem.buffer[i*sizeof(AKTIONSTEXTE)];
			(void)copyTextTo(record, at_ptr->text, _TEXTLEN);
			if (i == (int)0)
				(void)sprintf(text, "%s%s", leftmargin, record );
			else
				{
				(void)strcat(text, _P_EOL_);
				(void)strcat(text, leftmargin);
				(void)strcat(text, record);
				}
			}
		}
	else
		{
		(void)sprintf(query, _SELECT_TXT, textid, (short)spr, typ);
		status=MPAPIdb_sqlquery((int)_TEXTE, &sqlmem.buffer, query, &anzahl,
	                         &sqlmem.datalen, &sqlmem.alloclen);
		if (status != (int)MPOK || anzahl < 0)
			{
			txt.textid=(int)UNDEF;
			return((int)_UNDEF);
			}
		for (i=(int)0; i<anzahl; i++)
			{
			t_ptr = (TEXTE *)&sqlmem.buffer[i*sizeof(TEXTE)];
			(void)copyTextTo(record, t_ptr->text, _TEXTLEN);
			if (i == (int)0)
				(void)sprintf(text, "%s%s", leftmargin, record );
			else
				{
				(void)strcat(text, _P_EOL_);
				(void)strcat(text, leftmargin);
				(void)strcat(text, record);
				}
			}
		}
	return(anzahl);
}






        /*!!!!!!!!!!! OLD style use AKTobjtxt !!!!!!!!!!!!*/


/*!!! OLD style use AKTobjtxt */
int LanguageDependentText( int textid, int typ, int spr, int s_id, char *buffer )
{
	int anzzus;
	int status = MPOK;
	char leftmargin[_RECORDLEN];

	*leftmargin = NULL;
	*buffer = '\0';
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status == MPOK)
		{
		anzzus = (int)UNDEF;
		anzzus = SelectAktionsText(textid, (int)s_id, typ, buffer, leftmargin);
		if ( anzzus <= (int)0 )
			anzzus = SelectAktionsText(textid, spr, typ, buffer, leftmargin);
		}
	else
		anzzus = (int)_UNDEF;

	(void)MPAPIdb_committrx();

	return(anzzus);
}

