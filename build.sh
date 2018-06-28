#!/bin/bash

# todo:
# install all dependencies


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

echo "PKG_CONFIG_PATH: " $PKG_CONFIG_PATH

make