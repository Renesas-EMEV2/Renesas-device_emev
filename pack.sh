#!/bin/sh

ANDROID_DIR=$AOSP
KERNEL_DIR=$KERNEL
WORK_DIR=$ANDROID_DIR
OBJ_DIR=$ANDROID_DIR
GAPP_DIR=$ANDROID_DIR/device/renesas/emev/GoogleApps

# Create Userland
echo ""
echo "-----------------------"
echo "- userland deployment -"
echo "-----------------------"

# cleanup
rm -f ${ANDROID_DIR}/tmp-android.tar.gz 
rm -f ${OBJ_DIR}/android-fs4.tar.gz
sudo rm -rf ${WORK_DIR}/android-fs

# WORKAROUND (need to figure out why build doesn't do that)
cd ${ANDROID_DIR}/out/target/product/emev/
cp ./obj/lib/copybit.emxx.so ./system/lib/hw/copybit.emxx.so
cp ./obj/lib/gralloc.emxx.so ./system/lib/hw/gralloc.emxx.so
cp ./obj/lib/overlay.emxx.so ./system/lib/hw/overlay.emxx.so

# Adding Google Applications (Market, etc.)
# The full package can be found, for example, at:
# http://wiki.rootzwiki.com/Google_Apps#20110828
if [ ! -d ${GAPP_DIR}/system ] ; then
   cd ${ANDROID_DIR}/out/target/product/emev/
   cp -r $GAPP_DIR/system .
fi

# packaging Android file system
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

# Copying KERNEL modules
cd ${WORK_DIR}/android-fs
cp ${KERNEL}/arch/arm/mach-emxx/inter_dsp.ko ./lib/modules
cp ${KERNEL}/drivers/ave/em_ave.ko ./lib/modules

rmdir root
chmod +r system/usr/keychars/*
sudo chown -R 1000:1000 ./
sudo tar zcf ${OBJ_DIR}/android-fs4.tar.gz ./
