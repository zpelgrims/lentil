#!/bin/bash
# server-setup-ubuntu.sh

# set timezone, should be equal between all build servers regardless of location
sudo timedatectl set-timezone UTC

# create home folder
mkdir ~/lentil-build/
export LENTIL_BUILD_HOME=~/lentil-build
mkdir ~/lentil-build/builds/
cd ~/lentil-build/

# install build essentials (make, gcc, ..)
sudo apt-get update
sudo apt install build-essential --yes

# download arnold sdk's
wget -O ~/lentil-build/arnold.zip https://www.dropbox.com/sh/rx57g4e3reamk3i/AAD5wLVnUQL1GEvDKv3MbbRfa?dl=1

# unzip arnold sdk's
sudo apt install unzip
sudo apt install zip
unzip ~/lentil-build/arnold.zip -d ~/lentil-build/arnold
rm -f ~/lentil-build/arnold.zip
export LENTIL_ARNOLD_SDKS=~/lentil-build/arnold

# clone lentil repo
git clone --recurse-submodules https://zpelgrims@github.com/zpelgrims/lentil.git

cd ~/lentil-build/lentil
mkdir ~/lentil-build/lentil/pota/bin