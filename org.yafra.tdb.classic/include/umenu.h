/*D***********************************************************
 * Header:    umenu.h                                    
 *            global settings of global MENU struct for GUI
 *                                                            
 * ?inpt:     ob obligatorisch oder nicht                     
 * ?updt:     ob Suchfeld oder nicht                          
 * ?zuob:     externe Reihenfolge der Maskenfelder (what you see on Screen)
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************
 */




/**************************************************************/
/* define the look of the MENU's                              */
/**************************************************************/

/* Globalmenu 15 Felder */
int  GLOBtype[] = { READONLYFIELD, READONLYFIELD, READONLYFIELD, SELNOFIELD, SELNOFIELD, SELNOFIELD, SELNOFIELD, SELNOFIELD, SELNOFIELD, SELNOFIELD, SELNOFIELD, SELNOFIELD, SELNOFIELD, SELNOFIELD, SEDITFIELD }; 
int  GLOBupdt[] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  GLOBinpt[] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE }; 
int  GLOBline[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
int  GLOBcols[] = { 30, 8, 60, 30, 30, 30, 30, 40, 30, 30, 30, 30, 16, 16, 8 };
int  GLOBglob[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
int  GLOBzuob[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
char *GLOBlab[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char GLOBhelp[] = { "GLOBhelp" };
char GLOBmenu[] = { "GLOB" };


/*** BUCHUNGS MENU ***/

/* BUCHUNG 17 Felder */
int  BCHtype[] = { SEDITFIELD, SELNOFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD,
                  SELECTFIELD, SELECTFIELD, SELECTFIELD, SHOWGRAFIELD, MATRIXSELFIELD,
                  SELECTFIELD, SELECTFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD,
                  INPNEWLEVEL, SELECTFIELD, MEDITFIELD };
int  BCHupdt[] = { TRUE, TRUE, FALSE, FALSE,
                  FALSE, FALSE, FALSE, FALSE, FALSE,
                  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
                  FALSE, FALSE, FALSE };
int  BCHinpt[] = { TRUE, TRUE, TRUE, TRUE, TRUE,
                  TRUE, TRUE, TRUE, TRUE, TRUE,
                  TRUE, FALSE, FALSE, FALSE, FALSE,
                  FALSE, TRUE, TRUE };
int  BCHline[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3 };
int  BCHcols[] = { 30, 30, 30, 20, 60, 60, 60, 60, 30, 30, 30, 30, 30, 20, 20, 1, 60, 60 };
int  BCHglob[] = { -1, -1, -1, -1, -1, -1, 2, -1, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
int  BCHzuob[] = { 0, 1, 3, 4, 5, 6, 11, 10, 8, 7, 9, 13, 12, 14, 15, 16, 2, 17 };
char *BCHlab[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char BCHhelp[] = { "BCHhelp" };

/* Kunden  16 Felder */
int  KUNtype[] = { READONLYFIELD, SEDITFIELD, SEDITFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD, MEDITFIELD };
int  KUNupdt[] = { FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  KUNinpt[] = { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  KUNline[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3 };
int  KUNcols[] = { 8, 60, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 40 };
int  KUNglob[] = { -1, -1, -1, -1, -1, -1, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
int  KUNzuob[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
char *KUNlab[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char KUNhelp[] = { "KUNhelp" };


/* Dienstleistungsnehmer DLN Buchungsmaske  6 Felder */

/* Reisender  14 Felder */
int  REItype[] = { READONLYFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD,
                   SELECTFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD,
                   SEDITFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD,
                   MEDITFIELD, MEDITFIELD };
int  REIupdt[] = { FALSE, TRUE, FALSE, FALSE, FALSE,
                   FALSE, FALSE, FALSE, FALSE, FALSE,
                   FALSE, FALSE, FALSE, FALSE };
int  REIinpt[] = { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,
                   FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  REIline[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3 };
int  REIcols[] = { 30, 60, 30, 30, 30, 30, 30, 30, 10, 30, 30, 30, 60, 60 };
int  REIglob[] = { -1, -1, -1, -1, 9, -1, 3, -1, -1, -1, -1, -1, -1, -1 };
int  REIzuob[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
char *REIlab[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char REIhelp[] = { "REIhelp" };

/* Gruppe  7 Felder */
int  KOLtype[] = { SEDITFIELD, SELECTFIELD, SELECTFIELD, MEDITFIELD, SELECTFIELD, SELECTFIELD, SEDITFIELD };
int  KOLupdt[] = { TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  KOLinpt[] = { TRUE, FALSE, TRUE, FALSE, TRUE, TRUE, FALSE };
int  KOLline[] = { 1, 1, 1, 5, 1, 1, 1 };
int  KOLcols[] = { 30, 30, 30, 40, 50, 50, 30 };
int  KOLglob[] = { -1, -1, -1, -1, -1, 2, -1 };
int  KOLzuob[] = { 0, 5, 1, 6, 2, 3, 4 };
char *KOLlab[] = { 0, 0, 0, 0, 0, 0, 0 };
char KOLhelp[] = { "KOLhelp" };

/* Output  4 Felder */
int  OUTtype[] = { SELECTFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD };
int  OUTupdt[] = { TRUE, FALSE, FALSE, FALSE };
int  OUTinpt[] = { TRUE, TRUE, TRUE, TRUE };
int  OUTline[] = { 1, 1, 1, 1 };
int  OUTcols[] = { 50, 30, 30, 30 };
int  OUTglob[] = { -1, -1, -1, -1 };
int  OUTzuob[] = { 0, 1, 2, 3 };
char *OUTlab[] = { 0, 0, 0, 0 };
char OUThelp[] = { "OUThelp" };

/* Kommission/Reduktion  16 Felder */
int  KOMtype[] = { SEDITFIELD, SELECTFIELD, SELECTFIELD, SEDITFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD, TWINSELFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD, MEDITFIELD, SELECTFIELD };
int  KOMupdt[] = { TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  KOMinpt[] = { TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  KOMline[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
int  KOMcols[] = { 30, 30, 30, 30, 60, 30, 30, 30, 30, 50, 30, 30, 30, 30, 60, 30 };
int  KOMglob[] = { -1, -1, -1, -1, 2, -1, 6, 9, -1, -1, -1, -1, -1, -1, -1, -1 };
int  KOMzuob[] = { 0, 1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 13, 14, 15, 6 };
char *KOMlab[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char KOMhelp[] = { "KOMhelp" };

/* Kommissionsdetail  6 Felder */
int  KOMDtype[] = { SELECTFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD, ONEITEMFIELD };
int  KOMDupdt[] = { TRUE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  KOMDinpt[] = { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE };
int  KOMDline[] = { 1, 1, 1, 1, 1, 1 };
int  KOMDcols[] = { 30, 30, 60, 60, 30, 10 };
int  KOMDglob[] = { -1, -1, -1, -1, -1, -1 };
int  KOMDzuob[] = { 0, 1, 2, 3, 4, 5 };
char *KOMDlab[] = { 0, 0, 0, 0, 0, 0 };
char KOMDhelp[] = { "KOMDhelp" };

/* Versand  9 Felder */
int  ADRtype[] = { SELECTFIELD, SELECTFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD, SELECTFIELD };
int  ADRupdt[] = { TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  ADRinpt[] = { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE };
int  ADRline[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
int  ADRcols[] = { 60, 60, 30, 30, 30, 30, 30, 10, 30 };
int  ADRglob[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1 };
int  ADRzuob[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
char *ADRlab[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char ADRhelp[] = { "ADRhelp" };



/*** ANGEBOT MENU ***/

/* Saison  5 Felder */
int  SAItype[] = { SEDITFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD, MEDITFIELD };
int  SAIupdt[] = { TRUE, FALSE, FALSE, FALSE, FALSE };
int  SAIinpt[] = { TRUE, TRUE, TRUE, TRUE, FALSE };
int  SAIline[] = { 1, 1, 1, 1, 5 };
int  SAIcols[] = { 30, 10, 30, 30, 40 };
int  SAIglob[] = { -1, -1, -1, -1, -1 };
int  SAIzuob[] = { 0, 1, 2, 3, 4 };
char *SAIlab[] = { 0, 0, 0, 0, 0 };
char SAIhelp[] = { "SAIhelp" };

/* Programm  4 Felder */
int  PRGtype[] = { SEDITFIELD, SEDITFIELD, MEDITFIELD, SELECTFIELD };
int  PRGupdt[] = { TRUE, FALSE, FALSE, FALSE };
int  PRGinpt[] = { TRUE, TRUE, FALSE, FALSE };
int  PRGline[] = { 1, 1, 5, 1 };
int  PRGcols[] = { 30, 10, 40, 30 };
int  PRGglob[] = { -1, -1, -1, 10 };
int  PRGzuob[] = { 0, 1, 3, 2 };
char *PRGlab[] = { 0, 0, 0, 0 };
char PRGhelp[] = { "PRGhelp" };

/* Arrangement  8 Felder */
int  ARRtype[] = { SEDITFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD, MEDITFIELD, SELECTFIELD, ONEITEMFIELD, SEDITFIELD };
int  ARRupdt[] = { TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  ARRinpt[] = { TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, TRUE };
int  ARRline[] = { 1, 1, 1, 1, 5, 1, 1, 1 };
int  ARRcols[] = { 30, 30, 30, 30, 40, 50, 30, 10 };
int  ARRglob[] = { -1, -1, 11, -1, -1, -1, -1, -1 };
int  ARRzuob[] = { 0, 2, 3, 6, 4, 7, 5, 1 };
char *ARRlab[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
char ARRhelp[] = { "ARRhelp" };

/* Dienstleistung  7 Felder */
int  DTGtype[] = { SEDITFIELD, TWINSELFIELD, MEDITFIELD, SELECTFIELD, SELECTFIELD, ONEITEMFIELD, SEDITFIELD };
int  DTGupdt[] = { TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  DTGinpt[] = { TRUE, FALSE, FALSE, TRUE, TRUE, FALSE, TRUE };
int  DTGline[] = { 1, 1, 10, 1, 1, 1, 1 };
int  DTGcols[] = { 30, 50, 80, 30, 30, 30, 10 };
int  DTGglob[] = { -1, -1, -1, 12, -1, -1, -1 };
int  DTGzuob[] = { 0, 5, 4, 2, 3, 6, 1 };
char *DTGlab[] = { 0, 0, 0, 0, 0, 0, 0 };
char DTGhelp[] = { "DTGhelp" };

/* Dienstleistungsteile  12 Felder */
int  DLGtype[] = { SEDITFIELD, SELECTFIELD, SELECTFIELD, SEDITFIELD, SEDITFIELD, SELECTFIELD, SELECTFIELD, SEDITFIELD, MEDITFIELD, SELECTFIELD, SELECTFIELD, SEDITFIELD };
int  DLGupdt[] = { TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  DLGinpt[] = { TRUE, FALSE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, TRUE };
int  DLGline[] = { 1, 1, 1, 1, 1, 1, 1, 1, 10, 1, 1, 1 };
int  DLGcols[] = { 30, 50, 30, 30, 30, 30, 50, 30, 80, 30, 50, 10 };
int  DLGglob[] = { -1, -1, -1, 12, 13, -1, -1, -1, -1, 10, -1, -1 };
int  DLGzuob[] = { 0, 7, 2, 3, 4, 5, 8, 10, 11, 6, 9, 1 };
char *DLGlab[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char DLGhelp[] = { "DLGhelp" };

/* Dienstleistungsangebot  12 Felder */
int  DLAtype[] = { SEDITFIELD, SELECTFIELD, ONEITEMFIELD, SELECTFIELD, SELECTFIELD, SEDITFIELD, SELECTFIELD, SEDITFIELD, MEDITFIELD, SELECTFIELD, SELECTFIELD, SEDITFIELD };
int  DLAupdt[] = { TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  DLAinpt[] = { TRUE, FALSE, FALSE, TRUE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, TRUE };
int  DLAline[] = { 1, 1, 1, 1, 1, 1, 1, 1, 10, 1, 1, 1 };
int  DLAcols[] = { 30, 30, 30, 30, 30, 30, 30, 30, 80, 30, 30, 10 };
int  DLAglob[] = { -1, -1, -1, 7, -1, -1, 8, -1, -1, -1, -1, -1 };
int  DLAzuob[] = { 0, 5, 6, 2, 3, 7, 4, 10, 11, 8, 9, 1 };
char *DLAlab[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char DLAhelp[] = { "DLAhelp" };

/* Aktionen  7 Felder */
int  AKTtype[] = { SEDITFIELD, SELNOFIELD, MEDITFIELD, SELNOFIELD, SELNOFIELD, SELECTFIELD, SELECTFIELD };
int  AKTupdt[] = { TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  AKTinpt[] = { TRUE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE };
int  AKTline[] = { 1, 1, 5, 1, 1, 1, 1 };
int  AKTcols[] = { 30, 30, 40, 30, 30, 30, 30 };
int  AKTglob[] = { -1, -1, -1, -1, -1, -1, -1 };
int  AKTzuob[] = { 0, 5, 6, 4, 2, 1, 3 };
char *AKTlab[] = { 0, 0, 0, 0, 0, 0, 0 };
char AKThelp[] = { "AKThelp" };

/* Aktionsgruppe  3 Felder */
int  AKTGtype[] = { SELECTFIELD, SELECTFIELD, ONEITEMFIELD };
int  AKTGupdt[] = { TRUE, TRUE, FALSE };
int  AKTGinpt[] = { TRUE, TRUE, TRUE };
int  AKTGline[] = { 1, 1, 1 };
int  AKTGcols[] = { 30, 30, 10 };
int  AKTGglob[] = { -1, -1, -1 };
int  AKTGzuob[] = { 0, 1, 2 };
char *AKTGlab[] = { 0, 0, 0 };
char AKTGhelp[] = { "AKTGhelp" };

/* Haupt-Kontingent  10 Felder */
int  HKONtype[] = { SEDITFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD, MEDITFIELD };
int  HKONupdt[] = { TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  HKONinpt[] = { TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  HKONline[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
int  HKONcols[] = { 30, 50, 50, 30, 50, 30, 30, 30, 30, 50 };
int  HKONglob[] = { -1, -1, 2, -1, -1, -1, -1, -1, -1, -1 };
int  HKONzuob[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
char *HKONlab[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char HKONhelp[] = { "HKONhelp" };

/* Kontingent  6 Felder */
int  KONtype[] = { SEDITFIELD, SELECTFIELD, SELECTFIELD, SEDITFIELD, SEDITFIELD, MEDITFIELD };
int  KONupdt[] = { TRUE, TRUE, FALSE, FALSE, FALSE, FALSE };
int  KONinpt[] = { TRUE, TRUE, TRUE, FALSE, FALSE, FALSE };
int  KONline[] = { 1, 1, 1, 1, 1, 5 };
int  KONcols[] = { 30, 30, 50, 30, 30, 50 };
int  KONglob[] = { -1, -1, -1, -1, -1, -1 };
int  KONzuob[] = { 0, 1, 2, 3, 4, 5 };
char *KONlab[] = { 0, 0, 0, 0, 0, 0 };
char KONhelp[] = { "KONhelp" };

/* Kontingent-Detail  7 Felder */
int  KONDtype[] = { SELECTFIELD, SELECTFIELD, SELECTFIELD, ONEITEMFIELD, ONEITEMFIELD, TWINSELFIELD, SELECTFIELD };
int  KONDupdt[] = { TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  KONDinpt[] = { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE };
int  KONDline[] = { 1, 1, 1, 1, 1, 1, 1 };
int  KONDcols[] = { 30, 30, 30, 30, 30, 30, 30 };
int  KONDglob[] = { -1, -1, -1, -1, -1, -1, -1 };
int  KONDzuob[] = { 0, 1, 2, 3, 4, 5, 6 };
char *KONDlab[] = { 0, 0, 0, 0, 0, 0, 0 };
char KONDhelp[] = { "KONDhelp" };

/* Preis  22 Felder */
int  PREtype[] = { READONLYFIELD, SELECTFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD, TWINSELFIELD, SEDITFIELD, SEDITFIELD, SELECTFIELD, SELECTFIELD, MEDITFIELD, SELECTFIELD, SELECTFIELD, ONEITEMFIELD, ONEITEMFIELD };
int  PREupdt[] = { TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  PREinpt[] = { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  PREline[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1 };
int  PREcols[] = { 10, 30, 30, 30, 30, 30, 50, 30, 30, 30, 30, 30, 50, 15, 15, 30, 30, 50, 50, 30, 5, 5 };
int  PREglob[] = { -1, -1, -1, -1, -1, -1, 2, -1, -1, 6, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
int  PREzuob[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21 };
char *PRElab[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char PREhelp[] = { "PREhelp" };


/*** STAMM MENU ***/

/* Tr�gertyp  3 Felder */
int  DLTTtype[] = { SEDITFIELD, SELECTFIELD, MEDITFIELD };
int  DLTTupdt[] = { TRUE, FALSE, FALSE };
int  DLTTinpt[] = { TRUE, FALSE, FALSE };
int  DLTTline[] = { 1, 1, 5 };
int  DLTTcols[] = { 30, 30, 40 };
int  DLTTglob[] = { -1, -1, -1 };
int  DLTTzuob[] = { 0, 1, 2 };
char *DLTTlab[] = { 0, 0, 0 };
char DLTThelp[] = { "DLTThelp" };

/* Dienstleistungstr�ger  9 Felder */
int  DLTtype[] = { SEDITFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD, MEDITFIELD, SELECTFIELD, SELECTFIELD, SEDITFIELD, ONEITEMFIELD };
int  DLTupdt[] = { TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  DLTinpt[] = { TRUE, FALSE, TRUE, TRUE, FALSE, TRUE, FALSE, TRUE, FALSE };
int  DLTline[] = { 1, 1, 1, 1, 5, 1, 1, 1, 1 };
int  DLTcols[] = { 30, 30, 50, 50, 40, 30, 30, 10, 10 };
int  DLTglob[] = { -1, 6, -1, 5, -1, 7, -1, -1, -1 };
int  DLTzuob[] = { 2, 5, 1, 4, 8, 0, 6, 3, 7 };
char *DLTlab[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char DLThelp[] = { "DLThelp" };

/* Kategorie 5 Felder */
int  KATtype[] = { SEDITFIELD, SELECTFIELD, SELECTFIELD, SELNOFIELD, MEDITFIELD };
int  KATupdt[] = { TRUE, FALSE, FALSE, FALSE, FALSE };
int  KATinpt[] = { TRUE, TRUE, FALSE, FALSE, FALSE };
int  KATline[] = { 1, 1, 1, 1, 5 };
int  KATcols[] = { 30, 30, 30, 30, 40 };
int  KATglob[] = { -1, 5, -1, -1, -1 };
int  KATzuob[] = { 0, 1, 2, 3, 4 };
char *KATlab[] = { 0, 0, 0, 0, 0 };
char KAThelp[] = { "KAThelp" };

/* Pixelbilder  7 Felder */
int  PCXtype[] = { SEDITFIELD, SEDITFIELD, SELECTFIELD, SELECTFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD };
int  PCXupdt[] = { TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  PCXinpt[] = { TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE };
int  PCXline[] = { 1, 1, 1, 1, 1, 1, 1 };
int  PCXcols[] = { 30, 60, 30, 30, 10, 10, 10 };
int  PCXglob[] = { -1, -1, -1, -1, -1, -1, -1 };
int  PCXzuob[] = { 0, 1, 2, 3, 4, 5, 6 };
char *PCXlab[] = { 0, 0, 0, 0, 0, 0, 0 };
char PCXhelp[] = { "PCXhelp" };

/* Grafik  3 Felder */
int  GRAtype[] = { SEDITFIELD, INPUTGRAFIELD, MEDITFIELD };
int  GRAupdt[] = { TRUE, FALSE, FALSE };
int  GRAinpt[] = { TRUE, TRUE, FALSE };
int  GRAline[] = { 1, 1, 5 };
int  GRAcols[] = { 30, 30, 80 };
int  GRAglob[] = { -1, 7, -1 };
int  GRAzuob[] = { 0, 1, 2 };
char *GRAlab[] = { 0, 0, 0 };
char GRAhelp[] = { "GRAhelp" };

/* Kostenart  2 Felder */
int  KARtype[] = { SEDITFIELD, MEDITFIELD };
int  KARupdt[] = { TRUE, FALSE };
int  KARinpt[] = { TRUE, FALSE };
int  KARline[] = { 1, 5 };
int  KARcols[] = { 30, 40 };
int  KARglob[] = { -1, -1 };
int  KARzuob[] = { 0, 1 };
char *KARlab[] = { 0, 0 };
char KARhelp[] = { "KARhelp" };

/* Dienstleistungsangebots-Typ  2 Felder */
int  DLATtype[] = { SEDITFIELD, MEDITFIELD };
int  DLATupdt[] = { TRUE, FALSE };
int  DLATinpt[] = { TRUE, FALSE };
int  DLATline[] = { 1, 5 };
int  DLATcols[] = { 30, 40 };
int  DLATglob[] = { -1, -1 };
int  DLATzuob[] = { 0, 1 };
char *DLATlab[] = { 0, 0 };
char DLAThelp[] = { "DLAThelp" };

/* Kundentyp  3 Felder */
int  KUNTtype[] = { SEDITFIELD, MEDITFIELD, SEDITFIELD };
int  KUNTupdt[] = { TRUE, FALSE, FALSE };
int  KUNTinpt[] = { TRUE, FALSE, FALSE };
int  KUNTline[] = { 1, 5, 1 };
int  KUNTcols[] = { 30, 40, 10 };
int  KUNTglob[] = { -1, -1, -1 };
int  KUNTzuob[] = { 0, 2, 1 };
char *KUNTlab[] = { 0, 0, 0 };
char KUNThelp[] = { "KUNThelp" };

/* Reisendertyp  5 Felder */
int  REITtype[] = { SEDITFIELD, MEDITFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD };
int  REITupdt[] = { TRUE, FALSE, FALSE, FALSE, FALSE };
int  REITinpt[] = { TRUE, FALSE, FALSE, FALSE, FALSE };
int  REITline[] = { 1, 5, 1, 1, 1 };
int  REITcols[] = { 30, 40, 10, 8, 8 };
int  REITglob[] = { -1, -1, -1, -1, -1 };
int  REITzuob[] = { 0, 2, 1, 3, 4 };
char *REITlab[] = { 0, 0, 0, 0, 0 };
char REIThelp[] = { "REIThelp" };

/* Kollektivtyp  3 Felder */
int  KOLTtype[] = { SEDITFIELD, MEDITFIELD, SEDITFIELD };
int  KOLTupdt[] = { TRUE, FALSE, FALSE };
int  KOLTinpt[] = { TRUE, FALSE, FALSE };
int  KOLTline[] = { 1, 5, 1 };
int  KOLTcols[] = { 30, 40, 10 };
int  KOLTglob[] = { -1, -1, -1 };
int  KOLTzuob[] = { 0, 2, 1 };
char *KOLTlab[] = { 0, 0, 0 };
char KOLThelp[] = { "KOLThelp" };

/* Aktionstyp  9 Felder */
int  AKTTtype[] = { SEDITFIELD, SEDITFIELD, MEDITFIELD, ONEITEMFIELD, SELECTFIELD, SEDITFIELD, ONEITEMFIELD, ONEITEMFIELD, MEDITFIELD };
int  AKTTupdt[] = { TRUE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  AKTTinpt[] = { TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  AKTTline[] = { 1, 1, 5, 1, 1, 1, 1, 1, 2};
int  AKTTcols[] = { 30, 60, 60, 8, 30, 30, 30, 30, 60 };
int  AKTTglob[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1 };
int  AKTTzuob[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
char *AKTTlab[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char AKTThelp[] = { "AKTThelp" };

/* Statuswerte  5 Felder */
int  STAtype[] = { SEDITFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD, SELNOFIELD };
int  STAupdt[] = { TRUE, FALSE, FALSE, FALSE, TRUE };
int  STAinpt[] = { TRUE, FALSE, FALSE, FALSE, TRUE };
int  STAline[] = { 1, 1, 1, 1, 1 };
int  STAcols[] = { 30, 39, 39, 30, 30 };
int  STAglob[] = { -1, -1, -1, -1, -1 };
int  STAzuob[] = { 1, 2, 3, 4, 0 };
char *STAlab[] = { 0, 0, 0, 0, 0 };
char STAhelp[] = { "STAhelp" };


/*** GEO MENU ***/

/* Land   8 Felder */
int  LANDtype[] = { SEDITFIELD, SELECTFIELD, SELECTFIELD, SELECTFIELD, SEDITFIELD, SEDITFIELD, MEDITFIELD, SEDITFIELD };
int  LANDupdt[] = { TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  LANDinpt[] = { TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  LANDline[] = { 1, 1, 1, 1, 1, 1, 3, 1 };
int  LANDcols[] = { 30, 30, 30, 30, 10, 10, 40, 20 };
int  LANDglob[] = { -1, -1, -1, 3, -1, -1, -1, -1 };
int  LANDzuob[] = { 0, 1, 2, 3, 4, 5, 7, 6 };
char *LANDlab[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
char LANDhelp[] = { "LANDhelp" };

/* Ort   8 Felder */
int  ORTtype[] = { SEDITFIELD, SELECTFIELD, SELECTFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD, MEDITFIELD };
int  ORTupdt[] = { TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  ORTinpt[] = { TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE };
int  ORTline[] = { 1, 1, 1, 1, 1, 1, 1, 3 };
int  ORTcols[] = { 30, 30, 30, 10, 20, 20, 20, 40 };
int  ORTglob[] = { -1, -1, -1, -1, -1, -1, -1, -1 };
int  ORTzuob[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
char *ORTlab[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
char ORThelp[] = { "ORThelp" };

/* Waehrung  4 Felder */
int  WHRtype[] = { SEDITFIELD, SEDITFIELD, SEDITFIELD, MEDITFIELD };
int  WHRupdt[] = { TRUE, FALSE, FALSE, FALSE };
int  WHRinpt[] = { TRUE, FALSE, FALSE, FALSE };
int  WHRline[] = { 1, 1, 1, 3 };
int  WHRcols[] = { 30, 20, 10, 40 };
int  WHRglob[] = { -1, -1, -1, -1 };
int  WHRzuob[] = { 0, 1, 2, 3 };
char *WHRlab[] = { 0, 0, 0, 0 };
char WHRhelp[] = { "WHRhelp" };

/* Kurs Menu 6 Felder */
int	LWtype[] = { SELECTFIELD, SELECTFIELD, SELECTFIELD, SEDITFIELD, SEDITFIELD, SEDITFIELD };
int	LWupdt[] = { TRUE, TRUE, TRUE, FALSE, FALSE, FALSE };
int	LWinpt[] = { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE };
int	LWline[] = { 1, 1, 1, 1, 1, 1 };
int	LWcols[] = { 30, 30, 30, 20, 20, 20 };
int	LWglob[] = { -1, -1, -1, -1, -1, -1 };
int	LWzuob[] = { 0, 1, 2, 3, 4, 5 };
char	*LWlab[] = { 0, 0, 0, 0, 0, 0 };
char	LWhelp[] = { "LWhelp" };

/* Sprachen  5 Felder */
int  SPRtype[] = { SEDITFIELD, ONEITEMFIELD, SEDITFIELD, ONEITEMFIELD, ONEITEMFIELD };
int  SPRupdt[] = { TRUE, FALSE, FALSE, FALSE, FALSE };
int  SPRinpt[] = { TRUE, TRUE, TRUE, TRUE, TRUE };
int  SPRline[] = { 1, 1, 1, 1, 1 };
int  SPRcols[] = { 30, 8, 20, 5, 5 };
int  SPRglob[] = { -1, -1, -1, -1, -1 };
int  SPRzuob[] = { 0, 1, 2, 3, 4 };
char *SPRlab[] = { 0, 0, 0, 0 ,0 };
char SPRhelp[] = { "SPRhelp" };


/*** OPTIONS MENU ***/

/* Bezeichnung  4 Felder */
int  BEZtype[] = { SELNOFIELD, SELNOFIELD, SELNOFIELD, SEDITFIELD };
int  BEZupdt[] = { TRUE, TRUE, TRUE, FALSE };
int  BEZinpt[] = { TRUE, TRUE, TRUE, TRUE };
int  BEZline[] = { 1, 1, 1, 1 };
int  BEZcols[] = { 30, 30, 30, 30 };
int  BEZglob[] = { 3, -1, -1, -1 };
int  BEZzuob[] = { 0, 1, 2, 3 };
char *BEZlab[] = { 0, 0, 0, 0 };
char BEZhelp[] = { "BEZhelp" };

/* Texte 4 Felder */
int  TXTtype[] = { SELECTFIELD, MEDITFIELD, SELECTFIELD, MEDITFIELD };
int  TXTupdt[] = { TRUE, FALSE, FALSE, FALSE };
int  TXTinpt[] = { TRUE, TRUE, FALSE, FALSE };
int  TXTline[] = { 1, 5, 1, 5 };
int  TXTcols[] = { 30, 80, 30, 80 };
int  TXTglob[] = { 3, -1, -1, -1 };
int  TXTzuob[] = { 0, 1, 2, 3 };
char *TXTlab[] = { 0, 0, 0, 0 };
char TXThelp[] = { "TXThelp" };

/* Label  6 Felder */
int  LABtype[] = { SEDITFIELD, SELECTFIELD, ONEITEMFIELD, ONEITEMFIELD, ONEITEMFIELD, ONEITEMFIELD };
int  LABupdt[] = { TRUE, TRUE, FALSE, FALSE, FALSE, FALSE };
int  LABinpt[] = { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE };
int  LABline[] = { 1, 1, 1, 1, 1, 1 };
int  LABcols[] = { 30, 30, 5, 5, 5, 5 };
int  LABglob[] = { -1, -1, -1, -1, -1, -1 };
int  LABzuob[] = { 0, 1, 2, 3, 4, 5 };
char *LABlab[] = { 0, 0, 0, 0, 0, 0 };
char LABhelp[] = { "LABhelp" };

/* Message  4 Felder */
int  MSGtype[] = { SELECTFIELD, SEDITFIELD, SELECTFIELD, MEDITFIELD };
int  MSGupdt[] = { FALSE, TRUE, FALSE, FALSE };
int  MSGinpt[] = { TRUE, TRUE, TRUE, TRUE };
int  MSGline[] = { 1, 1, 1, 10 };
int  MSGcols[] = { 30, 30, 30, 80 };
int  MSGglob[] = { -1, -1, 3, -1 };
int  MSGzuob[] = { 0, 1, 2, 3 };
char *MSGlab[] = { 0, 0, 0, 0 };
char MSGhelp[] = { "MSGhelp" };

/* Help  4 Feld */
int  HELPtype[] = { SELECTFIELD, SEDITFIELD, SELECTFIELD, MEDITFIELD };
int  HELPupdt[] = { FALSE, TRUE, FALSE, FALSE };
int  HELPinpt[] = { TRUE, TRUE, TRUE, TRUE };
int  HELPline[] = { 1, 1, 1, 20 };
int  HELPcols[] = { 30, 30, 30, 80 };
int  HELPglob[] = { -1, -1, 3, -1 };
int  HELPzuob[] = { 0, 1, 2, 3 };
char *HELPlab[] = { 0, 0, 0, 0 };
char HELPhelp[] = { "HELPhelp" };

/* Backup  1 Feld */
int  BKPtype[] = { READONLYFIELD };
int  BKPupdt[] = { TRUE };
int  BKPinpt[] = { TRUE };
int  BKPline[] = { 1 };
int  BKPcols[] = { 30 };
int  BKPglob[] = { -1 };
int  BKPzuob[] = { 0 };
char *BKPlab[] = { 0 };
char BKPhelp[] = { "BKPhelp" };

/* Restore  1 Feld */
int  RESTtype[] = { READONLYFIELD };
int  RESTupdt[] = { TRUE };
int  RESTinpt[] = { TRUE };
int  RESTline[] = { 1 };
int  RESTcols[] = { 30 };
int  RESTglob[] = { -1 };
int  RESTzuob[] = { 0 };
char *RESTlab[] = { 0 };
char RESThelp[] = { "RESThelp" };

/* Setup global values 1 dummy Feld */
int  SETUtype[] = { READONLYFIELD };
int  SETUupdt[] = { TRUE };
int  SETUinpt[] = { TRUE };
int  SETUline[] = { 1 };
int  SETUcols[] = { 10 };
int  SETUglob[] = { -1 };
int  SETUzuob[] = { 0 };
char *SETUlab[] = { 0 };
char SETUhelp[] = { "SETUhelp" };

/* Option Einstellungen  1 dummy Feld */
int  OPTtype[] = { READONLYFIELD };
int  OPTupdt[] = { TRUE };
int  OPTinpt[] = { TRUE };
int  OPTline[] = { 1 };
int  OPTcols[] = { 10 };
int  OPTglob[] = { -1 };
int  OPTzuob[] = { 0 };
char *OPTlab[] = { 0 };
char OPThelp[] = { "OPThelp" };

/* Quit 1 dummy Feld */
int  QUITtype[] = { READONLYFIELD };
int  QUITupdt[] = { TRUE };
int  QUITinpt[] = { TRUE };
int  QUITline[] = { 1 };
int  QUITcols[] = { 10 };
int  QUITglob[] = { -1 };
int  QUITzuob[] = { 0 };
char *QUITlab[] = { 0 };
char QUIThelp[] = { "QUIThelp" };

/* About help  1 dummy Feld */
int  ABOUTtype[] = { READONLYFIELD };
int  ABOUTupdt[] = { TRUE };
int  ABOUTinpt[] = { TRUE };
int  ABOUTline[] = { 1 };
int  ABOUTcols[] = { 10 };
int  ABOUTglob[] = { -1 };
int  ABOUTzuob[] = { 0 };
char *ABOUTlab[] = { 0 };
char ABOUThelp[] = { "ABOUThelp" };

/* Application help 1 dummy Feld */
int  APPLItype[] = { READONLYFIELD };
int  APPLIupdt[] = { TRUE };
int  APPLIinpt[] = { TRUE };
int  APPLIline[] = { 1 };
int  APPLIcols[] = { 10 };
int  APPLIglob[] = { -1 };
int  APPLIzuob[] = { 0 };
char *APPLIlab[] = { 0 };
char APPLIhelp[] = { "APPLIhelp" };

char ALLmenu[] = { "pulldown" };


/**************************************************************/
/* create the diff. MENU structures                            */
/**************************************************************/
MENU glob = {
	_GLOBALMENU, 0, 0, 15, GLOBtype, GLOBupdt, GLOBinpt, GLOBline, GLOBcols,
	GLOBglob, GLOBzuob, 0, 0, GLOBhelp, 
	GLOBmenu, 0, GLOBlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True
	};

MENU menu[ANZ_MENU+2] = {
	{ _DIENST_TRAEGER, xUIcomm, xUIhelp, 9, DLTtype, DLTupdt, DLTinpt, DLTline,
	DLTcols,	DLTglob, DLTzuob, 3, 2, DLThelp,
	ALLmenu, 0, DLTlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _TRAEGER_TYP, xUIcomm, xUIhelp, 3, DLTTtype, DLTTupdt, DLTTinpt, DLTTline,
	DLTTcols, DLTTglob, DLTTzuob, 3, 0, DLTThelp,
	ALLmenu, 0, DLTTlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _DIENST_ANGEBOT, xUIcomm, xUIhelp, 12, DLAtype, DLAupdt, DLAinpt, DLAline,
	DLAcols,	DLAglob, DLAzuob, 2, 5, DLAhelp,
	ALLmenu, 0, DLAlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _ANGEBOTS_TYP, xUIcomm, xUIhelp, 2, DLATtype, DLATupdt, DLATinpt, DLATline,
	DLATcols, DLATglob, DLATzuob, 3, 10, DLAThelp,
	ALLmenu, 0, DLATlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _STATUS_WERTE, xUIcomm, xUIhelp, 5, STAtype, STAupdt, STAinpt, STAline,
	STAcols,	STAglob, STAzuob, 3, 11, STAhelp,
	ALLmenu, 0, STAlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _AKTIONEN, xUIcomm, xUIhelp, 7, AKTtype, AKTupdt, AKTinpt, AKTline, AKTcols,
	AKTglob, AKTzuob, 2, 6, AKThelp,
	ALLmenu, 0, AKTlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _AKTIONSGRP, xUIcomm, xUIhelp, 3, AKTGtype, AKTGupdt, AKTGinpt, AKTGline, AKTGcols,
	AKTGglob, AKTGzuob, 2, 7, AKTGhelp,
	ALLmenu, 0, AKTGlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _AKTIONS_TYP, xUIcomm, xUIhelp, 9, AKTTtype, AKTTupdt, AKTTinpt, AKTTline,		/**/
	AKTTcols, AKTTglob, AKTTzuob, 3, 9, AKTThelp,
	ALLmenu, 0, AKTTlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _KATEGORIE, xUIcomm, xUIhelp, 5, KATtype, KATupdt, KATinpt, KATline, KATcols,
	KATglob, KATzuob, 3, 1, KAThelp,
	ALLmenu, 0, KATlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _KUNDEN, xUIcomm, xUIhelp, 16, KUNtype, KUNupdt, KUNinpt, KUNline, KUNcols,
	KUNglob, KUNzuob, 1, 2, KUNhelp,
	ALLmenu, 0, KUNlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _KUNDEN_TYP, xUIcomm, xUIhelp, 3, KUNTtype, KUNTupdt, KUNTinpt, KUNTline,
	KUNTcols, KUNTglob, KUNTzuob, 3, 8, KUNThelp,
	ALLmenu, 0, KUNTlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _REISENDER_TYP, xUIcomm, xUIhelp, 5, REITtype, REITupdt, REITinpt, REITline,
	REITcols, REITglob, REITzuob, 3, 6, REIThelp,
	ALLmenu, 0, REITlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _KOSTEN_ART, xUIcomm, xUIhelp, 2, KARtype, KARupdt, KARinpt, KARline, KARcols,
	KARglob, KARzuob, 3, 5, KARhelp,
	ALLmenu, 0, KARlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _KOLLEKTIV_TYP, xUIcomm, xUIhelp, 3, KOLTtype, KOLTupdt, KOLTinpt, KOLTline,
	KOLTcols, KOLTglob, KOLTzuob, 3, 7, KOLThelp,
	ALLmenu, 0, KOLTlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _PROGRAMM, xUIcomm, xUIhelp, 4, PRGtype, PRGupdt, PRGinpt, PRGline, PRGcols,
	PRGglob, PRGzuob, 2, 1, PRGhelp,
	ALLmenu, 0, PRGlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _PREIS, xUIcomm, xUIhelp, 22, PREtype, PREupdt, PREinpt, PREline, PREcols,
	PREglob, PREzuob, 2, 11, PREhelp,
	ALLmenu, 0, PRElab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _REISENDER, xUIcomm, xUIhelp, 14, REItype, REIupdt, REIinpt, REIline,
	REIcols, REIglob, REIzuob, 1, 1, REIhelp,
	ALLmenu, 0, REIlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _KOLLEKTIV, xUIcomm, xUIhelp, 7, KOLtype, KOLupdt, KOLinpt, KOLline, KOLcols,
	KOLglob, KOLzuob, 1, 3, KOLhelp,
	ALLmenu, 0, KOLlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _SAISON, xUIcomm, xUIhelp, 5, SAItype, SAIupdt, SAIinpt, SAIline, SAIcols,
	SAIglob, SAIzuob, 2, 0, SAIhelp,
	ALLmenu, 0, SAIlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _ARRANGEMENT, xUIcomm, xUIhelp, 8, ARRtype, ARRupdt, ARRinpt, ARRline,
	ARRcols, ARRglob, ARRzuob, 2, 2, ARRhelp,
	ALLmenu, 0, ARRlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _DLG_PART, xUIcomm, xUIhelp, 12, DLGtype, DLGupdt, DLGinpt, DLGline, DLGcols,
	DLGglob, DLGzuob, 2, 4, DLGhelp,
	ALLmenu, 0, DLGlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _KONTINGENT, xUIcomm, xUIhelp, 6, KONtype, KONupdt, KONinpt, KONline,
	KONcols, KONglob, KONzuob, 2, 9, KONhelp,
	ALLmenu, 0, KONlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _PCX_FILES, xUIcomm, xUIhelp, 7, PCXtype, PCXupdt, PCXinpt, PCXline, PCXcols,
	PCXglob, PCXzuob, 3, 3, PCXhelp,
	ALLmenu, 0, PCXlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _GRAPHIK, xUIcomm, xUIhelp, 3, GRAtype, GRAupdt, GRAinpt, GRAline, GRAcols,
	GRAglob, GRAzuob, 3, 4, GRAhelp,
	ALLmenu, 0, GRAlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _BEZEICHNUNG, xUIcomm, xUIhelp, 4, BEZtype, BEZupdt, BEZinpt, BEZline,
	BEZcols, BEZglob, BEZzuob, 5, 0, BEZhelp,
	ALLmenu, 0, BEZlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _TEXTE, xUIcomm, xUIhelp, 4, TXTtype, TXTupdt, TXTinpt, TXTline, TXTcols,
	TXTglob, TXTzuob, 5, 1, TXThelp,
	ALLmenu, 0, TXTlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _SPRACHEN, xUIcomm, xUIhelp, 5, SPRtype, SPRupdt, SPRinpt, SPRline, SPRcols,
	SPRglob, SPRzuob, 4, 0, SPRhelp,
	ALLmenu, 0, SPRlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _OUTPUT, xUIcomm, xUIhelp, 4, OUTtype, OUTupdt, OUTinpt, OUTline, OUTcols,
	OUTglob, OUTzuob, 0, 0, OUThelp,
	ALLmenu, 0, OUTlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _BACKUP, xUIcomm, xUIhelp, 1, BKPtype, BKPupdt, BKPinpt, BKPline, BKPcols,
	BKPglob, BKPzuob, 5, 5, BKPhelp,
	ALLmenu, 0, BKPlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _DIENSTLEISTUNG, xUIcomm, xUIhelp, 7, DTGtype, DTGupdt, DTGinpt, DTGline,
	DTGcols, DTGglob, DTGzuob, 2, 3, DTGhelp,
	ALLmenu, 0, DTGlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _KOMMISSION, xUIcomm, xUIhelp, 16, KOMtype, KOMupdt, KOMinpt, KOMline,
	KOMcols, KOMglob, KOMzuob, 1, 5, KOMhelp,
	ALLmenu, 0, KOMlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _BUCHUNG, xUIcomm, xUIhelp, 18, BCHtype, BCHupdt, BCHinpt, BCHline, BCHcols,
	BCHglob, BCHzuob, 1, 0, BCHhelp,
	ALLmenu, 0, BCHlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _LAND, xUIcomm, xUIhelp, 8, LANDtype, LANDupdt, LANDinpt, LANDline, LANDcols,
	LANDglob, LANDzuob, 4, 2, LANDhelp,
	ALLmenu, 0, LANDlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _ORT, xUIcomm, xUIhelp, 8, ORTtype, ORTupdt, ORTinpt, ORTline, ORTcols,
	ORTglob, ORTzuob, 4, 3, ORThelp,
	ALLmenu, 0, ORTlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _WAEHRUNG, xUIcomm, xUIhelp, 4, WHRtype, WHRupdt, WHRinpt, WHRline, WHRcols,
	WHRglob, WHRzuob, 4, 1, WHRhelp,
	ALLmenu, 0, WHRlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _LABEL, xUIcomm, xUIhelp, 6, LABtype, LABupdt, LABinpt, LABline, LABcols,
	LABglob, LABzuob, 5, 2, LABhelp,
	ALLmenu, 0, LABlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _MSG, xUIcomm, xUIhelp, 4, MSGtype, MSGupdt, MSGinpt, MSGline, MSGcols,
	MSGglob, MSGzuob, 5, 3, MSGhelp,
	ALLmenu, 0, MSGlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _HELP, xUIcomm, xUIhelp, 4, HELPtype, HELPupdt, HELPinpt, HELPline, HELPcols,
	HELPglob, HELPzuob, 5, 4, HELPhelp,
	ALLmenu, 0, HELPlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _RESTORE, xUIcomm, xUIhelp, 1, RESTtype, RESTupdt, RESTinpt, RESTline, RESTcols,
	RESTglob, RESTzuob, 5, 6, RESThelp,
	ALLmenu, 0, RESTlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _LAND_WHR, xUIcomm, xUIhelp, 6, LWtype, LWupdt, LWinpt, LWline, LWcols,
	LWglob, LWzuob, 4, 4, LWhelp,
	ALLmenu, 0, LWlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _KOMM_DETAIL, xUIcomm, xUIhelp, 6, KOMDtype, KOMDupdt, KOMDinpt, KOMDline,
	KOMDcols, KOMDglob, KOMDzuob, 1, 6, KOMDhelp,
	ALLmenu, 0, KOMDlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _HOST_KONT, xUIcomm, xUIhelp, 10, HKONtype, HKONupdt, HKONinpt, HKONline,
	HKONcols, HKONglob, HKONzuob, 2, 8, HKONhelp,
	ALLmenu, 0, HKONlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _KONT_DETAIL, xUIcomm, xUIhelp, 7, KONDtype, KONDupdt, KONDinpt, KONDline,
	KONDcols, KONDglob, KONDzuob, 2, 10, KONDhelp,
	ALLmenu, 0, KONDlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _PERSADR, xUIcomm, xUIhelp, 9, ADRtype, ADRupdt, ADRinpt, ADRline,
	ADRcols, ADRglob, ADRzuob, 1, 4, ADRhelp,
	ALLmenu, 0, ADRlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _SETUPMENU, xUIcomm, xUIhelp, 1, SETUtype, SETUupdt, SETUinpt, SETUline,
	SETUcols, SETUglob, SETUzuob, 0, 1, SETUhelp,
	ALLmenu, 0, SETUlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _OPTIONMENU, xUIcomm, xUIhelp, 1, OPTtype, OPTupdt, OPTinpt, OPTline,
	OPTcols, OPTglob, OPTzuob, 0, 2, OPThelp,
	ALLmenu, 0, OPTlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _QUITMENU, xUIcomm, xUIhelp, 1, QUITtype, QUITupdt, QUITinpt, QUITline,
	QUITcols, QUITglob, QUITzuob, 0, 3, QUIThelp,
	ALLmenu, 0, QUITlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _APPLICATION, xUIcomm, xUIhelp, 1, APPLItype, APPLIupdt, APPLIinpt, APPLIline,
	APPLIcols, APPLIglob, APPLIzuob, 6, 0, APPLIhelp,
	ALLmenu, 0, APPLIlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ _ABOUT, xUIcomm, xUIhelp, 1, ABOUTtype, ABOUTupdt, ABOUTinpt, ABOUTline,
	ABOUTcols, ABOUTglob, ABOUTzuob, 6, 1, ABOUThelp,
	ALLmenu, 0, ABOUTlab, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	False, True, False, False, True},
	{ -1, NULL, NULL, 0, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, 0, 0, NULL, NULL, 0, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, False, False, False, False, False},
	{ -1, NULL, NULL, 0, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, 0, 0, NULL, NULL, 0, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, False, False, False, False, False}
};

