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

#include "../includes/AlutAlBuffer.h"
#include "alut.h"
#include "../includes/OpenAlException.h"

/**
*@author Grégory Van den Borre
*/

YZ::AlutAlBuffer::AlutAlBuffer(YZ::physfs* file) {
    /*this->number = 1;
     SF_INFO fileInfo;
        SF_VIRTUAL_IO io;
        io.get_filelen = &YZ::AlBuffer::Stream::getLength;
        io.read        = &YZ::AlBuffer::Stream::read;
        io.seek        = &YZ::AlBuffer::Stream::seek;
        io.tell        = &YZ::AlBuffer::Stream::tell;

        this->soundFile = sf_open_virtual(&io, SFM_READ, &fileInfo, file);
        if (!soundFile) {
            throw new OpenAlException("Error opening file");
        }
        this->sampleRate = fileInfo.samplerate;
        this->channelsCount = fileInfo.channels;
        this->nbSamples = this->sampleRate * this->channelsCount;
        switch (this->channelsCount) {
        case 1:
            this->format = AL_FORMAT_MONO16;
            break;
        case 2:
            this->format = AL_FORMAT_STEREO16;
            break;
        default:
            this->format = 0;
            break;
        }
        this->buffer = new ALuint[this->number];
        alGenBuffers(this->number, this->buffer);*/
}

YZ::AlutAlBuffer::AlutAlBuffer(const char* file) {
    this->buffer = alutCreateBufferFromFile(file);
    ALenum error = alutGetError();
    if(error != ALUT_ERROR_NO_ERROR) {
        throw OpenAlException("Error loading file.");
    }
}

YZ::AlutAlBuffer::~AlutAlBuffer() {
}
