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
@subject: utilities
@author: mwn

This module delivers user handling - it depends on the federated google login
'''
import logging
import datetime
from google.appengine.api import users
from google.appengine.ext import db
from models import MCBuser, MCBmember

#         'Facebook'  : 'http://facebook-openid.appspot.com/',


class UserMgmt():

    providers = {
        'Google'    : 'https://www.google.com/accounts/o8/id',
        'Flickr'    : 'flickr.com',
        'Yahoo'     : 'yahoo.com',
        'AOL'       : 'aol.com',
        'MyOpenID'  : 'myopenid.com',
        'Steam'     : 'http://steamcommunity.com/openid'
        # add more here
    }

    def get(self):
        user = users.get_current_user()
        if user:
            logging.info("mcbsujet.ch: User %s", user.nickname())
            query = MCBuser.all()
            query.filter('provider =', user.federated_provider())
            query.filter('name =', user.nickname())
            dbuser = query.get()
            if dbuser:
                logging.info("mcbsujet.ch: User already registered %s", dbuser.name)
            else:
                logging.info("mcbsujet.ch: User not yet registered - do register now")
                dbuser = self.newuser(user.email(), user.nickname(), user.federated_provider())
            return dbuser
        else:
            logging.info("mcbsujet.ch: NO User - register")
            return None

    def getid(self):
        user = users.get_current_user()
        if user:
            logging.info("mcbsujet.ch: User %s", user.email())
            query = MCBuser.all(keys_only=True)
            query.filter('provider =', user.federated_provider())
            query.filter('name =', user.nickname())
            dbuser = query.get()
            if dbuser:
                logging.info("mcbsujet.ch: got id")
                return(dbuser)
            else:
                logging.info("diniclique.ch: get id - no ID found")
                return None
        else:
            return None

    def ismember(self):
        user = users.get_current_user()
        if user:
            logging.info("mcbsujet.ch: User %s", user.federated_provider())
            query = MCBuser.all()
            query.filter('provider =', user.federated_provider())
            query.filter('name =', user.nickname())
            dbuser = query.get()
            if dbuser:
                logging.info("mcbsujet.ch: get id with %s", dbuser.email)
                for m in dbuser.memof:
                    return(m)
                return None
            else:
                logging.info("diniclique.ch: get id - no ID found")
                return None
        else:
            return None



    def getloginlist(self):
        urllist = list()
        for name, uri in self.providers.items():
            urllist.append(([name, users.create_login_url(federated_identity=uri)]))
        return urllist
    
    def getlogouturl(self):
        return users.create_logout_url("/")
    
    def newuser(self, aemail, aname, aprovider):
        n = MCBuser(email = aemail, name = aname, provider = aprovider)
        n.active = True
        n.linked = False
        n.dateofreg = datetime.datetime.now()
        n.admin = False
        if users.is_current_user_admin():
            logging.info("mcbsujet.ch: User is ADMIN")
            n.admin=True
        n.put()
        dbuser = n
        return dbuser
