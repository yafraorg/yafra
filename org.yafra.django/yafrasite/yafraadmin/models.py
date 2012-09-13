# Create your models here.
# This is an auto-generated Django model module.
# You'll have to do the following manually to clean this up:
#     * Rearrange models' order
#     * Make sure each model has one field with primary_key=True
# Feel free to rename the models, but don't rename db_table values or field names.
#
# Also note: You'll have to insert the output of 'django-admin.py sqlcustom [appname]'
# into your database.

from django.db import models

#class AutoPkSupport(models.Model):
#    table_name = models.CharField(unique=True, max_length=300, db_column='TABLE_NAME') # Field name made lowercase.
#    next_id = models.BigIntegerField(db_column='NEXT_ID') # Field name made lowercase.
#    class Meta:
#        db_table = u'auto_pk_support'

class Person(models.Model):
    address = models.CharField(max_length=30000, blank=True)
    country = models.CharField(max_length=3000, blank=True)
    firstname = models.CharField(max_length=3000)
    googleid = models.CharField(max_length=12000, db_column='googleId', blank=True) # Field name made lowercase.
    id = models.IntegerField()
    name = models.CharField(max_length=3000)
    pkperson = models.IntegerField(primary_key=True, db_column='pkPerson') # Field name made lowercase.
    type = models.CharField(max_length=300)
    class Meta:
        db_table = u'person'

class Personlog(models.Model):
    eventaudit = models.CharField(max_length=30000, db_column='eventAudit', blank=True) # Field name made lowercase.
    eventauditreviewer = models.CharField(max_length=3000, db_column='eventAuditReviewer', blank=True) # Field name made lowercase.
    eventcreator = models.CharField(max_length=3000, db_column='eventCreator') # Field name made lowercase.
    eventdate = models.DateField(db_column='eventDate') # Field name made lowercase.
    eventdescription = models.CharField(max_length=30000, db_column='eventDescription') # Field name made lowercase.
    fkpersonid = models.ForeignKey(Person, db_column='fkPersonId') # Field name made lowercase.
    pkpersonlog = models.IntegerField(primary_key=True, db_column='pkPersonLog') # Field name made lowercase.
    class Meta:
        db_table = u'personlog'

class Yafrauser(models.Model):
    name = models.CharField(max_length=3000)
    picturelink = models.CharField(max_length=12000, blank=True)
    pkyafrauser = models.IntegerField(primary_key=True, db_column='pkYafraUser') # Field name made lowercase.
    userid = models.CharField(max_length=1500)
    class Meta:
        db_table = u'yafrauser'

class Yafraaudit(models.Model):
    auditobject = models.CharField(max_length=3000, blank=True)
    audittext = models.CharField(max_length=30000)
    fkuser = models.ForeignKey(Yafrauser, db_column='fkUser') # Field name made lowercase.
    pkaudit = models.IntegerField(primary_key=True, db_column='pkAudit') # Field name made lowercase.
    timestamp = models.DateField()
    class Meta:
        db_table = u'yafraaudit'

class Yafrabusinessrole(models.Model):
    description = models.CharField(max_length=12000, blank=True)
    flag = models.IntegerField(null=True, blank=True)
    name = models.CharField(max_length=3000)
    pkyafrabusinessrole = models.IntegerField(primary_key=True, db_column='pkYafraBusinessRole') # Field name made lowercase.
    class Meta:
        db_table = u'yafrabusinessrole'

class Yafrarole(models.Model):
    description = models.CharField(max_length=12000, blank=True)
    fkbusinessrole = models.ForeignKey(Yafrabusinessrole, db_column='fkBusinessRole') # Field name made lowercase.
    name = models.CharField(max_length=3000)
    pkyafrarole = models.IntegerField(primary_key=True, db_column='pkYafraRole') # Field name made lowercase.
    rights = models.CharField(max_length=3000, blank=True)
    class Meta:
        db_table = u'yafrarole'

class Yafrauserrole(models.Model):
    yrole = models.ForeignKey(Yafrabusinessrole, db_column='YRole') # Field name made lowercase.
    yuser = models.ForeignKey(Yafrauser, db_column='YUser') # Field name made lowercase.
    pkyafrauserrole = models.IntegerField(primary_key=True, db_column='pkYafraUserRole') # Field name made lowercase.
    class Meta:
        db_table = u'yafrauserrole'