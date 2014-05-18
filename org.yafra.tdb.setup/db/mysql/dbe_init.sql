/* drop any old database first */
DROP DATABASE if exists tdbadmin;
GRANT USAGE ON *.* TO 'tdbadmin'@'localhost';
drop user 'tdbadmin'@'localhost';
GRANT USAGE ON *.* TO 'tdbadmin'@'127.0.0.1';
drop user 'tdbadmin'@'127.0.0.1';
GRANT USAGE ON *.* TO 'tdbadmin'@'192.168.%.%';
drop user 'tdbadmin'@'192.168.%.%';
commit;

/* create users */
CREATE USER 'tdbadmin'@'localhost' IDENTIFIED BY  'yafra';
CREATE USER 'tdbadmin'@'127.0.0.1' IDENTIFIED BY  'yafra';
CREATE USER 'tdbadmin'@'192.168.%.%' IDENTIFIED BY  'yafra';
commit;

/* use the newly created database now */
/* create database tdbadmin DEFAULT CHARACTER SET utf8; for UTF8 support */
create database tdbadmin;
use tdbadmin;
commit;

/* create users */
GRANT ALL PRIVILEGES ON tdbadmin. * TO  'tdbadmin'@'localhost';
GRANT ALL PRIVILEGES ON tdbadmin. * TO  'tdbadmin'@'127.0.0.1';
GRANT ALL PRIVILEGES ON tdbadmin. * TO  'tdbadmin'@'192.168.%.%';
commit;
