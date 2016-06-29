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

package jni;

/**
 * @author Grégory Van den Borre
 */
public class OpenAlSoundEngineNative {


    /**
     * Initialize the engine in native code.
     *
     * @return The pointer address to the created object.
     */
    public static native long initialize();

    /**
     * Close the engine in native code.
     *
     * @param pointerAddress The pointer address to the native object(YZ::OpenAlEngine*)
     */
    public static native void close(final long pointerAddress);

    /**
     * Add the resource path to use with virtual file system.
     *
     * @param path Path to add.
     */
    public static native void addResourcePath(final String path);

    /**
     * Set the listener(player) position.
     *
     * @param address The pointer address to the native object(YZ::OpenAlEngine*)
     * @param x       Position X value.
     * @param y       Position Y value.
     * @param z       Position Z value.
     */
    public static native void setListenerPosition(final long address, final float x, final float y, final float z);

    /**
     * Set the listener(player) orientation.
     *
     * @param address The pointer address to the native object(YZ::OpenAlEngine*)
     * @param x       Direction X value.
     * @param y       Direction Y value.
     * @param z       Direction Z value.
     */
    public static native void setListenerOrientation(final long address, final float x, final float y, final float z);

    /**
     * Delete the object in native code.
     *
     * @param address Address of the native object.
     */
    public static native void delete(final long address);
}
