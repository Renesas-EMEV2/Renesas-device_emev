#ifeq ($(TARGET_BOARD_PLATFORM),emxx)

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    EV2OMXTest.cpp

LOCAL_C_INCLUDES:= \
      $(TOP)/frameworks/native/include/media/openmax \
      $(TOP)/frameworks/native/include/media/hardware \
      $(TOP)/frameworks/av/include/media/stagefright/foundation

LOCAL_SHARED_LIBRARIES := \
      libdl \
      libutils \
      libcutils

LOCAL_MODULE_PATH := $(TARGET_OUT_OPTIONAL_EXECUTABLES)

LOCAL_MODULE := ev2omxtest
LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)

#endif
