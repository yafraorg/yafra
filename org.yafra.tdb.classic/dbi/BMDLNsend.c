/*D***********************************************************
 * Modul:     DBI - booking modul
 *            send DLN mask to GUI
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/BMDLNsend.c,v 1.2 2008-11-02 19:55:38 mwn Exp $";

static int UtilMakeSelectlist(int, char *, char);

int BMDLNsend(int len, char *buffer)
{
	extern int sprache;
	extern DLN_VIEW dlnv;
	extern SPRACHEN spr;
	extern unsigned char bm_arrkom;

	char *ptr;
	char tmp_buffer[(_BEZLEN + 2)];
	char text1[4*_RECORDLEN];
	char text2[4*_RECORDLEN];
	char spr_bez[_BEZLEN + 1];
	int status = (int)MPOK;
	int i;
	int id;
	int section;
	int buffersize;

	ptr = comm.buffer;

	/* - SEX - all description of SEX */
	section = 1;
	(void)sprintf(ptr, "%d\n\0", section);
	ptr += strlen(ptr);
	status = UtilMakeSelectlist((int)_SEX, ptr, _MPSYMB_TAB);
	if (status == (int)MPOK)
		ptr += strlen(ptr);
	else
		return(status);

	/* - DLN - select fields on DLN menu */
	/* Name, Vorname, Alter, Passnr, Int-Text, Ext-Text */
	section++;
	(void)sprintf(ptr, "%d\n%d\n\0", section, BMDLNFIELDS);
	ptr += strlen(ptr);
	if (ACTIONTYP == (unsigned char)UPDATE ||
       ACTIONTYP == (unsigned char)MPDELETE)
		{
		dlnv.name[30] = NULL;
		dlnv.vor[30] = NULL;
		dlnv.age[9] = NULL;
		text1[0] = NULL;
		text2[0] = NULL;

		/* SPRACHEN */
		id = MPAPIselectOneId((int)_SPRACHEN, (int)dlnv.s_id, (char *)&spr);
		id = SelectBez((int)_SPRACHEN, sprache, spr.bez_id, spr_bez);

		/* TEXTE extern */
		id = SelFromTxt(dlnv.textid, sprache, (int)_PERSONEN, text1);
		id = SelFromTxt(dlnv.ext_txt, sprache, (int)_REISENDER, text2);

		/* put bez/txt into the buffer */
		(void)sprintf(ptr, "%s\t%s\t%s\t%s\t%s\t%s\t", dlnv.name, dlnv.vor,
		              dlnv.age, text1, text2, spr_bez);
		}
	else
		(void)sprintf(ptr, "\t\t\t\t\t\t");
	ptr += strlen(ptr);

	/* - KOMMISSION - all descriptions */
	section++;
	(void)sprintf(ptr, "%d\n\0", section);
	ptr += strlen(ptr);

	status = UtilMakeSelectlist((int)_KOMM_DETAIL, ptr, _MPSYMB_TAB);
	if (status == (int)MPOK)
		ptr += strlen(ptr);
	else
		return(status);

	/* - DLNT - all descriptions of RKR/DLNT */
	section++;
	(void)sprintf(ptr, "%d\n\0", section);
	ptr += strlen(ptr);
	status = UtilMakeSelectlist((int)_REISENDER_TYP, ptr, _MPSYMB_TAB);
	if (status == (int)MPOK)
		ptr += strlen(ptr);
	else
		return(status);

	*ptr = NULL;
	COMMTYP = (unsigned char)BMDLN;
	return(status);
}

static int UtilMakeSelectlist(int typ, char *buffer, char trenner)
{
	extern MEMOBJ sqlmem;
	extern MEMOBJ bm_kommem;
	extern char sqlquery[];
	extern int sprache;
	extern BUCHUNG bch;
	extern BCH_DLN bd;
	extern DLN_VIEW dlnv;
	extern REISENDER_TYP reit;
	extern REISENDER_TYP globDLNT;
	extern KOMMISSION kom;
	extern STATUS_WERTE sta;
	extern unsigned char bm_obj;
	extern unsigned char bm_arrkom;
	extern unsigned char selectfromtemp;

	static int kom_cnt;

	MEMOBJ kom_mem;
	KOMMISSION *Pkom;
	BEZEICHNUNG *pBEZ;
	char tmp_buffer[(_BEZLEN + 2)];
	char *ptr;
	int i, j;
	int anzahl;
	int anzkom;
	int len = 0;
	int bez_id;
	int status = (int)MPOK;

	ptr = buffer;
	kom_mem.buffer = NULL;
	kom_mem.alloclen = 0;
	kom_mem.datalen = 0;

	switch (typ)
		{
		case (int)_SEX:
			sta.sta_id = (int)_UNDEF;
			if (ACTIONTYP == (unsigned char)UPDATE ||
   		    ACTIONTYP == (unsigned char)MPDELETE)
				{
				sta.typ = (int)_SEX;
				(void)MPAPIselectOneId((int)_STATUS_WERTE, dlnv.sex, (char *)&sta);
				}
			bez_id = sta.sta_id;
			(void)sprintf(sqlquery, _SEL_BEZ_STA, sprache, (int)_SEX, (int)_SEX);
			break;

		case (int)_KOMM_DETAIL:
			if (ACTIONTYP == (unsigned char)UPDATE ||
	   	    ACTIONTYP == (unsigned char)MPDELETE)
				{
				(void)sprintf(sqlquery, _SEL_KOM_BCHDLN, bd.bid, bd.dln_id);
				status = MPAPIdb_sqlquery((int)_KOMMISSION, &kom_mem.buffer, sqlquery,
				                         &anzkom, &kom_mem.datalen, &kom_mem.alloclen);
				if (status != (int)MPOK)
					{
					MPfreeobj(&kom_mem);
					return(status);
					}
				Pkom = (KOMMISSION *)kom_mem.buffer;
				}
			if (bm_obj == (unsigned char)_ARRANGEMENT)
				{
				if (selectfromtemp)
					(void)sprintf(sqlquery, _SEL_BEZ_DLN_ARRKOM, bch.arr_id, sprache, (int)_KOMMISSION);
				else
					(void)sprintf(sqlquery, _SEL_BEZ_KOM_KOMTYP_ARR, (int)_KOMM_DLN,
					              bch.arr_id, bch.arr_id, bch.arr_id, sprache, (int)_KOMMISSION);
				}
			else
				(void)sprintf(sqlquery, _SEL_BEZ_KOM_KOMTYP, (int)_KOMM_DLN,
			   	           sprache, (int)_KOMMISSION);
			if (bm_arrkom == (unsigned char)FALSE)
				{
				bm_arrkom = (unsigned char)TRUE;
				status=MPAPIdb_sqlquery((int)_BEZEICHNUNG, &bm_kommem.buffer, sqlquery,
				                         &kom_cnt, &bm_kommem.datalen, &bm_kommem.alloclen);
				if (status != (int)MPOK)
					{
					UtilMsg(status, MSGTYP_ERROR, NULL);
					return((int)MPERROR);
					}
				}

			(void)sprintf(ptr, "%d\n\0", kom_cnt);
			ptr += strlen(ptr);
			if (kom_cnt > (int)0)
				{
				for (i=0; i < kom_cnt; i++ )
					{
					pBEZ = (BEZEICHNUNG *)&bm_kommem.buffer[i*sizeof(BEZEICHNUNG)];
					(void)copyTextTo(tmp_buffer, (char *)pBEZ->bez, (int)_BEZLEN);
					len = strlen(tmp_buffer);
					(void)memcpy((void *)ptr, (void *)tmp_buffer, len+(size_t)1 );
					ptr += len;

					(void)memset((void *)ptr, trenner, sizeof(trenner));
					ptr += sizeof(trenner);

					(void)memset((void *)ptr, '0', sizeof(char));
					if (ACTIONTYP == (unsigned char)UPDATE ||
				       ACTIONTYP == (unsigned char)MPDELETE)
						{
						for (j=0; j<anzkom; j++)
							{
							if (pBEZ->bez_id == Pkom[j].bez_id)
								{
								(void)memset((void *)ptr, '1', sizeof(char));
								break;
								}
							}
						}
					ptr++;

					(void)memset((void *)ptr, trenner, sizeof(trenner));
					ptr++;

					(void)memset((void *)ptr, NULL, sizeof(char));
					}
				}
			MPfreeobj(&kom_mem);
			return(status);
			break;

		case (int)_REISENDER_TYP:
			if (globDLNT.rkr_id != (int)_UNDEF)
				reit.bez_id = (int)globDLNT.bez_id;
			else
				reit.bez_id = (int)_UNDEF;
			if (ACTIONTYP == (unsigned char)UPDATE ||
		       ACTIONTYP == (unsigned char)MPDELETE)
				{
				(void)MPAPIselectOneId((int)_REISENDER_TYP, dlnv.rkr_id, (char *)&reit);
				}
			bez_id = reit.bez_id;
			(void)sprintf(sqlquery, _SEL_BEZ_REIT, sprache, (int)_REISENDER_TYP);
			break;
		}

	status=MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, sqlquery,
	                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if (status == (int)MPOK)
		{
		(void)sprintf(ptr, "%d\n\0", anzahl);
		ptr += strlen(ptr);
		if (anzahl > (int)0 )
			{
			for (i=0; i < anzahl; i++ )
				{
				pBEZ = (BEZEICHNUNG *)&sqlmem.buffer[i*sizeof(BEZEICHNUNG)];
				(void)copyTextTo(tmp_buffer, (char *)pBEZ->bez, (int)_BEZLEN);
				len = strlen(tmp_buffer);
				(void)memcpy((void *)ptr, (void *)tmp_buffer, len+(size_t)1 );
				ptr += len;

				(void)memset((void *)ptr, trenner, sizeof(trenner));
				ptr += sizeof(trenner);

				(void)memset((void *)ptr, '0', sizeof(char));
				switch (typ)
					{
					case (int)_REISENDER_TYP:
					case (int)_SEX:
						/* bei INSERT ev. auf ersten Eintrag setzen */
						if (bez_id > 0 && pBEZ->bez_id == bez_id)
							(void)memset((void *)ptr, '1', sizeof(char));
						break;

					case (int)_KOMM_DETAIL:
						if (ACTIONTYP == (unsigned char)UPDATE ||
					       ACTIONTYP == (unsigned char)MPDELETE)
							{
							for (j=0; j<anzkom; j++)
								{
								if (pBEZ->bez_id == Pkom[j].bez_id)
									{
									(void)memset((void *)ptr, '1', sizeof(char));
									break;
									}
								}
							}
						break;

					default:
						break; /* that's not good ! */
					}
				ptr++;

				(void)memset((void *)ptr, trenner, sizeof(trenner));
				ptr++;

				(void)memset((void *)ptr, NULL, sizeof(char));
				}
			}
		}
	else
		{
		UtilMsg(status, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	return(status);
}
