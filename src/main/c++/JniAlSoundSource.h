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

#include <jni.h>

#ifndef _JNI_AL_VORBIS_STREAM_H_
#define _JNI_AL_VORBIS_STREAM_H_

/**
 * JNI interface for a yz::AlSoundSource.
*@author Grégory Van den Borre
*/
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @param env Environment provided by the JVM.
 * @param object Associated object, never used for performance reason.
 * @param jfile Path of the file to load from the file system.
 * @return The pointer of the loaded yz::AlSoundSource.
 * @throw A NativeException if an error occurred.
 */
JNIEXPORT jlong JNICALL Java_jni_ALSoundSourceNative_load(JNIEnv* env, jobject object, jstring jfile);

/**
 * @param env Environment provided by the JVM.
 * @param object Associated object, never used for performance reason.
 * @param jfile Path of the file to load from the virtual file system.
 * @return The pointer of the loaded yz::AlSoundSource.
 * @throw A NativeException if an error occurred.
 */
JNIEXPORT jlong JNICALL Java_jni_ALSoundSourceNative_loadFromVfs(JNIEnv* env, jobject object, jstring jfile);

/**
 * Start playing a sound source.
 * @param env Environment provided by the JVM.
 * @param object Associated object, never used for performance reason.
 * @param pointer Pointer of a yz::AlSoundSource to be used.
 * @throw A NativeException if an error occurred.
 */
JNIEXPORT void JNICALL Java_jni_ALSoundSourceNative_play(JNIEnv* env, jobject object, jlong pointer);

/**
 * Update the state of a sound source.
 * @param env Environment provided by the JVM.
 * @param object Associated object, never used for performance reason.
 * @param pointer Pointer of a yz::AlSoundSource to be used.
 * @return True if the file is still to be read, false otherwise.
 * @throw A NativeException if an error occurred.
 */
JNIEXPORT jboolean JNICALL Java_jni_ALSoundSourceNative_update(JNIEnv* env, jobject object, jlong pointer);

/**
 * Stop playing a sound source.
 * @param env Environment provided by the JVM.
 * @param object Associated object, never used for performance reason.
 * @param pointer Pointer of a yz::AlSoundSource to be used.
 * @throw A NativeException if an error occurred.
 */
JNIEXPORT void JNICALL Java_jni_ALSoundSourceNative_stop(JNIEnv* env, jobject o, jlong pointer);

/**
 * Set a sound source to restart once completed.
 * @param env Environment provided by the JVM.
 * @param object Associated object, never used for performance reason.
 * @param pointer Pointer of a yz::AlSoundSource to be used.
 */
JNIEXPORT void JNICALL Java_jni_ALSoundSourceNative_loop(JNIEnv* env, jobject o, jlong pointer);

/**
 * Set a sound source to restart at the beginning.
 * @param env Environment provided by the JVM.
 * @param object Associated object, never used for performance reason.
 * @param pointer Pointer of a yz::AlSoundSource to be used.
 */
JNIEXPORT void JNICALL Java_jni_ALSoundSourceNative_rewind(JNIEnv* env, jobject o, jlong pointer);

/**
 * Set a sound source position.
 * @param env Environment provided by the JVM.
 * @param object Associated object, never used for performance reason.
 * @param pointer Pointer of a yz::AlSoundSource to be used.
 * @param x Source new X position.
 * @param y Source new Y position.
 * @param z Source new Z position.
 */
JNIEXPORT void JNICALL Java_jni_ALSoundSourceNative_setPosition(
        JNIEnv* env, jobject o, jlong pointer, jfloat x, jfloat y, jfloat z);

/**
 * Check if a sound source is currently playing.
 * @param env Environment provided by the JVM.
 * @param object Associated object, never used for performance reason.
 * @param pointer Pointer of a yz::AlSoundSource to be used.
 * @return True if the sound source is playing, false otherwise.
 */
JNIEXPORT jboolean JNICALL Java_jni_ALSoundSourceNative_isPlaying(JNIEnv* env, jobject o, jlong pointer);

#ifdef __cplusplus
}
#endif
#endif
