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

#ifndef _ALUT_AL_BUFFER_H_
#define _ALUT_AL_BUFFER_H_

#include <al.h>
#include <alc.h>

#include "wrapperphysfs.hpp"

namespace YZ {

    /**
    * Create and wrap an OpenAL buffer object.
    * @author Grégory Van Den Borre
    */
    class AlutAlBuffer {

    public:

        /**
        * Full constructor, load a sound file to create the buffer.
        * @param file Path of the file to load.
        * @param number Number of buffers to use.
        */
        AlutAlBuffer(const char* file);

        AlutAlBuffer(YZ::physfs* file);

        /**
        * Destructor.
        */
        ~AlutAlBuffer();

        /**
        * @return The wrapped buffer value.
        */
        inline ALuint getBuffer() const {
            return this->buffer;
        }

    private:

        /**
        * Wrapped buffer value.
        */
        ALuint buffer;

        ALsizei alBufferLen;

        ALsizei nbSamples;

        ALuint channelsCount;

        /**
         * Sound format: mono, stereo...
         */
        ALenum format;

	int channels;

        unsigned int sampleRate;
    };
};

#endif
