'''
Created on 12.06.2012

@author: mwn
'''
from yafrasite.yafraadmin.models import Person, Personlog, Yafrauser, Yafraaudit, Yafrabusinessrole, Yafrarole, Yafrauserrole
from django.contrib import admin

class PersonAdmin(admin.ModelAdmin):
    list_display = ('id', 'firstname', 'name', 'address', 'country', 'type')
    search_fields = ('name',)
    list_filter = ('type', 'country',)
    ordering = ('-name',)
    fields = ('firstname', 'name', 'id', 'address', 'country', 'googleid', 'type')

       
admin.site.register(Person, PersonAdmin)
admin.site.register(Personlog)
admin.site.register(Yafrauser)
admin.site.register(Yafraaudit)
admin.site.register(Yafrabusinessrole)
admin.site.register(Yafrarole)
admin.site.register(Yafrauserrole)
