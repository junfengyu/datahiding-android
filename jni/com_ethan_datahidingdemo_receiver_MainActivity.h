/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_ethan_datahidingdemo_receiver_MainActivity */

#ifndef _Included_com_ethan_datahidingdemo_receiver_MainActivity
#define _Included_com_ethan_datahidingdemo_receiver_MainActivity
#ifdef __cplusplus
extern "C" {
#endif
#undef com_ethan_datahidingdemo_receiver_MainActivity_MODE_PRIVATE
#define com_ethan_datahidingdemo_receiver_MainActivity_MODE_PRIVATE 0L
#undef com_ethan_datahidingdemo_receiver_MainActivity_MODE_WORLD_READABLE
#define com_ethan_datahidingdemo_receiver_MainActivity_MODE_WORLD_READABLE 1L
#undef com_ethan_datahidingdemo_receiver_MainActivity_MODE_WORLD_WRITEABLE
#define com_ethan_datahidingdemo_receiver_MainActivity_MODE_WORLD_WRITEABLE 2L
#undef com_ethan_datahidingdemo_receiver_MainActivity_MODE_APPEND
#define com_ethan_datahidingdemo_receiver_MainActivity_MODE_APPEND 32768L
#undef com_ethan_datahidingdemo_receiver_MainActivity_MODE_MULTI_PROCESS
#define com_ethan_datahidingdemo_receiver_MainActivity_MODE_MULTI_PROCESS 4L
#undef com_ethan_datahidingdemo_receiver_MainActivity_MODE_ENABLE_WRITE_AHEAD_LOGGING
#define com_ethan_datahidingdemo_receiver_MainActivity_MODE_ENABLE_WRITE_AHEAD_LOGGING 8L
#undef com_ethan_datahidingdemo_receiver_MainActivity_BIND_AUTO_CREATE
#define com_ethan_datahidingdemo_receiver_MainActivity_BIND_AUTO_CREATE 1L
#undef com_ethan_datahidingdemo_receiver_MainActivity_BIND_DEBUG_UNBIND
#define com_ethan_datahidingdemo_receiver_MainActivity_BIND_DEBUG_UNBIND 2L
#undef com_ethan_datahidingdemo_receiver_MainActivity_BIND_NOT_FOREGROUND
#define com_ethan_datahidingdemo_receiver_MainActivity_BIND_NOT_FOREGROUND 4L
#undef com_ethan_datahidingdemo_receiver_MainActivity_BIND_ABOVE_CLIENT
#define com_ethan_datahidingdemo_receiver_MainActivity_BIND_ABOVE_CLIENT 8L
#undef com_ethan_datahidingdemo_receiver_MainActivity_BIND_ALLOW_OOM_MANAGEMENT
#define com_ethan_datahidingdemo_receiver_MainActivity_BIND_ALLOW_OOM_MANAGEMENT 16L
#undef com_ethan_datahidingdemo_receiver_MainActivity_BIND_WAIVE_PRIORITY
#define com_ethan_datahidingdemo_receiver_MainActivity_BIND_WAIVE_PRIORITY 32L
#undef com_ethan_datahidingdemo_receiver_MainActivity_BIND_IMPORTANT
#define com_ethan_datahidingdemo_receiver_MainActivity_BIND_IMPORTANT 64L
#undef com_ethan_datahidingdemo_receiver_MainActivity_BIND_ADJUST_WITH_ACTIVITY
#define com_ethan_datahidingdemo_receiver_MainActivity_BIND_ADJUST_WITH_ACTIVITY 128L
#undef com_ethan_datahidingdemo_receiver_MainActivity_CONTEXT_INCLUDE_CODE
#define com_ethan_datahidingdemo_receiver_MainActivity_CONTEXT_INCLUDE_CODE 1L
#undef com_ethan_datahidingdemo_receiver_MainActivity_CONTEXT_IGNORE_SECURITY
#define com_ethan_datahidingdemo_receiver_MainActivity_CONTEXT_IGNORE_SECURITY 2L
#undef com_ethan_datahidingdemo_receiver_MainActivity_CONTEXT_RESTRICTED
#define com_ethan_datahidingdemo_receiver_MainActivity_CONTEXT_RESTRICTED 4L
#undef com_ethan_datahidingdemo_receiver_MainActivity_RESULT_CANCELED
#define com_ethan_datahidingdemo_receiver_MainActivity_RESULT_CANCELED 0L
#undef com_ethan_datahidingdemo_receiver_MainActivity_RESULT_OK
#define com_ethan_datahidingdemo_receiver_MainActivity_RESULT_OK -1L
#undef com_ethan_datahidingdemo_receiver_MainActivity_RESULT_FIRST_USER
#define com_ethan_datahidingdemo_receiver_MainActivity_RESULT_FIRST_USER 1L
#undef com_ethan_datahidingdemo_receiver_MainActivity_DEFAULT_KEYS_DISABLE
#define com_ethan_datahidingdemo_receiver_MainActivity_DEFAULT_KEYS_DISABLE 0L
#undef com_ethan_datahidingdemo_receiver_MainActivity_DEFAULT_KEYS_DIALER
#define com_ethan_datahidingdemo_receiver_MainActivity_DEFAULT_KEYS_DIALER 1L
#undef com_ethan_datahidingdemo_receiver_MainActivity_DEFAULT_KEYS_SHORTCUT
#define com_ethan_datahidingdemo_receiver_MainActivity_DEFAULT_KEYS_SHORTCUT 2L
#undef com_ethan_datahidingdemo_receiver_MainActivity_DEFAULT_KEYS_SEARCH_LOCAL
#define com_ethan_datahidingdemo_receiver_MainActivity_DEFAULT_KEYS_SEARCH_LOCAL 3L
#undef com_ethan_datahidingdemo_receiver_MainActivity_DEFAULT_KEYS_SEARCH_GLOBAL
#define com_ethan_datahidingdemo_receiver_MainActivity_DEFAULT_KEYS_SEARCH_GLOBAL 4L
#undef com_ethan_datahidingdemo_receiver_MainActivity_USE_OAUTH1
#define com_ethan_datahidingdemo_receiver_MainActivity_USE_OAUTH1 0L
#undef com_ethan_datahidingdemo_receiver_MainActivity_NEW_PICTURE
#define com_ethan_datahidingdemo_receiver_MainActivity_NEW_PICTURE 1L
/*
 * Class:     com_ethan_datahidingdemo_receiver_MainActivity
 * Method:    SteganographyDecode
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_ethan_datahidingdemo_1receiver_MainActivity_SteganographyDecode
  (JNIEnv *, jobject, jstring);


JNIEXPORT jint JNICALL Java_com_ethan_datahidingdemo_1receiver_MainActivity_SteganographyFileDecode
  (JNIEnv *, jobject, jstring);


/*
 * Class:     com_ethan_datahidingdemo_receiver_MainActivity
 * Method:    nativeEncrypt
 * Signature: (Ljava/lang/String;Ljava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_ethan_datahidingdemo_1receiver_MainActivity_nativeEncrypt
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     com_ethan_datahidingdemo_receiver_MainActivity
 * Method:    nativeDecrypt
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jint JNICALL Java_com_ethan_datahidingdemo_1receiver_MainActivity_nativeDecrypt
  (JNIEnv *, jobject, jstring, jstring);


JNIEXPORT jint JNICALL Java_com_ethan_datahidingdemo_1receiver_MainActivity_nativeBinaryDecrypt
  (JNIEnv *, jobject, jstring, jstring);

#ifdef __cplusplus
}
#endif
#endif
