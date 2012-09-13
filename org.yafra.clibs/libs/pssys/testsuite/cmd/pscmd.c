/************************************************************
 *
 * cmd.c
 *
 ************************************************************/
 
/* RCS static ID */
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssys/testsuite/cmd/pscmd.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

#include <pssys.h>

#include "version.h"

/* end of global decl. */
int main(int, char *[]);

int main(int argc, char *argv[])
{
	int cret = 0;

	printf("debug: cmd test 1 start\n");
	cret = PSSYSexecute("\"D:\\usr\\Microsoft Office\\Office\\WinWord.exe\"");
	printf("debug: return of execute is %d\n", cret);

	printf("debug: cmd test 2 start\n");
	cret = PSSYSexecute("WinWord.exe");
	printf("debug: return of execute is %d\n", cret);

	printf("debug: and exit\n");
	exit(0);
}
