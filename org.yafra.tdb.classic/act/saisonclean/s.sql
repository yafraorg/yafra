select g.dlg_id, d.sai_id
from   dlg_dlg g, DIENSTLEISTUNG d
where  d.sai_id = 3
and    g.dlg_id = d.dlg_id
/
select g.dlg_id, d.sai_id
from   arr_dlg g, DIENSTLEISTUNG d
where  d.sai_id = 3
and    g.dlg_id = d.dlg_id
/
select g.dl_id
from   host_kont g, DIENSTLEISTUNG d
where  d.sai_id = 3
and    g.dl_id = d.dlg_id
/
select g.dlg_id, g.sai_id
from   akt_detail g, DIENSTLEISTUNG d
where  d.sai_id = 3
and    g.dlg_id = d.dlg_id
/
select g.dl_id
from   kommission g, DIENSTLEISTUNG d
where  d.sai_id = 3
and    g.dl_id = d.dlg_id
/
select g.dlg_id
from   reservation g, DIENSTLEISTUNG d
where  d.sai_id = 3
and    g.dlg_id = d.dlg_id
/
select g.dl_id
from   preis g, DIENSTLEISTUNG d
where  d.sai_id = 3
and    g.dl_id = d.dlg_id
/
