#!/bin/sh
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

WORK_DIR=$AOSP/device/renesas/emev/tmp
GAPP_DIR=$AOSP/device/renesas/emev/gapps
KERNEL_DIR=$KERNEL
OBJ_DIR=$1

echo "Preparing..."
if [ ! -d ${WORK_DIR} ] ; then
   mkdir ${WORK_DIR}
fi

# initial cleanup
rm -f ${WORK_DIR}/tmp-android.tar.gz 
rm -f ${OBJ_DIR}/android-fs4.tar.gz
sudo rm -rf ${WORK_DIR}/android-fs

# Android file system
echo "Packaging Android file system..."
cd ${AOSP}/out/target/product/emev/
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

# Adding Google Applications (Play, etc.)
# Packages can be found, for example, at:
# http://wiki.rootzwiki.com/Google_Apps
# http://goo.im/gapps/
# http://forum.xda-developers.com/showthread.php?t=1917411 (lightweight - this looks like working)
if [ -d ${GAPP_DIR}/system ] ; then
   echo "Adding Google Apps..."
   cp -r $GAPP_DIR/* ${WORK_DIR}/android-fs
fi

# KERNEL drivers
echo "Copying KERNEL drivers..."
if [ ! -d ${WORK_DIR}/android-fs/lib ] ; then
  cd ${WORK_DIR}
  mkdir android-fs/lib
fi
if [ ! -d ${WORK_DIR}/android-fs/lib/modules ] ; then
  cd ${WORK_DIR}
  mkdir android-fs/lib/modules
fi
cd ${WORK_DIR}/android-fs
cp ${KERNEL_DIR}/arch/arm/mach-emxx/inter_dsp.ko ./lib/modules/inter_dsp.ko
cp ${KERNEL_DIR}/drivers/ave/em_ave.ko ./lib/modules/em_ave.ko

# android fs tar.gz
echo "Creating android fs tar.gz..."
cd ${WORK_DIR}/android-fs
chmod +r system/usr/keychars/*
sudo chown -R 1000:1000 ./
sudo tar zcf ${OBJ_DIR}/android-fs4.tar.gz ./

# Kernel image
echo "Copying Kernel Image..."
cp ${KERNEL_DIR}/arch/arm/boot/uImage4 ${OBJ_DIR}/uImage4

# final cleanup
rm -f ${WORK_DIR}/tmp-android.tar.gz 
sudo rm -rf ${WORK_DIR}/android-fs
