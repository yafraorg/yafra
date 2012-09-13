/**************************************************************/
/* Modul:     Laden und bereitstellen eines PPM Bildes        */
/*                                                            */
/* Functions: PPMLoad                                         */
/*                                                            */
/* Copyright: Yafra.org     */
/* Autor:     Administrator, Yafra.org                     */
/*                                                            */
/* History:   01.04.1992 mw Erstellung                        */
/**************************************************************/
#include <psmume.h>
#include "ppm.h"
#include "ppmcmap.h"

static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/psmume/source/ppmload.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

#define MAXCOLORS 256

extern unsigned char BSETmask[];
extern unsigned char BCLRmask[];

static pixel** pixels;
static colorhash_table cht;

/* Color specific Globals */
extern struct point
{
   int rgb[3];
   int cnt;
   int orig_index;
};

extern struct ptlist 
{
   int n;
   struct point *pp[256];
};

extern struct box
{
   int min[3];
   int max[3];
   int mid[3];
   int num_pts;
   int total_cnt;
   struct ptlist *pl;
   int longest_color;		/* R, G, or B */
   int max_length;		/* length of the box along longest color */
   XColor xc;
   int sum_dist;
};
static struct box *bxl[256];

/* local Prototyps */
static int ColorDicking(RASTERIMAGE *);
static int do_boxing(RASTERIMAGE *, int); 
static struct ptlist *empty_ptlist(void);
static struct box *make_box(RASTERIMAGE *,struct ptlist *);
static int dist(int, int, int, int, int, int);
static int colorstobpp(int);

/* Farbwerte */
int used_cnt[256];
unsigned char used[256];
int  numused;
int Red[256];
int Green[256];
int Blue[256];
int boxtype;
unsigned long cols[256];
XColor        defs[256];
int           numcols;

#define R 0
#define G 1
#define B 2
#define NUMBOXES 9999


/**************************************************************/
/* Funktion:  Lade PPMdaten und stelle sie in EI und RootDate */
/*                                                            */
/**************************************************************/
int PPMLoad(RASTERIMAGE *img)
{
	FILE *PPMfp;
	int Format;
	int Width;
	int Height;
	int cret;
	unsigned long int Pos;
   int argn, rows, colors, i, BitsPerPixel;
   int interlace;
   pixval maxval;
   colorhist_vector chv;
	register unsigned int x, y;
	XColor PPMColor;

	PPMfp = pm_openr(img->Name);
	if (PPMfp == NULL)
		return(MOPEN);
	pixels = ppm_readppm(PPMfp, &Width, &Height, &maxval);
	pm_close(PPMfp);
	
	/* Figure out the colormap. */
	pm_message( "computing colormap..." );
	chv = ppm_computecolorhist(pixels, Width, Height, MAXCOLORS, &colors);
	if (chv == (colorhist_vector) 0 )
		return(MREAD);
	
	/* Now turn the ppm colormap into the appropriate GIF colormap. */
	for ( i = 0; i < colors; i++)
		{
		Red[i] = PPM_GETR( chv[i].color );
		Green[i] = PPM_GETG( chv[i].color );
		Blue[i] = PPM_GETB( chv[i].color );
		used[i] = 0;
		used_cnt[i] = 0;
		}
	numcols = numused = colors;
	BitsPerPixel = colorstobpp( colors );
	
	/* And make a hash table for fast lookup. */
	cht = ppm_colorhisttocolorhash( chv, colors );

	/* Setze globale Bildstruktur */
	img->Type = ZPIXMAP;
	img->Width = Width;
	img->Height = Height;
	img->Show.XImg->bits_per_pixel = BitsPerPixel;
	img->Show.XImg->format = ZPixmap;

	/* Allocate the Root image */
	img->Data = (unsigned char *)malloc((Width * Height)); /* Bitmapbuffer allozieren */
	if (!img->Data)
		return(MALLOC);

	for (y=0; y < Height; y++)
		{
		Pos = y * Width;
		for (x=0; x < Width; x++, Pos++)
			{
			register int tmp;

			tmp = img->Data[Pos] = (unsigned char)ppm_lookupcolor(cht, &pixels[y][x]);
			used[tmp] = 1;
			used_cnt[tmp]++;
			}
		}

	ppm_freecolorhist( chv );
	free(pixels);

	cret = ColorDicking(img);

	return(cret);
}

static int colorstobpp(int colors)
{
	int bpp;
	
	if ( colors <= 2 )
		bpp = 1;
	else if ( colors <= 4 )
		bpp = 2;
	else if ( colors <= 8 )
		bpp = 3;
	else if ( colors <= 16 )
		bpp = 4;
	else if ( colors <= 32 )
		bpp = 5;
	else if ( colors <= 64 )
		bpp = 6;
	else if ( colors <= 128 )
		bpp = 7;
	else if ( colors <= 256 )
		bpp = 8;
	else
		pm_error( "can't happen" );
	
	return bpp;
}


/**************************************************************/
/* Funktion:  Setze Farben im X                               */
/**************************************************************/
static int ColorDicking(RASTERIMAGE *img)
{
	register int   i,j;
	unsigned char *ptr;
	int cret;
	
	cret = do_boxing(img, boxtype);
	
	ptr = img->Data;
	for (i=0; i < img->Height; i++)
		for (j=0; j < img->Width; j++, ptr++) 
			*ptr = (unsigned char)cols[*ptr];
}

/**************************************************************/
/* Funktion:  Erstelle Boxen                                  */
/*                                                            */
/* Uebergabe: Boxtyp                                          */
/**************************************************************/
static int do_boxing(RASTERIMAGE *img, int type)
{
	struct point pts[256];
	struct ptlist *pl, *pl2, *pl3;
	int boxcnt = 0;
	int max_metric;
	int bi;
	struct box *b, *bx2, *bx3;
	int cmax, imax, i, pi;
	
	/* Set up points from Red[], Green[], Blue[], and used_cnt[].
	 * Put all the points in one list to start. */
	pl = empty_ptlist();
	pl->n = 0;
	for (i = 0; i < numcols; i++)
		{
		pts[i].rgb[R] = Red[i];
		pts[i].rgb[G] = Green[i];
		pts[i].rgb[B] = Blue[i];
		pts[i].cnt = used_cnt[i];
		pts[i].orig_index = i;
		if (used_cnt[i] > 0)
			{
			pl->pp[pl->n] = &pts[i];
			pl->n++;
			}
		}
	
	/* make the first box from that list */
	b = make_box(img, pl);
	if (b == NULL)
		return(MCOLORALLOC);

	bxl[boxcnt++] = b;
	
	/* as long as I can keep getting new color cells, pick the biggest
		* box and split it into two boxes.
		*/
	while (1)
		{
		/* choose the box with the biggest max dimension. 
			* [Alternate algorithms could choose most points or biggest
			* total_cnt (as long as points > 1)].
			* In any case we must set imax to be the box to split, and
			* cmax to be the color to split it along.
			*
			* type = 0 => split max dimension
			* type = 1 => split box with most points
			* type = 2 => split box with biggest total count
			* type = 3 => split box with biggest sum of distances
			*/
		max_metric = -1;
		for (bi = 0; bi < boxcnt; bi++)
			{
			b = bxl[bi];
			switch (type)
				{
				case 0:
					if (b->max_length > max_metric)
						{
						max_metric = b->max_length;
						imax = bi;
						cmax = b->longest_color;
						}
					break;
				case 1:
					if (b->num_pts > max_metric)
						{
						max_metric = b->num_pts;
						imax = bi;
						cmax = b->longest_color;
						}
					break;
				case 2:
					if ((b->total_cnt > max_metric) && (b->max_length > 0))
						{
						max_metric = b->total_cnt;
						imax = bi;
						cmax = b->longest_color;
						}
					break;
				case 3:
					if ((b->sum_dist > max_metric) && (b->max_length > 0))
						{
						max_metric = b->sum_dist;
						imax = bi;
						cmax = b->longest_color;
						}
					break;
				default:
					return(MCOLORALLOC);
				}
			}
		/* if biggest dimension is 1 OR
			* if no box has > 1 point OR
			* if biggest total count is 1 (unlikely).
			* THEN we're done.
			*/
		if (max_metric <= 1)
			break;
		
		/* now split that box */
		pl2 = empty_ptlist();
		pl3 = empty_ptlist();
		b = bxl[imax];

		/* assign each point in the box to one of two sub-boxes,
		 * depending on whether they're above or below the midpoint
		 * in the maximum dimension (cmax) */
		for (pi = 0; pi < b->pl->n; pi++)
			{
			struct point *p = b->pl->pp[pi];
			if (p->rgb[cmax] > b->mid[cmax])
				pl3->pp[pl3->n++] = p;
			else
				pl2->pp[pl2->n++] = p;
			}

		/* make children into real boxes */
		if ((bx2 = make_box(img, pl2)) == NULL) break;
		if ((bx3 = make_box(img, pl3)) == NULL) break;

		/* give up the color of the old parent */
		XFreeColors(XtDisplay(img->WImg), img->ImageMap, &(b->xc.pixel), 1, 0L);
		
		/* replace b with bx2 in bxl[] */
		bxl[imax] = bx2;

		/* add bx3 to end of bxl list */
		bxl[boxcnt++] = bx3;
		if (boxcnt >= (int)NUMBOXES)
			break;		/* used all we were told to */
		
		}

	/* For each box, use its color to set the color of each point in it */
	for (bi = 0; bi < boxcnt; bi++)
		{
		int j;
		pl = bxl[bi]->pl;
		for (j = 0; j < pl->n; j++)
			cols[pl->pp[j]->orig_index] = bxl[bi]->xc.pixel;
		}

	/* Free the boxes */
	free(pl);
	free(pl2);
	free(pl3);

	free(b);
	free(bx2);
	free(bx3);

	return(MOK);
}

/**************************************************************/
/* Funktion:  Erstelle leere Punktliste                       */
/*                                                            */
/* Rueckgabe: Punktliste                                      */
/**************************************************************/
static struct ptlist *empty_ptlist(void)
{
   struct ptlist *p;
	
   p = (struct ptlist *)malloc(sizeof(struct ptlist));
   p->n = 0;
   return(p);
}

/**************************************************************/
/* Funktion:  Erstelle Boxen                                  */
/*                                                            */
/* Uebergabe: Punktliste                                      */
/**************************************************************/
static struct box *make_box(RASTERIMAGE *img, struct ptlist *pl)
{
	struct box *b;
	int c;
	int pi;
	int sums[3];		/* sum of cnt*rgb values */
	
   b = (struct box *)malloc(sizeof(struct box));
   b->min[R] = b->min[G] = b->min[B] = 255;
   b->max[R] = b->max[G] = b->max[B] = 0;
	
   /* ignore mid for now */
   b->num_pts = 0;
   b->total_cnt = 0;
   b->sum_dist = 0;
   b->pl = pl;
	
   /* figure out bounds for each dimension */
   sums[R] = sums[G] = sums[B] = 0;
   for (pi = 0; pi < pl->n; pi++)
		{
	   struct point *pt = pl->pp[pi];
      for (c = R; c <=B; c++)
			{
	      if (pt->rgb[c] > b->max[c])
		      b->max[c] = pt->rgb[c];
			
	      if (pt->rgb[c] < b->min[c])
		      b->min[c] = pt->rgb[c];
			
	      sums[c] += (pt->cnt * pt->rgb[c]);
			}
	   b->total_cnt += pt->cnt;
	   b->num_pts++;
		}
   b->max_length = -1;		/* this will surely be exceeded */
	
   /* set the mid points for each dimension */
   for (c = R; c <=B; c++)
		{
/*??? b->mid[c] = (b->min[c] + b->max[c]) / 2; */
	   b->mid[c] = sums[c] / b->total_cnt;
	   if (b->max[c] - b->min[c] > b->max_length)
			{
	      b->longest_color = c;
	      b->max_length = b->max[c] - b->min[c];
			}
		}
   b->xc.red = (unsigned short)b->mid[R] << 8;
   b->xc.green = (unsigned short)b->mid[G] << 8;
   b->xc.blue = (unsigned short)b->mid[B] << 8;
   b->xc.flags = DoRed | DoGreen | DoBlue;
	
   for (pi = 0; pi < pl->n; pi++)
		{
	   struct point *pt = pl->pp[pi];
	   b->sum_dist += (pt->cnt * dist(b->mid[R], b->mid[G], b->mid[B],
												 pt->rgb[R], pt->rgb[G], pt->rgb[B]));
		
	   if (b->sum_dist < 0)
	      return(NULL);
		}
	
	/*--- Alloc the color in the cmap and return the pixel (ptr to cmap) */
	if (XAllocColor(XtDisplay(img->WImg), img->ImageMap, &(b->xc)))
		return(b);
	else
		return(NULL);
}

/**************************************************************/
/* Funktion:  dist                                            */
/*                                                            */
/* Uebergabe: RGB Werte                                       */
/*                                                            */
/* Rueckgabe: Boxtyp                                          */
/**************************************************************/
static int dist(int r1, int g1, int b1, int r2, int g2, int b2)
{
	int ret, delta;
	
	ret = 0;
	delta = r1 - r2;
	if (delta < 0) delta = -delta;
	ret += delta;
	delta = g1 - g2;
	if (delta < 0) delta = -delta;
	ret += delta;
	delta = b1 - b2;
	if (delta < 0) delta = -delta;
	ret += delta;
	return(ret);
}
