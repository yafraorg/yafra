/* use the newly created database now */
/* create database root DEFAULT CHARACTER SET utf8; for UTF8 support */
create database tdbadmin;
use tdbadmin;
commit;

/* create root user */
grant all privileges on tdbadmin.* to 'tdbadmin@%' identified by 'tdbadmin' with grant option;
commit;

/* create roles */

/* add members to the roles */
