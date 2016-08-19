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

#include "../includes/AlBuffer.h"
#include "../includes/OpenAlException.h"

/**
*@author Grégory Van den Borre
*/

YZ::AlBuffer::AlBuffer(YZ::physfs* file, const int number) {
    this->number = number;
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
        alGenBuffers(this->number, this->buffer);
}

YZ::AlBuffer::AlBuffer(const char* file, const int number) {
    this->number = number;
    SF_INFO fileInfo;

    this->soundFile = sf_open(file, SFM_READ, &fileInfo);
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
    alGenBuffers(this->number, this->buffer);
}

YZ::AlBuffer::~AlBuffer() {
    alDeleteBuffers(this->number, this->buffer);
}

bool YZ::AlBuffer::readIndex(const int bufferIndex) {
    ALshort samples[nbSamples];
        ALsizei read(
                static_cast<ALsizei>(sf_read_short(this->soundFile, samples,
                        this->nbSamples)));
        ALsizei size = read * sizeof(short);
        if (size == 0) {
            return false;
        }
        alBufferData(bufferIndex, this->format, samples, size,
                this->sampleRate);
        return true;
}

bool YZ::AlBuffer::read(const int bufferNumber) {
    return this->readIndex(this->buffer[bufferNumber]);
}

sf_count_t YZ::AlBuffer::Stream::getLength(void* userData) {
    YZ::physfs* stream = static_cast<YZ::physfs*>(userData);
    return stream->getSize();
}

sf_count_t  YZ::AlBuffer::Stream::read(void* ptr, sf_count_t count, void* userData) {
    YZ::physfs* stream = static_cast<YZ::physfs*>(userData);
    return stream->read(reinterpret_cast<char*>(ptr), count);
}

sf_count_t YZ::AlBuffer::Stream::seek(sf_count_t offset, int whence, void* userData) {
        YZ::physfs* stream = static_cast<YZ::physfs*>(userData);
    switch (whence) {
        case SEEK_SET : return stream->seek(offset);
        case SEEK_CUR : return stream->seek(stream->tell() + offset);
        case SEEK_END : return stream->seek(stream->getSize() - offset);
        default       : return stream->seek(0);
    }
}

sf_count_t YZ::AlBuffer::Stream::tell(void* userData) {
    YZ::physfs* stream = static_cast<YZ::physfs*>(userData);
    return stream->tell();
}
