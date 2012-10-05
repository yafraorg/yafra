/* drop any old database first */
DROP DATABASE if exists tdbadmin;
drop user 'tdbadmin'@'localhost';
drop user 'tdbadmin'@'192.168.%.%';
commit;

/* create users */
CREATE USER 'tdbadmin'@'localhost' IDENTIFIED BY  'yafra';
CREATE USER 'tdbadmin'@'192.168.%.%' IDENTIFIED BY  'yafra';
commit;

/* use the newly created database now */
/* create database tdbadmin DEFAULT CHARACTER SET utf8; for UTF8 support */
create database tdbadmin;
use tdbadmin;
commit;

/* create users */
GRANT ALL PRIVILEGES ON tdbadmin. * TO  'tdbadmin'@'localhost';
GRANT ALL PRIVILEGES ON tdbadmin. * TO  'tdbadmin'@'192.168.%.%';
commit;
