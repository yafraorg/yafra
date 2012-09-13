/*D********************************/
/* Default:   Aktion MANIFEST     */
/* Copyright: yafra.org    */
/*            Switzerland, 2002   */
/**********************************/

delete from aktionstexte where typ = 1007 and s_id = 1;

insert into aktionstexte values (1, 1, 1, 'lp -onb -oc -olandscape', 1007);
commit work;
