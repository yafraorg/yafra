/*D************************************************************
 * Modul:		GRAPHIC							gwrgraf.c
 *
 *					Write graphic data to DB 	
 *					Export graphic data to a file  	
 *
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */
#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/gwrgraf.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";

#define	PIXTOMMFACT(a,f)  ((WCVALUE)(a)/(f))



/*F--------------------------------------------------------------------------
 *  Function:	xGRwrite_graphikdata( )
 *					-prepare and send graphic data to DB
 *					-
 *  In:			-
 *  out:			-
 *  Return:		-nb of chars 
 *---------------------------------------------------------------------------
 */
long xGRwrite_graphikdata() 
{
	extern long		anzgrafObj;
	extern GRAGLOB	graglob;
	extern GRAWIDGETS grawidgets;
	extern GRAFOBJ *grafObj;
	extern char		*aktgraphikfile;
	extern char *outcomm;

	GRAFOBJ		*akt;
	GRAFOBJDISC obj;
	long			i, totlen;
	int			j;
	int			anzgraval;
	XPoint		*xp;
	XRectangle	*xr;
	XArc			*xa;
	char			*mainptr; 


	/*--- Nb of items -----------------------*/
	mainptr = outcomm;
	mainptr += sprintf( mainptr, "%d\n", anzgrafObj); 

	/*--- write data on buffer -----*/
	for (i=0;  i<anzgrafObj;  i++) 
	{
		akt = &grafObj[i];
		/*--- prepare temporary obj struct --*/
		obj.was = akt->was;
		obj.text = akt->text;
		obj.anzRegionPoints = akt->anzRegionPoints;
		obj.gc1 = akt->gc1;
		obj.gc2 = akt->gc2;
		obj.gc3 = akt->gc3;
		for (j=0; j<akt->anzRegionPoints; j++) {
			obj.regionPoint[j].p.x = (WCVALUE)akt->regionPoint[j].p.x/graglob.xfak;
			obj.regionPoint[j].p.y = (WCVALUE)akt->regionPoint[j].p.y/graglob.yfak;
			obj.regionPoint[j].n = akt->regionPoint[j].n;
		}
		switch (akt->was) {
			case OBJ_DRAWINGAREA:
			case OBJ_TEXT:
				obj.graVal[0].x = (WCVALUE)akt->xpoints[0]/graglob.xfak;
				obj.graVal[0].y = (WCVALUE)akt->xpoints[1]/graglob.yfak;
				anzgraval = 1;
				break;
			case OBJ_POINT:
				xp = (XPoint *)akt->xpoints;
				obj.graVal[0].x = (WCVALUE)xp->x/graglob.xfak;
				obj.graVal[0].y = (WCVALUE)xp->y/graglob.yfak;
				anzgraval = 1;
				break;
			case OBJ_LINE:
				xp = (XPoint *)akt->xpoints;
				obj.graVal[0].x = (WCVALUE)xp->x/graglob.xfak;
				obj.graVal[0].y = (WCVALUE)xp->y/graglob.yfak;
				xp++;
				obj.graVal[1].x = (WCVALUE)xp->x/graglob.xfak;
				obj.graVal[1].y = (WCVALUE)xp->y/graglob.yfak;
				anzgraval = 2;
				break;
			case OBJ_RECTANGLE:
			case OBJ_FILLEDRECTANGLE:
				xr = (XRectangle *)akt->xpoints;
				obj.graVal[0].x = (WCVALUE)xr->x/graglob.xfak;
				obj.graVal[0].y = (WCVALUE)xr->y/graglob.yfak;
				obj.graVal[1].x = (WCVALUE)xr->width/graglob.xfak;
				obj.graVal[1].y = (WCVALUE)xr->height/graglob.yfak;
				anzgraval = 2;
				break;
			case OBJ_ELLIPSE:
			case OBJ_ARC:
			case OBJ_CIRCLE:
			case OBJ_FILLEDELLIPSE:
			case OBJ_FILLEDARC:
			case OBJ_FILLEDCIRCLE:
				xa = (XArc *)akt->xpoints;
				obj.graVal[0].x = (WCVALUE)xa->x/graglob.xfak;
				obj.graVal[0].y = (WCVALUE)xa->y/graglob.yfak;
				obj.graVal[1].x = (WCVALUE)xa->width/graglob.xfak;
				obj.graVal[1].y = (WCVALUE)xa->height/graglob.yfak;
				obj.graVal[2].x = (WCVALUE)xa->angle1;
				obj.graVal[2].y = (WCVALUE)xa->angle2;
				anzgraval = 3;
				break;
		}

		/*--- Write to buffer  --------------------------------------*/
		mainptr += sprintf( mainptr, "%d\t", i);
		/*--- Was and Contexts ----*/
		mainptr += sprintf( mainptr, "%c %d %d %d ", ((char)obj.was+(char)65),
															(int)obj.gc1,
															(int)obj.gc2,
															(int)obj.gc3  );
		/*--- Graphic values ------*/
		for (j=0; j<anzgraval; j++)
		{
			mainptr += sprintf( mainptr, "%.2f %.2f ", obj.graVal[j].x,
															 obj.graVal[j].y);
		}
		/*--- Region points -------*/
		mainptr += sprintf( mainptr, "%d ", (int)obj.anzRegionPoints);
		for (j=0;  j<obj.anzRegionPoints;  j++)
		{
			mainptr += sprintf( mainptr, "%.2f %.2f %d ", obj.regionPoint[j].p.x,
																		obj.regionPoint[j].p.y,
																		obj.regionPoint[j].n);
		}
		/*--- Text ----------------*/
		if (akt->was == OBJ_TEXT)
			mainptr += sprintf( mainptr, "%s", obj.text);
		else
			mainptr -= 1;                                  /*no space before \t */

		mainptr += sprintf( mainptr, "\t\n");
	}

	return( mainptr - outcomm);		/*effective data length */
}




/*F--------------------------------------------------------------------------
 *  Function:	xGRwrite_graphik( )
 *					-prepare and export data to a FILE 
 *					-
 *  In:			-
 *  out:			-
 *  Return:		-nb of chars 
 *---------------------------------------------------------------------------
 */

/* simple_save wird vom activate Callback des save Menuepunktes          */
/* aufgerufen. Wenn noch kein Datenfile geladen war, wird gespeichert,   */

Boolean xGRwrite_graphik(char *datafile)
{
	extern long anzgrafObj;
	extern GRAGLOB graglob;
	extern GRAWIDGETS grawidgets;
	extern GRAFOBJ *grafObj;
	extern char *aktgraphikfile;

	GRAFOBJ *akt;
	GRAFOBJDISC obj;
	FILE *fp;
	long  i;
	int j;
	int anzgraval;
	Boolean ok;
	XPoint *xp;
	XRectangle *xr;
	XArc *xa;

	fp = fopen(datafile, _P_WRITE_);
	if (!fp)
		{
		xUIfehler(XGRGRAFILEOPEN, grawidgets.shell);
		return(False);
		}

	/* Datenbasis auf fp herausschreiben */
	for(i=0; i<anzgrafObj; i++)
		{
		akt = &grafObj[i];

		obj.was = akt->was;
		obj.text = akt->text;
		obj.anzRegionPoints = akt->anzRegionPoints;
		obj.gc1 = akt->gc1;
		obj.gc2 = akt->gc2;
		obj.gc3 = akt->gc3;
		for (j=0; j<akt->anzRegionPoints; j++) {
			obj.regionPoint[j].p.x = (WCVALUE)akt->regionPoint[j].p.x/graglob.xfak;
			obj.regionPoint[j].p.y = (WCVALUE)akt->regionPoint[j].p.y/graglob.yfak;
			obj.regionPoint[j].n = akt->regionPoint[j].n;
		}
		switch (akt->was) {
			case OBJ_DRAWINGAREA:
			case OBJ_TEXT:
				obj.graVal[0].x = (WCVALUE)akt->xpoints[0]/graglob.xfak;
				obj.graVal[0].y = (WCVALUE)akt->xpoints[1]/graglob.yfak;
				anzgraval = 1;
				break;
			case OBJ_POINT:
				xp = (XPoint *)akt->xpoints;
				obj.graVal[0].x = (WCVALUE)xp->x/graglob.xfak;
				obj.graVal[0].y = (WCVALUE)xp->y/graglob.yfak;
				anzgraval = 1;
				break;
			case OBJ_LINE:
				xp = (XPoint *)akt->xpoints;
				obj.graVal[0].x = (WCVALUE)xp->x/graglob.xfak;
				obj.graVal[0].y = (WCVALUE)xp->y/graglob.yfak;
				xp++;
				obj.graVal[1].x = (WCVALUE)xp->x/graglob.xfak;
				obj.graVal[1].y = (WCVALUE)xp->y/graglob.yfak;
				anzgraval = 2;
				break;
			case OBJ_RECTANGLE:
			case OBJ_FILLEDRECTANGLE:
				xr = (XRectangle *)akt->xpoints;
				obj.graVal[0].x = (WCVALUE)xr->x/graglob.xfak;
				obj.graVal[0].y =	(WCVALUE)xr->y/graglob.yfak;
				obj.graVal[1].x = (WCVALUE)xr->width/graglob.xfak;
				obj.graVal[1].y = (WCVALUE)xr->height/graglob.yfak;
				anzgraval = 2;
				break;
			case OBJ_ELLIPSE:
			case OBJ_ARC:
			case OBJ_CIRCLE:
			case OBJ_FILLEDELLIPSE:
			case OBJ_FILLEDARC:
			case OBJ_FILLEDCIRCLE:
				xa = (XArc *)akt->xpoints;
				obj.graVal[0].x = (WCVALUE)xa->x/graglob.xfak;
				obj.graVal[0].y = (WCVALUE)xa->y/graglob.yfak;
				obj.graVal[1].x = (WCVALUE)xa->width/graglob.xfak;
				obj.graVal[1].y = (WCVALUE)xa->height/graglob.yfak;
				obj.graVal[2].x = (WCVALUE)xa->angle1;
				obj.graVal[2].y = (WCVALUE)xa->angle2;
				anzgraval = 3;
				break;
			}

		fprintf(fp, "%c %d %d %d ", ((char)obj.was+(char)65),
		(int)obj.gc1, (int)obj.gc2, (int)obj.gc3);

		for (j=0; j<anzgraval; j++)
			fprintf(fp, "%.2f %.2f ", obj.graVal[j].x, obj.graVal[j].y);

		fprintf(fp, "%d ", (int)obj.anzRegionPoints);
		for (j=0; j<obj.anzRegionPoints; j++) {
			fprintf(fp, "%.2f %.2f %d ",
							obj.regionPoint[j].p.x, obj.regionPoint[j].p.y,
							obj.regionPoint[j].n);
			}
		/*fwrite((void *)&obj, sizeof(GRAFOBJDISC), 1, fp);*/
		if (akt->was == OBJ_TEXT) {
			/*fwrite((void *)akt->text, strlen(akt->text)+1, 1, fp);*/
			fprintf(fp, "%s", obj.text);
			}
		fprintf(fp, "\n");
		}

	fclose(fp);

/*!!! mw 23.10.98 **
	if (strcmp(aktgraphikfile, datafile) != 0)
		{
		ok = xGRset_filename(datafile);
		if (!ok)
			{
			return(False);
			}
		}
*******/

	return(True);
}
