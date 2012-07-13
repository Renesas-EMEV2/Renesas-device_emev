# config.mk
#
# Product-specific compile-time definitions.
#
TARGET_BOARD_PLATFORM := emxx

# The generic product target doesn't have any hardware-specific pieces.
TARGET_NO_BOOTLOADER := true
TARGET_NO_KERNEL := true
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi

# no hardware camera
USE_CAMERA_STUB := true

# Renesas EMEV specific
ARCH_ARM_HAVE_TLS_REGISTER=true
TARGET_ARCH_VARIANT=armv7-a-neon
TARGET_CPU_SMP=true
WITH_JIT=true
JS_ENGINE=v8

TARGET_NO_RADIOIMAGE := true
TARGET_NO_RECOVERY := true

TARGET_HARDWARE_3D := false

# Don't copy generic init.rc
TARGET_PROVIDES_INIT_RC := true

# Use EXT4
TARGET_USERIMAGES_USE_EXT4 := true
TARGET_BOOTIMAGE_USE_EXT4 := true

# Wifi module
# http://blog.linuxconsulting.ro/2010/04/porting-wifi-drivers-to-android.html
# dhd.ko is for BCM4329_4_218_248_15
# wlan.ko is for BCM4329_4_218_248_6
BOARD_WPA_SUPPLICANT_DRIVER := WEXT
WIFI_DRIVER_MODULE_PATH := /lib/modules/dhd.ko
WIFI_DRIVER_MODULE_NAME := dhd
#WIFI_DRIVER_MODULE_PATH := /lib/modules/wlan.ko
#WIFI_DRIVER_MODULE_NAME := wlan

# MultiMedia defines
BOARD_USES_GENERIC_AUDIO := true
#BOARD_USES_ALSA_AUDIO := true

