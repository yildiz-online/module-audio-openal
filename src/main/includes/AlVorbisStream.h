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

#ifndef _AL_VORBIS_STREAM_H_
#define _AL_VORBIS_STREAM_H_

#include "StbAlBuffer.h"
#include "OpenAlException.h"

#include <al.h>

namespace YZ {

/**
* @author Grégory Van den Borre
*/
class AlVorbisStream
{
public:

    /**
     * Create a new stream, initialize the sound from a given file path.
     * @param file Sound path name.
     */
    AlVorbisStream(const char* file);

    /**
     * Create a new stream, initialize the sound from a virtual file system.
     * @param file Sound path name in the virtual file system.
     */
    AlVorbisStream(YZ::physfs* file);

    ~AlVorbisStream();

    bool play();

    void close();

    bool update();

private :

    static int const BUFFER_NUMBER = 3;

    bool stream(ALuint buffer);

    void empty();

    bool playBack();

    bool isPlaying();

    void initialize(StbAlBuffer* buffer);

    /**
     * Check openAl state if an error occured.
     * @throw An OpenAlException if an error occured.
     */
    inline void check() {
        int error = alGetError();
        if (error != AL_NO_ERROR) {
            throw OpenAlException(error);
        }
    }


    StbAlBuffer* buffer;

    ALuint source;
};
};

#endif
