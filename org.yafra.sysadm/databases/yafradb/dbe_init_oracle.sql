/* drop users and roles */
drop user tdbadmin cascade;
drop role mpadmin;
drop role mpuser;
drop role mpbooker;
drop role mpreadonly;
drop profile tdbprof cascade;

commit work;


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