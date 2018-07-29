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
    # export PKG_CONFIG_PATH=/usr/local/Cellar/:$PKG_CONFIG_PATH
    # export PKG_CONFIG_PATH=/usr/local/Cellar/gtk+/2.24.31_1/lib/pkgconfig/:$PKG_CONFIG_PATH
    # export PKG_CONFIG_PATH=/usr/local/Cellar/pango/1.40.14/lib/pkgconfig/:$PKG_CONFIG_PATH
    # export PKG_CONFIG_PATH=/usr/local/Cellar/glib/2.54.2/lib/pkgconfig:$PKG_CONFIG_PATH
    # export PKG_CONFIG_PATH=/usr/local/Cellar/pcre/8.41/lib/pkgconfig/:$PKG_CONFIG_PATH
    # export PKG_CONFIG_PATH=/usr/local/Cellar/cairo/1.14.10/lib/pkgconfig/:$PKG_CONFIG_PATH
    # export PKG_CONFIG_PATH=/usr/local/Cellar/pixman/0.34.0_1/lib/pkgconfig/:$PKG_CONFIG_PATH
    export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH
    export PKG_CONFIG_PATH=/opt/X11/lib/pkgconfig/:$PKG_CONFIG_PATH
    echo -e "\t PKG_CONFIG_PATH: " $PKG_CONFIG_PATH
echo ""



# reset text formatting
tput sgr0

make