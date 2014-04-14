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
@subject: utilities
@author: mwn

This module delivers mainly default values for the model
'''

# sujetflag
nehmeteil = 1
nehmenichtteil =2

# status of member
typepf = unicode("Pfyffer", 'utf-8')
typetam = unicode("Tambour", 'utf-8')
typevor = unicode("Vorträbler", 'utf-8')
typemaj = unicode("Dambuurmaioor", 'utf-8')

# post type
vers = 1
cmt = 2
msg = 3

# privacy gpx header definition
privacy_private = 1
privacy_public = 2


# INTERNAL PDF SUPPORT
class CreatePDF():
    def FooterPDF(self, canvas, doc):
        canvas.saveState()
        canvas.setFont('Times-Roman', 11)
        canvas.drawString(150, 20, "Copyright 2014 Märtzplatz Clique Basel 1923 - Stammverein")
        canvas.restoreState()

