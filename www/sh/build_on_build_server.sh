BUILD_SERVER=root@66.42.72.219
DATE="$( date +"%y%m%d-%H%M" )" &&
USER=testemail@gmail.com &&
USER_BUILD_FOLDER=$DATE-$USER &&
DOWNLOAD_DIR = /root/test_upload_folder/$USER_BUILD_FOLDER &&

mkdir -p $DOWNLOAD_DIR/$USER_BUILD_FOLDER &&

ssh $BUILD_SERVER &&
cd lentil-build/lentil/pota &&
bash ./build_server.sh .1001.1002 $USER $USER_BUILD_FOLDER $DOWNLOAD_DIR && #note first dot in lens string is important!

# pass the .zip back to the user
url = $DOWNLOAD_DIR/$USER_BUILD_FOLDER.zip