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

#include "../includes/AlVorbisStream.h"

/**
*@author Grégory Van den Borre
*/

YZ::AlVorbisStream::AlVorbisStream(const char* file) {
    this->initialize(new YZ::StbAlBuffer(file, BUFFER_NUMBER));
}

YZ::AlVorbisStream::AlVorbisStream(YZ::physfs* file) {
    this->initialize(new YZ::StbAlBuffer(file, BUFFER_NUMBER));
}

YZ::AlVorbisStream::~AlVorbisStream() {
}

void YZ::AlVorbisStream::initialize(YZ::StbAlBuffer* buffer) {
    this->buffer = buffer;
    alGenSources(1, &this->source);

    alSource3f(this->source, AL_POSITION, 0.0, 0.0, 0.0);
    alSource3f(this->source, AL_VELOCITY, 0.0, 0.0, 0.0);
    alSource3f(this->source, AL_DIRECTION, 0.0, 0.0, 0.0);
    alSourcef(this->source, AL_ROLLOFF_FACTOR, 0.0);
    alSourcei(this->source, AL_SOURCE_RELATIVE, AL_TRUE);
}

void YZ::AlVorbisStream::close() {
    alSourceStop(this->source);
    this->empty();
    alDeleteSources(1, &this->source);
    this->check();
}

bool YZ::AlVorbisStream::play() {
    if (this->isPlaying()) {
        return true;
    }
    for (int i = 0; i < BUFFER_NUMBER; i++) {
        if (!this->buffer->read(i)) {
            return false;
        }
    }
    this->buffer->sourceQueue(this->source);
    alSourcePlay(this->source);
    return true;
}

bool YZ::AlVorbisStream::isPlaying() {
    ALenum state;
    alGetSourcei(this->source, AL_SOURCE_STATE, &state);
    return (state == AL_PLAYING);
}

bool YZ::AlVorbisStream::update() {
    int processed;
    bool active = true;
    alGetSourcei(this->source, AL_BUFFERS_PROCESSED, &processed);
    while (processed--) {
        ALuint bufferIndex;
        alSourceUnqueueBuffers(this->source, 1, &bufferIndex);
        active = this->buffer->readIndex(bufferIndex);
        alSourceQueueBuffers(this->source, 1, &bufferIndex);
    }
    if(!this->isPlaying()) {
        alSourcePlay(this->source);
    }
    return active;
}

void YZ::AlVorbisStream::empty() {
    int queued;
    alGetSourcei(this->source, AL_BUFFERS_QUEUED, &queued);
    while(queued--) {
        ALuint buffer;
        alSourceUnqueueBuffers(this->source, 1, &buffer);
    }
}

