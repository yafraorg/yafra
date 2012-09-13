/**************************************************************/
/* Modul:     Laden und bereitstellen vom PBM Dateien         */
/*                                                            */
/* Functions: PBMLoad                                         */
/*                                                            */
/* Copyright: Yafra.org     */
/* Autor:     Administrator, Yafra.org                     */
/*            based strongly on Patrick J. Naughton, 1989     */
/*                                                            */
/* History:   May 1992 mw Erstellung                          */
/**************************************************************/
#include <psmume.h>
#include "pbm.h"

static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/psmume/source/pbmload.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

extern unsigned char BSETmask[];
extern unsigned char BCLRmask[];

/**************************************************************/
/* Funktion:  Lese ein PBM Bild                               */
/*                                                            */
/**************************************************************/
int PBMLoad(RASTERIMAGE *img)
{
	FILE *PBMfp;
	int Format;
	int Width;
	int Height;
	int MaxPixel;
	int MaxBytes;

	char tmpMsg[160];

	PBMfp = pm_openr(img->Name);
	if (PBMfp == NULL)
		return(MOPEN);

	pbm_readpbminit(PBMfp, &Width, &Height, &Format);	

	/* Setze globale Bildstruktur */
	img->Type = BITMAP;
	img->Width = Width;
	img->Height = Height;

	MaxBytes = Width % 8;
	if (MaxBytes != 0)
		{
		unsigned char *tmpzeile;
		unsigned char *rootptr;
		register int i, k;
		unsigned int allocW;
		unsigned int tmpBit;
		unsigned int tmpByte;
		unsigned int rootBit = 0;

		/* Allocate the Root image */
		allocW = ((Width * Height) / 8) + 1;
		img->Data = (unsigned char *)malloc(allocW); /* Bitmapbuffer allozieren */
		if (!img->Data)
			return(MALLOC);

		rootptr = img->Data;
		MaxBytes = (Width / 8) + 1;
		tmpzeile = (unsigned char *)malloc(MaxBytes);

		for (i=0; i < Height; i++)
			{
			tmpByte = 0;
			tmpBit = 0;
			fread(tmpzeile, MaxBytes, 1, PBMfp);
			/* F�lle Bytes im img->Data Buffer mit Bits aus File */
			for (k=0; k < Width; k++)
				{
				if (tmpzeile[tmpByte] & BSETmask[tmpBit])
					*rootptr |= BSETmask[rootBit];
				else
					*rootptr &= BCLRmask[rootBit];

				rootBit++;
				tmpBit++;

				if (rootBit > 7)
					{
					rootptr++;
					rootBit = 0;
					}

				if (tmpBit > 7)
					{
					tmpByte++;
					tmpBit = 0;
					}
				}
			}
		free(tmpzeile);
		}

	else
		{
		MaxBytes = (Width * Height) / 8;

		/* Allocate the Root image */
		img->Data = (unsigned char *)malloc(MaxBytes); /* Bitmapbuffer allozieren */
		if (!img->Data)
			return(MALLOC);

		/* lese komprimierte Daten */
		if (fread(img->Data, (MaxBytes), 1, PBMfp) != 1)
			return(MREAD);
		}

	/* Schliesse Datei */
	fclose(PBMfp);
}
