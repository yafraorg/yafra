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
@subject: set QR code per entity
@author: mwn

This module loads some test data in order to have a populated database and test functionality
'''
import webapp2
import logging
from PyQRNativeGAE import PyQRNative, PyQRNativeGAE
from google.appengine.ext import db
from models import MCBmember
from views import BaseHandler

# /cron/jobqrgen - GAE background task
class JobQRgen(BaseHandler):
       
    @db.transactional(xg=True)
    def updqrcode(self, memkey):
        m = db.get(memkey)
        url = "http://mcbsujet.appspot.com/gfangene/%s" % m.key().id()
        qr = PyQRNativeGAE.QRCode(PyQRNativeGAE.QRCode.get_type_for_string(url), PyQRNative.QRErrorCorrectLevel.L)
        qr.addData(url)
        qr.make()
        m.qrcode = db.Blob(qr.make_image())
        m.put()
        return
       
    def post(self): # should run at most 1/s
        logging.info('mcbsujet.ch: starting QR Code update')
        members = MCBmember.all(keys_only=True)
        members.filter("qrcode =", None)
        for m in members:
            self.updqrcode(m)
        logging.info('mcbsujet.ch: finished QR Code update')
