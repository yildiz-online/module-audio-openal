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

import be.yildiz.common.collections.Sets;
import be.yildiz.common.exeption.ResourceMissingException;
import be.yildiz.common.nativeresources.NativePointer;
import be.yildiz.common.resource.FileResource.FileType;
import be.yildiz.module.sound.EndPlayListener;
import be.yildiz.module.sound.StreamSource;
import jni.ALVorbisStreamNative;

import java.io.File;
import java.util.Set;

/**
 * OpenAl implementation for a vorbis streaming source.
 *
 * @author Grégory Van Den Borre
 */
public final class ALVorbisStream implements StreamSource, Runnable {

    /**
     * Pointer to the native object.
     */
    private final NativePointer pointer;

    /**
     * Listeners to notify when the source stop playing.
     */
    private final Set<EndPlayListener> endPlayListeners = Sets.newSet();

    /**
     * Thread running to play the sound.
     */
    private final Thread thread;

    /**
     * <code>true</code> if the sound is currently playing, <code>false</code>
     * otherwise.
     */
    private boolean playing;

    /**
     * Flag to check if the stream must still be player or stopped.
     */
    private boolean mustBeStopped;

    /**
     * Full constructor.
     *
     * @param file Sound file to load and play.
     * @param type Type of file to load.
     */
    public ALVorbisStream(final String file, final FileType type) {
        super();
        long address;
        if (type == FileType.VFS) {
            address = ALVorbisStreamNative.loadFromVfs(file);
        } else {
            if (!new File(file).exists()) {
                throw new ResourceMissingException(file + " does not exists.");
            }
            address = ALVorbisStreamNative.load(file);
        }
        this.pointer = NativePointer.create(address);
        this.thread = new Thread(this);
    }

    /**
     * Start playing the sound in a new thread. When the sound finishes playing,
     * the EndPlayListener are notified.
     */
    @Override
    public void play() {
        if (!this.playing) {
            this.mustBeStopped = false;
            this.thread.start();
        }
    }

    @Override
    public void run() {
        ALVorbisStreamNative.play(this.pointer.address);
        this.playing = true;
        while (!this.mustBeStopped) {
            this.playing = ALVorbisStreamNative.update(this.pointer.address);
            if (!this.playing) {
                for (EndPlayListener epl : this.endPlayListeners) {
                    epl.soundFinished();
                }
            }
        }
    }

    @Override
    public void addEndPlayListener(final EndPlayListener listener) {
        this.endPlayListeners.add(listener);
    }

    /**
     * Stop playing the sound.
     */
    @Override
    public synchronized void stop() {
        this.mustBeStopped = true;
        this.playing = false;
    }
}
