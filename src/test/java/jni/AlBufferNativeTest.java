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

package jni;

import be.yildiz.module.sound.openal.OpenAlAudioEngine;
import be.yildizgames.common.exception.technical.NativeException;
import be.yildizgames.common.nativeresources.NativeResourceLoader;
import be.yildizgames.common.nativeresources.SystemLinux64;
import be.yildizgames.common.nativeresources.SystemWin64;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Nested;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertThrows;

/**
 * @author Grégory Van den Borre
 */
@Disabled
class AlBufferNativeTest {

    @Nested
    class Load {

        @BeforeEach
        void init() {
            initEngine();
        }

        @Test
        void happyFlow() {

        }

        @Test
        void fileNotExisting() {
            assertThrows(NativeException.class, () -> ALBufferNative.load(""));
        }

        @Test
        void withNull() {
            assertThrows(NativeException.class, () -> ALBufferNative.load(null));
        }
    }

    @Nested
    class LoadFromVfs {

        @BeforeEach
        void init() {
            initEngine();
        }

        @Test
        void happyFlow() {

        }

        @Test//(expected = NativeException.class)
        void vfsNotMounted() {

        }

        @Test//(expected = NativeException.class)
        void fileNotExisting() {
        }

        @Test
        void withNull() {
            assertThrows(NativeException.class, () -> ALBufferNative.loadFromVfs(null));
        }

    }

    @Nested
    class CreateSource {

        @BeforeEach
        void init() {
            initEngine();
        }

        @Test
        void happyFlow() {

        }

        @Test
        void withInvalidBuffer() {

        }
    }

    private static void initEngine() {
        try {
            OpenAlAudioEngine.create(NativeResourceLoader.inTestPath(new SystemLinux64(), new SystemWin64()));
        } catch (NativeException e) {
            //An exception is thrown on system without sound card, anyway, loading the engine is enough
        }
    }
}
