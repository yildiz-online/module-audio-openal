/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 *  Copyright (c) 2019 Grégory Van den Borre
 *
 *  More infos available: https://engine.yildiz-games.be
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

package be.yildizgames.module.audio.openal;

import be.yildizgames.common.geometry.Point3D;
import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.module.audio.EndPlayListener;
import be.yildizgames.module.audio.SoundSource;
import jni.ALSoundSourceNative;

import java.util.HashSet;
import java.util.Set;

/**
 * OpenAl implementation for a source.
 *
 * @author Grégory Van Den Borre
 */
final class ALSoundSource implements SoundSource, Runnable {

    /**
     * Pointer to the native object.
     */
    private final NativePointer pointer;

    /**
     * Listeners to notify when the source stop playing.
     */
    private final Set<EndPlayListener> endPlayListeners = new HashSet<>();

    /**
     * Thread running to play the audio.
     */
    private final Thread thread;

    /**
     * <code>true</code> if the audio is currently playing, <code>false</code>
     * otherwise.
     */
    private boolean playing;

    ALSoundSource(final NativePointer pointer) {
        super();
        this.pointer = pointer;
        this.thread = new Thread(this);
    }

    /**
     * Start playing the audio in a specific thread. When the audio finishes playing,
     * the EndPlayListener are notified.
     * If the audio was previously played then stopped, it is rewind before starting.
     */
    @Override
    public void play() {
        if (!this.playing) {
            this.thread.start();
        } else {
            this.rewind();
        }
    }

    /**
     * Do not call this directly, this is used with an internal thread.
     */
    @Override
    public void run() {
        this.playing = true;
        ALSoundSourceNative.play(this.pointer.getPointerAddress());
        this.endPlayListeners.forEach(EndPlayListener::soundFinished);
        this.playing = false;
    }

    @Override
    public ALSoundSource addEndPlayListener(final EndPlayListener listener) {
        this.endPlayListeners.add(listener);
        return this;
    }

    /**
     * Stop playing the audio.
     */
    @Override
    public synchronized ALSoundSource stop() {
        this.playing = false;
        ALSoundSourceNative.stop(this.pointer.getPointerAddress());
        return this;
    }

    /**
     * @return true if the audio is playing or paused, false otherwise.
     */
    @Override
    public boolean isPlaying() {
        return ALSoundSourceNative.isPlaying(this.pointer.getPointerAddress());
    }

    /**
     * Set the audio position in the 3d space.
     *
     * @param pos New position.
     */
    @Override
    public ALSoundSource setPosition(Point3D pos) {
        ALSoundSourceNative.setPosition(this.pointer.getPointerAddress(), pos.x, pos.y, pos.z);
        return this;
    }

    /**
     * The audio will be played in loop until stop is called.
     */
    @Override
    public ALSoundSource loop() {
        ALSoundSourceNative.loop(this.pointer.getPointerAddress());
        return this;
    }

    /**
     * Reset the audio at its beginning.
     */
    @Override
    public ALSoundSource rewind() {
        ALSoundSourceNative.rewind(this.pointer.getPointerAddress());
        return this;
    }

    @Override
    public ALSoundSource setGain(final float gain) {
        ALSoundSourceNative.setGain(this.pointer.getPointerAddress(), gain);
        return this;
    }

    @Override
    public ALSoundSource delete() {
        ALSoundSourceNative.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
        return this;
    }
}
