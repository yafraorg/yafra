#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/cashint.c,v 1.1.1.1 2002-10-26 21:10:42 mwn Exp $";


#ifdef TICK_BUG
char *cashint(int zahl ,
               char *format ,
               char *rec )
{
	char loc[100], *ptr;
	int i, j;

	sprintf(loc, format, zahl);
	i = strlen(loc);
	for (ptr=rec, j=0; i>0; i--, j++) {
		*ptr++ = loc[j];
		if (i/3 > 0 && i%3 == 1) {
			*ptr++ = '\'';
		}
	}
	*ptr = NULL;
	return(rec);
}
#endif


char *cashint(int zahl ,
               char *format ,
               char *rec )
{
	char loc[100], *ptr;
	int i, j;

	sprintf(loc, format, zahl);
	i = strlen(loc);
	ptr = rec;
	if (loc[0] == '-')  {
		*ptr++ = loc[0];
		i -= 1;
		j = 1;
	}
	else
		j = 0;

	for ( ;  i>0;  i--, j++) {
		*ptr++ = loc[j];
		if (i/3 > 0 && i%3 == 1) {
			*ptr++ = '\'';
		}
	}
	*ptr = NULL;
	return(rec);
}
