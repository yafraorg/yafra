/*D************************************************************
 * Modul:		GRAPHIC							ganzstr.c
 *
 *					Find the number of strings 
 *					copy the strings in array
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/gui/ganzstr.c,v 1.2 2008-11-02 19:55:47 mwn Exp $

 Log Information:
 $Log: ganzstr.c,v $
 Revision 1.2  2008-11-02 19:55:47  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:50:03  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/28 11:02:12  ja
 general version

 * Revision 1.3  94/02/18  10:36:06  10:36:06  ja (Jean-Marc Adam)
 * Name conversion for DOS
 * 
 * Revision 1.2  93/08/20  23:54:17  23:54:17  ja (Jean-Marc Adam)
 * update
 *  
 * 
*/

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ganzstr.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";




int xGRanz_strings(
char* liste,
char*** str
)

{
	char *anf;
	char tmp[80];
	int  i, anz, len;
	char **array;

	anf = liste;
	anz = 0;

	/*--- Get number of strings ----------------*/
	while(sscanf(anf, "%s", tmp) == 1) {
		while (*anf == ' ') anf++;
		len = strlen(tmp);
		anf += len;
		anz++;
	}

	/*--- Alloc str pointers -------------------*/
	array = (char **)malloc(anz*sizeof(char *));

	/*--- Get the strings ----------------------*/
	i = 0;
	anf = liste;
	while(sscanf(anf, "%s", tmp) == 1) {
		while (*anf == ' ') anf++;
		len = strlen(tmp);
		array[i] = (char *)malloc((unsigned)(len+1));
		strcpy(array[i], tmp);
		anf += len;
		i++;
	}
	*str = array;
	return(anz);
}
