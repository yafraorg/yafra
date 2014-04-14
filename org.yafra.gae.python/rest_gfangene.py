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

This module handles RESTful of model post
'''
import webapp2
import logging
import utils
import json
import base64
import datetime
from google.appengine.ext import db
from google.appengine.api import users
from models import MCBmember
from usermgmt import UserMgmt
from views import BaseHandler

# /rest/g - PUBLIC all gfangeni
class GfangeneRest(BaseHandler):
    def get(self):
        query = db.Query(MCBmember)
        query.filter('active =', True)
# TODO: check on limit here - or provide page-ing
        gfangeni = query.run(limit = 150, offset = 0)
        response = []
        for obj in gfangeni:
            if obj.pict != None:
                #p = base64.b64encode(obj.pict)
                p = "http://mcbsujet.appspot.com/pict?memid=%s" % obj.key().id()
            else:
                p = None
            if obj.qrcode != None:
                q = "http://mcbsujet.appspot.com/qrcode?memid=%s" % obj.key().id()
            else:
                q = None
            response.append({'pseudonym': obj.pseudonym, 'steckbrief': obj.steckbrief, 'strof': obj.strof, 'cmt': obj.cmt, 'type': obj.type, 'pict': p, 'qr': q})
        self.render_jsonget(json.dumps(response))

# /rest/gcvalid/([\w]+) - PUBLIC access with valid CODE - get detailed list without picts
class GfangeneValidateCodeRest(BaseHandler):
    def get(self, code):
        withcode = code != ''
        if withcode:
            query = db.Query(MCBmember)
            query.filter('code =', code)
            mem = query.get()
            if mem:
                self.render_jsonget(json.dumps({'pseudonym': mem.pseudonym, 'name': mem.name, 'vor': mem.prename, 'mail': mem.email}))
            else:
                self.render_jsonget(json.dumps(1))
        else:
            self.render_jsonget(json.dumps(1))


# /rest/gc/([\w]+) - PUBLIC access with valid CODE - get detailed list without picts
class GfangeneCodeRest(BaseHandler):
    def get(self, code):
        cuser = UserMgmt()
        user = cuser.get()
        withcode = code != ''
        if withcode:
            query = db.Query(MCBmember)
            query.filter('code =', code)
            mem = query.get()
            if mem:
                query2 = db.Query(MCBmember)
                query2.filter('active =', True)
                gfangeni = query2.run(limit = 150, offset = 0)
                response = []
                for obj in gfangeni:
                    mesz = obj.gpsdate + datetime.timedelta(hours=1)
                    response.append({'pseudonym': obj.pseudonym, 'steckbrief': obj.steckbrief, 'strof': obj.strof, 'cmt': obj.cmt, 'type': obj.type, 'pict': obj.cmt, 'lat': obj.lat, 'lon':obj.lon, 'gpsdate': mesz.strftime('%d.%m.%y %H:%M'), 'email': obj.email, 'tel': obj.mobil})
                self.render_jsonget(json.dumps(response))
            else:
                self.render_jsonget(json.dumps("{'status': 'ERROR - CODE WRONG'}"))
        else:
            self.render_jsonget(json.dumps("{'status': 'ERROR - NO CODE GIVEN'}"))

# /rest/gps/([\w]+) - PUBLIC access with valid CODE - get list for google maps
class GPSRest(BaseHandler):
    def get(self, code):
        cuser = UserMgmt()
        user = cuser.get()
        withcode = code != ''
        if withcode:
            query = db.Query(MCBmember)
            query.filter('code =', code)
            mem = query.get()
            if mem:
                filterdays = datetime.datetime.now() - datetime.timedelta(days=197)
                query2 = db.Query(MCBmember)
                query2.filter('gpsdate > ', filterdays)
                query2.order('-gpsdate')
                gfangeni = query2.run(limit = 150, offset = 0)
                response = []
                for obj in gfangeni:
                    mesz = obj.gpsdate + datetime.timedelta(hours=1)
                    response.append({'pseudonym': obj.pseudonym, 'lat': obj.lat, 'lon': obj.lon, 'date': mesz.strftime('%d.%m.%y %H:%M')})
                self.render_jsonget(json.dumps(response))
            else:
                self.render_jsonget(json.dumps("{'status': 'ERROR - CODE WRONG'}"))
        else:
            self.render_jsonget(json.dumps("{'status': 'ERROR - NO CODE GIVEN'}"))

    #{
    # "gc": "AAA1234",
    # "lat": "47.23232332",
    # "lon": "7.23232332"
    #}
    def post(self, code):
        cuser = UserMgmt()
        user = cuser.get()
        try:
            gpsdata = json.loads(self.request.body)
        except:
            raise Exception("Do sin keini GPS Date cho - ich erwart json GPS struktur")
        #logging.info('mcbsujet.ch: rest POST with data: %s' % gpsdata)
        withcode = gpsdata["gc"] != ''
        if withcode:
            #logging.info('mcbsujet.ch: get with code: %s' % gpsdata["gc"])
            query = db.Query(MCBmember)
            query.filter('code =', gpsdata["gc"])
            mem = query.get()
            mem.lat = float(gpsdata["lat"])
            mem.lon = float(gpsdata["lon"])
            mem.gpsdate = datetime.datetime.now()
            mem.put()
            self.render_jsonget(json.dumps(0))
        else:
            #logging.info('mcbsujet.ch: gps rest set error')
            self.render_jsonget(json.dumps(1))
