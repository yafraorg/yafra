'''
Created on Jul 5, 2012

@author: mwn
'''
import sys
import logging

log = None
tdbcom = None

def tdbloginit():
    global log
    FORMAT = "%(asctime)-15s %(message)s"
    logging.basicConfig(format=FORMAT)
    if log is None:
        log = logging.getLogger('tdbclient')
        log.setLevel("DEBUG")

def tdblogdebug(msg):
    global log
    log.debug("TDB DEBUG: %s", msg)

def tdblogerror(msg):
    global log
    log.error("TDB ERROR: %s", msg)