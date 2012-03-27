# config.mk
#
# Product-specific compile-time definitions.
#

# The generic product target doesn't have any hardware-specific pieces.
TARGET_NO_BOOTLOADER := true
TARGET_NO_KERNEL := true
TARGET_CPU_ABI := armeabi
HAVE_HTC_AUDIO_DRIVER := true
BOARD_USES_GENERIC_AUDIO := true

# no hardware camera
USE_CAMERA_STUB := true

# Renesas EMEV specific
ARCH_ARM_HAVE_TLS_REGISTER=true
TARGET_ARCH_VARIANT=armv7-a-neon
TARGET_CPU_SMP=true
WITH_JIT=true
JS_ENGINE=v8
