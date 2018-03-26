/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2018 Grégory Van den Borre
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

#ifndef YZ_SOUND_SOURCE_H
#define YZ_SOUND_SOURCE_H

#include "AlBuffer.hpp"
#include "OpenAlException.hpp"
#include "stdafx.h"
#include "NativeMovable.hpp"

#include <al.h>

namespace yz {

/**
* @author Grégory Van den Borre
*/
class AlSoundSource : public NativeMovableComponent {

public:

    /**
    * Constructor, initialize the sound from a shared buffer.
    * @param buffer Buffer containing the sound data.
    */
    AlSoundSource(yz::AlBuffer* buffer);

    ~AlSoundSource();

    bool play();

    /**
     * The source will restart playing when finished.
     */
    inline void loop() {
        LOG_FUNCTION
        alSourcei(this->source, AL_LOOPING, AL_TRUE);
    }

    inline virtual void setPosition(const float x, const float y, const float z) {
        LOG_FUNCTION
        alSource3f(this->source, AL_POSITION, x, y, z);
        this->movable->setPosition(x, y, z);
    }

    inline virtual void setDirection(const float x, const float y, const float z) {
        LOG_FUNCTION
        alSource3f(this->source, AL_DIRECTION, x, y, z);
        this->movable->setDirection(x, y, z);
    }

    inline virtual void setOrientation(const float x, const float y, const float z, const float w) {
    }

    inline virtual void addMovableComponent(NativeMovableComponent* c) {
        this->movable->addComponent(c);
    }

    inline virtual void removeMovableComponent(NativeMovableComponent* c) {
        this->movable->removeComponent(c);
    }

    inline void setGain(float gain) {
        LOG_FUNCTION
        alSourcef(this->source, AL_GAIN, gain);
    }

    inline void rewind() {
        LOG_FUNCTION
        alSourceRewind(this->source);
     }

    bool isPlaying();

    void stop();

private :

    static int const BUFFER_NUMBER = 3;

    yz::AlBuffer* buffer;

    ALuint source;

    yz::NativeMovable* movable;

	void empty();

    /**
     * Check openAl state if an error occurred.
     * @throw An OpenAlException if an error occurred.
     */
    inline void check() {
        LOG_FUNCTION
        int error = alGetError();
        if(error != AL_NO_ERROR) {
            throw yz::OpenAlException(error);
        }
    }
};
}

#endif
