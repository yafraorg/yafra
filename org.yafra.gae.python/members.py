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
@subject: member functions
@author: mwn

This module delivers user handling - it depends on the federated google login
'''
import logging
import datetime
from google.appengine.api import users
from google.appengine.ext import db
from models import MCBuser, MCBmember

class MemberMgmt():

    def checkcode(self, code):
        query = db.Query(MCBmember)
        query.filter('code =', code)
        mem = query.get()
        if mem:
            return mem
        else:
            return None

#class MemberExport():