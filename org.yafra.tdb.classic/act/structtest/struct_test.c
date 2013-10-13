/*D***********************************************************
 * program:      mpstruct
 * description:  complete c struct test
 *               program to check variable sizes
 *
 * arguments:    none
 *
 * Copyright: yafra.org
 *************************************************************/
#define SQL_MAX_ROW 50

#include <mpdb.h>      /* Includefile for relational database */
#include <mpmain.h>    /* Includefile for TDB */
#include <mpproapi.h>  /* Prototypes ANSI-C */

/* include def_table struct */
#include <mpdbglob.h>
#include <locale.h>
//#include  <stdalign.h>
#include "version.h"

void main()
{

	int aaa, aai, table_nr;

#ifdef ps_linux
	setlocale(LC_ALL, "en_US.utf8");
#endif

	printf("\nstructure test - %s\n", PSIDENT);
	printf("\nstructure test - test sizeof of standard types (int, char, long, etc)\n");
	printf("sizeof char: %2d\n", sizeof(char));
	printf("sizeof short: %2d\n", sizeof(short));
	printf("sizeof int: %2d\n", sizeof(int));
	printf("sizeof int *: %2d\n", sizeof(int *));
	printf("sizeof void *: %2d\n", sizeof(void *));
	printf("sizeof long: %2d\n", sizeof(long));
	printf("sizeof float: %2d\n", sizeof(float));
	printf("sizeof double: %2d\n", sizeof(double));

	printf("\nstructure test - test sizeof struct STATUS_WERTE and alignof()\n");
	printf("sizeof STATUS_WERTE: %4d\n", sizeof(STATUS_WERTE));
	//printf("alignof STATUS_WERTE: %4d\n", alignof(STATUS_WERTE));

	printf("\nstructure test - test sizeof of all TDB structs\n");
	for (table_nr = 0; table_nr < 292; table_nr++) {
		if (def_table[table_nr].name != NULL ) {
 			for (aai = aaa = 0; aai < def_table[table_nr].sqln; aai++) {
     			aaa += def_table[table_nr].elements[aai].leng;
			}
			if (aaa != def_table[table_nr].sqlrowlen) {
    			printf("table=[%14.14s] \tanzCol=%2d \tsqlrowlen=%3d, \tsum=%3d <==\n",
                                                def_table[table_nr].name,
				                                aai,
	                                         	def_table[table_nr].sqlrowlen,
	                                         	aaa);
			} else {
    			printf("table=[%14.14s] \tanzCol=%2d \tsqlrowlen=%3d, \tsum=%3d\n",
                                                def_table[table_nr].name,
				                                aai,
	                                         	def_table[table_nr].sqlrowlen,
	                                         	aaa);
			}
		}
	}
}
