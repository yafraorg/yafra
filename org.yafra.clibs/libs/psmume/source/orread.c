/**************************************************************/
/* Modul:     Read a Bitmap or a Pixmap                       */
/*                                                            */
/* Functions: ORread                                          */
/*            WhichImage                                      */
/*                                                            */
/* Copyright: Yafra.org     */
/* Autor:     Administrator, Yafra.org                     */
/*                                                            */
/* History:   May 1992 mw Erstellung                          */
/**************************************************************/
#include <stdio.h>
#include <psmume.h>
#include "version.h"

static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/psmume/source/orread.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

/* GLOBAL Data Definition with initialization ! */
/* Reihenfolge 76543210 
unsigned char BSETmask[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
unsigned char BCLRmask[8] = {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};
  Reihenfolge 01234567 */
unsigned char BSETmask[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
unsigned char BCLRmask[8] = {0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE};

/* local prototyp */
static unsigned short int WhichImage(char *);

/**************************************************************/
/* Funktion:  Lese ein Pixelbild ein und zeige es an          */
/*                                                            */
/* Uebergabe:                                                 */
/**************************************************************/
int ORread(RASTERIMAGE *img)
{
	unsigned short int ImageID;
	Dimension width, height;
	Arg     args[10];
	register int ac;
	register int cret;

	/* check if img allocated */
	if (img == NULL)
		return(MNOMOREIMG);

	/* Wurde ein Bildname eingegeben ? */
	if (img->Name == NULL || *img->Name == (char)NULL)
		return(MNOIMGNAME);

	/* allocate XImage struct if not yet */
	if (img->Show.XImg == NULL)
		{
		img->Show.XImg = (XImage *)XtMalloc(sizeof(XImage));
		if (img->Show.XImg == NULL)
			return(MNOMOREIMG);
		img->Show.XImg->data = NULL;
		}

	/* Create graphical context 
	img->Show.ImgGC = XCreateGC(XtDisplay(img->WImg),
		RootWindowOfScreen(XtScreen(img->WImg)), 0, NULL);
	*/

	/* Ermittle Bildtyp */
	ImageID = WhichImage(img->Name);

	/* Load external Image */
	switch (ImageID)
		{
		case PBM:
			cret = PBMLoad(img);
			break;
		case PPM:
			cret = PPMLoad(img);
			break;
		default:
			cret = MWRONGIMG;
			break;
		}

	return(cret);
}

/**************************************************************/
/* Funktion:  Entscheide welcher Bildtyp es ist. Die ersten   */
/*            3 Bytes gen�gen um die ID eines Bildes festzu-  */
/*            stellen.                                        */
/*                                                            */
/* Uebergabe: Name und Pfad der Bilddatei                     */
/*                                                            */
/* Rueckgabe: ID Nummer des Bildtyps (PCX, GIF, CCITT)        */
/**************************************************************/
static unsigned short int WhichImage(char *file)
{
	FILE *Imagefp;
	unsigned char ID[3];
	unsigned short int cid;
	int cret;
	char *triid = "PS9";

	if ((Imagefp = fopen(file, "r")) == NULL)
		return(MOPEN);
	
	/* Lies die ersten 3 Bytes der Bilddatei (die gen�gen f�r die ID) */
	cret = fread(ID, sizeof(ID), 1, Imagefp);
	if (cret != 1)
		return(MREAD);

	/* Entscheide um welches Bild es sich handelt */
	if (ID[0] == 'P' && ID[1] == '4')
		cid = PBM;
	else if (ID[0] == 'P' && ID[1] == '6')
		cid = PPM;
	else if (!(strncmp((char *)ID, triid, 3)))
		cid = TRI;
	else
		cid = UNKNOWNIMG;

	/* Schliesse File wieder */
	fclose(Imagefp);

	/* Bildtyp zur�ckgeben */
	return cid;
}
