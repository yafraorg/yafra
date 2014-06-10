# coding: utf-8
from app import db

#t_AUTO_PK_SUPPORT = db.Table(
#    'AUTO_PK_SUPPORT', db.metadata,
#    db.Column('TABLE_NAME', db.String(100), nullable=False, unique=True),
#    db.Column('NEXT_ID', db.BigInteger, nullable=False)
#)


class Person(db.Model):
    __tablename__ = 'Person'

    address = db.Column(db.String(4000))
    country = db.Column(db.String(1000))
    firstname = db.Column(db.String(1000), nullable=False)
    googleId = db.Column(db.String(4000))
    id = db.Column(db.Integer, nullable=False)
    name = db.Column(db.String(1000), nullable=False)
    pkPerson = db.Column(db.Integer, primary_key=True)
    type = db.Column(db.String(100), nullable=False)


class Personlog(db.Model):
    __tablename__ = 'PersonLog'

    eventAudit = db.Column(db.String(4000))
    eventAuditReviewer = db.Column(db.String(1000))
    eventCreator = db.Column(db.String(1000), nullable=False)
    eventDate = db.Column(db.Date, nullable=False)
    eventDescription = db.Column(db.String(4000), nullable=False)
    fkPersonId = db.Column(db.ForeignKey('Person.pkPerson'), nullable=False, index=True)
    pkPersonLog = db.Column(db.Integer, primary_key=True)

    Person = db.relationship('Person')


class Yafraaudit(db.Model):
    __tablename__ = 'YafraAudit'

    auditobject = db.Column(db.String(1000))
    audittext = db.Column(db.String(4000), nullable=False)
    fkUser = db.Column(db.ForeignKey('YafraUser.pkYafraUser'), nullable=False, index=True)
    pkAudit = db.Column(db.Integer, primary_key=True)
    timestamp = db.Column(db.Date, nullable=False)

    YafraUser = db.relationship('Yafrauser')


class Yafrabusinessrole(db.Model):
    __tablename__ = 'YafraBusinessRole'

    description = db.Column(db.String(4000))
    flag = db.Column(db.Integer)
    name = db.Column(db.String(1000), nullable=False)
    pkYafraBusinessRole = db.Column(db.Integer, primary_key=True)


class Yafrarole(db.Model):
    __tablename__ = 'YafraRole'

    description = db.Column(db.String(4000))
    fkBusinessRole = db.Column(db.ForeignKey('YafraBusinessRole.pkYafraBusinessRole'), nullable=False, index=True)
    name = db.Column(db.String(1000), nullable=False)
    pkYafraRole = db.Column(db.Integer, primary_key=True)
    rights = db.Column(db.String(1000))

    YafraBusinessRole = db.relationship('Yafrabusinessrole')


class Yafrauser(db.Model):
    __tablename__ = 'YafraUser'

    name = db.Column(db.String(1000), nullable=False)
    picturelink = db.Column(db.String(4000))
    pkYafraUser = db.Column(db.Integer, primary_key=True)
    userid = db.Column(db.String(500), nullable=False)


class Yafrauserrole(db.Model):
    __tablename__ = 'YafraUserRole'

    YRole = db.Column(db.ForeignKey('YafraBusinessRole.pkYafraBusinessRole'), nullable=False, index=True)
    YUser = db.Column(db.ForeignKey('YafraUser.pkYafraUser'), nullable=False, index=True)
    pkYafraUserRole = db.Column(db.Integer, primary_key=True)

    YafraBusinessRole = db.relationship('Yafrabusinessrole')
    YafraUser = db.relationship('Yafrauser')
