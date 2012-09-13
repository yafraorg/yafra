/*D************************************************************/
/* project:   travelDB stored procedures for DataSet          */
/*            upd/del/ins                                     */
/*            ATTENTION !! types are hardcoded here !!!       */
/*            see tdb_tabletypes.xml                          */
/*                                                            */
/* copyright: yafra.org, Switzerland, 2004                    */
/**************************************************************/


/* check for mpstadef.h and mpobjdef.h for codes */

-- dltt tree
-- EXEC showdltt 1, 1

DROP PROCEDURE showdltt;
commit;

CREATE PROCEDURE showdltt (@Tdbadmin int, @sid int)
BEGIN
	SET NOCOUNT ON
	DECLARE @Dltt int, @Bez varchar(30)

	SET @Bez = (SELECT bez FROM tdbv_dltt WHERE typ_id = @Tdbadmin and s_id = @sid)
--	PRINT REPLICATE('-', @@NESTLEVEL * 4) + @Bez
	PRINT CONVERT(varchar(5), @@NESTLEVEL) + @Bez

	SET @Dltt = (SELECT MIN(typ_id) FROM tdbv_dltt WHERE h_typ_id = @Tdbadmin and s_id = @sid)

	WHILE @Dltt IS NOT NULL
	BEGIN
		EXEC showdltt @Dltt, @sid
		SET @Dltt = (SELECT MIN(typ_id) FROM tdbv_dltt WHERE h_typ_id = @Tdbadmin AND typ_id > @Dltt and s_id = @sid)
	END
END;
commit;

-- MP_PROFILE
DROP PROCEDURE tdb_insprof
GO

CREATE PROCEDURE tdb_insprof
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

DROP PROCEDURE tdb_updprof
GO
CREATE PROCEDURE tdb_updprof
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

DROP PROCEDURE tdb_delprof
GO
CREATE PROCEDURE tdb_delprof
   (
      @mpid int
   )
AS
	DELETE FROM tdbadmin.mp_profil
		WHERE (MPID = @mpid)
	RETURN
GO