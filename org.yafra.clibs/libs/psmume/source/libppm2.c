/* libppm2.c - ppm utility library part 2
**
** Copyright (C) 1989 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

#include "ppm.h"
#include "libppm.h"

#if __STDC__
void
ppm_writeppminit( FILE* file, int cols, int rows, pixval maxval, int forceplain )
#else /*__STDC__*/
void
ppm_writeppminit( file, cols, rows, maxval, forceplain )
    FILE* file;
    int cols, rows;
    pixval maxval;
    int forceplain;
#endif /*__STDC__*/
    {
#ifdef PBMPLUS_RAWBITS
    if ( maxval <= 255 && ! forceplain )
	fprintf(
	    file, "%c%c\n%d %d\n%d\n", PPM_MAGIC1, RPPM_MAGIC2,
	    cols, rows, maxval );
    else
	fprintf(
	    file, "%c%c\n%d %d\n%d\n", PPM_MAGIC1, PPM_MAGIC2,
	    cols, rows, maxval );
#else /*PBMPLUS_RAWBITS*/
    fprintf(
	file, "%c%c\n%d %d\n%d\n", PPM_MAGIC1, PPM_MAGIC2,
	cols, rows, maxval );
#endif /*PBMPLUS_RAWBITS*/
    }

static int
putus( n, file )
    unsigned short n;
    FILE* file;
    {
    if ( n >= 10 )
	if ( putus( n / 10, file ) == EOF )
	    return EOF;
    return putc( n % 10 + '0', file );
    }

#ifdef PBMPLUS_RAWBITS
static void
ppm_writeppmrowraw( file, pixelrow, cols, maxval )
    FILE* file;
    pixel* pixelrow;
    int cols;
    pixval maxval;
    {
    register int col;
    register pixel* pP;
    register pixval val;

    for ( col = 0, pP = pixelrow; col < cols; ++col, ++pP )
	{
	val = PPM_GETR( *pP );
#ifdef DEBUG
	if ( val > maxval )
	    pm_error( "r value out of bounds (%u > %u)", val, maxval );
#endif /*DEBUG*/
	if ( putc( val, file ) == EOF )
	    pm_error( "write error" );
	val = PPM_GETG( *pP );
#ifdef DEBUG
	if ( val > maxval )
	    pm_error( "g value out of bounds (%u > %u)", val, maxval );
#endif /*DEBUG*/
	if ( putc( val, file ) == EOF )
	    pm_error( "write error" );
	val = PPM_GETB( *pP );
#ifdef DEBUG
	if ( val > maxval )
	    pm_error( "b value out of bounds (%u > %u)", val, maxval );
#endif /*DEBUG*/
	if ( putc( val, file ) == EOF )
	    pm_error( "write error" );
        }
    }
#endif /*PBMPLUS_RAWBITS*/

static void
ppm_writeppmrowplain( file, pixelrow, cols, maxval )
    FILE* file;
    pixel* pixelrow;
    int cols;
    pixval maxval;
    {
    register int col, charcount;
    register pixel* pP;
    register pixval val;

    charcount = 0;
    for ( col = 0, pP = pixelrow; col < cols; ++col, ++pP )
	{
	if ( charcount >= 65 )
	    {
	    if ( putc( '\n', file ) == EOF )
		pm_error( "write error" );
	    charcount = 0;
	    }
	else if ( charcount > 0 )
	    {
	    if ( putc( ' ', file ) == EOF )
		pm_error( "write error" );
	    if ( putc( ' ', file ) == EOF )
		pm_error( "write error" );
	    charcount += 2;
	    }
	val = PPM_GETR( *pP );
#ifdef DEBUG
	if ( val > maxval )
	    pm_error( "r value out of bounds (%u > %u)", val, maxval );
#endif /*DEBUG*/
	if ( putus( val, file ) == EOF )
	    pm_error( "write error" );
	if ( putc( ' ', file ) == EOF )
	    pm_error( "write error" );
	val = PPM_GETG( *pP );
#ifdef DEBUG
	if ( val > maxval )
	    pm_error( "g value out of bounds (%u > %u)", val, maxval );
#endif /*DEBUG*/
	if ( putus( val, file ) == EOF )
	    pm_error( "write error" );
	if ( putc( ' ', file ) == EOF )
	    pm_error( "write error" );
	val = PPM_GETB( *pP );
#ifdef DEBUG
	if ( val > maxval )
	    pm_error( "b value out of bounds (%u > %u)", val, maxval );
#endif /*DEBUG*/
	if ( putus( val, file ) == EOF )
	    pm_error( "write error" );
	charcount += 11;
	}
    if ( charcount > 0 )
	if ( putc( '\n', file ) == EOF )
	    pm_error( "write error" );
    }

#if __STDC__
void
ppm_writeppmrow( FILE* file, pixel* pixelrow, int cols, pixval maxval, int forceplain )
#else /*__STDC__*/
void
ppm_writeppmrow( file, pixelrow, cols, maxval, forceplain )
    FILE* file;
    pixel* pixelrow;
    int cols;
    pixval maxval;
    int forceplain;
#endif /*__STDC__*/
    {
#ifdef PBMPLUS_RAWBITS
    if ( maxval <= 255 && ! forceplain )
	ppm_writeppmrowraw( file, pixelrow, cols, maxval );
    else
	ppm_writeppmrowplain( file, pixelrow, cols, maxval );
#else /*PBMPLUS_RAWBITS*/
    ppm_writeppmrowplain( file, pixelrow, cols, maxval );
#endif /*PBMPLUS_RAWBITS*/
    }

#if __STDC__
void
ppm_writeppm( FILE* file, pixel** pixels, int cols, int rows, pixval maxval, int forceplain )
#else /*__STDC__*/
void
ppm_writeppm( file, pixels, cols, rows, maxval, forceplain )
    FILE* file;
    pixel** pixels;
    int cols, rows;
    pixval maxval;
    int forceplain;
#endif /*__STDC__*/
    {
    int row;

    ppm_writeppminit( file, cols, rows, maxval, forceplain );

    for ( row = 0; row < rows; ++row )
	ppm_writeppmrow( file, pixels[row], cols, maxval, forceplain );
    }
