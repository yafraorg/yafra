#
# socket server
#
#from ctypes import *
import struct
import sys
import socket
import config

sock = None
header = None
connected = None

'''
Communication client interface
comm 1) typs 2) len of buffer 3) buffer
'''

def TDBconnect(host=None, port=None):
    global sock
    global connected
    if connected is None:
        if host is None:
            host = config.SERVERNAME
        if port is None:
            port = config.SERVERPORT
        if sock is None:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((host, port))
        connected = True

def TDBwrite(aheader, amsg, alen):
    global connected
    global header
    if connected is None:
        return
    header = aheader
    IPCwrite(aheader)
    bodylen = struct.pack('@11s', str(alen))
    IPCwrite(bodylen)
    IPCwrite(amsg)

def TDBread():
    global connected
    global header
    if connected is None:
        return
    #print " debug tdb read"
    header = IPCread(config.HEADSIZE)
    #print repr(readheader)
    rawlen = IPCread(config.LENSIZE)
    #print repr(rawlen)
    len = rawlen.split('\x00', 1)
    #print len
    #print int(len[0])
    msg = IPCread(int(len[0]))
    return msg

def IPCwrite(msg):
    global sock
    sock.sendall(msg)

def IPCread(aLen):
    global sock
    msg = ''
    while len(msg) < aLen:
        chunk = sock.recv(aLen - len(msg))
        if chunk == '':
            raise RuntimeError("socket connection broken")
        msg = msg + chunk
    return msg

