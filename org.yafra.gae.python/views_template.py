# -*- coding: utf-8 -*-
'''
  Copyright 2012 yafra.org

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

Created on Jan 5, 2013
@subject: plan module
@author: mwn

This module manages plans/calendars for clubs
'''
import webapp2
import logging
import json
import string
import StringIO
from datetime import datetime, timedelta
from xlwt import *
from reportlab.lib import colors
from reportlab.lib.pagesizes import A4
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer, Image, Table, TableStyle
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from google.appengine.ext import db
from google.appengine.api import images
from models import MCBmember, MCBpost
from usermgmt import UserMgmt
from views import BaseHandler
from utils import CreatePDF
from members import MemberMgmt
import utils

# /gfangene - public - overview on all gfangene
class GfangenePage(BaseHandler):
    def get(self):
        cuser = UserMgmt()
        user = cuser.get()
        mymem = None
        if user:
            mymem = cuser.ismember()
        query1 = db.Query(MCBmember)
        query1.filter('type =', utils.typepf)
        pfyffer = query1.run()
        query2 = db.Query(MCBmember)
        query2.filter('type =', utils.typetam)
        tamb = query2.run()
        query3 = db.Query(MCBmember)
        query3.filter('type =', utils.typevor)
        vort = query3.run()
        query4 = db.Query(MCBmember)
        query4.filter('type =', utils.typemaj)
        maj = query4.run()
        self.render_template('gfangeni.html', {'pfy': pfyffer, 'tam': tamb, 'vor': vort, 'major': maj, 'myself': user, 'mymem': mymem})

# /gfangene/([\d]+) - public - view 1 gfangene details
# TODO: addthis support in html instead of individual buttons
class GfangeneDetPage(BaseHandler):
    def get(self, gfangeneid):
        cuser = UserMgmt()
        user = cuser.get()
        mymem = None
        if user:
            mymem = cuser.ismember()
        g = MCBmember.get_by_id(long(gfangeneid))
        self.render_template('gfangene.html', {'member': g, 'myself': user, 'mymem': mymem})

# /gc/([\w]+) - public but with CODE
class GfangeneCodePage(BaseHandler):
    def get(self, code):
        cuser = UserMgmt()
        user = cuser.get()
        myMem = MemberMgmt()
        me = myMem.checkcode(code)
        if me == None:
            logging.info('mcbsujet.ch: gfangene code page - wrong CODE given')
            raise Exception("Du hesch kai richtige CODE yygeh - jetzt wirsch erscht raecht gsuecht!!")

        query = db.Query(MCBmember)
        query.filter('code =', code)
        g = query.get()
        query2 = db.Query(MCBpost)
        query2.order('-date')
        query2.filter('scope =', utils.privacy_public)
        query2.filter('active =', True)
        query2.filter('type =', utils.msg)
        comments = query2.run(limit = 8, offset = 0)
        self.render_template('gfangenecode.html', {'member': g, 'myself': user, 'msgs': comments})

# /gc - public but with CODE POST handler
class GfangeneCodeWPage(BaseHandler):
    def post(self):
        updmem = MCBmember.get_by_id(long(self.request.get('fmemid')))
        updmem.email = self.request.get('femail')
        updmem.name = self.request.get('fname')
        updmem.prename = self.request.get('fprename')
        updmem.pseudonym = self.request.get('fpseudo')
        updmem.mobil = self.request.get('fmobil')
        updmem.strof = self.request.get('fstrof')
        updmem.steckbrief = self.request.get('fsteck')
        updmem.cmt = self.request.get('fcmt')
        updmem.put()
        return webapp2.redirect('/gc/%s' % updmem.code)

# /gcxls/([\w]+) - get member excel sheet - public but with CODE
class GfangeneCodeXlsPage(BaseHandler):
    def get(self, code):
        myMem = MemberMgmt()
        me = myMem.checkcode(code)
        if me == None:
            return webapp2.redirect('/login')
 
        members = MCBmember.all().order('name')
        wb = Workbook()
        GREEN_TABLE_HEADER = easyxf(
             'font: bold 1, name Tahoma, height 160;'
             'align: vertical center, horizontal center, wrap on;'
             'borders: left thin, right thin, top thin, bottom thin;'
             'pattern: pattern solid, pattern_fore_colour green, pattern_back_colour green'
             )
        style1 = XFStyle()
        style1.num_format_str = 'D-MMM-YY'
        fullname = "Mitgliederliste Maertplatz Clique Basel Stammverein fuer %s %s" % (me.prename, me.name)
        ws = wb.add_sheet('Mitgliederliste')
        ws.write(0, 0, fullname)
        ws.write(1, 0, "Datum:")
        ws.write(1, 1, datetime.now(), style1)
        ws.write(2, 0, 'Vorname', GREEN_TABLE_HEADER)
        ws.write(2, 1, 'Name', GREEN_TABLE_HEADER)
        ws.write(2, 2, 'Email', GREEN_TABLE_HEADER)
        ws.write(2, 3, 'Handy', GREEN_TABLE_HEADER)
        ws.write(2, 4, 'Pseudonym', GREEN_TABLE_HEADER)
        ws.write(2, 5, 'Nimmt teil 2014', GREEN_TABLE_HEADER)
        ws.write(2, 6, 'V/P/T', GREEN_TABLE_HEADER)
        ws.write(2, 7, 'Aktiv', GREEN_TABLE_HEADER)
        ws.write(2, 8, 'Overall groessi', GREEN_TABLE_HEADER)
        row = 3
        for m in members:
            ws.write(row, 0, "%s" % m.prename)
            ws.write(row, 1, "%s" % m.name)
            ws.write(row, 2, "%s" % m.email)
            ws.write(row, 3, "%s" % m.mobil)
            ws.write(row, 4, "%s" % m.pseudonym)
            ws.write(row, 5, "%s" % m.sujetflag)
            ws.write(row, 6, "%s" % m.type)
            ws.write(row, 7, "%s" % m.active)
            ws.write(row, 8, "%s" % m.size)
            row += 1
        
        # HTTP headers to force file download
        self.response.headers['Content-Type'] = 'application/ms-excel; charset=UTF-8'
        self.response.headers['Content-Transfer-Encoding'] = 'Binary'
        self.response.headers['Content-disposition'] = 'attachment; filename="workbook.xls"'
        
        # output to user
        wb.save(self.response.out)

# /gfangenipdf -public - export gfangeni overview as PDF
class ExportGfangeniPage(BaseHandler):
    def get(self):
        cuser = UserMgmt()
        user = cuser.get()

        query = db.Query(MCBmember)
        query.filter('active =', True)
        query.order('-pseudonym')
        gfangeni = query.run()
        story = []
        styles=getSampleStyleSheet()
        gfangtitStyle = ParagraphStyle(name='gfangtit')
        gfangtitStyle.fontSize = 14
        gfangStyle = ParagraphStyle(name='gfangtext')
        gfangStyle.fontSize = 11
        titleStyle = styles['Heading1']
        h2Style = styles['Heading2']
        h2Style.spaceBefore = 8

        #story.append(Paragraph("Gfangen im Netz", titleStyle))

        for g in gfangeni:
            ptext = "Steggbrief Gfangene %s" % g.pseudonym
            title = Paragraph(ptext, gfangtitStyle)
            ptext = "%s" % g.steckbrief
            content = Paragraph(ptext, gfangStyle)
            if (g.pict != None):
                img = Image(StringIO.StringIO(g.pict), 32, 32)
                data = [[title, img], [content]]
            else:
                data = [[title], [content]]
            table = Table(data)
            table.setStyle(TableStyle([
                       ('VALIGN',(0,0),(-1,-1),'MIDDLE'),
                       ]))
 
            story.append(table)
            story.append(Spacer(1, 12))
 
        self.response.headers['Content-Type'] = 'application/pdf'
        doc = SimpleDocTemplate(self.response.out,pagesize=A4)
        footer = CreatePDF()
        doc.build(story, onFirstPage=footer.FooterPDF, onLaterPages=footer.FooterPDF)

# /gfangenepdf/([\d]+) - public - export gfangene as PDF
class ExportGfangenePage(BaseHandler):
    def get(self, gfangeneid):
        g = MCBmember.get_by_id(long(gfangeneid))

        story = []
        styles=getSampleStyleSheet()
        gfangStyle = ParagraphStyle(name='fancy')
        gfangStyle.fontSize = 14
        gfangStyle.spaceBefore = 8
        titleStyle = styles['Heading1']
        h2Style = styles['Heading2']
        h2Style.spaceBefore = 8

        if (g.pict != None):
            img = images.resize(g.pict, 130, 130)
            story.append(Image(StringIO.StringIO(img)))
            story.append(Spacer(1, 12))
        ptext = "Steggbrief Gfangene %s" % g.pseudonym
        story.append(Paragraph(ptext, titleStyle))
        story.append(Spacer(1, 12))
        ptext = "Wird gsuecht wäge:"
        story.append(Paragraph(ptext, h2Style))
        ptext = "%s" % g.steckbrief
        story.append(Paragraph(ptext, gfangStyle))
        story.append(Spacer(1, 12))
        ptext = "Strof:"
        story.append(Paragraph(ptext, h2Style))
        ptext = "%s" % g.strof
        story.append(Paragraph(ptext, gfangStyle))
        story.append(Spacer(1, 12))
        ptext = "Au no wichtig:"
        story.append(Paragraph(ptext, h2Style))
        ptext = "%s" % g.cmt
        story.append(Paragraph(ptext, gfangStyle))
        story.append(Spacer(1, 12))
        ptext = "Ufgob:"
        story.append(Paragraph(ptext, h2Style))
        ptext = "%s" % g.type
        story.append(Paragraph(ptext, gfangStyle))
        story.append(Spacer(1, 12))
        ptext = "Gfangenen Code:"
        story.append(Paragraph(ptext, h2Style))
        if (g.qrcode != None):
            img = images.resize(g.qrcode, 120, 120)
            story.append(Image(StringIO.StringIO(img)))
            story.append(Spacer(1, 12))

        self.response.headers['Content-Type'] = 'application/pdf'
        doc = SimpleDocTemplate(self.response.out,pagesize=A4)
        footer = CreatePDF()
        doc.build(story, onFirstPage=footer.FooterPDF, onLaterPages=footer.FooterPDF)

# /pict
class ImageHandler(BaseHandler):
    def get(self):
        g = MCBmember.get_by_id(long(self.request.get('memid')))
        if g.pict:
            img = images.resize(g.pict, 140)
            self.response.headers['Content-Type'] = 'image/png'
            self.response.out.write(img)
        else:
            self.response.out.write("No Image")

    def post(self):
        cuser = UserMgmt()
        user = cuser.get()
        g = MCBmember.get_by_id(long(self.request.get('memid')))
        raw_file = self.request.get('image')
        if not raw_file:
            raise Exception("Du hesch kai Datei ageeh, probier none mol, sunsch im Admin maelde")
        img = images.Image(raw_file)
#         img.resize(140, 140)
        img.resize(140)
        save = img.execute_transforms(output_encoding=images.PNG, parse_source_metadata=True)
        meta_data = img.get_original_metadata()
        if meta_data != None:
            #logging.info('mcbsujet.ch: meta data nach image %s', meta_data)
            if meta_data.get("Orientation"):
                #logging.info('mcbsujet.ch: meta data Orientation found %s', meta_data["Orientation"])
                if meta_data.get("Orientation") == 6:
                    #logging.info('mcbsujet.ch: rotate image by 90')
                    img.rotate(90)
                    save = img.execute_transforms(output_encoding=images.PNG, parse_source_metadata=True)
                if meta_data.get("Orientation") == 3:
                    #logging.info('mcbsujet.ch: rotate image by 180')
                    img.rotate(180)
                    save = img.execute_transforms(output_encoding=images.PNG, parse_source_metadata=True)
                if meta_data.get("Orientation") == 8:
                    #logging.info('mcbsujet.ch: rotate image by 270')
                    img.rotate(270)
                    save = img.execute_transforms(output_encoding=images.PNG, parse_source_metadata=True)
            else:
                logging.info('mcbsujet.ch: no orientation')
        g.pict = db.Blob(save)
        g.put()
        #logging.info('mcbsujet.ch: uploaded image')
        if user:
            return webapp2.redirect('/member/%d' % g.key().id())
        else:
            return webapp2.redirect('/gc/%s' % g.code)

# /qrcode
class QRcode(BaseHandler):
    def get(self):
        g = MCBmember.get_by_id(long(self.request.get('memid')))
        if g.qrcode:
            img = images.resize(g.qrcode, 140, 140)
            self.response.headers['Content-Type'] = 'image/png'
            self.response.out.write(img)
        else:
            self.response.out.write("No Image")

# /gps
class GpsPage(BaseHandler):
    def get(self):
        cuser = UserMgmt()
        user = cuser.get()
        filterdays = datetime.now() - timedelta(days=197)
        members = MCBmember.all()
        members.filter('gpsdate > ', filterdays)
        members.order('-gpsdate')

        mems = []
        i = 0
        for m in members:
            mm = MapMarkers()
            mm.key = long(m.key().id())
            mm.name = m.pseudonym
            mm.lat = float(m.lat)
            mm.lon = float(m.lon)
            mesz = m.gpsdate + timedelta(hours=1)
            mm.date = mesz.strftime('%d.%m.%Y %H:%M')
            if i > 25:
                indexletter = 'Z'
            else:
                indexletter = string.uppercase[i]
            mm.icon = 'http://maps.google.com/mapfiles/marker' + indexletter + '.png'
            mm.indexname = indexletter
            mems.append(mm)
            i += 1

        self.render_template('gfangene-map.html', {'gfangeni': mems, 'myself': user})

    def post(self):
        g = MCBmember.get_by_id(long(self.request.get('fmemid')))
        g.lat = float(self.request.get('flat'))
        g.lon = float(self.request.get('flon'))
        g.gpsdate = datetime.now()
        g.put()


class MapMarkers():
    def __init__(self):
        self.name = None
        self.lat = float(0)
        self.lon = float(0)
        self.icon = None
        self.indexname = None
        self.date = None
        self.key = long(0)


