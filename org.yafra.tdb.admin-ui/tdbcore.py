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
@subject: core tdb handling (globdata, labels, start/stop, ...)
@author: mwn
'''

import sys
import struct
import config
import tdbglobal
import commtdb
from ctypes import *

bst = None
lang = "english"
user = None

def TDBinit(ahost):
    global bst
    global lang
    global user
    user = "mwn"
    # TODO: read mpprofil first
    commtdb.TDBconnect(ahost, config.SERVERPORT)
    #create first  init msg globstat
    tdbglobal.tdblogdebug("send 1st comm now (globprof)")
    header = struct.pack('@BBBBB', 0x00, 0x10, 0x00, 0x00, 0x00)
    globprof = struct.pack(config.GLOBPROFFMT, ahost, user, user, ahost, ahost)
    commtdb.TDBwrite(header, globprof, config.GLOBPROFLEN)
    retmsg = commtdb.TDBread()
    tdbglobal.tdblogdebug("1st: len of return message {0}".format(len(retmsg)))
    if len(retmsg) > config.GLOBDATALEN:
        colorslen = len(retmsg) - config.GLOBDATALEN
        msgunpack = "{0}{1}s".format(config.GLOBDATAFMT, colorslen)
        rglobdata = struct.unpack(msgunpack, retmsg)
        bst = rglobdata[0]
        lang = rglobdata[1]
        colorlist = rglobdata[13]
        colors = colorlist.split()
        tdbglobal.tdblogdebug("1st: got booking office {0} and first color {1}".format(bst, colors))
    else:
        rglobdata = struct.unpack(config.GLOBDATAFMT, retmsg)
        bst = rglobdata[0]
        tdbglobal.tdblogdebug("1st: got booking office {0} with NO colors".format(bst))

    #create second call to receive labels
    tdbglobal.tdblogdebug("send 2nd comm now (LABELS)")
    header = struct.pack('@BBBBB', 0x00, 0x10, 0x23, 0x00, 0x00)
    msg = struct.pack('@3s', str(config.LABELPRGID))
    commtdb.TDBwrite(header, msg, len(msg))
    retmsg = commtdb.TDBread()
    tdbglobal.tdblogdebug("2nd: len of return message {0}".format(len(retmsg)))
    labels = retmsg.split()
    #print repr(retmsg)


def TDBlabelinit():
    pass

def TDBquit():
    tdbglobal.tdblogdebug("send quit now")
    header = struct.pack('@BBBBB', 0x00, 0x10, 0x22, 0x00, 0x00)
    msg = struct.pack('@2s', 'OK')
    commtdb.TDBwrite(header, msg, len(msg))
    tdbglobal.tdblogdebug("send quit to server done")

'''
structures
bezlen 1024
userlen 128
pwdlen 20
'''

'''
    /* global profile */
    typedef struct {
        char   database[_CHAR200+1];
        char   user[_USERLEN+1];
        char   password[_PWDLEN+1];
        char   hostname[_CHAR200+1];
        char   displayname[_CHAR30+1];
    } MP_GLOBALPROFIL;
'''
class MP_GLOBALPROFIL(Structure):
   _fields_ = [("database", c_char),
               ("user", c_char),
               ("password", c_char),
               ("hostname", c_char),
               ("displayname", c_char)]

'''
    /* GUI global mask values */
    typedef struct {
        char   bchst[_BEZLEN];
        char   sprache[_BEZLEN];
        char   land[_BEZLEN];
        char   dltt[_BEZLEN];
        char   dlt[_BEZLEN];
        char   kat[_BEZLEN];
        char   dlat[_BEZLEN];
        char   dlnt[_BEZLEN];
        char   saison[_BEZLEN];
        char   programm[_BEZLEN];
        char   a_zeit[_BEZLEN];
        char   e_zeit[_BEZLEN];
        char   p_range[_BEZLEN];
    } GLOBDATA;
'''
class GLOBDATA(Structure):
   _fields_ = [("database", c_char),
               ("user", c_char),
               ("password", c_char),
               ("hostname", c_char),
               ("displayname", c_char)]

'''
    /* colortab for GUI - maps KATEGORIE with a color */
    typedef struct {
        int KAT_ID;
        int COL_IDX;
    } COLORTAB;
'''
class COLORTAB(Structure):
   _fields_ = [("database", c_char),
               ("user", c_char),
               ("password", c_char),
               ("hostname", c_char),
               ("displayname", c_char)]
