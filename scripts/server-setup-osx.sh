#!/bin/bash
# server-setup-osx.sh

# to launch: 
# wget -O server-setup-osx.sh https://raw.githubusercontent.com/zpelgrims/lentil/master/scripts/server-setup-osx.sh
# chmod 777 server-setup-osx.sh
# ./server-setup-osx.sh

# set timezone, should be equal between all build servers regardless of location
sudo ln -sf /usr/share/zoneinfo/UTC /etc/localtime

# create home folder
mkdir ~/lentil-build/
export LENTIL_BUILD_HOME=~/lentil-build
mkdir ~/lentil-build/builds/
cd ~/lentil-build/

# install package manager
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
# installing homebrew will launch an xcode cli install, which you need to accept in the gui...

brew install wget

# install build essentials (make, gcc, ..)
# wget -O install-osx-xcode-cli-no-gui.sh https://raw.githubusercontent.com/zpelgrims/lentil/master/scripts/install-osx-xcode-cli-no-gui.sh
# chmod 777 install-osx-xcode-cli-no-gui.sh
# ./install-osx-xcode-cli-no-gui.sh

# sudo apt-get update
# sudo apt install build-essential --yes

# download arnold sdk's
wget -O ~/lentil-build/arnold.zip https://www.dropbox.com/sh/rx57g4e3reamk3i/AAD5wLVnUQL1GEvDKv3MbbRfa?dl=1

# unzip arnold sdk's
brew install unzip
brew install zip
unzip ~/lentil-build/arnold.zip -d ~/lentil-build/arnold
rm -f ~/lentil-build/arnold.zip
export LENTIL_ARNOLD_SDKS=~/lentil-build/arnold

# clone lentil repo
git clone --recurse-submodules https://zpelgrims@github.com/zpelgrims/lentil.git

cd ~/lentil-build/lentil

# cleanup
rm -f ~/server-setup-osx.sh