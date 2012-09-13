/**************************************************************/
/* Modul:     ganzes Bild vergroessern/verkleinern            */
/*                                                            */
/* Uebergabe: RASTERIMAGE  the image struct                   */
/*            w/h			   new width and height               */
/*                                                            */
/* Functions: ORresize                                        */
/*                                                            */
/* Copyright: Yafra.org     */
/* Autor:     Administrator, Yafra.org                     */
/**************************************************************/
#include <psmume.h>

static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/psmume/source/orrsize.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

extern unsigned char BSETmask[];
extern unsigned char BCLRmask[];

int ORresize(RASTERIMAGE *img, unsigned int XnewWinW, unsigned int XnewWinH)
{
	unsigned char *ShowData;
	XImage *tmpXImage;

	unsigned char *orgptr;
	unsigned int orgY;
	unsigned int orgX;
	unsigned long int tmpPos;
	unsigned long int orgPos;
	unsigned short int whichBit;
	unsigned long int whichByte;

	unsigned char *newptr;
	unsigned int newX;
	unsigned int newY;
	unsigned long int newPos = 0;
	unsigned short int newBitPos = 0;

	unsigned int XcurWinW = img->Width; 
	unsigned int XcurWinH = img->Height;

	unsigned int allocW;

	/* Neue XImage Struktur allozieren */
	tmpXImage = (XImage *)XtMalloc(sizeof(XImage));
	tmpXImage->xoffset = 0;
	tmpXImage->byte_order = LSBFirst;
	tmpXImage->bitmap_unit = 8;
	tmpXImage->bitmap_bit_order = MSBFirst;
	tmpXImage->bitmap_pad = 8;
	tmpXImage->bits_per_pixel = img->Show.XImg->bits_per_pixel;
	tmpXImage->format = img->Show.XImg->format;

	/* Vorherige XImage Daten l�schen */
	if (img->Show.XImg != NULL)
		{
		if (img->Show.XImg->data != NULL)
			free((void *)img->Show.XImg->data);
		img->Show.XImg->data = NULL;
		XtFree((char *)img->Show.XImg);
		img->Show.XImg = NULL;
		}

	if (img->Type == 1)  /* B I T M A P */
		{
		/* Alloziere neuen Datenbuffer */
		allocW = (XnewWinW + 7) / 8;
		ShowData = (unsigned char *)malloc(allocW * XnewWinH);
		if (!ShowData)
			return(MALLOC);

		/* Init XImage Struktur */
		tmpXImage->bytes_per_line = allocW;
		tmpXImage->depth = 1;
		tmpXImage->format = XYBitmap;

		orgptr = img->Data;  /* Daten des Original Bildes        */
		newptr = ShowData;            /* Daten des zu erstellenden Bildes */
		
		/* RESIZING the image */
		for (newY = 0; newY < XnewWinH; newY++)
			{
			orgY = (XcurWinH * newY) / XnewWinH;
			orgPos = (orgY * XcurWinW);
			tmpPos = orgPos;
			for (newX = 0; newX < XnewWinW; newX++)
				{
				orgX = (XcurWinW * newX) / XnewWinW;
				orgPos = tmpPos + orgX;
				whichByte = orgPos / 8;
				whichBit = orgPos - (whichByte * 8);
				if (orgptr[whichByte] & BSETmask[whichBit])
					newptr[newPos] |= BSETmask[newBitPos];
				else
					newptr[newPos] &= BCLRmask[newBitPos];
				newBitPos++;
				if (newBitPos > 7)
					{
					newBitPos = 0;
					newPos++;
					}
				}
			if (allocW != (XnewWinW / 8))
				{
				newPos++;
				newBitPos = 0;
				}
			}
		}

	else               /* Z P I X M A P */
		{
		/* Alloziere neuen Datenbuffer */
		ShowData = (unsigned char *)malloc(XnewWinW * XnewWinH);
		if (!ShowData)
			return(MALLOC);

		/* Init XImage Struktur */
		tmpXImage->bytes_per_line = XnewWinW;
		tmpXImage->depth = XDefaultDepthOfScreen(XtScreen(img->WImg));
		tmpXImage->format = ZPixmap;

		orgptr = img->Data;  /* Daten des Original Bildes        */
		newptr = ShowData;            /* Daten des zu erstellenden Bildes */

		for (newY = 0; newY < XnewWinH; newY++)
			{
			orgY = (XcurWinH * newY) / XnewWinH;
			orgPos = orgY * XcurWinW;
			tmpPos = orgPos;
			for (newX = 0; newX < XnewWinW; newX++)
				{
				orgX = (XcurWinW * newX) / XnewWinW;
				orgPos = tmpPos + orgX;
				newptr[newPos++] = orgptr[orgPos];
				}
			}
		}

	/* Erstelle XImage Struktur */
	tmpXImage->data = (char *)ShowData;
	tmpXImage->width = XnewWinW;
	tmpXImage->height = XnewWinH;

	/* Erstelle neue ShowImg Struktur */
	img->Show.XImg = tmpXImage;
	img->Show.Width = XnewWinW;
	img->Show.Height = XnewWinH;

	return(MOK); /* alles gut gegangen */
}
