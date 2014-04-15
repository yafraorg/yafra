'''
  Copyright 2002 yafra.org

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

Created on Jul 6, 2012
@subject: about box
@author: mwn
'''
from gi.repository import Gtk

class TdbAbout(Gtk.Dialog):
    '''
    about dialog box
    '''


    def __init__(self):
        '''
        Constructor
        '''
        self.builder = Gtk.Builder()
        self.builder.add_from_file("about.glade") 
        #except:
        #    print("Failed to load UI XML file: tdb.glade")
        #    sys.exit(1)
            
        # get the widgets which will be referenced in callbacks
        self.tdb_about = self.builder.get_object("tdb_about")
        self.aboutinfo = self.builder.get_object("l_rtinfo")
        self.aboutinfo.set_text("Version 1.0A1")
       
        # connect signals
        self.builder.connect_signals(self)
        self.tdb_about.show()

    # When our window is destroyed, we want to break out of the GTK main loop. 
    # We do this by calling gtk_main_quit(). We could have also just specified 
    # gtk_main_quit as the handler in Glade!
    def on_b_about_close_clicked(self, widget, data=None):
        self.tdb_about.hide()
