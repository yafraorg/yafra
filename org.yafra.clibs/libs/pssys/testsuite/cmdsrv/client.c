/*D***********************************************************
 * File:       cmdclient.c
 * Module:     Command client 
 *                                                            
 * Copyright: Yafra.org     
 **************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssys/testsuite/cmdsrv/client.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

#include <stdio.h>

#include <pscmd.h>        /* Prototypes f�r ANSI-C         */
#include <pssys.h>

/*F--------------------------------------------------------------------------
 *  Function:	main()
 *					Main function of client
 *					
 *  In:			-arguments 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void main(int argc, char *argv[])
{
	int cret;

	if (argc != 2)
		{
		printf("\nusage: %s system_command_string\n", argv[0]);
		exit(-1);
		}

	printf("\nexecuting command %s\n", argv[1]);
	cret = PSSYSexecute(argv[1]);

	exit(0);
}
