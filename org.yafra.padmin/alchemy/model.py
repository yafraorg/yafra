# coding: utf-8
from sqlalchemy import BigInteger, Column, DateTime, Float, ForeignKey, Index, Integer, LargeBinary, String, Table
from sqlalchemy.orm import relationship
from sqlalchemy.ext.declarative import declarative_base


Base = declarative_base()
metadata = Base.metadata


t_akt_detail = Table(
    'akt_detail', metadata,
    Column('BID', ForeignKey('buchung.BID'), nullable=False, index=True),
    Column('PERS_ID', ForeignKey('personen.PERS_ID'), nullable=False, index=True),
    Column('DLG_ID', ForeignKey('dienstleistung.DLG_ID'), nullable=False, index=True),
    Column('DL_ID', ForeignKey('dlg_parts.DL_ID'), nullable=False, index=True),
    Column('TEIL', Integer, nullable=False),
    Column('AKT_ID', ForeignKey('aktionen.AKT_ID'), nullable=False, index=True),
    Column('ORD', Integer, nullable=False),
    Column('A_TYP_ID', ForeignKey('aktions_typ.A_TYP_ID'), nullable=False, index=True),
    Column('Z_FLAG', Integer, nullable=False),
    Column('AKT_NR', Integer, nullable=False),
    Column('SAI_ID', ForeignKey('saison.SAI_ID'), nullable=False, index=True),
    Column('PARENTAKT', ForeignKey('aktionen.AKT_ID'), nullable=False, index=True),
    Column('EXEC_DAT', BigInteger, nullable=False),
    Column('FILE_ID', ForeignKey('mp_file.FILE_ID'), index=True)
)


t_akt_detail_view = Table(
    'akt_detail_view', metadata,
    Column('bid', Integer),
    Column('pers_id', Integer),
    Column('dlg_id', Integer),
    Column('dl_id', Integer),
    Column('teil', Integer),
    Column('z_flag', Integer),
    Column('akt_id', Integer),
    Column('ord', Integer),
    Column('a_flag', Integer),
    Column('m_flag', Integer),
    Column('a_typ_id', Integer),
    Column('proz', String(1024))
)


t_akt_view = Table(
    'akt_view', metadata,
    Column('id', Integer),
    Column('bez', String(1024)),
    Column('ubez', String(1024)),
    Column('ord', Integer),
    Column('spr', Integer)
)


class Aktionen(Base):
    __tablename__ = 'aktionen'

    AKT_ID = Column(Integer, primary_key=True)
    BEZ_ID = Column(Integer, nullable=False)
    TEXTID = Column(Integer)
    A_FLAG = Column(Integer)
    B_FLAG = Column(Integer)
    M_FLAG = Column(Integer)
    A_TYP_ID = Column(ForeignKey('aktions_typ.A_TYP_ID'), nullable=False, index=True)
    B2_FLAG = Column(Integer)
    FILE_ID = Column(ForeignKey('mp_file.FILE_ID'), index=True)

    aktions_typ = relationship('AktionsTyp')
    mp_file = relationship('MpFile')


class AktionsTyp(Base):
    __tablename__ = 'aktions_typ'

    A_TYP_ID = Column(Integer, primary_key=True)
    BEZ_ID = Column(Integer, nullable=False)
    PROZ = Column(String(1024), nullable=False)
    TEXTID = Column(Integer)


class Aktionsgrp(Base):
    __tablename__ = 'aktionsgrp'

    PARENTAKT = Column(ForeignKey('aktionen.AKT_ID'), primary_key=True, nullable=False)
    CHILDAKT = Column(ForeignKey('aktionen.AKT_ID'), primary_key=True, nullable=False, index=True)
    ORD = Column(Integer, primary_key=True, nullable=False)
    H_AKT_ID = Column(ForeignKey('aktionen.AKT_ID'), nullable=False, index=True)

    aktionen = relationship('Aktionen', primaryjoin='Aktionsgrp.CHILDAKT == Aktionen.AKT_ID')
    aktionen1 = relationship('Aktionen', primaryjoin='Aktionsgrp.H_AKT_ID == Aktionen.AKT_ID')
    aktionen2 = relationship('Aktionen', primaryjoin='Aktionsgrp.PARENTAKT == Aktionen.AKT_ID')


class Aktionspara(Base):
    __tablename__ = 'aktionspara'

    A_TYP_ID = Column(ForeignKey('aktions_typ.A_TYP_ID'), primary_key=True, nullable=False)
    NR = Column(Integer, primary_key=True, nullable=False)
    TYP = Column(Integer)
    BEZ = Column(String(1024), nullable=False)
    MUSS = Column(Integer)
    FLAG = Column(Integer)
    TEXTID = Column(Integer)

    aktions_typ = relationship('AktionsTyp')


class Aktionstexte(Base):
    __tablename__ = 'aktionstexte'
    __table_args__ = (
        Index('atextid_index', 'TEXTID', 'TEXTNR', 'S_ID', 'TYP'),
        Index('atext_index', 'TEXTID', 'S_ID', 'TYP'),
        Index('atexttypspr_index', 'S_ID', 'TYP')
    )

    TEXTID = Column(Integer, primary_key=True, nullable=False)
    S_ID = Column(ForeignKey('sprachen.S_ID'), primary_key=True, nullable=False, index=True)
    TEXTNR = Column(Integer, primary_key=True, nullable=False)
    TEXT = Column(String(1024), nullable=False)
    TYP = Column(Integer, primary_key=True, nullable=False, index=True)

    sprachen = relationship('Sprachen')


class AngebotsTyp(Base):
    __tablename__ = 'angebots_typ'

    ART_ID = Column(Integer, primary_key=True)
    BEZ_ID = Column(Integer, nullable=False)
    TEXTID = Column(Integer)


t_arr_dl_view = Table(
    'arr_dl_view', metadata,
    Column('arr_id', Integer),
    Column('a_dat', BigInteger),
    Column('dlg_id', Integer),
    Column('bez', String(1024)),
    Column('a_zeit', BigInteger),
    Column('teil', Integer),
    Column('prio', Integer),
    Column('akt_id', Integer),
    Column('s_id', Integer)
)


class ArrDlg(Base):
    __tablename__ = 'arr_dlg'

    ARR_ID = Column(ForeignKey('arrangement.ARR_ID'), primary_key=True, nullable=False)
    TEIL = Column(Integer, primary_key=True, nullable=False)
    PRIO = Column(Integer, nullable=False)
    DLG_ID = Column(ForeignKey('dienstleistung.DLG_ID'), primary_key=True, nullable=False, index=True)

    arrangement = relationship('Arrangement')
    dienstleistung = relationship('Dienstleistung')


t_arr_dlg_view = Table(
    'arr_dlg_view', metadata,
    Column('arr_id', Integer),
    Column('teil', Integer),
    Column('prio', Integer),
    Column('dlg_id', Integer),
    Column('dl_id', Integer),
    Column('ord', Integer),
    Column('a_zeit', BigInteger),
    Column('res_f', Integer),
    Column('bez', String(1024)),
    Column('bez1', String(1024)),
    Column('s_id', Integer),
    Column('dtg_zeit', BigInteger)
)


t_arr_view = Table(
    'arr_view', metadata,
    Column('arr_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('a_dat', BigInteger),
    Column('prg_id', Integer),
    Column('textid', Integer),
    Column('sai_id', Integer)
)


class Arrangement(Base):
    __tablename__ = 'arrangement'

    ARR_ID = Column(Integer, primary_key=True)
    CODE = Column(String(256))
    BEZ_ID = Column(Integer, nullable=False)
    A_DAT = Column(BigInteger, nullable=False)
    PRG_ID = Column(ForeignKey('programm.PRG_ID'), nullable=False, index=True)
    TEXTID = Column(Integer)
    SAI_ID = Column(ForeignKey('saison.SAI_ID'), nullable=False, index=True)

    programm = relationship('Programm')
    saison = relationship('Saison')


t_bch_dln = Table(
    'bch_dln', metadata,
    Column('BID', ForeignKey('buchung.BID'), nullable=False, index=True),
    Column('DLN_ID', ForeignKey('personen.PERS_ID'), nullable=False, index=True)
)


class Bezeichnung(Base):
    __tablename__ = 'bezeichnung'
    __table_args__ = (
        Index('bezeich_index', 'BEZ_ID', 'S_ID', 'TYP'),
        Index('bezidtyp_index', 'BEZ_ID', 'TYP'),
        Index('btypspr_index', 'S_ID', 'TYP')
    )

    BEZ_ID = Column(Integer, primary_key=True, nullable=False, index=True)
    S_ID = Column(ForeignKey('sprachen.S_ID'), primary_key=True, nullable=False, index=True)
    BEZ = Column(String(1024), nullable=False)
    TYP = Column(Integer, primary_key=True, nullable=False, index=True)

    sprachen = relationship('Sprachen')


class Buchung(Base):
    __tablename__ = 'buchung'

    D_BID = Column(Integer, nullable=False)
    BID = Column(Integer, primary_key=True)
    REF = Column(String(256), nullable=False)
    ARR_ID = Column(ForeignKey('arrangement.ARR_ID'), nullable=False, index=True)
    KID = Column(ForeignKey('personen.PERS_ID'), nullable=False, index=True)
    SACH = Column(Integer, nullable=False)
    ANW = Column(Integer, nullable=False)
    B_DAT = Column(BigInteger)
    M_DAT = Column(BigInteger)
    OPT_BST = Column(Integer)
    OPT_KID = Column(Integer)
    STA = Column(Integer, nullable=False)
    AST = Column(Integer, nullable=False)
    SAI_ID = Column(ForeignKey('saison.SAI_ID'), nullable=False, index=True)
    K_ID = Column(ForeignKey('kollektiv.K_ID'), nullable=False, index=True)
    MPID = Column(ForeignKey('mp_profil.MPID'), index=True)
    HISTORY = Column(Integer)
    TEXTID = Column(Integer)

    arrangement = relationship('Arrangement')
    personen = relationship('Personen')
    kollektiv = relationship('Kollektiv')
    mp_profil = relationship('MpProfil')
    saison = relationship('Saison')
    personen1 = relationship('Personen', secondary='bch_dln')


class DienstAngebot(Base):
    __tablename__ = 'dienst_angebot'

    DLA_ID = Column(Integer, primary_key=True)
    CODE = Column(String(256))
    H_DLA_ID = Column(Integer, nullable=False)
    ORD = Column(Integer, nullable=False)
    DLT_ID = Column(ForeignKey('dienst_traeger.DLT_ID'), nullable=False, index=True)
    BEZ_ID = Column(Integer, nullable=False)
    AKT_ID = Column(ForeignKey('aktionen.AKT_ID'), nullable=False, index=True)
    ORT = Column(String(256), nullable=False)
    ART_ID = Column(ForeignKey('angebots_typ.ART_ID'), nullable=False, index=True)
    DAU = Column(Integer)
    TEXTID = Column(Integer)
    VON = Column(ForeignKey('ort.ORT_ID'), nullable=False, index=True)
    NACH = Column(ForeignKey('ort.ORT_ID'), nullable=False, index=True)

    aktionen = relationship('Aktionen')
    angebots_typ = relationship('AngebotsTyp')
    dienst_traeger = relationship('DienstTraeger')
    ort = relationship('Ort', primaryjoin='DienstAngebot.NACH == Ort.ORT_ID')
    ort1 = relationship('Ort', primaryjoin='DienstAngebot.VON == Ort.ORT_ID')


class DienstTraeger(Base):
    __tablename__ = 'dienst_traeger'

    DLT_ID = Column(Integer, primary_key=True)
    CODE = Column(String(256))
    BEZ_ID = Column(Integer, nullable=False)
    KAT_ID = Column(ForeignKey('kategorie.KAT_ID'), index=True)
    H_DLT_ID = Column(Integer, nullable=False)
    DLT_GRP_ID = Column(Integer, nullable=False)
    HOST_ID = Column(Integer, nullable=False)
    TYP_ID = Column(ForeignKey('traeger_typ.TYP_ID'), nullable=False, index=True)
    TEXTID = Column(Integer)
    STUFE = Column(Integer, nullable=False)
    STA_ID = Column(Integer)
    ANZ = Column(Integer)

    kategorie = relationship('Kategorie')
    traeger_typ = relationship('TraegerTyp')
    personen = relationship('Personen', secondary='traeger_detail')


class Dienstleistung(Base):
    __tablename__ = 'dienstleistung'

    DLG_ID = Column(Integer, primary_key=True)
    CODE = Column(String(256))
    BEZ_ID = Column(Integer, nullable=False)
    TEXTID = Column(Integer)
    SAI_ID = Column(ForeignKey('saison.SAI_ID'), nullable=False, index=True)
    A_ZEIT = Column(BigInteger)
    AKT_ID = Column(ForeignKey('aktionen.AKT_ID'), index=True)

    aktionen = relationship('Aktionen')
    saison = relationship('Saison')


t_dl_dlg_view = Table(
    'dl_dlg_view', metadata,
    Column('dlg_id', Integer),
    Column('start_zeit', BigInteger),
    Column('dl_id', Integer),
    Column('bez', String(1024)),
    Column('a_zeit', BigInteger),
    Column('e_zeit', BigInteger),
    Column('ord', Integer),
    Column('res_f', Integer),
    Column('s_id', Integer)
)


t_dla_view = Table(
    'dla_view', metadata,
    Column('dla_id', Integer),
    Column('h_dla_id', Integer),
    Column('ord', Integer),
    Column('dlt_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('akt_id', Integer),
    Column('ort', String(256)),
    Column('art_id', Integer),
    Column('dau', Integer),
    Column('textid', Integer),
    Column('von', Integer),
    Column('nach', Integer)
)


class DlgDlg(Base):
    __tablename__ = 'dlg_dlg'

    DLG_ID = Column(ForeignKey('dienstleistung.DLG_ID'), primary_key=True, nullable=False)
    DL_ID = Column(ForeignKey('dlg_parts.DL_ID'), primary_key=True, nullable=False, index=True)
    ORD = Column(Integer, nullable=False)

    dienstleistung = relationship('Dienstleistung')
    dlg_part = relationship('DlgPart')


class DlgPart(Base):
    __tablename__ = 'dlg_parts'

    DL_ID = Column(Integer, primary_key=True)
    CODE = Column(String(256))
    BEZ_ID = Column(Integer, nullable=False)
    H_DL_ID = Column(Integer, nullable=False)
    DLA_ID = Column(ForeignKey('dienst_angebot.DLA_ID'), nullable=False, index=True)
    ORD = Column(Integer)
    A_ZEIT = Column(BigInteger)
    E_ZEIT = Column(BigInteger)
    RES_F = Column(Integer, nullable=False)
    KID = Column(ForeignKey('personen.PERS_ID'), index=True)
    KONTO = Column(String(256))
    TEXTID = Column(Integer)
    SAI_ID = Column(ForeignKey('saison.SAI_ID'), nullable=False, index=True)
    RECHST = Column(ForeignKey('personen.PERS_ID'), index=True)

    dienst_angebot = relationship('DienstAngebot')
    personen = relationship('Personen', primaryjoin='DlgPart.KID == Personen.PERS_ID')
    personen1 = relationship('Personen', primaryjoin='DlgPart.RECHST == Personen.PERS_ID')
    saison = relationship('Saison')


t_dlg_view = Table(
    'dlg_view', metadata,
    Column('dl_id', Integer),
    Column('h_dl_id', Integer),
    Column('dla_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('ord', Integer),
    Column('a_zeit', BigInteger),
    Column('e_zeit', BigInteger),
    Column('res_f', Integer),
    Column('kid', Integer),
    Column('konto', String(256)),
    Column('textid', Integer),
    Column('sai_id', Integer)
)


t_dln_view = Table(
    'dln_view', metadata,
    Column('dln_id', Integer),
    Column('name', String(512)),
    Column('vor', String(512)),
    Column('ort', String(256)),
    Column('s_id', Integer),
    Column('sta_id', Integer),
    Column('textid', Integer),
    Column('rkr_id', Integer),
    Column('sex', Integer),
    Column('ext_txt', Integer),
    Column('land_id', Integer),
    Column('age', String(256)),
    Column('passnr', String(256)),
    Column('attr1', String(1024)),
    Column('attr2', String(1024))
)


t_dlt_view = Table(
    'dlt_view', metadata,
    Column('dlt_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('kat_id', Integer),
    Column('h_dlt_id', Integer),
    Column('host_id', Integer),
    Column('typ_id', Integer),
    Column('textid', Integer),
    Column('stufe', Integer)
)


t_dtg_view = Table(
    'dtg_view', metadata,
    Column('dlg_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('textid', Integer),
    Column('sai_id', Integer),
    Column('a_zeit', BigInteger),
    Column('akt_id', Integer)
)


t_gra_view = Table(
    'gra_view', metadata,
    Column('gra_id', Integer),
    Column('bez', String(1024)),
    Column('dlt_id', Integer),
    Column('dltbez', String(1024)),
    Column('textid', Integer),
    Column('s_id', Integer)
)


class Graform(Base):
    __tablename__ = 'graform'

    GRA_ID = Column(ForeignKey('graphik.GRA_ID'), primary_key=True, nullable=False)
    FORMNR = Column(Integer, primary_key=True, nullable=False)
    FORM = Column(String(256), nullable=False)

    graphik = relationship('Graphik')


class Graphik(Base):
    __tablename__ = 'graphik'

    GRA_ID = Column(Integer, primary_key=True)
    BEZ_ID = Column(Integer, nullable=False)
    DLT_ID = Column(ForeignKey('dienst_traeger.DLT_ID'), nullable=False, index=True)
    TEXTID = Column(Integer)

    dienst_traeger = relationship('DienstTraeger')


class Help(Base):
    __tablename__ = 'help'
    __table_args__ = (
        Index('hlp_index', 'HELP_TYP', 'HELP_ID', 'S_ID', 'TEXTNR'),
    )

    HELP_TYP = Column(Integer, primary_key=True, nullable=False, index=True)
    HELP_ID = Column(Integer, primary_key=True, nullable=False)
    S_ID = Column(ForeignKey('sprachen.S_ID'), primary_key=True, nullable=False, index=True)
    TEXTNR = Column(Integer, primary_key=True, nullable=False)
    TEXT = Column(String(1024), nullable=False)

    sprachen = relationship('Sprachen')


class History(Base):
    __tablename__ = 'history'
    __table_args__ = (
        Index('his_index', 'HIS_ID', 'S_ID', 'TEXTNR'),
    )

    HIS_ID = Column(Integer, primary_key=True, nullable=False, index=True)
    S_ID = Column(ForeignKey('sprachen.S_ID'), primary_key=True, nullable=False, index=True)
    TEXTNR = Column(Integer, primary_key=True, nullable=False)
    TEXT = Column(String(1024), nullable=False)
    DAT = Column(BigInteger, nullable=False)
    TYP = Column(Integer, nullable=False)

    sprachen = relationship('Sprachen')


class HostKont(Base):
    __tablename__ = 'host_kont'

    HOSTKONT_ID = Column(Integer, primary_key=True)
    BEZ_ID = Column(Integer, nullable=False)
    FROM_PERS = Column(ForeignKey('personen.PERS_ID'), nullable=False, index=True)
    KBST = Column(ForeignKey('personen.PERS_ID'), nullable=False, index=True)
    DLA_ID = Column(ForeignKey('dienst_angebot.DLA_ID'), index=True)
    DL_ID = Column(ForeignKey('dienstleistung.DLG_ID'), index=True)
    DL_VONDAT = Column(BigInteger)
    DL_BISDAT = Column(BigInteger)
    TEXTID = Column(Integer)
    OPT_DAT = Column(BigInteger)
    SAI_ID = Column(ForeignKey('saison.SAI_ID'), nullable=False, index=True)
    REF = Column(String(256))
    HISTORY = Column(Integer)

    dienst_angebot = relationship('DienstAngebot')
    dienstleistung = relationship('Dienstleistung')
    personen = relationship('Personen', primaryjoin='HostKont.FROM_PERS == Personen.PERS_ID')
    personen1 = relationship('Personen', primaryjoin='HostKont.KBST == Personen.PERS_ID')
    saison = relationship('Saison')


class Kapa(Base):
    __tablename__ = 'kapa'

    KAT_ID = Column(ForeignKey('kategorie.KAT_ID'), primary_key=True, nullable=False)
    KATBEZ_ID = Column(Integer, nullable=False)
    TDL_ID = Column(ForeignKey('dlg_parts.DL_ID'), primary_key=True, nullable=False, index=True)
    TDLBEZ_ID = Column(Integer, nullable=False)
    PRE_ID = Column(Integer, nullable=False)
    ANZ = Column(Integer)
    BUSY = Column(Integer)
    VPR = Column(Float)
    VON_DAT = Column(BigInteger, primary_key=True, nullable=False)
    BIS_DAT = Column(BigInteger, primary_key=True, nullable=False)

    kategorie = relationship('Kategorie')
    dlg_part = relationship('DlgPart')


t_kar_view = Table(
    'kar_view', metadata,
    Column('kar_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('textid', Integer)
)


t_kat_view = Table(
    'kat_view', metadata,
    Column('kat_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('h_kat_id', Integer),
    Column('typ_id', Integer),
    Column('ga', Integer),
    Column('textid', Integer)
)


class Kategorie(Base):
    __tablename__ = 'kategorie'

    KAT_ID = Column(Integer, primary_key=True)
    BEZ_ID = Column(Integer, nullable=False)
    H_KAT_ID = Column(Integer)
    TYP_ID = Column(ForeignKey('traeger_typ.TYP_ID'), nullable=False, index=True)
    GA = Column(Integer)
    TEXTID = Column(Integer)

    traeger_typ = relationship('TraegerTyp')


class Kollektiv(Base):
    __tablename__ = 'kollektiv'

    K_ID = Column(Integer, primary_key=True)
    REF = Column(String(256))
    NAME = Column(String(512))
    K_TYP_ID = Column(ForeignKey('kollektiv_typ.K_TYP_ID'), nullable=False, index=True)
    KBST = Column(ForeignKey('personen.PERS_ID'), nullable=False, index=True)
    K_STA = Column(Integer)
    HAUPTPERS = Column(ForeignKey('personen.PERS_ID'), index=True)
    KID = Column(ForeignKey('personen.PERS_ID'), index=True)
    TEXTID = Column(Integer)

    personen = relationship('Personen', primaryjoin='Kollektiv.HAUPTPERS == Personen.PERS_ID')
    personen1 = relationship('Personen', primaryjoin='Kollektiv.KBST == Personen.PERS_ID')
    personen2 = relationship('Personen', primaryjoin='Kollektiv.KID == Personen.PERS_ID')
    kollektiv_typ = relationship('KollektivTyp')


class KollektivTyp(Base):
    __tablename__ = 'kollektiv_typ'

    K_TYP_ID = Column(Integer, primary_key=True)
    KOLCODE = Column(String(256))
    BEZ_ID = Column(Integer, nullable=False)
    TEXTID = Column(Integer)


t_komm_detail = Table(
    'komm_detail', metadata,
    Column('KOMM_ID', ForeignKey('kommission.KOMM_ID'), nullable=False, index=True),
    Column('BID', ForeignKey('buchung.BID'), nullable=False, index=True),
    Column('DLN_ID', ForeignKey('personen.PERS_ID'), nullable=False, index=True),
    Column('KUN_ID', ForeignKey('personen.PERS_ID'), nullable=False, index=True),
    Column('KOL_ID', ForeignKey('kollektiv.K_ID'), nullable=False, index=True),
    Column('PRIO', Integer)
)


class Kommission(Base):
    __tablename__ = 'kommission'

    KOMM_ID = Column(Integer, primary_key=True)
    BEZ_ID = Column(Integer, nullable=False)
    SATZ_ART = Column(Integer, nullable=False)
    SATZ = Column(Float, nullable=False)
    KOMM_TYP = Column(Integer, nullable=False)
    KBST = Column(ForeignKey('personen.PERS_ID'), nullable=False, index=True)
    KAR_ID = Column(ForeignKey('kosten_art.KAR_ID'), index=True)
    DLTT_ID = Column(ForeignKey('traeger_typ.TYP_ID'), index=True)
    KAT_ID = Column(ForeignKey('kategorie.KAT_ID'), index=True)
    RKR_ID = Column(ForeignKey('reisender_typ.RKR_ID'), index=True)
    DLA_ID = Column(ForeignKey('dienst_angebot.DLA_ID'), index=True)
    DL_ID = Column(ForeignKey('dienstleistung.DLG_ID'), index=True)
    DL_VONDAT = Column(BigInteger)
    DL_BISDAT = Column(BigInteger)
    KONT_ID = Column(ForeignKey('kontingent.KONT_ID'), index=True)
    BID = Column(ForeignKey('buchung.BID'), index=True)
    HISTORY = Column(Integer)
    SAI_ID = Column(ForeignKey('saison.SAI_ID'), nullable=False, index=True)
    TEXTID = Column(Integer)

    buchung = relationship('Buchung')
    dienst_angebot = relationship('DienstAngebot')
    traeger_typ = relationship('TraegerTyp')
    dienstleistung = relationship('Dienstleistung')
    kosten_art = relationship('KostenArt')
    kategorie = relationship('Kategorie')
    personen = relationship('Personen')
    kontingent = relationship('Kontingent')
    reisender_typ = relationship('ReisenderTyp')
    saison = relationship('Saison')


t_kon_view = Table(
    'kon_view', metadata,
    Column('kont_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('hostkont_id', Integer),
    Column('kunden_id', Integer),
    Column('opt_dat', BigInteger),
    Column('ref', String(256)),
    Column('sai_id', Integer),
    Column('textid', Integer)
)


t_koncheck_view = Table(
    'koncheck_view', metadata,
    Column('hostkont_id', Integer),
    Column('kont_id', Integer),
    Column('kat_id', Integer),
    Column('dlt_id', Integer),
    Column('anz', Integer),
    Column('busy', Integer)
)


class KontDetail(Base):
    __tablename__ = 'kont_detail'

    HOSTKONT_ID = Column(ForeignKey('host_kont.HOSTKONT_ID'), primary_key=True, nullable=False)
    KONT_ID = Column(ForeignKey('kontingent.KONT_ID'), primary_key=True, nullable=False, index=True)
    KAT_ID = Column(ForeignKey('kategorie.KAT_ID'), primary_key=True, nullable=False, index=True)
    DLT_ID = Column(ForeignKey('dienst_traeger.DLT_ID'), primary_key=True, nullable=False, index=True)
    STA_ID = Column(Integer)
    ANZ = Column(Integer)
    BUSY = Column(Integer)
    MINANZ = Column(Integer)
    VON_DAT = Column(BigInteger, primary_key=True, nullable=False)
    BIS_DAT = Column(BigInteger, primary_key=True, nullable=False)

    dienst_traeger = relationship('DienstTraeger')
    host_kont = relationship('HostKont')
    kategorie = relationship('Kategorie')
    kontingent = relationship('Kontingent')


class Kontingent(Base):
    __tablename__ = 'kontingent'

    KONT_ID = Column(Integer, primary_key=True)
    BEZ_ID = Column(Integer, nullable=False)
    HOSTKONT_ID = Column(ForeignKey('host_kont.HOSTKONT_ID'), nullable=False, index=True)
    KUNDEN_ID = Column(ForeignKey('personen.PERS_ID'), nullable=False, index=True)
    OPT_DAT = Column(BigInteger)
    REF = Column(String(256))
    SAI_ID = Column(ForeignKey('saison.SAI_ID'), nullable=False, index=True)
    TEXTID = Column(Integer)

    host_kont = relationship('HostKont')
    personen = relationship('Personen')
    saison = relationship('Saison')


class KostenArt(Base):
    __tablename__ = 'kosten_art'

    KAR_ID = Column(Integer, primary_key=True)
    BEZ_ID = Column(Integer, nullable=False)
    TEXTID = Column(Integer)


t_kunden = Table(
    'kunden', metadata,
    Column('PERS_ID', ForeignKey('personen.PERS_ID'), nullable=False, index=True),
    Column('TEL', String(256)),
    Column('HANDY', String(256)),
    Column('FAX', String(256)),
    Column('TLX', String(256)),
    Column('EMAIL', String(1024)),
    Column('WEB', String(1024)),
    Column('KONTO', String(256)),
    Column('LEITER', Integer),
    Column('ATTR1', String(1024)),
    Column('ATTR2', String(1024)),
    Column('K_TYP_ID', ForeignKey('kunden_typ.K_TYP_ID'), nullable=False, index=True),
    Column('WHR_ID', ForeignKey('waehrung.WHR_ID'), nullable=False, index=True)
)


class KundenTyp(Base):
    __tablename__ = 'kunden_typ'

    K_TYP_ID = Column(Integer, primary_key=True)
    KUNCODE = Column(String(256))
    BEZ_ID = Column(Integer, nullable=False)
    TEXTID = Column(Integer)


t_kunden_view = Table(
    'kunden_view', metadata,
    Column('kun_id', Integer),
    Column('name', String(512)),
    Column('ort', String(256)),
    Column('s_id', Integer),
    Column('sta_id', Integer),
    Column('textid', Integer),
    Column('kant', String(256)),
    Column('tel', String(256)),
    Column('fax', String(256)),
    Column('tlx', String(256)),
    Column('konto', String(256)),
    Column('leiter', Integer),
    Column('attr1', String(1024)),
    Column('attr2', String(1024)),
    Column('k_typ_id', Integer),
    Column('land_id', Integer),
    Column('whr_id', Integer)
)


class Label(Base):
    __tablename__ = 'label'
    __table_args__ = (
        Index('label_index', 'LABEL_PRG', 'LABEL_TYP', 'STUFE1', 'STUFE2', 'S_ID'),
    )

    LABEL_PRG = Column(Integer, primary_key=True, nullable=False)
    LABEL_TYP = Column(Integer, primary_key=True, nullable=False)
    STUFE1 = Column(Integer, primary_key=True, nullable=False)
    STUFE2 = Column(Integer, primary_key=True, nullable=False)
    S_ID = Column(ForeignKey('sprachen.S_ID'), primary_key=True, nullable=False, index=True)
    LABEL = Column(String(1024), nullable=False)

    sprachen = relationship('Sprachen')


class Land(Base):
    __tablename__ = 'land'

    LAND_ID = Column(Integer, primary_key=True, unique=True)
    BEZ_ID = Column(Integer, nullable=False, unique=True)
    TEXTID = Column(Integer)
    KRZL = Column(String(256))
    HAUPT_ORT = Column(Integer)
    HAUPT_WHR = Column(ForeignKey('waehrung.WHR_ID'), index=True)
    HAUPT_SPR = Column(ForeignKey('sprachen.S_ID'), index=True)
    VAT = Column(Float)
    DATEFORMAT = Column(String(256))

    sprachen = relationship('Sprachen')
    waehrung = relationship('Waehrung')
    sprachen1 = relationship('Sprachen', secondary='land_spr')


t_land_spr = Table(
    'land_spr', metadata,
    Column('LAND_ID', ForeignKey('land.LAND_ID'), primary_key=True, nullable=False),
    Column('S_ID', ForeignKey('sprachen.S_ID'), primary_key=True, nullable=False, index=True),
    Index('land_spr_index', 'LAND_ID', 'S_ID')
)


t_land_view = Table(
    'land_view', metadata,
    Column('land_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('krzl', String(256)),
    Column('haupt_ort', Integer),
    Column('haupt_spr', Integer),
    Column('haupt_whr', Integer),
    Column('textid', Integer),
    Column('vat', Float)
)


class LandWhr(Base):
    __tablename__ = 'land_whr'
    __table_args__ = (
        Index('lw_index', 'LAND_ID', 'WHR_ID', 'KURS_TYP'),
    )

    LAND_ID = Column(ForeignKey('land.LAND_ID'), primary_key=True, nullable=False, index=True)
    WHR_ID = Column(ForeignKey('waehrung.WHR_ID'), primary_key=True, nullable=False, index=True)
    KURS_TYP = Column(Integer, primary_key=True, nullable=False)
    A_KURS = Column(Float, nullable=False)
    V_KURS = Column(Float, nullable=False)
    VON_DAT = Column(BigInteger)

    land = relationship('Land')
    waehrung = relationship('Waehrung')


class Maxima(Base):
    __tablename__ = 'maxima'

    TABELLE = Column(Integer, primary_key=True, nullable=False)
    TYP = Column(Integer, primary_key=True, nullable=False)
    MAX_ID = Column(Integer)
    MIN_ID = Column(Integer)
    INCR = Column(Integer)


t_mp2000_kunden = Table(
    'mp2000_kunden', metadata,
    Column('pers_id', Integer),
    Column('name', String(512)),
    Column('adr1', String(1024)),
    Column('plz', String(256)),
    Column('ort', String(256)),
    Column('land', String(1024)),
    Column('sprache', String(1024)),
    Column('code', String(1024)),
    Column('waehrung', String(1024)),
    Column('versand', String(1024)),
    Column('text', String(1024)),
    Column('textid', Integer),
    Column('s_id', Integer),
    Column('tel', String(256)),
    Column('fax', String(256)),
    Column('email', String(1024)),
    Column('web', String(1024)),
    Column('konto', String(256)),
    Column('typ', String(1024))
)


t_mp2000_saison = Table(
    'mp2000_saison', metadata,
    Column('sai_id', Integer),
    Column('bez_id', Integer),
    Column('bez', String(1024)),
    Column('code', String(256)),
    Column('von', BigInteger),
    Column('bis', BigInteger),
    Column('text', String(1024)),
    Column('s_id', Integer)
)


t_mp_arrkom = Table(
    'mp_arrkom', metadata,
    Column('ARR_ID', ForeignKey('arrangement.ARR_ID'), nullable=False, index=True),
    Column('KOMM_ID', ForeignKey('kommission.KOMM_ID'), nullable=False, index=True),
    Column('KOMM_BEZID', Integer, nullable=False)
)


class MpBchDlg(Base):
    __tablename__ = 'mp_bch_dlg'

    BID = Column(ForeignKey('buchung.BID'), primary_key=True, nullable=False)
    DLG_ID = Column(ForeignKey('dienstleistung.DLG_ID'), nullable=False, index=True)
    TEIL = Column(Integer, primary_key=True, nullable=False)

    buchung = relationship('Buchung')
    dienstleistung = relationship('Dienstleistung')


class MpDebitor(Base):
    __tablename__ = 'mp_debitor'

    DEB_ID = Column(Integer, primary_key=True, nullable=False)
    BID = Column(ForeignKey('buchung.BID'), nullable=False, index=True)
    STA_ID = Column(Integer)
    KID = Column(ForeignKey('personen.PERS_ID'), ForeignKey('personen.PERS_ID'), index=True)
    KONTO = Column(String(256))
    NACHSALDO = Column(Float)
    K_ID = Column(ForeignKey('kollektiv.K_ID'), index=True)
    FAKT_ID = Column(ForeignKey('mp_multimedia.MULT_ID'), index=True)
    FAKT_ZEIT = Column(DateTime)
    FAKT_NR = Column(String(256))
    FAKT_TEXT = Column(String(1024))
    DLN_DETAIL = Column(String(1024))
    DLG_DETAIL = Column(String(1024))
    WHR_ID = Column(ForeignKey('waehrung.WHR_ID'), index=True)
    WHR_LAND_ID = Column(ForeignKey('land.LAND_ID'), index=True)
    WHR_KURS = Column(Float)
    WHR_TEXT = Column(String(1024))
    WHR_EXCL = Column(Float)
    WHR_INKL = Column(Float)
    VAT_ID = Column(ForeignKey('kommission.KOMM_ID'), primary_key=True, nullable=False, index=True)
    VAT_LAND_ID = Column(ForeignKey('land.LAND_ID'), index=True)
    VAT = Column(Float)
    VAT_TEXT = Column(String(1024))
    RST_EXCL = Column(Float)
    RST_INKL = Column(Float)
    RST_GEWINN = Column(Float)
    OPT_TEXT = Column(String(1024))

    buchung = relationship('Buchung')
    mp_multimedia = relationship('MpMultimedia')
    personen = relationship('Personen', primaryjoin='MpDebitor.KID == Personen.PERS_ID')
    personen1 = relationship('Personen', primaryjoin='MpDebitor.KID == Personen.PERS_ID')
    kollektiv = relationship('Kollektiv')
    kommission = relationship('Kommission')
    land = relationship('Land', primaryjoin='MpDebitor.VAT_LAND_ID == Land.LAND_ID')
    waehrung = relationship('Waehrung')
    land1 = relationship('Land', primaryjoin='MpDebitor.WHR_LAND_ID == Land.LAND_ID')


class MpFile(Base):
    __tablename__ = 'mp_file'

    FILE_ID = Column(Integer, primary_key=True)
    CODE = Column(String(256))
    FILE_TYP = Column(Integer)
    LABEL_ID = Column(Integer)
    FILENAME = Column(String(1024))


class MpGemeinRe(Base):
    __tablename__ = 'mp_gemein_res'

    PERS_ID = Column(ForeignKey('personen.PERS_ID'), primary_key=True, nullable=False)
    DL_ID = Column(ForeignKey('dlg_parts.DL_ID'), primary_key=True, nullable=False, index=True)
    TEIL = Column(Integer, primary_key=True, nullable=False)
    BID = Column(ForeignKey('buchung.BID'), primary_key=True, nullable=False, index=True)
    GPERS_ID = Column(Integer, primary_key=True, nullable=False)

    buchung = relationship('Buchung')
    dlg_part = relationship('DlgPart')
    personen = relationship('Personen')


class MpKapa(Base):
    __tablename__ = 'mp_kapa'

    KAT_ID = Column(ForeignKey('kategorie.KAT_ID'), primary_key=True, nullable=False)
    KATBEZ_ID = Column(Integer)
    DLT_ID = Column(ForeignKey('dienst_traeger.DLT_ID'), primary_key=True, nullable=False, index=True)
    DLTBEZ_ID = Column(Integer)
    DL_ID = Column(ForeignKey('dlg_parts.DL_ID'), primary_key=True, nullable=False, index=True)
    DLBEZ_ID = Column(Integer)
    ANZ = Column(Integer)
    BUSY = Column(Integer)
    VON_DAT = Column(BigInteger, primary_key=True, nullable=False)
    BIS_DAT = Column(BigInteger, primary_key=True, nullable=False)

    dienst_traeger = relationship('DienstTraeger')
    dlg_part = relationship('DlgPart')
    kategorie = relationship('Kategorie')


class MpKolPer(Base):
    __tablename__ = 'mp_kol_pers'

    PERS_ID = Column(ForeignKey('personen.PERS_ID'), primary_key=True, nullable=False)
    ADR_TYP = Column(Integer, primary_key=True, nullable=False)
    MPID = Column(ForeignKey('mp_profil.MPID'), primary_key=True, nullable=False, index=True)
    K_ID = Column(ForeignKey('kollektiv.K_ID'), primary_key=True, nullable=False, index=True)

    kollektiv = relationship('Kollektiv')
    mp_profil = relationship('MpProfil')
    personen = relationship('Personen')


class MpKreditor(Base):
    __tablename__ = 'mp_kreditor'

    KRE_ID = Column(Integer, primary_key=True, nullable=False)
    BID = Column(ForeignKey('buchung.BID'), nullable=False, index=True)
    STA_ID = Column(Integer)
    KID = Column(ForeignKey('personen.PERS_ID'), ForeignKey('personen.PERS_ID'), primary_key=True, nullable=False, index=True)
    KONTO = Column(String(256))
    NACHSALDO = Column(Float)
    K_ID = Column(ForeignKey('kollektiv.K_ID'), index=True)
    FAKT_ID = Column(ForeignKey('mp_multimedia.MULT_ID'), index=True)
    FAKT_ZEIT = Column(DateTime)
    FAKT_NR = Column(String(256))
    FAKT_TEXT = Column(String(1024))
    DLN_DETAIL = Column(String(1024))
    DLG_DETAIL = Column(String(1024))
    WHR_ID = Column(ForeignKey('waehrung.WHR_ID'), index=True)
    WHR_LAND_ID = Column(ForeignKey('land.LAND_ID'), index=True)
    WHR_KURS = Column(Float)
    WHR_TEXT = Column(String(1024))
    WHR_EXCL = Column(Float)
    WHR_INKL = Column(Float)
    VAT_ID = Column(ForeignKey('kommission.KOMM_ID'), primary_key=True, nullable=False, index=True)
    VAT_LAND_ID = Column(ForeignKey('land.LAND_ID'), index=True)
    VAT = Column(Float)
    VAT_TEXT = Column(String(1024))
    RST_EXCL = Column(Float)
    RST_INKL = Column(Float)
    RST_GEWINN = Column(Float)
    OPT_TEXT = Column(String(1024))

    buchung = relationship('Buchung')
    mp_multimedia = relationship('MpMultimedia')
    personen = relationship('Personen', primaryjoin='MpKreditor.KID == Personen.PERS_ID')
    personen1 = relationship('Personen', primaryjoin='MpKreditor.KID == Personen.PERS_ID')
    kollektiv = relationship('Kollektiv')
    kommission = relationship('Kommission')
    land = relationship('Land', primaryjoin='MpKreditor.VAT_LAND_ID == Land.LAND_ID')
    waehrung = relationship('Waehrung')
    land1 = relationship('Land', primaryjoin='MpKreditor.WHR_LAND_ID == Land.LAND_ID')


class MpLabel(Base):
    __tablename__ = 'mp_label'

    LABEL_ID = Column(Integer, primary_key=True, nullable=False)
    SEC_ID = Column(Integer, primary_key=True, nullable=False)
    LABEL_TYP = Column(Integer, primary_key=True, nullable=False)
    S_ID = Column(ForeignKey('sprachen.S_ID'), primary_key=True, nullable=False, index=True)
    LABEL = Column(String(1024), nullable=False)

    sprachen = relationship('Sprachen')


class MpMultimedia(Base):
    __tablename__ = 'mp_multimedia'

    MULT_ID = Column(Integer, primary_key=True)
    MULT_TYP = Column(Integer)
    S_ID = Column(ForeignKey('sprachen.S_ID'), index=True)
    MULT = Column(LargeBinary)

    sprachen = relationship('Sprachen')


class MpParam(Base):
    __tablename__ = 'mp_param'

    PARAM_ID = Column(Integer, primary_key=True)
    CODE = Column(String(256))
    FILE_ID = Column(ForeignKey('mp_file.FILE_ID'), index=True)
    PARAM_TYP = Column(Integer)
    LABEL_ID = Column(Integer)
    PARAM = Column(String(1024))

    mp_file = relationship('MpFile')


t_mp_preferences = Table(
    'mp_preferences', metadata,
    Column('MPID', ForeignKey('mp_profil.MPID'), nullable=False, index=True),
    Column('FULLNAME', String(1024)),
    Column('FILTER', String(1024)),
    Column('GUI', String(1024)),
    Column('CUSTOM', String(1024))
)


class MpProfil(Base):
    __tablename__ = 'mp_profil'
    __table_args__ = (
        Index('MPUSERUNIQUE', 'BCHST', 'MPUSER'),
    )

    MPID = Column(Integer, primary_key=True)
    MPUSER = Column(String(128), nullable=False)
    BCHST = Column(ForeignKey('personen.PERS_ID'), nullable=False)
    SECLEVEL = Column(Integer, nullable=False)
    S_ID = Column(ForeignKey('sprachen.S_ID'), nullable=False, index=True)
    LAND_ID = Column(ForeignKey('land.LAND_ID'), nullable=False, index=True)
    DLTT_ID = Column(ForeignKey('traeger_typ.TYP_ID'), nullable=False, index=True)
    DLT_ID = Column(ForeignKey('dienst_traeger.DLT_ID'), nullable=False, index=True)
    KAT_ID = Column(ForeignKey('kategorie.KAT_ID'), nullable=False, index=True)
    DLAT_ID = Column(ForeignKey('angebots_typ.ART_ID'), nullable=False, index=True)
    DLNT_ID = Column(ForeignKey('reisender_typ.RKR_ID'), nullable=False, index=True)
    SAI_ID = Column(ForeignKey('saison.SAI_ID'), nullable=False, index=True)
    PRG_ID = Column(ForeignKey('programm.PRG_ID'), nullable=False, index=True)
    A_ZEIT = Column(BigInteger, nullable=False)
    E_ZEIT = Column(BigInteger, nullable=False)
    P_RANGE = Column(Integer, nullable=False)

    personen = relationship('Personen')
    angebots_typ = relationship('AngebotsTyp')
    reisender_typ = relationship('ReisenderTyp')
    traeger_typ = relationship('TraegerTyp')
    dienst_traeger = relationship('DienstTraeger')
    kategorie = relationship('Kategorie')
    land = relationship('Land')
    programm = relationship('Programm')
    saison = relationship('Saison')
    sprachen = relationship('Sprachen')


class MpProx(Base):
    __tablename__ = 'mp_prox'

    ORT_ID = Column(Integer, primary_key=True, nullable=False)
    PROX_ID = Column(Integer, primary_key=True, nullable=False)


class MpReminder(Base):
    __tablename__ = 'mp_reminder'

    REM_ID = Column(Integer, primary_key=True)
    MPID = Column(ForeignKey('mp_profil.MPID'), nullable=False, index=True)
    K_ID = Column(ForeignKey('kollektiv.K_ID'), index=True)
    BID = Column(ForeignKey('buchung.BID'), index=True)
    PERS_ID = Column(ForeignKey('personen.PERS_ID'), index=True)
    KID = Column(ForeignKey('personen.PERS_ID'), index=True)
    ENTRY = Column(DateTime)
    DEADLINE = Column(DateTime)
    PERSON = Column(Integer)
    PERS_TYP = Column(Integer)
    NOTICE = Column(String(1024))
    OPT = Column(String(1024))

    buchung = relationship('Buchung')
    personen = relationship('Personen', primaryjoin='MpReminder.KID == Personen.PERS_ID')
    kollektiv = relationship('Kollektiv')
    mp_profil = relationship('MpProfil')
    personen1 = relationship('Personen', primaryjoin='MpReminder.PERS_ID == Personen.PERS_ID')


class MpTextDoc(Base):
    __tablename__ = 'mp_text_doc'

    TEXTID = Column(Integer, primary_key=True, nullable=False)
    TYP = Column(Integer, primary_key=True, nullable=False)
    MULT_ID = Column(ForeignKey('mp_multimedia.MULT_ID'), primary_key=True, nullable=False, index=True)

    mp_multimedia = relationship('MpMultimedia')


class MpTexte(Base):
    __tablename__ = 'mp_texte'

    TEXTID = Column(Integer, primary_key=True, nullable=False)
    TYP = Column(Integer, primary_key=True, nullable=False)
    S_ID = Column(ForeignKey('sprachen.S_ID'), primary_key=True, nullable=False, index=True)
    TEXT = Column(String(1024), nullable=False)

    sprachen = relationship('Sprachen')


t_mpv_akt = Table(
    'mpv_akt', metadata,
    Column('id', Integer),
    Column('bez', String(1024)),
    Column('ubez', String(1024)),
    Column('ord', Integer),
    Column('spr', Integer)
)


t_mpv_akt_detail = Table(
    'mpv_akt_detail', metadata,
    Column('bid', Integer),
    Column('pers_id', Integer),
    Column('dlg_id', Integer),
    Column('dl_id', Integer),
    Column('teil', Integer),
    Column('z_flag', Integer),
    Column('akt_id', Integer),
    Column('ord', Integer),
    Column('a_flag', Integer),
    Column('m_flag', Integer),
    Column('a_typ_id', Integer),
    Column('proz', String(1024))
)


t_mpv_angebot = Table(
    'mpv_angebot', metadata,
    Column('art_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('textid', Integer)
)


t_mpv_arr = Table(
    'mpv_arr', metadata,
    Column('arr_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('a_dat', DateTime),
    Column('prg_id', Integer),
    Column('textid', Integer),
    Column('sai_id', Integer)
)


t_mpv_arr_dl = Table(
    'mpv_arr_dl', metadata,
    Column('arr_id', Integer),
    Column('a_dat', DateTime),
    Column('dlg_id', Integer),
    Column('bez', String(1024)),
    Column('a_zeit', DateTime),
    Column('teil', Integer),
    Column('prio', Integer),
    Column('akt_id', Integer),
    Column('s_id', Integer)
)


t_mpv_arr_dlg = Table(
    'mpv_arr_dlg', metadata,
    Column('arr_id', Integer),
    Column('teil', Integer),
    Column('prio', Integer),
    Column('dlg_id', Integer),
    Column('dl_id', Integer),
    Column('ord', Integer),
    Column('a_zeit', DateTime),
    Column('res_f', Integer),
    Column('bez', String(1024)),
    Column('bez1', String(1024)),
    Column('s_id', Integer),
    Column('dtg_zeit', DateTime)
)


t_mpv_buchung = Table(
    'mpv_buchung', metadata,
    Column('d_bid', Integer),
    Column('bid', Integer),
    Column('ref', String(256)),
    Column('arr_id', Integer),
    Column('kid', Integer),
    Column('sach', Integer),
    Column('bchst', Integer),
    Column('anw', Integer),
    Column('b_dat', DateTime),
    Column('m_dat', DateTime),
    Column('mapo_dat', BigInteger),
    Column('mapo_opt_bst', Integer),
    Column('opt_bst', DateTime),
    Column('mapo_opt_kid', Integer),
    Column('opt_kid', DateTime),
    Column('sta', Integer),
    Column('ast', Integer),
    Column('sai_id', Integer),
    Column('k_id', Integer),
    Column('history', Integer),
    Column('textid', Integer)
)


t_mpv_dl = Table(
    'mpv_dl', metadata,
    Column('dlg_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('textid', Integer),
    Column('sai_id', Integer),
    Column('a_zeit', DateTime),
    Column('akt_id', Integer)
)


t_mpv_dl_tdl = Table(
    'mpv_dl_tdl', metadata,
    Column('dlg_id', Integer),
    Column('start_zeit', DateTime),
    Column('dl_id', Integer),
    Column('bez', String(1024)),
    Column('a_zeit', DateTime),
    Column('e_zeit', DateTime),
    Column('ord', Integer),
    Column('res_f', Integer),
    Column('s_id', Integer)
)


t_mpv_dla = Table(
    'mpv_dla', metadata,
    Column('dla_id', Integer),
    Column('h_dla_id', Integer),
    Column('ord', Integer),
    Column('dlt_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('akt_id', Integer),
    Column('ort', String(256)),
    Column('art_id', Integer),
    Column('dau', Integer),
    Column('textid', Integer),
    Column('von', DateTime),
    Column('nach', DateTime)
)


t_mpv_dln = Table(
    'mpv_dln', metadata,
    Column('dln_id', Integer),
    Column('name', String(512)),
    Column('vor', String(512)),
    Column('ort', String(256)),
    Column('s_id', Integer),
    Column('sta_id', Integer),
    Column('textid', Integer),
    Column('rkr_id', Integer),
    Column('sex', Integer),
    Column('ext_txt', Integer),
    Column('land_id', Integer),
    Column('age', String(256)),
    Column('passnr', String(256)),
    Column('attr1', String(1024)),
    Column('attr2', String(1024))
)


t_mpv_dlnadr = Table(
    'mpv_dlnadr', metadata,
    Column('pers_id', Integer),
    Column('ans', String(256)),
    Column('name', String(512)),
    Column('vor', String(512)),
    Column('adr1', String(1024)),
    Column('adr2', String(1024)),
    Column('adr3', String(1024)),
    Column('plz', String(256)),
    Column('ort', String(256)),
    Column('land_id', Integer),
    Column('sta_id', Integer)
)


t_mpv_dlt = Table(
    'mpv_dlt', metadata,
    Column('dlt_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('kat_id', Integer),
    Column('h_dlt_id', Integer),
    Column('host_id', Integer),
    Column('typ_id', Integer),
    Column('textid', Integer),
    Column('stufe', Integer)
)


t_mpv_gra = Table(
    'mpv_gra', metadata,
    Column('gra_id', Integer),
    Column('bez', String(1024)),
    Column('dlt_id', Integer),
    Column('dltbez', String(1024)),
    Column('textid', Integer),
    Column('s_id', Integer)
)


t_mpv_kapa = Table(
    'mpv_kapa', metadata,
    Column('kat_id', Integer),
    Column('katbez', String(1024)),
    Column('kat_s_id', Integer),
    Column('tdl_id', Integer),
    Column('tdlbez', String(1024)),
    Column('tdl_s_id', Integer),
    Column('pre_id', Integer),
    Column('anz', Integer),
    Column('busy', Integer),
    Column('vpr', Float)
)


t_mpv_kapadet = Table(
    'mpv_kapadet', metadata,
    Column('kat_id', Integer),
    Column('katbez', String(1024)),
    Column('kat_s_id', Integer),
    Column('tdl_id', Integer),
    Column('tdlbez', String(1024)),
    Column('a_zeit', DateTime),
    Column('e_zeit', DateTime),
    Column('tdl_s_id', Integer),
    Column('pre_id', Integer),
    Column('anz', Integer),
    Column('busy', Integer),
    Column('vpr', Float)
)


t_mpv_kar = Table(
    'mpv_kar', metadata,
    Column('kar_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('textid', Integer)
)


t_mpv_kat = Table(
    'mpv_kat', metadata,
    Column('kat_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('h_kat_id', Integer),
    Column('typ_id', Integer),
    Column('ga', Integer),
    Column('textid', Integer)
)


t_mpv_kon = Table(
    'mpv_kon', metadata,
    Column('kont_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('hostkont_id', Integer),
    Column('kunden_id', Integer),
    Column('opt_dat', BigInteger),
    Column('ref', String(256)),
    Column('sai_id', Integer),
    Column('textid', Integer)
)


t_mpv_koncheck = Table(
    'mpv_koncheck', metadata,
    Column('hostkont_id', Integer),
    Column('kont_id', Integer),
    Column('kat_id', Integer),
    Column('dlt_id', Integer),
    Column('anz', Integer),
    Column('busy', Integer)
)


t_mpv_kunadr = Table(
    'mpv_kunadr', metadata,
    Column('pers_id', Integer),
    Column('ans', String(256)),
    Column('name', String(512)),
    Column('adr1', String(1024)),
    Column('adr2', String(1024)),
    Column('adr3', String(1024)),
    Column('plz', String(256)),
    Column('ort', String(256)),
    Column('kant', String(256)),
    Column('land_id', Integer),
    Column('sta_id', Integer),
    Column('k_typ_id', Integer),
    Column('tel', String(256)),
    Column('fax', String(256))
)


t_mpv_kunden = Table(
    'mpv_kunden', metadata,
    Column('kun_id', Integer),
    Column('name', String(512)),
    Column('ort', String(256)),
    Column('s_id', Integer),
    Column('sta_id', Integer),
    Column('textid', Integer),
    Column('kant', String(256)),
    Column('tel', String(256)),
    Column('fax', String(256)),
    Column('tlx', String(256)),
    Column('konto', String(256)),
    Column('leiter', Integer),
    Column('attr1', String(1024)),
    Column('attr2', String(1024)),
    Column('k_typ_id', Integer),
    Column('land_id', Integer),
    Column('whr_id', Integer)
)


t_mpv_land = Table(
    'mpv_land', metadata,
    Column('land_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('krzl', String(256)),
    Column('haupt_ort', Integer),
    Column('haupt_spr', Integer),
    Column('haupt_whr', Integer),
    Column('textid', Integer),
    Column('vat', Float)
)


t_mpv_lw = Table(
    'mpv_lw', metadata,
    Column('land_id', Integer),
    Column('landbez', String(1024)),
    Column('landbezs_id', Integer),
    Column('whr_id', Integer),
    Column('whrbez', String(1024)),
    Column('whrbezs_id', Integer),
    Column('kurs_typ', Integer),
    Column('a_kurs', Float),
    Column('v_kurs', Float)
)


t_mpv_ort = Table(
    'mpv_ort', metadata,
    Column('ort_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('krzl', String(256)),
    Column('landbez', String(1024)),
    Column('landbezs_id', Integer),
    Column('textid', Integer),
    Column('zeitver', Integer),
    Column('koord1', Integer),
    Column('koord2', Integer)
)


t_mpv_prg = Table(
    'mpv_prg', metadata,
    Column('prg_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('textid', Integer),
    Column('sai_id', Integer)
)


t_mpv_res_dl = Table(
    'mpv_res_dl', metadata,
    Column('bid', Integer),
    Column('pers_id', Integer),
    Column('name', String(512)),
    Column('dl_id', Integer),
    Column('dlazeit', DateTime),
    Column('tdl_id', Integer),
    Column('tdlazeit', DateTime),
    Column('tdlezeit', DateTime),
    Column('resazeit', DateTime),
    Column('resezeit', DateTime),
    Column('kat_id', Integer),
    Column('katbez', String(1024)),
    Column('typ_id', Integer),
    Column('dlt_id', Integer),
    Column('dltbez', String(1024)),
    Column('kont_id', Integer),
    Column('r_sta', Integer),
    Column('s_id', Integer)
)


t_mpv_resdl = Table(
    'mpv_resdl', metadata,
    Column('bid', Integer),
    Column('pers_id', Integer),
    Column('teil', Integer),
    Column('dl_id', Integer),
    Column('dl_bez', String(1024)),
    Column('dl_sid', Integer),
    Column('tdl_id', Integer),
    Column('resazeit', DateTime),
    Column('resezeit', DateTime),
    Column('kat_id', Integer),
    Column('typ_id', Integer),
    Column('dlt_id', Integer),
    Column('kont_id', Integer),
    Column('r_sta', Integer)
)


t_mpv_resdln = Table(
    'mpv_resdln', metadata,
    Column('bid', Integer),
    Column('pers_id', Integer),
    Column('name', String(512)),
    Column('teil', Integer),
    Column('dl_id', Integer),
    Column('tdl_id', Integer),
    Column('resazeit', DateTime),
    Column('resezeit', DateTime),
    Column('kat_id', Integer),
    Column('typ_id', Integer),
    Column('dlt_id', Integer),
    Column('kont_id', Integer),
    Column('r_sta', Integer)
)


t_mpv_rkr = Table(
    'mpv_rkr', metadata,
    Column('rkr_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('textid', Integer),
    Column('dlncode', String(256)),
    Column('vonalter', Integer),
    Column('bisalter', Integer)
)


t_mpv_routen = Table(
    'mpv_routen', metadata,
    Column('dlg_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('von', String(256)),
    Column('nach', String(256))
)


t_mpv_saidet = Table(
    'mpv_saidet', metadata,
    Column('sai_id', Integer),
    Column('saibez', String(1024)),
    Column('prg_id', Integer),
    Column('prgbez', String(1024)),
    Column('arr_id', Integer),
    Column('arrbez', String(1024)),
    Column('a_dat', DateTime),
    Column('teil', Integer),
    Column('prio', Integer),
    Column('dl_id', Integer),
    Column('dlbez', String(1024)),
    Column('a_zeit', DateTime),
    Column('s_id', Integer)
)


t_mpv_saison = Table(
    'mpv_saison', metadata,
    Column('sai_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('von', DateTime),
    Column('bis', DateTime),
    Column('textid', Integer)
)


t_mpv_sprache = Table(
    'mpv_sprache', metadata,
    Column('s_id', Integer),
    Column('bez', String(1024)),
    Column('bezsprid', Integer),
    Column('dialog', Integer),
    Column('sysbez', String(256))
)


t_mpv_status = Table(
    'mpv_status', metadata,
    Column('sta_id', Integer),
    Column('abk', String(256)),
    Column('sta', String(1024)),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('kond', Float),
    Column('typ', Integer)
)


t_mpv_tdl = Table(
    'mpv_tdl', metadata,
    Column('dl_id', Integer),
    Column('h_dl_id', Integer),
    Column('dla_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('ord', Integer),
    Column('a_zeit', DateTime),
    Column('e_zeit', DateTime),
    Column('res_f', Integer),
    Column('kid', Integer),
    Column('konto', String(256)),
    Column('textid', Integer),
    Column('sai_id', Integer)
)


t_mpv_traeger = Table(
    'mpv_traeger', metadata,
    Column('spr', Integer),
    Column('typ', Integer),
    Column('id', Integer),
    Column('bez', String(1024)),
    Column('hid', Integer),
    Column('host', Integer)
)


t_mpv_ttyp = Table(
    'mpv_ttyp', metadata,
    Column('spr', Integer),
    Column('id', Integer),
    Column('bez', String(1024)),
    Column('hid', Integer),
    Column('hbez', String(1024))
)


t_mpv_whr = Table(
    'mpv_whr', metadata,
    Column('whr_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('krzl', String(256)),
    Column('status', Integer),
    Column('textid', Integer)
)


class Msg(Base):
    __tablename__ = 'msg'
    __table_args__ = (
        Index('msg_index', 'MSG_TYP', 'MSG_ID', 'S_ID', 'TEXTNR'),
    )

    MSG_TYP = Column(Integer, primary_key=True, nullable=False, index=True)
    MSG_ID = Column(Integer, primary_key=True, nullable=False)
    S_ID = Column(ForeignKey('sprachen.S_ID'), primary_key=True, nullable=False, index=True)
    TEXTNR = Column(Integer, primary_key=True, nullable=False)
    TEXT = Column(String(1024), nullable=False)

    sprachen = relationship('Sprachen')


class Ort(Base):
    __tablename__ = 'ort'
    __table_args__ = (
        Index('ort_index', 'ORT_ID', 'LAND_ID'),
    )

    ORT_ID = Column(Integer, primary_key=True)
    BEZ_ID = Column(Integer, nullable=False, unique=True)
    LAND_ID = Column(ForeignKey('land.LAND_ID'), nullable=False, index=True)
    TEXTID = Column(Integer)
    KRZL = Column(String(256))
    ZEITVER = Column(Integer)
    KOORD1 = Column(Integer)
    KOORD2 = Column(Integer)
    ORT_TYP = Column(Integer)

    land = relationship('Land')


class PcxFile(Base):
    __tablename__ = 'pcx_files'

    PCX_ID = Column(Integer, primary_key=True)
    BEZ_ID = Column(Integer, nullable=False)
    FILENAME = Column(String(1024), nullable=False)
    X = Column(Integer)
    Y = Column(Integer)
    TYP = Column(Integer, nullable=False)
    TYPCODE = Column(Integer, nullable=False)
    FOLGE = Column(Integer, nullable=False)


class Persadr(Base):
    __tablename__ = 'persadr'

    PERS_ID = Column(ForeignKey('personen.PERS_ID'), primary_key=True, nullable=False, unique=True)
    ADR_TYP = Column(Integer, primary_key=True, nullable=False)
    ANS = Column(String(256))
    ADR1 = Column(String(1024))
    ADR2 = Column(String(1024))
    ADR3 = Column(String(1024))
    PLZ = Column(String(256))
    ORT = Column(String(256))
    KANT = Column(String(256))
    LAND_ID = Column(Integer)
    STA_ID = Column(Integer)
    HAUPT_FLAG = Column(Integer)
    RCH_FLAG = Column(Integer)
    MAIL_FLAG = Column(Integer)
    TEL = Column(String(256))
    HANDY = Column(String(256))
    FAX = Column(String(256))
    TLX = Column(String(256))
    EMAIL = Column(String(1024))
    WEB = Column(String(1024))

    personen = relationship('Personen')


class Personen(Base):
    __tablename__ = 'personen'

    PERS_ID = Column(Integer, primary_key=True, unique=True)
    PERS_TYP = Column(Integer, nullable=False, index=True)
    NAME = Column(String(512), nullable=False, index=True)
    S_ID = Column(ForeignKey('sprachen.S_ID'), nullable=False, index=True)
    STA_ID = Column(Integer)
    TEXTID = Column(Integer)

    sprachen = relationship('Sprachen')


class Prei(Base):
    __tablename__ = 'preis'

    PRE_ID = Column(Integer, primary_key=True)
    APR = Column(Float, nullable=False)
    EPR = Column(Float, nullable=False)
    VPR = Column(Float, nullable=False)
    GLT = Column(BigInteger, nullable=False)
    WHR_ID = Column(ForeignKey('waehrung.WHR_ID'), nullable=False, index=True)
    KBST = Column(ForeignKey('personen.PERS_ID'), nullable=False, index=True)
    KAR_ID = Column(ForeignKey('kosten_art.KAR_ID'), index=True)
    DLTT_ID = Column(ForeignKey('traeger_typ.TYP_ID'), index=True)
    KAT_ID = Column(ForeignKey('kategorie.KAT_ID'), index=True)
    RKR_ID = Column(ForeignKey('reisender_typ.RKR_ID'), index=True)
    DLA_ID = Column(ForeignKey('dienst_angebot.DLA_ID'), index=True)
    ARR_ID = Column(Integer)
    DL_ID = Column(ForeignKey('dienstleistung.DLG_ID'), index=True)
    EXT_ID = Column(Integer)
    DL_VONDAT = Column(BigInteger)
    DL_BISDAT = Column(BigInteger)
    KONT_ID = Column(ForeignKey('kontingent.KONT_ID'), index=True)
    STA_ID = Column(Integer)
    TEXTID = Column(Integer)
    HISTORY = Column(Integer)
    SAI_ID = Column(ForeignKey('saison.SAI_ID'), nullable=False, index=True)
    UNIT_TYP = Column(Integer)
    UNIT_VON = Column(Integer)
    UNIT_BIS = Column(Integer)
    DAU = Column(Integer)
    DAU_VON = Column(BigInteger)
    DAU_BIS = Column(BigInteger)

    dienst_angebot = relationship('DienstAngebot')
    traeger_typ = relationship('TraegerTyp')
    dienstleistung = relationship('Dienstleistung')
    kosten_art = relationship('KostenArt')
    kategorie = relationship('Kategorie')
    personen = relationship('Personen')
    kontingent = relationship('Kontingent')
    reisender_typ = relationship('ReisenderTyp')
    saison = relationship('Saison')
    waehrung = relationship('Waehrung')


class Programm(Base):
    __tablename__ = 'programm'

    PRG_ID = Column(Integer, primary_key=True)
    CODE = Column(String(256))
    BEZ_ID = Column(Integer, nullable=False)
    TEXTID = Column(Integer)
    SAI_ID = Column(ForeignKey('saison.SAI_ID'), nullable=False, index=True)

    saison = relationship('Saison')


class Region(Base):
    __tablename__ = 'regions'

    HOST_ID = Column(Integer, primary_key=True, nullable=False)
    H_DLT_ID = Column(Integer, primary_key=True, nullable=False)
    DLT_ID = Column(ForeignKey('dienst_traeger.DLT_ID'), primary_key=True, nullable=False, index=True)
    FOLGE = Column(Integer, primary_key=True, nullable=False)
    STUFE = Column(Integer, nullable=False)
    NUMMER = Column(Integer, nullable=False)

    dienst_traeger = relationship('DienstTraeger')


t_reisender = Table(
    'reisender', metadata,
    Column('PERS_ID', ForeignKey('personen.PERS_ID'), nullable=False, unique=True),
    Column('VOR', String(512), nullable=False),
    Column('RKR_ID', ForeignKey('reisender_typ.RKR_ID'), nullable=False, index=True),
    Column('SEX', Integer),
    Column('MUTTERS_ID', Integer),
    Column('AGE', String(256)),
    Column('PASSNR', String(256)),
    Column('ATTR1', String(1024)),
    Column('ATTR2', String(1024)),
    Column('TEXTID', Integer)
)


class ReisenderTyp(Base):
    __tablename__ = 'reisender_typ'

    RKR_ID = Column(Integer, primary_key=True, unique=True)
    DLNCODE = Column(String(256))
    BEZ_ID = Column(Integer, nullable=False, unique=True)
    VONALTER = Column(Integer)
    BISALTER = Column(Integer)
    TEXTID = Column(Integer)


t_res_dl_view = Table(
    'res_dl_view', metadata,
    Column('bid', Integer),
    Column('pers_id', Integer),
    Column('name', String(512)),
    Column('dl_id', Integer),
    Column('dlazeit', BigInteger),
    Column('tdl_id', Integer),
    Column('tdlazeit', BigInteger),
    Column('tdlezeit', BigInteger),
    Column('resazeit', BigInteger),
    Column('resezeit', BigInteger),
    Column('kat_id', Integer),
    Column('katbez', String(1024)),
    Column('typ_id', Integer),
    Column('dlt_id', Integer),
    Column('dltbez', String(1024)),
    Column('kont_id', Integer),
    Column('r_sta', Integer),
    Column('s_id', Integer)
)


t_resdl_view = Table(
    'resdl_view', metadata,
    Column('bid', Integer),
    Column('pers_id', Integer),
    Column('teil', Integer),
    Column('dl_id', Integer),
    Column('dl_bez', String(1024)),
    Column('dl_sid', Integer),
    Column('tdl_id', Integer),
    Column('resazeit', BigInteger),
    Column('resezeit', BigInteger),
    Column('kat_id', Integer),
    Column('typ_id', Integer),
    Column('dlt_id', Integer),
    Column('kont_id', Integer),
    Column('r_sta', Integer)
)


t_resdln_view = Table(
    'resdln_view', metadata,
    Column('bid', Integer),
    Column('pers_id', Integer),
    Column('name', String(512)),
    Column('teil', Integer),
    Column('dl_id', Integer),
    Column('tdl_id', Integer),
    Column('resazeit', BigInteger),
    Column('resezeit', BigInteger),
    Column('kat_id', Integer),
    Column('typ_id', Integer),
    Column('dlt_id', Integer),
    Column('kont_id', Integer),
    Column('r_sta', Integer)
)


t_reservation = Table(
    'reservation', metadata,
    Column('PERS_ID', ForeignKey('personen.PERS_ID'), nullable=False, index=True),
    Column('DLG_ID', ForeignKey('dienstleistung.DLG_ID'), nullable=False, index=True),
    Column('DL_ID', ForeignKey('dlg_parts.DL_ID'), nullable=False, index=True),
    Column('TEIL', Integer, nullable=False),
    Column('DLT_ID', ForeignKey('dienst_traeger.DLT_ID'), nullable=False, index=True),
    Column('TYP_ID', ForeignKey('traeger_typ.TYP_ID'), nullable=False, index=True),
    Column('BID', ForeignKey('buchung.BID'), nullable=False, index=True),
    Column('KONT_ID', ForeignKey('kontingent.KONT_ID'), nullable=False, index=True),
    Column('KAT_ID', ForeignKey('kategorie.KAT_ID'), nullable=False, index=True),
    Column('K_KON', Integer),
    Column('B_KON', Integer),
    Column('R_STA', Integer, nullable=False),
    Column('SAI_ID', ForeignKey('saison.SAI_ID'), nullable=False, index=True),
    Column('A_ZEIT', BigInteger),
    Column('E_ZEIT', BigInteger),
    Column('TEXTID', Integer)
)


t_rkr_view = Table(
    'rkr_view', metadata,
    Column('rkr_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('textid', Integer),
    Column('dlncode', String(256)),
    Column('vonalter', Integer),
    Column('bisalter', Integer)
)


t_routen_view = Table(
    'routen_view', metadata,
    Column('dlg_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('von', String(256)),
    Column('nach', String(256))
)


t_sai_view = Table(
    'sai_view', metadata,
    Column('sai_id', Integer),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('von', BigInteger),
    Column('bis', BigInteger),
    Column('textid', Integer)
)


class Saison(Base):
    __tablename__ = 'saison'

    SAI_ID = Column(Integer, primary_key=True, unique=True)
    CODE = Column(String(256))
    BEZ_ID = Column(Integer, nullable=False, unique=True)
    VON = Column(BigInteger, nullable=False)
    BIS = Column(BigInteger, nullable=False)
    TEXTID = Column(Integer)


t_spr_view = Table(
    'spr_view', metadata,
    Column('s_id', Integer),
    Column('bez', String(1024)),
    Column('bezsprid', Integer),
    Column('dialog', Integer),
    Column('sysbez', String(256))
)


class Sprachen(Base):
    __tablename__ = 'sprachen'

    S_ID = Column(Integer, primary_key=True, unique=True)
    BEZ_ID = Column(Integer, nullable=False, unique=True)
    DIALOG = Column(Integer, nullable=False)
    SYSBEZ = Column(String(256), nullable=False)
    OUTPUT = Column(Integer)
    GUI = Column(Integer)


t_sta_view = Table(
    'sta_view', metadata,
    Column('sta_id', Integer),
    Column('abk', String(256)),
    Column('sta', String(1024)),
    Column('bez', String(1024)),
    Column('s_id', Integer),
    Column('kond', Float),
    Column('typ', Integer)
)


class StatusWerte(Base):
    __tablename__ = 'status_werte'
    __table_args__ = (
        Index('sta_index', 'STA_ID', 'TYP'),
        Index('stabez_index', 'BEZ_ID', 'TYP')
    )

    STA_ID = Column(Integer, primary_key=True, nullable=False, index=True)
    ABK = Column(String(256), nullable=False)
    STA = Column(String(1024), nullable=False)
    BEZ_ID = Column(Integer, nullable=False, index=True)
    KOND = Column(Float, nullable=False)
    TYP = Column(Integer, primary_key=True, nullable=False, index=True)


class TdbVersion(Base):
    __tablename__ = 'tdb_version'

    DBVERSION = Column(Integer, primary_key=True)
    DBDATE = Column(DateTime, nullable=False)


t_tdbv_act = Table(
    'tdbv_act', metadata,
    Column('ACT_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer),
    Column('TEXTID', Integer),
    Column('AFLAG', String(1024)),
    Column('AFLAGID', Integer),
    Column('BFLAG', String(1024)),
    Column('BFLAGID', Integer),
    Column('B2FLAG', String(1024)),
    Column('B2FLAGID', Integer),
    Column('MFLAG', String(1024)),
    Column('MFLAGID', Integer),
    Column('ACTTYPE', String(1024)),
    Column('ACTTYPEID', Integer),
    Column('ACTTPROC', String(1024)),
    Column('FILE_ID', Integer)
)


t_tdbv_actgrp = Table(
    'tdbv_actgrp', metadata,
    Column('ACT_ID', Integer),
    Column('BEZ', String(1024)),
    Column('PARENTID', Integer),
    Column('PARENTBEZ', String(1024)),
    Column('ORD', Integer),
    Column('HOSTID', Integer),
    Column('HOST', String(1024)),
    Column('S_ID', Integer)
)


t_tdbv_actpara = Table(
    'tdbv_actpara', metadata,
    Column('ACTTYPE_ID', Integer),
    Column('BEZ', String(1024)),
    Column('CODE', String(1024)),
    Column('NO', Integer),
    Column('PARA', String(1024)),
    Column('PARATYPEID', Integer),
    Column('MAND', Integer),
    Column('FLAG', Integer),
    Column('TEXTID', Integer)
)


t_tdbv_actsel = Table(
    'tdbv_actsel', metadata,
    Column('ACT_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer)
)


t_tdbv_actt = Table(
    'tdbv_actt', metadata,
    Column('ACTTYPE_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer),
    Column('CODE', String(1024)),
    Column('TEXTID', Integer)
)


t_tdbv_acttsel = Table(
    'tdbv_acttsel', metadata,
    Column('ACTTYPE_ID', Integer),
    Column('BEZ', String(1024)),
    Column('CODE', String(1024)),
    Column('S_ID', Integer)
)


t_tdbv_adr = Table(
    'tdbv_adr', metadata,
    Column('PERS_ID', Integer),
    Column('ANS', String(256)),
    Column('ADR1', String(1024)),
    Column('ADR2', String(1024)),
    Column('ADR3', String(1024)),
    Column('PLZ', String(256)),
    Column('ORT', String(256)),
    Column('KANT', String(256)),
    Column('LAND_ID', Integer),
    Column('LAND', String(1024)),
    Column('LANDSID', Integer),
    Column('ADRTYP', String(1024)),
    Column('ADRTYPID', Integer),
    Column('ADRSTA', String(1024)),
    Column('ADRSTAID', Integer),
    Column('MAINFLAG', Integer),
    Column('INVOICEFLAG', Integer),
    Column('MAILFLAG', Integer),
    Column('TEL', String(256)),
    Column('HANDY', String(256)),
    Column('FAX', String(256)),
    Column('TLX', String(256)),
    Column('EMAIL', String(1024)),
    Column('WEB', String(1024))
)


t_tdbv_arr = Table(
    'tdbv_arr', metadata,
    Column('ARR_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer),
    Column('CODE', String(256)),
    Column('TEXTID', Integer),
    Column('ADAT', DateTime),
    Column('PRG_ID', Integer),
    Column('PRG', String(1024)),
    Column('SAI_ID', Integer),
    Column('SAI', String(1024))
)


t_tdbv_arrsel = Table(
    'tdbv_arrsel', metadata,
    Column('ARR_ID', Integer),
    Column('BEZ', String(1024)),
    Column('CODE', String(256)),
    Column('S_ID', Integer),
    Column('ADAT', DateTime)
)


t_tdbv_cat = Table(
    'tdbv_cat', metadata,
    Column('CAT_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer),
    Column('H_KAT_ID', Integer),
    Column('SUPTYP', String(1024)),
    Column('SUPTYPID', Integer),
    Column('GA', Integer),
    Column('TEXTID', Integer)
)


t_tdbv_catsel = Table(
    'tdbv_catsel', metadata,
    Column('CAT_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer)
)


t_tdbv_cattree = Table(
    'tdbv_cattree', metadata,
    Column('CAT_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('H_KAT_ID', Integer),
    Column('HBEZ', String(1024)),
    Column('S_ID', Integer)
)


t_tdbv_city = Table(
    'tdbv_city', metadata,
    Column('ORT_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer),
    Column('KRZL', String(256)),
    Column('LANDID', Integer),
    Column('LANDBEZ', String(256)),
    Column('TEXTID', Integer),
    Column('ZEITVER', Integer),
    Column('KOORD1', Integer),
    Column('KOORD2', Integer),
    Column('TYPE', Integer)
)


t_tdbv_citysel = Table(
    'tdbv_citysel', metadata,
    Column('ORT_ID', Integer),
    Column('BEZ', String(1024)),
    Column('KRZL', String(256)),
    Column('S_ID', Integer)
)


t_tdbv_country = Table(
    'tdbv_country', metadata,
    Column('LAND_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer),
    Column('KRZL', String(256)),
    Column('HAUPT_ORT', Integer),
    Column('HAUPT_SPR', Integer),
    Column('HAUPT_WHR', Integer),
    Column('TEXTID', Integer),
    Column('VAT', Float),
    Column('DATEFORMAT', String(256))
)


t_tdbv_countryd = Table(
    'tdbv_countryd', metadata,
    Column('LAND_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer),
    Column('KRZL', String(256)),
    Column('CAPITALID', Integer),
    Column('CAPITAL', String(1024)),
    Column('LANGID', Integer),
    Column('LANG', String(1024)),
    Column('CURID', Integer),
    Column('CURRENCY', String(1024)),
    Column('TEXTID', Integer),
    Column('VAT', Float),
    Column('DATEFORMAT', String(256))
)


t_tdbv_countrylang = Table(
    'tdbv_countrylang', metadata,
    Column('LAND_ID', Integer),
    Column('LANDBEZ', String(1024)),
    Column('CCODE', String(256)),
    Column('DATEFORMAT', String(256)),
    Column('S_ID', Integer),
    Column('SBEZ', String(1024)),
    Column('SCODE', String(256))
)


t_tdbv_countrysel = Table(
    'tdbv_countrysel', metadata,
    Column('LAND_ID', Integer),
    Column('BEZ', String(1024)),
    Column('KRZL', String(256)),
    Column('S_ID', Integer)
)


t_tdbv_cur = Table(
    'tdbv_cur', metadata,
    Column('WHR_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer),
    Column('KRZL', String(256)),
    Column('STATUS', Integer),
    Column('TEXTID', Integer)
)


t_tdbv_cursel = Table(
    'tdbv_cursel', metadata,
    Column('WHR_ID', Integer),
    Column('BEZ', String(1024)),
    Column('KRZL', String(256)),
    Column('S_ID', Integer)
)


t_tdbv_cust = Table(
    'tdbv_cust', metadata,
    Column('PERS_ID', Integer),
    Column('NAME', String(512)),
    Column('S_ID', Integer),
    Column('STA_ID', Integer),
    Column('TEXTID', Integer),
    Column('CUSTTYPEID', Integer),
    Column('TEL', String(256)),
    Column('HANDY', String(256)),
    Column('FAX', String(256)),
    Column('TLX', String(256)),
    Column('EMAIL', String(1024)),
    Column('WEB', String(1024)),
    Column('ACCOUNT', String(256)),
    Column('MANAGER', Integer),
    Column('ATTR1', String(1024)),
    Column('ATTR2', String(1024)),
    Column('CURID', Integer)
)


t_tdbv_custadr = Table(
    'tdbv_custadr', metadata,
    Column('PERS_ID', Integer),
    Column('ANS', String(256)),
    Column('NAME', String(512)),
    Column('LANG', String(1024)),
    Column('S_ID', Integer),
    Column('PERSSTA', String(1024)),
    Column('PERSSTAID', Integer),
    Column('ADR1', String(1024)),
    Column('ADR2', String(1024)),
    Column('ADR3', String(1024)),
    Column('PLZ', String(256)),
    Column('ORT', String(256)),
    Column('KANT', String(256)),
    Column('LAND_ID', Integer),
    Column('LAND', String(1024)),
    Column('TEXTID', Integer),
    Column('CUSTTYPE', String(256)),
    Column('CUSTTYPEID', Integer),
    Column('CTEL', String(256)),
    Column('CHANDY', String(256)),
    Column('CFAX', String(256)),
    Column('CTLX', String(256)),
    Column('CEMAIL', String(1024)),
    Column('CWEB', String(1024)),
    Column('ACCOUNT', String(256)),
    Column('MANAGER', Integer),
    Column('ATTR1', String(1024)),
    Column('ATTR2', String(1024)),
    Column('ADRTYP', String(1024)),
    Column('ADRTYPID', Integer),
    Column('ADRSTA', String(1024)),
    Column('ADRSTAID', Integer),
    Column('MAINFLAG', Integer),
    Column('INVOICEFLAG', Integer),
    Column('MAILFLAG', Integer),
    Column('TEL', String(256)),
    Column('HANDY', String(256)),
    Column('FAX', String(256)),
    Column('TLX', String(256)),
    Column('EMAIL', String(1024)),
    Column('WEB', String(1024)),
    Column('CURID', Integer),
    Column('CUR', String(256))
)


t_tdbv_custsel = Table(
    'tdbv_custsel', metadata,
    Column('PERS_ID', Integer),
    Column('NAME', String(512))
)


t_tdbv_cutt = Table(
    'tdbv_cutt', metadata,
    Column('CUSTTYPE_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer),
    Column('CODE', String(256)),
    Column('TEXTID', Integer)
)


t_tdbv_cuttsel = Table(
    'tdbv_cuttsel', metadata,
    Column('CUSTTYPE_ID', Integer),
    Column('BEZ', String(1024)),
    Column('CODE', String(256)),
    Column('S_ID', Integer)
)


t_tdbv_dlt = Table(
    'tdbv_dlt', metadata,
    Column('DLT_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('CODE', String(256)),
    Column('S_ID', Integer),
    Column('H_DLT_ID', Integer),
    Column('HOSTID', Integer),
    Column('DLT_GRP_ID', Integer),
    Column('TYP', String(1024)),
    Column('TYPID', Integer),
    Column('CAT', String(1024)),
    Column('CAT_ID', Integer),
    Column('LEVELPLACE', Integer),
    Column('NUMPLACE', Integer),
    Column('STA', String(1024)),
    Column('STAID', Integer),
    Column('TEXTID', Integer)
)


t_tdbv_dltoperator = Table(
    'tdbv_dltoperator', metadata,
    Column('DLT_ID', Integer),
    Column('BEZ', String(1024)),
    Column('CODE', String(256)),
    Column('S_ID', Integer),
    Column('COMPANY', String(512)),
    Column('COMPANYID', Integer)
)


t_tdbv_dltsel = Table(
    'tdbv_dltsel', metadata,
    Column('DLT_ID', Integer),
    Column('BEZ', String(1024)),
    Column('CODE', String(256)),
    Column('S_ID', Integer)
)


t_tdbv_dltt = Table(
    'tdbv_dltt', metadata,
    Column('TYP_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer),
    Column('H_TYP_ID', Integer),
    Column('HOST_TYP', Integer),
    Column('TEXTID', Integer)
)


t_tdbv_dlttree = Table(
    'tdbv_dlttree', metadata,
    Column('DLT_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('PARENTID', Integer),
    Column('PARENT', String(1024)),
    Column('HOSTID', Integer),
    Column('HOST', String(1024)),
    Column('S_ID', Integer)
)


t_tdbv_dlttsel = Table(
    'tdbv_dlttsel', metadata,
    Column('TYP_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer)
)


t_tdbv_dltttree = Table(
    'tdbv_dltttree', metadata,
    Column('TYP_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('H_TYP_ID', Integer),
    Column('HBEZ', String(1024)),
    Column('HOST_TYP', Integer),
    Column('HOSTBEZ', String(1024)),
    Column('S_ID', Integer)
)


t_tdbv_grpt = Table(
    'tdbv_grpt', metadata,
    Column('GRPTYPE_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer),
    Column('CODE', String(256)),
    Column('TEXTID', Integer)
)


t_tdbv_grptsel = Table(
    'tdbv_grptsel', metadata,
    Column('GRPTYPE_ID', Integer),
    Column('BEZ', String(1024)),
    Column('CODE', String(256)),
    Column('S_ID', Integer)
)


t_tdbv_lang = Table(
    'tdbv_lang', metadata,
    Column('S_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('SYSBEZ', String(256)),
    Column('DIALOG', Integer),
    Column('OUTPUT', Integer),
    Column('GUI', Integer),
    Column('BEZSPRID', Integer)
)


t_tdbv_langsel = Table(
    'tdbv_langsel', metadata,
    Column('S_ID', Integer),
    Column('BEZ', String(1024)),
    Column('SYSBEZ', String(256)),
    Column('BEZSPRID', Integer)
)


t_tdbv_o = Table(
    'tdbv_o', metadata,
    Column('O_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer),
    Column('CODE', String(256)),
    Column('TEXTID', Integer),
    Column('HOSTO', String(256)),
    Column('HOSTO_ID', Integer),
    Column('ORD', Integer),
    Column('SUP', String(256)),
    Column('SUPID', Integer),
    Column('ACT', String(1024)),
    Column('ACTID', Integer),
    Column('LOCATION', String(256)),
    Column('OT', String(1024)),
    Column('OTID', Integer),
    Column('DURATION', DateTime),
    Column('FROMCITY', String(256)),
    Column('FROMCITYID', Integer),
    Column('TOCITY', String(256)),
    Column('TOCITYID', Integer)
)


t_tdbv_osel = Table(
    'tdbv_osel', metadata,
    Column('O_ID', Integer),
    Column('BEZ', String(1024)),
    Column('CODE', String(256)),
    Column('S_ID', Integer)
)


t_tdbv_ot = Table(
    'tdbv_ot', metadata,
    Column('OT_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer),
    Column('TEXTID', Integer)
)


t_tdbv_otsel = Table(
    'tdbv_otsel', metadata,
    Column('OT_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer)
)


t_tdbv_pers = Table(
    'tdbv_pers', metadata,
    Column('PERS_ID', Integer),
    Column('FIRSTNAME', String(512)),
    Column('LASTNAME', String(512)),
    Column('S_ID', Integer),
    Column('STA_ID', Integer),
    Column('TEXTID', Integer),
    Column('PERSTYPEID', Integer),
    Column('SEX', Integer),
    Column('MUTTERSID', Integer),
    Column('AGE', String(256)),
    Column('PASSPORT', String(256)),
    Column('ATTR1', String(1024)),
    Column('ATTR2', String(1024)),
    Column('RTEXTID', Integer)
)


t_tdbv_persadr = Table(
    'tdbv_persadr', metadata,
    Column('PERS_ID', Integer),
    Column('ANS', String(256)),
    Column('FIRSTNAME', String(512)),
    Column('LASTNAME', String(512)),
    Column('LANG', String(1024)),
    Column('S_ID', Integer),
    Column('PERSSTA', String(1024)),
    Column('PERSSTAID', Integer),
    Column('ADR1', String(1024)),
    Column('ADR2', String(1024)),
    Column('ADR3', String(1024)),
    Column('PLZ', String(256)),
    Column('ORT', String(256)),
    Column('KANT', String(256)),
    Column('LAND_ID', Integer),
    Column('LAND', String(1024)),
    Column('TEXTID', Integer),
    Column('PERSTYPE', String(256)),
    Column('PERSTYPEID', Integer),
    Column('SEX', Integer),
    Column('MUTTERSID', Integer),
    Column('AGE', String(256)),
    Column('PASSPORT', String(256)),
    Column('ATTR1', String(1024)),
    Column('ATTR2', String(1024)),
    Column('RTEXTID', Integer),
    Column('ADRTYP', String(1024)),
    Column('ADRTYPID', Integer),
    Column('ADRSTA', String(1024)),
    Column('ADRSTAID', Integer),
    Column('MAINFLAG', Integer),
    Column('INVOICEFLAG', Integer),
    Column('MAILFLAG', Integer),
    Column('TEL', String(256)),
    Column('HANDY', String(256)),
    Column('FAX', String(256)),
    Column('TLX', String(256)),
    Column('EMAIL', String(1024)),
    Column('WEB', String(1024))
)


t_tdbv_perssel = Table(
    'tdbv_perssel', metadata,
    Column('PERS_ID', Integer),
    Column('FIRSTNAME', String(512)),
    Column('LASTNAME', String(512)),
    Column('SEX', Integer)
)


t_tdbv_perst = Table(
    'tdbv_perst', metadata,
    Column('PERSTYPE_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer),
    Column('CODE', String(256)),
    Column('VONALTER', Integer),
    Column('BISALTER', Integer),
    Column('TEXTID', Integer)
)


t_tdbv_perstsel = Table(
    'tdbv_perstsel', metadata,
    Column('PERSTYPE_ID', Integer),
    Column('BEZ', String(1024)),
    Column('CODE', String(256)),
    Column('S_ID', Integer)
)


t_tdbv_prg = Table(
    'tdbv_prg', metadata,
    Column('PRG_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer),
    Column('CODE', String(256)),
    Column('TEXTID', Integer),
    Column('SAI_ID', Integer),
    Column('SAI', String(1024))
)


t_tdbv_prgsel = Table(
    'tdbv_prgsel', metadata,
    Column('PRG_ID', Integer),
    Column('BEZ', String(1024)),
    Column('CODE', String(256)),
    Column('S_ID', Integer)
)


t_tdbv_prt = Table(
    'tdbv_prt', metadata,
    Column('PRT_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer),
    Column('TEXTID', Integer)
)


t_tdbv_prtsel = Table(
    'tdbv_prtsel', metadata,
    Column('PRT_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer)
)


t_tdbv_ratesel = Table(
    'tdbv_ratesel', metadata,
    Column('LAND_ID', Integer),
    Column('LANDBEZ', String(1024)),
    Column('WHR_ID', Integer),
    Column('WHRBEZ', String(1024)),
    Column('S_ID', Integer),
    Column('KURS_TYP', Integer),
    Column('A_KURS', Float),
    Column('V_KURS', Float),
    Column('FROMDAT', DateTime)
)


t_tdbv_sai = Table(
    'tdbv_sai', metadata,
    Column('SAI_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('CODE', String(256)),
    Column('VON', DateTime),
    Column('BIS', DateTime),
    Column('S_ID', Integer),
    Column('TEXTID', Integer)
)


t_tdbv_saisel = Table(
    'tdbv_saisel', metadata,
    Column('SAI_ID', Integer),
    Column('BEZ', String(1024)),
    Column('CODE', String(256)),
    Column('S_ID', Integer)
)


t_tdbv_serv = Table(
    'tdbv_serv', metadata,
    Column('SERV_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer),
    Column('CODE', String(256)),
    Column('TEXTID', Integer),
    Column('SEASON', String(1024)),
    Column('SEASONID', Integer),
    Column('ADAT', DateTime),
    Column('ACT', String(1024)),
    Column('ACTID', Integer)
)


t_tdbv_servsel = Table(
    'tdbv_servsel', metadata,
    Column('SERV_ID', Integer),
    Column('BEZ', String(1024)),
    Column('CODE', String(256)),
    Column('S_ID', Integer),
    Column('ADAT', DateTime)
)


t_tdbv_so = Table(
    'tdbv_so', metadata,
    Column('SO_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer),
    Column('CODE', String(256)),
    Column('TEXTID', Integer),
    Column('STARTDAT', DateTime),
    Column('STOPDAT', DateTime),
    Column('HOSTSO', String(256)),
    Column('HOSTSOID', Integer),
    Column('OFFER', String(256)),
    Column('OFFERID', Integer),
    Column('ORD', Integer),
    Column('RESFLAG', String(1024)),
    Column('RESFLAGID', Integer),
    Column('OPERATOR', String(512)),
    Column('OPERATORID', Integer),
    Column('ACCOUNT', String(256)),
    Column('INVOICE', String(512)),
    Column('INVOICEID', Integer),
    Column('SEASON', String(1024)),
    Column('SEASONID', Integer)
)


t_tdbv_sosel = Table(
    'tdbv_sosel', metadata,
    Column('SO_ID', Integer),
    Column('BEZ', String(1024)),
    Column('CODE', String(256)),
    Column('S_ID', Integer),
    Column('STARTDAT', DateTime),
    Column('STOPDAT', DateTime)
)


t_tdbv_sta = Table(
    'tdbv_sta', metadata,
    Column('STA_ID', Integer),
    Column('BEZ_ID', Integer),
    Column('ABK', String(256)),
    Column('STA', String(1024)),
    Column('BEZ', String(1024)),
    Column('S_ID', Integer),
    Column('KOND', Float),
    Column('TYP', Integer)
)


t_tdbv_stasel = Table(
    'tdbv_stasel', metadata,
    Column('STA_ID', Integer),
    Column('BEZ', String(1024)),
    Column('CODE', String(1024)),
    Column('S_ID', Integer),
    Column('TYP', Integer)
)


t_tdbv_user = Table(
    'tdbv_user', metadata,
    Column('MPID', Integer),
    Column('TDBUSER', String(128)),
    Column('BCHST', String(512)),
    Column('BCHSTID', Integer),
    Column('SECLEVEL', Integer),
    Column('LANG', String(1024)),
    Column('S_ID', Integer),
    Column('COUNTRY', String(1024)),
    Column('LAND_ID', Integer),
    Column('SUPTYPE', String(1024)),
    Column('DLTT_ID', Integer),
    Column('DLT', String(256)),
    Column('DLT_ID', Integer),
    Column('KAT', String(1024)),
    Column('KAT_ID', Integer),
    Column('DLAT', String(1024)),
    Column('DLAT_ID', Integer),
    Column('DLNT', String(256)),
    Column('DLNT_ID', Integer),
    Column('SEASON', String(256)),
    Column('SAI_ID', Integer),
    Column('PRG', String(256)),
    Column('PRG_ID', Integer),
    Column('STARTTIME', DateTime),
    Column('ENDTIME', DateTime),
    Column('PRANGE', Integer)
)


class Texte(Base):
    __tablename__ = 'texte'
    __table_args__ = (
        Index('textidtyp_index', 'TEXTID', 'TYP'),
        Index('texttypspr_index', 'S_ID', 'TYP'),
        Index('text_index', 'TEXTID', 'S_ID', 'TYP'),
        Index('textid_index', 'TEXTID', 'TEXTNR', 'S_ID', 'TYP')
    )

    TEXTID = Column(Integer, primary_key=True, nullable=False)
    S_ID = Column(ForeignKey('sprachen.S_ID'), primary_key=True, nullable=False, index=True)
    TEXTNR = Column(Integer, primary_key=True, nullable=False)
    TEXT = Column(String(1024), nullable=False)
    TYP = Column(Integer, primary_key=True, nullable=False, index=True)

    sprachen = relationship('Sprachen')


t_tmp_bezeichnung = Table(
    'tmp_bezeichnung', metadata,
    Column('BEZ_ID', Integer, nullable=False),
    Column('S_ID', Integer, nullable=False),
    Column('BEZ', String(1024), nullable=False),
    Column('TYP', Integer, nullable=False)
)


t_tmp_texte = Table(
    'tmp_texte', metadata,
    Column('TEXTID', Integer, nullable=False),
    Column('S_ID', Integer, nullable=False),
    Column('TEXTNR', Integer, nullable=False),
    Column('TEXT', String(1024), nullable=False),
    Column('TYP', Integer, nullable=False)
)


t_traeger_detail = Table(
    'traeger_detail', metadata,
    Column('DLT_ID', ForeignKey('dienst_traeger.DLT_ID'), primary_key=True, nullable=False),
    Column('FIRMA', ForeignKey('personen.PERS_ID'), primary_key=True, nullable=False, index=True)
)


class TraegerTyp(Base):
    __tablename__ = 'traeger_typ'

    TYP_ID = Column(Integer, primary_key=True)
    BEZ_ID = Column(Integer, nullable=False)
    H_TYP_ID = Column(Integer, nullable=False)
    HOST_TYP = Column(Integer, nullable=False)
    TEXTID = Column(Integer)


t_traeger_view = Table(
    'traeger_view', metadata,
    Column('spr', Integer),
    Column('typ', Integer),
    Column('id', Integer),
    Column('bez', String(1024)),
    Column('hid', Integer),
    Column('host', Integer)
)


t_ttyp_view = Table(
    'ttyp_view', metadata,
    Column('spr', Integer),
    Column('id', Integer),
    Column('bez', String(1024)),
    Column('hid', Integer),
    Column('hbez', String(1024))
)


class Waehrung(Base):
    __tablename__ = 'waehrung'

    WHR_ID = Column(Integer, primary_key=True, unique=True)
    BEZ_ID = Column(Integer, nullable=False, unique=True)
    TEXTID = Column(Integer)
    STATUS = Column(Integer)
    KRZL = Column(String(256))
