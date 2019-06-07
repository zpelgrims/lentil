# to test: ./build_on_build_server.sh osx testemail@gmail.com .1001

args=("$@")

DATE="$( date +"%y%m%d-%H%M" )" && #need to make sure this is in UTC?

# these three vars need to be passed from html
OS=${args[0]} # windows/linux/osx
USER=${args[1]} # username
LENSES=${args[2]} # .1001

if [ "$OS" == "windows" ]; then
   BUILD_SERVER=administrator@78.141.197.83
   USER_BUILD_FOLDER=$DATE-$USER-windows
elif [ "$OS" == "linux" ]; then
   BUILD_SERVER=root@66.42.72.219
   USER_BUILD_FOLDER=$DATE-$USER-linux
else
   BUILD_SERVER=Xcloud@185.90.39.34
   USER_BUILD_FOLDER=$DATE-$USER-osx
fi

DOWNLOAD_DIR=/root/test_upload_folder &&
mkdir -p $DOWNLOAD_DIR &&

if [ "$OS" == "windows" ]; then
   ssh -t $BUILD_SERVER "cd C:/lentil-build/lentil && git pull --recurse-submodules && cd pota/build/server && ./build_server_windows.bat $LENSES $USER $USER_BUILD_FOLDER $DOWNLOAD_DIR"
elif [ "$OS" == "linux" ]; then
   ssh -t $BUILD_SERVER "cd lentil-build/lentil && git pull --recurse-submodules && cd pota/build/server && bash ./build_server_linux.sh $LENSES $USER $USER_BUILD_FOLDER $DOWNLOAD_DIR"
else 
   ssh -t $BUILD_SERVER "cd lentil-build/lentil && git pull --recurse-submodules && cd pota/build/server && bash ./build_server_osx.sh $LENSES $USER $USER_BUILD_FOLDER $DOWNLOAD_DIR"
fi


# pass the .zip back to the user
url=$DOWNLOAD_DIR/$USER_BUILD_FOLDER.zip
if [ ! -f $url ]; then
    echo "The .zip was not created!"
fi