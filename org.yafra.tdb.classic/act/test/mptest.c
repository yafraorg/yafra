/*D***********************************************************
 * program:      mptest
 * description:  complete standalone database access test
 *               program to check if the db access works
 *               the default user (root/root)
 *
 * arguments:    standard arguments
 *               -n  database name
 *
 * Copyright: yafra.org
 *************************************************************/

/* RCS static ID */
static char rcsid[]="$Header: test program$";

#include "version.h"

/* tdb actions API includes */
#include <mpact.h>

/* Include or define globals */
#include <mpvarlib.h>
#include <mpvarapi.h>
#include <mpvaract.h>
#include <mpprolib.h>
#include <mpproapi.h>

#include <mpdb.h>
#define SQL_MAX_COL 50
#define SQL_MAX_ROW_LEN   512
#define SQL_MAX_ROW 50
#define SQL_MAX_BUF SQL_MAX_ROW_LEN*SQL_MAX_ROW
#include <mpdbglob.h>


#ifdef ps_win
#define MPTSTFILE "\\temp\\mptestout.txt"
#else
#define MPTSTFILE "/tmp/mptestout.txt"
#endif

/* make test insert and delete */
#define _INS_PROFIL_TEST "INSERT INTO TDBADMIN.MP_PROFIL \
         VALUES (998, 'test998', -1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0);"
#define _DEL_PROFIL_TEST "DELETE FROM TDBADMIN.MP_PROFIL \
         WHERE MPUSER =  'test998';"


#if defined(TDBORACLE)
#define _COMMIT "COMMIT;"
#define _SELECT_TRAEGER_VIEW "SELECT * FROM TDBADMIN.TRAEGER_VIEW WHERE SPR = 1 \
                              AND ID > -1 ORDER BY BEZ;"
#define _SELECT_MP_PROFIL "SELECT * FROM TDBADMIN.MP_PROFIL;"
#define _SELECT "SELECT * FROM TDBADMIN.SPRACHEN ORDER BY ROWNUM"
#define _COUNT_SPR_BEZ "SELECT COUNT(BEZ_ID) FROM TDBADMIN.SPRACHEN \
                        ORDER BY ROWNUM"
#define _SELECT_LAND "SELECT * FROM TDBADMIN.LAND WHERE ROWNUM < 4 \
                      ORDER BY ROWNUM"
#define _SELECT_SAISON "SELECT * FROM TDBADMIN.SAISON ORDER BY ROWNUM"

#define _SELECT_PERSONEN "SELECT * FROM TDBADMIN.PERSONEN WHERE ROWNUM < 10 \
                          ORDER BY ROWNUM"
#define _SELECT_REISENDER_TYP "SELECT * FROM TDBADMIN.REISENDER_TYP \
                               WHERE ROWNUM<4 ORDER BY ROWNUM"
#define _SELECT_PERSADR "SELECT * FROM TDBADMIN.PERSADR \
                         ORDER BY ROWNUM"
#define _SELECT_KONTINGENT "SELECT * FROM TDBADMIN.KONTINGENT WHERE ROWNUM < 4 \
                            ORDER BY ROWNUM"
#define _SELECT_KOMMISSION "SELECT * FROM TDBADMIN.KOMMISSION WHERE ROWNUM < 4 \
                            ORDER BY ROWNUM"
#define _SELECT_PREIS "SELECT * FROM TDBADMIN.PREIS WHERE ROWNUM < 4 \
                       ORDER BY ROWNUM"
#define _SELECT_KAPA "SELECT * FROM TDBADMIN.KAPA WHERE ROWNUM < 4 ORDER BY ROWNUM"
#define _SELECT_STA_VIEW "SELECT * FROM TDBADMIN.STA_VIEW WHERE ROWNUM < 4 \
                          ORDER BY ROWNUM"
#define _SELECT_LAND_VIEW "SELECT * FROM TDBADMIN.LAND_VIEW WHERE ROWNUM < 4 \
                           ORDER BY ROWNUM"
#define _SELECT_KUN_VIEW "SELECT * FROM TDBADMIN.KUNDEN_VIEW WHERE ROWNUM < 4 \
                          ORDER BY ROWNUM"
#define _SELECT_MPV_KAPA "SELECT * FROM TDBADMIN.MPV_KAPA WHERE ROWNUM < 4 \
                          ORDER BY ROWNUM"
#define _SELECT_MPV_DLNADR "SELECT * FROM TDBADMIN.MPV_DLNADR WHERE ROWNUM < 4 \
                            ORDER BY ROWNUM"
#define _SELECT_MPV_KUNADR "SELECT * FROM TDBADMIN.MPV_KUNADR WHERE ROWNUM < 4 \
                            ORDER BY ROWNUM"
#define _SELECT_STATUS_WERTE "SELECT * FROM TDBADMIN.STATUS_WERTE WHERE ROWNUM < 4 \
                              ORDER BY ROWNUM"
#define _SELECT_KOL "SELECT * FROM TDBADMIN.KOLLEKTIV WHERE ROWNUM < 4 \
                              ORDER BY ROWNUM"
#endif

#if defined(TDBODBC) || defined(TDBMYSQL) || defined(TDBMSSQL) || defined(TDBADABAS)
#define _SELECT "SELECT * FROM TDBADMIN.SPRACHEN;"
#define _SELECT_STATUS_WERTE "SELECT * FROM TDBADMIN.STATUS_WERTE;"
#define _SELECT_MP_PROFIL "SELECT * FROM TDBADMIN.MP_PROFIL;"
#define _COMMIT "COMMIT;"
#define _COUNT_SPR_BEZ "SELECT COUNT(BEZ_ID) FROM TDBADMIN.SPRACHEN;"
#define _SELECT_LAND "SELECT * FROM TDBADMIN.LAND;"
#define _SELECT_SAISON "SELECT * FROM TDBADMIN.SAISON;"
#define _SELECT_PERSONEN "SELECT * FROM TDBADMIN.PERSONEN;"
#define _SELECT_REISENDER_TYP "SELECT * FROM TDBADMIN.REISENDER_TYP;"
#define _SELECT_PERSADR "SELECT * FROM TDBADMIN.PERSADR;"
#define _SELECT_KONTINGENT "SELECT * FROM TDBADMIN.KONTINGENT;"
#define _SELECT_KOMMISSION "SELECT * FROM TDBADMIN.KOMMISSION;"
#define _SELECT_PREIS "SELECT * FROM TDBADMIN.PREIS;"
#define _SELECT_KAPA "SELECT * FROM TDBADMIN.KAPA;"
#define _SELECT_TRAEGER_VIEW "SELECT * FROM TDBADMIN.TRAEGER_VIEW WHERE SPR=1 \
                              AND ID=-1 ORDER BY BEZ;"
#define _SELECT_STA_VIEW "SELECT * FROM TDBADMIN.STA_VIEW;"
#define _SELECT_LAND_VIEW "SELECT * FROM TDBADMIN.LAND_VIEW;"
#define _SELECT_KUN_VIEW "SELECT * FROM TDBADMIN.KUNDEN_VIEW;"
#define _SELECT_MPV_KAPA "SELECT * FROM TDBADMIN.MPV_KAPA;"
#define _SELECT_MPV_DLNADR "SELECT * FROM TDBADMIN.MPV_DLNADR;"
#define _SELECT_MPV_KUNADR "SELECT * FROM TDBADMIN.MPV_KUNADR;"
#define _SELECT_KOL "SELECT * FROM TDBADMIN.KOLLEKTIV;"
#endif

/* local prototypes */
static int UtilSetUser(void);

static void StructTest(void);
static void put_mp_profil(MP_PROFIL *, int);
static void put_land(LAND *, int);
static void put_sprachen(SPRACHEN *, int);
static void put_saison(SAISON *, int);
static void put_personen(PERSONEN *, int);
static void put_reisender_typ(REISENDER_TYP *, int);
static void put_persadr(PERSADR *, int);
static void put_kontingent(KONTINGENT *, int);
static void put_kommission(KOMMISSION *, int);
static void put_preis(PREIS *, int);
static void put_kapa(KAPA *, int);
static void put_sta_view(STA_VIEW *, int);
static void put_land_view(LAND_VIEW *, int);
static void put_kun_view(KUN_VIEW *, int);
static void put_mpv_kapa(MPV_KAPA *, int);
static void put_mpv_dlnadr(MPV_DLNADR *, int);
static void put_mpv_kunadr(MPV_KUNADR *, int);
static void put_status_werte(STATUS_WERTE *, int);
static void put_kollektiv(KOLLEKTIV *, int);

extern void UtilMsgWrite(char *);

FILE *fp;

/*F--------------------------------------------------------------------------
 *  Function:	OUTcontrol()
 *					get "Kunden" infos (KID) and build filename
 *					find device (fax or tlx)
 *					the radix: "FAX" or "TLX" are also used in cronfax script!
 *					get text which is requested to destination (BID)
 *					Request specified action
 *
 *  In:			-argc, argv as action was invoked
 *  out:			-
 *  Return:		-completion code
 *---------------------------------------------------------------------------
 */
int main(int, char **);
int main(int argc, char **argv)
{
	extern MEMOBJ apimem;           /* defined in api functions.sql */
	extern STATUS_WERTE sta;
	extern int dialogsprache;
	extern int outputsprache;
	extern MP_PROFIL prof;

	int	status;
	int	row_cnt;
	char	bezeichnung[_BEZLEN+5];
	char	tmp_buffer[_RECORDLEN];
	char	query[_QUERYLEN];
	char	*coredump = NULL;
	MEMOBJ	sqlmem;
	int	sprache;                /* language id */
	int	intretval = (int)_INTEGER;
	char	mp_dbname[128];
	char MailFile[RECLAENGE];

	SPRACHEN       *Psprachen;
	LAND           *Pland;
	SAISON         *Psaison;
	TRAEGER_VIEW	*Ptraeger_view;
	MP_PROFIL	*Pmp_profil;
	PERSONEN	*Ppersonen;
	PERSADR *Padr;
	REISENDER_TYP	*Preisender_typ;
	PERSADR		*Ppersadr;
	KONTINGENT	*Pkontingent;
	KOLLEKTIV	*Pkol;
	KOMMISSION	*Pkommission;
	PREIS		*Ppreis;
	KAPA		*Pkapa;
	STA_VIEW	*Psta_view;
	LAND_VIEW	*Pland_view;
	KUN_VIEW	*Pkun_view;
	MPV_KAPA	*Pmpv_kapa;
	MPV_DLNADR	*Pmpv_dlnadr;
	MPV_KUNADR	*Pmpv_kunadr;
	STATUS_WERTE	*Pstatus_werte;

#ifdef ps_linux
	setlocale(LC_ALL, "en_US.utf8");
#endif

	/* extern FILE *FPmail; */

	(void)printf("Start travelDB test access to database");
	(void)strcpy(userpassword, "");
	fp = fopen(MPTSTFILE, _P_WRITE_);

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;
	apimem.buffer   = NULL;
	apimem.alloclen = 0;
	apimem.datalen  = 0;

	/* init language handling */
	sprache         = 1;
	intretval       = -1;
	dialogsprache   = 1;
	aktuellesprache = 1;
	outputsprache   = (int)UNDEF;

	/* Init */
	DebugFlag  = (int)TRUE;
	FatalError = (int)FALSE;
	reinitflag = (int)FALSE;
	targetsta  = (int)_UNDEF;
	exectyp    = _AKT_MAN;
	bchid      = (int)_UNDEF;
	dlid       = (int)_UNDEF;
	kunid      = (int)_UNDEF;
	dlgid      = (int)_UNDEF;
	akttid     = (int)_UNDEF;
	arrid      = (int)_UNDEF;
	kuntypid   = (int)_UNDEF;
	dlnid      = (int)_UNDEF;
	kolid      = (int)_UNDEF;
	dltid      = (int)_UNDEF;
	dlaid      = (int)_UNDEF;
	abdate     = (int)_UNDEF;
	time_start = (int)UNDEF, time_end = (int)UNDEF;
	aktuellesprache = 1;

	(void)UtilSetUser();
	strcpy(prof.mpuser, "");

	FPmail = MailOpen(MailFile, _UNDEF, 1);
	if (FPmail == NULL)
		exit(-1);

	if (argc < 2)
		{
		printf("usage: mptest -n database_name (default user is tdbadmin/yafra)\n");
		exit(-1);
		}
	if (strcmp(argv[1], "-n") == 0)
		{
		strcpy(mp_dbname, argv[2]);
		}
	else
		{
		printf("usage: mptest -n database_name (default user is tdbadmin/yafra)\n");
		exit(-1);
		}

#ifdef TDBDUMMY
	(void)printf("Dummy DB only - no operations to do with db\n", status);
	exit(0);
#endif

	/* DB connect */
	status = MPAPIdb_connect(mp_dbname, "tdbadmin", "yafra");
	if (status != (int)MPOK)
		{
		(void)printf("\nError opening the DB wiht code %d\n", status);
		exit(status);
		}
	else
		(void)printf("\n\nDB opened\n");

/* TEST structures (sizeof compared to mpdbglob.h) */
	StructTest();

/* TEST begin trx */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		return(status);

/* TEST SELECT ON Sprachen */
	(void)printf("start SPRACHEN SQL query\n");
	(void)sprintf(query, _SELECT);
	status = MPAPIdb_sqlquery((int)_SPRACHEN, &sqlmem.buffer, query,
	         &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
	Psprachen = (SPRACHEN *)sqlmem.buffer;
	printf("SQL query done with status %d and rowcnt %d\n", status, row_cnt);
	if (status != (int)MPOK)
		return((int)MPERROR);
	if (row_cnt < 1)
		return((int)MPERROR);
	(void)put_sprachen(Psprachen, row_cnt);

/* TEST SELECT ON STATUS_WERTE */
	(void)printf("start STATUS WERTE SQL query\n");
	(void)sprintf(query, _SELECT_STATUS_WERTE);
	status = MPAPIdb_sqlquery((int)_STATUS_WERTE, &sqlmem.buffer, query,
	         &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
	Pstatus_werte = (STATUS_WERTE *)sqlmem.buffer;
	printf("SQL query done with status %d and rowcnt %d\n", status, row_cnt);
	if (status != (int)MPOK)
		return((int)MPERROR);
	if (row_cnt < 1)
		return((int)MPERROR);
	(void)put_status_werte(Pstatus_werte, row_cnt);

/* TEST SELECT ON LAND */
   (void)printf("start LAND (nullables) SQL query\n");
   (void)sprintf(query, _SELECT_LAND);
   status = MPAPIdb_sqlquery((int)_LAND, &sqlmem.buffer, query,
            &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
   Pland = (LAND *)sqlmem.buffer;
   printf("SQL query done with status %d and rowcnt %d\n", status, row_cnt);
   if (status != (int)MPOK)
      return((int)MPERROR);
   if (row_cnt < 1)
      return((int)MPERROR);
	(void)put_land(Pland, row_cnt);

/* TEST SELECT ON VIEW LAND_VIEW */
   (void)printf("start LAND_VIEW (view) SQL query\n");
   (void)sprintf(query, _SELECT_LAND_VIEW);
   status = MPAPIdb_sqlquery((int)_LAND_VIEW, &sqlmem.buffer, query,
            &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
   Pland_view = (LAND_VIEW *)sqlmem.buffer;
   printf("SQL query done with status %d and rowcnt %d\n", status, row_cnt);
   if (status != (int)MPOK)
      return((int)MPERROR);
   if (row_cnt < 1)
      return((int)MPERROR);
	(void)put_land_view(Pland_view, row_cnt);

/* TEST SELECT ON KOLLEKTIV */
   (void)printf("start KOLLEKTIV SQL query\n");
   (void)sprintf(query, _SELECT_KOL);
   status = MPAPIdb_sqlquery((int)_KOLLEKTIV, &sqlmem.buffer, query,
            &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
   Pkol = (KOLLEKTIV *)sqlmem.buffer;
   printf("SQL query done with status %d and rowcnt %d\n", status, row_cnt);
   if (status != (int)MPOK)
      return((int)MPERROR);
   if (row_cnt < 1)
      return((int)MPERROR);
	(void)put_kollektiv(Pkol, row_cnt);

/* TEST SELECT ON PERSADR */
   (void)printf("start PERSADR SQL query\n");
   (void)sprintf(query, _SELECT_PERSADR);
   status = MPAPIdb_sqlquery((int)_PERSADR, &sqlmem.buffer, query,
            &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
   Padr = (PERSADR *)sqlmem.buffer;
   printf("SQL query done with status %d and rowcnt %d\n", status, row_cnt);
   if (status != (int)MPOK)
      return((int)MPERROR);
   if (row_cnt < 1)
      return((int)MPERROR);
	(void)put_persadr(Padr, row_cnt);

#ifdef TEST_INSUPD
/* TEST INSERT MPAPIdb_sqlcommand testen */
	row_cnt = -1;
	(void)sprintf(query, _INS_PROFIL_TEST);
	status = MPAPIdb_sqlcommand (query, &row_cnt);
	if (status != MPOK)
		return(MPERROR);

/* TEST DELETE MPAPIdb_sqlcommand testen */
	row_cnt = -1;
	(void)sprintf(query, _DEL_PROFIL_TEST);
	status = MPAPIdb_sqlcommand (query, &row_cnt);
	if (status != MPOK)
		return(MPERROR);

/* TEST commit trx */
	MPAPIdb_committrx();

/* AND START AGAIN FOR MORE TESTS */
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		return(status);

/* TEST SELECT on MP_PROFIL */
   (void)printf("start SQL query\n");
   (void)sprintf(query, _SELECT_MP_PROFIL);
   status = MPAPIdb_sqlquery((int)_MP_PROFIL, &sqlmem.buffer, query,
                         &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
   Pmp_profil = (MP_PROFIL *)sqlmem.buffer;
   printf("SQL query done with status %d and rowcnt %d\n", status, row_cnt);
   if (status != (int)MPOK)
      return((int)MPERROR);
   if (row_cnt < 1)
      return((int)MPERROR);
	(void)put_mp_profil(Pmp_profil, row_cnt);

/* TEST rollback trx */
	MPAPIdb_rollbacktrx();

#endif

/* TEST DB close */
	MPAPIdb_release();
	(void)printf("\n\nDB closed\n");
	fclose(fp);
	return(0);
}



/*SF**********************************************************
 * Function:        set user and userid of current job
 * Return:          the real userid
 *************************************************************/
static int UtilSetUser(void)
{
   extern char userid[];   /* wird durch MPdbi_glob.h definiert */

#ifdef ps_hpux
   uid_t user;
   struct passwd *userpw;

   user = getuid();
   userpw = getpwuid(user);
   strcpy(userid, userpw->pw_name);
#else
	int user = 0;

   strcpy(userid, "root");
#endif

   return((int)user);
}

#ifdef ps_unix
#define SFILE "/tmp/mpstruct"
#else
#define SFILE "\\TEMP\\mpstruct.txt"
#endif
static void StructTest(void)
{
	FILE *sfp;
	int table, elem, elemleng = 0;
	if ( (sfp = fopen(SFILE, _P_WRITE_)) == NULL )
		{
		return;
		}

	for ( table = 0; table < 293; table++ )
		{
		if (def_table[table].name == NULL)
			continue;
		elemleng = (int)0;
		for ( elem = 0; def_table[table].elements[elem].leng > (int)0; elem++ )
			{
			elemleng += def_table[table].elements[elem].leng;
			}
		if ( def_table[table].sqlrowlen != elemleng )
			{
			fprintf(sfp,"TABELLE = %-20.20s SIZEOF LENG = %4d ELEMENT LENG = %4d%s",
			def_table[table].name, def_table[table].sqlrowlen,elemleng, _P_EOL_);
			}
		else
			{
			fprintf(sfp,"TABELLE = %-20.20s SIZEOF = %4d | %4d%s",
			def_table[table].name, def_table[table].sqlrowlen,elemleng, _P_EOL_);
			}
		}
	fclose(sfp);
}


/*SF**********************************************************
 * Function:
 * Return:
 *************************************************************/
static void put_mp_profil(MP_PROFIL *Pmp_profil, int row_cnt)
{
	int i;

	fprintf(fp, "MP_PROFIL:%s", _P_EOL_);
	fprintf(fp, "==========%s", _P_EOL_);
	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, "|%d| ", Pmp_profil[i].mpid);
		fprintf(fp, "|%s| ", Pmp_profil[i].mpuser);
		fprintf(fp, "|%d| ", Pmp_profil[i].bchst);
		fprintf(fp, "|%d| ", Pmp_profil[i].seclevel);
		fprintf(fp, "|%d| ", Pmp_profil[i].s_id);
		fprintf(fp, "|%d| ", Pmp_profil[i].land_id);
		fprintf(fp, "|%d| ", Pmp_profil[i].dltt_id);
		fprintf(fp, "|%d| ", Pmp_profil[i].dlt_id);
		fprintf(fp, "|%d| ", Pmp_profil[i].kat_id);
		fprintf(fp, "|%d| ", Pmp_profil[i].dlat_id);
		fprintf(fp, "|%d| ", Pmp_profil[i].dlnt_id);
		fprintf(fp, "|%d| ", Pmp_profil[i].sai_id);
		fprintf(fp, "|%d| ", Pmp_profil[i].prg_id);
		fprintf(fp, "|%d| ", Pmp_profil[i].a_zeit);
		fprintf(fp, "|%d| ", Pmp_profil[i].e_zeit);
		fprintf(fp, "|%d|<<", Pmp_profil[i].p_range);

		fprintf(fp, "%s", _P_EOL_);
	}
	fprintf(fp, "%s", _P_EOL_);
}

/*SF**********************************************************
 * Function:
 * Return:
 *************************************************************/
static void put_land(LAND *Pland, int row_cnt)
{
	int i;

	fprintf(fp, "LAND:%s", _P_EOL_);
	fprintf(fp, "==========%s", _P_EOL_);
	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, "|%d| ", Pland[i].land_id);
		fprintf(fp, "|%d| ", Pland[i].bez_id);
		fprintf(fp, "|%d| ", Pland[i].textid);
		fprintf(fp, "|%s| ", Pland[i].krzl);
		fprintf(fp, "|%d| ", Pland[i].haupt_ort);
		fprintf(fp, "|%d| ", Pland[i].haupt_whr);
		fprintf(fp, "|%d| ", Pland[i].haupt_spr);
		fprintf(fp, "|%f| ", Pland[i].vat);
		fprintf(fp, "|%s|<<", Pland[i].dateformat);

		fprintf(fp, "%s", _P_EOL_);
	}
	fprintf(fp, "%s", _P_EOL_);
}

/*SF**********************************************************
 * Function:
 * Return:
 *************************************************************/
static void put_sprachen(SPRACHEN *Psprachen, int row_cnt) {
	int i;

	fprintf(fp, "SPRACHEN:%s", _P_EOL_);
	fprintf(fp, "==========%s", _P_EOL_);
	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, "|%d| ", Psprachen[i].s_id);
		fprintf(fp, "|%d| ", Psprachen[i].bez_id);
		fprintf(fp, "|%d| ", Psprachen[i].dialog);
		fprintf(fp, "|%d| ", Psprachen[i].output);
		fprintf(fp, "|%d| ", Psprachen[i].gui);
		fprintf(fp, "|%s|<<", Psprachen[i].sysbez);

		fprintf(fp, "%s", _P_EOL_);
	}
	fprintf(fp, "%s", _P_EOL_);
}

/*SF**********************************************************
 * Function:
 * Return:
 *************************************************************/
static void put_personen(PERSONEN *Ppersonen, int row_cnt) {
	int i;

	fprintf(fp, "PERSONEN:%s", _P_EOL_);
	fprintf(fp, "==========%s", _P_EOL_);
	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, "|%d| ", Ppersonen[i].pers_id);
		fprintf(fp, "|%d| ", Ppersonen[i].pers_typ);
		fprintf(fp, "|%s| ", Ppersonen[i].name);
		fprintf(fp, "|%d| ", Ppersonen[i].s_id);
		fprintf(fp, "|%d| ", Ppersonen[i].sta_id);
		fprintf(fp, "|%d|<<", Ppersonen[i].textid);

		fprintf(fp, "%s", _P_EOL_);
	}
	fprintf(fp, "%s", _P_EOL_);
}

/*SF**********************************************************
 * Function:
 * Return:
 *************************************************************/
static void put_reisender_typ(REISENDER_TYP *Preisender_typ, int row_cnt) {
	int i;

	fprintf(fp, "PERSONEN TYP:%s", _P_EOL_);
	fprintf(fp, "==========%s", _P_EOL_);
	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, "|%d| ", Preisender_typ[i].rkr_id);
		fprintf(fp, "|%d| ", Preisender_typ[i].bez_id);
		fprintf(fp, "|%d| ", Preisender_typ[i].textid);
		fprintf(fp, "|%s| ", Preisender_typ[i].dlncode);
		fprintf(fp, "|%d| ", Preisender_typ[i].vonalter);
		fprintf(fp, "|%d|<<", Preisender_typ[i].bisalter);

		fprintf(fp, "%s", _P_EOL_);
	}
	fprintf(fp, "%s", _P_EOL_);
}

/*SF**********************************************************
 * Function:
 * Return:
 *************************************************************/
static void put_persadr(PERSADR *Ppersadr, int row_cnt) {
	int i;

	fprintf(fp, "PERSADR:%s", _P_EOL_);
	fprintf(fp, "==========%s", _P_EOL_);
	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, "|%d| ", Ppersadr[i].pers_id);
		fprintf(fp, "|%s| ", Ppersadr[i].ans);
		fprintf(fp, "|%s| ", Ppersadr[i].adr1);
		fprintf(fp, "|%s| ", Ppersadr[i].adr2);
		fprintf(fp, "|%s| ", Ppersadr[i].adr3);
		fprintf(fp, "|%s| ", Ppersadr[i].ort);
		fprintf(fp, "|%s| ", Ppersadr[i].plz);
		fprintf(fp, "|%d|<<", Ppersadr[i].sta_id);

		fprintf(fp, "%s", _P_EOL_);
	}
	fprintf(fp, "%s", _P_EOL_);
}

/*SF**********************************************************
 * Function:
 * Return:
 *************************************************************/
static void put_kontingent(KONTINGENT *Pkontingent, int row_cnt) {
	int i;

	fprintf(fp, "KONTINGENTE:%s", _P_EOL_);
	fprintf(fp, "==========%s", _P_EOL_);
	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, "|%d| ", Pkontingent[i].kont_id);
		fprintf(fp, "|%d| ", Pkontingent[i].bez_id);
		fprintf(fp, "|%d| ", Pkontingent[i].hostkont_id);
		fprintf(fp, "|%d| ", Pkontingent[i].kunden_id);
		fprintf(fp, "|%d| ", Pkontingent[i].opt_dat);
		fprintf(fp, "|%s| ", Pkontingent[i].ref);
		fprintf(fp, "|%d| ", Pkontingent[i].sai_id);
		fprintf(fp, "|%d|<<", Pkontingent[i].textid);

		fprintf(fp, "%s", _P_EOL_);
	}
	fprintf(fp, "%s", _P_EOL_);
}

/*SF**********************************************************
 * Function:
 * Return:
 *************************************************************/
static void put_kommission(KOMMISSION *Pkommission, int row_cnt) {
	int i;

	fprintf(fp, "KOMMISSION:%s", _P_EOL_);
	fprintf(fp, "==========%s", _P_EOL_);
	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, "|%d| ", Pkommission[i].komm_id);
		fprintf(fp, "|%d| ", Pkommission[i].bez_id);
		fprintf(fp, "|%d| ", Pkommission[i].satz_art);
		fprintf(fp, "|%f| ", Pkommission[i].satz);
		fprintf(fp, "|%d| ", Pkommission[i].komm_typ);
		fprintf(fp, "|%d| ", Pkommission[i].kbst);
		fprintf(fp, "|%d| ", Pkommission[i].kar_id);
		fprintf(fp, "|%d| ", Pkommission[i].dltt_id);
		fprintf(fp, "|%d| ", Pkommission[i].kat_id);
		fprintf(fp, "|%d| ", Pkommission[i].rkr_id);
		fprintf(fp, "|%d| ", Pkommission[i].dla_id);
		fprintf(fp, "|%d| ", Pkommission[i].dl_id);
		fprintf(fp, "|%d| ", Pkommission[i].dl_vondat);
		fprintf(fp, "|%d| ", Pkommission[i].dl_bisdat);
		fprintf(fp, "|%d| ", Pkommission[i].kont_id);
		fprintf(fp, "|%d| ", Pkommission[i].bid);
		fprintf(fp, "|%d| ", Pkommission[i].history);
		fprintf(fp, "|%d| ", Pkommission[i].sai_id);
		fprintf(fp, "|%d|<<", Pkommission[i].textid);

		fprintf(fp, "%s", _P_EOL_);
	}
	fprintf(fp, "%s", _P_EOL_);
}

/*SF**********************************************************
 * Function:
 * Return:
 *************************************************************/
static void put_preis(PREIS *Ppreis, int row_cnt) {
	int i;

	fprintf(fp, "PREIS:%s", _P_EOL_);
	fprintf(fp, "==========%s", _P_EOL_);
	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, "|%d| ", Ppreis[i].pre_id);
		fprintf(fp, "|%f| ", Ppreis[i].apr);
		fprintf(fp, "|%f| ", Ppreis[i].epr);
		fprintf(fp, "|%f| ", Ppreis[i].vpr);
		fprintf(fp, "|%d| ", Ppreis[i].glt);
		fprintf(fp, "|%d| ", Ppreis[i].whr_id);
		fprintf(fp, "|%d| ", Ppreis[i].kbst);
		fprintf(fp, "|%d| ", Ppreis[i].kar_id);
		fprintf(fp, "|%d| ", Ppreis[i].dltt_id);
		fprintf(fp, "|%d| ", Ppreis[i].kat_id);
		fprintf(fp, "|%d| ", Ppreis[i].rkr_id);
		fprintf(fp, "|%d| ", Ppreis[i].dla_id);
		fprintf(fp, "|%d| ", Ppreis[i].dl_id);
		fprintf(fp, "|%d| ", Ppreis[i].dl_vondat);
		fprintf(fp, "|%d| ", Ppreis[i].dl_bisdat);
		fprintf(fp, "|%d| ", Ppreis[i].kont_id);
		fprintf(fp, "|%d| ", Ppreis[i].sta_id);
		fprintf(fp, "|%d| ", Ppreis[i].textid);
		fprintf(fp, "|%d| ", Ppreis[i].history);
		fprintf(fp, "|%d|<<", Ppreis[i].sai_id);

		fprintf(fp, "%s", _P_EOL_);
	}
	fprintf(fp, "%s", _P_EOL_);
}

/*SF**********************************************************
 * Function:
 * Return:
 *************************************************************/
static void put_kapa(KAPA *Pkapa, int row_cnt) {
	int i;

	fprintf(fp, "KAPA:%s", _P_EOL_);
	fprintf(fp, "==========%s", _P_EOL_);
	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, "|%d| ", Pkapa[i].kat_id);
		fprintf(fp, "|%d| ", Pkapa[i].katbez_id);
		fprintf(fp, "|%d| ", Pkapa[i].tdl_id);
		fprintf(fp, "|%d| ", Pkapa[i].tdlbez_id);
		fprintf(fp, "|%d| ", Pkapa[i].pre_id);
		fprintf(fp, "|%d| ", Pkapa[i].anz);
		fprintf(fp, "|%d| ", Pkapa[i].busy);
		fprintf(fp, "|%f|<<", Pkapa[i].vpr);

		fprintf(fp, "%s", _P_EOL_);
	}
	fprintf(fp, "%s", _P_EOL_);
}

/*SF**********************************************************
 * Function:
 * Return:
 *************************************************************/
static void put_sta_view(STA_VIEW *Psta_view, int row_cnt) {
	int i;

	fprintf(fp, "STA VIEW:%s", _P_EOL_);
	fprintf(fp, "==========%s", _P_EOL_);
	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, "|%d| ", Psta_view[i].sta_id);
		fprintf(fp, "|%s| ", Psta_view[i].abk);
		fprintf(fp, "|%s| ", Psta_view[i].sta);
		fprintf(fp, "|%s| ", Psta_view[i].bez);
		fprintf(fp, "|%d| ", Psta_view[i].s_id);
		fprintf(fp, "|%d| ", Psta_view[i].kond);
		fprintf(fp, "|%d|<<", Psta_view[i].typ);


		fprintf(fp, "%s", _P_EOL_);
	}
	fprintf(fp, "%s", _P_EOL_);
}

/*SF**********************************************************
 * Function:
 * Return:
 *************************************************************/
static void put_land_view(LAND_VIEW *Pland_view, int row_cnt) {
	int i;

	fprintf(fp, "LAND VIEW:%s", _P_EOL_);
	fprintf(fp, "==========%s", _P_EOL_);
	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, "|%d| ", Pland_view[i].land_id);
		fprintf(fp, "|%s| ", Pland_view[i].bez);
		fprintf(fp, "|%d| ", Pland_view[i].s_id);
		fprintf(fp, "|%s| ", Pland_view[i].krzl);
		fprintf(fp, "|%d| ", Pland_view[i].haupt_ort);
		fprintf(fp, "|%d| ", Pland_view[i].haupt_spr);
		fprintf(fp, "|%d| ", Pland_view[i].haupt_whr);
		fprintf(fp, "|%d| ", Pland_view[i].textid);
		fprintf(fp, "|%f|<<", Pland_view[i].vat);

		fprintf(fp, "%s", _P_EOL_);
	}
	fprintf(fp, "%s", _P_EOL_);
}

/*SF**********************************************************
 * Function:
 * Return:
 *************************************************************/
static void put_kun_view(KUN_VIEW *Pkun_view, int row_cnt) {
	int i;

	fprintf(fp, "PERSADR:%s", _P_EOL_);
	fprintf(fp, "==========%s", _P_EOL_);
	fprintf(fp, "KUN_VIEW:\n");
	fprintf(fp, "=========\n");
	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, "|%d| ", Pkun_view[i].kun_id);
		fprintf(fp, "|%s| ", Pkun_view[i].name);
		fprintf(fp, "|%s| ", Pkun_view[i].ort);
		fprintf(fp, "|%d| ", Pkun_view[i].s_id);
		fprintf(fp, "|%d| ", Pkun_view[i].sta_id);
		fprintf(fp, "|%d| ", Pkun_view[i].textid);
		fprintf(fp, "|%s| ", Pkun_view[i].kant);
		fprintf(fp, "|%s| ", Pkun_view[i].tel);
		fprintf(fp, "|%s| ", Pkun_view[i].fax);
		fprintf(fp, "|%s| ", Pkun_view[i].tlx);
		fprintf(fp, "|%s| ", Pkun_view[i].konto);
		fprintf(fp, "|%d| ", Pkun_view[i].leiter);
		fprintf(fp, "|%s| ", Pkun_view[i].attr1);
		fprintf(fp, "|%s| ", Pkun_view[i].attr2);
		fprintf(fp, "|%d| ", Pkun_view[i].k_typ_id);
		fprintf(fp, "|%d| ", Pkun_view[i].land_id);
		fprintf(fp, "|%d|<<", Pkun_view[i].whr_id);

		fprintf(fp, "%s", _P_EOL_);
	}
	fprintf(fp, "%s", _P_EOL_);
}

/*SF**********************************************************
 * Function:
 * Return:
 *************************************************************/
static void put_mpv_kapa(MPV_KAPA *Pmpv_kapa, int row_cnt) {
	int i;

	fprintf(fp, "MPV KAPA:%s", _P_EOL_);
	fprintf(fp, "==========%s", _P_EOL_);
	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, "|%d| ", Pmpv_kapa[i].kat_id);
		fprintf(fp, "|%s| ", Pmpv_kapa[i].katbez);
		fprintf(fp, "|%d| ", Pmpv_kapa[i].kat_s_id);
		fprintf(fp, "|%d| ", Pmpv_kapa[i].tdl_id);
		fprintf(fp, "|%s| ", Pmpv_kapa[i].tdlbez);
		fprintf(fp, "|%d| ", Pmpv_kapa[i].tdl_s_id);
		fprintf(fp, "|%d| ", Pmpv_kapa[i].pre_id);
		fprintf(fp, "|%d| ", Pmpv_kapa[i].anz);
		fprintf(fp, "|%d| ", Pmpv_kapa[i].busy);
		fprintf(fp, "|%f|<<", Pmpv_kapa[i].vpr);

		fprintf(fp, "%s", _P_EOL_);
	}
	fprintf(fp, "%s", _P_EOL_);
}

/*SF**********************************************************
 * Function:
 * Return:
 *************************************************************/
static void put_mpv_dlnadr(MPV_DLNADR *Pmpv_dlnadr, int row_cnt) {
	int i;

	fprintf(fp, "MPV DLNADR:%s", _P_EOL_);
	fprintf(fp, "==========%s", _P_EOL_);
	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, "|%d| ", Pmpv_dlnadr[i].pers_id);
		fprintf(fp, "|%s| ", Pmpv_dlnadr[i].ans);
		fprintf(fp, "|%s| ", Pmpv_dlnadr[i].name);
		fprintf(fp, "|%s| ", Pmpv_dlnadr[i].vor);
		fprintf(fp, "|%s| ", Pmpv_dlnadr[i].adr1);
		fprintf(fp, "|%s| ", Pmpv_dlnadr[i].adr2);
		fprintf(fp, "|%s| ", Pmpv_dlnadr[i].adr3);
		fprintf(fp, "|%s| ", Pmpv_dlnadr[i].plz);
		fprintf(fp, "|%s| ", Pmpv_dlnadr[i].ort);
		fprintf(fp, "|%d| ", Pmpv_dlnadr[i].land_id);
		fprintf(fp, "|%d|<<", Pmpv_dlnadr[i].sta_id);

		fprintf(fp, "%s", _P_EOL_);
	}
	fprintf(fp, "%s", _P_EOL_);
}

/*SF**********************************************************
 * Function:
 * Return:
 *************************************************************/
static void put_mpv_kunadr(MPV_KUNADR *Pmpv_kunadr, int row_cnt) {
	int i;

	fprintf(fp, "MPV KUNADR:%s", _P_EOL_);
	fprintf(fp, "==========%s", _P_EOL_);
	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, "|%d| ", Pmpv_kunadr[i].pers_id);
		fprintf(fp, "|%s| ", Pmpv_kunadr[i].ans);
		fprintf(fp, "|%s| ", Pmpv_kunadr[i].name);
		fprintf(fp, "|%s| ", Pmpv_kunadr[i].adr1);
		fprintf(fp, "|%s| ", Pmpv_kunadr[i].adr2);
		fprintf(fp, "|%s| ", Pmpv_kunadr[i].adr3);
		fprintf(fp, "|%s| ", Pmpv_kunadr[i].plz);
		fprintf(fp, "|%s| ", Pmpv_kunadr[i].ort);
		fprintf(fp, "|%s| ", Pmpv_kunadr[i].kant);
		fprintf(fp, "|%d| ", Pmpv_kunadr[i].land_id);
		fprintf(fp, "|%d| ", Pmpv_kunadr[i].sta_id);
		fprintf(fp, "|%d| ", Pmpv_kunadr[i].k_typ_id);
		fprintf(fp, "|%s| ", Pmpv_kunadr[i].tel);
		fprintf(fp, "|%s|<<", Pmpv_kunadr[i].fax);

		fprintf(fp, "%s", _P_EOL_);
	}
	fprintf(fp, "%s", _P_EOL_);
}

/*SF**********************************************************
 * Function:
 * Return:
 *************************************************************/
static void put_status_werte(STATUS_WERTE *Pstatus_werte, int row_cnt) {
	int i;

	fprintf(fp, "STATUS WERTE:%s", _P_EOL_);
	fprintf(fp, "==========%s", _P_EOL_);
	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, "|%d| ", Pstatus_werte[i].sta_id);
		fprintf(fp, "|%s| ", Pstatus_werte[i].abk);
		fprintf(fp, "|%s| ", Pstatus_werte[i].sta);
		fprintf(fp, "|%d| ", Pstatus_werte[i].bez_id);
		fprintf(fp, "|%f| ", Pstatus_werte[i].kond);
		fprintf(fp, "|%d|<<", Pstatus_werte[i].typ);

		fprintf(fp, "%s", _P_EOL_);
		}
	fprintf(fp, "%s", _P_EOL_);
}

/*SF**********************************************************
 * Function:
 * Return:
 *************************************************************/
static void put_kollektiv(KOLLEKTIV *Pkol, int row_cnt) {
	int i;

	fprintf(fp, "KOLLEKTIV:%s", _P_EOL_);
	fprintf(fp, "==========%s", _P_EOL_);
	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, "|%d| ", Pkol[i].k_id);
		fprintf(fp, "|%d| ", Pkol[i].k_typ_id);
		fprintf(fp, "|%s| ", Pkol[i].name);
		fprintf(fp, "|%d| ", Pkol[i].kbst);
		fprintf(fp, "|%s| ", Pkol[i].ref);
		fprintf(fp, "|%d| ", Pkol[i].k_sta);
		fprintf(fp, "|%d| ", Pkol[i].hauptpers);
		fprintf(fp, "|%d| ", Pkol[i].kid);
		fprintf(fp, "|%d|<<", Pkol[i].textid);

		fprintf(fp, "%s", _P_EOL_);
	}
	fprintf(fp, "%s", _P_EOL_);
}
