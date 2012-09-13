/*D***********************************************************
 * Name:      AKTrecipient.c
 *                                                            
 * Modul:     AKT base moduls  
 *            Handle recipient/addressee (Empfaenger) functions
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/

/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/lib/AKTrecipient.c,v 1.2 2008-11-02 19:55:50 mwn Exp $";

/* MarcoPolo API includes */
#include <mpact.h>         /* Standard Includefile   */


/*P--- EXTERNALS -----------------------------------------------------------*/


/*--- LAYOUT ---------------------------------------------------------------*/
#define TEXTID5       5                /* Group/Collective:  */
#define TEXTID6       6                /* Teilnehmer:        */

#define COL_R			"%42.42s"                    /* recipient             */

#define COL_P1			"%2s"                        /* participant margin    */
#define COL_P2			"%-s"                        /* participant name      */
#define COL_P3			"%-3s"                       /* participant gap       */
#define COL_P4			"%s"                       /* participant vorname   */

#define COL_K1			"%s"                         /* Kol group margin      */
#define COL_K2			"%-s"                        /* Kol group text        */


/*--- GLOBALS -------------------------------------------------------------*/



/*F--------------------------------------------------------------------------
 *  Function:	AKTrecipientSetType ()
 *					check if private or firm, collective or individual 
 *					global variable is changed  
 *  In:			-current booking 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTrecipientSetType( BUCHUNG *pBch)
{
	extern	int		recipientType;

	/*--- check Kollektiv ids type ---------*/
	if (pBch->k_id == (int)UNDEF) 
	{
		/*--- Kunde/Rechnungsempfaenger ?--*/
		if (pBch->kid == (int)UNDEF) 
			recipientType = REC_PRIV_SINGLE;
		else
			recipientType = REC_FIRM_SINGLE;
	}
	else
	{
		/*--- Kunde/Rechnungsempfaenger ?--*/
		if (pBch->kid == (int)UNDEF) 
			recipientType = REC_PRIV_GROUP;  
		else
			recipientType = REC_FIRM_GROUP;
	}
#ifdef DEBUG_GING
	switch(recipientType)
	{
		case REC_PRIV_SINGLE: fprintf(stderr, "%s PRIV_SINGLE", _P_EOL_);  break;
		case REC_FIRM_SINGLE: fprintf(stderr, "%s FIRM_SINGLE", _P_EOL_);  break;
		case REC_PRIV_GROUP:  fprintf(stderr, "%s PRIV_GROUP", _P_EOL_);   break;
		case REC_FIRM_GROUP:  fprintf(stderr, "%s FIRM_GROUP", _P_EOL_);   break;
	}
	fprintf(stderr, " %d%s", recipientType, _P_EOL_);
#endif
}

/*F--------------------------------------------------------------------------
 *  Function:	AKTrecipientGiveKundenType ()
 *					returns the k_typ_id from kunden table 
 *  In:			- current booking 
 *  out:			-
 *  Return:		- k_typ_id
 *---------------------------------------------------------------------------
 */
int AKTrecipientGiveKundenType( BUCHUNG *pBch )
{
	extern KUNDEN		kun;
	int id;

	/*--- Kunde from Buchung ----------------------*/
	if (pBch->kid != (int)_UNDEF)
	{
		id = MPAPIselectOneId((int)_KUNDEN, pBch->kid, (char *)&kun);
		if (id != _UNDEF)
			return ( kun.k_typ_id );
		else
			return ( (int)_UNDEF );
	}
	else
		return ( (int)_UNDEF );
}


/*F--------------------------------------------------------------------------
 *  Function:	AKTrecipientGetText ()
 *					check if private or firm, collective or individual 
 *					prepare a structure with name, address, et...  of recipient  
 *  In:			-a booking for checking, BCH_DLN array, number and current DLN
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTrecipientGetText( BUCHUNG *pBch, int aDlnid, RECIPIENT *pRecip)
{
	extern DLN_VIEW	dlnv;
	extern KUNDEN		kun;
	extern PERSONEN	pers;
	extern PERSADR		adr;
	extern KOLLEKTIV	kol;
	extern LAND			land;
	extern int		kolid;
	extern int		recipientType;
	extern int	aktuellesprache, dialogsprache;         
	
	int	id, idd, best_id;
	int	theKunid, theKolid;
	
	/*--- Init --------------------------*/
	pRecip->id            = 0;
	*(pRecip->anschrift)  = (char)NULL;
	*(pRecip->vor)        = (char)NULL;
	*(pRecip->name)       = (char)NULL;
	*(pRecip->adr1)       = (char)NULL;
	*(pRecip->adr2)       = (char)NULL;
	*(pRecip->adr3)       = (char)NULL;
	*(pRecip->plz)        = (char)NULL;
	*(pRecip->ort)        = (char)NULL;
	*(pRecip->land)       = (char)NULL;
	pRecip->versand       = 0;
	*(pRecip->tel)        = (char)NULL;
	*(pRecip->fax)        = (char)NULL;
	
	theKunid = pBch->kid ;    /* kunde Rechnungsemfpaenger */
	theKolid = pBch->k_id ;   /* Kollektiv                 */
	
	/*--- PRIVATE SINGLE ----------------------------------------------------*/
	if (recipientType == REC_PRIV_SINGLE) 
	{
		/*--- Get person ---------------------*/
		id = MPAPIselectOneId((int)_DLN_VIEW, aDlnid, (char *)&dlnv);
		if (id != (int)MPOK)
		{ 
			copyTextTo( pRecip->vor,  dlnv.vor,  _CHAR30) ;
			copyTextTo( pRecip->name, dlnv.name, _CHAR30) ;
		}
		/*--- land text ----------------------*/
		if (dlnv.land_id != (int)_UNDEF)
		{ 
			(void)AKTobjbez((int)_LAND, dlnv.land_id, pRecip->land);
		}
		/*--- person address -----------------*/
		id = MPAPIselectOneId((int)_PERSADR, aDlnid, (char *)&adr);
		if (id != (int)UNDEF )
		{
			copyTextTo( pRecip->anschrift, adr.ans, _CHAR30);
			copyTextTo( pRecip->adr1,      adr.adr1, _CHAR30);
			copyTextTo( pRecip->adr2,      adr.adr2, _CHAR30);
			copyTextTo( pRecip->adr3,      adr.adr3, _CHAR30);
			copyTextTo( pRecip->plz,       adr.plz, _CHAR10);
		}
		/*--- person -------------------------*/
		id = MPAPIselectOneId((int)_PERSONEN, aDlnid, (char *)&pers);
/*#4		if (id != (int)UNDEF )
			copyTextTo( pRecip->ort, pers.ort, _CHAR30);
*/
	}
	
	
	/*--- FIRM SINGLE -------------------------------------------------------*/
	if (recipientType == REC_FIRM_SINGLE) 
	{
		/*--- Get Kunde: Rechnungsempf. oder Buchungstelle or Reservatadresse */
		if (theKunid != (int)_UNDEF)
		{
			id = MPAPIselectOneId((int)_KUNDEN, theKunid, (char *)&kun);
			if (id != _UNDEF)
			{
				copyTextTo( pRecip->tel, kun.tel, _CHAR30); 
				copyTextTo( pRecip->fax, kun.fax, _CHAR30);
				
				id = MPAPIselectOneId((int)_PERSONEN, kun.pers_id, (char *)&pers);
				if (id != _UNDEF)
				{
					copyTextTo( pRecip->name, pers.name, _CHAR30); 
/*#4					copyTextTo( pRecip->ort,  pers.ort, _CHAR30); */
				}
			}
		}


/*#4 --- land text ----------------------
		if (kun.land_id != (int)_UNDEF)
		{ 
			(void)AKTobjbez((int)_LAND, kun.land_id, pRecip->land);
		}
*/

		/*--- person address -----------------*/
		id = MPAPIselectOneId((int)_PERSADR,  kun.pers_id, (char *)&adr);
		if (id != (int)UNDEF )
		{
			copyTextTo( pRecip->anschrift, adr.ans, _CHAR30);
			copyTextTo( pRecip->adr1,      adr.adr1, _CHAR30);
			copyTextTo( pRecip->adr2,      adr.adr2, _CHAR30);
			copyTextTo( pRecip->adr3,      adr.adr3, _CHAR30);
			copyTextTo( pRecip->plz,       adr.plz, _CHAR10);
		}
	}
	
	/*--- Private Group and firm ---------------------------------------------*/
	best_id = (int)UNDEF;
	idd = (int)UNDEF;
	if ((recipientType == REC_PRIV_GROUP) || (recipientType == REC_FIRM_GROUP))
	{
		/*--- Get responsible person ----------------*/
		id = MPAPIselectOneId((int)_KOLLEKTIV, theKolid, (char *)&kol);

		/*--- priority1: Kunde/rechnungsempfaenger auf buchung --*/
		if ((id != (int)UNDEF ) && (theKunid != (int)UNDEF))
		{
			idd = MPAPIselectOneId((int)_PERSONEN, theKunid, (char *)&pers);
			if (idd != (int)UNDEF )
				best_id = theKunid;
		}
		/*--- priority2: Kunde/rechnungsempfaenger in Kollektiv --*/
		else if ((id != (int)UNDEF ) && (kol.kid != (int)UNDEF))
		{
			idd = MPAPIselectOneId((int)_PERSONEN, kol.kid, (char *)&pers);
			if (idd != (int)UNDEF )
				best_id = kol.kid;
		}
		/*--- priority3: Bezugs person --------------*/
		else if ((id != (int)UNDEF ) && (kol.hauptpers != (int)UNDEF))
		{
			idd = MPAPIselectOneId((int)_PERSONEN, kol.hauptpers, (char *)&pers);
			if (idd != (int)UNDEF )
				best_id = kol.hauptpers;
		}

		/*--- write name and person address ------------------------*/
		if (best_id != (int)UNDEF )
		{
			copyTextTo( pRecip->name, pers.name, _CHAR30); 
/*#4			copyTextTo( pRecip->ort,  pers.ort,  _CHAR30); */

			id = MPAPIselectOneId((int)_PERSADR, best_id, (char *)&adr);
			if (id != (int)UNDEF )
			{
				copyTextTo( pRecip->anschrift, adr.ans,  _CHAR30);
				copyTextTo( pRecip->adr1,      adr.adr1, _CHAR30);
				copyTextTo( pRecip->adr2,      adr.adr2, _CHAR30);
				copyTextTo( pRecip->adr3,      adr.adr3, _CHAR30);
				copyTextTo( pRecip->plz,       adr.plz,  _CHAR10);
			}
		}
		
		/*--- Kunde tel and fax ----------------------*/
		if (theKunid != (int)_UNDEF)
		{
			id = MPAPIselectOneId((int)_KUNDEN, theKunid, (char *)&kun);
			if (id != _UNDEF)
			{
				copyTextTo( pRecip->tel, kun.tel, _CHAR30); 
				copyTextTo( pRecip->fax, kun.fax, _CHAR30);
			}

/*#4 --- land text -------------------------------
			if (kun.land_id != (int)_UNDEF)
			{ 
				(void)AKTobjbez((int)_LAND, kun.land_id, pRecip->land);
			}
*/
		}
		
	}
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTrecipientWriteOut ()
 *					Write from structure to output file 
 *				
 *  In:			-
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTrecipientWriteOut( RECIPIENT *pRecip )
{
	extern FILE		*FPout;

	char	margin[_GRAFORMLEN];

	/*--- Init margin -----------------*/
	sprintf(margin, COL_R, " "); 

	AKTdevicePrintCtrl( FPout, _DEV_PITCH_10 );

	/*--- Write person/firm address ---*/
	fprintf(FPout, "%s%-s%s",   margin,    pRecip->anschrift, _P_EOL_ );
	fprintf(FPout, "%s%-s  %-s%s", margin, pRecip->name, pRecip->vor, _P_EOL_ );
	fprintf(FPout, "%s%-s%s", margin,    pRecip->adr1, _P_EOL_ );
	fprintf(FPout, "%s%-s%s", margin,    pRecip->adr2, _P_EOL_ );
/*	fprintf(FPout, "%s%-s%s", margin,    pRecip->adr3, _P_EOL_ );   */
   fprintf(FPout, "%s%s %s%s", margin, pRecip->plz, pRecip->ort, _P_EOL_ );
	
	AKTlayoutLinesAdd( 5 );

}



/*F--------------------------------------------------------------------------
 *  Function:	AKTparticipantTitle ()
 *					find and write participant / group name 
 *  In:			-a Kollektiv id
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTparticipantTitle( int aKolid )
{
	extern FILE		*FPout;
	extern int		aktuellesprache, dialogsprache;         
	extern KOLLEKTIV   kol;

	int	id;
	char	format[_CHAR80+1];
	char	bezKol[_CHAR30+1];
	char	participantTxt[_CHAR30+1];
	char	groupTxt[_CHAR30+1];

	/*--- Init --------------------------*/
	*bezKol      = (char)NULL;
	sprintf(format, "%s%s%s", COL_K1, _P_EOL_, COL_K2 );

	/*--- Group or single --------------------------*/
	if (aKolid != _UNDEF)
		{
		(void)AKTobjtxt( (int)_COMMON_TYP, (int)TEXTID5, groupTxt, NOMARGIN);   
		/*--- Group name ----------------*/
		SelectBez((int)_KOLLEKTIV, aktuellesprache, aKolid, bezKol);
		if (id != _UNDEF)
			fprintf(FPout, "%s  %s%s", groupTxt, bezKol, _P_EOL_ );
		}
	else   /*--- single participant ---*/
		{
		(void)AKTobjtxt( (int)_COMMON_TYP, (int)TEXTID6, participantTxt, NOMARGIN);   
		fprintf(FPout, "%s%s", participantTxt, _P_EOL_ );
		}
}


/*F--------------------------------------------------------------------------
 *  Function:	AKTparticipantSingle ()
 *					write single participant to travel 
 *  In:			-BCH_DLN array, number, the current DLN
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTparticipantSingle( int aDlnid, char* margin)
{
	extern FILE		*FPout;
	extern DLN_VIEW		dlnv;

	char	format[_CHAR80+1];
	char	vor[_CHAR30+1], name[_CHAR30+1];
	int	id;

	/*--- Init --------------------------*/
	sprintf(format, "%s%s%s%s%s", margin, COL_P2, COL_P3, COL_P4, _P_EOL_ );

	/*--- Get name from dlnview ---------*/
	id = MPAPIselectOneId((int)_DLN_VIEW, aDlnid, (char *)&dlnv);
	if (id != (int)MPOK)
		{ 
		copyTextTo(vor,  dlnv.vor, _CHAR30) ;
		copyTextTo(name, dlnv.name, _CHAR30) ;
		}

	/*--- print out ---------------------*/
	fprintf(FPout, format, " ", name, " ", vor );
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTparticipantAll ()
 *					write all participants to travel 
 *  In:			-BCH_DLN array, number of dlnv
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
void AKTparticipantAll( BCH_DLN *bchdln, int anzBd, char* margin)
{
	extern FILE				*FPout;
	extern DLN_VIEW		dlnv;

	int 	j, id; 
	char	format[_CHAR80+1];
	char	vor[_CHAR30+1], name[_CHAR30+1];

	/*--- Init --------------------------*/
	sprintf(format, "%s%s%s%s%s", margin, COL_P2, COL_P3, COL_P4, _P_EOL_ );

	/*--- all Persons -----------------------*/
	for (j = 0;  j < anzBd;  j++)
		{
		/*--- Get name from bchdln -----------------------*/
		id = MPAPIselectOneId((int)_DLN_VIEW, bchdln[j].dln_id, (char *)&dlnv);
		if (id != (int)MPOK)
			{ 
			copyTextTo(vor,  dlnv.vor, _CHAR30) ;
			copyTextTo(name, dlnv.name, _CHAR30) ;
			}
		fprintf(FPout, format, " ", name, " ", vor );
		}
}




