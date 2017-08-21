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

#include <vector>
#include "AlBuffer.h"
#include "OpenAlException.h"
#include "OpenAlFileLoadingException.h"

/**
*@author Grégory Van den Borre
*/

yz::AlBuffer::AlBuffer(yz::physfs* file, const int number) : this->number(number) {
    LOG_FUNCTION
    SF_INFO fileInfo;
    SF_VIRTUAL_IO io;
    io.get_filelen = &yz::AlBuffer::Stream::getLength;
    io.read = &yz::AlBuffer::Stream::read;
    io.seek = &yz::AlBuffer::Stream::seek;
    io.tell = &yz::AlBuffer::Stream::tell;
    this->soundFile = sf_open_virtual(&io, SFM_READ, &fileInfo, file);
    this->init(fileInfo);
}

yz::AlBuffer::AlBuffer(const char* file, const int number) : this->number(number) {
    LOG_FUNCTION
    SF_INFO fileInfo;
    this->soundFile = sf_open(file, SFM_READ, &fileInfo);
    this->init(fileInfo);
}

void yz::AlBuffer::init(SF_INFO& fileInfo) {
    LOG_FUNCTION
    if (!soundFile) {
        throw OpenAlException("Error opening file.");
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
            throw OpenAlException("Cannot define sound format.");
    }
    this->buffer = new ALuint[this->number];
    alGenBuffers(this->number, this->buffer);
    for(int i = 0; i < this->number; i++) {
        this->read(this->buffer[i]);
    }
}

yz::AlBuffer::~AlBuffer() {
    LOG_FUNCTION
    alDeleteBuffers(this->number, this->buffer);
}


void yz::AlBuffer::read(ALuint buffer) {
    LOG_FUNCTION
    std::vector<ALshort> samples(this->nbSamples);
    ALsizei read(static_cast<ALsizei>(sf_read_short(this->soundFile, &samples[0], this->nbSamples)));
    alBufferData(buffer, this->format, &samples[0], read * sizeof(short), this->sampleRate);
}

sf_count_t yz::AlBuffer::Stream::getLength(void* userData) {
    LOG_FUNCTION
    yz::physfs* stream = static_cast<yz::physfs*>(userData);
    return stream->getSize();
}

sf_count_t yz::AlBuffer::Stream::read(void* ptr, sf_count_t count, void* userData) {
    LOG_FUNCTION
    yz::physfs* stream = static_cast<yz::physfs*>(userData);
    return stream->read(reinterpret_cast<char*>(ptr), count);
}

sf_count_t yz::AlBuffer::Stream::seek(sf_count_t offset, int whence, void* userData) {
    LOG_FUNCTION
    yz::physfs* stream = static_cast<yz::physfs*>(userData);
    switch (whence) {
        case SEEK_SET : return stream->seek(offset);
        case SEEK_CUR : return stream->seek(stream->tell() + offset);
        case SEEK_END : return stream->seek(stream->getSize() - offset);
        default       : return stream->seek(0);
    }
}

sf_count_t yz::AlBuffer::Stream::tell(void* userData) {
    LOG_FUNCTION
    yz::physfs* stream = static_cast<yz::physfs*>(userData);
    return stream->tell();
}
