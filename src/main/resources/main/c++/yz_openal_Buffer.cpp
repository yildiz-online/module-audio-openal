/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2019 Grégory Van den Borre
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
#include "../includes/yz_openal_Buffer.hpp"
#include "../includes/yz_openal_Exception.hpp"
#include "../includes/yz_openal_FileLoadingException.hpp"

/**
*@author Grégory Van den Borre
*/

yz::openal::Buffer::Buffer(yz::physfs::File* file, const int number) {
    LOG_FUNCTION
    this->number = number;
    SF_INFO fileInfo;
    SF_VIRTUAL_IO io;
    io.get_filelen = &yz::openal::Buffer::Stream::getLength;
    io.read = &yz::openal::Buffer::Stream::read;
    io.seek = &yz::openal::Buffer::Stream::seek;
    io.tell = &yz::openal::Buffer::Stream::tell;
    this->soundFile = sf_open_virtual(&io, SFM_READ, &fileInfo, file);
    this->init(fileInfo);
}

yz::openal::Buffer::Buffer(const char* file, const int number) {
    LOG_FUNCTION
    this->number = number;
    SF_INFO fileInfo;
    this->soundFile = sf_open(file, SFM_READ, &fileInfo);
    this->init(fileInfo);
}

void yz::openal::Buffer::init(SF_INFO& fileInfo) {
    LOG_FUNCTION
    if (!soundFile) {
        throw yz::openal::Exception("Error opening file.");
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
            throw yz::openal::Exception("Cannot define sound format.");
    }
    this->buffer = new ALuint[this->number];
    alGenBuffers(this->number, this->buffer);
    for(int i = 0; i < this->number; i++) {
        this->read(this->buffer[i]);
    }
}

yz::openal::Buffer::~AlBuffer() {
    LOG_FUNCTION
    alDeleteBuffers(this->number, this->buffer);
}


void yz::openal::Buffer::read(ALuint buffer) {
    LOG_FUNCTION
    std::vector<ALshort> samples(this->nbSamples);
    ALsizei read(static_cast<ALsizei>(sf_read_short(this->soundFile, &samples[0], this->nbSamples)));
    alBufferData(buffer, this->format, &samples[0], read * sizeof(short), this->sampleRate);
}

sf_count_t yz::openal::Buffer::Stream::getLength(void* userData) {
    LOG_FUNCTION
    yz::physfs::File* stream = static_cast<yz::physfs::File*>(userData);
    return stream->getSize();
}

sf_count_t yz::openal::Buffer::Stream::read(void* ptr, sf_count_t count, void* userData) {
    LOG_FUNCTION
    yz::physfs::File* stream = static_cast<yz::physfs::File*>(userData);
    return stream->readBytes(reinterpret_cast<char*>(ptr), count);
}

sf_count_t yz::openal::Buffer::Stream::seek(sf_count_t offset, int whence, void* userData) {
    LOG_FUNCTION
    yz::physfs::File* stream = static_cast<yz::physfs::File*>(userData);
    switch (whence) {
        case SEEK_SET : return stream->seek(offset);
        case SEEK_CUR : return stream->seek(stream->tell() + offset);
        case SEEK_END : return stream->seek(stream->getSize() - offset);
        default       : return stream->seek(0);
    }
}

sf_count_t yz::openal::Buffer::Stream::tell(void* userData) {
    LOG_FUNCTION
    yz::physfs::File* stream = static_cast<yz::physfs::File*>(userData);
    return stream->tell();
}
