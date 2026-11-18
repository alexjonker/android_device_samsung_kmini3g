LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES := strdup16.c
LOCAL_MODULE := libshim_secril
LOCAL_MODULE_TAGS := optional
LOCAL_VENDOR_MODULE := true
LOCAL_MULTILIB := 32
include $(BUILD_SHARED_LIBRARY)
