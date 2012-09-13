delete from regions;
commit work;
delete from graform;
commit work;
delete from graphik;
commit work;
delete from bezeichnung where bez_id > 0 and typ = 46;
commit work;
