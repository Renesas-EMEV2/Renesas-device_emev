# These definitions override the defaults in config/config.make.

TARGET_BOARD_PLATFORM := emxx
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi

TARGET_ARCH_VARIANT = armv7-a-neon
ARCH_ARM_HAVE_TLS_REGISTER := true

TARGET_NO_BOOTLOADER := true
TARGET_NO_KERNEL := true
TARGET_NO_RADIOIMAGE := true
TARGET_NO_RECOVERY := true
TARGET_CPU_SMP := true

TARGET_HARDWARE_3D := false

# Don't copy generic init.rc
TARGET_PROVIDES_INIT_RC := true

# Increased system partition
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 160M

# Use EXT4
TARGET_USERIMAGES_USE_EXT4 := true
TARGET_BOOTIMAGE_USE_EXT4 := true

# MultiMedia defines
BOARD_USES_GENERIC_AUDIO := true
#BOARD_USES_ALSA_AUDIO := true
USE_CAMERA_STUB := true

# Wifi related defines
WPA_SUPPLICANT_VERSION      := VER_0_8_X
BOARD_WPA_SUPPLICANT_DRIVER := WEXT

# Bluetooth
BOARD_HAVE_BLUETOOTH := true
BOARD_HAVE_BLUETOOTH_BCM := true

WITH_JIT := true
JS_ENGINE := v8

# Product-specific optimizations
PRODUCT_PROPERTY_OVERRIDES := \
	ro.sf.lcd_density=160 \
        sys.device.type=tablet \
        dalvik.vm.heapstartsize=5m \
        dalvik.vm.heapgrowthlimit=56m \
        dalvik.vm.heapsize=128m 
#	dalvik.vm.heapsize=64m

PRODUCT_CHARACTERISTICS := \
        tablet



