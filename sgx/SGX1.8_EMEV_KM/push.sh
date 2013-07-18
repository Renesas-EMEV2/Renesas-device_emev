# Run it only after succesfull completion of:
#  compile_km.sh
source source.sh

export WORKDIR=$PWD
export SGX_DIR=$WORKDIR
export SGX_KM_DIR=$SGX_DIR/eurasia_km
export SGX_KM_TARGET=$SGX_KM_DIR/eurasiacon/binary2_emev_android_$BUILD_TYPE/target

adb shell mkdir -p /system/modules/
adb push $SGX_KM_TARGET/pvrsrvkm.ko /system/modules/
adb push $SGX_KM_TARGET/emxxlfb.ko /system/modules/
adb shell sync

