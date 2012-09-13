/**************************************************************/
/* Header:    Prototypes for library DBI and GUI              */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
/*
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpprolib.h,v 1.4 2008-11-17 10:42:51 mwn Exp $
*/

/* communication */
unsigned long MPcomm(unsigned short int, long);

/* memory */
void *MPalloc(void *, unsigned long *, long, unsigned long, long);
void *MPallocobj(MEMOBJ *, int);
void MPfree(void *);
void MPfreeobj(MEMOBJ *);
void MPfreearray(char **, int);

/* logging */
void MPlog(int, int, char *, char *);
void MPsyslog(int, int, char *);

/* utilities */
void MPdate_makecurrent(char *, char *);
void MPdate_puttoint(int *, char *);
void MPdate_makefromint(int, char *, int);
int  MPgetSection(char *, int *, char);
int  MPgetTextsegment(char *, MEMOBJ *, char);

/* debugging */
void MPdebug(int, char *, char *);

/* signals */
void MPinstall_signals(int);
