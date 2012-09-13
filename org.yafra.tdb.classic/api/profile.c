/*D***********************************************************
 * Modul:     API - init
 *            init of the MP_PROFIL structure
 *
 * Copyright: yafra.org, Basel, Switzerland
 * Autor:     Administrator
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */
#include <mpsqlsel.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/profile.c,v 1.2 2008-11-02 19:55:49 mwn Exp $";

/*F--------------------------------------------------------------------------
 *  Function:	MPAPIprofile_init ()
 *					initialize the user profile 
 *
 *  In:			-user ID string
 *  out:			-user profile
 *  Return:		-MPOK or an error code
 *---------------------------------------------------------------------------
 */
int MPAPIprofile_init(char *aUserid, MP_PROFIL *aProf)
{
	extern MEMOBJ apimem;
	extern int sprache;
	extern char userid[];
	extern unsigned char logging_mp;

	int status = (int)MPOK;
	int prof_cnt;
	char sqlquery[_QUERYLEN];
	MP_PROFIL *Pprof;

	/* init SPRACHE */
	sprache = (int)DEFAULTLANGUAGE;

	/* start DB transaction */
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status != MPOK)
		{
		return(status);
		}

	/* select all profiles of a USER - it should return only one ! */
	(void)sprintf(sqlquery, _SEL_PROF_USER, aUserid);
	status = MPAPIdb_sqlquery((int)_MP_PROFIL, &apimem.buffer, sqlquery,
	                         &prof_cnt, &apimem.datalen, &apimem.alloclen);
	if (status != (int)MPOK)
		{
		/* db error */
		}
	else
		{
		if (prof_cnt == (int)1)
			{
			/* copy the profile to the argument profile pointer for returning */
			Pprof = (MP_PROFIL *)apimem.buffer;
			(void)memcpy((void *)aProf, (void *)&Pprof[0], sizeof(MP_PROFIL));

			/* set SPRACHE and USERID according user profile */
			sprache = Pprof[0].s_id;
			(void)strcpy(userid, Pprof[0].mpuser);
			}
		else
			{
			/* check if < 1 or > 1 and write error */
			status = MPE_NOPROFILE;
			}
		}

	/* end DB transaction */
	(void)MPAPIdb_committrx();

	return(status);
}
