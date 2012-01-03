LOCAL_PATH := $(realpath $(call my-dir)/..)
ENGINEDIR := $(LOCAL_PATH)/engine
GAMEDIR := $(LOCAL_PATH)/skycrasher

include $(CLEAR_VARS)
include $(ENGINEDIR)/src/zlib/Android.mk
include $(ENGINEDIR)/src/unzip/Android.mk
include $(ENGINEDIR)/src/tinyxml/Android.mk
include $(ENGINEDIR)/src/pvr/Android.mk
include $(ENGINEDIR)/src/Android.mk
include $(GAMEDIR)/game/src/Android.mk

LOCAL_MODULE     := liborangegrass
LOCAL_CFLAGS     := -Werror
LOCAL_C_INCLUDES += $(ENGINEDIR)/include \
                    $(GAMEDIR)/game/include
LOCAL_LDLIBS     := -llog -lGLESv2

include $(BUILD_SHARED_LIBRARY)
