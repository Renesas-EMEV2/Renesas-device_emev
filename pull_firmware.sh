#!/bin/sh

SGX_FILES=${AOSP}/device/renesas/emev/firmware
OMF_FILES=${AOSP}/device/renesas/emev/firmware
BCM_FILES=${AOSP}/device/renesas/emev/firmware

mkdir -p ${SGX_FILES}/lib/modules
mkdir -p ${SGX_FILES}/system/etc/
mkdir -p ${SGX_FILES}/system/lib/egl/
mkdir -p ${SGX_FILES}/system/vendor/bin/
mkdir -p ${SGX_FILES}/system/vendor/lib/egl/
mkdir -p ${SGX_FILES}/system/vendor/lib/hw/

adb pull /lib/modules/bc_example.ko ${SGX_FILES}/lib/modules/
adb pull /lib/modules/emxxlfb.ko ${SGX_FILES}/lib/modules/
adb pull /lib/modules/pvrsrvkm.ko ${SGX_FILES}/lib/modules/
adb pull /system/etc/powervr.ini ${SGX_FILES}/system/etc/
adb pull /system/lib/egl/egl.cfg ${SGX_FILES}/system/lib/egl/
adb pull /system/vendor/bin/pvrsrvinit ${SGX_FILES}/system/vendor/bin/
adb pull /system/vendor/lib/libglslcompiler.so ${SGX_FILES}/system/vendor/lib/egl/
adb pull /system/vendor/lib/libIMGegl.so ${SGX_FILES}/system/vendor/lib/egl/
adb pull /system/vendor/lib/libpvr2d.so ${SGX_FILES}/system/vendor/lib/egl/
adb pull /system/vendor/lib/libpvrANDROID_WSEGL.so ${SGX_FILES}/system/vendor/lib/egl/
adb pull /system/vendor/lib/libsrv_init.so ${SGX_FILES}/system/vendor/lib/egl/
adb pull /system/vendor/lib/libsrv_um.so ${SGX_FILES}/system/vendor/lib/egl/
adb pull /system/vendor/lib/libusc.so ${SGX_FILES}/system/vendor/lib/egl/
adb pull /system/vendor/lib/egl/libEGL_POWERVR_SGX530_120.so ${SGX_FILES}/system/vendor/lib/egl/
adb pull /system/vendor/lib/egl/libGLESv1_CM_POWERVR_SGX530_120.so ${SGX_FILES}/system/vendor/lib/egl/
adb pull /system/vendor/lib/egl/libGLESv2_POWERVR_SGX530_120.so ${SGX_FILES}/system/vendor/lib/egl/
#adb pull /system/vendor/lib/hw/gralloc.emxx.so ${SGX_FILES}/system/vendor/lib/hw/

chmod 755 ${SGX_FILES}/system/vendor/bin/pvrsrvinit

mkdir -p ${OMF_FILES}/system/etc/
mkdir -p ${OMF_FILES}/system/lib/omf/dspfw/
mkdir -p ${OMF_FILES}/lib/
mkdir -p ${OMF_FILES}/system/lib/

adb pull /system/etc/pvplayer.cfg ${OMF_FILES}/system/etc/
adb pull /system/lib/libomf_manager.so ${OMF_FILES}/system/lib/
adb pull /system/lib/libomf_me_video_cmn.so ${OMF_FILES}/system/lib/
adb pull /system/lib/omf/dspfw/omf_dsp_manager.em-ev ${OMF_FILES}/system/lib/omf/dspfw/
adb pull /system/lib/omf/dspfw/omf_me_aacd.em-ev ${OMF_FILES}/system/lib/omf/dspfw/
adb pull /system/lib/omf/dspfw/omf_me_jpegd.em-ev ${OMF_FILES}/system/lib/omf/dspfw/
adb pull /system/lib/omf/dspfw/omf_me_jpege.em-ev ${OMF_FILES}/system/lib/omf/dspfw/
adb pull /system/lib/omf/omx_av_codec.cfg ${OMF_FILES}/system/lib/omf/
adb pull /system/lib/omf_mc_aacd.so ${OMF_FILES}/system/lib/
adb pull /system/lib/omf_mc_h264d.so ${OMF_FILES}/system/lib/
adb pull /system/lib/omf_mc_jpegd.so ${OMF_FILES}/system/lib/
adb pull /system/lib/omf_mc_jpege.so ${OMF_FILES}/system/lib/
adb pull /system/lib/omf_mc_m4vd.so ${OMF_FILES}/system/lib/
adb pull /system/lib/omf_mc_m2vd.so ${OMF_FILES}/system/lib/
adb pull /system/lib/omf_mc_vc1d.so ${OMF_FILES}/system/lib/

cp ${OMF_FILES}/system/lib/libomf_manager.so ${OMF_FILES}/lib/

mkdir -p ${BCM_FILES}/lib/
adb pull /lib/modules/wlan.ko ${BCM_FILES}/lib/modules/

