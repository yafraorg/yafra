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
from google.appengine.ext import db
from google.appengine.api import users
from models import MCBpost, MCBmember
from usermgmt import UserMgmt
from views import BaseHandler

# /rest/posts
class PostsRest(BaseHandler):
    def get(self):
        cuser = UserMgmt()
        user = cuser.get()
        if user != None:
            logging.info('mcbsujet.ch: rest via app - login ? %s' % user.name)
        else:
            logging.info('mcbsujet.ch: rest via app - NO login')

        query = db.Query(MCBpost)
        query.filter('scope =', utils.privacy_public)
        query.filter('active =', True)
        query.filter('type =', utils.vers)
        query.order('-date')
        comments = query.run(limit = 150, offset = 0)
        response = []
        for obj in comments:
            response.append({'post': obj.post, 'date': obj.date.strftime('%d.%m.%y %H:%M'), 'postfromname': obj.postfromname})
        self.render_jsonget(json.dumps(response))

    #{
    # "gc": "AAA1234",
    # "post": "Text",
    # "scope": "1"
    #}
    def post(self):
        cuser = UserMgmt()
        user = cuser.get()
        try:
            post_data = json.loads(self.request.body)
        except:
            raise Exception("Do sin keini Date cho - ich erwart json post struktur")
        #logging.info('mcbsujet.ch: rest POST with data: %s' % post_data)
        withcode = post_data["gc"] != ''
        if withcode:
            # logging.info('mcbsujet.ch: get with code: %s' % post_data["gc"])
            query = db.Query(MCBmember)
            query.filter('code =', post_data["gc"])
            mem = query.get()
            if mem:
                n = MCBpost()
                n.postauthor = mem
                n.post = post_data["post"]
                n.postfromname = "%s" % (mem.pseudonym)
                n.type = utils.vers
                if (int(post_data["scope"]) == 1):
                    n.scope = utils.privacy_public
                else:
                    n.scope = utils.privacy_private
                n.active = True
                n.put()
                self.render_jsonget(json.dumps(0))
                #logging.info('mcbsujet.ch: post post OK')
            else:
                self.render_jsonget(json.dumps("{'status': 'ERROR - CODE WRONG'}"))
                #logging.info('mcbsujet.ch: post post ERROR CODE WRONG')
        else:
            self.render_jsonget(json.dumps("{'status': 'ERROR - NO CODE GIVEN'}"))
            #logging.info('mcbsujet.ch: post post ERROR NO CODE')


# /rest/msg/([\w]+) - public with CODE - show all internal messages
class PostsMsgRest(BaseHandler):
    def get(self, code):
        cuser = UserMgmt()
        user = cuser.get()
        withcode = code != ''
        if withcode:
            query = db.Query(MCBmember)
            query.filter('code =', code)
            mem = query.get()
            #logging.info('mcbsujet.ch: post get messages with CODE')
            if mem:
                query = db.Query(MCBpost)
                query.filter('active =', True)
                query.filter('type =', utils.msg)
                query.filter('active =', True)
                query.order('-date')
                comments = query.run(limit = 25, offset = 0)
                response = []
                for obj in comments:
                    response.append({'post': obj.post, 'date': obj.date.strftime('%d.%m.'), 'postfromname': obj.postfromname})
                self.render_jsonget(json.dumps(response))
            else:
                response = []
                response.append({'post': 'FEHLER: die CODE stimmt nid', 'date': 'ACHTUNG!', 'postfromname': 'mcbsujet server'})
                self.render_jsonget(json.dumps(response))
                #logging.info('mcbsujet.ch: post post ERROR CODE WRONG')
        else:
            logging.info('mcbsujet.ch: post post ERROR NO CODE')

# /rest/postsint/([\w]+) - public with CODE - show all internal posts (not yet reviewed)
class PostsIntRest(BaseHandler):
    def get(self, code):
        cuser = UserMgmt()
        user = cuser.get()
        withcode = code != ''
        if withcode:
            query = db.Query(MCBmember)
            query.filter('code =', code)
            mem = query.get()
            #logging.info('mcbsujet.ch: post get messages with CODE')
            if mem:
                query = db.Query(MCBpost)
                query.filter('scope =', utils.privacy_private)
                query.filter('type =', utils.vers)
                query.filter('active =', True)
                query.order('-date')
                comments = query.run(limit = 100, offset = 0)
                response = []
                for obj in comments:
                    response.append({'post': obj.post, 'date': obj.date.strftime('%d.%m.'), 'postfromname': obj.postfromname})
                self.render_jsonget(json.dumps(response))
            else:
                response = []
                response.append({'post': 'FEHLER: die CODE stimmt nid', 'date': 'ACHTUNG!', 'postfromname': 'mcbsujet server'})
                self.render_jsonget(json.dumps(response))
                #logging.info('mcbsujet.ch: post post ERROR CODE WRONG')
        else:
            logging.info('mcbsujet.ch: post post ERROR NO CODE')
