/*D************************************************************/
/* project:   travelDB                                        */
/*                                                            */
/* DBMS:      Oracle PL/SQL                                   */
/*            create function                                 */
/*            ACHTUNG !!! Zum Teil sind Typen hardcoded !!!   */
/*            Abstimmen mit mpobjdef.h                        */
/*                                                            */
/* copyright: yafra.org, Switzerland                          */
/**************************************************************/
/* RCS Information: */
/* $Header: /yafra/cvstdbadmin/mapo/db/mysql/dbe_functions.sql,v 1.1 2008-11-23 15:37:05 mwn Exp $ */
set echo off;
set autocommit off;

/* DATE Function to convert int date (seconds till 1970 to Oracle DATE */
create or replace function todate(n NUMBER) return DATE is
begin
 if ((n = -1) or (n = 0) ) then
  return null;
 end if;
  return (to_date('01.01.1970','dd.mm.yyyy')+n/(3600*24));
 end;
/
show errors function todate

/* function user by amexco to analyze the content of traveler comments */
CREATE OR REPLACE  FUNCTION getcctype   (delimiter VARCHAR2, str VARCHAR2) return VARCHAR2 is
  num_position_delimiter    NUMBER;
  tmp_str VARCHAR2(2000);
begin
  num_position_delimiter := INSTR(str, delimiter);
  IF num_position_delimiter = 0 THEN
    return '';
  ELSE
    tmp_str:=substr(str,num_position_delimiter);
    num_position_delimiter := INSTR(tmp_str, '@@@@');
    if num_position_delimiter != 0 THEN
      tmp_str:= substr(tmp_str,1, num_position_delimiter-1);
    END IF;
    tmp_str:= substr(tmp_str,LENGTH(delimiter)+1);
    return tmp_str;
  END IF;
end;
/
show errors function getcctype

/*function used to get prices */
CREATE OR REPLACE  FUNCTION GETPRICE (iBID NUMBER,
 iPERS_ID NUMBER,
 iTEIL NUMBER) return VARCHAR2 is
  price    VARCHAR2(2000);
begin
 
  
  SELECT DISTINCT p.VPR || ' ' || rtrim(w.KRZL) into price
FROM ( SELECT  r.BID, r.PERS_ID, r.TEIL,
        r.KAT_ID, hp.DL_ID, hp.DLA_ID, hp.A_ZEIT, t.HOST_ID
    FROM  tdbadmin.reservation r,
       tdbadmin.dlg_dlg dd,
       tdbadmin.dlg_parts p,
       tdbadmin.dlg_parts hp,
       tdbadmin.dienst_angebot a,
       tdbadmin.dienst_traeger t
    WHERE dd.DLG_ID = r.dlg_id
    AND dd.DL_ID = p.DL_ID
    AND hp.DL_ID = decode(p.H_DL_ID, -1, p.DL_ID, p.H_DL_ID)
    AND hp.DLA_ID = a.DLA_ID
    AND a.DLT_ID = t.DLT_ID
    AND r.BID = iBID
    AND r.PERS_ID = iPERS_ID
    AND r.TEIL = iTEIL
    ) myd,
    tdbadmin.dienst_traeger t,
    tdbadmin.preis p,
    tdbadmin.waehrung w
WHERE (p.KAT_ID = myd.KAT_ID OR p.KAT_ID = -1)
AND (p.DL_ID = myd.DL_ID OR p.DLA_ID = myd.DLA_ID)
AND p.GLT IN (SELECT max(allp.GLT)
       FROM tdbadmin.preis allp
       WHERE allp.GLT <= myd.A_ZEIT
       AND (allp.KAT_ID = p.KAT_ID OR allp.KAT_ID = -1)
       AND (allp.DL_ID = myd.DL_ID OR allp.DLA_ID = myd.DLA_ID))
AND w.WHR_ID = p.WHR_ID;

 
  return price;
end;
/

CREATE OR REPLACE  FUNCTION "TDBADMIN"."GETPREISID"    (iBID NUMBER,
 iPERS_ID NUMBER,
 iTEIL NUMBER) return NUMBER is
  priceid    NUMBER;
begin

  SELECT DISTINCT p.pre_id  into priceid
FROM ( SELECT  r.BID, r.PERS_ID, r.TEIL,
        r.KAT_ID, hp.DL_ID, hp.DLA_ID, hp.A_ZEIT, t.HOST_ID
    FROM  tdbadmin.reservation r,
       tdbadmin.dlg_dlg dd,
       tdbadmin.dlg_parts p,
       tdbadmin.dlg_parts hp,
       tdbadmin.dienst_angebot a,
       tdbadmin.dienst_traeger t
    WHERE dd.DLG_ID = r.dlg_id
    AND dd.DL_ID = p.DL_ID
    AND hp.DL_ID = decode(p.H_DL_ID, -1, p.DL_ID, p.H_DL_ID)
    AND hp.DLA_ID = a.DLA_ID
    AND a.DLT_ID = t.DLT_ID
    AND r.BID = iBID
    AND r.PERS_ID = iPERS_ID
    AND r.TEIL = iTEIL
    ) myd,
    tdbadmin.dienst_traeger t,
    tdbadmin.preis p,
    tdbadmin.waehrung w
WHERE (p.KAT_ID = myd.KAT_ID OR p.KAT_ID = -1)
AND (p.DL_ID = myd.DL_ID OR p.DLA_ID = myd.DLA_ID)
AND p.GLT IN (SELECT max(allp.GLT)
       FROM tdbadmin.preis allp
       WHERE allp.GLT <= myd.A_ZEIT
       AND (allp.KAT_ID = p.KAT_ID OR allp.KAT_ID = -1)
       AND (allp.DL_ID = myd.DL_ID OR allp.DLA_ID = myd.DLA_ID))
AND w.WHR_ID = p.WHR_ID;


  return priceid;
end;
/


show errors function getprice

CREATE OR REPLACE  FUNCTION "TDBADMIN"."PLACESBOOKED"     (edlt_id  NUMBER, edlg_id NUMBER) return NUMBER is
 tmp NUMBER;
begin

  select count(pers_id) into tmp from tdbadmin.reservation where dlg_id=edlg_id
  and dlt_id=edlt_id ; 
  return tmp;
end;
/
show errors function PLACESBOOKED

CREATE OR REPLACE  FUNCTION "TDBADMIN"."PLACESBOOKEDDETAILS"         (edlt_id  NUMBER, edlg_id NUMBER) return VARCHAR2 is
 tmp NUMBER;
 test varchar2(2000);
 first boolean;
 cursor all_persons (edlt_id_in NUMBER, eldg_id_in NUMBER) is
 select '('||res.bid||') '|| RTRIM(pers.name) name
 from tdbadmin.reservation res,
 tdbadmin.personen pers
 where res.dlg_id=eldg_id_in
 and res.dlt_id=edlt_id_in
 and res.pers_id=pers.pers_id;  
begin
/*
  select pers_id into tmp from tdbadmin.reservation where dlg_id=edlg_id
  and dlt_id=edlt_id ; 
  return tmp;
*/
  first :=true;
  for a_person in all_persons(edlt_id, edlg_id)
  loop
    if first then test:='';
    first:=false;
    else test:=test || chr(10);
    end if;
    test := test || a_person.name;
  end loop;
  return test;
end;
/
show errors function PLACESBOOKEDDETAILS



commit;