/*D***********************************************************
 * Modul:     DBI - database select
 *            Kontingent
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKONDselect.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

/*F***********************************************************
 * Function:  Select                                         
 *************************************************************/
int KONDselect(long *len, char *buffer, int *anzahl)
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
int KONDchoose(int table, char *buffer)
{
	extern int		sprache;
	extern HOST_KONT		hkon;
	extern KONTINGENT		kon;
	extern KONT_DETAIL	k_d;
	extern KATEGORIE		kat;
	extern DIENST_TRAEGER dlt;
	extern STATUS_WERTE	sta;

	extern char		glob_kond_hkon[];
	extern char		glob_kond_kon[];
	extern char		glob_kond_kat[];
	extern char		glob_kond_dlt[];

	char	bezeichnung[_RECORDLEN];
	char	buffer1[_RECORDLEN];
	int	id1, id2;
	int	status = (int)MPOK;

	k_d.hostkont_id = (int)_UNDEF;
	k_d.kont_id = (int)_UNDEF;
	k_d.kat_id = (int)_UNDEF;
	k_d.dlt_id = (int)_UNDEF;
	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	COMMTYP = CHOOSE;

	/* Einschr�nkungen */
	switch(FELDNR)
		{
		case MKOND_HKON:
			(void)strcpy(glob_kond_hkon, buffer);
			return(MPOK);
			break;
		case MKOND_KON:
			(void)strcpy(glob_kond_kon, buffer);
			return(MPOK);
			break;
		case MKOND_KAT:
			(void)strcpy(glob_kond_kat, buffer);
			break;
		case MKOND_DLT:
			(void)strcpy(glob_kond_dlt, buffer);
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* HOST_KONT */
	if (*glob_kond_hkon != NULL)
		{
		if (MPAPIselectEntry((int)_HOST_KONT, glob_kond_hkon, (char *)&kon,
		   sizeof(hkon), sizeof(hkon.hostkont_id)) == (int)_UNDEF)
			{
			UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		k_d.hostkont_id = hkon.hostkont_id;
		(void)sprintf(buffer, "%s\t", glob_kond_hkon);
		}
	else
		strcpy(buffer, "\t");

	/* KONTINGENT */
	if (*glob_kond_kon != NULL)
		{
		if (MPAPIselectEntry((int)_KONTINGENT, glob_kond_kon, (char *)&kon,
		   sizeof(kon), sizeof(kon.kont_id)) == (int)_UNDEF)
			{
			UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		k_d.kont_id = kon.kont_id;
		(void)strcat(buffer, glob_kond_kon);
		(void)strcat(buffer, "\t");
		}
	else
		{
		/* then HOST_KONT MUST be specified */
		if (*glob_kond_hkon == NULL)
			{
			UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		else
			strcat(buffer, "\t");
		}

	/* KATEGORIE */
	if (*glob_kond_kat != NULL)
		{
		if (MPAPIselectEntry((int)_KATEGORIE, glob_kond_kat, (char *)&kat,
		   sizeof(kat), sizeof(kat.kat_id)) == (int)_UNDEF)
			{
			UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		k_d.kat_id = kat.kat_id;
		(void)strcat(buffer, glob_kond_kat);
		(void)strcat(buffer, "\t");

		/* KONT_DETAIL with KATEGORIE */
		if (  k_d.hostkont_id != (int)_UNDEF )
			(void)MPAPIselectOneId((int)_KONT_DETAIL, k_d.hostkont_id, (char *)&k_d);
		else if (  k_d.kont_id != (int)_UNDEF )
			(void)MPAPIselectOneId((int)_KONT_DETAIL, k_d.kont_id, (char *)&k_d);

		/* UNDEF  KATEGORIE Menge */ 
		if (k_d.anz != (int)_UNDEF)
			{
			(void)sprintf(bezeichnung, "%d", k_d.anz);
			(void)strcat(buffer, bezeichnung);
			}
		(void)strcat(buffer, "\t");

		/* UNDEF  KATEGORIE Mindestmenge */ 
		if (k_d.minanz != (int)_UNDEF)
			{
			(void)sprintf(bezeichnung, "%d", k_d.minanz);
			(void)strcat(buffer, bezeichnung);
			}
		(void)strcat(buffer, "\t");

		/* let DLT empty if KONT is on a KAT */
		(void)strcat(buffer, "\t");
		}
	else
		{
		/* let KAT and MENGE/ANZ and MIN empty if KONT is on DLT */
		strcat(buffer, "\t");
		strcat(buffer, "\t");
		strcat(buffer, "\t");

		if (MPAPIselectEntry((int)_DIENST_TRAEGER, glob_kond_dlt, (char *)&dlt,
		   sizeof(dlt), sizeof(dlt.dlt_id)) == (int)_UNDEF)
			{
			UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		k_d.dlt_id = dlt.dlt_id;
		(void)strcat(buffer, glob_kond_dlt);
		(void)strcat(buffer, "\t");

		/* KONT_DETAIL with KATEGORIE */
		if (  k_d.hostkont_id != (int)_UNDEF )
			(void)MPAPIselectOneId((int)_KONT_DETAIL, k_d.hostkont_id, (char *)&k_d);
		else if (  k_d.kont_id != (int)_UNDEF )
			(void)MPAPIselectOneId((int)_KONT_DETAIL, k_d.kont_id, (char *)&k_d);

		}

	/* STATUS_WERTE  over-booking factor */
	sta.typ=(int)_U_FAK;
	id1 = MPAPIselectOneId((int)_STATUS_WERTE, k_d.sta_id, (char *)&sta);
	id2 =SelectBez((int)_U_FAK, sprache, sta.bez_id, bezeichnung);
	if (id1 != (int)_UNDEF && id2 != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");


	COMMTYP = SELECTITEM;
	return(MPOK);
}
