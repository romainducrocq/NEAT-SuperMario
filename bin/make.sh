#!/bin/bash

OPT=$(dirname $(pwd))'/opt/'

sudo apt-get update
sudo apt-get install g++ cmake libsfml-dev valgrind libgtest-dev wmctrl

cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp -v lib/*.a /usr/lib

cd "${OPT}"'java'
sudo rm -rv *
wget -O jre-8uLatest-linux-x64.tar.gz https://javadl.oracle.com/webapps/download/AutoDL?BundleId=247127_10e8cce67c7843478f41411b7003171c
tar zxvf jre-8uLatest-linux-x64.tar.gz
rm -v jre-8uLatest-linux-x64.tar.gz
mv -v jre1.8* jre1.8.0_latest

cd "${OPT}"'nintaco'
if [ -d "Nintaco_bin_2020-05-01" ]; then rm -rv Nintaco_bin_2020-05-01; fi
unzip Nintaco_bin_2020-05-01.zip
