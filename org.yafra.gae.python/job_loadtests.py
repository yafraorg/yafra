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
@subject: loading test data
@author: mwn

This module loads some test data in order to have a populated database and test functionality
'''
import webapp2
import logging
import utils
from datetime import datetime
from google.appengine.ext import db
from models import MCBpost, MCBmember
from views import BaseHandler

# /cron/jobinittests - GAE background task
class JobInitTest(BaseHandler):
       
    @db.transactional(xg=True)
    def loadlinkedmember(self):
        m = MCBmember(name = 'Weber Nissle')
        m.prename = 'Martin'
        m.pseudonym = 'Web'
        m.strof = 'Gullag 10 Joor'
        m.steckbrief = 'Het heimlich e Bier drunke'
        m.cmt = 'So ne saich'
        m.email = 'test@example.com'
        m.mobil = '+41792223344'
        m.type = utils.typevor
        m.sujetflag = utils.nehmeteil
        m.section = 'Stammverein'
        m.active = True
        m.code = 'QESDF332'
        m.lat = float(47.557421)
        m.lon = float(7.592573)
        m.gpsdate = datetime.now()
        m.put()
        return m
       
    @db.transactional(xg=True)
    def loadmembers(self, i, typ):
        m = MCBmember(name = 'TEST Muster %d' % (i))
        m.prename = 'Hans'
        m.pseudonym = 'Test Pseudo %d' % (i)
        m.adr = 'Heimadresse 11'
        m.strof = 'Strof'
        m.steckbrief = 'Steckbrief'
        m.cmt = 'Kommentar'
        m.email = 'info%d@yafra.org' % (i)
        m.mobil = '+41792223344'
        m.sujetflag = utils.nehmeteil
        m.section = 'Stammverein'
        m.type = typ
        m.active = True
        m.code = 'QESDF332%d' % (i)
        m.lat = float(47.557421 + ((i+1)*0.1))
        m.lon = float(7.592573)
        m.gpsdate = datetime.now()
        m.put()
        return m
        
    @db.transactional(xg=True)
    def loadposts(self, m, i, j):
        post = MCBpost(postauthor = m)
        post.postfromname = "%s %s" % (m.prename, m.name)
        post.post = 'TEST Versli %d' % j
        post.date = datetime.now()
        post.scope = utils.privacy_public
        post.type = utils.vers
        post.active = True
        post.put()
        
    @db.transactional(xg=True)
    def loadcomment(self, m, i, j):
        post = MCBpost(postauthor = m)
        post.postfromname = "%s %s" % (m.prename, m.name)
        post.post = 'TEST Kommentar %d' % j
        post.date = datetime.now()
        post.scope = utils.privacy_public
        post.type = utils.cmt
        post.active = True
        post.put()
        
    @db.transactional(xg=True)
    def loadmsg(self, m, i, j):
        post = MCBpost(postauthor = m)
        post.postfromname = "%s %s" % (m.prename, m.name)
        post.post = 'TEST Maeldige %d' % j
        post.date = datetime.now()
        post.scope = utils.privacy_public
        post.type = utils.msg
        post.active = True
        post.put()
 
    def post(self): # should run at most 1/s
        logging.info('mcbsujet.ch: starting with test data population')
        cntdambuure = 9
        cntgfang = 3
        cntmem = 5
        i = 0
        while i < cntdambuure:
            m = self.loadmembers(i, utils.typetam)
            j = 0
            while j < cntmem:
                self.loadposts(m, i, j)
                #self.loadcomment(m, i, j)
                self.loadmsg(m, i, j)
                j += 1
            i += 1
        self.loadlinkedmember()

        # create pfyffer entry
        i = 0
        while i < cntgfang:
            m = self.loadmembers(i, utils.typepf)
            i += 1

        # create vortrab entry
        i = 0
        while i < cntgfang:
            m = self.loadmembers(i, utils.typevor)
            i += 1

        # create dambuurmajoor entry
        m = self.loadmembers(0, utils.typemaj)

        logging.info('mcbsujet.ch: finished with test data population')
