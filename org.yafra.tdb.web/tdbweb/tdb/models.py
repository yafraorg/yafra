# This is an auto-generated Django model module.
# You'll have to do the following manually to clean this up:
#     * Rearrange models' order
#     * Make sure each model has one field with primary_key=True
# Feel free to rename the models, but don't rename db_table values or field names.
#
# Also note: You'll have to insert the output of 'django-admin.py sqlcustom [appname]'
# into your database.

from django.db import models


class Maxima(models.Model):
    tabelle = models.IntegerField(primary_key=True, db_column='TABELLE') # Field name made lowercase.
    typ = models.IntegerField(primary_key=True, db_column='TYP') # Field name made lowercase.
    max_id = models.IntegerField(null=True, db_column='MAX_ID', blank=True) # Field name made lowercase.
    min_id = models.IntegerField(null=True, db_column='MIN_ID', blank=True) # Field name made lowercase.
    incr = models.IntegerField(null=True, db_column='INCR', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'maxima'

class Sprachen(models.Model):
    s_id = models.IntegerField(unique=True, primary_key=True, db_column='S_ID') # Field name made lowercase.
    bez_id = models.IntegerField(unique=True, db_column='BEZ_ID') # Field name made lowercase.
    dialog = models.IntegerField(db_column='DIALOG') # Field name made lowercase.
    sysbez = models.CharField(max_length=768, db_column='SYSBEZ') # Field name made lowercase.
    output = models.IntegerField(null=True, db_column='OUTPUT', blank=True) # Field name made lowercase.
    gui = models.IntegerField(null=True, db_column='GUI', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'sprachen'

class StatusWerte(models.Model):
    sta_id = models.IntegerField(db_column='STA_ID') # Field name made lowercase.
    abk = models.CharField(max_length=768, db_column='ABK') # Field name made lowercase.
    sta = models.CharField(max_length=3072, db_column='STA') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    kond = models.FloatField(db_column='KOND') # Field name made lowercase.
    typ = models.IntegerField(db_column='TYP') # Field name made lowercase.
    class Meta:
        db_table = u'status_werte'

class TdbVersion(models.Model):
    dbversion = models.IntegerField(primary_key=True, db_column='DBVERSION') # Field name made lowercase.
    dbdate = models.DateTimeField(db_column='DBDATE') # Field name made lowercase.
    class Meta:
        db_table = u'tdb_version'

class MpFile(models.Model):
    file_id = models.IntegerField(primary_key=True, db_column='FILE_ID') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    file_typ = models.IntegerField(null=True, db_column='FILE_TYP', blank=True) # Field name made lowercase.
    label_id = models.IntegerField(null=True, db_column='LABEL_ID', blank=True) # Field name made lowercase.
    filename = models.CharField(max_length=3072, db_column='FILENAME', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'mp_file'

class MpLabel(models.Model):
    label_id = models.IntegerField(primary_key=True, db_column='LABEL_ID') # Field name made lowercase.
    sec_id = models.IntegerField(primary_key=True, db_column='SEC_ID') # Field name made lowercase.
    label_typ = models.IntegerField(primary_key=True, db_column='LABEL_TYP') # Field name made lowercase.
    s = models.ForeignKey(Sprachen, db_column='S_ID') # Field name made lowercase.
    label = models.CharField(max_length=3072, db_column='LABEL') # Field name made lowercase.
    class Meta:
        db_table = u'mp_label'

class MpMultimedia(models.Model):
    mult_id = models.IntegerField(primary_key=True, db_column='MULT_ID') # Field name made lowercase.
    mult_typ = models.IntegerField(null=True, db_column='MULT_TYP', blank=True) # Field name made lowercase.
    s = models.ForeignKey(Sprachen, null=True, db_column='S_ID', blank=True) # Field name made lowercase.
    mult = models.TextField(db_column='MULT', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'mp_multimedia'

class MpParam(models.Model):
    param_id = models.IntegerField(primary_key=True, db_column='PARAM_ID') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    file = models.ForeignKey(MpFile, null=True, db_column='FILE_ID', blank=True) # Field name made lowercase.
    param_typ = models.IntegerField(null=True, db_column='PARAM_TYP', blank=True) # Field name made lowercase.
    label_id = models.IntegerField(null=True, db_column='LABEL_ID', blank=True) # Field name made lowercase.
    param = models.CharField(max_length=3072, db_column='PARAM', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'mp_param'

class MpTextDoc(models.Model):
    textid = models.IntegerField(primary_key=True, db_column='TEXTID') # Field name made lowercase.
    typ = models.IntegerField(primary_key=True, db_column='TYP') # Field name made lowercase.
    mult = models.ForeignKey(MpMultimedia, db_column='MULT_ID') # Field name made lowercase.
    class Meta:
        db_table = u'mp_text_doc'

class MpTexte(models.Model):
    textid = models.IntegerField(primary_key=True, db_column='TEXTID') # Field name made lowercase.
    typ = models.IntegerField(primary_key=True, db_column='TYP') # Field name made lowercase.
    s = models.ForeignKey(Sprachen, db_column='S_ID') # Field name made lowercase.
    text = models.CharField(max_length=3072, db_column='TEXT') # Field name made lowercase.
    class Meta:
        db_table = u'mp_texte'

class Msg(models.Model):
    msg_typ = models.IntegerField(db_column='MSG_TYP') # Field name made lowercase.
    msg_id = models.IntegerField(unique=True, db_column='MSG_ID') # Field name made lowercase.
    s = models.ForeignKey(Sprachen, db_column='S_ID') # Field name made lowercase.
    textnr = models.IntegerField(unique=True, db_column='TEXTNR') # Field name made lowercase.
    text = models.CharField(max_length=3072, db_column='TEXT') # Field name made lowercase.
    class Meta:
        db_table = u'msg'

class PcxFiles(models.Model):
    pcx_id = models.IntegerField(unique=True, db_column='PCX_ID') # Field name made lowercase.
    bez_id = models.IntegerField(unique=True, db_column='BEZ_ID') # Field name made lowercase.
    filename = models.CharField(max_length=3072, db_column='FILENAME') # Field name made lowercase.
    x = models.IntegerField(null=True, db_column='X', blank=True) # Field name made lowercase.
    y = models.IntegerField(null=True, db_column='Y', blank=True) # Field name made lowercase.
    typ = models.IntegerField(db_column='TYP') # Field name made lowercase.
    typcode = models.IntegerField(db_column='TYPCODE') # Field name made lowercase.
    folge = models.IntegerField(db_column='FOLGE') # Field name made lowercase.
    class Meta:
        db_table = u'pcx_files'

class Help(models.Model):
    help_typ = models.IntegerField(db_column='HELP_TYP') # Field name made lowercase.
    help_id = models.IntegerField(unique=True, db_column='HELP_ID') # Field name made lowercase.
    s = models.ForeignKey(Sprachen, db_column='S_ID') # Field name made lowercase.
    textnr = models.IntegerField(unique=True, db_column='TEXTNR') # Field name made lowercase.
    text = models.CharField(max_length=3072, db_column='TEXT') # Field name made lowercase.
    class Meta:
        db_table = u'help'

class History(models.Model):
    his_id = models.IntegerField(db_column='HIS_ID') # Field name made lowercase.
    s = models.ForeignKey(Sprachen, db_column='S_ID') # Field name made lowercase.
    textnr = models.IntegerField(unique=True, db_column='TEXTNR') # Field name made lowercase.
    text = models.CharField(max_length=3072, db_column='TEXT') # Field name made lowercase.
    dat = models.IntegerField(db_column='DAT') # Field name made lowercase.
    typ = models.IntegerField(db_column='TYP') # Field name made lowercase.
    class Meta:
        db_table = u'history'


class Bezeichnung(models.Model):
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    s = models.ForeignKey(Sprachen, db_column='S_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    typ = models.IntegerField(db_column='TYP') # Field name made lowercase.
    class Meta:
        db_table = u'bezeichnung'

class Texte(models.Model):
    textid = models.IntegerField(db_column='TEXTID') # Field name made lowercase.
    s = models.ForeignKey(Sprachen, db_column='S_ID') # Field name made lowercase.
    textnr = models.IntegerField(unique=True, db_column='TEXTNR') # Field name made lowercase.
    text = models.CharField(max_length=3072, db_column='TEXT') # Field name made lowercase.
    typ = models.IntegerField(db_column='TYP') # Field name made lowercase.
    class Meta:
        db_table = u'texte'

class Label(models.Model):
    label_prg = models.IntegerField(unique=True, db_column='LABEL_PRG') # Field name made lowercase.
    label_typ = models.IntegerField(unique=True, db_column='LABEL_TYP') # Field name made lowercase.
    stufe1 = models.IntegerField(unique=True, db_column='STUFE1') # Field name made lowercase.
    stufe2 = models.IntegerField(unique=True, db_column='STUFE2') # Field name made lowercase.
    s = models.ForeignKey(Sprachen, db_column='S_ID') # Field name made lowercase.
    label = models.CharField(max_length=3072, db_column='LABEL') # Field name made lowercase.
    class Meta:
        db_table = u'label'

class Waehrung(models.Model):
    whr_id = models.IntegerField(unique=True, db_column='WHR_ID') # Field name made lowercase.
    bez_id = models.IntegerField(unique=True, db_column='BEZ_ID') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    status = models.IntegerField(null=True, db_column='STATUS', blank=True) # Field name made lowercase.
    krzl = models.CharField(max_length=768, db_column='KRZL', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'waehrung'

class Land(models.Model):
    land_id = models.IntegerField(unique=True, db_column='LAND_ID') # Field name made lowercase.
    bez_id = models.IntegerField(unique=True, db_column='BEZ_ID') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    krzl = models.CharField(max_length=768, db_column='KRZL', blank=True) # Field name made lowercase.
    haupt_ort = models.IntegerField(null=True, db_column='HAUPT_ORT', blank=True) # Field name made lowercase.
    haupt_whr = models.ForeignKey(Waehrung, null=True, db_column='HAUPT_WHR', blank=True) # Field name made lowercase.
    haupt_spr = models.ForeignKey(Sprachen, null=True, db_column='HAUPT_SPR', blank=True) # Field name made lowercase.
    vat = models.FloatField(null=True, db_column='VAT', blank=True) # Field name made lowercase.
    dateformat = models.CharField(max_length=768, db_column='DATEFORMAT', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'land'

class LandSpr(models.Model):
    land = models.ForeignKey(Land, unique=True, db_column='LAND_ID') # Field name made lowercase.
    s = models.ForeignKey(Sprachen, db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'land_spr'

class LandWhr(models.Model):
    land = models.ForeignKey(Land, db_column='LAND_ID') # Field name made lowercase.
    whr = models.ForeignKey(Waehrung, db_column='WHR_ID') # Field name made lowercase.
    kurs_typ = models.IntegerField(unique=True, db_column='KURS_TYP') # Field name made lowercase.
    a_kurs = models.FloatField(db_column='A_KURS') # Field name made lowercase.
    v_kurs = models.FloatField(db_column='V_KURS') # Field name made lowercase.
    von_dat = models.IntegerField(null=True, db_column='VON_DAT', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'land_whr'

class Ort(models.Model):
    ort_id = models.IntegerField(unique=True, db_column='ORT_ID') # Field name made lowercase.
    bez_id = models.IntegerField(unique=True, db_column='BEZ_ID') # Field name made lowercase.
    land = models.ForeignKey(Land, db_column='LAND_ID') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    krzl = models.CharField(max_length=768, db_column='KRZL', blank=True) # Field name made lowercase.
    zeitver = models.IntegerField(null=True, db_column='ZEITVER', blank=True) # Field name made lowercase.
    koord1 = models.IntegerField(null=True, db_column='KOORD1', blank=True) # Field name made lowercase.
    koord2 = models.IntegerField(null=True, db_column='KOORD2', blank=True) # Field name made lowercase.
    ort_typ = models.IntegerField(null=True, db_column='ORT_TYP', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'ort'

class TraegerTyp(models.Model):
    typ_id = models.IntegerField(db_column='TYP_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    h_typ_id = models.IntegerField(db_column='H_TYP_ID') # Field name made lowercase.
    host_typ = models.IntegerField(db_column='HOST_TYP') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'traeger_typ'

class Kategorie(models.Model):
    kat_id = models.IntegerField(db_column='KAT_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    h_kat_id = models.IntegerField(null=True, db_column='H_KAT_ID', blank=True) # Field name made lowercase.
    typ = models.ForeignKey(TraegerTyp, db_column='TYP_ID') # Field name made lowercase.
    ga = models.IntegerField(null=True, db_column='GA', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'kategorie'

class DienstTraeger(models.Model):
    dlt_id = models.IntegerField(db_column='DLT_ID') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    kat = models.ForeignKey(Kategorie, null=True, db_column='KAT_ID', blank=True) # Field name made lowercase.
    h_dlt_id = models.IntegerField(db_column='H_DLT_ID') # Field name made lowercase.
    dlt_grp_id = models.IntegerField(db_column='DLT_GRP_ID') # Field name made lowercase.
    host_id = models.IntegerField(db_column='HOST_ID') # Field name made lowercase.
    typ = models.ForeignKey(TraegerTyp, db_column='TYP_ID') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    stufe = models.IntegerField(db_column='STUFE') # Field name made lowercase.
    sta_id = models.IntegerField(null=True, db_column='STA_ID', blank=True) # Field name made lowercase.
    anz = models.IntegerField(null=True, db_column='ANZ', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'dienst_traeger'

class Graphik(models.Model):
    gra_id = models.IntegerField(unique=True, db_column='GRA_ID') # Field name made lowercase.
    bez_id = models.IntegerField(unique=True, db_column='BEZ_ID') # Field name made lowercase.
    dlt = models.ForeignKey(DienstTraeger, unique=True, db_column='DLT_ID') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'graphik'

class Regions(models.Model):
    host_id = models.IntegerField(db_column='HOST_ID') # Field name made lowercase.
    h_dlt_id = models.IntegerField(db_column='H_DLT_ID') # Field name made lowercase.
    dlt = models.ForeignKey(DienstTraeger, db_column='DLT_ID') # Field name made lowercase.
    folge = models.IntegerField(unique=True, db_column='FOLGE') # Field name made lowercase.
    stufe = models.IntegerField(db_column='STUFE') # Field name made lowercase.
    nummer = models.IntegerField(db_column='NUMMER') # Field name made lowercase.
    class Meta:
        db_table = u'regions'

class Graform(models.Model):
    gra = models.ForeignKey(Graphik, db_column='GRA_ID') # Field name made lowercase.
    formnr = models.IntegerField(unique=True, db_column='FORMNR') # Field name made lowercase.
    form = models.CharField(max_length=768, db_column='FORM') # Field name made lowercase.
    class Meta:
        db_table = u'graform'

class AktionsTyp(models.Model):
    a_typ_id = models.IntegerField(unique=True, db_column='A_TYP_ID') # Field name made lowercase.
    bez_id = models.IntegerField(unique=True, db_column='BEZ_ID') # Field name made lowercase.
    proz = models.CharField(max_length=3072, db_column='PROZ') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'aktions_typ'

class Aktionen(models.Model):
    akt_id = models.IntegerField(unique=True, db_column='AKT_ID') # Field name made lowercase.
    bez_id = models.IntegerField(unique=True, db_column='BEZ_ID') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    a_flag = models.IntegerField(null=True, db_column='A_FLAG', blank=True) # Field name made lowercase.
    b_flag = models.IntegerField(null=True, db_column='B_FLAG', blank=True) # Field name made lowercase.
    m_flag = models.IntegerField(null=True, db_column='M_FLAG', blank=True) # Field name made lowercase.
    a_typ = models.ForeignKey(AktionsTyp, db_column='A_TYP_ID') # Field name made lowercase.
    b2_flag = models.IntegerField(null=True, db_column='B2_FLAG', blank=True) # Field name made lowercase.
    file = models.ForeignKey(MpFile, null=True, db_column='FILE_ID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'aktionen'

class Aktionsgrp(models.Model):
    parentakt = models.ForeignKey(Aktionen, related_name='parentaktagrev', db_column='PARENTAKT') # Field name made lowercase.
    childakt = models.ForeignKey(Aktionen, related_name='childaktagrev', db_column='CHILDAKT') # Field name made lowercase.
    ord = models.IntegerField(unique=True, db_column='ORD') # Field name made lowercase.
    h_akt = models.ForeignKey(Aktionen, related_name='topaktagrev', db_column='H_AKT_ID') # Field name made lowercase.
    class Meta:
        db_table = u'aktionsgrp'

class Aktionspara(models.Model):
    a_typ = models.ForeignKey(AktionsTyp, db_column='A_TYP_ID') # Field name made lowercase.
    nr = models.IntegerField(unique=True, db_column='NR') # Field name made lowercase.
    typ = models.IntegerField(null=True, db_column='TYP', blank=True) # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    muss = models.IntegerField(null=True, db_column='MUSS', blank=True) # Field name made lowercase.
    flag = models.IntegerField(null=True, db_column='FLAG', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'aktionspara'

class Aktionstexte(models.Model):
    textid = models.IntegerField(db_column='TEXTID') # Field name made lowercase.
    s = models.ForeignKey(Sprachen, db_column='S_ID') # Field name made lowercase.
    textnr = models.IntegerField(unique=True, db_column='TEXTNR') # Field name made lowercase.
    text = models.CharField(max_length=3072, db_column='TEXT') # Field name made lowercase.
    typ = models.IntegerField(db_column='TYP') # Field name made lowercase.
    class Meta:
        db_table = u'aktionstexte'

class Personen(models.Model):
    pers_id = models.IntegerField(unique=True, db_column='PERS_ID') # Field name made lowercase.
    pers_typ = models.IntegerField(db_column='PERS_TYP') # Field name made lowercase.
    name = models.CharField(max_length=1536, db_column='NAME') # Field name made lowercase.
    s = models.ForeignKey(Sprachen, db_column='S_ID') # Field name made lowercase.
    sta_id = models.IntegerField(null=True, db_column='STA_ID', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'personen'

class Persadr(models.Model):
    pers = models.ForeignKey(Personen, unique=True, db_column='PERS_ID') # Field name made lowercase.
    adr_typ = models.IntegerField(primary_key=True, db_column='ADR_TYP') # Field name made lowercase.
    ans = models.CharField(max_length=768, db_column='ANS', blank=True) # Field name made lowercase.
    adr1 = models.CharField(max_length=3072, db_column='ADR1', blank=True) # Field name made lowercase.
    adr2 = models.CharField(max_length=3072, db_column='ADR2', blank=True) # Field name made lowercase.
    adr3 = models.CharField(max_length=3072, db_column='ADR3', blank=True) # Field name made lowercase.
    plz = models.CharField(max_length=768, db_column='PLZ', blank=True) # Field name made lowercase.
    ort = models.CharField(max_length=768, db_column='ORT', blank=True) # Field name made lowercase.
    kant = models.CharField(max_length=768, db_column='KANT', blank=True) # Field name made lowercase.
    land_id = models.IntegerField(null=True, db_column='LAND_ID', blank=True) # Field name made lowercase.
    sta_id = models.IntegerField(null=True, db_column='STA_ID', blank=True) # Field name made lowercase.
    haupt_flag = models.IntegerField(null=True, db_column='HAUPT_FLAG', blank=True) # Field name made lowercase.
    rch_flag = models.IntegerField(null=True, db_column='RCH_FLAG', blank=True) # Field name made lowercase.
    mail_flag = models.IntegerField(null=True, db_column='MAIL_FLAG', blank=True) # Field name made lowercase.
    tel = models.CharField(max_length=768, db_column='TEL', blank=True) # Field name made lowercase.
    handy = models.CharField(max_length=768, db_column='HANDY', blank=True) # Field name made lowercase.
    fax = models.CharField(max_length=768, db_column='FAX', blank=True) # Field name made lowercase.
    tlx = models.CharField(max_length=768, db_column='TLX', blank=True) # Field name made lowercase.
    email = models.CharField(max_length=3072, db_column='EMAIL', blank=True) # Field name made lowercase.
    web = models.CharField(max_length=3072, db_column='WEB', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'persadr'

class KundenTyp(models.Model):
    k_typ_id = models.IntegerField(unique=True, db_column='K_TYP_ID') # Field name made lowercase.
    kuncode = models.CharField(max_length=768, db_column='KUNCODE', blank=True) # Field name made lowercase.
    bez_id = models.IntegerField(unique=True, db_column='BEZ_ID') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'kunden_typ'

class Kunden(models.Model):
    pers = models.ForeignKey(Personen, unique=True, db_column='PERS_ID') # Field name made lowercase.
    tel = models.CharField(max_length=768, db_column='TEL', blank=True) # Field name made lowercase.
    handy = models.CharField(max_length=768, db_column='HANDY', blank=True) # Field name made lowercase.
    fax = models.CharField(max_length=768, db_column='FAX', blank=True) # Field name made lowercase.
    tlx = models.CharField(max_length=768, db_column='TLX', blank=True) # Field name made lowercase.
    email = models.CharField(max_length=3072, db_column='EMAIL', blank=True) # Field name made lowercase.
    web = models.CharField(max_length=3072, db_column='WEB', blank=True) # Field name made lowercase.
    konto = models.CharField(max_length=768, db_column='KONTO', blank=True) # Field name made lowercase.
    leiter = models.IntegerField(null=True, db_column='LEITER', blank=True) # Field name made lowercase.
    attr1 = models.CharField(max_length=3072, db_column='ATTR1', blank=True) # Field name made lowercase.
    attr2 = models.CharField(max_length=3072, db_column='ATTR2', blank=True) # Field name made lowercase.
    k_typ = models.ForeignKey(KundenTyp, db_column='K_TYP_ID') # Field name made lowercase.
    whr = models.ForeignKey(Waehrung, db_column='WHR_ID') # Field name made lowercase.
    class Meta:
        db_table = u'kunden'

class ReisenderTyp(models.Model):
    rkr_id = models.IntegerField(unique=True, db_column='RKR_ID') # Field name made lowercase.
    dlncode = models.CharField(max_length=768, db_column='DLNCODE', blank=True) # Field name made lowercase.
    bez_id = models.IntegerField(unique=True, db_column='BEZ_ID') # Field name made lowercase.
    vonalter = models.IntegerField(null=True, db_column='VONALTER', blank=True) # Field name made lowercase.
    bisalter = models.IntegerField(null=True, db_column='BISALTER', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'reisender_typ'

class Reisender(models.Model):
    pers = models.ForeignKey(Personen, unique=True, db_column='PERS_ID') # Field name made lowercase.
    vor = models.CharField(max_length=1536, db_column='VOR') # Field name made lowercase.
    rkr = models.ForeignKey(ReisenderTyp, db_column='RKR_ID') # Field name made lowercase.
    sex = models.IntegerField(null=True, db_column='SEX', blank=True) # Field name made lowercase.
    mutters_id = models.IntegerField(null=True, db_column='MUTTERS_ID', blank=True) # Field name made lowercase.
    age = models.CharField(max_length=768, db_column='AGE', blank=True) # Field name made lowercase.
    passnr = models.CharField(max_length=768, db_column='PASSNR', blank=True) # Field name made lowercase.
    attr1 = models.CharField(max_length=3072, db_column='ATTR1', blank=True) # Field name made lowercase.
    attr2 = models.CharField(max_length=3072, db_column='ATTR2', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'reisender'

class KollektivTyp(models.Model):
    k_typ_id = models.IntegerField(unique=True, db_column='K_TYP_ID') # Field name made lowercase.
    kolcode = models.CharField(max_length=768, db_column='KOLCODE', blank=True) # Field name made lowercase.
    bez_id = models.IntegerField(unique=True, db_column='BEZ_ID') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'kollektiv_typ'

class Kollektiv(models.Model):
    k_id = models.IntegerField(unique=True, db_column='K_ID') # Field name made lowercase.
    ref = models.CharField(max_length=768, db_column='REF', blank=True) # Field name made lowercase.
    name = models.CharField(max_length=1536, db_column='NAME', blank=True) # Field name made lowercase.
    k_typ = models.ForeignKey(KollektivTyp, db_column='K_TYP_ID') # Field name made lowercase.
    kbst = models.ForeignKey(Personen, related_name='bstkolrev', db_column='KBST') # Field name made lowercase.
    k_sta = models.IntegerField(null=True, db_column='K_STA', blank=True) # Field name made lowercase.
    hauptpers = models.ForeignKey(Personen, related_name='mainperskolrev', null=True, db_column='HAUPTPERS', blank=True) # Field name made lowercase.
    kid = models.ForeignKey(Personen, related_name='kidkolrev', null=True, db_column='KID', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'kollektiv'

class Saison(models.Model):
    sai_id = models.IntegerField(unique=True, db_column='SAI_ID') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    bez_id = models.IntegerField(unique=True, db_column='BEZ_ID') # Field name made lowercase.
    von = models.IntegerField(db_column='VON') # Field name made lowercase.
    bis = models.IntegerField(db_column='BIS') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'saison'

class Programm(models.Model):
    prg_id = models.IntegerField(unique=True, db_column='PRG_ID') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    bez_id = models.IntegerField(unique=True, db_column='BEZ_ID') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    sai = models.ForeignKey(Saison, db_column='SAI_ID') # Field name made lowercase.
    class Meta:
        db_table = u'programm'

class Arrangement(models.Model):
    arr_id = models.IntegerField(unique=True, db_column='ARR_ID') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    a_dat = models.IntegerField(db_column='A_DAT') # Field name made lowercase.
    prg = models.ForeignKey(Programm, db_column='PRG_ID') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    sai = models.ForeignKey(Saison, db_column='SAI_ID') # Field name made lowercase.
    class Meta:
        db_table = u'arrangement'

class AngebotsTyp(models.Model):
    art_id = models.IntegerField(unique=True, db_column='ART_ID') # Field name made lowercase.
    bez_id = models.IntegerField(unique=True, db_column='BEZ_ID') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'angebots_typ'

class DienstAngebot(models.Model):
    dla_id = models.IntegerField(unique=True, db_column='DLA_ID') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    h_dla_id = models.IntegerField(db_column='H_DLA_ID') # Field name made lowercase.
    ord = models.IntegerField(unique=True, db_column='ORD') # Field name made lowercase.
    dlt = models.ForeignKey(DienstTraeger, db_column='DLT_ID') # Field name made lowercase.
    bez_id = models.IntegerField(unique=True, db_column='BEZ_ID') # Field name made lowercase.
    akt = models.ForeignKey(Aktionen, db_column='AKT_ID') # Field name made lowercase.
    ort = models.CharField(max_length=768, db_column='ORT') # Field name made lowercase.
    art = models.ForeignKey(AngebotsTyp, db_column='ART_ID') # Field name made lowercase.
    dau = models.IntegerField(null=True, db_column='DAU', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    von = models.ForeignKey(Ort, related_name='vondarev', db_column='VON') # Field name made lowercase.
    nach = models.ForeignKey(Ort, related_name='nachdarev', db_column='NACH') # Field name made lowercase.
    class Meta:
        db_table = u'dienst_angebot'

class Dienstleistung(models.Model):
    dlg_id = models.IntegerField(db_column='DLG_ID') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    sai = models.ForeignKey(Saison, db_column='SAI_ID') # Field name made lowercase.
    a_zeit = models.IntegerField(null=True, db_column='A_ZEIT', blank=True) # Field name made lowercase.
    akt = models.ForeignKey(Aktionen, null=True, db_column='AKT_ID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'dienstleistung'

class DlgParts(models.Model):
    dl_id = models.IntegerField(db_column='DL_ID') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    h_dl_id = models.IntegerField(db_column='H_DL_ID') # Field name made lowercase.
    dla = models.ForeignKey(DienstAngebot, db_column='DLA_ID') # Field name made lowercase.
    ord = models.IntegerField(null=True, db_column='ORD', blank=True) # Field name made lowercase.
    a_zeit = models.IntegerField(null=True, db_column='A_ZEIT', blank=True) # Field name made lowercase.
    e_zeit = models.IntegerField(null=True, db_column='E_ZEIT', blank=True) # Field name made lowercase.
    res_f = models.IntegerField(db_column='RES_F') # Field name made lowercase.
    kid = models.ForeignKey(Personen, related_name='kiddprev', null=True, db_column='KID', blank=True) # Field name made lowercase.
    konto = models.CharField(max_length=768, db_column='KONTO', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    sai = models.ForeignKey(Saison, db_column='SAI_ID') # Field name made lowercase.
    rechst = models.ForeignKey(Personen, related_name='rstdgrev', null=True, db_column='RECHST', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'dlg_parts'

class DlgDlg(models.Model):
    dlg = models.ForeignKey(Dienstleistung, db_column='DLG_ID') # Field name made lowercase.
    dl = models.ForeignKey(DlgParts, db_column='DL_ID') # Field name made lowercase.
    ord = models.IntegerField(db_column='ORD') # Field name made lowercase.
    class Meta:
        db_table = u'dlg_dlg'

class ArrDlg(models.Model):
    arr = models.ForeignKey(Arrangement, db_column='ARR_ID') # Field name made lowercase.
    teil = models.IntegerField(db_column='TEIL') # Field name made lowercase.
    prio = models.IntegerField(db_column='PRIO') # Field name made lowercase.
    dlg = models.ForeignKey(Dienstleistung, db_column='DLG_ID') # Field name made lowercase.
    class Meta:
        db_table = u'arr_dlg'

class HostKont(models.Model):
    hostkont_id = models.IntegerField(unique=True, db_column='HOSTKONT_ID') # Field name made lowercase.
    bez_id = models.IntegerField(unique=True, db_column='BEZ_ID') # Field name made lowercase.
    from_pers = models.ForeignKey(Personen, related_name='fromphkrev', db_column='FROM_PERS') # Field name made lowercase.
    kbst = models.ForeignKey(Personen, related_name='bsthkrev', db_column='KBST') # Field name made lowercase.
    dla = models.ForeignKey(DienstAngebot, null=True, db_column='DLA_ID', blank=True) # Field name made lowercase.
    dl = models.ForeignKey(Dienstleistung, null=True, db_column='DL_ID', blank=True) # Field name made lowercase.
    dl_vondat = models.IntegerField(null=True, db_column='DL_VONDAT', blank=True) # Field name made lowercase.
    dl_bisdat = models.IntegerField(null=True, db_column='DL_BISDAT', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    opt_dat = models.IntegerField(null=True, db_column='OPT_DAT', blank=True) # Field name made lowercase.
    sai = models.ForeignKey(Saison, db_column='SAI_ID') # Field name made lowercase.
    ref = models.CharField(max_length=768, db_column='REF', blank=True) # Field name made lowercase.
    history = models.IntegerField(null=True, db_column='HISTORY', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'host_kont'

class Kontingent(models.Model):
    kont_id = models.IntegerField(unique=True, db_column='KONT_ID') # Field name made lowercase.
    bez_id = models.IntegerField(unique=True, db_column='BEZ_ID') # Field name made lowercase.
    hostkont = models.ForeignKey(HostKont, db_column='HOSTKONT_ID') # Field name made lowercase.
    kunden = models.ForeignKey(Personen, db_column='KUNDEN_ID') # Field name made lowercase.
    opt_dat = models.IntegerField(null=True, db_column='OPT_DAT', blank=True) # Field name made lowercase.
    ref = models.CharField(max_length=768, db_column='REF', blank=True) # Field name made lowercase.
    sai = models.ForeignKey(Saison, db_column='SAI_ID') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'kontingent'

class KontDetail(models.Model):
    hostkont = models.ForeignKey(HostKont, db_column='HOSTKONT_ID') # Field name made lowercase.
    kont = models.ForeignKey(Kontingent, db_column='KONT_ID') # Field name made lowercase.
    kat = models.ForeignKey(Kategorie, db_column='KAT_ID') # Field name made lowercase.
    dlt = models.ForeignKey(DienstTraeger, db_column='DLT_ID') # Field name made lowercase.
    sta_id = models.IntegerField(null=True, db_column='STA_ID', blank=True) # Field name made lowercase.
    anz = models.IntegerField(null=True, db_column='ANZ', blank=True) # Field name made lowercase.
    busy = models.IntegerField(null=True, db_column='BUSY', blank=True) # Field name made lowercase.
    minanz = models.IntegerField(null=True, db_column='MINANZ', blank=True) # Field name made lowercase.
    von_dat = models.IntegerField(primary_key=True, db_column='VON_DAT') # Field name made lowercase.
    bis_dat = models.IntegerField(primary_key=True, db_column='BIS_DAT') # Field name made lowercase.
    class Meta:
        db_table = u'kont_detail'

class Kapa(models.Model):
    kat = models.ForeignKey(Kategorie, db_column='KAT_ID') # Field name made lowercase.
    katbez_id = models.IntegerField(db_column='KATBEZ_ID') # Field name made lowercase.
    tdl = models.ForeignKey(DlgParts, db_column='TDL_ID') # Field name made lowercase.
    tdlbez_id = models.IntegerField(db_column='TDLBEZ_ID') # Field name made lowercase.
    pre_id = models.IntegerField(db_column='PRE_ID') # Field name made lowercase.
    anz = models.IntegerField(null=True, db_column='ANZ', blank=True) # Field name made lowercase.
    busy = models.IntegerField(null=True, db_column='BUSY', blank=True) # Field name made lowercase.
    vpr = models.FloatField(null=True, db_column='VPR', blank=True) # Field name made lowercase.
    von_dat = models.IntegerField(primary_key=True, db_column='VON_DAT') # Field name made lowercase.
    bis_dat = models.IntegerField(primary_key=True, db_column='BIS_DAT') # Field name made lowercase.
    class Meta:
        db_table = u'kapa'


class KostenArt(models.Model):
    kar_id = models.IntegerField(unique=True, db_column='KAR_ID') # Field name made lowercase.
    bez_id = models.IntegerField(unique=True, db_column='BEZ_ID') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'kosten_art'

class MpProfil(models.Model):
    mpid = models.IntegerField(unique=True, db_column='MPID') # Field name made lowercase.
    mpuser = models.CharField(max_length=384, db_column='MPUSER') # Field name made lowercase.
    bchst = models.ForeignKey(Personen, db_column='BCHST') # Field name made lowercase.
    seclevel = models.IntegerField(db_column='SECLEVEL') # Field name made lowercase.
    s = models.ForeignKey(Sprachen, db_column='S_ID') # Field name made lowercase.
    land = models.ForeignKey(Land, db_column='LAND_ID') # Field name made lowercase.
    dltt = models.ForeignKey(TraegerTyp, db_column='DLTT_ID') # Field name made lowercase.
    dlt = models.ForeignKey(DienstTraeger, db_column='DLT_ID') # Field name made lowercase.
    kat = models.ForeignKey(Kategorie, db_column='KAT_ID') # Field name made lowercase.
    dlat = models.ForeignKey(AngebotsTyp, db_column='DLAT_ID') # Field name made lowercase.
    dlnt = models.ForeignKey(ReisenderTyp, db_column='DLNT_ID') # Field name made lowercase.
    sai = models.ForeignKey(Saison, db_column='SAI_ID') # Field name made lowercase.
    prg = models.ForeignKey(Programm, db_column='PRG_ID') # Field name made lowercase.
    a_zeit = models.IntegerField(db_column='A_ZEIT') # Field name made lowercase.
    e_zeit = models.IntegerField(db_column='E_ZEIT') # Field name made lowercase.
    p_range = models.IntegerField(db_column='P_RANGE') # Field name made lowercase.
    class Meta:
        db_table = u'mp_profil'

class MpPreferences(models.Model):
    mpid = models.ForeignKey(MpProfil, db_column='MPID') # Field name made lowercase.
    fullname = models.CharField(max_length=3072, db_column='FULLNAME', blank=True) # Field name made lowercase.
    filter = models.CharField(max_length=3072, db_column='FILTER', blank=True) # Field name made lowercase.
    gui = models.CharField(max_length=3072, db_column='GUI', blank=True) # Field name made lowercase.
    custom = models.CharField(max_length=3072, db_column='CUSTOM', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'mp_preferences'

class MpProx(models.Model):
    ort_id = models.IntegerField(primary_key=True, db_column='ORT_ID') # Field name made lowercase.
    prox_id = models.IntegerField(primary_key=True, db_column='PROX_ID') # Field name made lowercase.
    class Meta:
        db_table = u'mp_prox'

class Preis(models.Model):
    pre_id = models.IntegerField(unique=True, db_column='PRE_ID') # Field name made lowercase.
    apr = models.FloatField(db_column='APR') # Field name made lowercase.
    epr = models.FloatField(db_column='EPR') # Field name made lowercase.
    vpr = models.FloatField(db_column='VPR') # Field name made lowercase.
    glt = models.IntegerField(db_column='GLT') # Field name made lowercase.
    whr = models.ForeignKey(Waehrung, db_column='WHR_ID') # Field name made lowercase.
    kbst = models.ForeignKey(Personen, db_column='KBST') # Field name made lowercase.
    kar = models.ForeignKey(KostenArt, null=True, db_column='KAR_ID', blank=True) # Field name made lowercase.
    dltt = models.ForeignKey(TraegerTyp, null=True, db_column='DLTT_ID', blank=True) # Field name made lowercase.
    kat = models.ForeignKey(Kategorie, null=True, db_column='KAT_ID', blank=True) # Field name made lowercase.
    rkr = models.ForeignKey(ReisenderTyp, null=True, db_column='RKR_ID', blank=True) # Field name made lowercase.
    dla = models.ForeignKey(DienstAngebot, null=True, db_column='DLA_ID', blank=True) # Field name made lowercase.
    arr_id = models.IntegerField(null=True, db_column='ARR_ID', blank=True) # Field name made lowercase.
    dl = models.ForeignKey(Dienstleistung, null=True, db_column='DL_ID', blank=True) # Field name made lowercase.
    ext_id = models.IntegerField(null=True, db_column='EXT_ID', blank=True) # Field name made lowercase.
    dl_vondat = models.IntegerField(unique=True, null=True, db_column='DL_VONDAT', blank=True) # Field name made lowercase.
    dl_bisdat = models.IntegerField(unique=True, null=True, db_column='DL_BISDAT', blank=True) # Field name made lowercase.
    kont = models.ForeignKey(Kontingent, null=True, db_column='KONT_ID', blank=True) # Field name made lowercase.
    sta_id = models.IntegerField(null=True, db_column='STA_ID', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    history = models.IntegerField(null=True, db_column='HISTORY', blank=True) # Field name made lowercase.
    sai = models.ForeignKey(Saison, db_column='SAI_ID') # Field name made lowercase.
    unit_typ = models.IntegerField(null=True, db_column='UNIT_TYP', blank=True) # Field name made lowercase.
    unit_von = models.IntegerField(null=True, db_column='UNIT_VON', blank=True) # Field name made lowercase.
    unit_bis = models.IntegerField(null=True, db_column='UNIT_BIS', blank=True) # Field name made lowercase.
    dau = models.IntegerField(null=True, db_column='DAU', blank=True) # Field name made lowercase.
    dau_von = models.IntegerField(null=True, db_column='DAU_VON', blank=True) # Field name made lowercase.
    dau_bis = models.IntegerField(null=True, db_column='DAU_BIS', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'preis'

class Buchung(models.Model):
    d_bid = models.IntegerField(db_column='D_BID') # Field name made lowercase.
    bid = models.IntegerField(unique=True, db_column='BID') # Field name made lowercase.
    ref = models.CharField(max_length=768, db_column='REF') # Field name made lowercase.
    arr = models.ForeignKey(Arrangement, db_column='ARR_ID') # Field name made lowercase.
    kid = models.ForeignKey(Personen, db_column='KID') # Field name made lowercase.
    sach = models.IntegerField(db_column='SACH') # Field name made lowercase.
    anw = models.IntegerField(db_column='ANW') # Field name made lowercase.
    b_dat = models.IntegerField(null=True, db_column='B_DAT', blank=True) # Field name made lowercase.
    m_dat = models.IntegerField(null=True, db_column='M_DAT', blank=True) # Field name made lowercase.
    opt_bst = models.IntegerField(null=True, db_column='OPT_BST', blank=True) # Field name made lowercase.
    opt_kid = models.IntegerField(null=True, db_column='OPT_KID', blank=True) # Field name made lowercase.
    sta = models.IntegerField(db_column='STA') # Field name made lowercase.
    ast = models.IntegerField(db_column='AST') # Field name made lowercase.
    sai = models.ForeignKey(Saison, db_column='SAI_ID') # Field name made lowercase.
    k = models.ForeignKey(Kollektiv, db_column='K_ID') # Field name made lowercase.
    mpid = models.ForeignKey(MpProfil, null=True, db_column='MPID', blank=True) # Field name made lowercase.
    history = models.IntegerField(null=True, db_column='HISTORY', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'buchung'

class BchDln(models.Model):
    bid = models.ForeignKey(Buchung, db_column='BID') # Field name made lowercase.
    dln = models.ForeignKey(Personen, db_column='DLN_ID') # Field name made lowercase.
    class Meta:
        db_table = u'bch_dln'

class Kommission(models.Model):
    komm_id = models.IntegerField(unique=True, db_column='KOMM_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    satz_art = models.IntegerField(unique=True, db_column='SATZ_ART') # Field name made lowercase.
    satz = models.FloatField(unique=True, db_column='SATZ') # Field name made lowercase.
    komm_typ = models.IntegerField(db_column='KOMM_TYP') # Field name made lowercase.
    kbst = models.ForeignKey(Personen, db_column='KBST') # Field name made lowercase.
    kar = models.ForeignKey(KostenArt, null=True, db_column='KAR_ID', blank=True) # Field name made lowercase.
    dltt = models.ForeignKey(TraegerTyp, null=True, db_column='DLTT_ID', blank=True) # Field name made lowercase.
    kat = models.ForeignKey(Kategorie, null=True, db_column='KAT_ID', blank=True) # Field name made lowercase.
    rkr = models.ForeignKey(ReisenderTyp, null=True, db_column='RKR_ID', blank=True) # Field name made lowercase.
    dla = models.ForeignKey(DienstAngebot, null=True, db_column='DLA_ID', blank=True) # Field name made lowercase.
    dl = models.ForeignKey(Dienstleistung, null=True, db_column='DL_ID', blank=True) # Field name made lowercase.
    dl_vondat = models.IntegerField(null=True, db_column='DL_VONDAT', blank=True) # Field name made lowercase.
    dl_bisdat = models.IntegerField(null=True, db_column='DL_BISDAT', blank=True) # Field name made lowercase.
    kont = models.ForeignKey(Kontingent, null=True, db_column='KONT_ID', blank=True) # Field name made lowercase.
    bid = models.ForeignKey(Buchung, null=True, db_column='BID', blank=True) # Field name made lowercase.
    history = models.IntegerField(null=True, db_column='HISTORY', blank=True) # Field name made lowercase.
    sai = models.ForeignKey(Saison, db_column='SAI_ID') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'kommission'

class KommDetail(models.Model):
    komm = models.ForeignKey(Kommission, db_column='KOMM_ID') # Field name made lowercase.
    bid = models.ForeignKey(Buchung, db_column='BID') # Field name made lowercase.
    dln = models.ForeignKey(Personen, related_name='dlnkdrev', db_column='DLN_ID') # Field name made lowercase.
    kun = models.ForeignKey(Personen, related_name='kunkdrev', db_column='KUN_ID') # Field name made lowercase.
    kol = models.ForeignKey(Kollektiv, db_column='KOL_ID') # Field name made lowercase.
    prio = models.IntegerField(unique=True, null=True, db_column='PRIO', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'komm_detail'

class Reservation(models.Model):
    pers = models.ForeignKey(Personen, db_column='PERS_ID') # Field name made lowercase.
    dlg = models.ForeignKey(Dienstleistung, db_column='DLG_ID') # Field name made lowercase.
    dl = models.ForeignKey(DlgParts, db_column='DL_ID') # Field name made lowercase.
    teil = models.IntegerField(db_column='TEIL') # Field name made lowercase.
    dlt = models.ForeignKey(DienstTraeger, db_column='DLT_ID') # Field name made lowercase.
    typ = models.ForeignKey(TraegerTyp, db_column='TYP_ID') # Field name made lowercase.
    bid = models.ForeignKey(Buchung, db_column='BID') # Field name made lowercase.
    kont = models.ForeignKey(Kontingent, db_column='KONT_ID') # Field name made lowercase.
    kat = models.ForeignKey(Kategorie, db_column='KAT_ID') # Field name made lowercase.
    k_kon = models.IntegerField(null=True, db_column='K_KON', blank=True) # Field name made lowercase.
    b_kon = models.IntegerField(null=True, db_column='B_KON', blank=True) # Field name made lowercase.
    r_sta = models.IntegerField(db_column='R_STA') # Field name made lowercase.
    sai = models.ForeignKey(Saison, db_column='SAI_ID') # Field name made lowercase.
    a_zeit = models.IntegerField(unique=True, null=True, db_column='A_ZEIT', blank=True) # Field name made lowercase.
    e_zeit = models.IntegerField(unique=True, null=True, db_column='E_ZEIT', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'reservation'


class AktDetail(models.Model):
    bid = models.ForeignKey(Buchung, db_column='BID') # Field name made lowercase.
    pers = models.ForeignKey(Personen, db_column='PERS_ID') # Field name made lowercase.
    dlg = models.ForeignKey(Dienstleistung, db_column='DLG_ID') # Field name made lowercase.
    dl = models.ForeignKey(DlgParts, db_column='DL_ID') # Field name made lowercase.
    teil = models.IntegerField(db_column='TEIL') # Field name made lowercase.
    akt = models.ForeignKey(Aktionen, related_name='aktaktdrev', db_column='AKT_ID') # Field name made lowercase.
    ord = models.IntegerField(db_column='ORD') # Field name made lowercase.
    a_typ = models.ForeignKey(AktionsTyp, db_column='A_TYP_ID') # Field name made lowercase.
    z_flag = models.IntegerField(db_column='Z_FLAG') # Field name made lowercase.
    akt_nr = models.IntegerField(db_column='AKT_NR') # Field name made lowercase.
    sai = models.ForeignKey(Saison, db_column='SAI_ID') # Field name made lowercase.
    parentakt = models.ForeignKey(Aktionen, related_name='parentaktaktdrev', db_column='PARENTAKT') # Field name made lowercase.
    exec_dat = models.IntegerField(db_column='EXEC_DAT') # Field name made lowercase.
    file = models.ForeignKey(MpFile, null=True, db_column='FILE_ID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'akt_detail'

class MpArrkom(models.Model):
    arr = models.ForeignKey(Arrangement, db_column='ARR_ID') # Field name made lowercase.
    komm = models.ForeignKey(Kommission, db_column='KOMM_ID') # Field name made lowercase.
    komm_bezid = models.IntegerField(db_column='KOMM_BEZID') # Field name made lowercase.
    class Meta:
        db_table = u'mp_arrkom'


class MpReminder(models.Model):
    rem_id = models.IntegerField(primary_key=True, db_column='REM_ID') # Field name made lowercase.
    mpid = models.ForeignKey(MpProfil, db_column='MPID') # Field name made lowercase.
    k = models.ForeignKey(Kollektiv, null=True, db_column='K_ID', blank=True) # Field name made lowercase.
    bid = models.ForeignKey(Buchung, null=True, db_column='BID', blank=True) # Field name made lowercase.
    pers = models.ForeignKey(Personen, related_name='persremrev', null=True, db_column='PERS_ID', blank=True) # Field name made lowercase.
    kid = models.ForeignKey(Personen, related_name='kidremrev', null=True, db_column='KID', blank=True) # Field name made lowercase.
    entry = models.DateTimeField(null=True, db_column='ENTRY', blank=True) # Field name made lowercase.
    deadline = models.DateTimeField(null=True, db_column='DEADLINE', blank=True) # Field name made lowercase.
    person = models.IntegerField(null=True, db_column='PERSON', blank=True) # Field name made lowercase.
    pers_typ = models.IntegerField(null=True, db_column='PERS_TYP', blank=True) # Field name made lowercase.
    notice = models.CharField(max_length=3072, db_column='NOTICE', blank=True) # Field name made lowercase.
    opt = models.CharField(max_length=3072, db_column='OPT', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'mp_reminder'

class MpBchDlg(models.Model):
    bid = models.ForeignKey(Buchung, primary_key=True, db_column='BID') # Field name made lowercase.
    dlg = models.ForeignKey(Dienstleistung, db_column='DLG_ID') # Field name made lowercase.
    teil = models.IntegerField(primary_key=True, db_column='TEIL') # Field name made lowercase.
    class Meta:
        db_table = u'mp_bch_dlg'

class MpKreditor(models.Model):
    kre_id = models.IntegerField(primary_key=True, db_column='KRE_ID') # Field name made lowercase.
    bid = models.ForeignKey(Buchung, db_column='BID') # Field name made lowercase.
    sta_id = models.IntegerField(null=True, db_column='STA_ID', blank=True) # Field name made lowercase.
    kid = models.ForeignKey(Personen, db_column='KID') # Field name made lowercase.
    konto = models.CharField(max_length=768, db_column='KONTO', blank=True) # Field name made lowercase.
    nachsaldo = models.FloatField(null=True, db_column='NACHSALDO', blank=True) # Field name made lowercase.
    k = models.ForeignKey(Kollektiv, null=True, db_column='K_ID', blank=True) # Field name made lowercase.
    fakt = models.ForeignKey(MpMultimedia, null=True, db_column='FAKT_ID', blank=True) # Field name made lowercase.
    fakt_zeit = models.DateTimeField(null=True, db_column='FAKT_ZEIT', blank=True) # Field name made lowercase.
    fakt_nr = models.CharField(max_length=768, db_column='FAKT_NR', blank=True) # Field name made lowercase.
    fakt_text = models.CharField(max_length=3072, db_column='FAKT_TEXT', blank=True) # Field name made lowercase.
    dln_detail = models.CharField(max_length=3072, db_column='DLN_DETAIL', blank=True) # Field name made lowercase.
    dlg_detail = models.CharField(max_length=3072, db_column='DLG_DETAIL', blank=True) # Field name made lowercase.
    whr = models.ForeignKey(Waehrung, null=True, db_column='WHR_ID', blank=True) # Field name made lowercase.
    whr_land = models.ForeignKey(Land, related_name='whrlandkrerev', null=True, db_column='WHR_LAND_ID', blank=True) # Field name made lowercase.
    whr_kurs = models.FloatField(null=True, db_column='WHR_KURS', blank=True) # Field name made lowercase.
    whr_text = models.CharField(max_length=3072, db_column='WHR_TEXT', blank=True) # Field name made lowercase.
    whr_excl = models.FloatField(null=True, db_column='WHR_EXCL', blank=True) # Field name made lowercase.
    whr_inkl = models.FloatField(null=True, db_column='WHR_INKL', blank=True) # Field name made lowercase.
    vat = models.ForeignKey(Kommission, db_column='VAT_ID') # Field name made lowercase.
    vat_land = models.ForeignKey(Land, related_name='vatlandkrerev', null=True, db_column='VAT_LAND_ID', blank=True) # Field name made lowercase.
    vat = models.FloatField(null=True, db_column='VAT', blank=True) # Field name made lowercase.
    vat_text = models.CharField(max_length=3072, db_column='VAT_TEXT', blank=True) # Field name made lowercase.
    rst_excl = models.FloatField(null=True, db_column='RST_EXCL', blank=True) # Field name made lowercase.
    rst_inkl = models.FloatField(null=True, db_column='RST_INKL', blank=True) # Field name made lowercase.
    rst_gewinn = models.FloatField(null=True, db_column='RST_GEWINN', blank=True) # Field name made lowercase.
    opt_text = models.CharField(max_length=3072, db_column='OPT_TEXT', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'mp_kreditor'

class MpDebitor(models.Model):
    deb_id = models.IntegerField(primary_key=True, db_column='DEB_ID') # Field name made lowercase.
    bid = models.ForeignKey(Buchung, db_column='BID') # Field name made lowercase.
    sta_id = models.IntegerField(null=True, db_column='STA_ID', blank=True) # Field name made lowercase.
    kid = models.ForeignKey(Personen, null=True, db_column='KID', blank=True) # Field name made lowercase.
    konto = models.CharField(max_length=768, db_column='KONTO', blank=True) # Field name made lowercase.
    nachsaldo = models.FloatField(null=True, db_column='NACHSALDO', blank=True) # Field name made lowercase.
    k = models.ForeignKey(Kollektiv, null=True, db_column='K_ID', blank=True) # Field name made lowercase.
    fakt = models.ForeignKey(MpMultimedia, null=True, db_column='FAKT_ID', blank=True) # Field name made lowercase.
    fakt_zeit = models.DateTimeField(null=True, db_column='FAKT_ZEIT', blank=True) # Field name made lowercase.
    fakt_nr = models.CharField(max_length=768, db_column='FAKT_NR', blank=True) # Field name made lowercase.
    fakt_text = models.CharField(max_length=3072, db_column='FAKT_TEXT', blank=True) # Field name made lowercase.
    dln_detail = models.CharField(max_length=3072, db_column='DLN_DETAIL', blank=True) # Field name made lowercase.
    dlg_detail = models.CharField(max_length=3072, db_column='DLG_DETAIL', blank=True) # Field name made lowercase.
    whr = models.ForeignKey(Waehrung, null=True, db_column='WHR_ID', blank=True) # Field name made lowercase.
    whr_land = models.ForeignKey(Land, related_name='whrlandrev', null=True, db_column='WHR_LAND_ID', blank=True) # Field name made lowercase.
    whr_kurs = models.FloatField(null=True, db_column='WHR_KURS', blank=True) # Field name made lowercase.
    whr_text = models.CharField(max_length=3072, db_column='WHR_TEXT', blank=True) # Field name made lowercase.
    whr_excl = models.FloatField(null=True, db_column='WHR_EXCL', blank=True) # Field name made lowercase.
    whr_inkl = models.FloatField(null=True, db_column='WHR_INKL', blank=True) # Field name made lowercase.
    vat = models.ForeignKey(Kommission, db_column='VAT_ID') # Field name made lowercase.
    vat_land = models.ForeignKey(Land, related_name='vatlandrev', null=True, db_column='VAT_LAND_ID', blank=True) # Field name made lowercase.
    vat = models.FloatField(null=True, db_column='VAT', blank=True) # Field name made lowercase.
    vat_text = models.CharField(max_length=3072, db_column='VAT_TEXT', blank=True) # Field name made lowercase.
    rst_excl = models.FloatField(null=True, db_column='RST_EXCL', blank=True) # Field name made lowercase.
    rst_inkl = models.FloatField(null=True, db_column='RST_INKL', blank=True) # Field name made lowercase.
    rst_gewinn = models.FloatField(null=True, db_column='RST_GEWINN', blank=True) # Field name made lowercase.
    opt_text = models.CharField(max_length=3072, db_column='OPT_TEXT', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'mp_debitor'

class MpGemeinRes(models.Model):
    pers = models.ForeignKey(Personen, primary_key=True, db_column='PERS_ID') # Field name made lowercase.
    dl = models.ForeignKey(DlgParts, db_column='DL_ID') # Field name made lowercase.
    teil = models.IntegerField(primary_key=True, db_column='TEIL') # Field name made lowercase.
    bid = models.ForeignKey(Buchung, db_column='BID') # Field name made lowercase.
    gpers_id = models.IntegerField(primary_key=True, db_column='GPERS_ID') # Field name made lowercase.
    class Meta:
        db_table = u'mp_gemein_res'

class MpKapa(models.Model):
    kat = models.ForeignKey(Kategorie, primary_key=True, db_column='KAT_ID') # Field name made lowercase.
    katbez_id = models.IntegerField(null=True, db_column='KATBEZ_ID', blank=True) # Field name made lowercase.
    dlt = models.ForeignKey(DienstTraeger, db_column='DLT_ID') # Field name made lowercase.
    dltbez_id = models.IntegerField(null=True, db_column='DLTBEZ_ID', blank=True) # Field name made lowercase.
    dl = models.ForeignKey(DlgParts, db_column='DL_ID') # Field name made lowercase.
    dlbez_id = models.IntegerField(null=True, db_column='DLBEZ_ID', blank=True) # Field name made lowercase.
    anz = models.IntegerField(null=True, db_column='ANZ', blank=True) # Field name made lowercase.
    busy = models.IntegerField(null=True, db_column='BUSY', blank=True) # Field name made lowercase.
    von_dat = models.IntegerField(primary_key=True, db_column='VON_DAT') # Field name made lowercase.
    bis_dat = models.IntegerField(primary_key=True, db_column='BIS_DAT') # Field name made lowercase.
    class Meta:
        db_table = u'mp_kapa'

class MpKolPers(models.Model):
    pers = models.ForeignKey(Personen, primary_key=True, db_column='PERS_ID') # Field name made lowercase.
    adr_typ = models.IntegerField(primary_key=True, db_column='ADR_TYP') # Field name made lowercase.
    mpid = models.ForeignKey(MpProfil, db_column='MPID') # Field name made lowercase.
    k = models.ForeignKey(Kollektiv, db_column='K_ID') # Field name made lowercase.
    class Meta:
        db_table = u'mp_kol_pers'


#
# Views
#

class TdbvAct(models.Model):
    act_id = models.IntegerField(db_column='ACT_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    aflag = models.CharField(max_length=3072, db_column='AFLAG') # Field name made lowercase.
    aflagid = models.IntegerField(null=True, db_column='AFLAGID', blank=True) # Field name made lowercase.
    bflag = models.CharField(max_length=3072, db_column='BFLAG') # Field name made lowercase.
    bflagid = models.IntegerField(null=True, db_column='BFLAGID', blank=True) # Field name made lowercase.
    b2flag = models.CharField(max_length=3072, db_column='B2FLAG') # Field name made lowercase.
    b2flagid = models.IntegerField(null=True, db_column='B2FLAGID', blank=True) # Field name made lowercase.
    mflag = models.CharField(max_length=3072, db_column='MFLAG') # Field name made lowercase.
    mflagid = models.IntegerField(null=True, db_column='MFLAGID', blank=True) # Field name made lowercase.
    acttype = models.CharField(max_length=3072, db_column='ACTTYPE') # Field name made lowercase.
    acttypeid = models.IntegerField(db_column='ACTTYPEID') # Field name made lowercase.
    acttproc = models.CharField(max_length=3072, db_column='ACTTPROC') # Field name made lowercase.
    file_id = models.IntegerField(null=True, db_column='FILE_ID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_act'

class TdbvActgrp(models.Model):
    act_id = models.IntegerField(db_column='ACT_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    parentid = models.IntegerField(db_column='PARENTID') # Field name made lowercase.
    parentbez = models.CharField(max_length=3072, db_column='PARENTBEZ') # Field name made lowercase.
    ord = models.IntegerField(db_column='ORD') # Field name made lowercase.
    hostid = models.IntegerField(db_column='HOSTID') # Field name made lowercase.
    host = models.CharField(max_length=3072, db_column='HOST') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_actgrp'

class TdbvActpara(models.Model):
    acttype_id = models.IntegerField(db_column='ACTTYPE_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    code = models.CharField(max_length=3072, db_column='CODE') # Field name made lowercase.
    no = models.IntegerField(db_column='NO') # Field name made lowercase.
    para = models.CharField(max_length=3072, db_column='PARA') # Field name made lowercase.
    paratypeid = models.IntegerField(null=True, db_column='PARATYPEID', blank=True) # Field name made lowercase.
    mand = models.IntegerField(null=True, db_column='MAND', blank=True) # Field name made lowercase.
    flag = models.IntegerField(null=True, db_column='FLAG', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_actpara'

class TdbvActsel(models.Model):
    act_id = models.IntegerField(db_column='ACT_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_actsel'

class TdbvActt(models.Model):
    acttype_id = models.IntegerField(db_column='ACTTYPE_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    code = models.CharField(max_length=3072, db_column='CODE') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_actt'

class TdbvActtsel(models.Model):
    acttype_id = models.IntegerField(db_column='ACTTYPE_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    code = models.CharField(max_length=3072, db_column='CODE') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_acttsel'

class TdbvAdr(models.Model):
    pers_id = models.IntegerField(db_column='PERS_ID') # Field name made lowercase.
    ans = models.CharField(max_length=768, db_column='ANS', blank=True) # Field name made lowercase.
    adr1 = models.CharField(max_length=3072, db_column='ADR1', blank=True) # Field name made lowercase.
    adr2 = models.CharField(max_length=3072, db_column='ADR2', blank=True) # Field name made lowercase.
    adr3 = models.CharField(max_length=3072, db_column='ADR3', blank=True) # Field name made lowercase.
    plz = models.CharField(max_length=768, db_column='PLZ', blank=True) # Field name made lowercase.
    ort = models.CharField(max_length=768, db_column='ORT', blank=True) # Field name made lowercase.
    kant = models.CharField(max_length=768, db_column='KANT', blank=True) # Field name made lowercase.
    land_id = models.IntegerField(null=True, db_column='LAND_ID', blank=True) # Field name made lowercase.
    land = models.CharField(max_length=3072, db_column='LAND') # Field name made lowercase.
    landsid = models.IntegerField(db_column='LANDSID') # Field name made lowercase.
    adrtyp = models.CharField(max_length=3072, db_column='ADRTYP') # Field name made lowercase.
    adrtypid = models.IntegerField(db_column='ADRTYPID') # Field name made lowercase.
    adrsta = models.CharField(max_length=3072, db_column='ADRSTA') # Field name made lowercase.
    adrstaid = models.IntegerField(null=True, db_column='ADRSTAID', blank=True) # Field name made lowercase.
    mainflag = models.IntegerField(null=True, db_column='MAINFLAG', blank=True) # Field name made lowercase.
    invoiceflag = models.IntegerField(null=True, db_column='INVOICEFLAG', blank=True) # Field name made lowercase.
    mailflag = models.IntegerField(null=True, db_column='MAILFLAG', blank=True) # Field name made lowercase.
    tel = models.CharField(max_length=768, db_column='TEL', blank=True) # Field name made lowercase.
    handy = models.CharField(max_length=768, db_column='HANDY', blank=True) # Field name made lowercase.
    fax = models.CharField(max_length=768, db_column='FAX', blank=True) # Field name made lowercase.
    tlx = models.CharField(max_length=768, db_column='TLX', blank=True) # Field name made lowercase.
    email = models.CharField(max_length=3072, db_column='EMAIL', blank=True) # Field name made lowercase.
    web = models.CharField(max_length=3072, db_column='WEB', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_adr'

class TdbvArr(models.Model):
    arr_id = models.IntegerField(db_column='ARR_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    adat = models.DateTimeField(null=True, db_column='ADAT', blank=True) # Field name made lowercase.
    prg_id = models.IntegerField(db_column='PRG_ID') # Field name made lowercase.
    prg = models.CharField(max_length=3072, db_column='PRG') # Field name made lowercase.
    sai_id = models.IntegerField(db_column='SAI_ID') # Field name made lowercase.
    sai = models.CharField(max_length=3072, db_column='SAI') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_arr'

class TdbvArrsel(models.Model):
    arr_id = models.IntegerField(db_column='ARR_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    adat = models.DateTimeField(null=True, db_column='ADAT', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_arrsel'

class TdbvCat(models.Model):
    cat_id = models.IntegerField(db_column='CAT_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    h_kat_id = models.IntegerField(null=True, db_column='H_KAT_ID', blank=True) # Field name made lowercase.
    suptyp = models.CharField(max_length=3072, db_column='SUPTYP') # Field name made lowercase.
    suptypid = models.IntegerField(db_column='SUPTYPID') # Field name made lowercase.
    ga = models.IntegerField(null=True, db_column='GA', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_cat'

class TdbvCatsel(models.Model):
    cat_id = models.IntegerField(db_column='CAT_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_catsel'

class TdbvCattree(models.Model):
    cat_id = models.IntegerField(db_column='CAT_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    h_kat_id = models.IntegerField(null=True, db_column='H_KAT_ID', blank=True) # Field name made lowercase.
    hbez = models.CharField(max_length=3072, db_column='HBEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_cattree'

class TdbvCity(models.Model):
    ort_id = models.IntegerField(db_column='ORT_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    krzl = models.CharField(max_length=768, db_column='KRZL', blank=True) # Field name made lowercase.
    landid = models.IntegerField(db_column='LANDID') # Field name made lowercase.
    landbez = models.CharField(max_length=768, db_column='LANDBEZ', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    zeitver = models.IntegerField(null=True, db_column='ZEITVER', blank=True) # Field name made lowercase.
    koord1 = models.IntegerField(null=True, db_column='KOORD1', blank=True) # Field name made lowercase.
    koord2 = models.IntegerField(null=True, db_column='KOORD2', blank=True) # Field name made lowercase.
    type = models.IntegerField(null=True, db_column='TYPE', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_city'

class TdbvCitysel(models.Model):
    ort_id = models.IntegerField(db_column='ORT_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    krzl = models.CharField(max_length=768, db_column='KRZL', blank=True) # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_citysel'

class TdbvCountry(models.Model):
    land_id = models.IntegerField(db_column='LAND_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    krzl = models.CharField(max_length=768, db_column='KRZL', blank=True) # Field name made lowercase.
    haupt_ort = models.IntegerField(null=True, db_column='HAUPT_ORT', blank=True) # Field name made lowercase.
    haupt_spr = models.IntegerField(null=True, db_column='HAUPT_SPR', blank=True) # Field name made lowercase.
    haupt_whr = models.IntegerField(null=True, db_column='HAUPT_WHR', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    vat = models.FloatField(null=True, db_column='VAT', blank=True) # Field name made lowercase.
    dateformat = models.CharField(max_length=768, db_column='DATEFORMAT', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_country'

class TdbvCountryd(models.Model):
    land_id = models.IntegerField(db_column='LAND_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    krzl = models.CharField(max_length=768, db_column='KRZL', blank=True) # Field name made lowercase.
    capitalid = models.IntegerField(null=True, db_column='CAPITALID', blank=True) # Field name made lowercase.
    capital = models.CharField(max_length=3072, db_column='CAPITAL') # Field name made lowercase.
    langid = models.IntegerField(null=True, db_column='LANGID', blank=True) # Field name made lowercase.
    lang = models.CharField(max_length=3072, db_column='LANG') # Field name made lowercase.
    curid = models.IntegerField(null=True, db_column='CURID', blank=True) # Field name made lowercase.
    currency = models.CharField(max_length=3072, db_column='CURRENCY') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    vat = models.FloatField(null=True, db_column='VAT', blank=True) # Field name made lowercase.
    dateformat = models.CharField(max_length=768, db_column='DATEFORMAT', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_countryd'

class TdbvCountrylang(models.Model):
    land_id = models.IntegerField(db_column='LAND_ID') # Field name made lowercase.
    landbez = models.CharField(max_length=3072, db_column='LANDBEZ') # Field name made lowercase.
    ccode = models.CharField(max_length=768, db_column='CCODE', blank=True) # Field name made lowercase.
    dateformat = models.CharField(max_length=768, db_column='DATEFORMAT', blank=True) # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    sbez = models.CharField(max_length=3072, db_column='SBEZ') # Field name made lowercase.
    scode = models.CharField(max_length=768, db_column='SCODE') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_countrylang'

class TdbvCountrysel(models.Model):
    land_id = models.IntegerField(db_column='LAND_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    krzl = models.CharField(max_length=768, db_column='KRZL', blank=True) # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_countrysel'

class TdbvCur(models.Model):
    whr_id = models.IntegerField(db_column='WHR_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    krzl = models.CharField(max_length=768, db_column='KRZL', blank=True) # Field name made lowercase.
    status = models.IntegerField(null=True, db_column='STATUS', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_cur'

class TdbvCursel(models.Model):
    whr_id = models.IntegerField(db_column='WHR_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    krzl = models.CharField(max_length=768, db_column='KRZL', blank=True) # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_cursel'

class TdbvCust(models.Model):
    pers_id = models.IntegerField(db_column='PERS_ID') # Field name made lowercase.
    name = models.CharField(max_length=1536, db_column='NAME') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    sta_id = models.IntegerField(null=True, db_column='STA_ID', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    custtypeid = models.IntegerField(db_column='CUSTTYPEID') # Field name made lowercase.
    tel = models.CharField(max_length=768, db_column='TEL', blank=True) # Field name made lowercase.
    handy = models.CharField(max_length=768, db_column='HANDY', blank=True) # Field name made lowercase.
    fax = models.CharField(max_length=768, db_column='FAX', blank=True) # Field name made lowercase.
    tlx = models.CharField(max_length=768, db_column='TLX', blank=True) # Field name made lowercase.
    email = models.CharField(max_length=3072, db_column='EMAIL', blank=True) # Field name made lowercase.
    web = models.CharField(max_length=3072, db_column='WEB', blank=True) # Field name made lowercase.
    account = models.CharField(max_length=768, db_column='ACCOUNT', blank=True) # Field name made lowercase.
    manager = models.IntegerField(null=True, db_column='MANAGER', blank=True) # Field name made lowercase.
    attr1 = models.CharField(max_length=3072, db_column='ATTR1', blank=True) # Field name made lowercase.
    attr2 = models.CharField(max_length=3072, db_column='ATTR2', blank=True) # Field name made lowercase.
    curid = models.IntegerField(db_column='CURID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_cust'

class TdbvCustadr(models.Model):
    pers_id = models.IntegerField(db_column='PERS_ID') # Field name made lowercase.
    ans = models.CharField(max_length=768, db_column='ANS', blank=True) # Field name made lowercase.
    name = models.CharField(max_length=1536, db_column='NAME') # Field name made lowercase.
    lang = models.CharField(max_length=3072, db_column='LANG') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    perssta = models.CharField(max_length=3072, db_column='PERSSTA') # Field name made lowercase.
    persstaid = models.IntegerField(null=True, db_column='PERSSTAID', blank=True) # Field name made lowercase.
    adr1 = models.CharField(max_length=3072, db_column='ADR1', blank=True) # Field name made lowercase.
    adr2 = models.CharField(max_length=3072, db_column='ADR2', blank=True) # Field name made lowercase.
    adr3 = models.CharField(max_length=3072, db_column='ADR3', blank=True) # Field name made lowercase.
    plz = models.CharField(max_length=768, db_column='PLZ', blank=True) # Field name made lowercase.
    ort = models.CharField(max_length=768, db_column='ORT', blank=True) # Field name made lowercase.
    kant = models.CharField(max_length=768, db_column='KANT', blank=True) # Field name made lowercase.
    land_id = models.IntegerField(null=True, db_column='LAND_ID', blank=True) # Field name made lowercase.
    land = models.CharField(max_length=3072, db_column='LAND') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    custtype = models.CharField(max_length=768, db_column='CUSTTYPE', blank=True) # Field name made lowercase.
    custtypeid = models.IntegerField(db_column='CUSTTYPEID') # Field name made lowercase.
    ctel = models.CharField(max_length=768, db_column='CTEL', blank=True) # Field name made lowercase.
    chandy = models.CharField(max_length=768, db_column='CHANDY', blank=True) # Field name made lowercase.
    cfax = models.CharField(max_length=768, db_column='CFAX', blank=True) # Field name made lowercase.
    ctlx = models.CharField(max_length=768, db_column='CTLX', blank=True) # Field name made lowercase.
    cemail = models.CharField(max_length=3072, db_column='CEMAIL', blank=True) # Field name made lowercase.
    cweb = models.CharField(max_length=3072, db_column='CWEB', blank=True) # Field name made lowercase.
    account = models.CharField(max_length=768, db_column='ACCOUNT', blank=True) # Field name made lowercase.
    manager = models.IntegerField(null=True, db_column='MANAGER', blank=True) # Field name made lowercase.
    attr1 = models.CharField(max_length=3072, db_column='ATTR1', blank=True) # Field name made lowercase.
    attr2 = models.CharField(max_length=3072, db_column='ATTR2', blank=True) # Field name made lowercase.
    adrtyp = models.CharField(max_length=3072, db_column='ADRTYP') # Field name made lowercase.
    adrtypid = models.IntegerField(db_column='ADRTYPID') # Field name made lowercase.
    adrsta = models.CharField(max_length=3072, db_column='ADRSTA') # Field name made lowercase.
    adrstaid = models.IntegerField(null=True, db_column='ADRSTAID', blank=True) # Field name made lowercase.
    mainflag = models.IntegerField(null=True, db_column='MAINFLAG', blank=True) # Field name made lowercase.
    invoiceflag = models.IntegerField(null=True, db_column='INVOICEFLAG', blank=True) # Field name made lowercase.
    mailflag = models.IntegerField(null=True, db_column='MAILFLAG', blank=True) # Field name made lowercase.
    tel = models.CharField(max_length=768, db_column='TEL', blank=True) # Field name made lowercase.
    handy = models.CharField(max_length=768, db_column='HANDY', blank=True) # Field name made lowercase.
    fax = models.CharField(max_length=768, db_column='FAX', blank=True) # Field name made lowercase.
    tlx = models.CharField(max_length=768, db_column='TLX', blank=True) # Field name made lowercase.
    email = models.CharField(max_length=3072, db_column='EMAIL', blank=True) # Field name made lowercase.
    web = models.CharField(max_length=3072, db_column='WEB', blank=True) # Field name made lowercase.
    curid = models.IntegerField(db_column='CURID') # Field name made lowercase.
    cur = models.CharField(max_length=768, db_column='CUR', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_custadr'

class TdbvCustsel(models.Model):
    pers_id = models.IntegerField(db_column='PERS_ID') # Field name made lowercase.
    name = models.CharField(max_length=1536, db_column='NAME') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_custsel'

class TdbvCutt(models.Model):
    custtype_id = models.IntegerField(db_column='CUSTTYPE_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_cutt'

class TdbvCuttsel(models.Model):
    custtype_id = models.IntegerField(db_column='CUSTTYPE_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_cuttsel'

class TdbvDlt(models.Model):
    dlt_id = models.IntegerField(db_column='DLT_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    h_dlt_id = models.IntegerField(db_column='H_DLT_ID') # Field name made lowercase.
    hostid = models.IntegerField(db_column='HOSTID') # Field name made lowercase.
    dlt_grp_id = models.IntegerField(db_column='DLT_GRP_ID') # Field name made lowercase.
    typ = models.CharField(max_length=3072, db_column='TYP') # Field name made lowercase.
    typid = models.IntegerField(db_column='TYPID') # Field name made lowercase.
    cat = models.CharField(max_length=3072, db_column='CAT') # Field name made lowercase.
    cat_id = models.IntegerField(null=True, db_column='CAT_ID', blank=True) # Field name made lowercase.
    levelplace = models.IntegerField(db_column='LEVELPLACE') # Field name made lowercase.
    numplace = models.IntegerField(null=True, db_column='NUMPLACE', blank=True) # Field name made lowercase.
    sta = models.CharField(max_length=3072, db_column='STA') # Field name made lowercase.
    staid = models.IntegerField(null=True, db_column='STAID', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_dlt'

class TdbvDltoperator(models.Model):
    dlt_id = models.IntegerField(db_column='DLT_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    company = models.CharField(max_length=1536, db_column='COMPANY') # Field name made lowercase.
    companyid = models.IntegerField(db_column='COMPANYID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_dltoperator'

class TdbvDltsel(models.Model):
    dlt_id = models.IntegerField(db_column='DLT_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_dltsel'

class TdbvDltt(models.Model):
    typ_id = models.IntegerField(db_column='TYP_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    h_typ_id = models.IntegerField(db_column='H_TYP_ID') # Field name made lowercase.
    host_typ = models.IntegerField(db_column='HOST_TYP') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_dltt'

class TdbvDlttree(models.Model):
    dlt_id = models.IntegerField(db_column='DLT_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    parentid = models.IntegerField(db_column='PARENTID') # Field name made lowercase.
    parent = models.CharField(max_length=3072, db_column='PARENT') # Field name made lowercase.
    hostid = models.IntegerField(db_column='HOSTID') # Field name made lowercase.
    host = models.CharField(max_length=3072, db_column='HOST') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_dlttree'

class TdbvDlttsel(models.Model):
    typ_id = models.IntegerField(db_column='TYP_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_dlttsel'

class TdbvDltttree(models.Model):
    typ_id = models.IntegerField(db_column='TYP_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    h_typ_id = models.IntegerField(db_column='H_TYP_ID') # Field name made lowercase.
    hbez = models.CharField(max_length=3072, db_column='HBEZ') # Field name made lowercase.
    host_typ = models.IntegerField(db_column='HOST_TYP') # Field name made lowercase.
    hostbez = models.CharField(max_length=3072, db_column='HOSTBEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_dltttree'

class TdbvGrpt(models.Model):
    grptype_id = models.IntegerField(db_column='GRPTYPE_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_grpt'

class TdbvGrptsel(models.Model):
    grptype_id = models.IntegerField(db_column='GRPTYPE_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_grptsel'

class TdbvLang(models.Model):
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    sysbez = models.CharField(max_length=768, db_column='SYSBEZ') # Field name made lowercase.
    dialog = models.IntegerField(db_column='DIALOG') # Field name made lowercase.
    output = models.IntegerField(null=True, db_column='OUTPUT', blank=True) # Field name made lowercase.
    gui = models.IntegerField(null=True, db_column='GUI', blank=True) # Field name made lowercase.
    bezsprid = models.IntegerField(db_column='BEZSPRID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_lang'

class TdbvLangsel(models.Model):
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    sysbez = models.CharField(max_length=768, db_column='SYSBEZ') # Field name made lowercase.
    bezsprid = models.IntegerField(db_column='BEZSPRID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_langsel'

class TdbvO(models.Model):
    o_id = models.IntegerField(db_column='O_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    hosto = models.CharField(max_length=768, db_column='HOSTO', blank=True) # Field name made lowercase.
    hosto_id = models.IntegerField(db_column='HOSTO_ID') # Field name made lowercase.
    ord = models.IntegerField(db_column='ORD') # Field name made lowercase.
    sup = models.CharField(max_length=768, db_column='SUP', blank=True) # Field name made lowercase.
    supid = models.IntegerField(db_column='SUPID') # Field name made lowercase.
    act = models.CharField(max_length=3072, db_column='ACT') # Field name made lowercase.
    actid = models.IntegerField(db_column='ACTID') # Field name made lowercase.
    location = models.CharField(max_length=768, db_column='LOCATION') # Field name made lowercase.
    ot = models.CharField(max_length=3072, db_column='OT') # Field name made lowercase.
    otid = models.IntegerField(db_column='OTID') # Field name made lowercase.
    duration = models.DateTimeField(null=True, db_column='DURATION', blank=True) # Field name made lowercase.
    fromcity = models.CharField(max_length=768, db_column='FROMCITY', blank=True) # Field name made lowercase.
    fromcityid = models.IntegerField(db_column='FROMCITYID') # Field name made lowercase.
    tocity = models.CharField(max_length=768, db_column='TOCITY', blank=True) # Field name made lowercase.
    tocityid = models.IntegerField(db_column='TOCITYID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_o'

class TdbvOsel(models.Model):
    o_id = models.IntegerField(db_column='O_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_osel'

class TdbvOt(models.Model):
    ot_id = models.IntegerField(db_column='OT_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_ot'

class TdbvOtsel(models.Model):
    ot_id = models.IntegerField(db_column='OT_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_otsel'

class TdbvPers(models.Model):
    pers_id = models.IntegerField(db_column='PERS_ID') # Field name made lowercase.
    firstname = models.CharField(max_length=1536, db_column='FIRSTNAME') # Field name made lowercase.
    lastname = models.CharField(max_length=1536, db_column='LASTNAME') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    sta_id = models.IntegerField(null=True, db_column='STA_ID', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    perstypeid = models.IntegerField(db_column='PERSTYPEID') # Field name made lowercase.
    sex = models.IntegerField(null=True, db_column='SEX', blank=True) # Field name made lowercase.
    muttersid = models.IntegerField(null=True, db_column='MUTTERSID', blank=True) # Field name made lowercase.
    age = models.CharField(max_length=768, db_column='AGE', blank=True) # Field name made lowercase.
    passport = models.CharField(max_length=768, db_column='PASSPORT', blank=True) # Field name made lowercase.
    attr1 = models.CharField(max_length=3072, db_column='ATTR1', blank=True) # Field name made lowercase.
    attr2 = models.CharField(max_length=3072, db_column='ATTR2', blank=True) # Field name made lowercase.
    rtextid = models.IntegerField(null=True, db_column='RTEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_pers'

class TdbvPersadr(models.Model):
    pers_id = models.IntegerField(db_column='PERS_ID') # Field name made lowercase.
    ans = models.CharField(max_length=768, db_column='ANS', blank=True) # Field name made lowercase.
    firstname = models.CharField(max_length=1536, db_column='FIRSTNAME') # Field name made lowercase.
    lastname = models.CharField(max_length=1536, db_column='LASTNAME') # Field name made lowercase.
    lang = models.CharField(max_length=3072, db_column='LANG') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    perssta = models.CharField(max_length=3072, db_column='PERSSTA') # Field name made lowercase.
    persstaid = models.IntegerField(null=True, db_column='PERSSTAID', blank=True) # Field name made lowercase.
    adr1 = models.CharField(max_length=3072, db_column='ADR1', blank=True) # Field name made lowercase.
    adr2 = models.CharField(max_length=3072, db_column='ADR2', blank=True) # Field name made lowercase.
    adr3 = models.CharField(max_length=3072, db_column='ADR3', blank=True) # Field name made lowercase.
    plz = models.CharField(max_length=768, db_column='PLZ', blank=True) # Field name made lowercase.
    ort = models.CharField(max_length=768, db_column='ORT', blank=True) # Field name made lowercase.
    kant = models.CharField(max_length=768, db_column='KANT', blank=True) # Field name made lowercase.
    land_id = models.IntegerField(null=True, db_column='LAND_ID', blank=True) # Field name made lowercase.
    land = models.CharField(max_length=3072, db_column='LAND') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    perstype = models.CharField(max_length=768, db_column='PERSTYPE', blank=True) # Field name made lowercase.
    perstypeid = models.IntegerField(db_column='PERSTYPEID') # Field name made lowercase.
    sex = models.IntegerField(null=True, db_column='SEX', blank=True) # Field name made lowercase.
    muttersid = models.IntegerField(null=True, db_column='MUTTERSID', blank=True) # Field name made lowercase.
    age = models.CharField(max_length=768, db_column='AGE', blank=True) # Field name made lowercase.
    passport = models.CharField(max_length=768, db_column='PASSPORT', blank=True) # Field name made lowercase.
    attr1 = models.CharField(max_length=3072, db_column='ATTR1', blank=True) # Field name made lowercase.
    attr2 = models.CharField(max_length=3072, db_column='ATTR2', blank=True) # Field name made lowercase.
    rtextid = models.IntegerField(null=True, db_column='RTEXTID', blank=True) # Field name made lowercase.
    adrtyp = models.CharField(max_length=3072, db_column='ADRTYP') # Field name made lowercase.
    adrtypid = models.IntegerField(db_column='ADRTYPID') # Field name made lowercase.
    adrsta = models.CharField(max_length=3072, db_column='ADRSTA') # Field name made lowercase.
    adrstaid = models.IntegerField(null=True, db_column='ADRSTAID', blank=True) # Field name made lowercase.
    mainflag = models.IntegerField(null=True, db_column='MAINFLAG', blank=True) # Field name made lowercase.
    invoiceflag = models.IntegerField(null=True, db_column='INVOICEFLAG', blank=True) # Field name made lowercase.
    mailflag = models.IntegerField(null=True, db_column='MAILFLAG', blank=True) # Field name made lowercase.
    tel = models.CharField(max_length=768, db_column='TEL', blank=True) # Field name made lowercase.
    handy = models.CharField(max_length=768, db_column='HANDY', blank=True) # Field name made lowercase.
    fax = models.CharField(max_length=768, db_column='FAX', blank=True) # Field name made lowercase.
    tlx = models.CharField(max_length=768, db_column='TLX', blank=True) # Field name made lowercase.
    email = models.CharField(max_length=3072, db_column='EMAIL', blank=True) # Field name made lowercase.
    web = models.CharField(max_length=3072, db_column='WEB', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_persadr'

class TdbvPerssel(models.Model):
    pers_id = models.IntegerField(db_column='PERS_ID') # Field name made lowercase.
    firstname = models.CharField(max_length=1536, db_column='FIRSTNAME') # Field name made lowercase.
    lastname = models.CharField(max_length=1536, db_column='LASTNAME') # Field name made lowercase.
    sex = models.IntegerField(null=True, db_column='SEX', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_perssel'

class TdbvPerst(models.Model):
    perstype_id = models.IntegerField(db_column='PERSTYPE_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    vonalter = models.IntegerField(null=True, db_column='VONALTER', blank=True) # Field name made lowercase.
    bisalter = models.IntegerField(null=True, db_column='BISALTER', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_perst'

class TdbvPerstsel(models.Model):
    perstype_id = models.IntegerField(db_column='PERSTYPE_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_perstsel'

class TdbvPrg(models.Model):
    prg_id = models.IntegerField(db_column='PRG_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    sai_id = models.IntegerField(db_column='SAI_ID') # Field name made lowercase.
    sai = models.CharField(max_length=3072, db_column='SAI') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_prg'

class TdbvPrgsel(models.Model):
    prg_id = models.IntegerField(db_column='PRG_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_prgsel'

class TdbvPrt(models.Model):
    prt_id = models.IntegerField(db_column='PRT_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_prt'

class TdbvPrtsel(models.Model):
    prt_id = models.IntegerField(db_column='PRT_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_prtsel'

class TdbvRatesel(models.Model):
    land_id = models.IntegerField(db_column='LAND_ID') # Field name made lowercase.
    landbez = models.CharField(max_length=3072, db_column='LANDBEZ') # Field name made lowercase.
    whr_id = models.IntegerField(db_column='WHR_ID') # Field name made lowercase.
    whrbez = models.CharField(max_length=3072, db_column='WHRBEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    kurs_typ = models.IntegerField(db_column='KURS_TYP') # Field name made lowercase.
    a_kurs = models.FloatField(db_column='A_KURS') # Field name made lowercase.
    v_kurs = models.FloatField(db_column='V_KURS') # Field name made lowercase.
    fromdat = models.DateTimeField(null=True, db_column='FROMDAT', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_ratesel'

class TdbvSai(models.Model):
    sai_id = models.IntegerField(db_column='SAI_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    von = models.DateTimeField(null=True, db_column='VON', blank=True) # Field name made lowercase.
    bis = models.DateTimeField(null=True, db_column='BIS', blank=True) # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_sai'

class TdbvSaisel(models.Model):
    sai_id = models.IntegerField(db_column='SAI_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_saisel'

class TdbvServ(models.Model):
    serv_id = models.IntegerField(db_column='SERV_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    season = models.CharField(max_length=3072, db_column='SEASON') # Field name made lowercase.
    seasonid = models.IntegerField(db_column='SEASONID') # Field name made lowercase.
    adat = models.DateTimeField(null=True, db_column='ADAT', blank=True) # Field name made lowercase.
    act = models.CharField(max_length=3072, db_column='ACT') # Field name made lowercase.
    actid = models.IntegerField(null=True, db_column='ACTID', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_serv'

class TdbvServsel(models.Model):
    serv_id = models.IntegerField(db_column='SERV_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    adat = models.DateTimeField(null=True, db_column='ADAT', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_servsel'

class TdbvSo(models.Model):
    so_id = models.IntegerField(db_column='SO_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    textid = models.IntegerField(null=True, db_column='TEXTID', blank=True) # Field name made lowercase.
    startdat = models.DateTimeField(null=True, db_column='STARTDAT', blank=True) # Field name made lowercase.
    stopdat = models.DateTimeField(null=True, db_column='STOPDAT', blank=True) # Field name made lowercase.
    hostso = models.CharField(max_length=768, db_column='HOSTSO', blank=True) # Field name made lowercase.
    hostsoid = models.IntegerField(db_column='HOSTSOID') # Field name made lowercase.
    offer = models.CharField(max_length=768, db_column='OFFER', blank=True) # Field name made lowercase.
    offerid = models.IntegerField(db_column='OFFERID') # Field name made lowercase.
    ord = models.IntegerField(null=True, db_column='ORD', blank=True) # Field name made lowercase.
    resflag = models.CharField(max_length=3072, db_column='RESFLAG') # Field name made lowercase.
    resflagid = models.IntegerField(db_column='RESFLAGID') # Field name made lowercase.
    operator = models.CharField(max_length=1536, db_column='OPERATOR') # Field name made lowercase.
    operatorid = models.IntegerField(null=True, db_column='OPERATORID', blank=True) # Field name made lowercase.
    account = models.CharField(max_length=768, db_column='ACCOUNT', blank=True) # Field name made lowercase.
    invoice = models.CharField(max_length=1536, db_column='INVOICE') # Field name made lowercase.
    invoiceid = models.IntegerField(null=True, db_column='INVOICEID', blank=True) # Field name made lowercase.
    season = models.CharField(max_length=3072, db_column='SEASON') # Field name made lowercase.
    seasonid = models.IntegerField(db_column='SEASONID') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_so'

class TdbvSosel(models.Model):
    so_id = models.IntegerField(db_column='SO_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    code = models.CharField(max_length=768, db_column='CODE', blank=True) # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    startdat = models.DateTimeField(null=True, db_column='STARTDAT', blank=True) # Field name made lowercase.
    stopdat = models.DateTimeField(null=True, db_column='STOPDAT', blank=True) # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_sosel'

class TdbvSta(models.Model):
    sta_id = models.IntegerField(db_column='STA_ID') # Field name made lowercase.
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    abk = models.CharField(max_length=768, db_column='ABK') # Field name made lowercase.
    sta = models.CharField(max_length=3072, db_column='STA') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    kond = models.FloatField(db_column='KOND') # Field name made lowercase.
    typ = models.IntegerField(db_column='TYP') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_sta'

class TdbvStasel(models.Model):
    sta_id = models.IntegerField(db_column='STA_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    code = models.CharField(max_length=3072, db_column='CODE') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    typ = models.IntegerField(db_column='TYP') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_stasel'

class TdbvUser(models.Model):
    mpid = models.IntegerField(db_column='MPID') # Field name made lowercase.
    tdbuser = models.CharField(max_length=384, db_column='TDBUSER') # Field name made lowercase.
    bchst = models.CharField(max_length=1536, db_column='BCHST') # Field name made lowercase.
    bchstid = models.IntegerField(db_column='BCHSTID') # Field name made lowercase.
    seclevel = models.IntegerField(db_column='SECLEVEL') # Field name made lowercase.
    lang = models.CharField(max_length=3072, db_column='LANG') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    country = models.CharField(max_length=3072, db_column='COUNTRY') # Field name made lowercase.
    land_id = models.IntegerField(db_column='LAND_ID') # Field name made lowercase.
    suptype = models.CharField(max_length=3072, db_column='SUPTYPE') # Field name made lowercase.
    dltt_id = models.IntegerField(db_column='DLTT_ID') # Field name made lowercase.
    dlt = models.CharField(max_length=768, db_column='DLT', blank=True) # Field name made lowercase.
    dlt_id = models.IntegerField(db_column='DLT_ID') # Field name made lowercase.
    kat = models.CharField(max_length=3072, db_column='KAT') # Field name made lowercase.
    kat_id = models.IntegerField(db_column='KAT_ID') # Field name made lowercase.
    dlat = models.CharField(max_length=3072, db_column='DLAT') # Field name made lowercase.
    dlat_id = models.IntegerField(db_column='DLAT_ID') # Field name made lowercase.
    dlnt = models.CharField(max_length=768, db_column='DLNT', blank=True) # Field name made lowercase.
    dlnt_id = models.IntegerField(db_column='DLNT_ID') # Field name made lowercase.
    season = models.CharField(max_length=768, db_column='SEASON', blank=True) # Field name made lowercase.
    sai_id = models.IntegerField(db_column='SAI_ID') # Field name made lowercase.
    prg = models.CharField(max_length=768, db_column='PRG', blank=True) # Field name made lowercase.
    prg_id = models.IntegerField(db_column='PRG_ID') # Field name made lowercase.
    starttime = models.DateTimeField(null=True, db_column='STARTTIME', blank=True) # Field name made lowercase.
    endtime = models.DateTimeField(null=True, db_column='ENDTIME', blank=True) # Field name made lowercase.
    prange = models.IntegerField(db_column='PRANGE') # Field name made lowercase.
    class Meta:
        db_table = u'tdbv_user'

class MpvAktDetail(models.Model):
    bid = models.IntegerField()
    pers_id = models.IntegerField()
    dlg_id = models.IntegerField()
    dl_id = models.IntegerField()
    teil = models.IntegerField()
    z_flag = models.IntegerField()
    akt_id = models.IntegerField()
    ord = models.IntegerField()
    a_flag = models.IntegerField(null=True, blank=True)
    m_flag = models.IntegerField(null=True, blank=True)
    a_typ_id = models.IntegerField()
    proz = models.CharField(max_length=3072)
    class Meta:
        db_table = u'mpv_akt_detail'

class MpvAngebot(models.Model):
    art_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    textid = models.IntegerField(null=True, blank=True)
    class Meta:
        db_table = u'mpv_angebot'

class MpvArr(models.Model):
    arr_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    a_dat = models.DateTimeField(null=True, blank=True)
    prg_id = models.IntegerField()
    textid = models.IntegerField(null=True, blank=True)
    sai_id = models.IntegerField()
    class Meta:
        db_table = u'mpv_arr'

class MpvArrDl(models.Model):
    arr_id = models.IntegerField()
    a_dat = models.DateTimeField(null=True, blank=True)
    dlg_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    a_zeit = models.DateTimeField(null=True, blank=True)
    teil = models.IntegerField()
    prio = models.IntegerField()
    akt_id = models.IntegerField(null=True, blank=True)
    s_id = models.IntegerField()
    class Meta:
        db_table = u'mpv_arr_dl'

class MpvArrDlg(models.Model):
    arr_id = models.IntegerField()
    teil = models.IntegerField()
    prio = models.IntegerField()
    dlg_id = models.IntegerField()
    dl_id = models.IntegerField()
    ord = models.IntegerField()
    a_zeit = models.DateTimeField(null=True, blank=True)
    res_f = models.IntegerField()
    bez = models.CharField(max_length=3072)
    bez1 = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    dtg_zeit = models.DateTimeField(null=True, blank=True)
    class Meta:
        db_table = u'mpv_arr_dlg'

class MpvBuchung(models.Model):
    d_bid = models.IntegerField()
    bid = models.IntegerField()
    ref = models.CharField(max_length=768)
    arr_id = models.IntegerField()
    kid = models.IntegerField()
    sach = models.IntegerField()
    bchst = models.IntegerField()
    anw = models.IntegerField()
    b_dat = models.DateTimeField(null=True, blank=True)
    m_dat = models.DateTimeField(null=True, blank=True)
    mapo_dat = models.IntegerField(null=True, blank=True)
    mapo_opt_bst = models.IntegerField(null=True, blank=True)
    opt_bst = models.DateTimeField(null=True, blank=True)
    mapo_opt_kid = models.IntegerField(null=True, blank=True)
    opt_kid = models.DateTimeField(null=True, blank=True)
    sta = models.IntegerField()
    ast = models.IntegerField()
    sai_id = models.IntegerField()
    k_id = models.IntegerField()
    history = models.IntegerField(null=True, blank=True)
    textid = models.IntegerField(null=True, blank=True)
    class Meta:
        db_table = u'mpv_buchung'

class MpvDl(models.Model):
    dlg_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    textid = models.IntegerField(null=True, blank=True)
    sai_id = models.IntegerField()
    a_zeit = models.DateTimeField(null=True, blank=True)
    akt_id = models.IntegerField(null=True, blank=True)
    class Meta:
        db_table = u'mpv_dl'

class MpvDlTdl(models.Model):
    dlg_id = models.IntegerField()
    start_zeit = models.DateTimeField(null=True, blank=True)
    dl_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    a_zeit = models.DateTimeField(null=True, blank=True)
    e_zeit = models.DateTimeField(null=True, blank=True)
    ord = models.IntegerField()
    res_f = models.IntegerField()
    s_id = models.IntegerField()
    class Meta:
        db_table = u'mpv_dl_tdl'

class MpvDla(models.Model):
    dla_id = models.IntegerField()
    h_dla_id = models.IntegerField()
    ord = models.IntegerField()
    dlt_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    akt_id = models.IntegerField()
    ort = models.CharField(max_length=768)
    art_id = models.IntegerField()
    dau = models.IntegerField(null=True, blank=True)
    textid = models.IntegerField(null=True, blank=True)
    von = models.DateTimeField(null=True, blank=True)
    nach = models.DateTimeField(null=True, blank=True)
    class Meta:
        db_table = u'mpv_dla'

class MpvDln(models.Model):
    dln_id = models.IntegerField()
    name = models.CharField(max_length=1536)
    vor = models.CharField(max_length=1536)
    ort = models.CharField(max_length=768, blank=True)
    s_id = models.IntegerField()
    sta_id = models.IntegerField(null=True, blank=True)
    textid = models.IntegerField(null=True, blank=True)
    rkr_id = models.IntegerField()
    sex = models.IntegerField(null=True, blank=True)
    ext_txt = models.IntegerField(null=True, blank=True)
    land_id = models.IntegerField(null=True, blank=True)
    age = models.CharField(max_length=768, blank=True)
    passnr = models.CharField(max_length=768, blank=True)
    attr1 = models.CharField(max_length=3072, blank=True)
    attr2 = models.CharField(max_length=3072, blank=True)
    class Meta:
        db_table = u'mpv_dln'

class MpvDlnadr(models.Model):
    pers_id = models.IntegerField()
    ans = models.CharField(max_length=768, blank=True)
    name = models.CharField(max_length=1536)
    vor = models.CharField(max_length=1536)
    adr1 = models.CharField(max_length=3072, blank=True)
    adr2 = models.CharField(max_length=3072, blank=True)
    adr3 = models.CharField(max_length=3072, blank=True)
    plz = models.CharField(max_length=768, blank=True)
    ort = models.CharField(max_length=768, blank=True)
    land_id = models.IntegerField(null=True, blank=True)
    sta_id = models.IntegerField(null=True, blank=True)
    class Meta:
        db_table = u'mpv_dlnadr'

class MpvDlt(models.Model):
    dlt_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    kat_id = models.IntegerField(null=True, blank=True)
    h_dlt_id = models.IntegerField()
    host_id = models.IntegerField()
    typ_id = models.IntegerField()
    textid = models.IntegerField(null=True, blank=True)
    stufe = models.IntegerField()
    class Meta:
        db_table = u'mpv_dlt'

class MpvGra(models.Model):
    gra_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    dlt_id = models.IntegerField()
    dltbez = models.CharField(max_length=3072)
    textid = models.IntegerField(null=True, blank=True)
    s_id = models.IntegerField()
    class Meta:
        db_table = u'mpv_gra'

class MpvKapa(models.Model):
    kat_id = models.IntegerField()
    katbez = models.CharField(max_length=3072)
    kat_s_id = models.IntegerField()
    tdl_id = models.IntegerField()
    tdlbez = models.CharField(max_length=3072)
    tdl_s_id = models.IntegerField()
    pre_id = models.IntegerField()
    anz = models.IntegerField(null=True, blank=True)
    busy = models.IntegerField(null=True, blank=True)
    vpr = models.FloatField(null=True, blank=True)
    class Meta:
        db_table = u'mpv_kapa'

class MpvKapadet(models.Model):
    kat_id = models.IntegerField()
    katbez = models.CharField(max_length=3072)
    kat_s_id = models.IntegerField()
    tdl_id = models.IntegerField()
    tdlbez = models.CharField(max_length=3072)
    a_zeit = models.DateTimeField(null=True, blank=True)
    e_zeit = models.DateTimeField(null=True, blank=True)
    tdl_s_id = models.IntegerField()
    pre_id = models.IntegerField()
    anz = models.IntegerField(null=True, blank=True)
    busy = models.IntegerField(null=True, blank=True)
    vpr = models.FloatField(null=True, blank=True)
    class Meta:
        db_table = u'mpv_kapadet'

class MpvKar(models.Model):
    kar_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    textid = models.IntegerField(null=True, blank=True)
    class Meta:
        db_table = u'mpv_kar'

class MpvKat(models.Model):
    kat_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    h_kat_id = models.IntegerField(null=True, blank=True)
    typ_id = models.IntegerField()
    ga = models.IntegerField(null=True, blank=True)
    textid = models.IntegerField(null=True, blank=True)
    class Meta:
        db_table = u'mpv_kat'

class MpvKon(models.Model):
    kont_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    hostkont_id = models.IntegerField()
    kunden_id = models.IntegerField()
    opt_dat = models.IntegerField(null=True, blank=True)
    ref = models.CharField(max_length=768, blank=True)
    sai_id = models.IntegerField()
    textid = models.IntegerField(null=True, blank=True)
    class Meta:
        db_table = u'mpv_kon'

class MpvKoncheck(models.Model):
    hostkont_id = models.IntegerField()
    kont_id = models.IntegerField()
    kat_id = models.IntegerField()
    dlt_id = models.IntegerField()
    anz = models.IntegerField(null=True, blank=True)
    busy = models.IntegerField(null=True, blank=True)
    class Meta:
        db_table = u'mpv_koncheck'

class MpvKunadr(models.Model):
    pers_id = models.IntegerField()
    ans = models.CharField(max_length=768, blank=True)
    name = models.CharField(max_length=1536)
    adr1 = models.CharField(max_length=3072, blank=True)
    adr2 = models.CharField(max_length=3072, blank=True)
    adr3 = models.CharField(max_length=3072, blank=True)
    plz = models.CharField(max_length=768, blank=True)
    ort = models.CharField(max_length=768, blank=True)
    kant = models.CharField(max_length=768, blank=True)
    land_id = models.IntegerField(null=True, blank=True)
    sta_id = models.IntegerField(null=True, blank=True)
    k_typ_id = models.IntegerField()
    tel = models.CharField(max_length=768, blank=True)
    fax = models.CharField(max_length=768, blank=True)
    class Meta:
        db_table = u'mpv_kunadr'

class MpvKunden(models.Model):
    kun_id = models.IntegerField()
    name = models.CharField(max_length=1536)
    ort = models.CharField(max_length=768, blank=True)
    s_id = models.IntegerField()
    sta_id = models.IntegerField(null=True, blank=True)
    textid = models.IntegerField(null=True, blank=True)
    kant = models.CharField(max_length=768, blank=True)
    tel = models.CharField(max_length=768, blank=True)
    fax = models.CharField(max_length=768, blank=True)
    tlx = models.CharField(max_length=768, blank=True)
    konto = models.CharField(max_length=768, blank=True)
    leiter = models.IntegerField(null=True, blank=True)
    attr1 = models.CharField(max_length=3072, blank=True)
    attr2 = models.CharField(max_length=3072, blank=True)
    k_typ_id = models.IntegerField()
    land_id = models.IntegerField(null=True, blank=True)
    whr_id = models.IntegerField()
    class Meta:
        db_table = u'mpv_kunden'

class MpvLand(models.Model):
    land_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    krzl = models.CharField(max_length=768, blank=True)
    haupt_ort = models.IntegerField(null=True, blank=True)
    haupt_spr = models.IntegerField(null=True, blank=True)
    haupt_whr = models.IntegerField(null=True, blank=True)
    textid = models.IntegerField(null=True, blank=True)
    vat = models.FloatField(null=True, blank=True)
    class Meta:
        db_table = u'mpv_land'

class MpvLw(models.Model):
    land_id = models.IntegerField()
    landbez = models.CharField(max_length=3072)
    landbezs_id = models.IntegerField()
    whr_id = models.IntegerField()
    whrbez = models.CharField(max_length=3072)
    whrbezs_id = models.IntegerField()
    kurs_typ = models.IntegerField()
    a_kurs = models.FloatField()
    v_kurs = models.FloatField()
    class Meta:
        db_table = u'mpv_lw'

class MpvOrt(models.Model):
    ort_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    krzl = models.CharField(max_length=768, blank=True)
    landbez = models.CharField(max_length=3072)
    landbezs_id = models.IntegerField()
    textid = models.IntegerField(null=True, blank=True)
    zeitver = models.IntegerField(null=True, blank=True)
    koord1 = models.IntegerField(null=True, blank=True)
    koord2 = models.IntegerField(null=True, blank=True)
    class Meta:
        db_table = u'mpv_ort'

class MpvPrg(models.Model):
    prg_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    textid = models.IntegerField(null=True, blank=True)
    sai_id = models.IntegerField()
    class Meta:
        db_table = u'mpv_prg'

class MpvResDl(models.Model):
    bid = models.IntegerField()
    pers_id = models.IntegerField()
    name = models.CharField(max_length=1536)
    dl_id = models.IntegerField()
    dlazeit = models.DateTimeField(null=True, blank=True)
    tdl_id = models.IntegerField()
    tdlazeit = models.DateTimeField(null=True, blank=True)
    tdlezeit = models.DateTimeField(null=True, blank=True)
    resazeit = models.DateTimeField(null=True, blank=True)
    resezeit = models.DateTimeField(null=True, blank=True)
    kat_id = models.IntegerField()
    katbez = models.CharField(max_length=3072)
    typ_id = models.IntegerField()
    dlt_id = models.IntegerField()
    dltbez = models.CharField(max_length=3072)
    kont_id = models.IntegerField()
    r_sta = models.IntegerField()
    s_id = models.IntegerField()
    class Meta:
        db_table = u'mpv_res_dl'

class MpvResdl(models.Model):
    bid = models.IntegerField()
    pers_id = models.IntegerField()
    teil = models.IntegerField()
    dl_id = models.IntegerField()
    dl_bez = models.CharField(max_length=3072)
    dl_sid = models.IntegerField()
    tdl_id = models.IntegerField()
    resazeit = models.DateTimeField(null=True, blank=True)
    resezeit = models.DateTimeField(null=True, blank=True)
    kat_id = models.IntegerField()
    typ_id = models.IntegerField()
    dlt_id = models.IntegerField()
    kont_id = models.IntegerField()
    r_sta = models.IntegerField()
    class Meta:
        db_table = u'mpv_resdl'

class MpvResdln(models.Model):
    bid = models.IntegerField()
    pers_id = models.IntegerField()
    name = models.CharField(max_length=1536)
    teil = models.IntegerField()
    dl_id = models.IntegerField()
    tdl_id = models.IntegerField()
    resazeit = models.DateTimeField(null=True, blank=True)
    resezeit = models.DateTimeField(null=True, blank=True)
    kat_id = models.IntegerField()
    typ_id = models.IntegerField()
    dlt_id = models.IntegerField()
    kont_id = models.IntegerField()
    r_sta = models.IntegerField()
    class Meta:
        db_table = u'mpv_resdln'

class MpvRkr(models.Model):
    rkr_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    textid = models.IntegerField(null=True, blank=True)
    dlncode = models.CharField(max_length=768, blank=True)
    vonalter = models.IntegerField(null=True, blank=True)
    bisalter = models.IntegerField(null=True, blank=True)
    class Meta:
        db_table = u'mpv_rkr'

class MpvRouten(models.Model):
    dlg_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    von = models.CharField(max_length=768, blank=True)
    nach = models.CharField(max_length=768, blank=True)
    class Meta:
        db_table = u'mpv_routen'

class MpvSaidet(models.Model):
    sai_id = models.IntegerField()
    saibez = models.CharField(max_length=3072)
    prg_id = models.IntegerField()
    prgbez = models.CharField(max_length=3072)
    arr_id = models.IntegerField()
    arrbez = models.CharField(max_length=3072)
    a_dat = models.DateTimeField(null=True, blank=True)
    teil = models.IntegerField()
    prio = models.IntegerField()
    dl_id = models.IntegerField()
    dlbez = models.CharField(max_length=3072)
    a_zeit = models.DateTimeField(null=True, blank=True)
    s_id = models.IntegerField()
    class Meta:
        db_table = u'mpv_saidet'

class MpvSaison(models.Model):
    sai_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    von = models.DateTimeField(null=True, blank=True)
    bis = models.DateTimeField(null=True, blank=True)
    textid = models.IntegerField(null=True, blank=True)
    class Meta:
        db_table = u'mpv_saison'

class MpvSprache(models.Model):
    s_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    bezsprid = models.IntegerField()
    dialog = models.IntegerField()
    sysbez = models.CharField(max_length=768)
    class Meta:
        db_table = u'mpv_sprache'

class MpvStatus(models.Model):
    sta_id = models.IntegerField()
    abk = models.CharField(max_length=768)
    sta = models.CharField(max_length=3072)
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    kond = models.FloatField()
    typ = models.IntegerField()
    class Meta:
        db_table = u'mpv_status'

class MpvTdl(models.Model):
    dl_id = models.IntegerField()
    h_dl_id = models.IntegerField()
    dla_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    ord = models.IntegerField(null=True, blank=True)
    a_zeit = models.DateTimeField(null=True, blank=True)
    e_zeit = models.DateTimeField(null=True, blank=True)
    res_f = models.IntegerField()
    kid = models.IntegerField(null=True, blank=True)
    konto = models.CharField(max_length=768, blank=True)
    textid = models.IntegerField(null=True, blank=True)
    sai_id = models.IntegerField()
    class Meta:
        db_table = u'mpv_tdl'

class MpvWhr(models.Model):
    whr_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    krzl = models.CharField(max_length=768, blank=True)
    status = models.IntegerField(null=True, blank=True)
    textid = models.IntegerField(null=True, blank=True)
    class Meta:
        db_table = u'mpv_whr'

#
# LEGACY views
#

class AktDetailView(models.Model):
    bid = models.IntegerField()
    pers_id = models.IntegerField()
    dlg_id = models.IntegerField()
    dl_id = models.IntegerField()
    teil = models.IntegerField()
    z_flag = models.IntegerField()
    akt_id = models.IntegerField()
    ord = models.IntegerField()
    a_flag = models.IntegerField(null=True, blank=True)
    m_flag = models.IntegerField(null=True, blank=True)
    a_typ_id = models.IntegerField()
    proz = models.CharField(max_length=3072)
    class Meta:
        db_table = u'akt_detail_view'

class StaView(models.Model):
    sta_id = models.IntegerField()
    abk = models.CharField(max_length=768)
    sta = models.CharField(max_length=3072)
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    kond = models.FloatField()
    typ = models.IntegerField()
    class Meta:
        db_table = u'sta_view'


class TmpBezeichnung(models.Model):
    bez_id = models.IntegerField(db_column='BEZ_ID') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    bez = models.CharField(max_length=3072, db_column='BEZ') # Field name made lowercase.
    typ = models.IntegerField(db_column='TYP') # Field name made lowercase.
    class Meta:
        db_table = u'tmp_bezeichnung'

class TmpTexte(models.Model):
    textid = models.IntegerField(db_column='TEXTID') # Field name made lowercase.
    s_id = models.IntegerField(db_column='S_ID') # Field name made lowercase.
    textnr = models.IntegerField(db_column='TEXTNR') # Field name made lowercase.
    text = models.CharField(max_length=3072, db_column='TEXT') # Field name made lowercase.
    typ = models.IntegerField(db_column='TYP') # Field name made lowercase.
    class Meta:
        db_table = u'tmp_texte'

class TraegerDetail(models.Model):
    dlt = models.ForeignKey(DienstTraeger, primary_key=True, db_column='DLT_ID') # Field name made lowercase.
    firma = models.ForeignKey(Personen, db_column='FIRMA') # Field name made lowercase.
    class Meta:
        db_table = u'traeger_detail'

class ArrDlgView(models.Model):
    arr_id = models.IntegerField()
    teil = models.IntegerField()
    prio = models.IntegerField()
    dlg_id = models.IntegerField()
    dl_id = models.IntegerField()
    ord = models.IntegerField()
    a_zeit = models.IntegerField(null=True, blank=True)
    res_f = models.IntegerField()
    bez = models.CharField(max_length=3072)
    bez1 = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    dtg_zeit = models.IntegerField(null=True, blank=True)
    class Meta:
        db_table = u'arr_dlg_view'

class ArrView(models.Model):
    arr_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    a_dat = models.IntegerField()
    prg_id = models.IntegerField()
    textid = models.IntegerField(null=True, blank=True)
    sai_id = models.IntegerField()
    class Meta:
        db_table = u'arr_view'

class KonView(models.Model):
    kont_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    hostkont_id = models.IntegerField()
    kunden_id = models.IntegerField()
    opt_dat = models.IntegerField(null=True, blank=True)
    ref = models.CharField(max_length=768, blank=True)
    sai_id = models.IntegerField()
    textid = models.IntegerField(null=True, blank=True)
    class Meta:
        db_table = u'kon_view'

class KoncheckView(models.Model):
    hostkont_id = models.IntegerField()
    kont_id = models.IntegerField()
    kat_id = models.IntegerField()
    dlt_id = models.IntegerField()
    anz = models.IntegerField(null=True, blank=True)
    busy = models.IntegerField(null=True, blank=True)
    class Meta:
        db_table = u'koncheck_view'

class DlgView(models.Model):
    dl_id = models.IntegerField()
    h_dl_id = models.IntegerField()
    dla_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    ord = models.IntegerField(null=True, blank=True)
    a_zeit = models.IntegerField(null=True, blank=True)
    e_zeit = models.IntegerField(null=True, blank=True)
    res_f = models.IntegerField()
    kid = models.IntegerField(null=True, blank=True)
    konto = models.CharField(max_length=768, blank=True)
    textid = models.IntegerField(null=True, blank=True)
    sai_id = models.IntegerField()
    class Meta:
        db_table = u'dlg_view'

class DlnView(models.Model):
    dln_id = models.IntegerField()
    name = models.CharField(max_length=1536)
    vor = models.CharField(max_length=1536)
    ort = models.CharField(max_length=768, blank=True)
    s_id = models.IntegerField()
    sta_id = models.IntegerField(null=True, blank=True)
    textid = models.IntegerField(null=True, blank=True)
    rkr_id = models.IntegerField()
    sex = models.IntegerField(null=True, blank=True)
    ext_txt = models.IntegerField(null=True, blank=True)
    land_id = models.IntegerField(null=True, blank=True)
    age = models.CharField(max_length=768, blank=True)
    passnr = models.CharField(max_length=768, blank=True)
    attr1 = models.CharField(max_length=3072, blank=True)
    attr2 = models.CharField(max_length=3072, blank=True)
    class Meta:
        db_table = u'dln_view'

class DltView(models.Model):
    dlt_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    kat_id = models.IntegerField(null=True, blank=True)
    h_dlt_id = models.IntegerField()
    host_id = models.IntegerField()
    typ_id = models.IntegerField()
    textid = models.IntegerField(null=True, blank=True)
    stufe = models.IntegerField()
    class Meta:
        db_table = u'dlt_view'

class DtgView(models.Model):
    dlg_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    textid = models.IntegerField(null=True, blank=True)
    sai_id = models.IntegerField()
    a_zeit = models.IntegerField(null=True, blank=True)
    akt_id = models.IntegerField(null=True, blank=True)
    class Meta:
        db_table = u'dtg_view'

class GraView(models.Model):
    gra_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    dlt_id = models.IntegerField()
    dltbez = models.CharField(max_length=3072)
    textid = models.IntegerField(null=True, blank=True)
    s_id = models.IntegerField()
    class Meta:
        db_table = u'gra_view'

class ArrDlView(models.Model):
    arr_id = models.IntegerField()
    a_dat = models.IntegerField()
    dlg_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    a_zeit = models.IntegerField(null=True, blank=True)
    teil = models.IntegerField()
    prio = models.IntegerField()
    akt_id = models.IntegerField(null=True, blank=True)
    s_id = models.IntegerField()
    class Meta:
        db_table = u'arr_dl_view'

class ResDlView(models.Model):
    bid = models.IntegerField()
    pers_id = models.IntegerField()
    name = models.CharField(max_length=1536)
    dl_id = models.IntegerField()
    dlazeit = models.IntegerField(null=True, blank=True)
    tdl_id = models.IntegerField()
    tdlazeit = models.IntegerField(null=True, blank=True)
    tdlezeit = models.IntegerField(null=True, blank=True)
    resazeit = models.IntegerField(null=True, blank=True)
    resezeit = models.IntegerField(null=True, blank=True)
    kat_id = models.IntegerField()
    katbez = models.CharField(max_length=3072)
    typ_id = models.IntegerField()
    dlt_id = models.IntegerField()
    dltbez = models.CharField(max_length=3072)
    kont_id = models.IntegerField()
    r_sta = models.IntegerField()
    s_id = models.IntegerField()
    class Meta:
        db_table = u'res_dl_view'

class ResdlView(models.Model):
    bid = models.IntegerField()
    pers_id = models.IntegerField()
    teil = models.IntegerField()
    dl_id = models.IntegerField()
    dl_bez = models.CharField(max_length=3072)
    dl_sid = models.IntegerField()
    tdl_id = models.IntegerField()
    resazeit = models.IntegerField(null=True, blank=True)
    resezeit = models.IntegerField(null=True, blank=True)
    kat_id = models.IntegerField()
    typ_id = models.IntegerField()
    dlt_id = models.IntegerField()
    kont_id = models.IntegerField()
    r_sta = models.IntegerField()
    class Meta:
        db_table = u'resdl_view'

class ResdlnView(models.Model):
    bid = models.IntegerField()
    pers_id = models.IntegerField()
    name = models.CharField(max_length=1536)
    teil = models.IntegerField()
    dl_id = models.IntegerField()
    tdl_id = models.IntegerField()
    resazeit = models.IntegerField(null=True, blank=True)
    resezeit = models.IntegerField(null=True, blank=True)
    kat_id = models.IntegerField()
    typ_id = models.IntegerField()
    dlt_id = models.IntegerField()
    kont_id = models.IntegerField()
    r_sta = models.IntegerField()
    class Meta:
        db_table = u'resdln_view'

class DlDlgView(models.Model):
    dlg_id = models.IntegerField()
    start_zeit = models.IntegerField(null=True, blank=True)
    dl_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    a_zeit = models.IntegerField(null=True, blank=True)
    e_zeit = models.IntegerField(null=True, blank=True)
    ord = models.IntegerField()
    res_f = models.IntegerField()
    s_id = models.IntegerField()
    class Meta:
        db_table = u'dl_dlg_view'

class DlaView(models.Model):
    dla_id = models.IntegerField()
    h_dla_id = models.IntegerField()
    ord = models.IntegerField()
    dlt_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    akt_id = models.IntegerField()
    ort = models.CharField(max_length=768)
    art_id = models.IntegerField()
    dau = models.IntegerField(null=True, blank=True)
    textid = models.IntegerField(null=True, blank=True)
    von = models.IntegerField()
    nach = models.IntegerField()
    class Meta:
        db_table = u'dla_view'

class RkrView(models.Model):
    rkr_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    textid = models.IntegerField(null=True, blank=True)
    dlncode = models.CharField(max_length=768, blank=True)
    vonalter = models.IntegerField(null=True, blank=True)
    bisalter = models.IntegerField(null=True, blank=True)
    class Meta:
        db_table = u'rkr_view'

class RoutenView(models.Model):
    dlg_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    von = models.CharField(max_length=768, blank=True)
    nach = models.CharField(max_length=768, blank=True)
    class Meta:
        db_table = u'routen_view'

class SaiView(models.Model):
    sai_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    von = models.IntegerField()
    bis = models.IntegerField()
    textid = models.IntegerField(null=True, blank=True)
    class Meta:
        db_table = u'sai_view'

class SprView(models.Model):
    s_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    bezsprid = models.IntegerField()
    dialog = models.IntegerField()
    sysbez = models.CharField(max_length=768)
    class Meta:
        db_table = u'spr_view'

class KarView(models.Model):
    kar_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    textid = models.IntegerField(null=True, blank=True)
    class Meta:
        db_table = u'kar_view'

class KatView(models.Model):
    kat_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    h_kat_id = models.IntegerField(null=True, blank=True)
    typ_id = models.IntegerField()
    ga = models.IntegerField(null=True, blank=True)
    textid = models.IntegerField(null=True, blank=True)
    class Meta:
        db_table = u'kat_view'

class KundenView(models.Model):
    kun_id = models.IntegerField()
    name = models.CharField(max_length=1536)
    ort = models.CharField(max_length=768, blank=True)
    s_id = models.IntegerField()
    sta_id = models.IntegerField(null=True, blank=True)
    textid = models.IntegerField(null=True, blank=True)
    kant = models.CharField(max_length=768, blank=True)
    tel = models.CharField(max_length=768, blank=True)
    fax = models.CharField(max_length=768, blank=True)
    tlx = models.CharField(max_length=768, blank=True)
    konto = models.CharField(max_length=768, blank=True)
    leiter = models.IntegerField(null=True, blank=True)
    attr1 = models.CharField(max_length=3072, blank=True)
    attr2 = models.CharField(max_length=3072, blank=True)
    k_typ_id = models.IntegerField()
    land_id = models.IntegerField(null=True, blank=True)
    whr_id = models.IntegerField()
    class Meta:
        db_table = u'kunden_view'


class LandView(models.Model):
    land_id = models.IntegerField()
    bez = models.CharField(max_length=3072)
    s_id = models.IntegerField()
    krzl = models.CharField(max_length=768, blank=True)
    haupt_ort = models.IntegerField(null=True, blank=True)
    haupt_spr = models.IntegerField(null=True, blank=True)
    haupt_whr = models.IntegerField(null=True, blank=True)
    textid = models.IntegerField(null=True, blank=True)
    vat = models.FloatField(null=True, blank=True)
    class Meta:
        db_table = u'land_view'
