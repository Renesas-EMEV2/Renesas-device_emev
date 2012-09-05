
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
PRODUCT_PROPERTY_OVERRIDES += \
    dalvik.vm.heapsize=48m
#PRODUCT_COPY_FILES += \
    #frameworks/base/data/etc/android.hardware.camera.xml:system/etc/permissions/android.hardware.camera.xml \
    #frameworks/base/data/etc/android.hardware.touchscreen.xml:system/etc/permissions/android.hardware.touchscreen.xml \
    #packages/wallpapers/LivePicker/android.software.live_wallpaper.xml:system/etc/permissions/android.software.live_wallpaper.xml

