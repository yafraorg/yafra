/*D************************************************************
 * Modul:		GRAPHIC							grdgraf.c
 *
 *					Read graphic data from DB and create graf Objects	
 *					Read graphic file and create graf Objects	
 *					
 *
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */


#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/grdgraf.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";


#define	END_OF_LINE		'\n'
#define	MMTOPIXFACT(a,f) ((short)(((a)*(f))+0.5) )


/*P------------------------ PROTOTYPES --------------------------------------*/
static int  xGRread_line( char *pd, char *ps );


/*F--------------------------------------------------------------------------
 *  Function:	xGRread_graphikdata( )
 *					-get graphic data from DB
 *					-
 *  In:			-buffer
 *  out:			-
 *  Return:		-nb of chars read 
 *---------------------------------------------------------------------------
 */
long xGRread_graphikdata( char *graphikBuf )
{
	extern long				anzgrafObj;
	extern unsigned long anzregionPoints;
	extern Display		*display;
	extern GRAGLOB		graglob;
	extern GRAWINDOWS grawindows;
	extern GRAWIDGETS grawidgets;

	GRAFOBJDISC discobj;
	GRAFOBJ		memobj;
	char			inbuf[1024];
	char			buffer[512];
	char			*text;
	char			*ptr, *mainptr;
	char		was;
	int		j, number;
	int		m;
	int		anzgraval;
	float		fval;
	int		ival;
	long		i, nbitems;
	WCVALUE		xfactor, yfactor;       /*local factors for speed enhance*/
	XPoint		*xp;
	XRectangle	*xr;
	XArc			*xa;

	/*--- inits ---------*/
	anzgrafObj = 0;
	anzregionPoints = 0;
	xfactor = graglob.xfak;
	yfactor = graglob.yfak;

	/*--- Get nb of items ------*/
	mainptr = graphikBuf;
	mainptr += xGRread_line( inbuf, mainptr);
	nbitems = atoi( inbuf);
	if (nbitems == 0)
	{
		xUIfehler( XGRGRAFORMAT, grawidgets.shell);
		return( mainptr - graphikBuf); 
	}

	/*--- Go for all items ---------------------------------*/
	for (i=0;  i < nbitems;  i++ ) 
	{
		/*--- scan DB entries ---*/
		mainptr += xGRread_line( inbuf, mainptr);

		/*--- must be a number -------*/
		if (inbuf[0] != '0' && inbuf[0] != '1' && inbuf[0] != '2' &&
          inbuf[0] != '3' && inbuf[0] != '4' && inbuf[0] != '5' &&
		    inbuf[0] != '6' && inbuf[0] != '7' && inbuf[0] != '8' &&
		    inbuf[0] != '9' )
		{
			/*-- format problem --*/
			return(0); /*>>>>>>>>>>> exit >>>>>>>*/
		}
		ptr = inbuf;
		sscanf(ptr, "%d", &number);

		/*--- object type A-P -------*/
		ptr += strlen(ptr);
		while (*ptr == 0) ptr++;
		sscanf(ptr, "%c", &was);
		discobj.was = (was-65)%16;

		/*--- GC --------------------*/
		ptr += strlen(ptr);
		while (*ptr == 0) ptr++;
		sscanf(ptr, "%d", &ival);
		discobj.gc1 = (unsigned char)ival;

		ptr += strlen(ptr);
		while (*ptr == 0) ptr++;
		sscanf(ptr, "%d", &ival);
		discobj.gc2 = (unsigned char)ival;

		ptr += strlen(ptr);
		while (*ptr == 0) ptr++;
		sscanf(ptr, "%d", &ival);
		discobj.gc3 = (unsigned char)ival;

		/*--- Nb and Coordinates --------------*/
		switch (discobj.was) {
			case OBJ_DRAWINGAREA:
			case OBJ_TEXT:
			case OBJ_POINT:
				anzgraval = 1;
				break;
			case OBJ_LINE:
			case OBJ_RECTANGLE:
			case OBJ_FILLEDRECTANGLE:
				anzgraval = 2;
				break;
			case OBJ_ELLIPSE:
			case OBJ_FILLEDELLIPSE:
			case OBJ_CIRCLE:
			case OBJ_FILLEDCIRCLE:
			case OBJ_ARC:
			case OBJ_FILLEDARC:
				anzgraval = 3;
				break;
		}
		for (m=0;  m<anzgraval;  m++) {
			ptr += strlen(ptr);
			while (*ptr == 0) ptr++;
			sscanf(ptr, "%f", &fval);
			discobj.graVal[m].x = fval;

			ptr += strlen(ptr);
			while (*ptr == 0) ptr++;
			sscanf(ptr, "%f", &fval);
			discobj.graVal[m].y = fval;
		}

		/*--- Nb of Coordinates --------------*/
		ptr += strlen(ptr);
		while (*ptr == 0) ptr++;
		sscanf(ptr, "%d", &ival);
		discobj.anzRegionPoints = ival%16;

		for (m=0;  m < (int)discobj.anzRegionPoints;  m++) {
			ptr += strlen(ptr);
			while (*ptr == 0) ptr++;
			sscanf(ptr, "%f", &fval);
			discobj.regionPoint[m].p.x = fval;

			ptr += strlen(ptr);
			while (*ptr == 0) ptr++;
			sscanf(ptr, "%f", &fval);
			discobj.regionPoint[m].p.y = fval;

			ptr += strlen(ptr);
			while (*ptr == 0) ptr++;
			sscanf(ptr, "%d", &ival);
			discobj.regionPoint[m].n = ival;
		}
		if (discobj.was > OBJ_DRAWINGAREA) {
			return(0);                                     /*>>>>>>>>>>> exit >>>>>>>*/
		}
		/*--- get Drawing area parameters -------*/
		if (i == 0) {
			graglob.Limitx = MMTOPIXFACT( discobj.graVal[0].x, xfactor);
			graglob.Limity = MMTOPIXFACT( discobj.graVal[0].y, yfactor);
		}
		if (discobj.was == OBJ_TEXT)
		{
			ptr += strlen(ptr);
			while (*ptr == 0) ptr++;
			sscanf(ptr, "%s", buffer);

			text = 0;
			text = (char *)malloc(strlen(buffer)+1);
			if (!text) {
				xUIfehler(XUINOMEMORY, grawidgets.shell);
				return(0);                                   /*>>>>>>>>>>> exit >>>>>>>*/
			}
			strcpy(text, buffer);
			discobj.text = text;
		}
		else
			discobj.text = NULL;

		/*--- Convert to a GRAFOBJ struct (float to int) --------------------*/
		memobj.was = discobj.was;
		memobj.text = discobj.text;
		memobj.anzRegionPoints = discobj.anzRegionPoints;
		memobj.gc1 = discobj.gc1;
		memobj.gc2 = discobj.gc2;
		memobj.gc3 = discobj.gc3;
		memobj.regionPoint = (REGIONPOINT *)malloc((unsigned long)
										(memobj.anzRegionPoints * sizeof(REGIONPOINT)));
		if (!memobj.regionPoint) {
			xUIfehler(XUINOMEMORY, grawidgets.shell);
			return(False);
		}
		for (j=0; j<memobj.anzRegionPoints; j++) {
			memobj.regionPoint[j].p.x = MMTOPIXFACT(discobj.regionPoint[j].p.x, xfactor);
			memobj.regionPoint[j].p.y = MMTOPIXFACT(discobj.regionPoint[j].p.y, yfactor);
			memobj.regionPoint[j].n = discobj.regionPoint[j].n;
		}
		switch (memobj.was) {
			case OBJ_DRAWINGAREA:
			case OBJ_TEXT:
				memobj.xpoints = (int *)malloc((unsigned long)(2*sizeof(int)));
				memobj.xpoints[0] = MMTOPIXFACT( discobj.graVal[0].x, xfactor);
				memobj.xpoints[1] = MMTOPIXFACT( discobj.graVal[0].y, yfactor);
				break;
			case OBJ_POINT:
				memobj.xpoints = (int *)malloc((unsigned long)(1*sizeof(XPoint)));
				xp = (XPoint *)memobj.xpoints;
				xp->x = MMTOPIXFACT( discobj.graVal[0].x, xfactor);
				xp->y = MMTOPIXFACT( discobj.graVal[0].y, yfactor);
				break;
			case OBJ_LINE:
				memobj.xpoints = (int *)malloc((unsigned long)(2*sizeof(XPoint)));
				xp = (XPoint *)memobj.xpoints;
				xp->x = MMTOPIXFACT( discobj.graVal[0].x, xfactor);
				xp->y = MMTOPIXFACT( discobj.graVal[0].y, yfactor);
				xp++;
				xp->x = MMTOPIXFACT( discobj.graVal[1].x, xfactor);
				xp->y = MMTOPIXFACT( discobj.graVal[1].y, yfactor);
				break;
			case OBJ_RECTANGLE:
			case OBJ_FILLEDRECTANGLE:
				memobj.xpoints = (int *)malloc((unsigned long)(1*sizeof(XRectangle)));
				xr = (XRectangle *)memobj.xpoints;
				xr->x      = MMTOPIXFACT( discobj.graVal[0].x, xfactor);
				xr->y      = MMTOPIXFACT( discobj.graVal[0].y, yfactor);
				xr->width  = MMTOPIXFACT( discobj.graVal[1].x, xfactor);
				xr->height = MMTOPIXFACT( discobj.graVal[1].y, yfactor);
				break;
			case OBJ_ELLIPSE:
			case OBJ_ARC:
			case OBJ_CIRCLE:
			case OBJ_FILLEDELLIPSE:
			case OBJ_FILLEDARC:
			case OBJ_FILLEDCIRCLE:
				memobj.xpoints = (int *)malloc((unsigned long)(1*sizeof(XArc)));
				xa = (XArc *)memobj.xpoints;
				xa->x      = MMTOPIXFACT( discobj.graVal[0].x, xfactor);
				xa->y      = MMTOPIXFACT( discobj.graVal[0].y, yfactor);
				xa->width  = MMTOPIXFACT( discobj.graVal[1].x, xfactor);
				xa->height = MMTOPIXFACT( discobj.graVal[1].y, yfactor);
				xa->angle1 = MMTOPIXFACT( discobj.graVal[2].x, xfactor);
				xa->angle2 = MMTOPIXFACT( discobj.graVal[2].y, yfactor);
				break;
		}
		/*--- add this new grafobject and registrate private regionPoints ----*/
		xGRcreate_grafobj(&memobj);
	}

	/*--- return nb of chars read ---*/
	return( mainptr - graphikBuf); 
}






/*F--------------------------------------------------------------------------
 *  Function:	xGRread_graphik()
 *					-read graphic information from a file (import)
 *					-
 *  In:			-buffer
 *  out:			-
 *  Return:		-nb of chars read 
 *---------------------------------------------------------------------------
 */
Boolean xGRread_graphik(char *graphikfile)
{
	extern long anzgrafObj;
	extern unsigned long anzregionPoints;
	extern Display *display;
	extern GRAGLOB graglob;
	extern GRAWINDOWS grawindows;
	extern GRAWIDGETS grawidgets;

	GRAFOBJDISC discobj;
	GRAFOBJ memobj;
	char inbuf[1024];
	char buffer[512];
	char *text;
	char *ptr;
	char was;
	FILE *fp;
	int j;
	int m;
	int anzgraval;
	float fval;
	int   ival;
	long i;
	unsigned width, height;
	Boolean ok;
	WCVALUE		xfactor, yfactor;       /*local factors for speed enhance*/
	XPoint		*xp;
	XRectangle	*xr;
	XArc			*xa;

	/*--- inits -------------*/
	xfactor = graglob.xfak;
	yfactor = graglob.yfak;

	/*--- Graphikfile er�ffnen */
	fp = fopen(graphikfile, _P_READ_);
	if (!fp) {
		xUIfehler(XGRGRAFILE, grawidgets.shell);
		return(False);
	}

	anzgrafObj = 0;
	anzregionPoints = 0;
	i = 0;
	/*while (fread((void *)&discobj, sizeof(GRAFOBJDISC), 1, fp)) {*/

	while (fgets(inbuf, sizeof(inbuf), fp))
		{
		for (ptr=inbuf; *ptr!='\n'; ptr++) {
			if (*ptr == ' ') *ptr=0;
		}

		ptr = inbuf;
		sscanf(ptr, "%c", &was);
		discobj.was = (was-65)%16;

		ptr += strlen(ptr);
		while (*ptr == 0) ptr++;
		sscanf(ptr, "%d", &ival);
		discobj.gc1 = (unsigned char)ival;

		ptr += strlen(ptr);
		while (*ptr == 0) ptr++;
		sscanf(ptr, "%d", &ival);
		discobj.gc2 = (unsigned char)ival;

		ptr += strlen(ptr);
		while (*ptr == 0) ptr++;
		sscanf(ptr, "%d", &ival);
		discobj.gc3 = (unsigned char)ival;

		switch (discobj.was) {
			case OBJ_DRAWINGAREA:
			case OBJ_TEXT:
			case OBJ_POINT:
				anzgraval = 1;
				break;
			case OBJ_LINE:
			case OBJ_RECTANGLE:
			case OBJ_FILLEDRECTANGLE:
				anzgraval = 2;
				break;
			case OBJ_ELLIPSE:
			case OBJ_FILLEDELLIPSE:
			case OBJ_CIRCLE:
			case OBJ_FILLEDCIRCLE:
			case OBJ_ARC:
			case OBJ_FILLEDARC:
				anzgraval = 3;
				break;
		}
		for (m=0; m<anzgraval; m++) {
			ptr += strlen(ptr);
			while (*ptr == 0) ptr++;
			sscanf(ptr, "%f", &fval);
			discobj.graVal[m].x = fval;

			ptr += strlen(ptr);
			while (*ptr == 0) ptr++;
			sscanf(ptr, "%f", &fval);
			discobj.graVal[m].y = fval;
		}

		ptr += strlen(ptr);
		while (*ptr == 0) ptr++;
		sscanf(ptr, "%d", &ival);
		discobj.anzRegionPoints = ival%16;

		for (m=0; m<discobj.anzRegionPoints; m++) {
			ptr += strlen(ptr);
			while (*ptr == 0) ptr++;
			sscanf(ptr, "%f", &fval);
			discobj.regionPoint[m].p.x = fval;

			ptr += strlen(ptr);
			while (*ptr == 0) ptr++;
			sscanf(ptr, "%f", &fval);
			discobj.regionPoint[m].p.y = fval;

			ptr += strlen(ptr);
			while (*ptr == 0) ptr++;
			sscanf(ptr, "%d", &ival);
			discobj.regionPoint[m].n = ival;
		}
		if (discobj.was > OBJ_DRAWINGAREA) {
			xUIfehler(XGRGRAFORMAT, grawidgets.shell);
			return(False);
		}
		if (i == 0) {
			graglob.Limitx = MMTOPIXFACT( discobj.graVal[0].x, xfactor);
			graglob.Limity = MMTOPIXFACT( discobj.graVal[0].y, yfactor);
		}
		if (discobj.was == OBJ_TEXT)
		{
			/*fscanf(fp, "%s", buffer);*/
			ptr += strlen(ptr);
			while (*ptr == 0) ptr++;
			sscanf(ptr, "%s", buffer);

			text = 0;
			text = (char *)malloc(strlen(buffer)+1);
			if (!text) {
				xUIfehler(XUINOMEMORY, grawidgets.shell);
				return(False);
			}
			strcpy(text, buffer);
			discobj.text = text;
		}
		else
			discobj.text = NULL;

		/*--- convert to a GRAFOBJ struct -----------------------------------*/
		memobj.was = discobj.was;
		memobj.text = discobj.text;
		memobj.anzRegionPoints = discobj.anzRegionPoints;
		memobj.gc1 = discobj.gc1;
		memobj.gc2 = discobj.gc2;
		memobj.gc3 = discobj.gc3;
		memobj.regionPoint = (REGIONPOINT *)malloc((unsigned long)
		(memobj.anzRegionPoints * sizeof(REGIONPOINT)));
		if (!memobj.regionPoint) {
			xUIfehler(XUINOMEMORY, grawidgets.shell);
			return(False);
		}
		for (j=0; j<memobj.anzRegionPoints; j++) {
			memobj.regionPoint[j].p.x = MMTOPIXFACT(discobj.regionPoint[j].p.x, xfactor);
			memobj.regionPoint[j].p.y = MMTOPIXFACT(discobj.regionPoint[j].p.y, yfactor);
			memobj.regionPoint[j].n = discobj.regionPoint[j].n;
		}
		switch (memobj.was) {
			case OBJ_DRAWINGAREA:
			case OBJ_TEXT:
				memobj.xpoints = (int *)malloc((unsigned long)(2*sizeof(int)));
				memobj.xpoints[0] = MMTOPIXFACT( discobj.graVal[0].x, xfactor);
				memobj.xpoints[1] = MMTOPIXFACT( discobj.graVal[0].y, yfactor);
				break;
			case OBJ_POINT:
				memobj.xpoints = (int *)malloc((unsigned long)
				(1*sizeof(XPoint)));
				xp = (XPoint *)memobj.xpoints;
				xp->x = MMTOPIXFACT( discobj.graVal[0].x, xfactor);
				xp->y = MMTOPIXFACT( discobj.graVal[0].y, yfactor);
				break;
			case OBJ_LINE:
				memobj.xpoints = (int *)malloc((unsigned long)
				(2*sizeof(XPoint)));
				xp = (XPoint *)memobj.xpoints;
				xp->x = MMTOPIXFACT( discobj.graVal[0].x, xfactor);
				xp->y = MMTOPIXFACT( discobj.graVal[0].y, yfactor);
				xp++;
				xp->x = MMTOPIXFACT( discobj.graVal[1].x, xfactor);
				xp->y = MMTOPIXFACT( discobj.graVal[1].y, yfactor);
				break;
			case OBJ_RECTANGLE:
			case OBJ_FILLEDRECTANGLE:
				memobj.xpoints = (int *)malloc((unsigned long)
				(1*sizeof(XRectangle)));
				xr = (XRectangle *)memobj.xpoints;
				xr->x      = MMTOPIXFACT( discobj.graVal[0].x, xfactor);
				xr->y      = MMTOPIXFACT( discobj.graVal[0].y, yfactor);
				xr->width  = MMTOPIXFACT( discobj.graVal[1].x, xfactor);
				xr->height = MMTOPIXFACT( discobj.graVal[1].y, yfactor);
				break;
			case OBJ_ELLIPSE:
			case OBJ_ARC:
			case OBJ_CIRCLE:
			case OBJ_FILLEDELLIPSE:
			case OBJ_FILLEDARC:
			case OBJ_FILLEDCIRCLE:
				memobj.xpoints = (int *)malloc((unsigned long)
				(1*sizeof(XArc)));
				xa = (XArc *)memobj.xpoints;
				xa->x      = MMTOPIXFACT( discobj.graVal[0].x, xfactor);
				xa->y      = MMTOPIXFACT( discobj.graVal[0].y, yfactor);
				xa->width  = MMTOPIXFACT( discobj.graVal[1].x, xfactor);
				xa->height = MMTOPIXFACT( discobj.graVal[1].y, yfactor);
				xa->angle1 = MMTOPIXFACT( discobj.graVal[2].x, xfactor);
				xa->angle2 = MMTOPIXFACT( discobj.graVal[2].y, yfactor);
				break;
		}
		/*--- add this new grafobject --------*/
		xGRcreate_grafobj(&memobj);
		i++;
	}
	fclose(fp);

	return(True);
}




/*F--------------------------------------------------------------------------
 *  Function:	xGRread_graphikdata_default( )
 *					-create at least One graphic object: the drawing area
 *					-
 *  In:			-
 *  out:			-
 *  Return:		-nb of chars read 
 *---------------------------------------------------------------------------
 */
void xGRread_graphikdata_default()
{
	extern ApplicationData app_data;
	extern unsigned long anzregionPoints;
	extern long			anzgrafObj;
	extern GRAGLOB		graglob;

	GRAFOBJ		obj;
	Dimension	w, h;

	/*--- Forget oldies new will be created ------*/
	anzregionPoints = 0;

	/*----- 1. Grafikobjekt = Zeichenfl�che setzen ------*/
	if (anzgrafObj <= 0) {
		w = app_data.breite * graglob.xfak;
		h = app_data.hoehe  * graglob.yfak;
		obj.was = OBJ_DRAWINGAREA;
		obj.gc1 = 0;
		obj.gc2 = 0;
		obj.gc3 = 0;
		obj.text = 0;
		obj.xpoints = (int *)malloc((unsigned long)(2*sizeof(int)));
		obj.xpoints[0] = w;
		obj.xpoints[1] = h;
		obj.regionPoint = (REGIONPOINT *)malloc((unsigned long)(4*sizeof(REGIONPOINT)));
		obj.anzRegionPoints = 4;
		obj.regionPoint[0].p.x = 0;
		obj.regionPoint[0].p.y = 0;
		obj.regionPoint[0].n   = 0;
		obj.regionPoint[1].p.x = w;
		obj.regionPoint[1].p.y = 0;
		obj.regionPoint[1].n   = 0;
		obj.regionPoint[2].p.x = w;
		obj.regionPoint[2].p.y = h;
		obj.regionPoint[2].n   = 0;
		obj.regionPoint[3].p.x = 0;
		obj.regionPoint[3].p.y = h;
		obj.regionPoint[3].n   = 0;
		/*--- Limits ----------------*/
		graglob.Limitx = w;
		graglob.Limity = h;
		/*--- drawing area grafobject is mandatory -----*/
		xGRcreate_grafobj(&obj);
	}

}



/*F--------------------------------------------------------------------------
 *  Function:	xGRread_line( )
 *					-get string with included blanks till delimiter
 *					-
 *  In:			-delimiter character
 *  out:			-ad of source, destination
 *  Return:		-nb of characters INCLUSIVE delim (no need to skip delim!)
 *---------------------------------------------------------------------------
 */
static int  xGRread_line( char *pd, char *ps )
{
	int	i;
 
	/*-- copy till delim ------------------------*/
	for ( i=0;  *ps != END_OF_LINE;  i++, ps++, pd++ )
	{  
		if ((*ps == ' ') || (*ps == '\t'))
			*pd = '\0';							/*replace source*/
		else
			*pd = *ps ;							/*copy source*/
	}

	*pd ='\0';
	i++; 					/* skip delim */
	return (i); 
}


