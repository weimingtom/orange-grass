LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := liborangegrass
LOCAL_CFLAGS    := -Werror
LOCAL_SRC_FILES := orangegrass.cpp
LOCAL_LDLIBS    := -llog -lGLESv2
APP_STL 		:= stlport_static

include $(BUILD_SHARED_LIBRARY)
