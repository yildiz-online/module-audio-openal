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

#ifndef _AL_ENGINE_H_
#define _AL_ENGINE_H_

#include <al.h>
#include <alc.h>
#include <alut.h>
#include "OpenAlException.h"

namespace YZ {

/**
 * Initialize the openAl context and manage the listener.
 * @author Van den Borre Grégory.
 */
class OpenAlEngine {

public:

    /**
     * Full constructor initialize the openAl context.
     * @param deviceName Name of the device to use, optional parameter.
     */
    OpenAlEngine(const char* deviceName = NULL) {
        /*ALCdevice* device = alcOpenDevice(deviceName);
        if (!device) {
            throw YZ::OpenAlException("Unable to open audio device");
        }
        ALCcontext* context = alcCreateContext(device, NULL);
        if (!context) {
            alcCloseDevice(device);
            throw YZ::OpenAlException("Unable to create the context.");
        }
        if (!alcMakeContextCurrent(context)) {
            alcMakeContextCurrent(NULL);
            alcDestroyContext(context);
            alcCloseDevice(device);
            throw YZ::OpenAlException("Unable to activate the context.");
        }
        if(alGetError() != AL_NO_ERROR) {
            throw OpenAlException("Error starting the engine.");
        }*/
        if(alutInit (NULL, NULL) == AL_FALSE) {
            throw OpenAlException("Error Initializing alut.");
        }
       /* ALuint buffer = alutCreateBufferFromFile("/home/moussa/test.wav");
        ALuint source;
        alGenSources(1, &source);
        if(alGetError() != AL_NO_ERROR) {
            throw OpenAlException("Error starting the engine.");
        }
        alSourcei(source, AL_BUFFER, buffer);
        if(alGetError() != AL_NO_ERROR) {
            throw OpenAlException("Error starting the engine.");
        }
        alSourcePlay(source);
        if(alGetError() != AL_NO_ERROR) {

            throw OpenAlException("Error starting the engine.");

        }
        ALenum state;
        alGetSourcei(source, AL_SOURCE_STATE, &state);
        while(state == AL_PLAYING) {
             alGetSourcei(source, AL_SOURCE_STATE, &state);
        }*/
    }

    /**
     * Destroy the context and close the device.
     */
    ~OpenAlEngine(void) {
        /*ALCcontext* context = alcGetCurrentContext();
        ALCdevice* device = alcGetContextsDevice(context);
        alcMakeContextCurrent(NULL);
        alcDestroyContext(context);
        alcCloseDevice(device);*/
        alutExit();
    }

    /**
     * Change the listener position.
     * @param x Listener new X position value.
     * @param y Listener new Y position value.
     * @param z Listener new Z position value.
     */
    inline void setListenerPosition(
        const float x,
        const float y,
        const float z) {
        alListener3f(AL_POSITION, x, y, z);
    }
};

}
;

#endif

