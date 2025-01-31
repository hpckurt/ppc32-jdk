/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_sun_imageio_plugins_jpeg_JPEGImageReader */

#ifndef _Included_com_sun_imageio_plugins_jpeg_JPEGImageReader
#define _Included_com_sun_imageio_plugins_jpeg_JPEGImageReader
#ifdef __cplusplus
extern "C" {
#endif
#undef com_sun_imageio_plugins_jpeg_JPEGImageReader_WARNING_NO_EOI
#define com_sun_imageio_plugins_jpeg_JPEGImageReader_WARNING_NO_EOI 0L
#undef com_sun_imageio_plugins_jpeg_JPEGImageReader_WARNING_NO_JFIF_IN_THUMB
#define com_sun_imageio_plugins_jpeg_JPEGImageReader_WARNING_NO_JFIF_IN_THUMB 1L
#undef com_sun_imageio_plugins_jpeg_JPEGImageReader_WARNING_IGNORE_INVALID_ICC
#define com_sun_imageio_plugins_jpeg_JPEGImageReader_WARNING_IGNORE_INVALID_ICC 2L
#undef com_sun_imageio_plugins_jpeg_JPEGImageReader_MAX_WARNING
#define com_sun_imageio_plugins_jpeg_JPEGImageReader_MAX_WARNING 2L
#undef com_sun_imageio_plugins_jpeg_JPEGImageReader_UNKNOWN
#define com_sun_imageio_plugins_jpeg_JPEGImageReader_UNKNOWN -1L
#undef com_sun_imageio_plugins_jpeg_JPEGImageReader_MIN_ESTIMATED_PASSES
#define com_sun_imageio_plugins_jpeg_JPEGImageReader_MIN_ESTIMATED_PASSES 10L
/*
 * Class:     com_sun_imageio_plugins_jpeg_JPEGImageReader
 * Method:    initReaderIDs
 * Signature: (Ljava/lang/Class;Ljava/lang/Class;Ljava/lang/Class;)V
 */
JNIEXPORT void JNICALL Java_com_sun_imageio_plugins_jpeg_JPEGImageReader_initReaderIDs
  (JNIEnv *, jclass, jclass, jclass, jclass);

/*
 * Class:     com_sun_imageio_plugins_jpeg_JPEGImageReader
 * Method:    initJPEGImageReader
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_sun_imageio_plugins_jpeg_JPEGImageReader_initJPEGImageReader
  (JNIEnv *, jobject);

/*
 * Class:     com_sun_imageio_plugins_jpeg_JPEGImageReader
 * Method:    setSource
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_sun_imageio_plugins_jpeg_JPEGImageReader_setSource
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_sun_imageio_plugins_jpeg_JPEGImageReader
 * Method:    readImageHeader
 * Signature: (JZZ)Z
 */
JNIEXPORT jboolean JNICALL Java_com_sun_imageio_plugins_jpeg_JPEGImageReader_readImageHeader
  (JNIEnv *, jobject, jlong, jboolean, jboolean);

/*
 * Class:     com_sun_imageio_plugins_jpeg_JPEGImageReader
 * Method:    setOutColorSpace
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_com_sun_imageio_plugins_jpeg_JPEGImageReader_setOutColorSpace
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     com_sun_imageio_plugins_jpeg_JPEGImageReader
 * Method:    readImage
 * Signature: (IJ[BI[I[IIIIIII[Ljavax/imageio/plugins/jpeg/JPEGQTable;[Ljavax/imageio/plugins/jpeg/JPEGHuffmanTable;[Ljavax/imageio/plugins/jpeg/JPEGHuffmanTable;IIZ)Z
 */
JNIEXPORT jboolean JNICALL Java_com_sun_imageio_plugins_jpeg_JPEGImageReader_readImage
  (JNIEnv *, jobject, jint, jlong, jbyteArray, jint, jintArray, jintArray, jint, jint, jint, jint, jint, jint, jobjectArray, jobjectArray, jobjectArray, jint, jint, jboolean);

/*
 * Class:     com_sun_imageio_plugins_jpeg_JPEGImageReader
 * Method:    abortRead
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_sun_imageio_plugins_jpeg_JPEGImageReader_abortRead
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_sun_imageio_plugins_jpeg_JPEGImageReader
 * Method:    resetLibraryState
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_sun_imageio_plugins_jpeg_JPEGImageReader_resetLibraryState
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_sun_imageio_plugins_jpeg_JPEGImageReader
 * Method:    resetReader
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_sun_imageio_plugins_jpeg_JPEGImageReader_resetReader
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_sun_imageio_plugins_jpeg_JPEGImageReader
 * Method:    disposeReader
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_sun_imageio_plugins_jpeg_JPEGImageReader_disposeReader
  (JNIEnv *, jclass, jlong);

#ifdef __cplusplus
}
#endif
#endif
