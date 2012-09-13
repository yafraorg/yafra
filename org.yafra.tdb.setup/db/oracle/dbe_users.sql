/*D************************************************************/ 
/* project:   travelDB                                        */ 
/*                                                            */ 
/* DBMS:      ORACLE                                          */ 
/*            create users and roles                          */ 
/*                                                            */ 
/* copyright: yafra.org, 2005, Switzerlan d                   */ 
/**************************************************************/ 
 
/* RCS Information: */ /* $Header: /yafra/cvsroot/mapo/db/oracle/dbe_users.sql,v 1.3 2005-03-11 19:17:46 mwn Exp $ */  
 
/* create role */ 
create role mpadmin; 
grant create session to mpadmin; 
grant connect to mpadmin; 

create role mpuser; 
grant create session to mpuser; 
grant connect to mpuser; 

create role mpbooker; 
grant create session to mpbooker; 
grant connect to mpbooker; 

create role mpreadonly; 
grant create session to mpreadonly; 
grant connect to mpreadonly;  

/* create a tdb profile */ 
create profile tdbprof limit sessions_per_user unlimited;  

/* create users */ 
create user tdbadmin identified by tdbadmin profile tdbprof;
grant dba to tdbadmin;

commit work;