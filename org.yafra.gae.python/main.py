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
@subject: main entry module
@author: mwn

This module is the main entry point of this application - dispatches all URLs - see app.yaml as well
'''
import webapp2
from views import MainPage, HelpPage, Search, SearchStr
from views_admin import MemberPage, MembersPage, UserPage, AdmUserPage, UsersPage, PostsPage, DeleteMem, DeleteUser, DeletePost, TogglePost, ExportMembersPage, ExportUsersPage, ExportPostsPage
from views_admin import LoginPage, SuperAdminPage, TaskLoadTestData, ExportAllPage, TaskQRgen, AdmFasnachtsPage, AdmFasnachtDel, AdmFasnachtToggle, AdmFasnachtExport, TogglePostScope, PostsUpd, AdmFasnachtUpd
from views_zettel import ZettelPage, ZettelExportPage
from views_fasnacht import FasnachtsPage, FasnachtAddImpPage, FasnachtUploadHandler, FasnachtsAllPage
from views_gfangene import GfangenePage, GfangeneDetPage, ExportGfangenePage, ExportGfangeniPage, ImageHandler, QRcode, GpsPage, GfangeneCodePage, GfangeneCodeWPage, GfangeneCodeXlsPage
from rest_posts import PostsRest, PostsMsgRest, PostsIntRest
from rest_gfangene import GfangeneRest, GfangeneCodeRest, GPSRest, GfangeneValidateCodeRest
from rest_fasnacht import FasnachtRest, FasnachtUploadRest
from job_loadtests import JobInitTest
from job_qrgen import JobQRgen

app = webapp2.WSGIApplication([
        ('/', MainPage), 
        ('/login', LoginPage),
        ('/_ah/login_required', LoginPage),
        ('/zeedel', ZettelPage),
        ('/zeedel/export', ZettelExportPage),
        ('/fasnacht', FasnachtsPage),
        ('/fasnachtalli', FasnachtsAllPage),
        ('/fc/([\w]+)', FasnachtAddImpPage),
        ('/fcupload', FasnachtUploadHandler),
        ('/gfangene', GfangenePage),
        ('/gfangene/([\d]+)', GfangeneDetPage),
        ('/gfangenepdf/([\d]+)', ExportGfangenePage),
        ('/gfangenipdf', ExportGfangeniPage),
        ('/gc/([\w]+)', GfangeneCodePage),
        ('/gcxls/([\w]+)', GfangeneCodeXlsPage),
        ('/gc', GfangeneCodeWPage),
        ('/pict', ImageHandler),
        ('/qrcode', QRcode),
        ('/gps', GpsPage),
        ('/search', Search),
        ('/search/([\w]+)', SearchStr),
        ('/member/([\d]+)', MemberPage),
        ('/member/export', ExportMembersPage),
        ('/user/([\d]+)', UserPage),
        ('/admin', SuperAdminPage),
        ('/admin/user', UsersPage),
        ('/admin/user/([\d]+)', AdmUserPage),
        ('/admin/deluser/([\d]+)', DeleteUser),
        ('/admin/exportuser', ExportUsersPage),
        ('/admin/member', MembersPage),
        ('/admin/delmem/([\d]+)', DeleteMem),
        ('/admin/post', PostsPage),
        ('/admin/delpost/([\d]+)', DeletePost),
        ('/admin/togglepost/([\d]+)', TogglePost),
        ('/admin/togglepostscope/([\d]+)', TogglePostScope),
        ('/admin/postupd', PostsUpd),
        ('/admin/exportpost', ExportPostsPage),
        ('/admin/imp', AdmFasnachtsPage),
        ('/admin/delimp/([\d]+)', AdmFasnachtDel),
        ('/admin/toggleimp/([\d]+)', AdmFasnachtToggle),
        ('/admin/impupd', AdmFasnachtUpd),
        ('/admin/exportimp', AdmFasnachtExport),
        ('/admin/export', ExportAllPage),
        ('/admin/testdatamcbgugug', TaskLoadTestData),
        ('/admin/qrgen', TaskQRgen),
        ('/help', HelpPage),
        ('/cron/jobinittests', JobInitTest),
        ('/cron/jobqrgen', JobQRgen),
        ('/rest/f', FasnachtRest),
        ('/rest/fupl', FasnachtUploadRest),
        ('/rest/g', GfangeneRest),
        ('/rest/gc/([\w]+)', GfangeneCodeRest),
        ('/rest/gcvalid/([\w]+)', GfangeneValidateCodeRest),
        ('/rest/gps/([\w]+)', GPSRest),
        ('/rest/msg/([\w]+)', PostsMsgRest),
        ('/rest/postsint/([\w]+)', PostsIntRest),
        ('/rest/posts', PostsRest)
        ],
        debug=True)
