#!/bin/bash
cd /work/repos
cd openshift/jee
echo .
echo "openshift jee"
git status
git pull
cd ../nodejs
echo .
echo "openshift nodejs"
git status
git pull
cd ../python
echo .
echo "openshift python"
git status
git pull
cd ../../git/YafraLocalGit
echo .
echo "yafra"
git status
git pull
cd ../mcbsujet
echo .
echo "yafra - mcbsujet"
git status
git pull
cd ../ionictests
echo .
echo "yafra - ionictests"
git status
git pull
cd ../tire
echo .
echo "yafra - tire"
git status
git pull
