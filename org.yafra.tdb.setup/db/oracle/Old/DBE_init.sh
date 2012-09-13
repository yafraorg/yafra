#!/bin/sh
#
# MARCO POLO TO Classic SQL Data Loader for Oracle
#
# (c) yafra.org, Switzerland, www.pisoag.com

#
# globals
#
SQLPATH=../abstract
SQLLOAD="sqlplus root@weblapi/root"

# init
$SQLLOAD < $SQLPATH/def_mp2000.sql > data.log

# aktionen definition
$SQLLOAD < $SQLPATH/def_d_aktionen.sql >> data.log
$SQLLOAD < $SQLPATH/def_e_aktionen.sql >> data.log

# classic messages
$SQLLOAD < $SQLPATH/def_d_msgakt.sql >> data.log
$SQLLOAD < $SQLPATH/def_d_msgerr.sql >> data.log
$SQLLOAD < $SQLPATH/def_d_msginf.sql >> data.log
$SQLLOAD < $SQLPATH/def_d_msgsql.sql >> data.log
$SQLLOAD < $SQLPATH/def_d_msgsys.sql >> data.log
$SQLLOAD < $SQLPATH/def_d_msgwar.sql >> data.log
$SQLLOAD < $SQLPATH/def_e_msgact.sql >> data.log
$SQLLOAD < $SQLPATH/def_e_msgerr.sql >> data.log
$SQLLOAD < $SQLPATH/def_e_msginf.sql >> data.log
$SQLLOAD < $SQLPATH/def_e_msgsql.sql >> data.log
$SQLLOAD < $SQLPATH/def_e_msgsys.sql >> data.log
$SQLLOAD < $SQLPATH/def_e_msgwar.sql >> data.log

# classic status_werte 
#$SQLLOAD < $SQLPATH/def_d_status.sql >> data.log

# classic output settings
$SQLLOAD < $SQLPATH/out_d_common.sql >> data.log
$SQLLOAD < $SQLPATH/out_d_annulation.sql >> data.log
$SQLLOAD < $SQLPATH/out_d_auftrag.sql >> data.log
$SQLLOAD < $SQLPATH/out_d_control.sql >> data.log
$SQLLOAD < $SQLPATH/out_d_faktura.sql >> data.log
$SQLLOAD < $SQLPATH/out_d_manifest.sql >> data.log
$SQLLOAD < $SQLPATH/out_d_option.sql >> data.log
$SQLLOAD < $SQLPATH/out_d_order.sql >> data.log
$SQLLOAD < $SQLPATH/out_d_passagier.sql >> data.log
$SQLLOAD < $SQLPATH/out_d_paxbus.sql >> data.log
$SQLLOAD < $SQLPATH/out_d_paxdl.sql >> data.log
$SQLLOAD < $SQLPATH/out_d_program.sql >> data.log
$SQLLOAD < $SQLPATH/out_d_request.sql >> data.log
$SQLLOAD < $SQLPATH/out_d_revenu.sql >> data.log
$SQLLOAD < $SQLPATH/out_d_stamm.sql >> data.log
$SQLLOAD < $SQLPATH/out_d_statdlt.sql >> data.log
$SQLLOAD < $SQLPATH/out_d_statistik.sql >> data.log
$SQLLOAD < $SQLPATH/out_d_ticket.sql >> data.log
$SQLLOAD < $SQLPATH/out_d_voucher.sql >> data.log
