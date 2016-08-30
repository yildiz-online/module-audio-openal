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

#ifndef _AL_BUFFER_H_
#define _AL_BUFFER_H_

#include <AL/al.h>
#include <AL/alc.h>
extern "C" {
    #include <sndfile.h>
}
#include "wrapperphysfs.hpp"

namespace YZ {

    /**
    * Create and wrap an OpenAL buffer object.
    * @author Van Den Borre Grégory
    */
    class AlBuffer {

    public:

        /**
        * Full constructor, load a sound file to create the buffer.
        * @param file Path of the file to load.
        * @param number Number of buffers to use.
        */
        AlBuffer(const char* file, const int number);

        AlBuffer(YZ::physfs* file, const int number);

        /**
        * Destructor.
        */
        ~AlBuffer();

        bool read(const int bufferNumber);

        bool readIndex(const int bufferIndex);

        /**
        * @return The wrapped buffer value.
        */
        inline ALuint* getBuffer() const {
            return this->buffer;
        }

        inline int getNumber() const {
            return this->number;
        }

        inline void sourceQueue(const ALuint source) {
            alSourceQueueBuffers(source, this->number, this->buffer);
        }

    private:

        /**
        * Wrapped buffer value.
        */
        ALuint* buffer;

        /**
         * Number of buffer to use.
         */
        int number;

        ALsizei nbSamples;

        ALsizei sampleRate;

        ALuint channelsCount;

        /**
         * Sound format: mono, stereo...
         */
        ALenum format;

        /**
         * File to play.
        */
        SNDFILE* soundFile;

        struct Stream {
            static sf_count_t getLength(void* user);
            static sf_count_t read(void* ptr, sf_count_t count, void* user);
            static sf_count_t seek(sf_count_t offset, int whence, void* user);
            static sf_count_t tell(void* user);
        };
    };
};

#endif
