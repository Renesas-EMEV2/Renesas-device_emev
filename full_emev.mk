$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_small.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/generic.mk)
$(call inherit-product, device/renesas/emev/gpu.mk)
$(call inherit-product, frameworks/base/data/sounds/OriginalAudio.mk)

PRODUCT_PACKAGES += \
    LiveWallpapersPicker \
    LiveWallpapers \
    MagicSmokeWallpapers \
    VisualizationWallpapers \
    librs_jni \

PRODUCT_PACKAGES += \
	gralloc.emxx \
	copybit.emxx \
	lights.emxx \
	alsa.default \
	overlay.emxx \
	libstagefrighthw \
        acoustics.default

# Discard inherited values and use our own instead.
PRODUCT_NAME := renesas_emev
PRODUCT_DEVICE := emev
PRODUCT_MODEL := Full Renesas EMEV
PRODUCT_BOARD := emev
PRODUCT_BRAND := emxx
PRODUCT_MANUFACTURER := renesas
PRODUCT_PROPERTY_OVERRIDES += \
    dalvik.vm.heapsize=32m

PRODUCT_COPY_FILES += \
    frameworks/base/data/etc/android.hardware.camera.xml:system/etc/permissions/android.hardware.camera.xml \
    frameworks/base/data/etc/android.hardware.touchscreen.xml:system/etc/permissions/android.hardware.touchscreen.xml \
    packages/wallpapers/LivePicker/android.software.live_wallpaper.xml:system/etc/permissions/android.software.live_wallpaper.xml

PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/emev.kl:system/usr/keylayout/qwerty.kl

PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/init.rc:root/init.rc \
	$(LOCAL_PATH)/init.emev.rc:root/init.emxx.rc \
 	$(LOCAL_PATH)/ueventd.emev.rc:root/ueventd.emxx.rc \
  	$(LOCAL_PATH)/init.emev.sh:system/etc/init.emev.sh \
  	$(LOCAL_PATH)/vold.fstab:system/etc/vold.fstab \
  	$(LOCAL_PATH)/media_profiles.xml:system/etc/media_profiles.xml

# Wifi modules
# See  http://blog.linuxconsulting.ro/2010/04/porting-wifi-drivers-to-android.html
# dhd.ko module, version 4.218.248.15 (dhd.ko module, version 4.218.248.15, ICS Livall kernel)
PRODUCT_COPY_FILES += \
       $(LOCAL_PATH)/bcm/4.218.248.15/wpa_supplicant.conf:system/etc/wifi/wpa_supplicant.conf \
       $(LOCAL_PATH)/bcm/4.218.248.15/dhd.ko:root/lib/modules/dhd.ko \
       $(LOCAL_PATH)/bcm/4.218.248.15/fw4329.bin:system/etc/firmware/fw4329.bin \
       $(LOCAL_PATH)/bcm/4.218.248.15/4329_nvram.txt:system/etc/firmware/4329_nvram.txt

# wlan.ko module, version 4.218.248.6 (wlan.ko module, version 4.218.248.6, GB Livall kernel)
#PRODUCT_COPY_FILES += \
#       $(LOCAL_PATH)/bcm/4.218.248.6/wpa_supplicant.conf:system/etc/wifi/wpa_supplicant.conf \
#       $(LOCAL_PATH)/bcm/4.218.248.6/wlan.ko:root/lib/modules/wlan.ko \
#       $(LOCAL_PATH)/bcm/4.218.248.6/fw_bcm4329.bin:root/lib/modules/fw_bcm4329.bin \
#       $(LOCAL_PATH)/bcm/4.218.248.6/nvram.txt:root/lib/modules/nvram.txt \
#       $(LOCAL_PATH)/bcm/4.218.248.6/USI_BCM4329B1.hcd:root/lib/modules/USI_BCM4329B1.hcd
 

#$(call inherit-product, frameworks/base/data/sounds/OriginalAudio.mk)

# include available languages for TTS in the system image
include external/svox/pico/lang/PicoLangDeDeInSystem.mk
include external/svox/pico/lang/PicoLangEnGBInSystem.mk
include external/svox/pico/lang/PicoLangEnUsInSystem.mk
include external/svox/pico/lang/PicoLangEsEsInSystem.mk
include external/svox/pico/lang/PicoLangFrFrInSystem.mk
include external/svox/pico/lang/PicoLangItItInSystem.mk

include $(call all-makefiles-under,$(LOCAL_PATH))

