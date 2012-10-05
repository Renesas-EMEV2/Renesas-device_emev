#!/bin/sh
WORK_DIR=$AOSP/device/renesas/emev/tmp
GAPP_DIR=$AOSP/device/renesas/emev/GoogleApps
OBJ_DIR=$1

if [ -z $AOSP ] ; then
	echo "AOSP variable not set"
	exit 1
fi
if [ -z $KERNEL ] ; then
	echo "KERNEL variable not set"
	exit 1
fi
if [ $# -eq 0 ] ; then
	echo "Usage: pack.sh <destination>"
	exit 1
fi
if [ ! -d ${1} ] ; then
	echo "Invalid destination dir"
	exit 1
fi

echo "Creating Android fs..."
if [ ! -d ${WORK_DIR} ] ; then
   mkdir ${WORK_DIR}
fi

# cleanup
rm -f ${WORK_DIR}/tmp-android.tar.gz 
rm -f ${OBJ_DIR}/android-fs4.tar.gz
sudo rm -rf ${WORK_DIR}/android-fs

# Adding Google Applications (Market, etc.)
# The full package can be found, for example, at:
# http://wiki.rootzwiki.com/Google_Apps#20110828
# Need review and test in JB !!!
if [ -d ${GAPP_DIR}/system ] ; then
   cd ${ANDROID_DIR}/out/target/product/emev/
   cp -r $GAPP_DIR/system .
fi

# packaging Android file system
cd ${ANDROID_DIR}/out/target/product/emev/
tar zcf ${WORK_DIR}/tmp-android.tar.gz system data root

if [ ! -d ${WORK_DIR}/android-fs ] ; then
  cd ${WORK_DIR}
  mkdir android-fs
fi
cd ${WORK_DIR}/android-fs
tar zxf ${WORK_DIR}/tmp-android.tar.gz
mv data root
mv system root
mv root/* ./
rmdir root

# Create android fs tar.gz
cd ${WORK_DIR}/android-fs
chmod +r system/usr/keychars/*
sudo chown -R 1000:1000 ./
sudo tar zcf ${OBJ_DIR}/android-fs4.tar.gz ./

# Kernel image
cp ${KERNEL}/arch/arm/boot/uImage ${OBJ_DIR}/uImage4
