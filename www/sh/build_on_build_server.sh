BUILD_SERVER=root@66.42.72.219
DATE="$( date +"%y%m%d-%H%M" )" && #need to make sure this is in UTC?
USER=testemail@gmail.com &&
USER_BUILD_FOLDER=$DATE-$USER &&
DOWNLOAD_DIR=/root/test_upload_folder &&

mkdir -p $DOWNLOAD_DIR &&

ssh -t $BUILD_SERVER "cd lentil-build/lentil/pota && bash ./build_server.sh .1001 $USER $USER_BUILD_FOLDER $DOWNLOAD_DIR" &&

# pass the .zip back to the user
url=$DOWNLOAD_DIR/$USER_BUILD_FOLDER.zip
if [ ! -f $url ]; then
    echo "The .zip was not created!"
fi