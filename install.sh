#!/bin/bash
appname=player
libname=lib$appname.so

libpath=src/lib
apppath=src/player

path=`dirname $0`
old_path=`pwd`

function makeLib {   
   cd $libpath
   make
   cd - >/dev/null
}

function installLib {
  
  rm /usr/lib/$libname.1 /usr/lib/$libname.1.0 2>/dev/null
  cp  target/$libname /usr/lib
  ln -s /usr/lib/$libname /usr/lib/$libname.1
  ln -s /usr/lib/$libname /usr/lib/$libname.1.0
}

function makeApp {
  cd $apppath
  make
  cd - >/dev/null
}

function installApp {

  mkdir -p /usr/share/kde4/apps/$appname
  rsync -r --exclude='.*' data/ /usr/share/kde4/apps/$appname  
  cp -R target/$appname /usr/bin

  chown root /usr/bin/$appname
  chown -R root /usr/share/kde4/apps/$appname
  chmod -R 755 /usr/share/kde4/apps/$appname
}

if [ `whoami` != 'root' ]
then
  echo "installation need to be root" 1>&2
  exit 1
fi


cd $path

./configure
if [ $? -ne 0 ]
then
  echo "./configure error" 1>&2
  cd $old_path
  exit 1
fi

echo "compiling library"
makeLib
if [ $? -ne 0 ]
then
  echo "compiling library error" 1>&2
  cd $old_path
  exit 1
fi
  
echo "installing the library"
installLib

echo "compiling application"
makeApp
if [ $? -ne 0 ]
then
  echo "compiling application error" 1>&2
  cd $old_path
  exit 1
fi

echo "installing the application"
installApp

echo "done"

cd $old_path