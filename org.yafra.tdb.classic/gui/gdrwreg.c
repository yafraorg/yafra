/*D************************************************************
 * Modul:		GRAPHIC							gdrwreg.c
 *
 *					Draw region polygon and text 	
 *					Color is updated for booked objects
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gdrwreg.c,v 1.2 2008-11-02 19:55:45 mwn Exp $";



/*F--------------------------------------------------------------------------
 *  Function:	xGRdraw_region()
 *					Draw a region if it has enough points 
 *					graphic contexts of categories colors are used 
 *	
 *	CAUTION: gracatGCs (from db_data) cannot be used for compatibility with oldies
 *	
 *---------------------------------------------------------------------------
 */
void xGRdraw_region(
REGOBJ *reg
)

{
	extern Display    *display;
	extern GRAWINDOWS grawindows;
	extern GRAGLOB    graglob;
	extern GRACAT     gracat;
	extern ApplicationData app_data;

	unsigned char col;
	long i, j;
	GC gc;
	XPoint *anf;

	if (reg->region && !XEmptyRegion(reg->region) && reg->Eckpunkte) {
		anf = &reg->Eckpunkte[1];
		if (reg->temp) {
			col = graglob.Tempfarbe;
		} else {
			if (reg->zustand <= 0) {
				col = reg->color;
			} else {
				col = graglob.Buchungsfarbe[reg->zustand];
			}
		}

		/*--- Polygon -------------*/
		if (col != 255) {
			if (col >= graglob.anzColors) col=0;
			gc = graglob.GCR[col];    
			XFillPolygon( display, grawindows.graphik, gc, anf, reg->anzEckpunkte-1,
								Complex, CoordModeOrigin);
		}

		/*--- Text of region ------*/
		gc = *graglob.gcf;
		XDrawString( display, grawindows.graphik, gc,
								(int)(reg->Eckpunkte[0].x), (int)(reg->Eckpunkte[0].y),
								reg->Regionname, strlen(reg->Regionname));
	}
}
