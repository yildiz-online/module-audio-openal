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

/**
 * @author Grégory Van den Borre
 */
public class ALSoundSourceNative {

    private ALSoundSourceNative() {
        super();
    }

    /**
     * Start playing the file.
     *
     * @param pointerAddress Address to the native object.
     */
    public static native void play(final long pointerAddress);

    /**
     * Stop playing the file.
     *
     * @param pointerAddress Address to the native object.
     */
    public static native void stop(final long pointerAddress);

    /**
     * Call the native code to play the sound in loop.
     *
     * @param pointerAddress The pointer address to the native object(yz::AlSource*).
     */
    public static native void loop(final long pointerAddress);

    /**
     * Call the native code to set the sound position.
     *
     * @param pointerAddress The pointer address to the native object(yz::AlSource*).
     * @param posX           Sound position X value.
     * @param posY           Sound position Y value.
     * @param posZ           Sound position Z value.
     */
    public static native void setPosition(final long pointerAddress, final float posX, final float posY, final float posZ);

    /**
     * Check in native code if the source is currently playing.
     *
     * @param pointerAddress The pointer address to the native object(yz::AlSource*).
     * @return <code>true</code> if the source is currently playing,
     * <code>false</code> otherwise.
     */
    public static native boolean isPlaying(final long pointerAddress);

    /**
     * Call the native code to restart the sound at the beginning.
     *
     * @param pointerAddress The pointer address to the native object(yz::AlSource*).
     */
    public static native void rewind(final long pointerAddress);

    public static native void setGain(final long pointerAddress, final float gain);

    public static native void delete(final long pointerAddress);
}