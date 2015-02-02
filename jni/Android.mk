LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#OPENCV_CAMERA_MODULES:=off
OPENCV_INSTALL_MODULES:=on
#OPENCV_LIB_TYPE:=SHARED
include /opt/sdk/OpenCV-2.4.9-android-sdk/sdk/native/jni/OpenCV.mk

LOCAL_SRC_FILES  := datahidingdemoreceiver.cpp bd.c aes-tables.c libbdtest.c
LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_LDLIBS     += -llog -ldl
LOCAL_CFLAGS	:=-std=c99
LOCAL_MODULE     := datahidingdemoreceiver

include $(BUILD_SHARED_LIBRARY) 
