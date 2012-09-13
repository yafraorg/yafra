/*D***********************************************************
 * Header:    MPmsg.h
 *            Returncodes for all functions
 *
 * Copyright: yafra.org, Basel, Switzerland
 *************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpmsg.h,v 1.3 2008-11-02 19:55:33 mwn Exp $
*/

/* message types are defined in MPsta_def.h */


/****************************************************************************
 * neutral elements  0 - 9
 ****************************************************************************/
#define MPOK                  0  /* alles soweit gut          */

#define MPERROR               1  /* allg. Error               */

#define MPMSG                 2  /* allg. Warning/Message     */
#define MPWARNING             2  /*         "                 */

#define MPINFO                3  /* allg. Info                */

#define MPDBERROR             4  /* allg. DB Error            */

#define MPEMERG               5  /* emergency error           */

#define MPDEBUG               6  /* debug information         */

#define MPNOP                 9  /* keine Operation ausgef.   */

/****************************************************************************
 * errors  10 - 1999
 ****************************************************************************/
#define MPE_ALLOC            10  /* Fehler beim allocieren    */
#define MPE_PROTOCOL         11  /* Fehler im erwateten Protokoll */
#define MPE_GLOBPROF         12  /* kein globales Profil */
#define MPE_NOPROFILE        13  /* kein Benutzerprofil vorhanden */
#define MPE_NOUNIQUEBEZ      14  /* keine eindeutige Bez      */
#define MPE_CUTBUFFERIN      15  /* Fehler im CutBufferIn     */
#define MPE_NOBEZINSERT      16  /* keine BEZ insert          */
#define MPE_NOCHOOSE         18  /* keine Auswahl gefunden    */
#define MPE_IDXISUNDEF       20  /* Index ist UNDEF           */
#define MPE_NOSPR            21  /* keine Sprache gefunden    */
#define MPE_NOINSUPDDEL      24  /* kein INS/UPD/DEL gemacht  */
#define MPE_NOPERMISSION     25  /* keine Berechtigung        */
#define MPE_NOBEZ            26  /* keine Bezeichnung vorh.   */
#define MPE_NOSELECTTABLE    28  /* kein ID-Select m�glich    */
#define MPE_NONEWID          29  /* keine neue ID gemacht     */
#define MPE_BEZDELWRONG      30  /* kann diese BEZ nicht loeschen */
#define MPE_NOKAT            35  /* kein KAT vorhanden        */
#define MPE_NODLT            36  /* kein DLT vorhanden        */
#define MPE_NODLTT           37  /* kein DLTT vorhanden       */
#define MPE_NOPCX            44  /* kein PCX vorhanden        */
#define MPE_NODLA            46  /* kein DLA vorhanden        */
#define MPE_NODLAT           47  /* kein DLAT vorhanden       */
#define MPE_NOINFO           48  /* keine Info vorhanden      */
#define MPE_TIMEWRONG        50  /* Zeit falsch (DLA, DL)     */
#define MPE_NOKUNT           52  /* kein KUNT vorhanden       */
#define MPE_NODLNT           59  /* kein DLNT vorhanden       */
#define MPE_NODLN            60  /* kein DLN vorhanden        */
#define MPE_NODLTINDLA       63  /* kein DLT in DLA vorhanden */
#define MPE_NOSAI            64  /* keine SAI vorhanden       */
#define MPE_DATEFROMTO       66  /* DATUM von - bis nicht ok  */
#define MPE_NOWHR            67  /* keine WHR vorhanden       */
#define MPE_NOLAND           68  /* kein LAND vorhanden       */
#define MPE_NOORT            72  /* kein ORT vorhanden        */
#define MPE_NOKOL            74  /* kein Kollektiv vorhanden  */
#define MPE_NOKOLT           75  /* kein KOLT gew�hlt         */
#define MPE_NOPRG            78  /* kein PRG vorhanden        */
#define MPE_NOARR            82  /* kein ARR vorhanden        */
#define MPE_NODLG            83  /* kein TDL vorhanden        */
#define MPE_NOTDL            83  /* kein TDL vorhanden        */
#define MPE_NODL             84  /* keine DL vorhanden        */
#define MPE_NODLTDL          85  /* kein TDL fuer DL vorhanden */
#define MPE_NOAKTT           87  /* kein AKTT vorhanden       */
#define MPE_NOAKT            88  /* keine AKT vorhanden       */
#define MPE_NOKON            90  /* kein KON vorhanden        */
#define MPE_NOHOLDER         91  /* kein Halter(Kunde) def.   */
#define MPE_MUSTONDLORDLA    92  /* Muss entweder auf DL oder DLA  */
#define MPE_NOKONTMENGE      94  /* keine KONT Menge def.     */
#define MPE_NOTXT            96  /* kein TXT vorhanden        */
#define MPE_NOBCH           106  /* keine BCH vorhanden       */
#define MPE_HOSTFIELD       110  /* DLT Fehler beim HostID Feld */
#define MPE_NOAKTTPROZ      111  /* kein Prozess beim AKTT eing. */
#define MPE_NOENTRYFOUND    112  /* kein Eintrag gefunden     */
#define MPE_DLTMISMATCH     113  /* DLT passt nicht mit H_DLT oder HOST */
#define MPE_NOPERSORT       117  /* kein Ortschaft fuer PERS  */
#define MPE_NONAM           118  /* kein Name gefunden        */
#define MPE_NOVOR           119  /* kein Vorname gefunden     */
#define MPE_NOSTA           120  /* kein STA gefunden         */
#define MPE_NODLTDEL_DLA    123  /* kein DLT loeschen w. DLA  */
#define MPE_NODLTDEL_RES    125  /* kein DLT loeschen w. RES  */
#define MPE_NODLTDEL_GRA    126  /* kein DLT loeschen w. GRA  */
#define MPE_NODLTDEL_PCX    127  /* kein DLT loeschen w. PCX  */
#define MPE_NODEL           128  /* kann Entry nicht l�schen  */
#define MPE_NOTXTDEL        129  /* kann TXT nicht l�schen    */
#define MPE_NOBEZDEL        130  /* kann BEZ nicht l�schen    */
#define MPE_NODLTTDEL_DLT   131  /* kann DLTT wegen DL nich l. */
#define MPE_NODLTTDEL_DLTT  132  /* kann DLTT wegen DLTT Host nicht l. */
#define MPE_NODLTTDEL_KAT   133  /* kann DLTT wegen KAT nicht l. */
#define MPE_NODLADEL_TDL    141  /* kann DLA wegen TDL nicht l. */
#define MPE_NOSPRDEL_KUN    153  /* kann SPR wegen KUN nicht l. */
#define MPE_NOSPRDEL_DLN    154  /* kann SPR wegen DLN nicht l. */
#define MPE_NOSPRDEL_BEZ    156  /* kann SPR wegen BEZ nicht l. */
#define MPE_NOSPRDEL_TXT    157  /* kann SPR wegen TXT nicht l. */
#define MPE_NOAKTTDEL_AKT   158  /* kann AKTT wegen AKT nicht l. */
#define MPE_NODLNDEL_KOL    168  /* kann DLN wegen KOL nicht l. */
#define MPE_NOKOLDEL_BCH    170  /* kann KOL wegen BCH nicht loeschen */
#define MPE_NOHKONDEL_KON   171  /* kann HKON wegen KON n.l. */
#define MPE_NODLDEL_PRE     172  /* kann DL wegen PRE nicht l.  */
#define MPE_NODLDEL_KON     173  /* kann DL wegen KON nicht l.  */
#define MPE_NOKONDEL_PRE    174  /* kann KON wegen PRE nicht l. */
#define MPE_NOKONDEL_RES    175  /* kann KON wegen RES nicht l. */
#define MPE_KONKATMIS       184  /* KAT mismatch for this KONT  */
#define MPE_KONDLTMIS       185  /* DLT mismatch for this KONT  */
#define MPE_KONDLTORKAT     186  /* Kontingent entweder auf DLT oder KAT */
#define MPE_KONDLTEXISTS    187  /* DLT bereits in anderem Kontingent */
#define MPE_KONKATSUMME     188  /* Summer der Objecte der Kontingent falsch */
#define MPE_KONOVERFLOW     189  /* Das Kontingentdetail ist ausgebucht */
#define MPE_WRONGOBJECT     190  /* unbekanntes Objekt PRG ERROR */
#define MPE_ONLYDLORDLA     192  /* entweder auf DL oder DLA */
#define MPE_WRONGBCHINDLN   193  /* unbek. BCH als Referenz in DLN */
#define MPE_NOBCHACTIV      194  /* keine Buchung aktiv       */
#define MPE_NOBCHOBJ        195  /* kein Buchungsobjekt vorh. */
#define MPE_NOBCHST         197  /* keine Buchungsstelle vor. */
#define MPE_OUTPUT          198  /* error in OUTPUT Menu */
#define MPE_NOSEX           200  /* kein Geschlecht           */
#define MPE_NOKAR           201  /* kein KAR vorhanden        */
#define MPE_WRONGBCHSTA     203  /* falscher Buchungsstatus   */
#define MPE_NODLDEL_ARRDL   205  /* kann DL wegen ARR_DL nicht l.  */
#define MPE_NOINFOPCX       206  /* keine Info oder PCX Bild  */
#define MPE_RESMIS          208  /* RES inkonsistenz          */
#define MPE_NODLTDEP        211  /* keine DLT Einschr�nkungen */
#define MPE_NOBCHAKTDET     212  /* kein AKT_DETAIL zur BCH   */
#define MPE_NODLNINBCH      221  /* kein DLN in BCH           */
#define MPE_MUSSPARAEMPTY   232  /* Mussparameter fehlt       */
#define MPE_NOKOMM          233  /* keine Kommission vorhanden */
#define MPE_NOKOMSATZ       234  /* kein Komm. Satz           */
#define MPE_NOKOMTYP        235  /* Kommissionstyp Fehler     */
#define MPE_KOMDEF          236  /* Kommissionsdef. Fehler    */
#define MPE_KOMTYPSATZTYP   237  /* Durcheinander mit Kom.Typ */
#define MPE_NOAKTTDEL_AD    244  /* kann AKTT wegen AKTDET nicht l. */
#define MPE_DBIDPTR         245  /* Doppel BuchungsID verptr. */
#define MPE_NODLADEL_DLA    247  /* kann DLA wegen DLA nicht l. */
#define MPE_NODLADEL_PRE    248  /* kann DLA wegen PRE nicht l. */
#define MPE_NODLADEL_KON    249  /* kann DLA wegen KON nicht l. */
#define MPE_NODLADEL_KOM    250  /* kann DLA wegen KOM nicht l. */
#define MPE_NOTDLDEL_TDL    251  /* kann TDL wegen TDL nicth l. */
#define MPE_NOTDLDEL_RES    252  /* kann TDL wegen RES nicth l. */
#define MPE_NOTDLDEL_DL     253  /* kann TDL wegen DL nicth l. */
#define MPE_NOTDLDEL_AKTDET 254  /* kann TDL wegen AKTDET nicth l. */
#define MPE_NODLTTDEL_RES   255  /* kann DLTT wegen RES nicth l. */
#define MPE_NODLDEL_RES     256  /* kann DL wegen RES nicht l.  */
#define MPE_NODLDEL_KOM     257  /* kann DL wegen KOM nicht l.  */
#define MPE_NODLDEL_AKTDET  258  /* kann DL wegen AKTDETAIL nicht l.  */
#define MPE_NODLDEL_DLPART  259  /* kann DL wegen DLPARTS nicht l.  */
#define MPE_NOKONDEL_KOND   267  /* kann KON wegen KONDET n. l. */
#define MPE_DLNSTEP         271  /* DLN Step mismatch         */
#define MPE_BCHWITHNODLN    273  /* BCH ohne DLN              */
#define MPE_DLTKATMIS       274  /* KAT und DLT stimmen nicht */
#define MPE_NOPRE           276  /* kein PRE vorhanden        */
#define MPE_PREGLTABDAT     277  /* Zeit/Datum Fehler (Format) */
#define MPE_NOKOLDEL_KOM    278  /* kann KOL wegen KOMD nicht loeschen */
#define MPE_NOGRADLT        279  /* kein DLT in GRA vorhanden */
#define MPE_NOGRA           282  /* kein GRA vorhanden        */
#define MPE_ARRBUFFER       283  /* interner ArrDetail Buffer Fehler */
#define MPE_DLTNOTINKON     286  /* DLT is not in this KONT */
#define MPE_BUSYBYKON       287  /* DLT is busy by KONT */
#define MPE_NODIRECTDEL     288  /* kein direkt. l�schen m�gl.*/
#define MPE_DLNDETAIL       289  /* WriteDetail Fehler beim DLN */
#define MPE_KOMMISMATCH     290  /* Kommissionstyp stimmt nicht */
#define MPE_NOKATFORRES     292  /* keine KAT in RES          */
#define MPE_ARRCOPY         293  /* Copy/Move ARR Fehler      */
#define MPE_DLCOPY          294  /* Copy/Move DL Fehler       */
#define MPE_WRONGCOMMTYP    295  /* falscher comm-typ im MPtalk */
#define MPE_TESTREGION      296  /* Fehler im GRtestRegion    */
#define MPE_NOGRAINDELMODE  297  /* keine Grafik im delete mode */
#define MPE_NOLABELS        298  /* keine GUI labels in der DB */
#define MPE_PASSWD          301  /* Fehler bei /etc/passwd    */
#define MPE_WRONGACTIONTYP  302  /* falscher ACTIONTYP        */
#define MPE_NOMAXID         303  /* keine MAX ID gefunden     */
#define MPE_NOMINID         304  /* keine MIN ID gefunden     */
#define MPE_SPLIT           305  /* UtilSplitBuffer Fehler    */
#define MPE_FILEERROR       306  /* gen. file error           */
#define MPE_NOFILE          307  /* kein file vorhanden       */
#define MPE_NOACCES         308  /* kein Zugriff              */
#define MPE_FAULT           309  /* file korrupt              */
#define MPE_NOTDIR          310  /* not a directory           */
#define MPE_LOOP            311  /* zuviele links auf file    */
#define MPE_TOOLONG         312  /* name zu lang              */
#define MPE_PCXINPUT        313  /* PCX braucht Bez + File f�r Input */
#define MPE_NONEWIDINSERT   314  /* keine neue ID gefunden    */
#define MPE_SPRBEZCOPY      315  /* kein copy der BEZ einer SPR */
#define MPE_SPRTXTCOPY      316  /* kein copy des TXT einer SPR */
#define MPE_NODEFAULTSPRDEL 317  /* kein loeschen der def. SPR */
#define MPE_GRAFORMTOOLONG  318  /* GRAFORM entry too long */
#define MPE_NODLNFORKOL     319  /* kein Verantwortlicher fuer Kollektiv */
#define MPE_NOAKTSTART      320  /* AKTIONEN konnten nicht gestartet werden */
#define MPE_NODLATDEL_DLA   321  /* DLAT is still in DLA */
#define MPE_NORES           322  /* keine RES Daten */
#define MPE_RESIMPOSSIBLE   323  /* DL hat impossible status  */
#define MPE_NORESDAT        324  /* kein DATUM zu dyn. DL     */
#define MPE_NODLTFREE       325  /* kein DLT mehr frei       */
#define MPE_DLTSPACE        326  /* zu wenig platz in DLT    */
#define MPE_DLTISNOTFREE    327  /* DLT ist nicht frei */
#define MPE_NOAKTTDEL_AKTP  328  /* kann AKTT wegen AKTPARA nicht loeschen */
#define MPE_NOPARABEZ       329  /* keine Parameterbezeichnung */
#define MPE_PARAMISMATCH    330  /* Parameter Durcheinander */
#define MPE_NOAKTDEL_AKTG   331  /* kein AKT del wegen AKTG */
#define MPE_NOAKTFORDLDLA   332  /* kein AKT fuer DL/DLA definiert */
#define MPE_NOHKONDEL_KOND  333  /* kann HKON wegen KONDET n.l. */

/****************************************************************************
 * warnings/questions  500 - 999
 ****************************************************************************/
#define MPW_NOFREE          500  /* kein mem freigegeben      */
#define MPW_NODLTDEL_DLT    501  /* Frage DLT loeschen w. Host ? */
#define MPW_SPRCOPY         502  /* kopiere SPR ? */
#define MPW_KOMMDET_DEL     503  /* kommissionsdetail ebenfalls l. ? */
#define MPW_DLINSORUPD      504  /* DL insert or update ?            */
#define MPW_DELALLDLN       505  /* gesamter DLN loeschen ?          */

#define MPW_ARRSTILLINBCH   178	/* ARR sind noch in BCH drin */
#define MPW_ARRDLGPRESENT   204  /* ARR_DLG Verkn�pfung vorh. */

/****************************************************************************
 * infos  1000 - xxxx
 ****************************************************************************/
#define MPI_MOREDLBOOKING  1000  /* noch mehr DL's buchen     */
#define MPI_MOREDLN        1001  /* noch ein DLN eingeben     */
#define MPI_AKTSTART       1002  /* Aktionsstart              */
#define MPI_BOOKEND        1003  /* Buchung abgeschlossen     */
#define MPI_RESINFOTITEL1  1004  /* Reservationsinfotitel     */
#define MPI_RESINFOTITEL2  1005  /* Reservationstitel 2       */
#define MPI_RESINFOARRTIT  1006  /* Res.Info ARR Titel        */
#define MPI_RESINFODLNTIT  1007  /* Res.Info DLN Titel        */
#define MPI_RESINFORESTIT  1008  /* Res.Info RES Titel        */
#define MPI_RESINFOOPEN    1009  /* Res.Info noch offen       */
#define MPI_RESINFONOTHING 1010  /* Res.Info nichts zu buchen */
#define MPI_BMKATTITEL     1011  /* BM Kategorien Menu Titel  */
#define MPI_AKTEXECDONE1   1012  /* OK Meldung ueber exec AKT */
#define MPI_AKTEXECDONE2   1013  /* OK Meldung ueber exec AKT */
#define MPI_RESINFOTITEL3  1014
#define MPI_RESINFOTITEL4  1015
#define MPI_RESINFORESTIT2 1016  /* Res.Info RES Titel        */
#define MPI_YES_TRUE       1017
#define MPI_NO_FALSE       1018

/**************************************************************/
/* db errors -1 - -99999      in memory sql_messages[]        */
/**************************************************************/
#define MPSQL_OK                 (int)0      /*!!! must be same as MPOK !!!*/
#define MPSQL_END_OF_TABLE       (int)100
#define MPSQL_TRANSACTION_EXISTS (int)-2103
#define MPSQL_ENTRY_EXISTS       (int)-2509
#define MPSQL_NOMEMORY           (int)-4008
#define MPSQL_MULTIPLE_ROWS      (int)-10002
#define MPSQL_DEADLOCK           (int)-14024
#define MPSQL_DB_KORRUPT         (int)-14075

/**************************************************************/
/* system messages 0 - 9999   in memory sys_messages[]        */
/**************************************************************/
#define MPS_SUPPORT           0  /* Supportmeldung            */
#define MPS_MSGERROR          1  /* Fehler in UtilMsg         */
#define MPS_NOMSG             2  /* keine Meldung gefunden    */
#define MPS_ALLOC             3  /* memory allocation error   */
#define MPS_ERRORHEADER       4  /* Kopf der Fehlermeldung    */
#define MPS_IPCERROR          9005  // IPC socket error - exit
