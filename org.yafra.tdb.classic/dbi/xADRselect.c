/*D***********************************************************
 * Modul:     DBI - database select
 *            person addresses
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xADRselect.c,v 1.3 2009-01-02 16:51:34 mwn Exp $";

/*F***********************************************************
 * Function:  Select
 *************************************************************/
int ADRselect(long *len, char *buffer, int *anzahl)
{
	int status = MPOK;

	*buffer = NULL;
	*len = (int)strlen( buffer );
	if (*anzahl == 1)
		buffer[(*len - 1)] = NULL;
	return( status );
}

/*F***********************************************************
 * Function:  Choose
 *************************************************************/
int ADRchoose(int table, char *buffer)
{
	extern int		sprache;
	extern KUN_VIEW kunv;
	extern DLN_VIEW dlnv;
	extern PERSADR adr;
	extern PERSONEN pers;
	extern STATUS_WERTE	sta;

	char	tmpbez[_RECORDLEN];
	char	tmport[_RECORDLEN];
	char	buffer1[_RECORDLEN];
	int	id1, id2;
	int	status = (int)MPOK;
	int   perstyp;

	perstyp = (int)_UNDEF;
	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	COMMTYP = CHOOSE;

	/* Einschr�nkungen */
	switch(FELDNR)
		{
		case MADR_KUN:
			perstyp = (int)_PERS_FIRMEN;
			strcpy(tmpbez, buffer);
			break;
		case MADR_DLN:
			perstyp = (int)_PERS_PRIVAT;
			strcpy(tmpbez, buffer);
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */
	adr.pers_id = (int)_UNDEF;
	(void)memset((void *)&adr, NULL, sizeof(adr));

	/* get right PERSON */
	if (perstyp == (int)_PERS_FIRMEN)
		{
		if (MPAPIselectEntry((int)_KUN_VIEW, tmpbez, (char *)&kunv,
		   sizeof(kunv), sizeof(kunv.kun_id)) == (int)_UNDEF)
			{
			UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		adr.pers_id = kunv.kun_id;
		(void)copyTextTo(tmport, (char *)kunv.ort, (int)_CHAR256);
		(void)sprintf(buffer, "%s\t\t", tmpbez);
		}
	else
		{
		if (MPAPIselectEntry((int)_DLN_VIEW, tmpbez, (char *)&dlnv,
		   sizeof(dlnv), sizeof(dlnv.dln_id)) == (int)_UNDEF)
			{
			UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		adr.pers_id = dlnv.dln_id;
		(void)copyTextTo(tmport, (char *)dlnv.ort, (int)_BEZLEN);
		(void)sprintf(buffer, "\t%s\t", tmpbez);
		}

	/* KONT_DETAIL with KATEGORIE */
	(void)MPAPIselectOneId((int)_PERSADR, adr.pers_id, (char *)&adr);

	/* let KAT and MENGE/ANZ empty if KONT is on DLT */
	(void)copyTextTo(tmpbez, (char *)adr.ans, (int)_CHAR256);
	strcat(buffer, tmpbez);
	strcat(buffer, "\t");

	(void)copyTextTo(tmpbez, (char *)adr.adr1, (int)_CHAR2000);
	strcat(buffer, tmpbez);
	strcat(buffer, "\t");

	(void)copyTextTo(tmpbez, (char *)adr.adr2, (int)_CHAR2000);
	strcat(buffer, tmpbez);
	strcat(buffer, "\t");

	(void)copyTextTo(tmpbez, (char *)adr.adr3, (int)_CHAR2000);
	strcat(buffer, tmpbez);
	strcat(buffer, "\t");

	if (*tmport != NULL)
		strcat(buffer, tmport);
	strcat(buffer, "\t");

	(void)copyTextTo(tmpbez, (char *)adr.plz, (int)_CHAR256);
	strcat(buffer, tmpbez);
	strcat(buffer, "\t");

	/* STATUS_WERTE  over-booking factor */
	sta.typ=(int)_ADRSTA;
	id1 = MPAPIselectOneId((int)_STATUS_WERTE, adr.sta_id, (char *)&sta);
	id2 =SelectBez((int)_ADRSTA, sprache, sta.bez_id, tmpbez);
	if (id1 != (int)_UNDEF && id2 != (int)_UNDEF)
		(void)strcat(buffer, tmpbez);
	(void)strcat(buffer, "\t");


	COMMTYP = SELECTITEM;
	return(MPOK);
}
