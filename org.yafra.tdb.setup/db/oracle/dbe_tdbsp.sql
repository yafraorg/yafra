/*D************************************************************/
/* project:   travelDB stored procedures for DataSet          */
/*            upd/del/ins                                     */
/*            ATTENTION !! types are hardcoded here !!!       */
/*            see tdb_tabletypes.xml                          */
/*                                                            */
/* copyright: yafra.org, Switzerland, 2004                    */
/**************************************************************/
/* RCS Information: */
/* $Header: /yafra/cvstdbadmin/mapo/db/oracle/dbe_tdbsp.sql,v 1.1 2004-03-28 22:31:53 mwn Exp $ */

/* check for mpstadef.h and mpobjdef.h for codes */

-- //// Insert Stored Procedure.
CREATE OR REPLACE  PROCEDURE "TDBADMIN"."TDB_INSPROF" (
	p_MPID	IN	MP_PROFIL.MPID%TYPE,
	p_MPUSER	IN	MP_PROFIL.MPUSER%TYPE,
	p_BCHST	IN	MP_PROFIL.BCHST%TYPE,
	p_SECLEVEL	IN	MP_PROFIL.SECLEVEL%TYPE,
	p_S_ID	IN	MP_PROFIL.S_ID%TYPE,
	p_LAND_ID	IN	MP_PROFIL.LAND_ID%TYPE,
	p_DLTT_ID	IN	MP_PROFIL.DLTT_ID%TYPE,
	p_DLT_ID	IN	MP_PROFIL.DLT_ID%TYPE,
	p_KAT_ID	IN	MP_PROFIL.KAT_ID%TYPE,
	p_DLAT_ID	IN	MP_PROFIL.DLAT_ID%TYPE,
	p_DLNT_ID	IN	MP_PROFIL.DLNT_ID%TYPE,
	p_SAI_ID	IN	MP_PROFIL.SAI_ID%TYPE,
	p_PRG_ID	IN	MP_PROFIL.PRG_ID%TYPE,
	p_A_ZEIT	IN	MP_PROFIL.A_ZEIT%TYPE,
	p_E_ZEIT	IN	MP_PROFIL.E_ZEIT%TYPE,
	p_P_RANGE	IN	MP_PROFIL.P_RANGE%TYPE
)
AS
BEGIN
	insert into MP_PROFIL
	(
		MPID,
		MPUSER,
		BCHST,
		SECLEVEL,
		S_ID,
		LAND_ID,
		DLTT_ID,
		DLT_ID,
		KAT_ID,
		DLAT_ID,
		DLNT_ID,
		SAI_ID,
		PRG_ID,
		A_ZEIT,
		E_ZEIT,
		P_RANGE
	)
	values
	(
		p_MPID,
		p_MPUSER,
		p_BCHST,
		p_SECLEVEL,
		p_S_ID,
		p_LAND_ID,
		p_DLTT_ID,
		p_DLT_ID,
		p_KAT_ID,
		p_DLAT_ID,
		p_DLNT_ID,
		p_SAI_ID,
		p_PRG_ID,
		p_A_ZEIT,
		p_E_ZEIT,
		p_P_RANGE
	);
END;

-- //// Update Stored Procedure Based On Primary Key.
create or replace PROCEDURE "TDBADMIN"."TDB_UPDPROF"
(
	p_MPID	IN	MP_PROFIL.MPID%TYPE,
	p_MPUSER	IN	MP_PROFIL.MPUSER%TYPE,
	p_BCHST	IN	MP_PROFIL.BCHST%TYPE,
	p_SECLEVEL	IN	MP_PROFIL.SECLEVEL%TYPE,
	p_S_ID	IN	MP_PROFIL.S_ID%TYPE,
	p_LAND_ID	IN	MP_PROFIL.LAND_ID%TYPE,
	p_DLTT_ID	IN	MP_PROFIL.DLTT_ID%TYPE,
	p_DLT_ID	IN	MP_PROFIL.DLT_ID%TYPE,
	p_KAT_ID	IN	MP_PROFIL.KAT_ID%TYPE,
	p_DLAT_ID	IN	MP_PROFIL.DLAT_ID%TYPE,
	p_DLNT_ID	IN	MP_PROFIL.DLNT_ID%TYPE,
	p_SAI_ID	IN	MP_PROFIL.SAI_ID%TYPE,
	p_PRG_ID	IN	MP_PROFIL.PRG_ID%TYPE,
	p_A_ZEIT	IN	MP_PROFIL.A_ZEIT%TYPE,
	p_E_ZEIT	IN	MP_PROFIL.E_ZEIT%TYPE,
	p_P_RANGE	IN	MP_PROFIL.P_RANGE%TYPE
)
AS
BEGIN
	update	MP_PROFIL
		set	MPUSER = p_MPUSER,
			BCHST = p_BCHST,
			SECLEVEL = p_SECLEVEL,
			S_ID = p_S_ID,
			LAND_ID = p_LAND_ID,
			DLTT_ID = p_DLTT_ID,
			DLT_ID = p_DLT_ID,
			KAT_ID = p_KAT_ID,
			DLAT_ID = p_DLAT_ID,
			DLNT_ID = p_DLNT_ID,
			SAI_ID = p_SAI_ID,
			PRG_ID = p_PRG_ID,
			A_ZEIT = p_A_ZEIT,
			E_ZEIT = p_E_ZEIT,
			P_RANGE = p_P_RANGE
	where	MPID = p_MPID;
END;

-- //// Delete Stored Procedure Based On Primary Key.
create or replace PROCEDURE "TDBADMIN"."TDB_DELPROF"
(
	p_MPID	IN	MP_PROFIL.MPID%TYPE
)
AS
BEGIN
	delete from MP_PROFIL
	where  MPID = p_MPID;
END;

COMMIT WORK;