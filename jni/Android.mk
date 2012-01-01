LOCAL_PATH := $(realpath $(call my-dir)/..)
ENGINEDIR := $(LOCAL_PATH)/engine

include $(CLEAR_VARS)
include $(ENGINEDIR)/src/zlib/Android.mk
include $(ENGINEDIR)/src/unzip/Android.mk
include $(ENGINEDIR)/src/tinyxml/Android.mk
include $(ENGINEDIR)/src/pvr/Android.mk
include $(ENGINEDIR)/src/Android.mk

LOCAL_MODULE     := liborangegrass
LOCAL_CFLAGS     := -Werror
LOCAL_C_INCLUDES += $(ENGINEDIR)/include
LOCAL_LDLIBS     := -llog -lGLESv2

include $(BUILD_SHARED_LIBRARY)
