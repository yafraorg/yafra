/*D***********************************************************
 * Modul:     AKT base moduls
 *            handle language code selection
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/
/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/lib/AKTlanguage.c,v 1.2 2008-11-02 19:55:50 mwn Exp $";

/* MarcoPolo API includes */
#include <mpact.h>         /* Standard Includefile   */



/*--- SQL ------------------------------------------------------------------*/
#define COUNT_SPR "SELECT COUNT(S_ID) FROM TDBADMIN.SPRACHEN;"



/*F--------------------------------------------------------------------------
 * Function:  AKTlanguageCount
 *            count the nb of languages in DB Sprachen table
 * 
 * in:        
 * out:       
 * return:    count or unsuccess code
 *---------------------------------------------------------------------------
 */
int AKTlanguageCount( )
{
	extern 	MEMOBJ		sqlmem; 

	int		status, anzLang, count;
	char		query[2*RECLAENGE];

	/*--- general inits ------------*/
	status = (int)MPOK ;

/*** force return ???????????? Query makes problem ???????????????????*/
return(4);

	/*--- query reservations -------*/
	(void)sprintf(query, COUNT_SPR );
	status = MPAPIdb_sqlquery((int)_INTEGER, (char **)(&sqlmem.buffer),
									 query, &anzLang, &sqlmem.datalen, &sqlmem.alloclen );

	if (status == (int)MPOK && anzLang > 0)
		(void)memcpy((void *)&count, (void *)sqlmem.buffer, sizeof(int));
	else
		count = (int)_UNDEF;

	return(count);
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTlanguage ()
 *					set id 'aktuellesprache' find out the correct priorities 
 *             if 'outputsprache' is defined this is used (overwrite mode)
 *					first is DLN/KUN/BCH/KOL and default is 'dialogsprache'
 *					set bez 'sbez'  default is "german"
 *
 *  In:			id's
 *  out:			aktuellesprache and language
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTlanguage( int aBCHid, int aKOLid, int aDLNid, int aKUNid)
{
	extern int	dialogsprache;
	extern int	aktuellesprache;
	extern int	outputsprache;    
	extern int	sprache;
	extern char language[];
	
	extern SPRACHEN	spr;
	extern PERSONEN	pers;
	extern KOLLEKTIV	kol;
	extern BUCHUNG	 	bch;
	
	int	id;
	
	/*--- has user set a flag ? ---------------------------------------------*/
	if (outputsprache != (int)_UNDEF)
		aktuellesprache = outputsprache;         /* overwrite by forced flag */
	else 
	{
		/*--- DLN/REISENDER language ? --------------------------------------*/
		if (aDLNid != (int)_UNDEF)
		{
			id = MPAPIselectOneId((int)_PERSONEN, aDLNid, (char *)&pers);
			if (id != (int)_UNDEF)
				aktuellesprache = pers.s_id;        /* take DLN one */
		}
		
		/*--- special KUNDEN language ? (anbieter/bch-stelle) ----------------*/
		if (aKUNid != (int)_UNDEF)
		{
			id = MPAPIselectOneId((int)_PERSONEN, aKUNid, (char *)&pers);
			if (id != (int)_UNDEF)
				aktuellesprache = pers.s_id;         /* take KUNDEN one */
		}
		
		/*--- RECH-STELLE language ? -----------------------------------------*/
		if (aBCHid != (int)_UNDEF)
		{
			(void*)MPAPIselectOneId((int)_BUCHUNG, aBCHid, (char *)&bch);
			if ((bch.bid >= 0) && (bch.kid != (int)_UNDEF))
			{
				id = MPAPIselectOneId((int)_PERSONEN, bch.kid, (char *)&pers);
				if (id != (int)_UNDEF)
					aktuellesprache = pers.s_id;        /* take KUNDEN one */
			}
		}
		
		/*--- KOLLEKTIV language ? -------------------------------------------*/
		if (aKOLid != (int)_UNDEF)
		{
			id = MPAPIselectOneId((int)_KOLLEKTIV, aKOLid, (char *)&kol);
			if (id != (int)_UNDEF)
			{
				id = MPAPIselectOneId((int)_PERSONEN, kol.kid, (char *)&pers);
				if (id != (int)_UNDEF)
					aktuellesprache = pers.s_id;       /* take KOLLEKTIV one */
			}
		}
		/*--- Nothing was set, use default -----------------------------------*/
		if (aktuellesprache == (int)_UNDEF)
			aktuellesprache = dialogsprache;
	}
	
	/* set sprache equal to aktuellesprache */
	sprache = aktuellesprache;
	
	/*--- get language with correct id --------------------------------------*/
	id = MPAPIselectOneId((int)_SPRACHEN, aktuellesprache, (char *)&spr);
	if (id != (int)_UNDEF)
		copyTextTo( language, spr.sysbez, _CHAR20);
	else
		sprintf( language, "%s", DEFAULTLANGTEXT); 
}
