#!/bin/bash


CURRENT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"


# todo:
# check if dependencies are installed
# if not, install all dependencies



echo ""
echo "Setting environment variables: "
    # green text color
    tput setaf 2;
    export LENTIL_PATH=$CURRENT_DIR
    echo -e "\t LENTIL_PATH: " $LENTIL_PATH

    # add dependency packages environment variables
    export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH
    export PKG_CONFIG_PATH=/opt/X11/lib/pkgconfig/:$PKG_CONFIG_PATH
    echo -e "\t PKG_CONFIG_PATH: " $PKG_CONFIG_PATH
echo ""



# reset text formatting
tput sgr0

make