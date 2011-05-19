#!/bin/bash
appname=player
libname=lib$appname.so

libpath=src/lib
apppath=src/player

path=`dirname $0`

echo $@
echo $path

function makeLib {
   echo "compiling library"
   cd $libpath
   make
   cd ../..
}

function installLib {

  echo "installing the library"
  rm /usr/lib/$libname.1 /usr/lib/$libname.1.0
  cp  target/$libname /usr/lib
  ln -s /usr/lib/$libname /usr/lib/$libname.1
  ln -s /usr/lib/$libname /usr/lib/$libname.1.0
}

function makeApp {
  echo "compiling application"
  cd $apppath
  make
  cd ../..
}

function installApp {

  echo "installing the application"
  mkdir -p /usr/share/kde4/apps/$appname
  cp -R  data/* /usr/share/kde4/apps/$appname
  cp -R sql /usr/share/kde4/apps/$appname
  cp -R target/$appname /usr/bin
}


if [ $# -eq 0 ] 
then
  
  echo edo
  ./configure
  makeLib
  installLib
  makeApp
  installApp

elif [ $1 == 'lib' ]
then

  ./configure
  makeLib
  if [ "$2" == '-i' ]
  then
    installLib
  fi

elif [ $1 == 'app' ]
then

  ./configure
  makeApp
  if [ $2 == '-i' ]
  then
    installApp
  fi

fi

