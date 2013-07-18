###### NOTE ########
## Requires creation of soft-links first:
##  links.sh

source source.sh

export TARGET_PRODUCT=emev
export WORKDIR=$PWD
export SGX_DIR=$WORKDIR
export SGX_KM_DIR=$SGX_DIR/eurasia_km
export TARGET_ROOT=${ANDROID_ROOT}/out/target
export SGX_TARGET_DIR=${TARGET_ROOT}/product/${TARGET_PRODUCT}/target
export SGX_KM_TARGET=$SGX_KM_DIR/eurasiacon/binary2_emev_android_$BUILD_TYPE/target

# Full cleanup
# rm -rf $SGX_KM_TARGET/*

# Compile KM
export CROSS_COMPILE=${ANDROID_ROOT}/prebuilt/linux-x86/toolchain/arm-eabi-4.4.3/bin/arm-eabi-
export KM_BUILD_DIR=$SGX_KM_DIR/eurasiacon/build/linux2/emev_android/
cd $KM_BUILD_DIR
BUILD=$BUILD_TYPE make

