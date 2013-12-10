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
from views import MainPage, HelpPage
from views_community import Search, Community
from views_club import ClubAdminPage, ClubEmptyPage, ClubAdminEmptyPage, ClubPage, ClubAddmembersPage, ClubGPSPage, ExportMembersPage
from views_member import MemberPage, MemberStartPage, MemberReqPage
from views_admin import LoginPage, Settings
from views_super import SuperAdminPage, SuperClubAdminPage, DeleteClub, TaskLoadTestData, TaskUpdMemlist, TaskPurgeData
from views_event import EventPage
from views_route import RoutePage
from views_plan import PlanPage, ExportPlanPage, PlanAddPage
from views_mygps import MygpsPage
from job_loadtests import JobInitTest
from job_updatememof import JobUpdMemOf
from job_purgedata import JobPurgeData

app = webapp2.WSGIApplication([
        ('/', MainPage), 
        ('/login', LoginPage),
        ('/_ah/login_required', LoginPage),
        ('/help', HelpPage),
        ('/community', Community),
        ('/club', ClubEmptyPage),
        ('/club/([\d]+)', ClubPage),
        ('/clubmap/([\d]+)', ClubGPSPage),
        ('/clubxls/([\d]+)', ExportMembersPage),
        ('/clubadmin', ClubAdminEmptyPage),
        ('/clubadmin/([\d]+)', ClubAdminPage),
        ('/clubaddmembers/([\d]+)', ClubAddmembersPage),
        ('/clubaddmembers', ClubAddmembersPage),
        ('/member', MemberStartPage),
        ('/member/([\d]+)', MemberPage),
        ('/member/req/([\d]+)', MemberReqPage),
        ('/event', EventPage),
        ('/route', RoutePage),
        ('/plan', PlanPage),
        ('/plan/new/([\d]+)', PlanAddPage),
        ('/planpdf/([\d]+)', ExportPlanPage),
        ('/mygps', MygpsPage),
        ('/settings', Settings),
        ('/settingsexport', Settings),
        ('/search', Search),
        ('/search/([\w]+)', Search),
        ('/super', SuperAdminPage),
        ('/super/club', SuperClubAdminPage),
        ('/super/testdata', TaskLoadTestData),
        ('/super/purgedata', TaskPurgeData),
        ('/super/updmemlist', TaskUpdMemlist),
        ('/delclub/([\d]+)', DeleteClub),
        ('/cron/jobupdmemof', JobUpdMemOf),
        ('/cron/jobpurgedata', JobPurgeData),
        ('/cron/jobinittests', JobInitTest)
        ],
        debug=True)
