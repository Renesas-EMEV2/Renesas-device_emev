export BUILD_TYPE=debug
export WORKDIR=$PWD
export SGX_DIR=$WORKDIR
export SGX_KM_DIR=$SGX_DIR/eurasia_km
#export SGX_KM_TARGET=$SGX_KM_DIR/eurasiacon/binary2_emxx_android_$BUILD_TYPE/target/
export SGX_KM_TARGET=$SGX_KM_DIR/eurasiacon/binary2_emev_android_$BUILD_TYPE/target/
export SGX_UM_DIR=$SGX_DIR/eurasia
export SGX_UM_TARGET=$SGX_UM_DIR/eurasiacon/binary2_emev_android_$BUILD_TYPE/target/
export SGX_OUT=$WORKDIR/out/
export DISCIMAGE=$SGX_OUT

#export BUILD_TYPE=debug
#export TARGET_PRODUCT=emev
#export WORKDIR=$PWD
#export SGX_DIR=$WORKDIR
#export SGX_KM_DIR=$SGX_DIR/eurasia_km
#export SGX_UM_DIR=$SGX_DIR/eurasia
#export TARGET_ROOT=${ANDROID_ROOT}/out/target
#export SGX_TARGET_DIR=${TARGET_ROOT}/product/${TARGET_PRODUCT}/target/
##export SGX_UM_TARGET=$SGX_UM_DIR/eurasiacon/binary2_emev_android_$BUILD_TYPE/target/
##export SGX_KM_TARGET=$SGX_KM_DIR/eurasiacon/binary2_emxx_android_$BUILD_TYPE/target/
##export SGX_OUT=$WORKDIR/out/
#export SGX_UM_TARGET=$SGX_TARGET_DIR
#export SGX_KM_TARGET=$SGX_TARGET_DIR/kbuild/
#echo $TARGET_ROOT
#export SGX_OUT=${TARGET_ROOT}/product/${TARGET_PRODUCT}/SGX/

################
# Kernel Modules
#adb shell mkdir -p /system/modules/
adb push $SGX_KM_TARGET/kbuild/pvrsrvkm.ko /lib/modules/pvrsrvkm.ko
adb push $SGX_KM_TARGET/kbuild/emxxlfb.ko /lib/modules/emxxlfb.ko

################
# UM binaries
cd $SGX_OUT
adb push ./system/vendor/lib/egl/libGLESv1_CM_POWERVR_SGX530_120.so /system/vendor/lib/egl/libGLESv1_CM_POWERVR_SGX530_120.so
adb push ./system/vendor/lib/libusc.so /system/vendor/lib/libusc.so
adb push ./system/vendor/lib/egl/libGLESv2_POWERVR_SGX530_120.so /system/vendor/lib/egl/libGLESv2_POWERVR_SGX530_120.so
adb push ./system/vendor/lib/libglslcompiler.so /system/vendor/lib/libglslcompiler.so
adb push ./system/vendor/lib/libIMGegl.so /system/vendor/lib/libIMGegl.so
adb push ./system/vendor/lib/egl/libEGL_POWERVR_SGX530_120.so /system/vendor/lib/egl/libEGL_POWERVR_SGX530_120.so
adb push ./system/vendor/lib/libpvr2d.so /system/vendor/lib/libpvr2d.so
adb push ./system/vendor/lib/libsrv_um.so /system/vendor/lib/libsrv_um.so
adb push ./system/vendor/lib/libsrv_init.so /system/vendor/lib/libsrv_init.so
adb push ./system/vendor/lib/libPVRScopeServices.so /system/vendor/lib/libPVRScopeServices.so
adb push ./system/vendor/lib/hw/gralloc.emxx.so /system/vendor/lib/hw/gralloc.emxx.so
adb push ./system/vendor/lib/hw/hwcomposer.emxx.so /system/vendor/lib/hw/hwcomposer.emxx.so
adb push ./system/vendor/lib/libpvrANDROID_WSEGL.so /system/vendor/lib/libpvrANDROID_WSEGL.so
adb push ./system/vendor/bin/pvrsrvinit /system/vendor/bin/pvrsrvinit
adb push ./system/vendor/bin/pvrsrvctl /system/vendor/bin/pvrsrvctl
adb push ./system/vendor/bin/sgx_init_test /system/vendor/bin/sgx_init_test
adb push ./system/vendor/bin/services_test /system/vendor/bin/services_test
adb push ./system/vendor/bin/sgx_flip_test /system/vendor/bin/sgx_flip_test
adb push ./system/vendor/bin/sgx_render_flip_test /system/vendor/bin/sgx_render_flip_test
adb push ./system/vendor/bin/testwrap /system/vendor/bin/testwrap
adb push ./system/lib/egl/egl.cfg /system/lib/egl/egl.cfg
adb push ./data/app/gles1test1.apk /data/app/gles1test1.apk
adb push ./data/app/gles2test1.apk /data/app/gles2test1.apk
adb push ./data/app/eglinfo.apk /data/app/eglinfo.apk
#adb push ./data/app/launcher.apk /data/app/launcher.apk
adb push ./system/vendor/bin/hal_client_test /system/vendor/bin/hal_client_test
adb push ./system/vendor/bin/hal_server_test /system/vendor/bin/hal_server_test
adb push ./system/vendor/bin/framebuffer_test /system/vendor/bin/framebuffer_test
adb push ./system/vendor/bin/texture_benchmark /system/vendor/bin/texture_benchmark
adb push ./system/lib/egl/egl.cfg /system/lib/egl/egl.cfg

adb shell sync

