/* buchungen mit komm_detail */
select a.KOMM_ID, a.bid
from   kommission  k,
       komm_detail a,
       buchung      b
where  a.bid      = b.bid
and    b.sai_id   = 3
and    k.komm_id  = a.komm_id
and    k.sai_id  != 3
/

/* host_kont mit kontingent */
select h.SAI_ID, k.sai_id, h.HOSTKONT_ID, k.KONT_ID
from   host_kont  h,
       kontingent k
where  h.HOSTKONT_ID = k.HOSTKONT_ID
and    h.sai_id     != 3
and    k.sai_id     != 3
/

/* host_kont mit kont_detail */
select h.SAI_ID, k.HOSTKONT_ID, k.KONT_ID
from   host_kont h, kont_detail k
where  h.HOSTKONT_ID = k.HOSTKONT_ID
and    h.sai_id     != 3
/
