/*D***********************************************************
 * Modul:     DBI - database select                           
 *            KOMM_DETAIL
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKOMDselect.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

static int KOMDETchoose(char *);

/*F***********************************************************
 * Function:  Select                                         
 *************************************************************/
int KOMDselect(long *len, char *buffer, int *anzahl)
{
	buffer[0] = NULL;
	*len = (int)strlen( buffer );
	if (*anzahl == 1)
		buffer[(*len - 1)] = NULL;
	return((int)MPOK);
}

/*F***********************************************************
 * Function:  Choose                                          
 *************************************************************/
int KOMDchoose(int table, char *buffer)
{
	extern int sprache;
	extern KOMM_DETAIL      k_d;
	extern KOMMISSION			kom;
	extern BEZEICHNUNG		bez;
	extern BUCHUNG				bch;
	extern REISENDER        rei;
	extern KOLLEKTIV        kol;
	extern char glob_bez_kom[];

	BEZEICHNUNG	tmpbez;
	struct tm DateTime;
	char	bezeichnung[RECLAENGE];
	char	buffer1[_RECORDLEN];
	char	message[RECLAENGE];
	char dbbuffer[RECLAENGE];
	char satzstring[_RECORDLEN];
	int	id, state;
	int   status = MPOK;

	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MKOMD_KOM:
			(void)strcpy(glob_bez_kom, buffer);
			break;
		case MKOMD_DLN:
			(void)MPAPIselectEntry((int)_REISENDER, buffer, (char *)&rei,
			      sizeof(REISENDER), sizeof(rei.pers_id));
			return(MPOK);
			break;
		case MKOMD_BCH:
			(void)MPAPIselectEntry((int)_BUCHUNG, buffer, (char *)&bch,
			      sizeof(BUCHUNG), (size_t)0);
			return(MPOK);
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* KOMMISSION */
	strcpy(dbbuffer, buffer);
	(void)ConvertSpecialChar(dbbuffer, NULL);
	if (MPAPIselectEntry((int)_KOMMISSION, dbbuffer, (char *)&kom,
					sizeof(KOMMISSION), sizeof(kom.komm_id)) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, "\t");

	/* BUCHUNG  Buchungsreferenz */
	bch.bid=(int)_UNDEF;
	(void)MPAPIselectOneId((int)_BUCHUNG, k_d.bid, (char *)&bch);
	if (bch.bid != (int)_UNDEF)
		{
		(void)copyTextTo(buffer1, (char *)bch.ref, (int)_BEZLEN);
		(void)strcat(buffer, buffer1);
		}
	(void)strcat(buffer, "\t");

	/* REISENDER  Reisenderkommission */
	id = DLNmkbez(k_d.dln_id, buffer1, (int)_RECORDLEN);
	if (id == (int)MPOK)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* KUNDEN  Kundenkommission */
	id = KUNmkbez(k_d.kun_id, buffer1, (int)_RECORDLEN);
	if (id == (int)MPOK)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* KOLLEKTIV */
	id = MPAPIselectOneId((int)_KOLLEKTIV, k_d.kol_id, (char *)&kol);
	if (id != (int)_UNDEF)
      {
      (void)copyTextTo(bezeichnung, kol.name, (int)_BEZLEN);
		(void)strcat(buffer, bezeichnung);
      }
	(void)strcat(buffer, "\t");

	/* UNDEF  Prio/Reihenfolge */
	if (k_d.prio > 0)
		{
		sprintf(buffer1, "%d", k_d.prio);
		strcat(buffer, buffer1);
		}
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}
