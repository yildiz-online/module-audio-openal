//        This file is part of the Yildiz-Online project, licenced under the MIT License
//        (MIT)
//
//        Copyright (c) 2016 Grégory Van den Borre
//
//        More infos available: http://yildiz.bitbucket.org
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
//        of this software and associated documentation files (the "Software"), to deal
//        in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
//        furnished to do so, subject to the following conditions:
//
//        The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
//        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//        SOFTWARE.

package be.yildiz.module.sound.openal;

import be.yildiz.common.nativeresources.NativePointer;
import be.yildiz.common.vector.Point3D;
import be.yildiz.module.sound.SoundSource;
import jni.ALSourceNative;

/**
 * OpenAl implementation for a SoundSource. A Source is a sound built from a
 * buffer.
 *
 * @author Grégory Van den Borre
 */
final class AlSource implements SoundSource {

    /**
     * Pointer to the native YZ::Source* object.
     */
    private final NativePointer pointer;

    /**
     * Full constructor.
     *
     * @param nativePointerAddress Address of the associated native object.
     */
    AlSource(final NativePointer nativePointerAddress) {
        this.pointer = nativePointerAddress;
    }

    /**
     * Start playing the sound.
     */
    @Override
    public void play() {
        ALSourceNative.play(this.pointer.address);
    }

    @Override
    public void stop() {
        ALSourceNative.stop(this.pointer.address);
    }

    @Override
    public boolean isPlaying() {
        return ALSourceNative.isPlaying(this.pointer.address);
    }

    @Override
    public void setPosition(final Point3D pos) {
        ALSourceNative.setPosition(this.pointer.address, pos.x, pos.y, pos.z);
    }

    @Override
    public void loop() {
        ALSourceNative.loop(this.pointer.address);
    }

    @Override
    public void rewind() {
        ALSourceNative.rewind(this.pointer.address);
    }

}
