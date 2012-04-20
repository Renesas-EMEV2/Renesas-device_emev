#!/bin/sh

ANDROID_DIR=$AOSP
WORK_DIR=$ANDROID_DIR
OBJ_DIR=$ANDROID_DIR

# Create Userland
echo ""
echo "-----------------------"
echo "- userland deployment -"
echo "-----------------------"

# cleanup
rm -f ${ANDROID_DIR}/tmp-android.tar.gz 
rm -f ${OBJ_DIR}/android-fs4.tar.gz
sudo rm -rf ${WORK_DIR}/android-fs

cd ${ANDROID_DIR}/out/target/product/emev/
cp ${ANDROID_DIR}/device/renesas/emev/initlogo.rle ./root/
tar zcf ${ANDROID_DIR}/tmp-android.tar.gz system data root

if [ ! -d ${WORK_DIR}/android-fs ] ; then
  cd ${WORK_DIR}
  mkdir android-fs
fi
cd ${WORK_DIR}/android-fs
tar zxf ${ANDROID_DIR}/tmp-android.tar.gz
mv data root
mv system root
mv root/* ./

# Copying builtin firmware
#cp -r ${ANDROID_DIR}/device/renesas/emev/firmware/* ./

rmdir root
chmod +r system/usr/keychars/*
sudo chown -R 1000:1000 ./
sudo tar zcf ${OBJ_DIR}/android-fs4.tar.gz ./
