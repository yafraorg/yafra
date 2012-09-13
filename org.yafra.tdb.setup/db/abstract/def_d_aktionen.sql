/*D***********************************************************/
/* Default:   AKTIONEN                                       */
/*            Aktions_typ      19                            */
/*            Aktionparameter  20                            */
/*            Aktionen         21                            */
/*            Aktiongruppen    22                            */
/*            Aktionsdetail    38                            */
/*                                                           */
/* Copyright: yafra.org, Switzerland, www.pisoag.com  */
/*************************************************************/

/* Loeschen der bestehenden Daten */
delete from akt_detail;
delete from bezeichnung where typ=38 and bez_id > 0;
delete from aktionspara;
delete from bezeichnung where typ=20 and bez_id > 0;
delete from aktions_typ where a_typ_id > -1;
delete from bezeichnung where typ=19 and bez_id > 0;

/* Einfuegen der neuen Daten */
insert into aktions_typ values (1, 1, 'default virtual action', -1);
insert into bezeichnung values (1, 1, 'Standard Aktion', 19);
insert into bezeichnung values (1, 25, 'standard virtual action', 19);

insert into aktions_typ values (2, 2, 'OUTarrkom', -1);
insert into bezeichnung values (2, 1, 'ADMIN Kommissionen', 19);
insert into bezeichnung values (2, 25, 'ADMIN Kommissionen', 19);
insert into aktionspara values (2, 1, 30, '-a', -1, 0, 0);
insert into aktionspara values (2, 2, -1, '-D', -1, 0, 1);

insert into aktions_typ values (3, 3, 'OUTkapaupdate', -1);
insert into bezeichnung values (3, 1, 'ADMIN Kapazitaet', 19);
insert into bezeichnung values (3, 25, 'ADMIN Kapazitaet', 19);
insert into aktionspara values (3, 1, 23, '-A', -1, 0, 0);
insert into aktionspara values (3, 2, -1, '-D', -1, 0, 1);

insert into aktions_typ values (4, 4, 'OUTpassagier', -1);
insert into bezeichnung values (4, 1, 'Passagierliste PAX', 19);
insert into bezeichnung values (4, 25, 'Passagierliste PAX', 19);
insert into aktions_typ values (5, 5, 'OUTticket', -1);
insert into bezeichnung values (5, 1, 'Ticket', 19);
insert into bezeichnung values (5, 25, 'Ticket', 19);
insert into aktions_typ values (6, 6, 'OUTvoucher', -1);
insert into bezeichnung values (6, 1, 'Voucher', 19);
insert into bezeichnung values (6, 25, 'Voucher', 19);
insert into aktions_typ values (7, 7, 'OUTauftrag', -1);
insert into bezeichnung values (7, 1, 'Auftragsbestaetigung', 19);
insert into bezeichnung values (7, 25, 'Auftragsbestaetigung', 19);
insert into aktions_typ values (8, 8, 'OUTfaktura', -1);
insert into bezeichnung values (8, 1, 'Rechnung/Faktura', 19);
insert into bezeichnung values (8, 25, 'Rechnung/Faktura', 19);
insert into aktions_typ values (9, 9, 'OUTrequest', -1);
insert into bezeichnung values (9, 1, 'Anfrage', 19);
insert into bezeichnung values (9, 25, 'Anfrage', 19);
insert into aktions_typ values (10, 10, 'OUTprogram', -1);
insert into bezeichnung values (10, 1, 'Reiseprogram', 19);
insert into bezeichnung values (10, 25, 'Reiseprogram', 19);

