$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_small.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/generic.mk)

PRODUCT_PACKAGES += \
    LiveWallpapersPicker \
    LiveWallpapers \
    MagicSmokeWallpapers \
    VisualizationWallpapers \
    librs_jni \
    lights.emxx

# Discard inherited values and use our own instead.
PRODUCT_NAME := full_renesas_emev
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
	$(LOCAL_PATH)/init.emxx.rc:root/init.emxx.rc \
	$(LOCAL_PATH)/init.emev.sh:system/etc/init.emev.sh

#$(call inherit-product, frameworks/base/data/sounds/OriginalAudio.mk)

# include available languages for TTS in the system image
include external/svox/pico/lang/PicoLangDeDeInSystem.mk
include external/svox/pico/lang/PicoLangEnGBInSystem.mk
include external/svox/pico/lang/PicoLangEnUsInSystem.mk
include external/svox/pico/lang/PicoLangEsEsInSystem.mk
include external/svox/pico/lang/PicoLangFrFrInSystem.mk
include external/svox/pico/lang/PicoLangItItInSystem.mk

include $(call all-makefiles-under,$(LOCAL_PATH))

