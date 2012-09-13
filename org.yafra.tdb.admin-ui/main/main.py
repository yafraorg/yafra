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

Created on Jul 5, 2012
@subject: main gui entry point
@author: mwn
'''
import sys
import struct
import about
import config
import tdbcore
import commtdb
import tdbglobal
from gi.repository import Gtk, Gio

class TdbMain:
 
    # We use the initialization of the TutorialTextEditor class to establish
    # references to the widgets we'll need to work with in the callbacks for
    # various signals. This is done using the XML file we created with Glade    
    def __init__(self):
        # Default values
        self.filename = None
        
        # use GtkBuilder to build our interface from the XML file 
        #try:
        self.builder = Gtk.Builder()
        self.builder.add_from_file("main.glade") 
        #except:
        #    print("Failed to load UI XML file: tdb.glade")
        #    sys.exit(1)
            
        # get the widgets which will be referenced in callbacks
        self.window = self.builder.get_object("tdb_main")

        # connect signals
        self.builder.connect_signals(self)

    # Run main application window
    def main(self):
        tdbglobal.tdblogdebug("start gtk main loop")
        self.window.connect("delete-event", Gtk.main_quit)
        self.host = self.builder.get_object("e_main_db")
        self.host.set_text(config.SERVERNAME)
        self.window.show()
        Gtk.main()

    # CALLBACK
    # quit
    def on_window_destroy(self, widget, data=None):
        tdbglobal.tdblogdebug("exit client now")
        tdbcore.TDBquit()
        Gtk.main_quit()

    # CALLBACK
    # quit
    def on_mi_exit_activate(self, widget, data=None):
        tdbglobal.tdblogdebug("exit client now")
        tdbcore.TDBquit()
        Gtk.main_quit()

    # CALLBACK
    # connect
    def on_mi_connect_activate(self, widget, data=None):
        tdbglobal.tdblogdebug("start connection")
        shost = self.host.get_text()
        tdbcore.TDBinit(shost)
        self.mainlang = self.builder.get_object("e_main_lang")
        self.mainlang.set_text(tdbcore.lang)
        self.mainuser = self.builder.get_object("e_main_user")
        self.mainuser.set_text(tdbcore.user)
        self.mainbst = self.builder.get_object("e_main_bst")
        self.mainbst.set_text(tdbcore.bst)

        

    # CALLBACK
    # connect as
    def on_mi_connectas_activate(self, widget, data=None):
        tdbglobal.tdblogdebug("start connection")
        shost = self.host.get_text()
        tdbcore.TDBinit(shost)

    # CALLBACK
    # search offerings
    def on_mi_search_activate(self, widget, data=None):
        pass

    # CALLBACK
    # book
    def on_mi_book_activate(self, widget, data=None):
        pass
 
    # CALLBACK
    # manage a booking
    def on_mi_bookmanage_activate(self, widget, data=None):
        pass
   
    # CALLBACK
    # abouut
    def on_mi_about_activate(self, widget, data=None):
        tdbglobal.tdblogdebug("start about dialog")
        tdbabout = about.TdbAbout()

#-------------------------------------------------------------------------
#
# MAIN EXEC
#
if __name__ == '__main__':
    tdbglobal.tdbloginit()
    tdbglobal.tdblogdebug("start python client")
    tdbmain = TdbMain()
    tdbmain.main()
    pass
