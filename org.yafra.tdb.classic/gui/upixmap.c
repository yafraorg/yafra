/*D***********************************************************
 * Modul:	GUI - dialog			upixmap.c
 * 	                                       
 *				Create a X11 pixmap
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************
 */
#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/upixmap.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";

/*************************************************************************/
/* Make_IconPixmap setzt die Resource XmNiconPixmap des Widgets fenster. */
/* Die Pixmap wird aus dem file, das als 2. Eingabeparameter uebergeben  */
/* wird (Bitmapdatei) erstellt. Die Bitmapdatei wird mit der bitmap      */
/* Utility von X gezeichnet.                                             */
/*                                                                       */
/* Rueckgabewert : 0 bei Fehler                                          */
/*                 Pixmap bei erfolgreicher Abarbeitung                  */
/*                                                                       */
/* Erstellt :  Sept. 1991 WSp                                            */
/* Ge�ndert :  Okt.  1991 pi                                             */
/*************************************************************************/
Pixmap xUIpixmap(Display *display, char *bitmapfilename,
unsigned long *hotspot_x, unsigned long *hotspot_y)
{
	Pixmap             pix; 
 long unsigned int  foreground, background;
 long unsigned int  width, height, depth=1;
 long unsigned int  zeichen;
 char              *bits;
 unsigned int       i,j,n;
 FILE               *datei; 
 char               buf1[1000];    
 char               buf2[1000];   

#ifdef ps_unix
	struct stat        stbuf;  
	if (stat(bitmapfilename, &stbuf) == -1)
		return(0);
 
	if( (datei = fopen(bitmapfilename, _P_READ_))==NULL )
		return(0);
 
	if( (bits=(char *)malloc(((unsigned)stbuf.st_size)*sizeof(char)))==NULL )
		return(0);
#endif

#ifdef ps_win
#ifndef ps_humm
	struct stat        stbuf;  
	if (stat(bitmapfilename, &stbuf) == -1)
		return(0);
#endif

	if( (datei = fopen(bitmapfilename, _P_READ_))==NULL )
		return(0);

#ifdef ps_humm
	if( (bits=(char *)malloc(((unsigned)_filelength(_fileno(datei)))*sizeof(char)))==NULL )
		return(0);
#else
	if( (bits=(char *)malloc(((unsigned)stbuf.st_size)*sizeof(char)))==NULL )
		return(0);
#endif

#endif

 *bits = 0;
 (*hotspot_x)=0;
 (*hotspot_y)=0;
 /*************************************************************************/
 /* Bitmap Datei zeilenweise lesen; wenn _width  gelesen wurde, folgt die */
 /* Ganzzahl unsigned int width, bei _height folgt die Ganzzahl height.   */
 /* = Breite und Hoehe der Bitmap                                         */
 /* nach bits[] folgt der char * bits.                                    */
 /*************************************************************************/
 while( fgets(buf1,999,datei)!=NULL )
      {
	if(strstr(buf1,"_width")!=NULL)
          {
	   if(sscanf(buf1,"%*[^ ]%*1[ ]%*[^ ]%*1[ ]%[^ ]",buf2)!=1)
	     {
               return(0);
             }
           if((width=atoi(buf2))==0)
             {
               return(0);
             }
	  }
	if(strstr(buf1,"_height")!=NULL)
          {
	   if(sscanf(buf1,"%*[^ ]%*1[ ]%*[^ ]%*1[ ]%[^ ]",buf2)!=1)
	     {
               return(0);
             }
           if((height=atoi(buf2))==0)
             {
               return(0);
             }
	  }
	if(strstr(buf1,"_x_hot")!=NULL)
          {
	   if(sscanf(buf1,"%*[^ ]%*1[ ]%*[^ ]%*1[ ]%[^ ]",buf2)==1)
	     {
                 (*hotspot_x)=atoi(buf2);
             }
	  }
	if(strstr(buf1,"_y_hot")!=NULL)
          {
	   if(sscanf(buf1,"%*[^ ]%*1[ ]%*[^ ]%*1[ ]%[^ ]",buf2)==1)
	     {
                 (*hotspot_y)=atoi(buf2);
             }
	  }
 /*************************************************************************/
 /* Es folgt das hexadezimale Array. Jeder hex Hex Wert beginnt mit 0x    */
 /* oder 0X. Diese Werte (4 Zeichen) werden im char Array buf2 jeweils    */
 /* einzeln abgelegt - dann mit sscanf in die int Variable zeichen ueber- */
 /* tragen - und danach im Feld bits abgespeichert. Die Funktion sscanf   */
 /* produziert einen Fehler, wenn man schreibt sscanf(buf2,"%x",bits[n++])*/
 /* , da nur Integer Zahlen mit dem %x Format auslesen duerfen.           */
 /*************************************************************************/
	if(strstr(buf1,"bits[] =")!=NULL)
          {
	   n=0;
           while( fgets(buf1,999,datei)!=NULL )   /* 1 Zeile in buf1 */
		{
                  for(i=0;i<=strlen(buf1);i++)    /* analysieren     */
		     {
                       if(buf1[i]=='x'||buf1[i]=='X') /* x oder X gelesen */
			 {
                           buf2[0]=buf1[i-1];
                           buf2[1]=buf1[i];
                           buf2[2]=buf1[i+1];
                           buf2[3]=buf1[i+2];
                           buf2[4]='\0';
                           sscanf(buf2,"%x",&zeichen);
			   bits[n++]=zeichen;
			 }
		      }
                }
	   bits[n]='\0';
	  }
	}

	fclose(datei);

	/* Einfache Version */
	pix = XCreateBitmapFromData(display, XDefaultRootWindow(display),
                               bits, width, height);
	free((void *)bits);
	return(pix);
}
