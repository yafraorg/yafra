'''
Created on Jul 5, 2012
@brief pssys python client testcase
@author: mwn
'''
import sys
import socket
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
        self.window.connect("delete-event", Gtk.main_quit)
        self.window.show()
        self.host = self.builder.get_object("e_main_db")
        self.host.set_editable(True)
        Gtk.main()

    # CALLBACK
    # quit
    def on_window_destroy(self, widget, data=None):
        Gtk.main_quit()

    # CALLBACK
    # quit
    def on_mi_exit_activate(self, widget, data=None):
        Gtk.main_quit()

    # CALLBACK
    # open socket
    def on_mi_open_activate(self, widget, data=None):
        shost = self.host.get_text()
        if len(shost) == 0:
            shost = "localhost"
            self.host.set_text(shost)
        txtv = self.builder.get_object("textview1")
        txtbuf = txtv.get_buffer()
        txtbuf.set_text("starting ipc communication now")
        com = IPCclient()
        starti = txtbuf.get_start_iter()
        endi = txtbuf.get_end_iter()
        currbuf = txtbuf.get_text(starti, endi, False)
        txtbuf.set_text("{0}\nconnect to host {1}".format(currbuf, shost))
        com.IPCconnect(shost, 5001)
        starti = txtbuf.get_start_iter()
        endi = txtbuf.get_end_iter()
        currbuf = txtbuf.get_text(starti, endi, False)
        txtbuf.set_text("{0}\nconnected to localhost on 5001".format(currbuf))
        com.IPCwrite("0Hello from python")
        starti = txtbuf.get_start_iter()
        endi = txtbuf.get_end_iter()
        currbuf = txtbuf.get_text(starti, endi, False)
        txtbuf.set_text("{0}\nsend 0Hello from python".format(currbuf))
        com.IPCwrite("1")
        starti = txtbuf.get_start_iter()
        endi = txtbuf.get_end_iter()
        currbuf = txtbuf.get_text(starti, endi, False)
        txtbuf.set_text("{0}\nsend 1 (exit)".format(currbuf))

    # CALLBACK
    # quit
    def on_mi_about_activate(self, widget, data=None):
        tdbabout = about.TdbAbout()


class IPCclient:
    '''
    Communication client interface
    - connect
    - read
    - write
    '''

    def __init__(self, sock=None):
        if sock is None:
            self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        else:
            self.s = sock

    def IPCconnect(self, host, port):
        self.s.connect((host, port))

    def IPCwrite(self, msg):
        lenmsg = len(msg)
        lenlen = "%d\0      " % lenmsg
        self.swrite(lenlen[0:4], 4)
        self.swrite(msg, lenmsg)

    def swrite(self, msg, len):
        self.s.sendall(msg)

    def swriteb(self, msg, len):
        totalsent = 0
        while totalsent < len:
            sent = self.s.send(msg[totalsent:])
            if sent == 0:
                raise RuntimeError("socket connection broken")
            totalsent = totalsent + sent

    '''
    read 1) typs 2) len of buffer 3) buffer
    '''
    def IPCread(self, aLen):
        msg = ''
        while len(msg) < aLen:
            chunk = self.s.recv(aLen - len(msg))
            if chunk == '':
                raise RuntimeError("socket connection broken")
            msg = msg + chunk
        return msg


#-------------------------------------------------------------------------
#
# MAIN EXEC
#
if __name__ == '__main__':
    tdbmain = TdbMain()
    tdbmain.main()
    pass
