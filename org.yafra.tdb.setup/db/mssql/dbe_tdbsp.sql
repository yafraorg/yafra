/*D************************************************************/
/* project:   travelDB stored procedures for DataSet          */
/*            upd/del/ins                                     */
/*            ATTENTION !! types are hardcoded here !!!       */
/*            see tdb_tabletypes.xml                          */
/*                                                            */
/* copyright: yafra.org, Switzerland, 2004                    */
/**************************************************************/
/* RCS Information: */
/* $Header: /yafra/cvstdbadmin/mapo/db/mssql/dbe_tdbsp.sql,v 1.2 2006-01-16 08:11:20 mwn Exp $ */

/* check for mpstadef.h and mpobjdef.h for codes */

-- dltt tree
-- EXEC showdltt 1, 1

DROP PROC tdbadmin.showdltt
GO

CREATE PROC tdbadmin.showdltt
(
	@Root int,
	@sid int
)
AS
BEGIN
	SET NOCOUNT ON
	DECLARE @Dltt int, @Bez varchar(30)

	SET @Bez = (SELECT bez FROM tdbadmin.tdbv_dltt WHERE typ_id = @Root and s_id = @sid)
--	PRINT REPLICATE('-', @@NESTLEVEL * 4) + @Bez
	PRINT CONVERT(varchar(5), @@NESTLEVEL) + @Bez

	SET @Dltt = (SELECT MIN(typ_id) FROM tdbadmin.tdbv_dltt WHERE h_typ_id = @Root and s_id = @sid)

	WHILE @Dltt IS NOT NULL
	BEGIN
		EXEC tdbadmin.showdltt @Dltt, @sid
		SET @Dltt = (SELECT MIN(typ_id) FROM tdbadmin.tdbv_dltt WHERE h_typ_id = @Root AND typ_id > @Dltt and s_id = @sid)
	END
END
GO

-- MP_PROFILE
DROP PROCEDURE tdbadmin.tdb_insprof
GO

CREATE PROCEDURE tdbadmin.tdb_insprof
   (
      @mpid int,
      @mpuser varchar(128),
      @bchst int,
      @seclevel int,
      @s_id int,
      @land_id int,
      @dltt_id int,
      @dlt_id int,
      @kat_id int,
      @dlat_id int,
      @dlnt_id int,
      @sai_id int,
      @prg_id int,
      @azeit int,
      @ezeit int,
      @prange int
   )
AS
	INSERT INTO tdbadmin.mp_profil
		(MPID, MPUSER, BCHST, SECLEVEL, S_ID, LAND_ID, DLTT_ID, DLT_ID, KAT_ID, DLAT_ID,
		 DLNT_ID, SAI_ID, PRG_ID, A_ZEIT, E_ZEIT, P_RANGE)
		VALUES (@mpid, @mpuser, @bchst, @seclevel, @s_id, @land_id, @dltt_id, @dlt_id, @kat_id,
		 @dlat_id, @dlnt_id, @sai_id, @prg_id, @azeit, @ezeit, @prange)
   RETURN
GO

DROP PROCEDURE tdbadmin.tdb_updprof
GO
CREATE PROCEDURE tdbadmin.tdb_updprof
   (
      @mpid int,
      @mpuser varchar(128),
      @bchst int,
      @seclevel int,
      @s_id int,
      @land_id int,
      @dltt_id int,
      @dlt_id int,
      @kat_id int,
      @dlat_id int,
      @dlnt_id int,
      @sai_id int,
      @prg_id int,
      @azeit int,
      @ezeit int,
      @prange int
   )
AS
	UPDATE tdbadmin.mp_profil
		SET MPUSER = @mpuser,
			BCHST = @bchst,
			SECLEVEL = @seclevel,
			S_ID = @s_id,
			LAND_ID = @land_id,
			DLTT_ID = @dltt_id,
			DLT_ID = @dlt_id,
			KAT_ID = @kat_id,
			DLAT_ID = @dlat_id,
			DLNT_ID = @dlnt_id,
			SAI_ID = @sai_id,
			PRG_ID = @prg_id,
			A_ZEIT = @azeit,
			E_ZEIT = @ezeit,
			P_RANGE = @prange
		WHERE (MPID = @mpid)
   RETURN
GO

DROP PROCEDURE tdbadmin.tdb_delprof
GO
CREATE PROCEDURE tdbadmin.tdb_delprof
   (
      @mpid int
   )
AS
	DELETE FROM tdbadmin.mp_profil
		WHERE (MPID = @mpid)
	RETURN
GO