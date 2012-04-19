#!/bin/sh

ANDROID_DIR=$AOSP
WORK_DIR=$ANDROID_DIR
OBJ_DIR=$ANDROID_DIR

#Create Userland
echo ""
echo "-----------------------"
echo "- userland deployment -"
echo "-----------------------"
cd  ${ANDROID_DIR}
rm -f tmp-android.tar.gz android-fs.tar.gz
sudo rm -rf android-fs/
cd ${ANDROID_DIR}/out/target/product/emev/
cp ${ANDROID_DIR}/device/renesas/emev/initlogo.rle ./system/
tar zcf ${ANDROID_DIR}/tmp-android.tar.gz system data root
cd ${WORK_DIR}
if [ ! -d ${WORK_DIR}/android-fs ] ; then
mkdir android-fs
fi
cd android-fs
tar zxf ${ANDROID_DIR}/tmp-android.tar.gz
mv data root
mv system root
mv root/* ./
rmdir root
chmod +r system/usr/keychars/*
sudo chown -R 1000:1000 ./
sudo tar zcf ${OBJ_DIR}/android-fs4.tar.gz ./
