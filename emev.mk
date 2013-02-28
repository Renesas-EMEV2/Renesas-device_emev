$(call inherit-product, build/target/product/generic.mk)
$(call inherit-product, device/renesas/emev/device.mk)

# include available languages for TTS in the system image
include external/svox/pico/lang/PicoLangDeDeInSystem.mk
include external/svox/pico/lang/PicoLangEnGBInSystem.mk
include external/svox/pico/lang/PicoLangEnUsInSystem.mk
include external/svox/pico/lang/PicoLangEsEsInSystem.mk
include external/svox/pico/lang/PicoLangFrFrInSystem.mk
include external/svox/pico/lang/PicoLangItItInSystem.mk

# Overrides
PRODUCT_NAME := renesas_emev
PRODUCT_DEVICE := emev
PRODUCT_BOARD := emev
PRODUCT_BRAND := emxx
PRODUCT_MANUFACTURER := renesas
PRODUCT_LOCALES += en_US ja_JP ldpi hdpi mdpi

#PRODUCT_COPY_FILES += \
    #frameworks/base/data/etc/android.hardware.camera.xml:system/etc/permissions/android.hardware.camera.xml \
    #frameworks/base/data/etc/android.hardware.touchscreen.xml:system/etc/permissions/android.hardware.touchscreen.xml \
    #packages/wallpapers/LivePicker/android.software.live_wallpaper.xml:system/etc/permissions/android.software.live_wallpaper.xml

######### 
# ALSA
#asound.conf
#PRODUCT_COPY_FILES += \
#    $(LOCAL_PATH)/asound.conf:system/etc/asound.conf
#alsa-lib conf
#PRODUCT_COPY_FILES += \
#    external/alsa-lib/src/conf/alsa.conf:system/usr/share/alsa/alsa.conf \
#    external/alsa-lib/src/conf/cards/aliases.conf:system/usr/share/alsa/cards/aliases.conf \
#    external/alsa-lib/src/conf/pcm/center_lfe.conf:system/usr/share/alsa/pcm/center_lfe.conf \
#    external/alsa-lib/src/conf/pcm/default.conf:system/usr/share/alsa/pcm/default.conf \
#    external/alsa-lib/src/conf/pcm/dmix.conf:system/usr/share/alsa/pcm/dmix.conf \
#    external/alsa-lib/src/conf/pcm/dpl.conf:system/usr/share/alsa/pcm/dpl.conf \
#    external/alsa-lib/src/conf/pcm/dsnoop.conf:system/usr/share/alsa/pcm/dsnoop.conf \
#    external/alsa-lib/src/conf/pcm/front.conf:system/usr/share/alsa/pcm/front.conf \
#    external/alsa-lib/src/conf/pcm/iec958.conf:system/usr/share/alsa/pcm/iec958.conf \
#    external/alsa-lib/src/conf/pcm/modem.conf:system/usr/share/alsa/pcm/modem.conf \
#    external/alsa-lib/src/conf/pcm/rear.conf:system/usr/share/alsa/pcm/rear.conf \
#    external/alsa-lib/src/conf/pcm/side.conf:system/usr/share/alsa/pcm/side.conf \
#    external/alsa-lib/src/conf/pcm/surround40.conf:system/usr/share/alsa/pcm/surround40.conf \
#    external/alsa-lib/src/conf/pcm/surround41.conf:system/usr/share/alsa/pcm/surround41.conf \
#    external/alsa-lib/src/conf/pcm/surround50.conf:system/usr/share/alsa/pcm/surround50.conf \
#    external/alsa-lib/src/conf/pcm/surround51.conf:system/usr/share/alsa/pcm/surround51.conf \
#    external/alsa-lib/src/conf/pcm/surround71.conf:system/usr/share/alsa/pcm/surround71.conf \
#    #external/alsa-lib/src/conf/pcm/hdmi.conf:system/usr/share/alsa/pcm/hdmi.conf


