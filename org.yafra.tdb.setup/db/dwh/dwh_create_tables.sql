/* 
 * ED_YES_NO 
 * English Data table for Yes/No values 
 * single table that contain "Yes" and "No" to translate our 0/1 flags 
 */
create table ed_yes_no(
id number(1)  not null,
descr varchar2(10)  not null,
constraint ed_yes_no_pk
primary key(id)
using index
pctfree 10
tablespace system
) tablespace system;
insert into ed_yes_no values (0, 'No');
insert into ed_yes_no values (1, 'Yes');
grant select on ed_yes_no to public;

/* 
 * ED_DATA_LANGUAGE 
 * English Data table for languages used in for data naming in marco polo 
 * single table that contain "Yes" and "No" to translate our 0/1 flags 
 */
create table ed_data_language(
id number not null,
priority number not null,
about varchar2(1000),
constraint ed_data_language_pk
primary key(id)
using index
pctfree 10
tablespace system
)
tablespace system;
insert into ed_data_language values (1,1,'german, used by amexco and for demos');
insert into ed_data_language values (25,2,'english, whished to be used by someone');
insert into ed_data_language values (34,3,'french...');
grant select on dwh.ed_data_language to public;

/* 
 * ET_LANGUAGE
 * English Tool table for Languages 
 * single table that contain the language list 
 */
create table et_language as 
select s.s_id language_id, b.bez language
, s.sysbez shortcut
, decode(s.dialog, 1, 'Yes', 'No') is_dialog_language
, decode(s.output, 1, 'Yes', 'no') is_output_language
, decode(s.gui, 1, 'Yes', 'No') is_interface_language
from root.sprachen s, root.bezeichnung b
where s.bez_id = b.bez_id
and b.typ = 1
and b.s_id = 25;
grant select on dwh.et_language to public;

/* 
 * ET_FOLDER_STATE
 * English Tool table for Folder State 
 * single table that contain the folder state list 
 */
create table et_folder_state as 
select unique s.sta_id state_id
, s.sta shortcut
, b.bez name
, to_char(s.sta_id,'99990') || ' - ' || b.bez state
from root.bezeichnung b, root.status_werte s
where b.s_id = 25
and b.typ  in (1108, 1112) 
and s.typ  = b.typ 
and b.bez_id = s.bez_id
and s.sta_id > 0;
grant select on dwh.et_folder_state to public;

/* 
 * EM_CLIENT
 * English Main table for Clients 
 * important table that contain all infos about clients 
 */
create table em_client as
select unique p.pers_id person_id
, nvl(ptype.bez, null) person_type
, nvl(ctypedesc.bez, null) client_type
, p.name name
, nvl(lang.bez, null) language
, nvl(curr.krzl, null) currency_code
, nvl(currdesc.bez, null) currency
, k.konto account
, k.leiter leiter_id
, k.attr1 code, k.attr2 attribute
, nvl(atype.bez, null) address_type
, a.ans title, a.adr1 address_1, a.adr2 address_2, a.adr3 address_3
, a.PLZ ZIP, a.ort city, a.kant state   
, nvl(coun.krzl, null) country_code, nvl(coundesc.bez, null) country
, nvl(stype.bez, null) sending_mode
, k.tel phone, k.fax fax, k.handy mobile, k.tlx telex, k.email email, k.web web
, a.tel phone_2, a.fax fax_2, a.tlx mobile_2, a.email email_2, a.web web_2
, decode(haupt_flag, 1, 'Yes', 'No') is_main_address
, decode(rch_flag, 1, 'Yes', 'No') is_invoicing_address
, decode(mail_flag, 1, 'Yes', 'No') is_mailing_address
from ed_data_language d
, root.personen p
, root.persadr a
, root.kunden k
, root.bezeichnung ptype
, root.bezeichnung lang
, root.bezeichnung atype
, root.land coun, root.bezeichnung coundesc
, root.bezeichnung stype
, root.kunden_typ ctype, root.bezeichnung ctypedesc
, root.waehrung curr, root.bezeichnung currdesc
where d.priority = 1
and k.pers_id = p.pers_id
and a.pers_id = p.pers_id 
and a.haupt_flag = 1
and atype.bez_id    (+)= a.adr_typ    and atype.bez_id    (+)> 0 and atype.typ    (+)= 1127 and atype.s_id    (+)= 25
and lang.bez_id     (+)= p.s_id       and lang.bez_id     (+)> 0 and lang.typ     (+)= 1    and lang.s_id     (+)= 25
and ptype.bez_id    (+)= p.pers_typ   and ptype.bez_id    (+)> 0 and ptype.typ    (+)= 1104 and ptype.s_id    (+)= 25
and coun.land_id    (+)= a.land_id    and coun.bez_id     (+)> 0
and coundesc.bez_id (+)= coun.bez_id  and coundesc.bez_id (+)> 0 and coundesc.typ (+)= 10   and coundesc.s_id (+)= 25
and stype.bez_id    (+)= a.sta_id     and stype.bez_id    (+)> 0 and stype.typ    (+)= 1111 and stype.s_id    (+)= 25 
and ctype.k_typ_id  (+)= k.k_typ_id   and ctype.k_typ_id  (+)> 0
and ctypedesc.bez_id(+)= ctype.bez_id and ctypedesc.bez_id(+)> 0 and ctypedesc.typ(+)= 24   and ctypedesc.s_id = d.id
and curr.whr_id     (+)= k.whr_id     and curr.whr_id     (+)> 0
and currdesc.bez_id (+)= curr.bez_id  and currdesc.bez_id (+)> 0 and currdesc.typ (+)= 12   and currdesc.s_id (+)= 25;
alter table dwh.em_client add ( 
constraint em_client_pk primary key (person_id) using index tablespace system );
grant select on dwh.em_client to public;

/* 
 * EM_CONTINGENT
 * English Main table for Contingent 
 * important table that contain all infos about contingents 
 */
create table em_contingent as
select h.hostkont_id host_contingent_id, hdesc.bez host_contingent
, s.sai_id season_id, sdesc.bez season
, part.dl_id service_part_id, partdesc.bez service_part
, part.dla_id offer_id
, root.todate(part.a_zeit) starting_date
, root.todate(part.e_zeit) end_date
, kid client_id
, c.kont_id contingent_id, cdesc.bez contingent
, c.ref contingent_reference
, d.kat_id category_id, catdesc.bez category
, d.anz existing_places, d.busy occupied_places, d.minanz minimal_places
from ed_data_language dlang
, root.host_kont h, root.bezeichnung hdesc
, root.saison s, root.bezeichnung sdesc
, root.dlg_parts part, root.bezeichnung partdesc
, root.kontingent c, root.bezeichnung cdesc
, root.kont_detail d
, root.kategorie cat, root.bezeichnung catdesc
where dlang.priority = 1
and d.kont_id = c.kont_id
and d.hostkont_id = -1
and h.hostkont_id = c.hostkont_id
and hdesc.bez_id = h.bez_id       and hdesc.typ = 38    and hdesc.s_id    = dlang.id
and part.dl_id = h.dl_id
and partdesc.bez_id = part.bez_id and partdesc.typ = 26 and partdesc.s_id = dlang.id
and s.sai_id = h.sai_id
and sdesc.bez_id = s.bez_id       and sdesc.typ = 9     and sdesc.s_id    = dlang.id
and cdesc.bez_id = c.bez_id       and cdesc.typ = 39    and cdesc.s_id    = dlang.id
and c.hostkont_id = h.hostkont_id
and cat.kat_id = d.kat_id and d.kat_id > 0
and catdesc.bez_id = cat.bez_id and catdesc.typ = 16    and catdesc.s_id  = dlang.id;
alter table dwh.em_contingent add ( 
constraint em_contingent_pk primary key (contingent_id, category_id) 
using index tablespace system );
alter table em_contingent add
(
  constraint em_contingent_em_client_fk 
  foreign key( client_id)
  references dwh.em_client( person_id)
);
grant select on dwh.em_contingent to public;
