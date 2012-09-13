/*HP***************************************************************/
/* Header:    prototypes for DBI                                  */
/*                                                                */
/* Copyright: yafra.org, Dornacherweg 104 Basel     */
/*            Switzerland                                         */
/*                                                                */
/******************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpprodbi.h,v 1.2 2008-11-02 19:55:33 mwn Exp $
*/

#include <mpprolib.h>
#include <mpproapi.h>

/* main Prototyp  */
int main(int, char *argc[]);           /* it's in the function MainServer */
int MainMarco(int, char **, int);
int MPDBImain_exit(int);

/* Interrupt Handling */
void MainLoop(int fd);
int MenuGlobal(GLOBDATA *);
int MenuSelect(int *, char *);
int MenuChoose(int *, char *);
int MenuAktion(int, char *);
int MenuHelp(int *, char *);
int MenuInfo(int *, char *);
int MenuDelete(int);
int MenuOneitem(int *, char *);
int MenuGraphics(int, char *);
int MenuOptiontoggles(int, char *);
int MenuBM(int, char *);
int MenuMatrix(int, char *);
int BuchungsMenu(int, char *);

/* Init functions */
int InitLAB(int);
int InitDLT(void);
void InitMenu(void);
void InitField(void);
void InitGlobal(GLOBDATA *);

/* Utilities functions */
int UtilImmediatCall(char *);
int UtilBackup(int, char *);
int UtilRestore(int, char *);
char *UtilSplitBuffer(char *, int *, char);
int  UtilSplitMenubuffer(char *, char *[], char);
void UtilSplitFreeMenubuffer(char *to_buffer[]);
void UtilDelBlanks(char *);
void UtilMsg(int, int, char *);
void UtilMsgWrite(char *);
void UtilMsgGet(int, int, char *);
int xSqlMessage(char *);
int find_text_nr(int, char *);
int UtilMsgInit(void);
int UtilMsgFree(void);
int CleanPipeString (char *);
int readDouble(double *, char *);
int readInteger(int *, char *);
int readShort(short *, char *);

/* global mask functions */
int GLOBinit(MP_PROFIL *, GLOBDATA *);
int GLOBsave(MP_PROFIL *, GLOBDATA *);

/* graphical booking */
int GRinput(int, char *);
int GRselect(int, char *);
int GRwrite(int, char *);
int GRchoose(int, char *);
int GRrefresh(int, char *);
int GRcolorInit(char **, int *);
int GRgetRegionsFromDB(GRAPHIK *);
int GRnextRegion(char **, char *, REGIONS **);
int GRtestRegion(REGIONS *, int);

/* matrix functions */
int MXshowsend(int, char *);
int MXbinarysend(int, char *);

/* general database function */
int WriteEntry(int table , char *datastring , BEZEICHNUNG *bez );
void WriteInfo(int table , char *datastring , char *buffer );
int createIndex(char *table , char **ptr , int *anzahl );
int dropIndex(char *table , char **ptr , int *anzahl );


/* BUCHUNG */
int BCHdelete(void);
int BCHinput(int, char *);
int BCHselect(long *, char *, int *);

/* BUCHUNGSMASKE */
void BMinit(void);
int BMBCHinput(int, char *);
int BMBCHchoose(int, char *);
int BMDLNsend(int, char *);
int BMDLNinput(int, char *);
int BMDLNchoose(int, char *);
int BMobjChoose(int, char *);
int BMRESsend(int, char *);
int BMRESinput(int, char *);
int BMRESchoose(int, char *);
int BMRESreadprotocol(char *, RESERVATION *, int **, int *);

/* DLN Dienstleistungsnehmer (Reisender) */
int DLNinput(int, char *);
int DLNdefaults(ARRANGEMENT *, REISENDER *);
int DLNdelete(void);
int DLNselect(long *, char *, int *);
int DLNchoose(int, char *);
int DLNinfo(int, char *);

/* Reservation */
int RESdelete(void);
int RESwrite(int, int, int, int, int *, RESERVATION *);

/* Aktionsdetail */
int AKTDwrite(int, int, int, RESERVATION *);
int AKTDwritegroup(AKT_DETAIL *, int);

/* KUNDEN */
int KUNdelete(void);
int KUNinput(int, char *);
int KUNselect(long *, char *, int *);
int KUNchoose(int, char *);

/* PERSADR */
int ADRdelete(void);
int ADRinput(int, char *);
int ADRselect(long *, char *, int *);
int ADRchoose(int, char *);
int ADRinfo(char *);


/* KOLLEKTIV */
int KOLdelete(void);
int KOLinput(int, char *);
int KOLselect(long *, char *, int *);
int KOLchoose(int, char *);
int KOLinfo(char *);

/* OUTPUT Menu */
int OUTchoose(int, char *);
int OUTexec(int, char *);

/* KOMMISSION */
int KOMdelete(void);
int KOMinput(int, char *);
int KOMselect(long *, char *, int *);
int KOMchoose(int, char *);
int KOMinfo(char *);

/* KOMM_DETAIL */
int KOMDdelete(void);
int KOMDinput(int, char *);
int KOMDinput_dln(int, int, int);
int KOMDselect(long *, char *, int *);
int KOMDchoose(int, char *);
int KOMDinfo(char *buffer );



/* SAISON */
int SAIdelete(void);
int SAIinput(int, char *);
int SAIselect(long *, char *, int *);
int SAIchoose(int, char *);

/* Programm */
int PRGdelete(void);
int PRGinput(int, char *);
int PRGselect(long *, char *, int *);
int PRGchoose(int, char *);

/* Arrangement */
int ARRinput(int ,char *);
int ARRdelete(void);
int ARRselect(long *, char *, int *);
int ARRchoose(int, char *);
int ARRinfo(int, char *);
int ARRcopymove(char *, char *);

/* DIENSTLEISTUNG */
int DLdelete(void);
int DLinput(int, char *);
int DLselect(long *, char *, int *);
int DLchoose(int, char *);
int DLinfo(int, char *);
int DLcopymove(DIENSTLEISTUNG *, char *, int );

/* DLG_PARTS */
int DLGdelete(void);
int DLGinput(int, char *);
int DLGselect(long *, char *, int *);
int DLGchoose(int, char *);
int DLGinfo(char *);

/* DIENST_ANGEBOT */
int DLAdelete(void);
int DLAinput(int, char *);
int DLAselect(long *, char *, int *);
int DLAchoose(int, char *);
int DLAinfo(char *buffer );

/* ANGEBOTS_TYP */
int DLATdelete(void);
int DLATinput(int, char *);
int DLATselect(long *, char *, int *);
int DLATchoose(int, char *);
int DLAmatrix(int, char *);

/* HOST_KONT */
int KONHdelete(void);
int KONHinput(int, char *);
int KONHselect(long *, char *, int *);
int KONHchoose(int, char *);

/* KONTINGENT */
int KONdelete(void);
int KONinput(int, char *);
int KONselect(long *, char *, int *);
int KONchoose(int, char *);
int KONinfo(char *buffer );

/* KONT_DETAIL */
int KONDdelete(void);
int KONDinput(int, char *);
int KONDselect(long *, char *, int *);
int KONDchoose(int, char *);
int KONDinfo(char *buffer );

/* PREIS */
int PREdelete(void);
int PREinput(int, char *);
int PREchoose(int, char *);
int PREselect(long *, char *, int *);
int PREinfo(char *buffer );

/* AKTIONEN */
int AKTexec(BUCHUNG *, int);
int AKTdelete(void);
int AKTinput(int, char *);
int AKTselect(long *, char *, int *);
int AKTchoose(int, char *);

/* AKTIONSGRP */
int AKTGinfo(char *);
int AKTGdelete(void);
int AKTGinput(int, char *);
int AKTGselect(long *, char *, int *);
int AKTGchoose(int, char *);

/* AKTIONS_TYP */
int AKTTdelete(void);
int AKTTinput(int, char *);
int AKTTselect(long *, char *, int *);
int AKTTchoose(int, char *);
int AKTTinfo(char *);
int AKTPdelete(void);




/* TRAEGER_TYP */
int DLTTdelete(void);
int DLTTinput(int, char *);
int DLTTselect(long *, char *, int *);
int DLTTchoose(int, char *);

/* KATEGORIE */
int KATdelete(void);
int KATinput(int, char *);
int KATselect(long *, char *, int *);
int KATchoose(int, char *);
int KATinfo(int, char *);
int KATfree(int *, int *, int, int, int, int, int, time_t);

/* DIENSTLEISTUNGSTRAEGER */
int DLTdelete(void);
int DLTinput(int, char *);
int DLTselect(long *, char *, int *);
int DLTchoose(int, char *);
int DLTinfo(int, char *);
int DLTfree(int, int, int, int, time_t, int *, int *, int *);
int DLTnum_of_dln(int, int *);

/* GRAPHIK */
int GRAdelete(void);
int GRAinput(int, char *);
int GRAselect(long *, char *, int *);
int GRAchoose(int, char *);

/* KOSTEN_ART */
int KARdelete(void);
int KARinput(int, char *);
int KARselect(long *, char *, int *);
int KARchoose(int, char *);

/* KOLLEKTIV_TYP */
int KOLTdelete(void);
int KOLTinput(int, char *);
int KOLTselect(long *, char *, int *);
int KOLTchoose(int, char *);

/* KUNDENTYP */
int KUNTdelete(void);
int KUNTinput(int, char *);
int KUNTselect(long *, char *, int *);
int KUNTchoose(int, char *);

/* Pixelbilder PCX */
int PCXdelete(void);
int PCXinput(int, char *);
int PCXselect(long *, char *, int *);
int PCXchoose(int, char *);
int PCXinfo(int, char *);
int PCXsearch(int, int, char *);

/* DLN Typ */
int DLNTinput(int, char *);
int DLNTdelete(void);
int DLNTselect(long *, char *, int *);
int DLNTchoose(int, char *);

/* Statuswerte */
int STAdelete(void);
int STAinput(int, char *);
int STAselect(long *, char *, int *);
int STAchoose(int, char *);
int getAttribut(int attribut , char *name );




/* LAND */
int LANDdelete(void);
int LANDinfo(char *);
int LANDinput(int, char *);
int LANDselect(long *, char *, int *);
int LANDchoose(int, char *);

/* ORT */
int ORTdelete(void);
int ORTinfo(char *);
int ORTinput(int, char *);
int ORTselect(long *, char *, int *);
int ORTchoose(int, char *);

/* WAEHRUNG */
int WHRdelete(void);
int WHRinfo(char *);
int WHRinput(int, char *);
int WHRselect(long *, char *, int *);
int WHRchoose(int, char *);

/* SPRACHE */
int SPRdelete(void);
int SPRinput(int, char *);
int SPRselect(long *, char *, int *);
int SPRchoose(int, char *);

/* LAND_WHR */
int LWdelete(void);
int LWinfo(char *);
int LWinput(int, char *);
int LWselect(long *, char *, int *);
int LWchoose(int, char *);



/* BEZEICHNUNG */
int BEZdelete(void);
int BEZinput(int, char *);
int BEZselect(long *, char *, int *);
int BEZchoose(int, char *);

/* TEXTE */
int TXTinput(int, char *);
int xTxtWrite(char *);

/* MSG */
int MSGdelete(void);
int MSGinput(int, char *);
int MSGselect(long *, char *, int *);
int MSGchoose(int, char *);

/* DATUM */
int DATUMselect(long *, char *, int *);
