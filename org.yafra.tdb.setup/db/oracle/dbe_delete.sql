/*D************************************************************/ 
/* project:   travelDB                                        */ 
/* client:    DEMONSTRATION                                   */
/*                                                            */ 
/* DBMS:      ORACLE                                          */ 
/*            drop root schema                                */ 
/*                                                            */ 
/* copyright: yafra.org, Switzerland                          */ 
/**************************************************************/ 
 
 /* RCS Information: */ /* $Header: /yafra/cvsroot/mapo/db/oracle/dbe_delete.sql,v 1.1 2005-03-08 21:52:16 mwn Exp $ */  
 
/* drop users and roles */
drop user tdbadmin cascade;
drop role mpadmin;
drop role mpuser;
drop role mpbooker;
drop role mpreadonly;
drop profile tdbprof cascade;

commit work;


