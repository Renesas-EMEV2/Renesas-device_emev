#
# Copyright (C) 2011 The Android Open-Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#
# Everything in this directory will become public

LOCAL_KERNEL := uImage

#DEVICE_PACKAGE_OVERLAYS := device/samsung/tuna/overlay

PRODUCT_PACKAGES := \
	lights.emxx \
        gralloc.emxx 

# Audio
PRODUCT_PACKAGES += \
	audio.primary.emxx

# Audio samples
PRODUCT_COPY_FILES += \
	frameworks/base/data/sounds/effects/Lock.ogg:system/media/audio/ui/Lock.ogg \
	frameworks/base/data/sounds/effects/Lock.ogg:system/media/audio/ui/Unlock.ogg \
	frameworks/base/data/sounds/effects/Effect_Tick.ogg:system/media/audio/ui/Effect_Tick.ogg \
	frameworks/base/data/sounds/effects/KeypressStandard.ogg:system/media/audio/ui/KeypressStandard.ogg \
	frameworks/base/data/sounds/effects/KeypressSpacebar.ogg:system/media/audio/ui/KeypressSpacebar.ogg \
	frameworks/base/data/sounds/effects/KeypressDelete.ogg:system/media/audio/ui/KeypressDelete.ogg \
	frameworks/base/data/sounds/effects/KeypressReturn.ogg:system/media/audio/ui/KeypressReturn.ogg

PRODUCT_COPY_FILES += \
	device/renesas/emev/audio/audio_policy.conf:system/etc/audio_policy.conf \
	device/renesas/emev/audio/mixer_paths.xml:system/etc/mixer_paths.xml

# kernel modules - moved to final packaging script.
#PRODUCT_COPY_FILES += \
#	$(LOCAL_PATH)/modules/inter_dsp.ko:root/lib/modules/inter_dsp.ko \
#	$(LOCAL_PATH)/modules/em_ave.ko:root/lib/modules/em_ave.ko \
#	$(LOCAL_PATH)/modules/pwm.ko:root/lib/modules/pwm.ko

# EMEV Setting file
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/init.rc:root/init.rc \
	$(LOCAL_PATH)/ueventd.emev.rc:root/ueventd.emxx.rc \
	$(LOCAL_PATH)/init.emxx.rc:root/init.emxx.rc \
	$(LOCAL_PATH)/init.emev.sh:system/etc/init.emev.sh \
	$(LOCAL_PATH)/vold.fstab:system/etc/vold.fstab \
	$(LOCAL_PATH)/media_profiles.xml:system/etc/media_profiles.xml

# EMEV logo file
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/initlogo.rle:root/initlogo.rle

# EMEV keycode
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/emev-keypad.kl:system/usr/keylayout/qwerty.kl

# EMEV touch pad configure file
PRODUCT_COPY_FILES += \
        $(LOCAL_PATH)/touch.idc:system/usr/idc/pixcir168.idc \
	$(LOCAL_PATH)/touch.idc:system/usr/idc/gt80x.idc

# Wifi configuration
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/wifi/wpa_supplicant.conf:system/etc/wifi/wpa_supplicant.conf \
	$(LOCAL_PATH)/wifi/dhd.ko:system/lib/modules/dhd.ko \
	$(LOCAL_PATH)/wifi/fw4329.bin:system/etc/firmware/fw4329.bin \
	$(LOCAL_PATH)/wifi/4329_nvram.txt:system/etc/firmware/4329_nvram.txt
# hardware conf
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/wifi/android.hardware.wifi.xml:system/etc/permissions/android.hardware.wifi.xml

##############################################
# PowerVR SGX 530 EGL rendering engine drivers
SGX_PATH := $(LOCAL_PATH)/sgx
SGX_BINARIES := $(SGX_PATH)/out/system
SGX_MODULES := $(SGX_PATH)/eurasia_km/eurasiacon/binary2_emev_android_debug/target/kbuild
PRODUCT_COPY_FILES += \
	$(SGX_MODULES)/pvrsrvkm.ko:root/lib/modules/pvrsrvkm.ko \
	$(SGX_MODULES)/emxxlfb.ko:root/lib/modules/emxxlfb.ko
# HAL libraries
PRODUCT_COPY_FILES += \
	$(SGX_BINARIES)/vendor/lib/hw/gralloc.emxx.so:system/vendor/lib/hw/gralloc.emxx.so \
	$(SGX_BINARIES)/vendor/lib/hw/hwcomposer.emxx.so:system/vendor/lib/hw/hwcomposer.emxx.so
# SGX library files
PRODUCT_COPY_FILES += \
	$(SGX_BINARIES)/vendor/lib/egl/libEGL_POWERVR_SGX530_120.so:system/vendor/lib/egl/libEGL_POWERVR_SGX530_120.so \
	$(SGX_BINARIES)/vendor/lib/egl/libGLESv1_CM_POWERVR_SGX530_120.so:system/vendor/lib/egl/libGLESv1_CM_POWERVR_SGX530_120.so \
	$(SGX_BINARIES)/vendor/lib/egl/libGLESv2_POWERVR_SGX530_120.so:system/vendor/lib/egl/libGLESv2_POWERVR_SGX530_120.so \
	$(SGX_BINARIES)/vendor/lib/libIMGegl.so:system/vendor/lib/libIMGegl.so \
	$(SGX_BINARIES)/vendor/lib/libPVRScopeServices.so:system/vendor/lib/libPVRScopeServices.so \
	$(SGX_BINARIES)/vendor/lib/libglslcompiler.so:system/vendor/lib/libglslcompiler.so \
	$(SGX_BINARIES)/vendor/lib/libsrv_um.so:system/vendor/lib/libsrv_um.so \
	$(SGX_BINARIES)/vendor/lib/libsrv_init.so:system/vendor/lib/libsrv_init.so \
	$(SGX_BINARIES)/vendor/lib/libusc.so:system/vendor/lib/libusc.so \
	$(SGX_BINARIES)/vendor/lib/libpvr2d.so:system/vendor/lib/libpvr2d.so \
	$(SGX_BINARIES)/vendor/lib/libpvrANDROID_WSEGL.so:system/vendor/lib/libpvrANDROID_WSEGL.so
# SGX Execution files
PRODUCT_COPY_FILES += \
	$(SGX_BINARIES)/vendor/bin/pvrsrvinit:system/vendor/bin/pvrsrvinit
# EGL configuration
PRODUCT_COPY_FILES += \
	$(SGX_BINARIES)/lib/egl/egl.cfg:system/lib/egl/egl.cfg

# Live Wallpapers
PRODUCT_PACKAGES += \
        LiveWallpapers \
        LiveWallpapersPicker \
        VisualizationWallpapers \
        librs_jni

PRODUCT_PROPERTY_OVERRIDES += \
	ro.sf.lcd_density=160

PRODUCT_TAGS += dalvik.gc.type-precise

# Filesystem management tools
PRODUCT_PACKAGES += \
	make_ext4fs \
	setup_fs

#$(call inherit-product, frameworks/base/build/phone-xhdpi-1024-dalvik-heap.mk)

#$(call inherit-product-if-exists, vendor/nxp/pn544/nxp-pn544-fw-vendor.mk)
#$(call inherit-product, hardware/ti/omap4xxx/omap4.mk)
#$(call inherit-product-if-exists, vendor/ti/proprietary/omap4/ti-omap4-vendor.mk)
#$(call inherit-product-if-exists, vendor/samsung/tuna/device-vendor.mk)

#BOARD_WLAN_DEVICE_REV := bcm4330_b2
#WIFI_BAND             := 802_11_ABG
#$(call inherit-product-if-exists, hardware/broadcom/wlan/bcmdhd/firmware/bcm4330/device-bcm.mk)
