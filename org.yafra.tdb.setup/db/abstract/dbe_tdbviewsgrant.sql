/*D************************************************************/
/* project:   travelDB                                        */
/*                                                            */
/*            grant for tdb views                             */
/*                                                            */
/* copyright: yafra.org, 2003, Switzerland                    */
/**************************************************************/
/* RCS Information: */
/* $Header: /yafra/cvsroot/mapo/db/abstract/dbe_tdbviewsgrant.sql,v 1.3 2004-03-28 22:27:39 mwn Exp $ */

/* groups */
/* mpadmin for _SECLEVEL_ADMIN         */
/* mpuser for _SECLEVEL_USER         */
/* mpbooker for _SECLEVEL_BOOKING   */
/* mpreadonly for _SECLEVEL_READONLY */

grant select on tdbadmin.tdbv_langsel to mpadmin;
grant select on tdbadmin.tdbv_langsel to mpuser;
grant select on tdbadmin.tdbv_langsel to mpbooker;
grant select on tdbadmin.tdbv_langsel to mpreadonly;

grant select on tdbadmin.tdbv_lang to mpadmin;
grant select on tdbadmin.tdbv_lang to mpuser;
grant select on tdbadmin.tdbv_lang to mpbooker;
grant select on tdbadmin.tdbv_lang to mpreadonly;

grant select on tdbadmin.tdbv_stasel to mpadmin;
grant select on tdbadmin.tdbv_stasel to mpuser;
grant select on tdbadmin.tdbv_stasel to mpbooker;
grant select on tdbadmin.tdbv_stasel to mpreadonly;

grant select on tdbadmin.tdbv_sta to mpadmin;
grant select on tdbadmin.tdbv_sta to mpuser;
grant select on tdbadmin.tdbv_sta to mpbooker;
grant select on tdbadmin.tdbv_sta to mpreadonly;

grant select on tdbadmin.tdbv_saisel to mpadmin;
grant select on tdbadmin.tdbv_saisel to mpuser;
grant select on tdbadmin.tdbv_saisel to mpbooker;
grant select on tdbadmin.tdbv_saisel to mpreadonly;

grant select on tdbadmin.tdbv_sai to mpadmin;
grant select on tdbadmin.tdbv_sai to mpuser;
grant select on tdbadmin.tdbv_sai to mpbooker;
grant select on tdbadmin.tdbv_sai to mpreadonly;

grant select on tdbadmin.tdbv_countrysel to mpadmin;
grant select on tdbadmin.tdbv_countrysel to mpuser;
grant select on tdbadmin.tdbv_countrysel to mpbooker;
grant select on tdbadmin.tdbv_countrysel to mpreadonly;

grant select on tdbadmin.tdbv_country to mpadmin;
grant select on tdbadmin.tdbv_country to mpuser;
grant select on tdbadmin.tdbv_country to mpbooker;
grant select on tdbadmin.tdbv_country to mpreadonly;

grant select on tdbadmin.tdbv_countryd to mpadmin;
grant select on tdbadmin.tdbv_countryd to mpuser;
grant select on tdbadmin.tdbv_countryd to mpbooker;
grant select on tdbadmin.tdbv_countryd to mpreadonly;

grant select on tdbadmin.tdbv_citysel to mpadmin;
grant select on tdbadmin.tdbv_citysel to mpuser;
grant select on tdbadmin.tdbv_citysel to mpbooker;
grant select on tdbadmin.tdbv_citysel to mpreadonly;

grant select on tdbadmin.tdbv_city to mpadmin;
grant select on tdbadmin.tdbv_city to mpuser;
grant select on tdbadmin.tdbv_city to mpbooker;
grant select on tdbadmin.tdbv_city to mpreadonly;

grant select on tdbadmin.tdbv_cursel to mpadmin;
grant select on tdbadmin.tdbv_cursel to mpuser;
grant select on tdbadmin.tdbv_cursel to mpbooker;
grant select on tdbadmin.tdbv_cursel to mpreadonly;

grant select on tdbadmin.tdbv_cur to mpadmin;
grant select on tdbadmin.tdbv_cur to mpuser;
grant select on tdbadmin.tdbv_cur to mpbooker;
grant select on tdbadmin.tdbv_cur to mpreadonly;

grant select on tdbadmin.tdbv_ratesel to mpadmin;
grant select on tdbadmin.tdbv_ratesel to mpuser;
grant select on tdbadmin.tdbv_ratesel to mpbooker;
grant select on tdbadmin.tdbv_ratesel to mpreadonly;

grant select on tdbadmin.tdbv_countrylang to mpadmin;
grant select on tdbadmin.tdbv_countrylang to mpuser;
grant select on tdbadmin.tdbv_countrylang to mpbooker;
grant select on tdbadmin.tdbv_countrylang to mpreadonly;

grant select on tdbadmin.tdbv_user to mpadmin;
grant select on tdbadmin.tdbv_user to mpuser;
grant select on tdbadmin.tdbv_user to mpbooker;
grant select on tdbadmin.tdbv_user to mpreadonly;

grant select on tdbadmin.tdbv_perstsel to mpadmin;
grant select on tdbadmin.tdbv_perstsel to mpuser;
grant select on tdbadmin.tdbv_perstsel to mpbooker;
grant select on tdbadmin.tdbv_perstsel to mpreadonly;

grant select on tdbadmin.tdbv_perst to mpadmin;
grant select on tdbadmin.tdbv_perst to mpuser;
grant select on tdbadmin.tdbv_perst to mpbooker;
grant select on tdbadmin.tdbv_perst to mpreadonly;

grant select on tdbadmin.tdbv_cuttsel to mpadmin;
grant select on tdbadmin.tdbv_cuttsel to mpuser;
grant select on tdbadmin.tdbv_cuttsel to mpbooker;
grant select on tdbadmin.tdbv_cuttsel to mpreadonly;

grant select on tdbadmin.tdbv_cutt to mpadmin;
grant select on tdbadmin.tdbv_cutt to mpuser;
grant select on tdbadmin.tdbv_cutt to mpbooker;
grant select on tdbadmin.tdbv_cutt to mpreadonly;

grant select on tdbadmin.tdbv_grptsel to mpadmin;
grant select on tdbadmin.tdbv_grptsel to mpuser;
grant select on tdbadmin.tdbv_grptsel to mpbooker;
grant select on tdbadmin.tdbv_grptsel to mpreadonly;

grant select on tdbadmin.tdbv_grpt to mpadmin;
grant select on tdbadmin.tdbv_grpt to mpuser;
grant select on tdbadmin.tdbv_grpt to mpbooker;
grant select on tdbadmin.tdbv_grpt to mpreadonly;

grant select on tdbadmin.tdbv_perssel to mpadmin;
grant select on tdbadmin.tdbv_perssel to mpuser;
grant select on tdbadmin.tdbv_perssel to mpbooker;
grant select on tdbadmin.tdbv_perssel to mpreadonly;

grant select on tdbadmin.tdbv_pers to mpadmin;
grant select on tdbadmin.tdbv_pers to mpuser;
grant select on tdbadmin.tdbv_pers to mpbooker;
grant select on tdbadmin.tdbv_pers to mpreadonly;

grant select on tdbadmin.tdbv_persadr to mpadmin;
grant select on tdbadmin.tdbv_persadr to mpuser;
grant select on tdbadmin.tdbv_persadr to mpbooker;
grant select on tdbadmin.tdbv_persadr to mpreadonly;

grant select on tdbadmin.tdbv_custsel to mpadmin;
grant select on tdbadmin.tdbv_custsel to mpuser;
grant select on tdbadmin.tdbv_custsel to mpbooker;
grant select on tdbadmin.tdbv_custsel to mpreadonly;

grant select on tdbadmin.tdbv_cust to mpadmin;
grant select on tdbadmin.tdbv_cust to mpuser;
grant select on tdbadmin.tdbv_cust to mpbooker;
grant select on tdbadmin.tdbv_cust to mpreadonly;

grant select on tdbadmin.tdbv_custadr to mpadmin;
grant select on tdbadmin.tdbv_custadr to mpuser;
grant select on tdbadmin.tdbv_custadr to mpbooker;
grant select on tdbadmin.tdbv_custadr to mpreadonly;

grant select on tdbadmin.tdbv_adr to mpadmin;
grant select on tdbadmin.tdbv_adr to mpuser;
grant select on tdbadmin.tdbv_adr to mpbooker;
grant select on tdbadmin.tdbv_adr to mpreadonly;



grant select on tdbadmin.tdbv_dlttsel to mpadmin;
grant select on tdbadmin.tdbv_dlttsel to mpuser;
grant select on tdbadmin.tdbv_dlttsel to mpbooker;
grant select on tdbadmin.tdbv_dlttsel to mpreadonly;

grant select on tdbadmin.tdbv_dltt to mpadmin;
grant select on tdbadmin.tdbv_dltt to mpuser;
grant select on tdbadmin.tdbv_dltt to mpbooker;
grant select on tdbadmin.tdbv_dltt to mpreadonly;

grant select on tdbadmin.tdbv_dltttree to mpadmin;
grant select on tdbadmin.tdbv_dltttree to mpuser;
grant select on tdbadmin.tdbv_dltttree to mpbooker;
grant select on tdbadmin.tdbv_dltttree to mpreadonly;

grant select on tdbadmin.tdbv_catsel to mpadmin;
grant select on tdbadmin.tdbv_catsel to mpuser;
grant select on tdbadmin.tdbv_catsel to mpbooker;
grant select on tdbadmin.tdbv_catsel to mpreadonly;

grant select on tdbadmin.tdbv_cat to mpadmin;
grant select on tdbadmin.tdbv_cat to mpuser;
grant select on tdbadmin.tdbv_cat to mpbooker;
grant select on tdbadmin.tdbv_cat to mpreadonly;

grant select on tdbadmin.tdbv_cattree to mpadmin;
grant select on tdbadmin.tdbv_cattree to mpuser;
grant select on tdbadmin.tdbv_cattree to mpbooker;
grant select on tdbadmin.tdbv_cattree to mpreadonly;

grant select on tdbadmin.tdbv_dltsel to mpadmin;
grant select on tdbadmin.tdbv_dltsel to mpuser;
grant select on tdbadmin.tdbv_dltsel to mpbooker;
grant select on tdbadmin.tdbv_dltsel to mpreadonly;

grant select on tdbadmin.tdbv_dlt to mpadmin;
grant select on tdbadmin.tdbv_dlt to mpuser;
grant select on tdbadmin.tdbv_dlt to mpbooker;
grant select on tdbadmin.tdbv_dlt to mpreadonly;

grant select on tdbadmin.tdbv_dlttree to mpadmin;
grant select on tdbadmin.tdbv_dlttree to mpuser;
grant select on tdbadmin.tdbv_dlttree to mpbooker;
grant select on tdbadmin.tdbv_dlttree to mpreadonly;

grant select on tdbadmin.tdbv_dltoperator to mpadmin;
grant select on tdbadmin.tdbv_dltoperator to mpuser;
grant select on tdbadmin.tdbv_dltoperator to mpbooker;
grant select on tdbadmin.tdbv_dltoperator to mpreadonly;

grant select on tdbadmin.tdbv_acttsel to mpadmin;
grant select on tdbadmin.tdbv_acttsel to mpuser;
grant select on tdbadmin.tdbv_acttsel to mpbooker;
grant select on tdbadmin.tdbv_acttsel to mpreadonly;

grant select on tdbadmin.tdbv_actt to mpadmin;
grant select on tdbadmin.tdbv_actt to mpuser;
grant select on tdbadmin.tdbv_actt to mpbooker;
grant select on tdbadmin.tdbv_actt to mpreadonly;

grant select on tdbadmin.tdbv_actpara to mpadmin;
grant select on tdbadmin.tdbv_actpara to mpuser;
grant select on tdbadmin.tdbv_actpara to mpbooker;
grant select on tdbadmin.tdbv_actpara to mpreadonly;

grant select on tdbadmin.tdbv_actsel to mpadmin;
grant select on tdbadmin.tdbv_actsel to mpuser;
grant select on tdbadmin.tdbv_actsel to mpbooker;
grant select on tdbadmin.tdbv_actsel to mpreadonly;

grant select on tdbadmin.tdbv_act to mpadmin;
grant select on tdbadmin.tdbv_act to mpuser;
grant select on tdbadmin.tdbv_act to mpbooker;
grant select on tdbadmin.tdbv_act to mpreadonly;

grant select on tdbadmin.tdbv_actgrp to mpadmin;
grant select on tdbadmin.tdbv_actgrp to mpuser;
grant select on tdbadmin.tdbv_actgrp to mpbooker;
grant select on tdbadmin.tdbv_actgrp to mpreadonly;

grant select on tdbadmin.tdbv_otsel to mpadmin;
grant select on tdbadmin.tdbv_otsel to mpuser;
grant select on tdbadmin.tdbv_otsel to mpbooker;
grant select on tdbadmin.tdbv_otsel to mpreadonly;

grant select on tdbadmin.tdbv_ot to mpadmin;
grant select on tdbadmin.tdbv_ot to mpuser;
grant select on tdbadmin.tdbv_ot to mpbooker;
grant select on tdbadmin.tdbv_ot to mpreadonly;

grant select on tdbadmin.tdbv_osel to mpadmin;
grant select on tdbadmin.tdbv_osel to mpuser;
grant select on tdbadmin.tdbv_osel to mpbooker;
grant select on tdbadmin.tdbv_osel to mpreadonly;

grant select on tdbadmin.tdbv_o to mpadmin;
grant select on tdbadmin.tdbv_o to mpuser;
grant select on tdbadmin.tdbv_o to mpbooker;
grant select on tdbadmin.tdbv_o to mpreadonly;

grant select on tdbadmin.tdbv_sosel to mpadmin;
grant select on tdbadmin.tdbv_sosel to mpuser;
grant select on tdbadmin.tdbv_sosel to mpbooker;
grant select on tdbadmin.tdbv_sosel to mpreadonly;

grant select on tdbadmin.tdbv_so to mpadmin;
grant select on tdbadmin.tdbv_so to mpuser;
grant select on tdbadmin.tdbv_so to mpbooker;
grant select on tdbadmin.tdbv_so to mpreadonly;

grant select on tdbadmin.tdbv_servsel to mpadmin;
grant select on tdbadmin.tdbv_servsel to mpuser;
grant select on tdbadmin.tdbv_servsel to mpbooker;
grant select on tdbadmin.tdbv_servsel to mpreadonly;

grant select on tdbadmin.tdbv_serv to mpadmin;
grant select on tdbadmin.tdbv_serv to mpuser;
grant select on tdbadmin.tdbv_serv to mpbooker;
grant select on tdbadmin.tdbv_serv to mpreadonly;

grant select on tdbadmin.tdbv_prgsel to mpadmin;
grant select on tdbadmin.tdbv_prgsel to mpuser;
grant select on tdbadmin.tdbv_prgsel to mpbooker;
grant select on tdbadmin.tdbv_prgsel to mpreadonly;

grant select on tdbadmin.tdbv_prg to mpadmin;
grant select on tdbadmin.tdbv_prg to mpuser;
grant select on tdbadmin.tdbv_prg to mpbooker;
grant select on tdbadmin.tdbv_prg to mpreadonly;

grant select on tdbadmin.tdbv_arrsel to mpadmin;
grant select on tdbadmin.tdbv_arrsel to mpuser;
grant select on tdbadmin.tdbv_arrsel to mpbooker;
grant select on tdbadmin.tdbv_arrsel to mpreadonly;

grant select on tdbadmin.tdbv_arr to mpadmin;
grant select on tdbadmin.tdbv_arr to mpuser;
grant select on tdbadmin.tdbv_arr to mpbooker;
grant select on tdbadmin.tdbv_arr to mpreadonly;


grant select on tdbadmin.tdbv_prt to mpadmin;
grant select on tdbadmin.tdbv_prt to mpuser;
grant select on tdbadmin.tdbv_prt to mpbooker;
grant select on tdbadmin.tdbv_prt to mpreadonly;

grant select on tdbadmin.tdbv_prtsel to mpadmin;
grant select on tdbadmin.tdbv_prtsel to mpuser;
grant select on tdbadmin.tdbv_prtsel to mpbooker;
grant select on tdbadmin.tdbv_prtsel to mpreadonly;








grant EXECUTE on tdbadmin.tdb_insprof to mpadmin;
grant EXECUTE on tdbadmin.tdb_insprof to mpuser;
grant EXECUTE on tdbadmin.tdb_insprof to mpbooker;
grant EXECUTE on tdbadmin.tdb_insprof to mpreadonly;

grant EXECUTE on tdbadmin.tdb_updprof to mpadmin;
grant EXECUTE on tdbadmin.tdb_updprof to mpuser;
grant EXECUTE on tdbadmin.tdb_updprof to mpbooker;
grant EXECUTE on tdbadmin.tdb_updprof to mpreadonly;

grant EXECUTE on tdbadmin.tdb_delprof to mpadmin;
grant EXECUTE on tdbadmin.tdb_delprof to mpuser;
grant EXECUTE on tdbadmin.tdb_delprof to mpbooker;
grant EXECUTE on tdbadmin.tdb_delprof to mpreadonly;
