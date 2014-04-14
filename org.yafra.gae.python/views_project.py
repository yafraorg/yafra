import webapp2
import logging
import utils
import datetime
from reportlab.lib import colors
from reportlab.lib.pagesizes import A4
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer, Image, Table, TableStyle
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.colors import red, black, navy, white, green
from google.appengine.ext import db
from models import MCBpost, MCBmember
from usermgmt import UserMgmt
from members import MemberMgmt
from views import BaseHandler
from utils import CreatePDF


# /zeedel
class ZettelPage(BaseHandler):
    def get(self):
        cuser = UserMgmt()
        user = cuser.get()

        qvers = db.Query(MCBpost)
        qvers.filter('scope =', utils.privacy_public)
        qvers.filter('type =', utils.vers)
        qvers.filter('active =', True)
        qvers.order('-date')
        verse = qvers.run()

        if user:
            qcmts = db.Query(MCBpost)
            qcmts.filter('scope =', utils.privacy_private)
            qcmts.filter('active =', True)
            qcmts.filter('type =', utils.vers)
            qcmts.order('-date')
            cmts = qcmts.run(limit = 250, offset = 0)
        else:
            cmts = None
        self.render_template('zettel.html', {'verse': verse, 'cmts': cmts, 'myself': user})

    def post(self):
        cuser = UserMgmt()
        user = cuser.get()
        withcode = self.request.get('fwithcode') != ''
        if withcode:
            code = self.request.get('fcode')
            myMember = MemberMgmt()
            mymem = myMember.checkcode(code)
            if mymem == None:
                logging.info('mcbsujet.ch: gfangene code page - wrong CODE given', code)
                raise Exception("Du hesch kai richtige CODE yygeh - jetzt wirsch erscht raecht gsuecht!!")
            n = MCBpost(post = self.request.get('fcmt'))
            n.postauthor = mymem
            n.postfromname = "%s" % (mymem.pseudonym)
            n.type = int(self.request.get('ftype'))
            n.scope = utils.privacy_private
            #if code == 'QESDF332':
            #if code == 'KDOW42':
            #    n.scope = utils.privacy_public
            n.active = True
            n.put()
            #logging.info('mcbsujet.ch: post created from code with id %s', n.key().id())
        elif user:
            mymem = cuser.ismember()
            if mymem == None:
                raise(Exception("Du bist noch keinem Member zugewiesen, bitte Martin per mail kontaktiere - webernissle(at)gmail.com"))
            n = MCBpost(post = self.request.get('fcmt'))
            n.postauthor = mymem
            n.postfromname = "%s" % (mymem.pseudonym)
            n.type = int(self.request.get('ftype'))
            if (user.admin):
                n.scope = utils.privacy_public
            else:
                n.scope = utils.privacy_private
            n.active = True
            n.put()
            #logging.info('mcbsujet.ch: post created with id %s', n.key().id())
        else:
            logging.info('mcbsujet.ch: no club for post - not saving')
        return webapp2.redirect('/zeedel')

# /zeedel/export
class ZettelExportPage(BaseHandler):
    def get(self):
        qvers = db.Query(MCBpost)
        qvers.filter('scope =', utils.privacy_public)
        qvers.filter('type =', utils.vers)
        qvers.filter('active =', True)
        qvers.order('-date')
        verse = qvers.run()

        story = []
        styles=getSampleStyleSheet()
        titleStyle = styles['Heading1']
        titleStyle.spaceAfter = 30
        gfangStyle = ParagraphStyle(name='gfangtext')
        gfangStyle.fontSize = 10
        gfangStyle.fontName = 'Courier'
        #gfangStyle.textColor=green
        #gfangStyle.backColor=black

        story.append(Paragraph("Gfangen im Netz", titleStyle))

        for v in verse:
            content = Paragraph(v.post, gfangStyle)
            story.append(content)
            story.append(Spacer(1, 12))
 
        self.response.headers['Content-Type'] = 'application/pdf'
        doc = SimpleDocTemplate(self.response.out,pagesize=A4)
        doc.rightMargin=150
        doc.leftMargin=150
        footer = CreatePDF()
        doc.build(story, onFirstPage=footer.FooterPDF, onLaterPages=footer.FooterPDF)
