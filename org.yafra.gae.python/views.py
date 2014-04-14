import jinja2
import os
import webapp2
import logging
import utils
import datetime
import re
from google.appengine.ext import db
from models import MCBpost, MCBmember
from usermgmt import UserMgmt

TEMPLATE_DIR = os.path.join(os.path.dirname(__file__), 'templates')
jinja_environment = \
    jinja2.Environment(loader=jinja2.FileSystemLoader(TEMPLATE_DIR))

#TODO: timezone handling
def datetimeformat(value, format='%d.%m.%Y %H:%M'):
    mesz = value + datetime.timedelta(hours=1)
    return mesz.strftime(format)

def dateformat(value, format='%d.%m.%Y'):
    mesz = value + datetime.timedelta(hours=1)
    return mesz.strftime(format)

def makeurl(value):
    r = re.compile(r"(http://[^ ]+)")
    return r.sub(r'<a href="\1">\1</a>', value)

jinja_environment.filters['dtform'] = datetimeformat
jinja_environment.filters['dform'] = dateformat
jinja_environment.filters['mkurl'] = makeurl

class BaseHandler(webapp2.RequestHandler):

    @webapp2.cached_property
    def jinja2(self):
        return jinja2.get_jinja2(app=self.app)

    def render_template(self, filename, template_values, **template_args):
        template = jinja_environment.get_template(filename)
        self.response.headers['Content-Type'] = 'text/html; charset=UTF-8'
        self.response.out.write(template.render(template_values))

    def render_jsonget(self, data):
        self.response.headers['Content-Type'] = 'application/json; charset=UTF-8'
        self.response.headers['Accept'] = 'application/json'
        self.request.charset='utf-8'
        self.response.out.write(data)

    def handle_exception(self, exception, debug_mode):
        #if debug_mode:
        #    webapp2.RequestHandler.handle_exception(self, exception, debug_mode)
        #    return
        x = self.request.url
        self.error(500)
        logging.exception(exception)
        msg = exception.args
        self.response.out.write(self.render_template('error.html', {'errormsg': msg, 'url': x.decode('utf-8')}))


# / -> index.html
class MainPage(BaseHandler):
    def get(self):
        cuser = UserMgmt()
        user = cuser.get()
        query = db.Query(MCBpost)
        query.order('-date')
        if user:
            query.filter('scope =', utils.privacy_public)
            query.filter('active =', True)
            query.filter('type =', utils.msg)
        else:
            query.filter('scope =', utils.privacy_public)
            query.filter('active =', True)
            query.filter('type =', utils.vers)
        comments = query.run(limit = 3, offset = 0)
        self.render_template('index.html', {'comments': comments, 'myself' : user})
        
# /search
class Search(BaseHandler):
    def post(self):
        searchtxt = self.request.get('fsearchtxt')
        return webapp2.redirect('/search/%s' % searchtxt)

    def get(self):
        cuser = UserMgmt()
        user = cuser.get()
        self.render_template('search.html', {'myself': user})

# /search/([\w]+)
class SearchStr(BaseHandler):
    def get(self, searchtxt):
        query = db.Query(MCBpost)
        query.order('post')
        res = query.run()
        matches = []
# TODO: search in gfangene and posts
        for r in res:
            post = r.post.upper()
            if post.find(searchtxt.upper()) != -1:
                matches.append(r)
        template_values = {}
        template_values.update({'results': matches})
        #logging.info('mcbsujet.ch: get - search %s', searchtxt)
        self.render_template('searchresults.html', template_values)

# /help
class HelpPage(BaseHandler):
    def get(self):
        cuser = UserMgmt()
        user = cuser.get()
        self.render_template('help.html', {'myself' : user})

class ErrorMsg(BaseHandler):
    def get(self, error=500, errormsg='An error occured - please try again or log an incident at xxxx'):
        self.error(error)
        self.render_template('error.html', {'errormsg' : errormsg})

class CH_tzinfo(datetime.tzinfo):
    """Implementation of the Pacific timezone."""
    def utcoffset(self, dt):
        return datetime.timedelta(hours=+1) + self.dst(dt)

    def _FirstSunday(self, dt):
        """First Sunday on or after dt."""
        return dt + datetime.timedelta(days=(6-dt.weekday()))

    def dst(self, dt):
        # 2 am on the second Sunday in March
        dst_start = self._FirstSunday(datetime.datetime(dt.year, 3, 8, 2))
        # 1 am on the first Sunday in November
        dst_end = self._FirstSunday(datetime.datetime(dt.year, 11, 1, 1))

        if dst_start <= dt.replace(tzinfo=None) < dst_end:
            return datetime.timedelta(hours=1)
        else:
            return datetime.timedelta(hours=0)
    def tzname(self, dt):
        return "MESZ"
