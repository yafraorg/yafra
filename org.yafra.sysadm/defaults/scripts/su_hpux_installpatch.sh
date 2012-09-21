#!/usr/bin/sh
#
# install a HP patch for HP-UX 10.X
#
# argument 1 is the patch name (only PXXX_9999 is needed without ending !)
#

# title
echo "yafra.org - HP-UX patch installer for PATCH: $1"
echo "copy patch now to /tmp and then installing it"
echo .
cp $1.depot /tmp/.
swinstall -x autoreboot=true -x match_target=true -s /tmp/$1.depot
rm /tmp/$1.depot
echo .
echo "done"
