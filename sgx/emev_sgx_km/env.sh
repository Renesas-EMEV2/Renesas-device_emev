#!/bin/sh
export LANG=C
export ARCH=arm
export KERNELDIR=$KERNEL
export ANDROID_ROOT=$AOSP
export CROSS_COMPILE=arm-eabi-
export KERNEL_CROSS_COMPILE=$CROSS_COMPILE
cd eurasia_km/eurasiacon/build/linux2/emev_android
make 
