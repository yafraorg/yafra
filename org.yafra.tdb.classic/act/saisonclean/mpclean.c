/*D***********************************************************
 * program:      MAIN mpclean
 * description:  complete standalone maintenance action
 *
 * arguments:    standard arguments
 *               -s  must   action typ
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/

/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/saisonclean/mpclean.c,v 1.2 2008-11-02 19:55:52 mwn Exp $";

#include "version.h"

/* MarcoPolo API includes */
#include <mpact.h>

/* Include or define globals */
#include <mpvarlib.h>
#include <mpvarapi.h>
#include <mpvaract.h>

#define PINTEGER "%11d"
#define PDOUBLE  "%24.15f"

#ifdef ps_win
#define MPF_KAPA           "\\temp\\mp_kapa.dat"
#define MPF_MP_ARRKOM      "\\temp\\mp_arrkom.dat"
#define MPF_PREIS          "\\temp\\mp_preis.dat"
#define MPF_RESERVATION    "\\temp\\mp_reservation.dat"
#define MPF_KOMMISSION     "\\temp\\mp_kommission.dat"
#define MPF_KOMM_DETAIL    "\\temp\\mp_komm_detail.dat"
#define MPF_AKT_DETAIL     "\\temp\\mp_akt_detail.dat"
#define MPF_BUCHUNG        "\\temp\\mp_buchung.dat"
#define MPF_BCH_DLN        "\\temp\\mp_bch_dln.dat"
#define MPF_KONTINGENT     "\\temp\\mp_kontingent.dat"
#define MPF_KONT_DETAIL    "\\temp\\mp_kont_detail.dat"
#define MPF_HOST_KONT      "\\temp\\mp_host_kont.dat"
#define MPF_ARRANGEMENT    "\\temp\\mp_arrangement.dat"
#define MPF_ARR_DLG        "\\temp\\mp_arr_dlg.dat"
#define MPF_PROGRAMM       "\\temp\\mp_programm.dat"
#define MPF_DIENSTLEISTUNG "\\temp\\mp_dienstleistung.dat"
#define MPF_DLG_DLG        "\\temp\\mp_dlg_dlg.dat"
#define MPF_DLG_PARTS      "\\temp\\mp_dlg_parts.dat"
#define MPF_SAISON         "\\temp\\mp_saison.dat"
#define MPF_TEXTE          "\\temp\\mp_texte.dat"
#define MPF_BEZEICHNUNG    "\\temp\\mp_bezeichnung.dat"
#define MPF_SQLLOAD        "\\temp\\mp_sqlload.bat"
#else
#define MPF_KAPA           "/tmp/mp_kapa.dat"
#define MPF_MP_ARRKOM      "/tmp/mp_arrkom.dat"
#define MPF_PREIS          "/tmp/mp_preis.dat"
#define MPF_RESERVATION    "/tmp/mp_reservation.dat"
#define MPF_KOMMISSION     "/tmp/mp_kommission.dat"
#define MPF_KOMM_DETAIL    "/tmp/mp_komm_detail.dat"
#define MPF_AKT_DETAIL     "/tmp/mp_akt_detail.dat"
#define MPF_BUCHUNG        "/tmp/mp_buchung.dat"
#define MPF_BCH_DLN        "/tmp/mp_bch_dln.dat"
#define MPF_KONTINGENT     "/tmp/mp_kontingent.dat"
#define MPF_KONT_DETAIL    "/tmp/mp_kont_detail.dat"
#define MPF_HOST_KONT      "/tmp/mp_host_kont.dat"
#define MPF_ARRANGEMENT    "/tmp/mp_arrangement.dat"
#define MPF_ARR_DLG        "/tmp/mp_arr_dlg.dat"
#define MPF_PROGRAMM       "/tmp/mp_programm.dat"
#define MPF_DIENSTLEISTUNG "/tmp/mp_dienstleistung.dat"
#define MPF_DLG_DLG        "/tmp/mp_dlg_dlg.dat"
#define MPF_DLG_PARTS      "/tmp/mp_dlg_parts.dat"
#define MPF_SAISON         "/tmp/mp_saison.dat"
#define MPF_TEXTE          "/tmp/mp_texte.dat"
#define MPF_BEZEICHNUNG    "/tmp/mp_bezeichnung.dat"
#define MPF_SQLLOAD        "/tmp/mp_sqlload.bat"
#endif

#ifdef TDBMYSQL
#define _SELECT_KAPA "SELECT * FROM TDBADMIN.KAPA;"
#define _DELETE_KAPA "DELETE TDBADMIN.KAPA;"
#define _SELECT_MP_ARRKOM "SELECT * FROM TDBADMIN.MP_ARRKOM;"
#define _DELETE_MP_ARRKOM "DELETE TDBADMIN.MP_ARRKOM;"
#define _SELECT_PREIS "SELECT * FROM TDBADMIN.PREIS WHERE SAI_ID = %d;"
#define _DELETE_PREIS "DELETE TDBADMIN.PREIS WHERE SAI_ID = %d;"
#define _SELECT_RESERVATION "SELECT * FROM TDBADMIN.RESERVATION WHERE BID = %d;"
#define _DELETE_RESERVATION "DELETE TDBADMIN.RESERVATION WHERE BID = %d;"
#define _SELECT_KOMMISSION "SELECT * FROM TDBADMIN.KOMMISSION WHERE SAI_ID = %d;"
#define _DELETE_KOMMISSION "DELETE TDBADMIN.KOMMISSION WHERE SAI_ID = %d;"
#define _SELECT_KOMM_DETAIL "SELECT * FROM TDBADMIN.KOMM_DETAIL WHERE KOMM_ID = %d;"
#define _DELETE_KOMM_DETAIL "DELETE TDBADMIN.KOMM_DETAIL WHERE KOMM_ID = %d;"
#define _SELECT_AKT_DETAIL "SELECT * FROM TDBADMIN.AKT_DETAIL WHERE BID = %d;"
#define _DELETE_AKT_DETAIL "DELETE TDBADMIN.AKT_DETAIL WHERE BID = %d;"
#define _SELECT_BUCHUNG "SELECT * FROM TDBADMIN.BUCHUNG WHERE SAI_ID = %d;"
#define _DELETE_BUCHUNG "DELETE TDBADMIN.BUCHUNG WHERE SAI_ID = %d;"
#define _SELECT_BCH_DLN "SELECT * FROM TDBADMIN.BCH_DLN WHERE BID = %d;"
#define _DELETE_BCH_DLN "DELETE TDBADMIN.BCH_DLN WHERE BID = %d;"
#define _SELECT_KONTINGENT "SELECT * FROM TDBADMIN.KONTINGENT WHERE SAI_ID = %d;"
#define _DELETE_KONTINGENT "DELETE TDBADMIN.KONTINGENT WHERE SAI_ID = %d;"
#define _SELECT_KONT_DETAIL_KONT "SELECT * FROM TDBADMIN.KONT_DETAIL \
                                  WHERE KONT_ID = %d;"
#define _DELETE_KONT_DETAIL_KONT "DELETE TDBADMIN.KONT_DETAIL WHERE KONT_ID = %d;"
#define _SELECT_KONT_DETAIL_HOST "SELECT * FROM TDBADMIN.KONT_DETAIL \
                                  WHERE HOSTKONT_ID = %d;"
#define _DELETE_KONT_DETAIL_HOST "DELETE TDBADMIN.KONT_DETAIL \
                                  WHERE HOSTKONT_ID = %d;"
#define _SELECT_HOST_KONT "SELECT * FROM TDBADMIN.HOST_KONT WHERE SAI_ID = %d;"
#define _DELETE_HOST_KONT "DELETE TDBADMIN.HOST_KONT WHERE SAI_ID = %d;"
#define _SELECT_ARRANGEMENT "SELECT * FROM TDBADMIN.ARRANGEMENT WHERE SAI_ID = %d;"
#define _DELETE_ARRANGEMENT "DELETE TDBADMIN.ARRANGEMENT WHERE SAI_ID = %d;"
#define _SELECT_ARR_DLG "SELECT * FROM TDBADMIN.ARR_DLG WHERE ARR_ID = %d;"
#define _DELETE_ARR_DLG "DELETE TDBADMIN.ARR_DLG WHERE ARR_ID = %d;"
#define _SELECT_PROGRAMM "SELECT * FROM TDBADMIN.PROGRAMM WHERE SAI_ID = %d;"
#define _DELETE_PROGRAMM "DELETE TDBADMIN.PROGRAMM WHERE SAI_ID = %d;"
#define _SELECT_DIENSTLEISTUNG "SELECT * FROM TDBADMIN.DIENSTLEISTUNG \
                                WHERE SAI_ID = %d;"
#define _DELETE_DIENSTLEISTUNG "DELETE TDBADMIN.DIENSTLEISTUNG WHERE SAI_ID = %d;"
#define _SELECT_DLG_DLG "SELECT * FROM TDBADMIN.DLG_DLG WHERE DLG_ID = %d;"
#define _DELETE_DLG_DLG "DELETE TDBADMIN.DLG_DLG WHERE DLG_ID = %d;"
#define _SELECT_DLG_PARTS "SELECT * FROM TDBADMIN.DLG_PARTS WHERE SAI_ID = %d;"
#define _DELETE_DLG_PARTS "DELETE TDBADMIN.DLG_PARTS WHERE SAI_ID = %d;"
#define _SELECT_SAISON "SELECT * FROM TDBADMIN.SAISON WHERE SAI_ID = %d;"
#define _DELETE_SAISON "DELETE TDBADMIN.SAISON WHERE SAI_ID = %d;"
#define _SELECT_TEXTE "SELECT * FROM TDBADMIN.TEXTE WHERE TEXTID = %d \
                       AND TYP = %d;"
#define _DELETE_TEXTE "DELETE TDBADMIN.TEXTE WHERE TEXTID = %d \
                             AND TYP = %d;"
#define _SELECT_BEZEICHNUNG "SELECT * FROM TDBADMIN.BEZEICHNUNG \
                             WHERE BEZ_ID = %d AND TYP = %d;"
#define _DELETE_BEZEICHNUNG "DELETE TDBADMIN.BEZEICHNUNG WHERE BEZ_ID = %d \
                             AND TYP = %d;"
#define _SELECT_KOMMISSION_TEXTE "SELECT * FROM TDBADMIN.KOMMISSION \
                                  WHERE SAI_ID = %d ORDER BY TEXTID;"
#define _SELECT_KOMMISSION_BEZ "SELECT * FROM TDBADMIN.KOMMISSION \
                                WHERE SAI_ID = %d ORDER BY BEZ_ID;"
#endif

#ifdef MPDBODBC
#define _SELECT_KAPA "SELECT * FROM TDBADMIN.KAPA;"
#define _DELETE_KAPA "DELETE TDBADMIN.KAPA;"
#define _SELECT_MP_ARRKOM "SELECT * FROM TDBADMIN.MP_ARRKOM;"
#define _DELETE_MP_ARRKOM "DELETE TDBADMIN.MP_ARRKOM;"
#define _SELECT_PREIS "SELECT * FROM TDBADMIN.PREIS WHERE SAI_ID = %d;"
#define _DELETE_PREIS "DELETE TDBADMIN.PREIS WHERE SAI_ID = %d;"
#define _SELECT_RESERVATION "SELECT * FROM TDBADMIN.RESERVATION WHERE BID = %d;"
#define _DELETE_RESERVATION "DELETE TDBADMIN.RESERVATION WHERE BID = %d;"
#define _SELECT_KOMMISSION "SELECT * FROM TDBADMIN.KOMMISSION WHERE SAI_ID = %d;"
#define _DELETE_KOMMISSION "DELETE TDBADMIN.KOMMISSION WHERE SAI_ID = %d;"
#define _SELECT_KOMM_DETAIL "SELECT * FROM TDBADMIN.KOMM_DETAIL WHERE KOMM_ID = %d;"
#define _DELETE_KOMM_DETAIL "DELETE TDBADMIN.KOMM_DETAIL WHERE KOMM_ID = %d;"
#define _SELECT_AKT_DETAIL "SELECT * FROM TDBADMIN.AKT_DETAIL WHERE BID = %d;"
#define _DELETE_AKT_DETAIL "DELETE TDBADMIN.AKT_DETAIL WHERE BID = %d;"
#define _SELECT_BUCHUNG "SELECT * FROM TDBADMIN.BUCHUNG WHERE SAI_ID = %d;"
#define _DELETE_BUCHUNG "DELETE TDBADMIN.BUCHUNG WHERE SAI_ID = %d;"
#define _SELECT_BCH_DLN "SELECT * FROM TDBADMIN.BCH_DLN WHERE BID = %d;"
#define _DELETE_BCH_DLN "DELETE TDBADMIN.BCH_DLN WHERE BID = %d;"
#define _SELECT_KONTINGENT "SELECT * FROM TDBADMIN.KONTINGENT WHERE SAI_ID = %d;"
#define _DELETE_KONTINGENT "DELETE TDBADMIN.KONTINGENT WHERE SAI_ID = %d;"
#define _SELECT_KONT_DETAIL_KONT "SELECT * FROM TDBADMIN.KONT_DETAIL \
                                  WHERE KONT_ID = %d;"
#define _DELETE_KONT_DETAIL_KONT "DELETE TDBADMIN.KONT_DETAIL WHERE KONT_ID = %d;"
#define _SELECT_KONT_DETAIL_HOST "SELECT * FROM TDBADMIN.KONT_DETAIL \
                                  WHERE HOSTKONT_ID = %d;"
#define _DELETE_KONT_DETAIL_HOST "DELETE TDBADMIN.KONT_DETAIL \
                                  WHERE HOSTKONT_ID = %d;"
#define _SELECT_HOST_KONT "SELECT * FROM TDBADMIN.HOST_KONT WHERE SAI_ID = %d;"
#define _DELETE_HOST_KONT "DELETE TDBADMIN.HOST_KONT WHERE SAI_ID = %d;"
#define _SELECT_ARRANGEMENT "SELECT * FROM TDBADMIN.ARRANGEMENT WHERE SAI_ID = %d;"
#define _DELETE_ARRANGEMENT "DELETE TDBADMIN.ARRANGEMENT WHERE SAI_ID = %d;"
#define _SELECT_ARR_DLG "SELECT * FROM TDBADMIN.ARR_DLG WHERE ARR_ID = %d;"
#define _DELETE_ARR_DLG "DELETE TDBADMIN.ARR_DLG WHERE ARR_ID = %d;"
#define _SELECT_PROGRAMM "SELECT * FROM TDBADMIN.PROGRAMM WHERE SAI_ID = %d;"
#define _DELETE_PROGRAMM "DELETE TDBADMIN.PROGRAMM WHERE SAI_ID = %d;"
#define _SELECT_DIENSTLEISTUNG "SELECT * FROM TDBADMIN.DIENSTLEISTUNG \
                                WHERE SAI_ID = %d;"
#define _DELETE_DIENSTLEISTUNG "DELETE TDBADMIN.DIENSTLEISTUNG WHERE SAI_ID = %d;"
#define _SELECT_DLG_DLG "SELECT * FROM TDBADMIN.DLG_DLG WHERE DLG_ID = %d;"
#define _DELETE_DLG_DLG "DELETE TDBADMIN.DLG_DLG WHERE DLG_ID = %d;"
#define _SELECT_DLG_PARTS "SELECT * FROM TDBADMIN.DLG_PARTS WHERE SAI_ID = %d;"
#define _DELETE_DLG_PARTS "DELETE TDBADMIN.DLG_PARTS WHERE SAI_ID = %d;"
#define _SELECT_SAISON "SELECT * FROM TDBADMIN.SAISON WHERE SAI_ID = %d;"
#define _DELETE_SAISON "DELETE TDBADMIN.SAISON WHERE SAI_ID = %d;"
#define _SELECT_TEXTE "SELECT * FROM TDBADMIN.TEXTE WHERE TEXTID = %d \
                       AND TYP = %d;"
#define _DELETE_TEXTE "DELETE TDBADMIN.TEXTE WHERE TEXTID = %d \
                             AND TYP = %d;"
#define _SELECT_BEZEICHNUNG "SELECT * FROM TDBADMIN.BEZEICHNUNG \
                             WHERE BEZ_ID = %d AND TYP = %d;"
#define _DELETE_BEZEICHNUNG "DELETE TDBADMIN.BEZEICHNUNG WHERE BEZ_ID = %d \
                             AND TYP = %d;"
#endif

static int MPC_argTest(int , char **, int *);
static int MPC_connectDB();
static int MPC_sqlload_script();

static int MPC_put_texte(TEXTE *, int);
static int MPC_delete_texte(int, int);
static int MPC_put_bezeichnung(BEZEICHNUNG *, int);
static int MPC_delete_bezeichnung(int, int);

static int MPC_texte_bez_kommission(KOMMISSION *, int);
static int MPC_texte_bez_kontingent(KONTINGENT *, int);
static int MPC_texte_bez_host_kont(HOST_KONT *, int);
static int MPC_texte_bez_arrangement(ARRANGEMENT *, int);
static int MPC_texte_bez_programm(PROGRAMM *, int);
static int MPC_texte_bez_dienstleistung(DIENSTLEISTUNG *, int);
static int MPC_texte_bez_dlg_parts(DLG_PART *, int);
static int MPC_texte_bez_saison(SAISON *, int);

static int MPC_kapa();
static int MPC_mp_arrkom();
static int MPC_preis(int);
static int MPC_kommission(int);
static int MPC_buchung(int);
static int MPC_kontingent(int);
static int MPC_host_kont(int);
static int MPC_arrangement(int);
static int MPC_programm(int);
static int MPC_dienstleistung(int);
static int MPC_dlg_parts(int);
static int MPC_saison(int);

static int MPC_put_kapa(KAPA *, int);
static int MPC_put_mp_arrkom(MP_ARRKOM *, int);
static int MPC_put_preis(PREIS *, int);
static int MPC_put_kommission(KOMMISSION *, int);
static int MPC_put_buchung(BUCHUNG *, int);
static int MPC_put_kontingent(KONTINGENT *, int);
static int MPC_put_host_kont(HOST_KONT *, int);
static int MPC_put_arrangement(ARRANGEMENT *, int);
static int MPC_put_programm(PROGRAMM *, int);
static int MPC_put_dienstleistung(DIENSTLEISTUNG *, int);
static int MPC_put_dlg_parts(DLG_PART *, int);
static int MPC_put_saison(SAISON *, int);

static int MPC_delete_kapa();
static int MPC_delete_mp_arrkom();
static int MPC_delete_preis(int);
static int MPC_delete_kommission(int);
static int MPC_delete_buchung(int);
static int MPC_delete_kontingent(int);
static int MPC_delete_host_kont(int);
static int MPC_delete_arrangement(int);
static int MPC_delete_programm(int);
static int MPC_delete_dienstleistung(int);
static int MPC_delete_dlg_parts(int);
static int MPC_delete_saison(int);

static int MPC_komm_detail(KOMMISSION *, int);
static int MPC_delete_komm_detail(int);

static int MPC_bch_dln(BUCHUNG *, int);
static int MPC_delete_bch_dln(int);

static int MPC_kont_detail_kont(KONTINGENT *, int);
static int MPC_delete_kont_detail_kont(int);

static int MPC_kont_detail_host(HOST_KONT *, int);
static int MPC_delete_kont_detail_host(int);

static int MPC_arr_dlg(ARRANGEMENT *, int);
static int MPC_delete_arr_dlg(int);

static int MPC_dlg_dlg(DIENSTLEISTUNG *, int);
static int MPC_delete_dlg_dlg(int);

static int MPC_reservation(BUCHUNG *, int);
static int MPC_delete_reservation(int);

static int MPC_akt_detail(BUCHUNG *, int);
static int MPC_delete_akt_detail(int);

/*F--------------------------------------------------------------------------
 *  Function:	main(int argc, char *argv[])
 *             Loescht eine Saison. Mit dem Argument '-s' kann die Saison id
 *             mit gegeben werden. Dabei wird bevor records auf den ent-
 *             sprechenden Tabellen geloescht werden, diese in ein Ascii-File
 *             geschrieben. Dieser Output sollte in Notfaellen wieder mit
 *             SQL-Loader wieder eingespielt werden koennen.
 *
 *  In:			-argc, argv as action was invoked
 *  out:			-
 *  Return:		-completion code 
 *---------------------------------------------------------------------------
 */
int main(int argc, char *argv[])
{
	int	status;
	int	sai_id;
	int	intretval = (int)_INTEGER;

	/* init language handling */
	intretval       = -1;

	/* Init */
	DebugFlag  = (int)FALSE;
	FatalError = (int)FALSE;
	reinitflag = (int)FALSE;
	targetsta  = (int)_UNDEF;
	exectyp    = _AKT_MAN;

	/* ------ Argumenten Testen ------ */
	status = MPC_argTest(argc, argv, &sai_id);
	if (status != (int)MPOK)
		exit(status);

	/* ------ DB connect ------ */
	status = MPC_connectDB();
	if (status != (int)MPOK)
		exit(status);

	/* ------ load script ------ */
	status = MPC_sqlload_script();

	/* ------ KAPA ------ */
	if ( status == (int)MPOK )
		status = MPC_kapa(sai_id);

	/* ------ MP_ARRKOM ------ */
	if ( status == (int)MPOK )
		status = MPC_mp_arrkom(sai_id);

	/* ------ PREIS ------ */
	if ( status == (int)MPOK )
		status = MPC_preis(sai_id);

	/* ------ KOMMISSION ------ */
	if ( status == (int)MPOK )
		status = MPC_kommission(sai_id);

	/* ------ BUCHUNG ------ */
	if ( status == (int)MPOK )
		status = MPC_buchung(sai_id);

	/* ------ KONTINGENT ------ */
	if ( status == (int)MPOK )
		status = MPC_kontingent(sai_id);

	/* ------ HOST_KONT ------ */
	if ( status == (int)MPOK )
		status = MPC_host_kont(sai_id);

	/* ------ ARRANGEMENT ------ */
	if ( status == (int)MPOK )
		status = MPC_arrangement(sai_id);

	/* ------ PROGRAMM ------ */
	if ( status == (int)MPOK )
		status = MPC_programm(sai_id);

	/* ------ DIENSTLEISTUNG ------ */
	if ( status == (int)MPOK )
		status = MPC_dienstleistung(sai_id);

	/* ------ DLG_PARTS ------ */
	if ( status == (int)MPOK )
		status = MPC_dlg_parts(sai_id);

	/* ------ SAISON ------ */
	if ( status == (int)MPOK )
		status = MPC_saison(sai_id);

	/* ------ DB close ------ */
	MPAPIdb_release();
	(void)printf("\n\nDB closed\n");

	return 0;
}


/*SF**********************************************************
 * Function: MPC_argTest
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_argTest(int argc, char **argv, int *sai_id)
{
	if (argc = 3) {
		if ((strcmp(argv[1], "-s")) == 0 && strlen(argv[2]) > 0) {
			*sai_id = atoi(argv[2]);
		} else {
			fprintf (stderr, "\nusage: mpclean -s saison_id \n\n");
			return (int)MPERROR;
		}
	} else {
		fprintf (stderr, "\nusage: mpclean -s saison_id \n\n");
		return (int)MPERROR;
	}
	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_connectDB
 * Return:   status
 *************************************************************/
static int MPC_connectDB()
{
	int	status=(int)MPOK;

#ifdef MPDBHPSQL
	status = MPAPIdb_connect("/piso/mapo/demodb/DEMO", "mw", "mapo");
#endif
#ifdef MPDBINGRES
	status = MPAPIdb_connect("marco", "mw", "mapo");
#endif
#ifdef MPDBORACLE
	status = MPAPIdb_connect("mapo", "root", "root");
#endif
#ifdef MPDBODBC
	status = MPAPIdb_connect("mapo", "mw", "magnol");
#endif
#ifdef MPDBMSQL
	status = MPAPIdb_connect("mapo", "mw", "mapo");
#endif
#ifdef MPDBDUMMY
	status = MPAPIdb_connect("mapo", "mw", "mapo");
#endif

	if (status != (int)MPOK)
		(void)fprintf(stderr, "\nError opening the DB\n");
	else
		(void)printf("\n\nDB opened\n");

	return status ;
}




/*SF**********************************************************
 * Function: MPC_sqlload_script
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_sqlload_script()
{
	FILE	*fp;
	int	status=(int)MPOK;

	if ((fp = fopen(MPF_SQLLOAD, _P_WRITE_)) == NULL) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
		                MPF_SQLLOAD);
		return (int)MPERROR;
	}

	fprintf(fp, "sqlload root/root, saison.ctl, saison.log, saison.bad, mp_saison.dat, saison.dis\n");

	fprintf(fp, "sqlload root/root, dlg_parts.ctl, dlg_parts.log, dlg_parts.bad, mp_dlg_parts.dat, dlg_parts.dis\n");

	fprintf(fp, "sqlload root/root, dienstleistung.ctl, dienstleistung.log, dienstleistung.bad, mp_dienstleistung.dat, dienstleistung.dis\n");

	fprintf(fp, "sqlload root/root, dlg_dlg.ctl, dlg_dlg.log, dlg_dlg.bad, mp_dlg_dlg.dat, dlg_dlg.dis\n");

	fprintf(fp, "sqlload root/root, programm.ctl, programm.log, programm.bad, mp_programm.dat, programm.dis\n");

	fprintf(fp, "sqlload root/root, arrangement.ctl, arrangement.log, arrangement.bad, mp_arrangement.dat, arrangement.dis\n");

	fprintf(fp, "sqlload root/root, arr_dlg.ctl, arr_dlg.log, arr_dlg.bad, mp_arr_dlg.dat, arr_dlg.dis\n");

	fprintf(fp, "sqlload root/root, host_kont.ctl, host_kont.log, host_kont.bad, mp_host_kont.dat, host_kont.dis\n");

	fprintf(fp, "sqlload root/root, kontingent.ctl, kontingent.log, kontingent.bad, mp_kontingent.dat, kontingent.dis\n");

	fprintf(fp, "sqlload root/root, kont_detail.ctl, kont_detail.log, kont_detail.bad, mp_kont_detail.dat, kont_detail.dis\n");

	fprintf(fp, "sqlload root/root, buchung.ctl, buchung.log, buchung.bad, mp_buchung.dat, buchung.dis\n");

	fprintf(fp, "sqlload root/root, bch_dln.ctl, bch_dln.log, bch_dln.bad, mp_bch_dln.dat, bch_dln.dis\n");

	fprintf(fp, "sqlload root/root, akt_detail.ctl, akt_detail.log, akt_detail.bad, mp_akt_detail.dat, akt_detail.dis\n");

	fprintf(fp, "sqlload root/root, kommission.ctl, kommission.log, kommission.bad, mp_kommission.dat, kommission.dis\n");

	fprintf(fp, "sqlload root/root, komm_detail.ctl, komm_detail.log, komm_detail.bad, mp_komm_detail.dat, komm_detail.dis\n");

	fprintf(fp, "sqlload root/root, reservation.ctl, reservation.log, reservation.bad, mp_reservation.dat, reservation.dis\n");

	fprintf(fp, "sqlload root/root, preis.ctl, preis.log, preis.bad, mp_preis.dat, preis.dis\n");

	fprintf(fp, "sqlload root/root, mp_arrkom.ctl, mp_arrkom.log, mp_arrkom.bad, mp_arrkom.dat, mp_arrkom.dis\n");

	fprintf(fp, "sqlload root/root, kapa.ctl, kapa.log, kapa.bad, mp_kapa.dat, kapa.dis\n");

	fprintf(fp, "sqlload root/root, bezeichnung.ctl, bezeichnung.log, bezeichnung.bad, mp_bezeichnung.dat, bezeichnung.dis\n");

	fprintf(fp, "sqlload root/root, texte.ctl, texte.log, texte.bad, mp_texte.dat, texte.dis\n");

	fclose(fp);

	return status;
}


/*SF**********************************************************
 * Function: MPC_put_texte
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_put_texte(TEXTE *Ptexte, int row_cnt)
{
	FILE		*fp;
	int		status=(int)MPOK;
	int		i;

	if ((fp = fopen(MPF_TEXTE, _P_APPEND_)) == NULL) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n", MPF_TEXTE);
		return (int)MPERROR;
	}

	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, PINTEGER, Ptexte[i].textid);
		fprintf(fp, PINTEGER, Ptexte[i].s_id);
		fprintf(fp, PINTEGER, Ptexte[i].textnr);
		fprintf(fp, "%-81s",  Ptexte[i].text);
		fprintf(fp, PINTEGER, Ptexte[i].typ);

		fprintf(fp, "\n");
	}
	fclose(fp);

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_put_bezeichnung
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_put_bezeichnung(BEZEICHNUNG *Pbezeichnung, int row_cnt)
{
	FILE		*fp;
	int		status=(int)MPOK;
	int		i;

	if ((fp = fopen(MPF_BEZEICHNUNG, _P_APPEND_)) == NULL) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
		                 MPF_BEZEICHNUNG);
		return (int)MPERROR;
	}

	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, PINTEGER, Pbezeichnung[i].bez_id);
		fprintf(fp, PINTEGER, Pbezeichnung[i].s_id);
		fprintf(fp, "%-31s",  Pbezeichnung[i].bez);
		fprintf(fp, PINTEGER, Pbezeichnung[i].typ);

		fprintf(fp, "\n");
	}
	fclose(fp);

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_texte
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_texte(int textid, int tableid)
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_TEXTE, textid, tableid);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle TEXTE\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete TEXTE del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_bezeichnung
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_bezeichnung(int bez_id, int tableid)
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_BEZEICHNUNG, bez_id, tableid);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle BEZEICHNUNG\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete BEZEICHNUNG del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_put_kapa
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_put_kapa(KAPA *Pkapa, int row_cnt)
{
	int  i;
	FILE *fp;

	if ((fp = fopen(MPF_KAPA, _P_WRITE_)) == NULL) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n", MPF_KAPA);
		return (int)MPERROR;
	}

	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, PINTEGER, Pkapa[i].kat_id);
		fprintf(fp, PINTEGER, Pkapa[i].katbez_id);
		fprintf(fp, PINTEGER, Pkapa[i].tdl_id);
		fprintf(fp, PINTEGER, Pkapa[i].tdlbez_id);
		fprintf(fp, PINTEGER, Pkapa[i].pre_id);
		fprintf(fp, PINTEGER, Pkapa[i].anz);
		fprintf(fp, PINTEGER, Pkapa[i].busy);
		fprintf(fp, PDOUBLE,  Pkapa[i].vpr);

		fprintf(fp, "\n");
	}
	fclose(fp);

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_put_mp_arrkom
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_put_mp_arrkom(MP_ARRKOM *Pmp_arrkom, int row_cnt)
{
	int  i;
	FILE *fp;

	if ((fp = fopen(MPF_MP_ARRKOM, _P_WRITE_)) == NULL ) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
		                MPF_MP_ARRKOM);
		return (int)MPERROR;
	}

	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, PINTEGER, Pmp_arrkom[i].arr_id);
		fprintf(fp, PINTEGER, Pmp_arrkom[i].komm_id);
		fprintf(fp, PINTEGER, Pmp_arrkom[i].komm_bezid);

		fprintf(fp, "\n");
	}
	fclose(fp);

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_put_preis
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_put_preis(PREIS *Ppreis, int row_cnt)
{
	int  i;
	FILE *fp;

	if ((fp = fopen(MPF_PREIS, _P_WRITE_)) == NULL ) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n", MPF_PREIS);
		return (int)MPERROR;
	}

	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, PINTEGER, Ppreis[i].pre_id);
		fprintf(fp, PDOUBLE,  Ppreis[i].apr);
		fprintf(fp, PDOUBLE,  Ppreis[i].epr);
		fprintf(fp, PDOUBLE,  Ppreis[i].vpr);
		fprintf(fp, PINTEGER, Ppreis[i].glt);
		fprintf(fp, PINTEGER, Ppreis[i].whr_id);
		fprintf(fp, PINTEGER, Ppreis[i].kbst);
		fprintf(fp, PINTEGER, Ppreis[i].kar_id);
		fprintf(fp, PINTEGER, Ppreis[i].dltt_id);
		fprintf(fp, PINTEGER, Ppreis[i].kat_id);
		fprintf(fp, PINTEGER, Ppreis[i].rkr_id);
		fprintf(fp, PINTEGER, Ppreis[i].dla_id);
		fprintf(fp, PINTEGER, Ppreis[i].dl_id);
		fprintf(fp, PINTEGER, Ppreis[i].dl_vondat);
		fprintf(fp, PINTEGER, Ppreis[i].dl_bisdat);
		fprintf(fp, PINTEGER, Ppreis[i].kont_id);
		fprintf(fp, PINTEGER, Ppreis[i].sta_id);
		fprintf(fp, PINTEGER, Ppreis[i].textid);
		fprintf(fp, PINTEGER, Ppreis[i].history);
		fprintf(fp, PINTEGER, Ppreis[i].sai_id);

		fprintf(fp, "\n");
	}
	fclose(fp);

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_put_kommission
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_put_kommission(KOMMISSION *Pkommission, int row_cnt)
{
	int  i;
	FILE *fp;

	if ((fp = fopen(MPF_KOMMISSION, _P_WRITE_)) == NULL ) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
		                MPF_KOMMISSION);
		return (int)MPERROR;
	}

	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, PINTEGER, Pkommission[i].komm_id);
		fprintf(fp, PINTEGER, Pkommission[i].bez_id);
		fprintf(fp, PINTEGER, Pkommission[i].satz_art);
		fprintf(fp, PDOUBLE,  Pkommission[i].satz);
		fprintf(fp, PINTEGER, Pkommission[i].komm_typ);
		fprintf(fp, PINTEGER, Pkommission[i].kbst);
		fprintf(fp, PINTEGER, Pkommission[i].kar_id);
		fprintf(fp, PINTEGER, Pkommission[i].dltt_id);
		fprintf(fp, PINTEGER, Pkommission[i].kat_id);
		fprintf(fp, PINTEGER, Pkommission[i].rkr_id);
		fprintf(fp, PINTEGER, Pkommission[i].dla_id);
		fprintf(fp, PINTEGER, Pkommission[i].dl_id);
		fprintf(fp, PINTEGER, Pkommission[i].dl_vondat);
		fprintf(fp, PINTEGER, Pkommission[i].dl_bisdat);
		fprintf(fp, PINTEGER, Pkommission[i].kont_id);
		fprintf(fp, PINTEGER, Pkommission[i].bid);
		fprintf(fp, PINTEGER, Pkommission[i].history);
		fprintf(fp, PINTEGER, Pkommission[i].sai_id);
		fprintf(fp, PINTEGER, Pkommission[i].textid);

		fprintf(fp, "\n");
	}
	fclose(fp);

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_put_buchung
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_put_buchung(BUCHUNG *Pbuchung, int row_cnt)
{
	int  i;
	FILE *fp;

	if ((fp = fopen(MPF_BUCHUNG, _P_WRITE_) ) == NULL ) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
		                MPF_BUCHUNG);
		return (int)MPERROR;
	}

	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, PINTEGER, Pbuchung[i].d_bid);
		fprintf(fp, PINTEGER, Pbuchung[i].bid);
		fprintf(fp, "%-31s",  Pbuchung[i].ref);
		fprintf(fp, PINTEGER, Pbuchung[i].arr_id);
		fprintf(fp, PINTEGER, Pbuchung[i].kid);
		fprintf(fp, "%-31s",  Pbuchung[i].sach);
		fprintf(fp, "%-9s",   Pbuchung[i].anw);
		fprintf(fp, PINTEGER, Pbuchung[i].b_dat);
		fprintf(fp, PINTEGER, Pbuchung[i].m_dat);
		fprintf(fp, PINTEGER, Pbuchung[i].opt_bst);
		fprintf(fp, PINTEGER, Pbuchung[i].opt_kid);
		fprintf(fp, PINTEGER, Pbuchung[i].sta);
		fprintf(fp, PINTEGER, Pbuchung[i].ast);
		fprintf(fp, PINTEGER, Pbuchung[i].sai_id);
		fprintf(fp, PINTEGER, Pbuchung[i].k_id);
		fprintf(fp, PINTEGER, Pbuchung[i].history);
		fprintf(fp, PINTEGER, Pbuchung[i].b_text);

		fprintf(fp, "\n");
	}
	fclose(fp);

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_put_kontingent
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_put_kontingent(KONTINGENT *Pkontingent, int row_cnt)
{
	int  i;
	FILE *fp;

	if ((fp = fopen(MPF_KONTINGENT, _P_WRITE_)) == NULL ) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
		                MPF_KONTINGENT);
		return (int)MPERROR;
	}

	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, PINTEGER, Pkontingent[i].kont_id);
		fprintf(fp, PINTEGER, Pkontingent[i].bez_id);
		fprintf(fp, PINTEGER, Pkontingent[i].hostkont_id);
		fprintf(fp, PINTEGER, Pkontingent[i].kunden_id);
		fprintf(fp, PINTEGER, Pkontingent[i].opt_dat);
		fprintf(fp, "%-31s",  Pkontingent[i].ref);
		fprintf(fp, PINTEGER, Pkontingent[i].sai_id);
		fprintf(fp, PINTEGER, Pkontingent[i].textid);

		fprintf(fp, "\n");
	}
	fclose(fp);

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_put_host_kont
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_put_host_kont(HOST_KONT *Phost_kont, int row_cnt)
{
	int  i;
	FILE *fp;

	if ((fp = fopen(MPF_HOST_KONT, _P_WRITE_)) == NULL ) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
		                MPF_HOST_KONT);
		return (int)MPERROR;
	}

	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, PINTEGER, Phost_kont[i].hostkont_id);
		fprintf(fp, PINTEGER, Phost_kont[i].bez_id);
		fprintf(fp, PINTEGER, Phost_kont[i].from_pers);
		fprintf(fp, PINTEGER, Phost_kont[i].kbst);
		fprintf(fp, PINTEGER, Phost_kont[i].dla_id);
		fprintf(fp, PINTEGER, Phost_kont[i].dl_id);
		fprintf(fp, PINTEGER, Phost_kont[i].dl_vondat);
		fprintf(fp, PINTEGER, Phost_kont[i].dl_bisdat);
		fprintf(fp, PINTEGER, Phost_kont[i].textid);
		fprintf(fp, PINTEGER, Phost_kont[i].opt_dat);
		fprintf(fp, PINTEGER, Phost_kont[i].sai_id);
		fprintf(fp, "%-31s",  Phost_kont[i].ref);
		fprintf(fp, PINTEGER, Phost_kont[i].history);

		fprintf(fp, "\n");
	}
	fclose(fp);

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_put_arrangement
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_put_arrangement(ARRANGEMENT *Parrangement, int row_cnt)
{
	int  i;
	FILE *fp;

	if ((fp = fopen(MPF_ARRANGEMENT, _P_WRITE_)) == NULL ) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
		                MPF_ARRANGEMENT);
		return (int)MPERROR;
	}

	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, PINTEGER, Parrangement[i].arr_id);
		fprintf(fp, PINTEGER, Parrangement[i].bez_id);
		fprintf(fp, PINTEGER, Parrangement[i].a_dat);
		fprintf(fp, PINTEGER, Parrangement[i].prg_id);
		fprintf(fp, PINTEGER, Parrangement[i].textid);
		fprintf(fp, PINTEGER, Parrangement[i].sai_id);

		fprintf(fp, "\n");
	}
	fclose(fp);

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_put_programm
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_put_programm(PROGRAMM *Pprogramm, int row_cnt)
{
	int  i;
	FILE *fp;

	if ((fp = fopen(MPF_PROGRAMM, _P_WRITE_)) == NULL ) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
		                MPF_PROGRAMM);
		return (int)MPERROR;
	}

	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, PINTEGER, Pprogramm[i].prg_id);
		fprintf(fp, PINTEGER, Pprogramm[i].bez_id);
		fprintf(fp, PINTEGER, Pprogramm[i].textid);
		fprintf(fp, PINTEGER, Pprogramm[i].sai_id);

		fprintf(fp, "\n");
	}
	fclose(fp);

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_put_dienstleistung
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_put_dienstleistung(DIENSTLEISTUNG *Pdienstleistung, int row_cnt)
{
	int  i;
	FILE *fp;

	if ((fp = fopen(MPF_DIENSTLEISTUNG, _P_WRITE_)) == NULL ) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
		                MPF_DIENSTLEISTUNG);
		return (int)MPERROR;
	}

	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, PINTEGER, Pdienstleistung[i].dlg_id);
		fprintf(fp, PINTEGER, Pdienstleistung[i].bez_id);
		fprintf(fp, PINTEGER, Pdienstleistung[i].textid);
		fprintf(fp, PINTEGER, Pdienstleistung[i].sai_id);
		fprintf(fp, PINTEGER, Pdienstleistung[i].a_zeit);
		fprintf(fp, PINTEGER, Pdienstleistung[i].akt_id);

		fprintf(fp, "\n");
	}
	fclose(fp);

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_put_dlg_parts
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_put_dlg_parts(DLG_PART *Pdlg_parts, int row_cnt)
{
	int  i;
	FILE *fp;

	if ((fp = fopen(MPF_DLG_PARTS, _P_WRITE_)) == NULL ) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
		                MPF_DLG_PARTS);
		return (int)MPERROR;
	}

	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, PINTEGER, Pdlg_parts[i].dl_id);
		fprintf(fp, PINTEGER, Pdlg_parts[i].h_dl_id);
		fprintf(fp, PINTEGER, Pdlg_parts[i].dla_id);
		fprintf(fp, PINTEGER, Pdlg_parts[i].bez_id);
		fprintf(fp, PINTEGER, Pdlg_parts[i].ord);
		fprintf(fp, PINTEGER, Pdlg_parts[i].a_zeit);
		fprintf(fp, PINTEGER, Pdlg_parts[i].e_zeit);
		fprintf(fp, PINTEGER, Pdlg_parts[i].res_f);
		fprintf(fp, PINTEGER, Pdlg_parts[i].kid);
		fprintf(fp, "%-11s",  Pdlg_parts[i].konto);
		fprintf(fp, PINTEGER, Pdlg_parts[i].textid);
		fprintf(fp, PINTEGER, Pdlg_parts[i].sai_id);
		fprintf(fp, PINTEGER, Pdlg_parts[i].rechst);

		fprintf(fp, "\n");
	}
	fclose(fp);

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_put_saison
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_put_saison(SAISON *Psaison, int row_cnt)
{
	int  i;
	FILE *fp;

	if ((fp = fopen(MPF_SAISON, _P_WRITE_)) == NULL ) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
		                MPF_SAISON);
		return (int)MPERROR;
	}

	for (i = 0; i < row_cnt; i++ ) {
		fprintf(fp, PINTEGER, Psaison[i].sai_id);
		fprintf(fp, PINTEGER, Psaison[i].bez_id);
		fprintf(fp, PINTEGER, Psaison[i].von);
		fprintf(fp, PINTEGER, Psaison[i].bis);
		fprintf(fp, PINTEGER, Psaison[i].textid);

		fprintf(fp, "\n");
	}
	fclose(fp);

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_kapa
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_kapa()
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_KAPA);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle KAPA\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete KAPA del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_mp_arrkom
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_mp_arrkom()
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_MP_ARRKOM);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle MP_ARRKOM\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete MP_ARRKOM del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_preis
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_preis(int sai_id)
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_PREIS, sai_id);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle PREIS\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete PREIS del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_reservation
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_reservation(int bid)
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_RESERVATION, bid);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle RESERVATION\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete RESERVATION del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_kommission
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_kommission(int sai_id)
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_KOMMISSION, sai_id);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle KOMMISSION\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete KOMMISSION del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_akt_detail
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_akt_detail(int bid)
{
	char	command[_QUERYLEN];
	int	anzahl;
	int	status=(int)MPOK;

	(void)sprintf(command, _DELETE_AKT_DETAIL, bid);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle AKT_DETAIL\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete AKT_DETAIL del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_buchung
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_buchung(int sai_id)
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_BUCHUNG, sai_id);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle BUCHUNG\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete BUCHUNG del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_kontingent
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_kontingent(int sai_id)
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_KONTINGENT, sai_id);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle KONTINGENT\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete KONTINGENT del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_host_kont
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_host_kont(int sai_id)
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_HOST_KONT, sai_id);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle HOST_KONT\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete HOST_KONT del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_arrangement
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_arrangement(int sai_id)
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_ARRANGEMENT, sai_id);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle ARRANGEMENT\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete ARRANGEMENT del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_programm
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_programm(int sai_id)
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_PROGRAMM, sai_id);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle PROGRAMM\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete PROGRAMM del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_dienstleistung
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_dienstleistung(int sai_id)
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_DIENSTLEISTUNG, sai_id);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle DIENSTLEISTUNG\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete DIENSTLEISTUNG del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_dlg_parts
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_dlg_parts(int sai_id)
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_DLG_PARTS, sai_id);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle DLG_PARTS\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete DLG_PARTS del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_saison
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_saison(int sai_id)
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_SAISON, sai_id);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle SAISON\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete SAISON del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_komm_detail
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_komm_detail(int komm_id)
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_KOMM_DETAIL, komm_id);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle KOMM_DETAIL\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete KOMM_DETAIL del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_bch_dln
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_bch_dln(int bid)
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_BCH_DLN, bid);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle BCH_DLN\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete BCH_DLN del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_kont_detail_kont
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_kont_detail_kont(int kont_id)
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_KONT_DETAIL_KONT, kont_id);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle KONT_DETAIL_KONT\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete KONT_DETAIL_KONT del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_kont_detail_host
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_kont_detail_host(int hostkont_id)
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_KONT_DETAIL_HOST, hostkont_id);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle KONT_DETAIL_HOST\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete KONT_DETAIL_HOST del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_arr_dlg
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_arr_dlg(int arr_id)
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_ARR_DLG, arr_id);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle ARR_DLG\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete ARR_DLG del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_delete_dlg_dlg
 * Return:   MPOK or MPERROR
 *************************************************************/
static int MPC_delete_dlg_dlg(int dlg_id)
{
	char  command[_QUERYLEN];
	int   anzahl;
	int   status=(int)MPOK;

	(void)sprintf(command, _DELETE_DLG_DLG, dlg_id);
	status = MPAPIdb_sqlcommand(command, &anzahl);

	if (status != (int)MPOK) {
		fprintf (stderr, "Fehler beim loeschen in Tabelle DLG_DLG\n");
		return (int)MPERROR;
	} else {
		printf("SQL delete DLG_DLG del-rowcnt %d\n", anzahl);
	}

	return (int)MPOK;
}


/*SF**********************************************************
 * Function: MPC_kapa
 * Return:   status
 *************************************************************/
static int MPC_kapa()
{
	KAPA		*Pkapa;
	MEMOBJ	sqlmem;
	char		query[_QUERYLEN];
	int		status=(int)MPOK;
	int		row_cnt;

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ Begin Transaction ------ */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);

	/* ------ select the data ------ */
	(void)printf("start SQL query\n");
	(void)sprintf(query, _SELECT_KAPA);
	status = MPAPIdb_sqlquery((int)_KAPA, &sqlmem.buffer, query,
	                          &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
	Pkapa = (KAPA *)sqlmem.buffer;
	printf("SQL query KAPA done with status %d and rowcnt %d\n", status, row_cnt);

	if (status != (int)MPOK )
		return status;

	/* ------ delete data in the table ------ */
	status = MPC_delete_kapa();
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ put the data in a ascii - file ------ */
	status = MPC_put_kapa(Pkapa, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ commit work ------ */
	(void)MPAPIdb_committrx();

	return status;
}


/*SF**********************************************************
 * Function: MPC_mp_arrkom
 * Return:   status
 *************************************************************/
static int MPC_mp_arrkom()
{
	MP_ARRKOM	*Pmp_arrkom;
	MEMOBJ		sqlmem;
	char			query[_QUERYLEN];
	int			status=(int)MPOK;
	int			row_cnt;

	/* ------ Begin Transaction ------ */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ select the data ------ */
	(void)printf("start SQL query\n");
	(void)sprintf(query, _SELECT_MP_ARRKOM);
	status = MPAPIdb_sqlquery((int)_MP_ARRKOM, &sqlmem.buffer, query,
	                          &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
	Pmp_arrkom = (MP_ARRKOM *)sqlmem.buffer;
	printf("SQL query MP_ARRKOM done with status %d and rowcnt %d\n", status, row_cnt);

	if (status != (int)MPOK)
		return status;

	/* ------ delete data in the table ------ */
	status = MPC_delete_mp_arrkom();
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ put the data in a ascii - file ------ */
	status = MPC_put_mp_arrkom(Pmp_arrkom, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ commit work ------ */
	(void)MPAPIdb_committrx();

	return status;
}


/*SF**********************************************************
 * Function: MPC_preis
 * Return:   status
 *************************************************************/
static int MPC_preis(int sai_id)
{
	PREIS		*Ppreis;
	MEMOBJ	sqlmem;
	char		query[_QUERYLEN];
	int		status=(int)MPOK;
	int		row_cnt;

	/* ------ Begin Transaction ------ */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ select the data ------ */
	(void)printf("start SQL query\n");
	(void)sprintf(query, _SELECT_PREIS, sai_id);
	status = MPAPIdb_sqlquery((int)_PREIS, &sqlmem.buffer, query,
	                          &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
	Ppreis = (PREIS *)sqlmem.buffer;
	printf("SQL query PREIS done with status %d and rowcnt %d\n", status, row_cnt);

	if (status != (int)MPOK)
		return status;

	/* ------ delete data in the table ------ */
	status = MPC_delete_preis(sai_id);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ put the data in a ascii - file ------ */
	status = MPC_put_preis(Ppreis, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ commit work ------ */
	(void)MPAPIdb_committrx();

	return status;
}


/*SF**********************************************************
 * Function: MPC_reservation
 * Return:   status
 *************************************************************/
static int MPC_reservation(BUCHUNG *Pbuchung, int anz_buchung)
{
	RESERVATION	*Preservation;
	MEMOBJ		sqlmem;
	FILE			*fp;
	char			query[_QUERYLEN];
	int			status=(int)MPOK;
	int			row_cnt;
	int			i, a;

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ File open for write ------ */
	if ((fp = fopen(MPF_RESERVATION, _P_WRITE_)) == NULL ) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
		                MPF_RESERVATION);
		return (int)MPERROR;
	}

	/* ------ loop for all buchung ------ */
	for (i = 0; i < anz_buchung; i++) {

		/* ------ Begin Transaction ------ */
		status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);

		/* ------ select the data ------ */
		(void)printf("start SQL query\n");
		(void)sprintf(query, _SELECT_RESERVATION, Pbuchung[i].bid);
		status = MPAPIdb_sqlquery((int)_RESERVATION, &sqlmem.buffer, query,
	                             &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
		Preservation = (RESERVATION *)sqlmem.buffer;
		printf("SQL query RESERVATION done with status %d and rowcnt %d\n", status, row_cnt);

		if (status != (int)MPOK) {
			/* ------ rollback ------ */
			(void)MPAPIdb_rollbacktrx();
			fclose(fp);
			return status;
		}

		/* ------ delete data in the table ------ */
		status = MPC_delete_reservation(Pbuchung[i].bid);
		if (status != (int)MPOK) {
			/* ------ rollback ------ */
			(void)MPAPIdb_rollbacktrx();
			fclose(fp);
			return status;
		}

		/* ------ put the data in a ascii - file ------ */
		for (a = 0; a < row_cnt; a++ ) {
			fprintf(fp, PINTEGER, Preservation[a].pers_id);
			fprintf(fp, PINTEGER, Preservation[a].dlg_id);
			fprintf(fp, PINTEGER, Preservation[a].dl_id);
			fprintf(fp, PINTEGER, Preservation[a].teil);
			fprintf(fp, PINTEGER, Preservation[a].dlt_id);
			fprintf(fp, PINTEGER, Preservation[a].typ_id);
			fprintf(fp, PINTEGER, Preservation[a].bid);
			fprintf(fp, PINTEGER, Preservation[a].kont_id);
			fprintf(fp, PINTEGER, Preservation[a].kat_id);
			fprintf(fp, PINTEGER, Preservation[a].k_kon);
			fprintf(fp, PINTEGER, Preservation[a].b_kon);
			fprintf(fp, PINTEGER, Preservation[a].r_sta);
			fprintf(fp, PINTEGER, Preservation[a].sai_id);
			fprintf(fp, PINTEGER, Preservation[a].a_zeit);
			fprintf(fp, PINTEGER, Preservation[a].e_zeit);
			fprintf(fp, PINTEGER, Preservation[a].textid);

			fprintf(fp, "\n");
		}

		/* ------ commit work ------ */
		(void)MPAPIdb_committrx();
	}

	fclose(fp);

	return status;
}


/*SF**********************************************************
 * Function: MPC_kommission
 * Return:   status
 *************************************************************/
static int MPC_kommission(int sai_id)
{
	KOMMISSION	*Pkommission;
	MEMOBJ		sqlmem;
	char			query[_QUERYLEN];
	int			status=(int)MPOK;
	int			row_cnt;

	/* ------ Begin Transaction ------ */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ select the data ------ */
	(void)printf("start SQL query\n");
	(void)sprintf(query, _SELECT_KOMMISSION, sai_id);
	status = MPAPIdb_sqlquery((int)_KOMMISSION, &sqlmem.buffer, query,
	                          &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
	Pkommission = (KOMMISSION *)sqlmem.buffer;
	printf("SQL query KOMMISSION done with status %d and rowcnt %d\n", status, row_cnt);

	if (status != (int)MPOK)
		return status;

	/* ------ TEXTE and BEZEICHNUNG ------ */
	status = MPC_texte_bez_kommission(Pkommission, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ KOMM_DETAIL ------ */
	status = MPC_komm_detail(Pkommission, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ delete data in the table ------ */
	status = MPC_delete_kommission(sai_id);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ put the data in a ascii - file ------ */
	status = MPC_put_kommission(Pkommission, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ commit work ------ */
	(void)MPAPIdb_committrx();

	return status;
}


/*SF**********************************************************
 * Function: MPC_akt_detail
 * Return:   status
 *************************************************************/
static int MPC_akt_detail(BUCHUNG *Pbuchung, int anz_buchung)
{
	AKT_DETAIL	*Pakt_detail;
	MEMOBJ		sqlmem;
	FILE			*fp;
	char			query[_QUERYLEN];
	int			status=(int)MPOK;
	int			row_cnt;
	int			i, a;

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ File open for write ------ */
	if ((fp = fopen(MPF_AKT_DETAIL, _P_WRITE_)) == NULL ) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
		                MPF_AKT_DETAIL);
		return (int)MPERROR;
	}

	/* ------ loop for all buchung ------ */
	for (i = 0; i < anz_buchung; i++) {

		/* ------ Begin Transaction ------ */
		status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);

		/* ------ select the data ------ */
		(void)printf("start SQL query\n");
		(void)sprintf(query, _SELECT_AKT_DETAIL, Pbuchung[i].bid);
		status = MPAPIdb_sqlquery((int)_AKT_DETAIL, &sqlmem.buffer, query,
	                             &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
		Pakt_detail = (AKT_DETAIL *)sqlmem.buffer;
		printf("SQL query AKT_DETAIL done with status %d and rowcnt %d\n", status, row_cnt);

		if (status != (int)MPOK) {
			/* ------ rollback ------ */
			(void)MPAPIdb_rollbacktrx();
			fclose(fp);
			return status;
		}

		/* ------ delete data in the table ------ */
		status = MPC_delete_akt_detail(Pbuchung[i].bid);
		if (status != (int)MPOK) {
			/* ------ rollback ------ */
			(void)MPAPIdb_rollbacktrx();
			fclose(fp);
			return status;
		}

		/* ------ put the data in a ascii - file ------ */
		for (a = 0; a < row_cnt; a++ ) {
			fprintf(fp, PINTEGER, Pakt_detail[a].bid);
			fprintf(fp, PINTEGER, Pakt_detail[a].pers_id);
			fprintf(fp, PINTEGER, Pakt_detail[a].dlg_id);
			fprintf(fp, PINTEGER, Pakt_detail[a].dl_id);
			fprintf(fp, PINTEGER, Pakt_detail[a].teil);
			fprintf(fp, PINTEGER, Pakt_detail[a].akt_id);
			fprintf(fp, PINTEGER, Pakt_detail[a].ord);
			fprintf(fp, PINTEGER, Pakt_detail[a].a_typ_id);
			fprintf(fp, PINTEGER, Pakt_detail[a].z_flag);
			fprintf(fp, PINTEGER, Pakt_detail[a].akt_nr);
			fprintf(fp, PINTEGER, Pakt_detail[a].sai_id);
			fprintf(fp, PINTEGER, Pakt_detail[a].parentakt);
			fprintf(fp, PINTEGER, Pakt_detail[a].exec_dat);

			fprintf(fp, "\n");
		}

		/* ------ commit work ------ */
		(void)MPAPIdb_committrx();
	}

	fclose(fp);

	return status;
}


/*SF**********************************************************
 * Function: MPC_buchung
 * Return:   status
 *************************************************************/
static int MPC_buchung(int sai_id)
{
	BUCHUNG	*Pbuchung;
	MEMOBJ	sqlmem;
	char		query[_QUERYLEN];
	int		status=(int)MPOK;
	int		row_cnt;

	/* ------ Begin Transaction ------ */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ select the data ------ */
	(void)printf("start SQL query\n");
	(void)sprintf(query, _SELECT_BUCHUNG, sai_id);
	status = MPAPIdb_sqlquery((int)_BUCHUNG, &sqlmem.buffer, query,
	                          &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
	Pbuchung = (BUCHUNG *)sqlmem.buffer;
	printf("SQL query BUCHUNG done with status %d and rowcnt %d\n", status, row_cnt);

	/* ------ commit work ------ */
	(void)MPAPIdb_committrx();

	if (status != (int)MPOK)
		return status;

   /* ------ BCH_DLN ------ */
	status = MPC_bch_dln(Pbuchung, row_cnt);
	if (status != (int)MPOK) {
		return status;
	}

   /* ------ AKT_DETAIL ------ */
	status = MPC_akt_detail(Pbuchung, row_cnt);
	if (status != (int)MPOK)
		return status;

   /* ------ RESERVATION ------ */
	status = MPC_reservation(Pbuchung, row_cnt);
	if (status != (int)MPOK)
		return status;

	/* ------ Begin Transaction ------ */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);

	/* ------ delete data in the table ------ */
	status = MPC_delete_buchung(sai_id);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ put the data in a ascii - file ------ */
	status = MPC_put_buchung(Pbuchung, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ commit work ------ */
	(void)MPAPIdb_committrx();

	return status;
}


/*SF**********************************************************
 * Function: MPC_kontingent
 * Return:   status
 *************************************************************/
static int MPC_kontingent(int sai_id)
{
	KONTINGENT	*Pkontingent;
	MEMOBJ		sqlmem;
	char			query[_QUERYLEN];
	int			status=(int)MPOK;
	int			row_cnt;

	/* ------ Begin Transaction ------ */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ select the data ------ */
	(void)printf("start SQL query\n");
	(void)sprintf(query, _SELECT_KONTINGENT, sai_id);
	status = MPAPIdb_sqlquery((int)_KONTINGENT, &sqlmem.buffer, query,
	                          &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
	Pkontingent = (KONTINGENT *)sqlmem.buffer;
	printf("SQL query KONTINGENT done with status %d and rowcnt %d\n", status, row_cnt);

	if (status != (int)MPOK)
		return status;

	/* ------ TEXTE and BEZEICHNUNG ------ */
	status = MPC_texte_bez_kontingent(Pkontingent, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ KONT_DETAIL KONT ------ */
	status = MPC_kont_detail_kont(Pkontingent, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ delete data in the table ------ */
	status = MPC_delete_kontingent(sai_id);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ put the data in a ascii - file ------ */
	status = MPC_put_kontingent(Pkontingent, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ commit work ------ */
	(void)MPAPIdb_committrx();

	return status;
}


/*SF**********************************************************
 * Function: MPC_host_kont
 * Return:   status
 *************************************************************/
static int MPC_host_kont(int sai_id)
{
	HOST_KONT	*Phost_kont;
	MEMOBJ		sqlmem;
	char			query[_QUERYLEN];
	int			status=(int)MPOK;
	int			row_cnt;

	/* ------ Begin Transaction ------ */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ select the data ------ */
	(void)printf("start SQL query\n");
	(void)sprintf(query, _SELECT_HOST_KONT, sai_id);
	status = MPAPIdb_sqlquery((int)_HOST_KONT, &sqlmem.buffer, query,
	                          &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
	Phost_kont = (HOST_KONT *)sqlmem.buffer;
	printf("SQL query HOST_KONT done with status %d and rowcnt %d\n", status, row_cnt);

	if (status != (int)MPOK)
		return status;

	/* ------ TEXTE and BEZEICHNUNG ------ */
	status = MPC_texte_bez_host_kont(Phost_kont, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ KONT_DETAIL HOST ------ */
	status = MPC_kont_detail_host(Phost_kont, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ delete data in the table ------ */
	status = MPC_delete_host_kont(sai_id);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ put the data in a ascii - file ------ */
	status = MPC_put_host_kont(Phost_kont, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ commit work ------ */
	(void)MPAPIdb_committrx();

	return status;
}


/*SF**********************************************************
 * Function: MPC_arrangement
 * Return:   status
 *************************************************************/
static int MPC_arrangement(int sai_id)
{
	ARRANGEMENT	*Parrangement;
	MEMOBJ		sqlmem;
	char			query[_QUERYLEN];
	int			status=(int)MPOK;
	int			row_cnt;

	/* ------ Begin Transaction ------ */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ select the data ------ */
	(void)printf("start SQL query\n");
	(void)sprintf(query, _SELECT_ARRANGEMENT, sai_id);
	status = MPAPIdb_sqlquery((int)_ARRANGEMENT, &sqlmem.buffer, query,
	                          &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
	Parrangement = (ARRANGEMENT *)sqlmem.buffer;
	printf("SQL query ARRANGEMENT done with status %d and rowcnt %d\n", status, row_cnt);

	if (status != (int)MPOK)
		return status;

	/* ------ TEXTE and BEZEICHNUNG ------ */
	status = MPC_texte_bez_arrangement(Parrangement, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

   /* ------ ARR_DLG ------ */
   status = MPC_arr_dlg(Parrangement, row_cnt);
   if (status != (int)MPOK) {
      (void)MPAPIdb_rollbacktrx();
      return status;
   }

	/* ------ delete data in the table ------ */
	status = MPC_delete_arrangement(sai_id);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ put the data in a ascii - file ------ */
	status = MPC_put_arrangement(Parrangement, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ commit work ------ */
	(void)MPAPIdb_committrx();

	return status;
}


/*SF**********************************************************
 * Function: MPC_programm
 * Return:   status
 *************************************************************/
static int MPC_programm(int sai_id)
{
	PROGRAMM	*Pprogramm;
	MEMOBJ	sqlmem;
	char		query[_QUERYLEN];
	int		status=(int)MPOK;
	int		row_cnt;

	/* ------ Begin Transaction ------ */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ select the data ------ */
	(void)printf("start SQL query\n");
	(void)sprintf(query, _SELECT_PROGRAMM, sai_id);
	status = MPAPIdb_sqlquery((int)_PROGRAMM, &sqlmem.buffer, query,
	                          &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
	Pprogramm = (PROGRAMM *)sqlmem.buffer;
	printf("SQL query PROGRAMM done with status %d and rowcnt %d\n", status, row_cnt);

	if (status != (int)MPOK)
		return status;

	/* ------ TEXTE and BEZEICHNUNG ------ */
	status = MPC_texte_bez_programm(Pprogramm, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ delete data in the table ------ */
	status = MPC_delete_programm(sai_id);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ put the data in a ascii - file ------ */
	status = MPC_put_programm(Pprogramm, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ commit work ------ */
	(void)MPAPIdb_committrx();

	return status;
}


/*SF**********************************************************
 * Function: MPC_dienstleistung
 * Return:   status
 *************************************************************/
static int MPC_dienstleistung(int sai_id)
{
	DIENSTLEISTUNG	*Pdienstleistung;
	MEMOBJ			sqlmem;
	char				query[_QUERYLEN];
	int				status=(int)MPOK;
	int				row_cnt;

	/* ------ Begin Transaction ------ */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ select the data ------ */
	(void)printf("start SQL query\n");
	(void)sprintf(query, _SELECT_DIENSTLEISTUNG, sai_id);
	status = MPAPIdb_sqlquery((int)_DIENSTLEISTUNG, &sqlmem.buffer, query,
	                          &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
	Pdienstleistung = (DIENSTLEISTUNG *)sqlmem.buffer;
	printf("SQL query DIENSTLEISTUNG done with status %d and rowcnt %d\n", status, row_cnt);

	if (status != (int)MPOK)
		return status;

	/* ------ TEXTE and BEZEICHNUNG ------ */
	status = MPC_texte_bez_dienstleistung(Pdienstleistung, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ DLG_DLG ------ */
	status = MPC_dlg_dlg(Pdienstleistung, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ delete data in the table ------ */
	status = MPC_delete_dienstleistung(sai_id);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ put the data in a ascii - file ------ */
	status = MPC_put_dienstleistung(Pdienstleistung, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ commit work ------ */
	(void)MPAPIdb_committrx();

	return status;
}


/*SF**********************************************************
 * Function: MPC_dlg_parts
 * Return:   status
 *************************************************************/
static int MPC_dlg_parts(int sai_id)
{
	DLG_PART	*Pdlg_parts;
	MEMOBJ	sqlmem;
	char		query[_QUERYLEN];
	int		status=(int)MPOK;
	int		row_cnt;

	/* ------ Begin Transaction ------ */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ select the data ------ */
	(void)printf("start SQL query\n");
	(void)sprintf(query, _SELECT_DLG_PARTS, sai_id);
	status = MPAPIdb_sqlquery((int)_DLG_PART, &sqlmem.buffer, query,
	                          &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
	Pdlg_parts = (DLG_PART *)sqlmem.buffer;
	printf("SQL query DLG_PARTS done with status %d and rowcnt %d\n", status, row_cnt);

	if (status != (int)MPOK)
		return status;

	/* ------ TEXTE and BEZEICHNUNG ------ */
	status = MPC_texte_bez_dlg_parts(Pdlg_parts, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ delete data in the table ------ */
	status = MPC_delete_dlg_parts(sai_id);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ put the data in a ascii - file ------ */
	status = MPC_put_dlg_parts(Pdlg_parts, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ commit work ------ */
	(void)MPAPIdb_committrx();

	return status;
}


/*SF**********************************************************
 * Function: MPC_saison
 * Return:   status
 *************************************************************/
static int MPC_saison(int sai_id)
{
	SAISON	*Psaison;
	MEMOBJ	sqlmem;
	char		query[_QUERYLEN];
	int		status=(int)MPOK;
	int		row_cnt;

	/* ------ Begin Transaction ------ */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ select the data ------ */
	(void)printf("start SQL query\n");
	(void)sprintf(query, _SELECT_SAISON, sai_id);
	status = MPAPIdb_sqlquery((int)_SAISON, &sqlmem.buffer, query,
	                          &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
	Psaison = (SAISON *)sqlmem.buffer;
	printf("SQL query SAISON done with status %d and rowcnt %d\n", status, row_cnt);

	if (status != (int)MPOK)
		return status;

	/* ------ TEXTE and BEZEICHNUNG ------ */
	status = MPC_texte_bez_saison(Psaison, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ delete data in the table ------ */
	status = MPC_delete_saison(sai_id);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ put the data in a ascii - file ------ */
	status = MPC_put_saison(Psaison, row_cnt);
	if (status != (int)MPOK) {
		(void)MPAPIdb_rollbacktrx();
		return status;
	}

	/* ------ commit work ------ */
	(void)MPAPIdb_committrx();

	return status;
}


/*SF**********************************************************
 * Function: MPC_komm_detail
 * Return:   status
 *************************************************************/
static int MPC_komm_detail(KOMMISSION *Pkommission, int anz_kommission)
{
	KOMM_DETAIL	*Pkomm_detail;
	MEMOBJ		sqlmem;
	FILE			*fp;
	char			query[_QUERYLEN];
	int			status=(int)MPOK;
	int			row_cnt;
	int			i, a;

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ File open for write ------ */
	if ((fp = fopen(MPF_KOMM_DETAIL, _P_WRITE_)) == NULL ) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
		                MPF_KOMM_DETAIL);
		return (int)MPERROR;
	}

	/* ------ loop for all kommissions ------ */
	for (i = 0; i < anz_kommission; i++) {
		/* ------ select the data ------ */
		(void)printf("start SQL query\n");
		(void)sprintf(query, _SELECT_KOMM_DETAIL, Pkommission[i].komm_id);
		status = MPAPIdb_sqlquery((int)_KOMM_DETAIL, &sqlmem.buffer, query,
	                             &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
		Pkomm_detail = (KOMM_DETAIL *)sqlmem.buffer;
		printf("SQL query KOMM_DETAIL done with status %d and rowcnt %d\n", status, row_cnt);

		if (status != (int)MPOK)
			return status;

		/* ------ delete data in the table ------ */
		status = MPC_delete_komm_detail(Pkommission[i].komm_id);
		if (status != (int)MPOK) {
			fclose(fp);
			return status;
		}

		/* ------ put the data in a ascii - file ------ */
		for (a = 0; a < row_cnt; a++ ) {
			fprintf(fp, PINTEGER, Pkomm_detail[a].komm_id);
			fprintf(fp, PINTEGER, Pkomm_detail[a].bid);
			fprintf(fp, PINTEGER, Pkomm_detail[a].dln_id);
			fprintf(fp, PINTEGER, Pkomm_detail[a].kun_id);
			fprintf(fp, PINTEGER, Pkomm_detail[a].kol_id);
			fprintf(fp, PINTEGER, Pkomm_detail[a].prio);

			fprintf(fp, "\n");
		}
	}

	fclose(fp);

	return status;
}


/*SF**********************************************************
 * Function: MPC_bch_dln
 * Return:   status
 *************************************************************/
static int MPC_bch_dln(BUCHUNG *Pbuchung, int anz_buchung)
{
	BCH_DLN	*Pbch_dln;
	MEMOBJ	sqlmem;
	FILE		*fp;
	char		query[_QUERYLEN];
	int		status=(int)MPOK;
	int		row_cnt;
	int		i, a;

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ File open for write ------ */
	if ((fp = fopen(MPF_BCH_DLN, _P_WRITE_)) == NULL ) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
		                MPF_BCH_DLN);
		return (int)MPERROR;
	}

	/* ------ loop for all buchung ------ */
	for (i = 0; i < anz_buchung; i++) {

		/* ------ Begin Transaction ------ */
		status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);

		/* ------ select the data ------ */
		(void)printf("start SQL query\n");
		(void)sprintf(query, _SELECT_BCH_DLN, Pbuchung[i].bid);
		status = MPAPIdb_sqlquery((int)_BCH_DLN, &sqlmem.buffer, query,
	                             &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
		Pbch_dln = (BCH_DLN *)sqlmem.buffer;
		printf("SQL query BCH_DLN done with status %d and rowcnt %d\n", status, row_cnt);

		if (status != (int)MPOK) {
			/* ------ rollback ------ */
			(void)MPAPIdb_rollbacktrx();
			fclose(fp);
			return status;
		}

		/* ------ delete data in the table ------ */
		status = MPC_delete_bch_dln(Pbuchung[i].bid);
		if (status != (int)MPOK) {
			/* ------ rollback ------ */
			(void)MPAPIdb_rollbacktrx();
			fclose(fp);
			return status;
		}

		/* ------ put the data in a ascii - file ------ */
		for (a = 0; a < row_cnt; a++ ) {
			fprintf(fp, PINTEGER, Pbch_dln[a].bid);
			fprintf(fp, PINTEGER, Pbch_dln[a].dln_id);

			fprintf(fp, "\n");
		}

		/* ------ commit work ------ */
		(void)MPAPIdb_committrx();
	}

	fclose(fp);

	return status;
}


/*SF**********************************************************
 * Function: MPC_kont_detail_kont
 * Return:   status
 *************************************************************/
static int MPC_kont_detail_kont(KONTINGENT *Pkontingent, int anz_kontingent)
{
	KONT_DETAIL	*Pkont_detail;
	MEMOBJ		sqlmem;
	FILE			*fp;
	char			query[_QUERYLEN];
	int			status=(int)MPOK;
	int			row_cnt;
	int			i, a;

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ File open for write ------ */
	if ((fp = fopen(MPF_KONT_DETAIL, _P_WRITE_)) == NULL ) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
		                MPF_KONT_DETAIL);
		return (int)MPERROR;
	}

	/* ------ loop for all kontingent ------ */
	for (i = 0; i < anz_kontingent; i++) {

		/* ------ select the data ------ */
		(void)printf("start SQL query\n");
		(void)sprintf(query, _SELECT_KONT_DETAIL_KONT, Pkontingent[i].kont_id);
		status = MPAPIdb_sqlquery((int)_KONT_DETAIL, &sqlmem.buffer, query,
	                             &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
		Pkont_detail = (KONT_DETAIL *)sqlmem.buffer;
		printf("SQL query KONT_DETAIL done with status %d and rowcnt %d\n", status, row_cnt);

		if (status != (int)MPOK) {
			fclose(fp);
			return status;
		}

		/* ------ delete data in the table ------ */
		status = MPC_delete_kont_detail_kont(Pkontingent[i].kont_id);
		if (status != (int)MPOK) {
			fclose(fp);
			return status;
		}

		/* ------ put the data in a ascii - file ------ */
		for (a = 0; a < row_cnt; a++ ) {
			fprintf(fp, PINTEGER, Pkont_detail[a].hostkont_id);
			fprintf(fp, PINTEGER, Pkont_detail[a].kont_id);
			fprintf(fp, PINTEGER, Pkont_detail[a].kat_id);
			fprintf(fp, PINTEGER, Pkont_detail[a].dlt_id);
			fprintf(fp, PINTEGER, Pkont_detail[a].sta_id);
			fprintf(fp, PINTEGER, Pkont_detail[a].anz);
			fprintf(fp, PINTEGER, Pkont_detail[a].busy);

			fprintf(fp, "\n");
		}
	}

	fclose(fp);

	return status;
}


/*SF**********************************************************
 * Function: MPC_kont_detail_kont
 * Return:   status
 *************************************************************/
static int MPC_kont_detail_host(HOST_KONT *Phost_kont, int anz_host_kont)
{
	KONT_DETAIL	*Pkont_detail;
	MEMOBJ		sqlmem;
	FILE			*fp;
	char			query[_QUERYLEN];
	int			status=(int)MPOK;
	int			row_cnt;
	int			i, a;

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ File open for write ------ */
	if ((fp = fopen(MPF_KONT_DETAIL, _P_APPEND_)) == NULL ) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
		                MPF_KONT_DETAIL);
		return (int)MPERROR;
	}

	/* ------ loop for all host_kont ------ */
	for (i = 0; i < anz_host_kont; i++) {

		/* ------ select the data ------ */
		(void)printf("start SQL query\n");
		(void)sprintf(query, _SELECT_KONT_DETAIL_HOST, Phost_kont[i].hostkont_id);
		status = MPAPIdb_sqlquery((int)_KONT_DETAIL, &sqlmem.buffer, query,
	                             &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
		Pkont_detail = (KONT_DETAIL *)sqlmem.buffer;
		printf("SQL query KONT_DETAIL done with status %d and rowcnt %d\n", status, row_cnt);

		if (status != (int)MPOK) {
			fclose(fp);
			return status;
		}

		/* ------ delete data in the table ------ */
		status = MPC_delete_kont_detail_host(Phost_kont[i].hostkont_id);
		if (status != (int)MPOK) {
			fclose(fp);
			return status;
		}

		/* ------ put the data in a ascii - file ------ */
		for (a = 0; a < row_cnt; a++ ) {
			fprintf(fp, PINTEGER, Pkont_detail[a].hostkont_id);
			fprintf(fp, PINTEGER, Pkont_detail[a].kont_id);
			fprintf(fp, PINTEGER, Pkont_detail[a].kat_id);
			fprintf(fp, PINTEGER, Pkont_detail[a].dlt_id);
			fprintf(fp, PINTEGER, Pkont_detail[a].sta_id);
			fprintf(fp, PINTEGER, Pkont_detail[a].anz);
			fprintf(fp, PINTEGER, Pkont_detail[a].busy);

			fprintf(fp, "\n");
		}
	}

	fclose(fp);

	return status;
}


/*SF**********************************************************
 * Function: MPC_arr_dlg
 * Return:   status
 *************************************************************/
static int MPC_arr_dlg(ARRANGEMENT *Parrangement, int anz_arrangement)
{
	ARR_DLG	*Parr_dlg;
	MEMOBJ	sqlmem;
	FILE		*fp;
	char		query[_QUERYLEN];
	int		status=(int)MPOK;
	int		row_cnt;
	int		i, a;

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ File open for write ------ */
	if ((fp = fopen(MPF_ARR_DLG, _P_WRITE_)) == NULL ) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
		                MPF_ARR_DLG);
		return (int)MPERROR;
	}

	/* ------ loop for all arrangement ------ */
	for (i = 0; i < anz_arrangement; i++) {

		/* ------ select the data ------ */
		(void)printf("start SQL query\n");
		(void)sprintf(query, _SELECT_ARR_DLG, Parrangement[i].arr_id);
		status = MPAPIdb_sqlquery((int)_ARR_DLG, &sqlmem.buffer, query,
	                             &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
		Parr_dlg = (ARR_DLG *)sqlmem.buffer;
		printf("SQL query ARR_DLG done with status %d and rowcnt %d\n", status, row_cnt);

		if (status != (int)MPOK) {
			fclose(fp);
			return status;
		}

		/* ------ delete data in the table ------ */
		status = MPC_delete_arr_dlg(Parrangement[i].arr_id);
		if (status != (int)MPOK) {
			fclose(fp);
			return status;
		}

		/* ------ put the data in a ascii - file ------ */
		for (a = 0; a < row_cnt; a++ ) {
			fprintf(fp, PINTEGER, Parr_dlg[a].arr_id);
			fprintf(fp, PINTEGER, Parr_dlg[a].teil);
			fprintf(fp, PINTEGER, Parr_dlg[a].prio);
			fprintf(fp, PINTEGER, Parr_dlg[a].dlg_id);

			fprintf(fp, "\n");
		}
	}

	fclose(fp);

	return status;
}


/*SF**********************************************************
 * Function: MPC_dlg_dlg
 * Return:   status
 *************************************************************/
static int MPC_dlg_dlg(DIENSTLEISTUNG *Pdienstleistung, int anz_dienstleistung)
{
	DLG_DLG	*Pdlg_dlg;
	MEMOBJ	sqlmem;
	FILE		*fp;
	char		query[_QUERYLEN];
	int		status=(int)MPOK;
	int		row_cnt;
	int		i, a;

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ File open for write ------ */
	if ((fp = fopen(MPF_DLG_DLG, _P_WRITE_)) == NULL ) {
		fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
		                MPF_DLG_DLG);
		return (int)MPERROR;
	}

	/* ------ loop for all arrangement ------ */
	for (i = 0; i < anz_dienstleistung; i++) {

		/* ------ select the data ------ */
		(void)printf("start SQL query\n");
		(void)sprintf(query, _SELECT_DLG_DLG, Pdienstleistung[i].dlg_id);
		status = MPAPIdb_sqlquery((int)_DLG_DLG, &sqlmem.buffer, query,
	                             &row_cnt, &sqlmem.datalen, &sqlmem.alloclen);
		Pdlg_dlg = (DLG_DLG *)sqlmem.buffer;
		printf("SQL query DLG_DLG done with status %d and rowcnt %d\n", status, row_cnt);

		if (status != (int)MPOK) {
			fclose(fp);
			return status;
		}

		/* ------ delete data in the table ------ */
		status = MPC_delete_dlg_dlg(Pdienstleistung[i].dlg_id);
		if (status != (int)MPOK) {
			fclose(fp);
			return status;
		}

		/* ------ put the data in a ascii - file ------ */
		for (a = 0; a < row_cnt; a++ ) {
			fprintf(fp, PINTEGER, Pdlg_dlg[a].dlg_id);
			fprintf(fp, PINTEGER, Pdlg_dlg[a].dl_id);
			fprintf(fp, PINTEGER, Pdlg_dlg[a].ord);

			fprintf(fp, "\n");
		}
	}

	fclose(fp);

	return status;
}


/*SF**********************************************************
 * Function: MPC_texte_bez_kommission
 * Return:   status
 *************************************************************/
static int MPC_texte_bez_kommission(KOMMISSION *Pkommission, int row_cnt)
{
	TEXTE			*Ptexte;
	BEZEICHNUNG	*Pbezeichnung;
	MEMOBJ		sqlmem;
	FILE			*fp;
	char			query[_QUERYLEN];
	int			status=(int)MPOK;
	int			i, a, anz, found, id;

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ File erstellen fuer TEXTE ------ */
   if ((fp = fopen(MPF_TEXTE, _P_WRITE_)) == NULL) {
      fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n", MPF_TEXTE);
      return (int)MPERROR;
   }
	fclose(fp);

	/* ------ File erstellen fuer BEZEICHNUNG ------ */
   if ((fp = fopen(MPF_BEZEICHNUNG, _P_WRITE_)) == NULL) {
      fprintf(stderr, "\nFile: %s konnte nicht geoefnet werden!\n",
                       MPF_BEZEICHNUNG);
      return (int)MPERROR;
   }
	fclose(fp);

	/* ------ TEXTE ------ */
	for (i = 0; i < row_cnt; i++) {
		id = Pkommission[i].textid;
		found = 0;
		for (a = 0; a < i; a++) {
			if (Pkommission[a].textid = id) {
				found = 1;
				break;
			}
		}
		/* ------ id wurde noch nicht verarbeitet ------ */
		if (found == 0) {
			/* ------ select the data ------ */
			(void)printf("start SQL query\n");
			(void)sprintf(query, _SELECT_TEXTE, Pkommission[i].textid,
			                                    _KOMMISSION);
			status = MPAPIdb_sqlquery((int)_TEXTE, &sqlmem.buffer, query,
			                          &anz, &sqlmem.datalen, &sqlmem.alloclen);
			Ptexte = (TEXTE *)sqlmem.buffer;
			printf("SQL query TEXTE done with status %d and rowcnt %d\n", status, anz);
			if (status != (int)MPOK)
				return status;

			/* ------ delete texte ------ */
			status = MPC_delete_texte(Pkommission[i].textid, _KOMMISSION);
			if (status != (int)MPOK)
				return status;

			/* ------ put texte ------ */
			status = MPC_put_texte(Ptexte, anz);
			if (status != (int)MPOK)
				return status;
		} 
	}

	/* ------ BEZEICHNUNG ------ */
	for (i = 0; i < row_cnt; i++) {
		id = Pkommission[i].bez_id;
		found = 0;
		for (a = 0; a < i; a++) {
			if (Pkommission[a].bez_id = id) {
				found = 1;
				break;
			}
		}
		if (found == 0) {
			/* ------ select the data ------ */
			(void)printf("start SQL query\n");
			(void)sprintf(query, _SELECT_BEZEICHNUNG, Pkommission[i].bez_id,
			                                          _KOMMISSION);
			status = MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, query,
			                          &anz, &sqlmem.datalen, &sqlmem.alloclen);
			Pbezeichnung = (BEZEICHNUNG *)sqlmem.buffer;
			printf("SQL query BEZEICHNUNG done with status %d and rowcnt %d\n", status, anz);
			if (status != (int)MPOK)
				return status;

			/* ------ delete texte ------ */
			status = MPC_delete_bezeichnung(Pkommission[i].bez_id, _KOMMISSION);
			if (status != (int)MPOK)
				return status;

			/* ------ put bezeichnung ------ */
			status = MPC_put_bezeichnung(Pbezeichnung, anz);
			if (status != (int)MPOK)
				return status;
		}
	}

	return status;
}


/*SF**********************************************************
 * Function: MPC_texte_bez_kontingent
 * Return:   status
 *************************************************************/
static int MPC_texte_bez_kontingent(KONTINGENT *Pkontingent, int row_cnt)
{
	TEXTE			*Ptexte;
	BEZEICHNUNG	*Pbezeichnung;
	MEMOBJ		sqlmem;
	char			query[_QUERYLEN];
	int			status=(int)MPOK;
	int			i, a, anz, found, id;

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ TEXTE ------ */
	for (i = 0; i < row_cnt; i++) {
		id = Pkontingent[i].textid;
		found = 0;
		for (a = 0; a < i; a++) {
			if (Pkontingent[a].textid = id) {
				found = 1;
				break;
			}
		}
		/* ------ id wurde noch nicht verarbeitet ------ */
		if (found == 0) {
			/* ------ select the data ------ */
			(void)printf("start SQL query\n");
			(void)sprintf(query, _SELECT_TEXTE, Pkontingent[i].textid,
			                                    _KONTINGENT);
			status = MPAPIdb_sqlquery((int)_TEXTE, &sqlmem.buffer, query,
			                          &anz, &sqlmem.datalen, &sqlmem.alloclen);
			Ptexte = (TEXTE *)sqlmem.buffer;
			printf("SQL query TEXTE done with status %d and rowcnt %d\n", status, anz);
			if (status != (int)MPOK)
				return status;

			/* ------ delete texte ------ */
			status = MPC_delete_texte(Pkontingent[i].textid, _KONTINGENT);
			if (status != (int)MPOK)
				return status;

			/* ------ put texte ------ */
			status = MPC_put_texte(Ptexte, anz);
			if (status != (int)MPOK)
				return status;
		} 
	}

	/* ------ BEZEICHNUNG ------ */
	for (i = 0; i < row_cnt; i++) {
		id = Pkontingent[i].bez_id;
		found = 0;
		for (a = 0; a < i; a++) {
			if (Pkontingent[a].bez_id = id) {
				found = 1;
				break;
			}
		}
		if (found == 0) {
			/* ------ select the data ------ */
			(void)printf("start SQL query\n");
			(void)sprintf(query, _SELECT_BEZEICHNUNG, Pkontingent[i].bez_id,
			                                          _KONTINGENT);
			status = MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, query,
			                          &anz, &sqlmem.datalen, &sqlmem.alloclen);
			Pbezeichnung = (BEZEICHNUNG *)sqlmem.buffer;
			printf("SQL query BEZEICHNUNG done with status %d and rowcnt %d\n", status, anz);
			if (status != (int)MPOK)
				return status;

			/* ------ delete texte ------ */
			status = MPC_delete_bezeichnung(Pkontingent[i].bez_id, _KONTINGENT);
			if (status != (int)MPOK)
				return status;

			/* ------ put bezeichnung ------ */
			status = MPC_put_bezeichnung(Pbezeichnung, anz);
			if (status != (int)MPOK)
				return status;
		}
	}

	return status;
}


/*SF**********************************************************
 * Function: MPC_texte_bez_host_kont
 * Return:   status
 *************************************************************/
static int MPC_texte_bez_host_kont(HOST_KONT *Phost_kont, int row_cnt)
{
	TEXTE			*Ptexte;
	BEZEICHNUNG	*Pbezeichnung;
	MEMOBJ		sqlmem;
	char			query[_QUERYLEN];
	int			status=(int)MPOK;
	int			i, a, anz, found, id;

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ TEXTE ------ */
	for (i = 0; i < row_cnt; i++) {
		id = Phost_kont[i].textid;
		found = 0;
		for (a = 0; a < i; a++) {
			if (Phost_kont[a].textid = id) {
				found = 1;
				break;
			}
		}
		/* ------ id wurde noch nicht verarbeitet ------ */
		if (found == 0) {
			/* ------ select the data ------ */
			(void)printf("start SQL query\n");
			(void)sprintf(query, _SELECT_TEXTE, Phost_kont[i].textid,
			                                    _HOST_KONT);
			status = MPAPIdb_sqlquery((int)_TEXTE, &sqlmem.buffer, query,
			                          &anz, &sqlmem.datalen, &sqlmem.alloclen);
			Ptexte = (TEXTE *)sqlmem.buffer;
			printf("SQL query TEXTE done with status %d and rowcnt %d\n", status, anz);
			if (status != (int)MPOK)
				return status;

			/* ------ delete texte ------ */
			status = MPC_delete_texte(Phost_kont[i].textid, _HOST_KONT);
			if (status != (int)MPOK)
				return status;

			/* ------ put texte ------ */
			status = MPC_put_texte(Ptexte, anz);
			if (status != (int)MPOK)
				return status;
		} 
	}

	/* ------ BEZEICHNUNG ------ */
	for (i = 0; i < row_cnt; i++) {
		id = Phost_kont[i].bez_id;
		found = 0;
		for (a = 0; a < i; a++) {
			if (Phost_kont[a].bez_id = id) {
				found = 1;
				break;
			}
		}
		if (found == 0) {
			/* ------ select the data ------ */
			(void)printf("start SQL query\n");
			(void)sprintf(query, _SELECT_BEZEICHNUNG, Phost_kont[i].bez_id,
			                                          _HOST_KONT);
			status = MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, query,
			                          &anz, &sqlmem.datalen, &sqlmem.alloclen);
			Pbezeichnung = (BEZEICHNUNG *)sqlmem.buffer;
			printf("SQL query BEZEICHNUNG done with status %d and rowcnt %d\n", status, anz);
			if (status != (int)MPOK)
				return status;

			/* ------ delete texte ------ */
			status = MPC_delete_bezeichnung(Phost_kont[i].bez_id, _HOST_KONT);
			if (status != (int)MPOK)
				return status;

			/* ------ put bezeichnung ------ */
			status = MPC_put_bezeichnung(Pbezeichnung, anz);
			if (status != (int)MPOK)
				return status;
		}
	}

	return status;
}


/*SF**********************************************************
 * Function: MPC_texte_bez_arrangement
 * Return:   status
 *************************************************************/
static int MPC_texte_bez_arrangement(ARRANGEMENT *Parrangement, int row_cnt)
{
	TEXTE			*Ptexte;
	BEZEICHNUNG	*Pbezeichnung;
	MEMOBJ		sqlmem;
	char			query[_QUERYLEN];
	int			status=(int)MPOK;
	int			i, a, anz, found, id;

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ TEXTE ------ */
	for (i = 0; i < row_cnt; i++) {
		id = Parrangement[i].textid;
		found = 0;
		for (a = 0; a < i; a++) {
			if (Parrangement[a].textid = id) {
				found = 1;
				break;
			}
		}
		/* ------ id wurde noch nicht verarbeitet ------ */
		if (found == 0) {
			/* ------ select the data ------ */
			(void)printf("start SQL query\n");
			(void)sprintf(query, _SELECT_TEXTE, Parrangement[i].textid,
			                                    _ARRANGEMENT);
			status = MPAPIdb_sqlquery((int)_TEXTE, &sqlmem.buffer, query,
			                          &anz, &sqlmem.datalen, &sqlmem.alloclen);
			Ptexte = (TEXTE *)sqlmem.buffer;
			printf("SQL query TEXTE done with status %d and rowcnt %d\n", status, anz);
			if (status != (int)MPOK)
				return status;

			/* ------ delete texte ------ */
			status = MPC_delete_texte(Parrangement[i].textid, _ARRANGEMENT);
			if (status != (int)MPOK)
				return status;

			/* ------ put texte ------ */
			status = MPC_put_texte(Ptexte, anz);
			if (status != (int)MPOK)
				return status;
		} 
	}

	/* ------ BEZEICHNUNG ------ */
	for (i = 0; i < row_cnt; i++) {
		id = Parrangement[i].bez_id;
		found = 0;
		for (a = 0; a < i; a++) {
			if (Parrangement[a].bez_id = id) {
				found = 1;
				break;
			}
		}
		if (found == 0) {
			/* ------ select the data ------ */
			(void)printf("start SQL query\n");
			(void)sprintf(query, _SELECT_BEZEICHNUNG, Parrangement[i].bez_id,
			                                          _ARRANGEMENT);
			status = MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, query,
			                          &anz, &sqlmem.datalen, &sqlmem.alloclen);
			Pbezeichnung = (BEZEICHNUNG *)sqlmem.buffer;
			printf("SQL query BEZEICHNUNG done with status %d and rowcnt %d\n", status, anz);
			if (status != (int)MPOK)
				return status;

			/* ------ delete texte ------ */
			status = MPC_delete_bezeichnung(Parrangement[i].bez_id, _ARRANGEMENT);
			if (status != (int)MPOK)
				return status;

			/* ------ put bezeichnung ------ */
			status = MPC_put_bezeichnung(Pbezeichnung, anz);
			if (status != (int)MPOK)
				return status;
		}
	}

	return status;
}


/*SF**********************************************************
 * Function: MPC_texte_bez_programm
 * Return:   status
 *************************************************************/
static int MPC_texte_bez_programm(PROGRAMM *Pprogramm, int row_cnt)
{
	TEXTE			*Ptexte;
	BEZEICHNUNG	*Pbezeichnung;
	MEMOBJ		sqlmem;
	char			query[_QUERYLEN];
	int			status=(int)MPOK;
	int			i, a, anz, found, id;

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ TEXTE ------ */
	for (i = 0; i < row_cnt; i++) {
		id = Pprogramm[i].textid;
		found = 0;
		for (a = 0; a < i; a++) {
			if (Pprogramm[a].textid = id) {
				found = 1;
				break;
			}
		}
		/* ------ id wurde noch nicht verarbeitet ------ */
		if (found == 0) {
			/* ------ select the data ------ */
			(void)printf("start SQL query\n");
			(void)sprintf(query, _SELECT_TEXTE, Pprogramm[i].textid,
			                                    _PROGRAMM);
			status = MPAPIdb_sqlquery((int)_TEXTE, &sqlmem.buffer, query,
			                          &anz, &sqlmem.datalen, &sqlmem.alloclen);
			Ptexte = (TEXTE *)sqlmem.buffer;
			printf("SQL query TEXTE done with status %d and rowcnt %d\n", status, anz);
			if (status != (int)MPOK)
				return status;

			/* ------ delete texte ------ */
			status = MPC_delete_texte(Pprogramm[i].textid, _PROGRAMM);
			if (status != (int)MPOK)
				return status;

			/* ------ put texte ------ */
			status = MPC_put_texte(Ptexte, anz);
			if (status != (int)MPOK)
				return status;
		} 
	}

	/* ------ BEZEICHNUNG ------ */
	for (i = 0; i < row_cnt; i++) {
		id = Pprogramm[i].bez_id;
		found = 0;
		for (a = 0; a < i; a++) {
			if (Pprogramm[a].bez_id = id) {
				found = 1;
				break;
			}
		}
		if (found == 0) {
			/* ------ select the data ------ */
			(void)printf("start SQL query\n");
			(void)sprintf(query, _SELECT_BEZEICHNUNG, Pprogramm[i].bez_id,
			                                          _PROGRAMM);
			status = MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, query,
			                          &anz, &sqlmem.datalen, &sqlmem.alloclen);
			Pbezeichnung = (BEZEICHNUNG *)sqlmem.buffer;
			printf("SQL query BEZEICHNUNG done with status %d and rowcnt %d\n", status, anz);
			if (status != (int)MPOK)
				return status;

			/* ------ delete texte ------ */
			status = MPC_delete_bezeichnung(Pprogramm[i].bez_id, _PROGRAMM);
			if (status != (int)MPOK)
				return status;

			/* ------ put bezeichnung ------ */
			status = MPC_put_bezeichnung(Pbezeichnung, anz);
			if (status != (int)MPOK)
				return status;
		}
	}

	return status;
}


/*SF**********************************************************
 * Function: MPC_texte_bez_dienstleistung
 * Return:   status
 *************************************************************/
static int MPC_texte_bez_dienstleistung(DIENSTLEISTUNG *Pdienstleistung,
                                        int row_cnt)
{
	TEXTE			*Ptexte;
	BEZEICHNUNG	*Pbezeichnung;
	MEMOBJ		sqlmem;
	char			query[_QUERYLEN];
	int			status=(int)MPOK;
	int			i, a, anz, found, id;

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ TEXTE ------ */
	for (i = 0; i < row_cnt; i++) {
		id = Pdienstleistung[i].textid;
		found = 0;
		for (a = 0; a < i; a++) {
			if (Pdienstleistung[a].textid = id) {
				found = 1;
				break;
			}
		}
		/* ------ id wurde noch nicht verarbeitet ------ */
		if (found == 0) {
			/* ------ select the data ------ */
			(void)printf("start SQL query\n");
			(void)sprintf(query, _SELECT_TEXTE, Pdienstleistung[i].textid,
			                                    _DIENSTLEISTUNG);
			status = MPAPIdb_sqlquery((int)_TEXTE, &sqlmem.buffer, query,
			                          &anz, &sqlmem.datalen, &sqlmem.alloclen);
			Ptexte = (TEXTE *)sqlmem.buffer;
			printf("SQL query TEXTE done with status %d and rowcnt %d\n", status, anz);
			if (status != (int)MPOK)
				return status;

			/* ------ delete texte ------ */
			status = MPC_delete_texte(Pdienstleistung[i].textid, _DIENSTLEISTUNG);
			if (status != (int)MPOK)
				return status;

			/* ------ put texte ------ */
			status = MPC_put_texte(Ptexte, anz);
			if (status != (int)MPOK)
				return status;
		} 
	}

	/* ------ BEZEICHNUNG ------ */
	for (i = 0; i < row_cnt; i++) {
		id = Pdienstleistung[i].bez_id;
		found = 0;
		for (a = 0; a < i; a++) {
			if (Pdienstleistung[a].bez_id = id) {
				found = 1;
				break;
			}
		}
		if (found == 0) {
			/* ------ select the data ------ */
			(void)printf("start SQL query\n");
			(void)sprintf(query, _SELECT_BEZEICHNUNG, Pdienstleistung[i].bez_id,
			                                          _DIENSTLEISTUNG);
			status = MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, query,
			                          &anz, &sqlmem.datalen, &sqlmem.alloclen);
			Pbezeichnung = (BEZEICHNUNG *)sqlmem.buffer;
			printf("SQL query BEZEICHNUNG done with status %d and rowcnt %d\n", status, anz);
			if (status != (int)MPOK)
				return status;

			/* ------ delete texte ------ */
			status = MPC_delete_bezeichnung(Pdienstleistung[i].bez_id,
			                                _DIENSTLEISTUNG);
			if (status != (int)MPOK)
				return status;

			/* ------ put bezeichnung ------ */
			status = MPC_put_bezeichnung(Pbezeichnung, anz);
			if (status != (int)MPOK)
				return status;
		}
	}

	return status;
}


/*SF**********************************************************
 * Function: MPC_texte_bez_dlg_parts
 * Return:   status
 *************************************************************/
static int MPC_texte_bez_dlg_parts(DLG_PART *Pdlg_parts, int row_cnt)
{
	TEXTE			*Ptexte;
	BEZEICHNUNG	*Pbezeichnung;
	MEMOBJ		sqlmem;
	char			query[_QUERYLEN];
	int			status=(int)MPOK;
	int			i, a, anz, found, id;

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ TEXTE ------ */
	for (i = 0; i < row_cnt; i++) {
		id = Pdlg_parts[i].textid;
		found = 0;
		for (a = 0; a < i; a++) {
			if (Pdlg_parts[a].textid = id) {
				found = 1;
				break;
			}
		}
		/* ------ id wurde noch nicht verarbeitet ------ */
		if (found == 0) {
			/* ------ select the data ------ */
			(void)printf("start SQL query\n");
			(void)sprintf(query, _SELECT_TEXTE, Pdlg_parts[i].textid,
			                                    _DLG_PART);
			status = MPAPIdb_sqlquery((int)_TEXTE, &sqlmem.buffer, query,
			                          &anz, &sqlmem.datalen, &sqlmem.alloclen);
			Ptexte = (TEXTE *)sqlmem.buffer;
			printf("SQL query TEXTE done with status %d and rowcnt %d\n", status, anz);
			if (status != (int)MPOK)
				return status;

			/* ------ delete texte ------ */
			status = MPC_delete_texte(Pdlg_parts[i].textid, _DLG_PART);
			if (status != (int)MPOK)
				return status;

			/* ------ put texte ------ */
			status = MPC_put_texte(Ptexte, anz);
			if (status != (int)MPOK)
				return status;
		} 
	}

	/* ------ BEZEICHNUNG ------ */
	for (i = 0; i < row_cnt; i++) {
		id = Pdlg_parts[i].bez_id;
		found = 0;
		for (a = 0; a < i; a++) {
			if (Pdlg_parts[a].bez_id = id) {
				found = 1;
				break;
			}
		}
		if (found == 0) {
			/* ------ select the data ------ */
			(void)printf("start SQL query\n");
			(void)sprintf(query, _SELECT_BEZEICHNUNG, Pdlg_parts[i].bez_id,
			                                          _DLG_PART);
			status = MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, query,
			                          &anz, &sqlmem.datalen, &sqlmem.alloclen);
			Pbezeichnung = (BEZEICHNUNG *)sqlmem.buffer;
			printf("SQL query BEZEICHNUNG done with status %d and rowcnt %d\n", status, anz);
			if (status != (int)MPOK)
				return status;

			/* ------ delete texte ------ */
			status = MPC_delete_bezeichnung(Pdlg_parts[i].bez_id, _DLG_PART);
			if (status != (int)MPOK)
				return status;

			/* ------ put bezeichnung ------ */
			status = MPC_put_bezeichnung(Pbezeichnung, anz);
			if (status != (int)MPOK)
				return status;
		}
	}

	return status;
}


/*SF**********************************************************
 * Function: MPC_texte_bez_saison
 * Return:   status
 *************************************************************/
static int MPC_texte_bez_saison(SAISON *Psaison, int row_cnt)
{
	TEXTE			*Ptexte;
	BEZEICHNUNG	*Pbezeichnung;
	MEMOBJ		sqlmem;
	char			query[_QUERYLEN];
	int			status=(int)MPOK;
	int			i, a, anz, found, id;

	/* SQL Memorypointer auf NULL initialisieren und sonstiges init */
	sqlmem.buffer   = NULL;
	sqlmem.alloclen = 0;
	sqlmem.datalen  = 0;

	/* ------ TEXTE ------ */
	for (i = 0; i < row_cnt; i++) {
		id = Psaison[i].textid;
		found = 0;
		for (a = 0; a < i; a++) {
			if (Psaison[a].textid = id) {
				found = 1;
				break;
			}
		}
		/* ------ id wurde noch nicht verarbeitet ------ */
		if (found == 0) {
			/* ------ select the data ------ */
			(void)printf("start SQL query\n");
			(void)sprintf(query, _SELECT_TEXTE, Psaison[i].textid,
			                                    _SAISON);
			status = MPAPIdb_sqlquery((int)_TEXTE, &sqlmem.buffer, query,
			                          &anz, &sqlmem.datalen, &sqlmem.alloclen);
			Ptexte = (TEXTE *)sqlmem.buffer;
			printf("SQL query TEXTE done with status %d and rowcnt %d\n", status, anz);
			if (status != (int)MPOK)
				return status;

			/* ------ delete texte ------ */
			status = MPC_delete_texte(Psaison[i].textid, _SAISON);
			if (status != (int)MPOK)
				return status;

			/* ------ put texte ------ */
			status = MPC_put_texte(Ptexte, anz);
			if (status != (int)MPOK)
				return status;
		} 
	}

	/* ------ BEZEICHNUNG ------ */
	for (i = 0; i < row_cnt; i++) {
		id = Psaison[i].bez_id;
		found = 0;
		for (a = 0; a < i; a++) {
			if (Psaison[a].bez_id = id) {
				found = 1;
				break;
			}
		}
		if (found == 0) {
			/* ------ select the data ------ */
			(void)printf("start SQL query\n");
			(void)sprintf(query, _SELECT_BEZEICHNUNG, Psaison[i].bez_id,
			                                          _SAISON);
			status = MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, query,
			                          &anz, &sqlmem.datalen, &sqlmem.alloclen);
			Pbezeichnung = (BEZEICHNUNG *)sqlmem.buffer;
			printf("SQL query BEZEICHNUNG done with status %d and rowcnt %d\n", status, anz);
			if (status != (int)MPOK)
				return status;

			/* ------ delete texte ------ */
			status = MPC_delete_bezeichnung(Psaison[i].bez_id, _SAISON);
			if (status != (int)MPOK)
				return status;

			/* ------ put bezeichnung ------ */
			status = MPC_put_bezeichnung(Pbezeichnung, anz);
			if (status != (int)MPOK)
				return status;
		}
	}

	return status;
}
