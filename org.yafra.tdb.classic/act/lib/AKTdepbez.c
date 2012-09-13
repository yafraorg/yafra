/**************************************************************
 * Modul:     AKTobjbez
 *            get BEZEICHNUNG of an object dependent on the
 *            right language
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/lib/AKTdepbez.c,v 1.3 2008-11-23 15:44:38 mwn Exp $";

/* MarcoPolo API includes */
#include <mpact.h>         /* Standart Includefile   */

int AKTobjbez(int typ, int bez_id, char *buffer)
{
	extern int aktuellesprache;

	int status = (int)MPOK;
	int id;

	id = SelectBez(typ, aktuellesprache, bez_id, buffer);
	if (id == (int)_UNDEF)
		{
		id = SelectBez(typ, DEFAULTLANGUAGE, bez_id, buffer);
		if (id == (int)_UNDEF)
			{
			status = (int)MPERROR;
			buffer[0] = NULL;
			}
		}
	return(status);
}


// TODO OLD style
int LanguageDependentBez( int bez_id, int typ, int spr, int s_id, char *buffer )
{
	int anzzus;
	int status = MPOK;

	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status == MPOK)
		{
      anzzus = (int)_UNDEF;
      anzzus = SelectBez( typ, (int)s_id, bez_id, buffer );
      if ( anzzus <= (int)0 )
         anzzus = SelectBez( typ, spr, bez_id, buffer );
		}
	else
      anzzus = (int)_UNDEF;

	(void)MPAPIdb_committrx();

	return(anzzus);
}
