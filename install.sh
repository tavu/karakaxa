#!/bin/bash
appname=player
libname=lib$appname.so

./configure

make

mkdir -p /usr/share/kde4/apps/$appname

cp -R  data/* /usr/share/kde4/apps/$appname

cp -R target/$appname /usr/bin

cp  target/$libname /usr/lib

sudo ln -s /usr/lib/$libname /usr/lib/$libname.1

sudo ln -s /usr/lib/$libname /usr/lib/$libname.1.0