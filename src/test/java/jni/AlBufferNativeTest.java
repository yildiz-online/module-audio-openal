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

import be.yildiz.common.exeption.NativeException;
import be.yildiz.common.log.Logger;
import be.yildiz.common.nativeresources.NativeResourceLoader;
import be.yildiz.common.nativeresources.SystemLinux64;
import be.yildiz.common.nativeresources.SystemWin32;
import be.yildiz.module.sound.openal.OpenAlSoundEngine;
import org.junit.Before;
import org.junit.Test;
import org.junit.experimental.runners.Enclosed;
import org.junit.runner.RunWith;

/**
 * @author Grégory Van den Borre
 */
@RunWith(Enclosed.class)
public class AlBufferNativeTest {

    public static class Load {

        @Before
        public void init() {
            Logger.disable();
            new OpenAlSoundEngine(NativeResourceLoader.inTestPath(new SystemLinux64(), new SystemWin32()));
        }

        @Test
        public void happyFlow() {

        }

        @Test(expected = NativeException.class)
        public void fileNotExisting() {

            ALBufferNative.load("");
        }

        @Test(expected = NativeException.class)
        public void withNull() {
            ALBufferNative.load(null);
        }
    }

    public static class LoadFromVfs {

        @Before
        public void init() {
            Logger.disable();
            new OpenAlSoundEngine(NativeResourceLoader.inTestPath(new SystemLinux64(), new SystemWin32()));
        }

        @Test
        public void happyFlow() {

        }

        @Test//(expected = NativeException.class)
        public void vfsNotMounted() {

        }

        @Test//(expected = NativeException.class)
        public void fileNotExisting() {
        }

        @Test(expected = NativeException.class)
        public void withNull() {
            ALBufferNative.loadFromVfs(null);
        }

    }

    public static class CreateSource {

        @Before
        public void init() {
            Logger.disable();
            new OpenAlSoundEngine(NativeResourceLoader.inTestPath(new SystemLinux64(), new SystemWin32()));
        }

        @Test
        public void happyFlow() {

        }

        @Test
        public void withInvalidBuffer() {

        }
    }
}
