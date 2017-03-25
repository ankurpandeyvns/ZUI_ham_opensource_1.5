# ZUK wangwq14 add 2015-12-01

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)


LOCAL_SRC_FILES := md5.c sha1.c sha2.c rsa.c bignum.c verfiy.c

LOCAL_C_INCLUDES += $(LOCAL_PATH)

LOCAL_CFLAGS := 

LOCAL_STATIC_LIBRARIES += libc 

LOCAL_MODULE := libpolarssl

include $(BUILD_STATIC_LIBRARY)

