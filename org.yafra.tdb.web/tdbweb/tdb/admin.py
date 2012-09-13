'''
Created on 12.06.2012

@author: mwn
'''
from models import Sprachen
from django.contrib import admin

class SprachenAdmin(admin.ModelAdmin):
    list_display = ('s_id', 'bez_id', 'dialog', 'sysbez', 'gui')
    search_fields = ('sysbez',)
    list_filter = ('gui', 'dialog',)
    ordering = ('-sysbez',)
    fields = ['s_id', 'bez_id', 'dialog', 'sysbez', 'output', 'gui']
       
admin.site.register(Sprachen, SprachenAdmin)
