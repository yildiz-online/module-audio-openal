/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2019 Grégory Van den Borre
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
#include "../includes/AlSoundSource.hpp"
#include "../includes/JniUtil.h"

/**
 * Implementation for JniAlSoundSource.h
 *@author Grégory Van den Borre
*/

JNIEXPORT void JNICALL Java_jni_ALSoundSourceNative_play(JNIEnv* env, jobject o, jlong pointer) {
    LOG_FUNCTION
    try {
        yz::openal::SoundSource* stream = reinterpret_cast<yz::openal::SoundSource*>(pointer);
        stream->play();
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_jni_ALSoundSourceNative_stop(JNIEnv* env, jobject o, jlong pointer) {
    LOG_FUNCTION
    try {
        yz::openal::SoundSource* stream = reinterpret_cast<yz::openal::SoundSource*>(pointer);
        stream->stop();
    } catch (std::exception& e) {
        throwException(env, e.what());
    }
}

JNIEXPORT void JNICALL Java_jni_ALSoundSourceNative_loop(JNIEnv* env, jobject o, jlong pointer) {
    LOG_FUNCTION
    yz::openal::SoundSource* stream = reinterpret_cast<yz::openal::SoundSource*>(pointer);
    stream->loop();
}

JNIEXPORT void JNICALL Java_jni_ALSoundSourceNative_rewind(JNIEnv* env, jobject o, jlong pointer) {
    LOG_FUNCTION
    yz::openal::SoundSource* stream = reinterpret_cast<yz::openal::SoundSource*>(pointer);
    stream->rewind();
}

JNIEXPORT void JNICALL Java_jni_ALSoundSourceNative_setPosition(
        JNIEnv* env, jobject o, jlong pointer, jfloat x, jfloat y, jfloat z) {
    LOG_FUNCTION
    yz::AlSoundSource* stream = reinterpret_cast<yz::AlSoundSource*>(pointer);
    stream->setPosition(x, y, z);
}

JNIEXPORT jboolean JNICALL Java_jni_ALSoundSourceNative_isPlaying(JNIEnv* env, jobject o, jlong pointer) {
    LOG_FUNCTION
    yz::openal::SoundSource* stream = reinterpret_cast<yz::openal::SoundSource*>(pointer);
    stream->isPlaying();
}

JNIEXPORT void JNICALL Java_jni_ALSoundSourceNative_delete(JNIEnv* env, jobject o, jlong pointer) {
    LOG_FUNCTION
    yz::openal::SoundSource* stream = reinterpret_cast<yz::openal::SoundSource*>(pointer);
    delete stream;
}

JNIEXPORT void JNICALL Java_jni_ALSoundSourceNative_setGain(JNIEnv* env, jobject o, jlong pointer, jfloat gain) {
    LOG_FUNCTION
    yz::openal::SoundSource* stream = reinterpret_cast<yz::openal::SoundSource*>(pointer);
    stream->setGain(gain);
}

