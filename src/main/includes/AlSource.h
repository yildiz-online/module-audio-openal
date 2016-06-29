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

#ifndef _AL_SOURCE_H_
#define _AL_SOURCE_H_

#include <al.h>
#include <alc.h>
#include "StbAlBuffer.h"
#include "AlutAlBuffer.h"

namespace YZ {

    /**
    * A source is a sound built from a buffer.
    * @author Van den Borre Grégory
    */
    class AlSource {

    public:

        /**
        * Full constructor, build the source from the given buffer.
        * @param buffer Buffer to use to build the source.
        */
        AlSource(const YZ::StbAlBuffer* buffer);

        /**
        * Full constructor, build the source from the given buffer.
        * @param buffer Buffer to use to build the source.
        */
        AlSource(const YZ::AlutAlBuffer* buffer);

        /**
        * Destructor.
        */
        virtual ~AlSource();

        /**
        * Rewind and play the source.
        */
        inline void play() {
            alSourceRewind(this->source);
            alSourcePlay(this->source);
            while (this->isPlaying());
        }

        /**
         * Stop playing the source.
         */
        inline void stop() {
            alSourceStop(this->source);
        }

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

		/**
		 * @return <code>true</code> if the source is currently playing, <code>false</code> otherwise.
		 */
		inline bool isPlaying() {
			ALenum state;
			alGetSourcei(this->source, AL_SOURCE_STATE, &state);
			return (state == AL_PLAYING);
		}

    private :

        /**
        * Wrapped source value.
        */
        ALuint source;
    };
};

#endif
