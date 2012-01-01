LOCAL_PATH := $(realpath $(call my-dir)/..)
ENGINEDIR := $(LOCAL_PATH)/engine

include $(ENGINEDIR)/src/zlib/Android.mk
include $(ENGINEDIR)/src/unzip/Android.mk

include $(CLEAR_VARS)

LOCAL_MODULE    := liborangegrass
LOCAL_CFLAGS    := -Werror
LOCAL_LDLIBS    := -llog -lGLESv2
APP_STL 		:= stlport_static

include $(BUILD_SHARED_LIBRARY)
