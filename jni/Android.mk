LOCAL_PATH := $(realpath $(call my-dir)/..)
ENGINEDIR := $(LOCAL_PATH)/sources/engine
GAMEDIR := $(LOCAL_PATH)/sources/skycrasher

include $(CLEAR_VARS)
include $(ENGINEDIR)/src/zlib/Android.mk
include $(ENGINEDIR)/src/unzip/Android.mk
include $(ENGINEDIR)/src/tinyxml/Android.mk
include $(ENGINEDIR)/src/pvr/Android.mk
include $(ENGINEDIR)/src/Android.mk
include $(GAMEDIR)/game/src/Android.mk
include $(GAMEDIR)/launcher/android/Android.mk

ifeq ($(TARGET_ARCH_ABI),x86)
LOCAL_CFLAGS += -fno-stack-protector 
endif

LOCAL_MODULE     := liborangegrass
LOCAL_CFLAGS     := -Werror -std=gnu++11
LOCAL_C_INCLUDES += $(ENGINEDIR)/include \
                    $(GAMEDIR)/game/include
LOCAL_LDLIBS     := -llog -lGLESv2 -lEGL

include $(BUILD_SHARED_LIBRARY)
