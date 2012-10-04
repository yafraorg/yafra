/* drop any old database first */
DROP SCHEMA if exists yafra;

/* use the newly created database now */
/* create database root DEFAULT CHARACTER SET utf8; for UTF8 support */
create database yafra;
use yafra;
commit;

/* create root user */
grant all privileges on yafra.* to 'yafraadmin' identified by 'yafraadmin' with grant option;
/*grant all privileges on yafra.* to 'yafraadmin@% localhost' identified by 'yafraadmin' with grant option;*/
commit;

/* create roles */

/* add members to the roles */
