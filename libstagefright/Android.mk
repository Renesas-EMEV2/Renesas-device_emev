#ifeq ($(TARGET_BOARD_PLATFORM),emxx)

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    EV2OMXPlugin.cpp

LOCAL_C_INCLUDES:= \
      $(TOP)/frameworks/native/include/media/openmax \
      $(TOP)/frameworks/native/include/media/hardware \
      $(TOP)/frameworks/av/include/media/stagefright/foundation

LOCAL_SHARED_LIBRARIES :=       \
        libbinder               \
        libutils                \
        libcutils               \
        libui                   \
        libcutils                       \
        libstagefright_foundation       \
        libdl                   

#LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw

LOCAL_MODULE := libstagefrighthw
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)

#endif
