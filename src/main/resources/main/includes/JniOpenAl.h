/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2018 Grégory Van den Borre
 *
 * More infos available: https://www.yildiz-games.be
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without
 * limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT  HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  SOFTWARE.
 */

#include <jni.h>

#ifndef _JNI_OPENAL_H_
#define _JNI_OPENAL_H_

#define TYPE yz::OpenAlEngine
#define GET_POINTER reinterpret_cast <TYPE*>(pointer)

#ifdef __cplusplus
extern "C" {
#endif

/**
*@author Grégory Van den Borre
*/

/**
 * Call the openAl engine initialization.
 * @param env JNI environment.
 * @param object Unused.
 * @throw NativeException if initialization failed.
 * @return A pointer to the created and initialized engine.
 */
JNIEXPORT jlong JNICALL Java_jni_OpenAlSoundEngineNative_initialize(JNIEnv *env, jobject object);

/**
 * Set the engine listener position.
 * @param env JNI environment.
 * @param object Unused.
 * @param pointer Engine pointer.
 * @param x Listener new X position value.
 * @param y Listener new Y position value.
 * @param z Listener new Z position value.
 */
JNIEXPORT void JNICALL Java_jni_OpenAlSoundEngineNative_setListenerPosition(
    JNIEnv *env,
    jobject object,
    jlong pointer,
    jfloat x,
    jfloat y,
    jfloat z);

JNIEXPORT void JNICALL Java_jni_OpenAlSoundEngineNative_setListenerOrientation(
    JNIEnv *env,
    jobject object,
    jlong pointer,
    jfloat x,
    jfloat y,
    jfloat z);

/**
 * Close the engine.
 * @param env JNI environment.
 * @param object Unused.
 * @param pointer Engine pointer.
 */
JNIEXPORT void JNICALL Java_jni_OpenAlSoundEngineNative_close(
    JNIEnv *env,
    jobject object,
    jlong pointer);

#ifdef __cplusplus
}
#endif
#endif
