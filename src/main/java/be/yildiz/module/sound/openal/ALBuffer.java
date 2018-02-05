/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 *  Copyright (c) 2018 Grégory Van den Borre
 *
 *  More infos available: https://www.yildiz-games.be
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 *  documentation files (the "Software"), to deal in the Software without restriction, including without
 *  limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 *  of the Software, and to permit persons to whom the Software is furnished to do so,
 *  subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or substantial
 *  portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *  WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 *  OR COPYRIGHT  HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  SOFTWARE.
 *
 */

package be.yildiz.module.sound.openal;

import be.yildiz.module.sound.AudioFile;
import be.yildiz.module.sound.SoundSource;
import be.yildizgames.common.nativeresources.NativePointer;
import jni.ALBufferNative;

/**
 * A buffer is the data loaded from a file to create OpenAL sources.
 *
 * @author Grégory Van den Borre
 */
final class ALBuffer {

    /**
     * Pointer to the native yz::AlBuffer* object.
     */
    private final NativePointer pointer;

    /**
     * Full constructor, build a buffer from a file.
     *
     * @param file File to load, must be wav format.
     * @param type Type of file to load.
     */
    ALBuffer(final AudioFile file) {
        super();
        long address;
        if (file.isVfs()) {
            address = ALBufferNative.loadFromVfs(file.name);
        } else {
            address = ALBufferNative.load(file.name);
        }
        this.pointer = NativePointer.create(address);
    }

    /**
     * Build a new source from the buffer.
     * Ensures return != null.
     * @return The built sound source.
     */
    SoundSource createSource() {
        NativePointer sourcePointer = NativePointer.create(ALBufferNative.createSource(this.pointer.getPointerAddress()));
        return new ALSoundSource(sourcePointer);
    }
}