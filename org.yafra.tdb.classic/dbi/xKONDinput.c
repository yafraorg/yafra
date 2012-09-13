/*D***********************************************************
 * modul:     DBI - database action
 *            ins/upd/del a KONT_DETAIL
 *
 *            there are two typs of details:
 *            - a detail of a KONTINGENT (kont_id != -1, hostkont_id = -1)
 *            - a detail of a HOST_KONT  (kont_id = -1, hostkont_id != -1)
 *
 *            the detail is based on the following items:
 *            - KATEGORIE
 *            - MENGE of KATEGORIE (quantity of KATEGORIE)
 *            or
 *            - DIENST_TRAEGER
 *
 * copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f?r ANSI-C */
#include <mpsqlsel.h>

#define _SEL_ALL_KOND_HKON "SELECT KD.* FROM TDBADMIN.KONT_DETAIL KD, TDBADMIN.KONTINGENT K \
                            WHERE K.HOSTKONT_ID = %d \
	                         AND KD.KONT_ID = K.KONT_ID \
	                         ORDER BY KD.KAT_ID, KD.DLT_ID;"

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKONDinput.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

static int KONDwriteentry      (char *, KONT_DETAIL *);
static int KONDcheckwithhost   (KONT_DETAIL *);
static int KONDcountwithhost   (KONT_DETAIL *Pkond, KONTINGENT *Pkon );

int KONDinput(int len, char *buffer)
{
	extern int sprache;

	extern HOST_KONT hkon;
	extern KONTINGENT kon;
	extern KONT_DETAIL k_d;
	extern KUNDEN kun;
	extern KATEGORIE kat;
	extern DIENST_TRAEGER dlt;
	extern STATUS_WERTE sta;

	struct tm DateTime;

	char **splitbuffer;
	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;
	int id;
	int anzsplit;
	int splitflag;
	int i;

	/* hole Eintrage aus dem Menustring der GUI */
	status = UtilSplitMenubuffer(buffer, to_buffers, '~' );
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		kon.kont_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	/* init */
	if (ACTIONTYP == (unsigned char)INSERT)
		{
		k_d.hostkont_id =	(int)_UNDEF;
		k_d.kont_id =		(int)_UNDEF;
		k_d.von_dat =		(int)_UNDEF;
		k_d.bis_dat =		(int)_UNDEF;
		}

	/* HOST_KONT check FROM kontingent */
	if (*to_buffers[MKOND_HKON] != NULL)
		{
		k_d.hostkont_id = MPAPIselectEntry((int)_HOST_KONT, to_buffers[MKOND_HKON],
		                  (char *)&hkon, sizeof(HOST_KONT), sizeof(kon.hostkont_id));
		}
	/* KONTINGENT check kontingent */
	if (*to_buffers[MKOND_KON] != NULL)
		{
		k_d.kont_id = MPAPIselectEntry((int)_KONTINGENT, to_buffers[MKOND_KON],
		                  (char *)&kon, sizeof(KONTINGENT), sizeof(kon.kont_id));
		}
	if ((k_d.kont_id == (int)_UNDEF && k_d.hostkont_id == (int)_UNDEF) ||
	    (k_d.kont_id != (int)_UNDEF && k_d.hostkont_id != (int)_UNDEF))
		{
		/* if KON and HKON are not defined or both are defined - send ERROR */
		UtilMsg((int)MPE_KONDLTORKAT, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* KATEGORIE */
	if (*to_buffers[MKOND_KAT] != NULL)
		{
		k_d.kat_id = MPAPIselectEntry((int)_KATEGORIE, to_buffers[MKOND_KAT],
			          (char *)&kat, sizeof(KATEGORIE), sizeof(kat.kat_id));
		}
	else
		k_d.kat_id = (int)_UNDEF;

	/* UNDEF  MENGE einer KATEGORIE */
	status = readInteger(&k_d.anz, to_buffers[MKOND_MENGE]);
	if (status == (int)MPERROR)
		k_d.anz = 0;

	/* UNDEF  MIN mindestanzahl plaetze die belegt sein muessen */
	status = readInteger(&k_d.minanz, to_buffers[MKOND_MIN]);
	if (status == (int)MPERROR)
		k_d.minanz = 0;

	/* Teildienstleistung die mit der Dienstleistung verkn?pft wird */
	/* lese DLG_PART */
	k_d.dlt_id = (int)_UNDEF;
	splitflag = NOPARTS;
	if (*to_buffers[MKOND_DLT] != NULL)
		{
		splitbuffer = (char **)UtilSplitBuffer(to_buffers[MKOND_DLT], &anzsplit, (char)_MPSYMB_CR);
		if (splitbuffer == NULL && anzsplit == (int)_UNDEF)
			{
			UtilMsg((int)MPE_SPLIT, MSGTYP_ERROR, NULL);
			UtilSplitFreeMenubuffer(to_buffers);
			return((int)MPERROR);
			}
		else if (anzsplit == (int)0)
			splitflag = SINGLESEL;
		else
			splitflag = MULTISEL;
		}

	/* KOND busy space */
	k_d.busy = (int)_UNDEF;

	/* STATUS_WERTE _U_FAK  over-booking factor */
	if (*to_buffers[MKOND_STA] != NULL)
		{
		sta.typ = (int)_U_FAK;
		status = getAttribut((int)_U_FAK, to_buffers[MKOND_STA]);
		if (status == (int)MPOK)
			k_d.sta_id = sta.sta_id;
		else
			k_d.sta_id = (int)_UNDEF;
		}
	else
		k_d.sta_id = (int)_UNDEF;

	if (splitflag == SINGLESEL)
		status = KONDwriteentry(to_buffers[MKOND_DLT], &k_d);
	else if (splitflag == MULTISEL)
		{
		for (i=0; i<anzsplit && status == MPOK; i++)
			status = KONDwriteentry(splitbuffer[i], &k_d);
		}
	else
		status = KONDwriteentry(NULL, &k_d);

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}


/************************************************************
 * functions: write one KONT_DETAIL entry to database
 **************************************************************/
static int KONDwriteentry(char *dltbez, KONT_DETAIL *Pkd)
{
	extern DIENST_TRAEGER dlt;
	int status = MPOK;

	/* get DLT id from bez */
	if (dltbez != NULL && *dltbez != NULL)
		{
		dlt.stufe = 0; /* suche nach untergeordnetem Eintrag */
		Pkd->dlt_id = MPAPIselectEntry((int)_DIENST_TRAEGER, dltbez, (char *)&dlt,
		  sizeof(DIENST_TRAEGER), sizeof(dlt.dlt_id));
		if (Pkd->dlt_id == (int)_UNDEF)
			return((int)MPERROR);
		}

	/* check with host-kont entry, if this entry is ok */
	if (ACTIONTYP != (unsigned char)MPDELETE)
		{
		/* falls sub-Kontingent check ob definition innerhalb host-Kontingent */
		if (Pkd->hostkont_id == (int)_UNDEF)
			status = KONDcheckwithhost(Pkd);
		}

	/* write entry into database */
	if (status == (int)MPOK)
		status=WriteEntry((int)_KONT_DETAIL, (char *)Pkd, (BEZEICHNUNG *)NULL);

	/* go home */
	return(status);
}

#define KONKAT_MISMATCH 1
#define KONDLT_MISMATCH 2
/************************************************************
 * functions: validate KONT_DETAIL entry before writing to db
 **************************************************************/
static int KONDcheckwithhost(KONT_DETAIL *Pkond)
{
	extern MEMOBJ sqlmem;
	extern char sqlquery[];
	extern HOST_KONT hkon;
	extern KONTINGENT kon;

	KONT_DETAIL *Phkd;
	int status = (int)MPOK;
	int id;
	int anzahl;
	int i;
	int kondstat = (int)MPERROR;

	/* check if all needed fields are set */
	if (Pkond->kont_id == (int)_UNDEF ||
	    (Pkond->kat_id == (int)_UNDEF && Pkond->dlt_id == (int)_UNDEF))
		return((int)MPERROR);

	/* set default error message if something wrong */
	if (Pkond->dlt_id == (int)_UNDEF)
		kondstat = KONKAT_MISMATCH;
	else
		kondstat = KONDLT_MISMATCH;

	/* get all kont-details of the host kont. check if the definition */
   /* of the new kontingent is possible (that means it has to be a sub- */
	/* definition of the host kont definition !) */
	id = MPAPIselectOneId((int)_KONTINGENT, Pkond->kont_id, (char *)&kon);
	(void)sprintf(sqlquery, _SELECT_KOND_HKON, kon.hostkont_id);
	status = MPAPIdb_sqlquery((int)_KONT_DETAIL, &sqlmem.buffer, sqlquery,
		                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if (status == (int)MPOK || anzahl > 0)
	{
		Phkd = (KONT_DETAIL *)sqlmem.buffer;
		
		/*--- Search for the entry in hostkont ---*/
		for (i=0; i<anzahl; i++)
		{
			if (Pkond->dlt_id == (int)_UNDEF)  /* detail on KATEGORIE */
			{
				if (Pkond->kat_id == Phkd[i].kat_id)
				{
					if (Pkond->anz <= Phkd[i].anz)
					{
						status = KONDcountwithhost( Pkond, &kon );
						if ( status == (int)MPERROR )
							return( status );

						kondstat = (int)MPOK;   /* definition is ok */
						break;
					}
					else
						break;
				}
			}
			else if (Pkond->kat_id == (int)_UNDEF) /* detail on DLT */
			{
				if (Pkond->dlt_id == Phkd[i].dlt_id)
				{
					status = KONDcountwithhost( Pkond, &kon );
					if ( status == (int)MPERROR )
						return( status );

					kondstat = (int)MPOK;  /* definition is ok */
					break;
				}
			}
			/* else case is already checked on the top */
		}
	}

	/* display error msg if kondstat == MPERROR */
	if (kondstat == KONKAT_MISMATCH)
		{
		UtilMsg((int)MPE_KONKATMIS, MSGTYP_ERROR, NULL);
		status = (int)MPERROR;
		}
	else if (kondstat == KONDLT_MISMATCH)
		{
		UtilMsg((int)MPE_KONDLTMIS, MSGTYP_ERROR, NULL);
		status = (int)MPERROR;
		}
	else if (status != MPOK)
		{
		UtilMsg(status, MSGTYP_ERROR, NULL);
		status = (int)MPERROR;
		}

	return(status);
}

#define KONKAT_MISMATCH       1
#define KONDLT_MISMATCH       2
#define HKOND_TO_SMALL        3
#define KOND_ALLREADY_EXISTS  4
/************************************************************
 * functions: count KONT_DETAIL entry before writing to db
 **************************************************************/
static int KONDcountwithhost( KONT_DETAIL *Pkond, KONTINGENT *Pkon )
{
	extern MEMOBJ sqlmem;
	extern char sqlquery[];
	extern HOST_KONT hkon;
	extern KONTINGENT kon;

	KONT_DETAIL hkd;
	KONT_DETAIL *Phkd;
	int status = (int)MPOK;
	int id;
	int anzahlobjects = (int)0;
	int i, anzkd;
	int kondstat = (int)MPOK;

	/*--- Initialisation ---*/
	anzkd = (int)0;

	hkd.hostkont_id = Pkon->hostkont_id;
	hkd.dlt_id      = Pkond->dlt_id;
	hkd.kat_id      = Pkond->kat_id;

	id = MPAPIselectOneId((int)_KONT_DETAIL, Pkon->hostkont_id, (char *)&hkd);
	if (id != (int)_UNDEF )
	{
		if ( hkd.anz >= Pkond->anz )
		{	
			(void)sprintf(sqlquery, _SEL_ALL_KOND_HKON, kon.hostkont_id);
			status = MPAPIdb_sqlquery((int)_KONT_DETAIL, &sqlmem.buffer, sqlquery,
											  &anzkd, &sqlmem.datalen, &sqlmem.alloclen);
			if (status == (int)MPOK && anzkd > 0)
			{
				Phkd = (KONT_DETAIL *)sqlmem.buffer;
				
				/*--- Count equal entries ---*/
				for (i=0; i<anzkd; i++)
				{
					if ( Pkond->kont_id == Phkd[i].kont_id )      /* schon in diesem kont definiert */
						continue;
					
					if (Pkond->dlt_id == (int)_UNDEF)
					{
						if (Pkond->kat_id == Phkd[i].kat_id)
							anzahlobjects += Phkd[i].anz;
					}
					else if (Pkond->kat_id == (int)_UNDEF)
					{
						if (Pkond->dlt_id == Phkd[i].dlt_id)
						{
							kondstat = (int)KOND_ALLREADY_EXISTS;   /* definition allready exists */
							break;
						}
					}
				}
			}
		}
		else
			kondstat = (int)HKOND_TO_SMALL;
	}
	else
	{
		/* set default error message if something wrong */
		if (Pkond->dlt_id == (int)_UNDEF)
			kondstat = KONKAT_MISMATCH;
		else
			kondstat = KONDLT_MISMATCH;
	}

	/* display error msg if kondstat == MPERROR */
	if ( (anzahlobjects+Pkond->anz) > hkd.anz )
		{
		UtilMsg((int)MPE_KONKATSUMME, MSGTYP_ERROR, NULL);
		status = (int)MPERROR;
		}
	else if (kondstat == KONKAT_MISMATCH)
		{
		UtilMsg((int)MPE_KONKATMIS, MSGTYP_ERROR, NULL);
		status = (int)MPERROR;
		}
	else if (kondstat == KONDLT_MISMATCH)
		{
		UtilMsg((int)MPE_KONDLTMIS, MSGTYP_ERROR, NULL);
		status = (int)MPERROR;
		}
	else if (kondstat == HKOND_TO_SMALL)
		{
		UtilMsg((int)MPE_KONKATMIS, MSGTYP_ERROR, NULL);
		status = (int)MPERROR;
		}
	else if (kondstat == KOND_ALLREADY_EXISTS)
		{
		UtilMsg((int)MPE_KONDLTEXISTS, MSGTYP_ERROR, NULL);
		status = (int)MPERROR;
		}
	else if (status != MPOK)
		{
		UtilMsg(status, MSGTYP_ERROR, NULL);
		status = (int)MPERROR;
		}

	return(status);
}
