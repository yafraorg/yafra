/**************************************************************/
/* Modul:     printen eines PBM bildes                        */
/*                                                            */
/* Functions: PBMprint                                        */
/*                                                            */
/* Copyright: Yafra.org     */
/* Autor:     Administrator, Yafra.org                     */
/*            based strongly on Patrick J. Naughton, 1989     */
/*                                                            */
/* History:   May 1992 mw Erstellung                          */
/**************************************************************/
#include <psmume.h>
#include "pbm.h"

static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/psmume/source/pbmprint.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

static void putbit(bit b);
static void putrest(void);
static void putitem(void);
static void putinit(int dpi);

static int item, bitsperitem, bitshift, itemsperline, firstitem;

int PBMPrint(unsigned char *buf, int width, int height, int dpi)
{
	bit* bitrow;
	register bit* bP;
	int argn, rows, cols, format, rucols, padright, row;
	register int nzcol, col;
	char* usage = "[-resolution N] [pbmfile]\n\tresolution = [75|100|150|300] (dpi)";
		
	rows = width;
	cols = height;
		
	putinit(dpi);
		
	/* Find rightmost black pixel. */
	for ( nzcol = cols - 1; nzcol >= 0 && bitrow[nzcol] == PBM_WHITE; --nzcol )
		continue;
		
	/* Round up to the nearest multiple of 8. */
	rucols = ( nzcol + 8 ) / 8;
	rucols = rucols * 8;
	padright = rucols - (nzcol + 1);
		
	/* Transfer raster graphics */
	printf("\033*b%dW",rucols/8);
	for ( col = 0, bP = bitrow; col <= nzcol; ++col, ++bP )
		putbit( *bP );
	for ( col = 0; col < padright; ++col )
		putbit( 0 );
		
	putrest();
	return(MOK);	
}

static void putinit(int dpi)
{
	/* Printer reset. */
	printf("\033E");
			
	/* Ensure top margin is zero */
	printf("\033&l0E");
			
	/* Set raster graphics resolution */
	printf("\033*t%dR",dpi);
			
	/* Start raster graphics, relative adressing */
	printf("\033*r1A");
			
	itemsperline = 0;
	bitsperitem = 1;
	item = 0;
	bitshift = 7;
	firstitem = 1;
}

#if __STDC__
static void putbit(bit b)
#else /*__STDC__*/
void putbit(b)
bit b;
#endif /*__STDC__*/
{
	if ( b == PBM_BLACK )
		item += 1 << bitshift;
	bitshift--;
	if ( bitsperitem == 8 )
		{
		putitem( );
		bitshift = 7;
		}
	bitsperitem++;
}

static void putrest(void)
{
	if ( bitsperitem > 1 )
		putitem( );

	/* end raster graphics */
	printf( "\033*rB" );

	/* Printer reset. */
	printf("\033E");
}

static void putitem(void)
{
	putchar( item );
	bitsperitem = 0;
	item = 0;
}
