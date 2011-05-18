#!/bin/bash
appname=player
libname=lib$appname.so

./configure

make

rm /usr/lib/$libname.1 /usr/lib/$libname.1.0

cp  target/$libname /usr/lib

sudo ln -s /usr/lib/$libname /usr/lib/$libname.1

sudo ln -s /usr/lib/$libname /usr/lib/$libname.1.0



mkdir -p /usr/share/kde4/apps/$appname

cp -R  data/* /usr/share/kde4/apps/$appname

cp -R sql /usr/share/kde4/apps/$appname

cp -R target/$appname /usr/bin
