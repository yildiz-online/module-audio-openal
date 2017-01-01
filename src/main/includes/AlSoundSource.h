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

#ifndef _AL_VORBIS_STREAM_H_
#define _AL_VORBIS_STREAM_H_

#include "AlBuffer.h"
#include "OpenAlException.h"

#include <AL/al.h>

#define BUFFER_SIZE (4096 * 8)

namespace YZ {

/**
* @author Grégory Van den Borre
*/
class AlSoundSource
{
public:

    /**
     * Constructor, initialize the sound from a given file path.
     * @param file Sound path name.
     */
    AlSoundSource(const char* file);

    AlSoundSource(YZ::physfs* file);

    AlSoundSource(YZ::AlBuffer* buffer);

    ~AlSoundSource();

    bool play();

    void close();

    bool update();

    /**
     * The source will restart playing when finished.
     */
    inline void loop() {
        alSourcei(this->source, AL_LOOPING ,AL_TRUE);
    }

    inline void setPosition(const float x, const float y, const float z) {
        alSource3f(this->source, AL_POSITION, x, y, z);
    }

    inline void rewind() {
        alSourceRewind(this->source);
     }

    bool isPlaying();

    void stop();

private :

    static int const BUFFER_NUMBER = 3;

    YZ::AlBuffer* buffer;

    ALuint source;

    bool stream(ALuint buffer);

	void empty();

    bool playBack();

    /**
     * Check openAl state if an error occurred.
     * @throw An OpenAlException if an error occurred.
     */
    inline void check() {
        int error = alGetError();
        if(error != AL_NO_ERROR) {
            throw YZ::OpenAlException(error);
        }
    }
};
};

#endif
