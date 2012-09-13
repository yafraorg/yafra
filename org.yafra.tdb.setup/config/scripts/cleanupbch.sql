delete from reservation;
commit work;

delete from akt_detail where a_typ_id=6;
commit work;
delete from akt_detail;
commit work;

delete from komm_detail where bid > 0 or dln_id > 0;
commit work;

delete from bch_dln;
commit work;

delete from reisender where pers_id > 0;
commit work;

delete from personen where pers_typ = 1;
commit work;

delete from buchung where bid > 0;
commit work;
