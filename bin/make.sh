#!/bin/bash

BIN=$(pwd)

sudo apt-get update
sudo apt-get install g++ cmake valgrind libgtest-dev

cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp -v lib/*.a /usr/lib

cd "${BIN}"'/java'
sudo rm -rv *
wget -O jre-8uLatest-linux-x64.tar.gz https://javadl.oracle.com/webapps/download/AutoDL?BundleId=247127_10e8cce67c7843478f41411b7003171c
tar zxvf jre-8uLatest-linux-x64.tar.gz
rm -v jre-8uLatest-linux-x64.tar.gz
mv -v jre1.8* jre1.8.0_latest

cd "${BIN}"'/nintaco'
rm -rv *
mkdir -p Nintaco_bin_2020-05-01
cd Nintaco_bin_2020-05-01
wget https://nintaco.com/Nintaco_bin_2020-05-01.zip
unzip Nintaco_bin_2020-05-01.zip
rm -v Nintaco_bin_2020-05-01.zip
