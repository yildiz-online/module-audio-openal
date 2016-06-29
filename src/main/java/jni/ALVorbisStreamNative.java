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
public class ALVorbisStreamNative {

    /**
     * Load the file in the openAL native code.
     *
     * @param file Path to the file to load.
     * @return The native address pointer.
     */
    public static native long load(final String file);

    /**
     * Load the virtual file in the openAL native code.
     *
     * @param file Path to the virtual file to load.
     * @return The native address pointer.
     */
    public static native long loadFromVfs(final String file);

    /**
     * Start playing the file.
     *
     * @param pointerAddress Address to the native object.
     * @return <code>true</code> if the sound is playing.
     */
    public static native boolean play(final long pointerAddress);

    /**
     * Update the stream status in native code.
     *
     * @param pointerAddress Address to the native object.
     * @return <code>true</code> if the sound is playing.
     */
    public static native boolean update(final long pointerAddress);
}
