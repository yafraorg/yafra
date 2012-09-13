#define SQL_MAX_ROW 50

#include <mpdb.h>      /* Includefile fuer die Relationalen Datenbanken */
#include <mpmain.h>    /* Includefile fuer MARCO-POLO */
#include <mpproapi.h>  /* Prototypes fœr ANSI-C */

/* include def_table struct */
#include <mpdbglob.h>



void main()
{

	int aaa, aai, table_nr;

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
