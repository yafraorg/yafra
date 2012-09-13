#!/usr/bin/env python
'''

'''
import re
import sys

def scanlogfile(filename):
    fh = open(filename)
    j = 0
    for i in fh:
        j += 1
        err = re.search(r"error: ",i)
        crit = re.search(r"BUILD FAILED",i)
        fail = re.search(r"[Ff][Aa][Ii][Ll]",i)
        if err or crit or fail:
            print "error on line {0}".format(j)
            print "line content: {0}".format(i)
            # mail file, linenumber, error message
    fh.close()

if __name__ == "__main__":
    if len(sys.argv)<2:
        print "error no arg given"
    else:
        filename = sys.argv[1]
        if filename:
            print "start of scan on file {0}".format(filename)
            scanlogfile(filename)
    print "end of scan"
