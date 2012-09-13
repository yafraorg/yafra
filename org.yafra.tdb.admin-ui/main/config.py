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
@subject: tdb configuration values used by all other modules
@author: mwn
'''
LENSIZE = 11
HEADSIZE = 5
SERVERNAME = "localhost"
SERVERPORT = 5000
LABELPRGID = 181

'''
tdb data structures definition and length
see mpobjvar.h mpstrlen.h
'''
GLOBDATAFMT = "@1024s1024s1024s1024s1024s1024s1024s1024s1024s1024s1024s1024s1024s"
GLOBDATALEN = 13*1024
GLOBPROFFMT = "@201s129s21s201s31s"
GLOBPROFLEN = 201+129+21+201+31
