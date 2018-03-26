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

#include "../includes/JniOpenAl.h"
#include "../includes/JniUtil.h"
#include "../includes/OpenAlEngine.hpp"

/**
*@author Grégory Van den Borre
*/

JNIEXPORT jlong JNICALL Java_jni_OpenAlSoundEngineNative_initialize(JNIEnv *env, jobject) {
    try {
        return reinterpret_cast<jlong>(new TYPE());
    } catch (yz::OpenAlException& e) {
        throwException(env, e.what());
    }
    return -1L;
}

JNIEXPORT void JNICALL Java_jni_OpenAlSoundEngineNative_addResourcePath(JNIEnv *env, jobject, jstring jpath) {
    const char* path = env->GetStringUTFChars(jpath, 0);
    PHYSFS_mount(path, NULL, true);
    env->ReleaseStringUTFChars(jpath, path);
    const char* error = PHYSFS_getLastError();
}

JNIEXPORT void JNICALL Java_jni_OpenAlSoundEngineNative_setListenerPosition(
    JNIEnv *env,
    jobject object,
    jlong pointer,
    jfloat x,
    jfloat y,
    jfloat z) {
    GET_POINTER->setListenerPosition(x, y, z);
}

JNIEXPORT void JNICALL Java_jni_OpenAlSoundEngineNative_setListenerOrientation(
    JNIEnv *env,
    jobject object,
    jlong pointer,
    jfloat x,
    jfloat y,
    jfloat z) {
}

JNIEXPORT void JNICALL Java_jni_OpenAlSoundEngineNative_close(JNIEnv*, jobject, jlong pointer) {
    delete GET_POINTER;
}
