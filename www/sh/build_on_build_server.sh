args=("$@")
OS=${args[0]} #windows/linux/osx
BUILD_SERVER=root@66.42.72.219
DATE="$( date +"%y%m%d-%H%M" )" && #need to make sure this is in UTC?
USER=testemail@gmail.com &&

if [ $OS -eq "windows" ]; then
   USER_BUILD_FOLDER=$DATE-$USER-windows &&
elif [ $OS -eq "linux" ]; then
   USER_BUILD_FOLDER=$DATE-$USER-linux &&
else
   USER_BUILD_FOLDER=$DATE-$USER-osx &&
fi

DOWNLOAD_DIR=/root/test_upload_folder &&
mkdir -p $DOWNLOAD_DIR &&

if [ $OS -eq "windows" ]; then
   ssh -t $BUILD_SERVER "cd lentil-build/lentil/pota/build/server && bash ./build_server_unix.sh .1001 $USER $USER_BUILD_FOLDER $DOWNLOAD_DIR" &&
elif [ $OS -eq "linux" ]; then
   ssh -t $BUILD_SERVER "cd lentil-build/lentil/pota/build/server && bash ./build_server_unix.sh .1001 $USER $USER_BUILD_FOLDER $DOWNLOAD_DIR" &&
elif [ $OS -eq "osx" ]; then
   ssh -t $BUILD_SERVER "cd lentil-build/lentil/pota/build/server && bash ./build_server_unix.sh .1001 $USER $USER_BUILD_FOLDER $DOWNLOAD_DIR" &&
fi


# pass the .zip back to the user
url=$DOWNLOAD_DIR/$USER_BUILD_FOLDER.zip
if [ ! -f $url ]; then
    echo "The .zip was not created!"
fi