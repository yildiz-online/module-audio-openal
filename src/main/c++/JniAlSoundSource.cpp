/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2017 Grégory Van den Borre
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

#include "../includes/JniAlSoundSource.h"
#include "../includes/AlSoundSource.h"
#include "../includes/JniUtil.h"

/**
*@author Grégory Van den Borre
*/

JNIEXPORT jlong JNICALL Java_jni_ALSoundSourceNative_load(
    JNIEnv *env,
    jobject,
    jstring jfile) {
    const char* file = env->GetStringUTFChars(jfile, 0);
    try {
        yz::AlSoundSource* stream = new yz::AlSoundSource(file);
        env->ReleaseStringUTFChars(jfile, file);
        return reinterpret_cast<jlong>(stream);
    } catch (std::exception& e) {
        env->ReleaseStringUTFChars(jfile, file);
        throwException(env, e.what());
    }
    return -1L;
}

JNIEXPORT jlong JNICALL Java_jni_ALSoundSourceNative_loadFromVfs(
    JNIEnv *env,
    jobject,
    jstring jfile) {
    const char* file = env->GetStringUTFChars(jfile, 0);
    try {
        yz::AlSoundSource* stream = new yz::AlSoundSource(
                new yz::physfs(file));
        env->ReleaseStringUTFChars(jfile, file);
        return reinterpret_cast<jlong>(stream);
    } catch (std::exception& e) {
        env->ReleaseStringUTFChars(jfile, file);
        throwException(env, e.what());
    }
    return -1L;
}

JNIEXPORT void JNICALL Java_jni_ALSoundSourceNative_play(
    JNIEnv* env,
    jobject,
    jlong pointer) {
    try {
        yz::AlSoundSource* stream =
                reinterpret_cast<yz::AlSoundSource*>(pointer);
        stream->play();
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT jboolean JNICALL Java_jni_ALSoundSourceNative_update(
    JNIEnv* env,
    jobject,
    jlong pointer) {
    try {
        yz::AlSoundSource* stream =
                reinterpret_cast<yz::AlSoundSource*>(pointer);
        return stream->update();
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
    return 0;
}

JNIEXPORT void JNICALL Java_jni_ALSoundSourceNative_stop(
    JNIEnv*,
    jobject,
    jlong pointer) {
    yz::AlSoundSource* stream =
                    reinterpret_cast<yz::AlSoundSource*>(pointer);
    stream->stop();
}

JNIEXPORT void JNICALL Java_jni_ALSoundSourceNative_loop(
    JNIEnv*,
    jobject,
    jlong pointer) {
    yz::AlSoundSource* stream =
                    reinterpret_cast<yz::AlSoundSource*>(pointer);
    stream->loop();
}

JNIEXPORT void JNICALL Java_jni_ALSoundSourceNative_rewind(
    JNIEnv*,
    jobject,
    jlong pointer) {
    yz::AlSoundSource* stream =
                    reinterpret_cast<yz::AlSoundSource*>(pointer);
                    stream->rewind();
}

JNIEXPORT void JNICALL Java_jni_ALSoundSourceNative_setPosition(
    JNIEnv*,
    jobject,
    jlong pointer,
    jfloat x,
    jfloat y,
    jfloat z) {
    yz::AlSoundSource* stream =
                    reinterpret_cast<yz::AlSoundSource*>(pointer);
                    stream->setPosition(x, y, z);
}

JNIEXPORT jboolean JNICALL Java_jni_ALSoundSourceNative_isPlaying(
    JNIEnv*,
    jobject,
    jlong pointer) {
    yz::AlSoundSource* stream =
                    reinterpret_cast<yz::AlSoundSource*>(pointer);
                    stream->isPlaying();
}

