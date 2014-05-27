# coding: utf-8
from sqlalchemy import BigInteger, Column, Date, ForeignKey, Integer, String, Table
from sqlalchemy.orm import relationship
from sqlalchemy.ext.declarative import declarative_base


Base = declarative_base()
metadata = Base.metadata


t_auto_pk_support = Table(
    'auto_pk_support', metadata,
    Column('TABLE_NAME', String(100), nullable=False, unique=True),
    Column('NEXT_ID', BigInteger, nullable=False)
)


class Person(Base):
    __tablename__ = 'person'

    address = Column(String(4000))
    country = Column(String(1000))
    firstname = Column(String(1000), nullable=False)
    googleId = Column(String(4000))
    id = Column(Integer, nullable=False)
    name = Column(String(1000), nullable=False)
    pkPerson = Column(Integer, primary_key=True)
    type = Column(String(100), nullable=False)


class Personlog(Base):
    __tablename__ = 'personlog'

    eventAudit = Column(String(4000))
    eventAuditReviewer = Column(String(1000))
    eventCreator = Column(String(1000), nullable=False)
    eventDate = Column(Date, nullable=False)
    eventDescription = Column(String(4000), nullable=False)
    fkPersonId = Column(ForeignKey('person.pkPerson'), nullable=False, index=True)
    pkPersonLog = Column(Integer, primary_key=True)

    person = relationship(u'Person')


class Yafraaudit(Base):
    __tablename__ = 'yafraaudit'

    auditobject = Column(String(1000))
    audittext = Column(String(4000), nullable=False)
    fkUser = Column(ForeignKey('yafrauser.pkYafraUser'), nullable=False, index=True)
    pkAudit = Column(Integer, primary_key=True)
    timestamp = Column(Date, nullable=False)

    yafrauser = relationship(u'Yafrauser')


class Yafrabusinessrole(Base):
    __tablename__ = 'yafrabusinessrole'

    description = Column(String(4000))
    flag = Column(Integer)
    name = Column(String(1000), nullable=False)
    pkYafraBusinessRole = Column(Integer, primary_key=True)


class Yafrarole(Base):
    __tablename__ = 'yafrarole'

    description = Column(String(4000))
    fkBusinessRole = Column(ForeignKey('yafrabusinessrole.pkYafraBusinessRole'), nullable=False, index=True)
    name = Column(String(1000), nullable=False)
    pkYafraRole = Column(Integer, primary_key=True)
    rights = Column(String(1000))

    yafrabusinessrole = relationship(u'Yafrabusinessrole')


class Yafrauser(Base):
    __tablename__ = 'yafrauser'

    name = Column(String(1000), nullable=False)
    picturelink = Column(String(4000))
    pkYafraUser = Column(Integer, primary_key=True)
    userid = Column(String(500), nullable=False)


class Yafrauserrole(Base):
    __tablename__ = 'yafrauserrole'

    YRole = Column(ForeignKey('yafrabusinessrole.pkYafraBusinessRole'), nullable=False, index=True)
    YUser = Column(ForeignKey('yafrauser.pkYafraUser'), nullable=False, index=True)
    pkYafraUserRole = Column(Integer, primary_key=True)

    yafrabusinessrole = relationship(u'Yafrabusinessrole')
    yafrauser = relationship(u'Yafrauser')
