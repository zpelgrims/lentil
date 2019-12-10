#!/bin/bash

# should be called like ". ./build.sh"

CURRENT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"

echo ""
echo "Setting environment variables: "
    # green text color
    tput setaf 2;
    export LENTIL_PATH=$CURRENT_DIR
    echo -e "\t LENTIL_PATH: " $LENTIL_PATH

    # add dependency packages environment variables
    #export PKG_CONFIG_PATH=/usr/lib64/pkgconfig/:$PKG_CONFIG_PATH
    export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig/:$PKG_CONFIG_PATH
    echo -e "\t PKG_CONFIG_PATH: " $PKG_CONFIG_PATH
echo ""



# reset text formatting
tput sgr0

make -j 16