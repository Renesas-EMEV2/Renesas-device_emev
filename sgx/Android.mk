LOCAL_PATH := $(call my-dir)

# Use "../pull_firmware.sh" before build, to pull files off a working device

# SGX driver files
PRODUCT_COPY_FILES += \
       $(LOCAL_PATH)/pvrsrvkm.ko:root/lib/modules/pvrsrvkm.ko \
       $(LOCAL_PATH)/emxxlfb.ko:root/lib/modules/emxxlfb.ko \
       $(LOCAL_PATH)/bc_example.ko:root/lib/modules/bc_example.ko

# SGX library files
PRODUCT_COPY_FILES += \
       $(LOCAL_PATH)/libEGL_POWERVR_SGX530_120.so:system/vendor/lib/egl/libEGL_POWERVR_SGX530_120.so \
       $(LOCAL_PATH)/libGLESv1_CM_POWERVR_SGX530_120.so:system/vendor/lib/egl/libGLESv1_CM_POWERVR_SGX530_120.so \
       $(LOCAL_PATH)/libGLESv2_POWERVR_SGX530_120.so:system/vendor/lib/egl/libGLESv2_POWERVR_SGX530_120.so \
       $(LOCAL_PATH)/libIMGegl.so:system/vendor/lib/libIMGegl.so \
       $(LOCAL_PATH)/libglslcompiler.so:system/vendor/lib/libglslcompiler.so \
       $(LOCAL_PATH)/libsrv_um.so:system/vendor/lib/libsrv_um.so \
       $(LOCAL_PATH)/libsrv_init.so:system/vendor/lib/libsrv_init.so \
       $(LOCAL_PATH)/libusc.so:system/vendor/lib/libusc.so \
       $(LOCAL_PATH)/libpvr2d.so:system/vendor/lib/libpvr2d.so \
       $(LOCAL_PATH)/libpvrANDROID_WSEGL.so:system/vendor/lib/libpvrANDROID_WSEGL.so 
#       $(LOCAL_PATH)/gralloc.emxx.so:system/vendor/lib/hw/gralloc.emxx.so

# SGX Execution files
PRODUCT_COPY_FILES += \
       $(LOCAL_PATH)/pvrsrvinit:system/vendor/bin/pvrsrvinit
       
# SGX other files
PRODUCT_COPY_FILES += \
       $(LOCAL_PATH)/powervr.ini:system/etc/powervr.ini \
       $(LOCAL_PATH)/egl.cfg:system/lib/egl/egl.cfg
