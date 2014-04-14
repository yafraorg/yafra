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
import json
import datetime
from google.appengine.ext import db
from google.appengine.ext import blobstore
from models import MCBfasnacht
from views import BaseHandler

# /rest/f
class FasnachtRest(BaseHandler):
    def get(self):
        query = db.Query(MCBfasnacht)
        query.filter('active =', True)
        query.order('-date')
# TODO: check on limit here - or provide page-ing
        imps = query.run(limit = 150, offset = 0)
        response = []
        for obj in imps:
            mesz = obj.date + datetime.timedelta(hours=1)
            response.append({'pseudonym': obj.fromname, 'post': obj.post, 'date': mesz.strftime('%d.%m.%y %H:%M'), 'scope': obj.scope, 'pict': obj.picturl, 'pict2': obj.picturl2})
        self.render_jsonget(json.dumps(response))

# /rest/fupl
class FasnachtUploadRest(BaseHandler):
    def get(self):
        upload_url = blobstore.create_upload_url('/fcupload')
        response = []
        response.append({'uploadurl': upload_url})
        self.render_jsonget(json.dumps({'uploadurl': upload_url}))
