/******************************************************************/
/* Header:    prototypes for MARCO POLO API                       */
/*                                                                */
/* Copyright: yafra.org, Dornacherweg 104 Basel     */
/*            Switzerland                                         */
/* Autor:     Administrator                                  */
/*                                                                */
/******************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpproapi.h,v 1.3 2008-11-23 15:44:38 mwn Exp $
*/


/* SQL - RDBMS low-level API prototyps */
int MPAPIdb_connect(char *, char *, char *);
int MPAPIdb_release(void);

int MPAPIdb_begintrx(int, int);
void MPAPIdb_committrx(void);
void MPAPIdb_rollbacktrx(void);
int MPAPIdb_settrx(int, int);

int MPAPIdb_setsavepoint(int *);
int MPAPIdb_rollbacksavepoint(int *);

int MPAPIdb_sqlquery(int, char **, char *, int *, unsigned long *,
                      unsigned long *);
int MPAPIdb_sqlcommand(char *, int *);


/* High-Level SQL prototyps */
/* INSERT functions */
int MPAPIinsertEntry(int, char *, BEZEICHNUNG *);
int InsertBEZ(BEZEICHNUNG *);

/* UPDATE functions */
int MPAPIupdateEntry(int, char *, BEZEICHNUNG *);
int MPAPIupdate_booksta(int);

/* SELECT functions */
int MPAPIselectEntry(int, char *, char *, int, size_t);
int MPAPIselectOneId(int, int, char *);
int MPAPIselectDLT(int, int, int, DIENST_TRAEGER *);
int MPAPIselectTDL(int, DLG_PART *);
int MPAPIselectTDLbez(int, int, char *, int);
int MPAPIselectDL(int, DIENSTLEISTUNG *);
int MPAPIselectDLbez(int, int, char *, int);
int MPAPIselectRECHST(int, PERSONEN *);
int MPAPIselectARRbez(int, int, char *, int);
int SelFromTxt(int, int, int, char *);
int SelectBez(int, int, int, char *);

// TODO check module setup and namespace
int DLNmkbez(int, char *, int);
int KUNmkbez(int, char *, int);
/*!!! new style
 int MPAPIselectDLNbez(int, int, char *, int);
 int MPAPIselectKUNbez(int, int, char *, int);
*/

/* DELETE functions */
int MPAPIdeleteEntry(int, char *);
int DeleteBEZ(int, char *, int);

/* COUNT / MAX / MIN ... */
int MPAPIid_count(int, int, char *);
int MPAPIid_new(int, int, int);
int MPAPIid_max(int, int, char *);
int MPAPIid_min(int, int);

/* profile handling */
int MPAPIprofile_init(char *, MP_PROFIL *);


/* Utilities */
int UtilExec(char *, int);

int UtilFileCheck(char *);

char *MPAPIbufferSplit(char *, int *, char);

char *copyTextTo(char *, char *, int);
char *ConvertSpecialChar(char *, char);

int ReadDate(struct tm *, time_t *, char *);
int WriteDate(struct tm *, time_t *, char *);
int ReadTime(struct tm *, time_t *, char *);
int WriteTime(struct tm *, time_t *, char *);
time_t put_date_in(char *, char *, char *, char *, char *);

int MPAPIpre_getprice(int, int, PREIS *, PREIS *, char *);
char *cashint(int, char *, char *);
char *cashdouble(double, char *);

/* Mailing commands */
FILE	*MailOpen	(char *, int, int);
int	MailAdd		(FILE *, char *);
int	MailClose	(FILE *, char *);
int	MailSend		(char *, FILE *, char *);

double MPAPIreduktion(STA_VIEW *, double, int, double *, double *);
