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

#include "../includes/JniAlBuffer.h"
#include "../includes/AlBuffer.hpp"
#include "../includes/JniUtil.h"
#include "../includes/AlSoundSource.hpp"

/**
*@author Grégory Van den Borre
*/

JNIEXPORT jlong JNICALL Java_jni_ALBufferNative_load(JNIEnv *env, jobject, jstring jfile) {
    LOG_FUNCTION
    if(jfile == NULL) {
        throwException(env, "File is null.");
        return -1L;
    }
    const char* file = env->GetStringUTFChars(jfile, 0);
	try {
	    yz::AlBuffer* buffer = new yz::AlBuffer(file, 3);
	    env->ReleaseStringUTFChars(jfile, file);
	    return reinterpret_cast<jlong>(buffer);
    } catch(std::exception& e) {
        env->ReleaseStringUTFChars(jfile, file);
        throwException(env, e.what());
    }
    return -1L;
}

JNIEXPORT jlong JNICALL Java_jni_ALBufferNative_loadFromVfs(JNIEnv *env, jobject o, jstring jfile) {
    LOG_FUNCTION
    if(jfile == NULL) {
        throwException(env, "File is null.");
        return -1L;
    }
    const char* file = env->GetStringUTFChars(jfile, 0);
    try {
        yz::AlBuffer* buffer = new yz::AlBuffer(new yz::physfs(file), 3);
        env->ReleaseStringUTFChars(jfile, file);
        return reinterpret_cast<jlong>(buffer);
    } catch(std::exception& e) {
        env->ReleaseStringUTFChars(jfile, file);
        throwException(env, e.what());
    }
    return -1L;
}

JNIEXPORT jlong JNICALL Java_jni_ALBufferNative_createSource(JNIEnv*, jobject, jlong pointer) {
    LOG_FUNCTION
	yz::AlBuffer* buffer = reinterpret_cast<yz::AlBuffer*>(pointer);
	return reinterpret_cast<jlong>(new yz::AlSoundSource(buffer));
}