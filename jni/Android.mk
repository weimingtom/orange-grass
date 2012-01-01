LOCAL_PATH := $(realpath $(call my-dir)/..)
ENGINEDIR := $(LOCAL_PATH)/engine

include $(CLEAR_VARS)
include $(ENGINEDIR)/src/zlib/Android.mk
include $(ENGINEDIR)/src/unzip/Android.mk

LOCAL_MODULE    := liborangegrass
LOCAL_CFLAGS    := -Werror
LOCAL_LDLIBS    := -llog -lGLESv2

include $(BUILD_SHARED_LIBRARY)
