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

#include <AL/al.h>
#include <AL/alc.h>
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
        ALCdevice* device = alcOpenDevice(deviceName);
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
    }

    /**
     * Destroy the context and close the device.
     */
    ~OpenAlEngine(void) {
        ALCcontext* context = alcGetCurrentContext();
        ALCdevice* device = alcGetContextsDevice(context);
        alcMakeContextCurrent(NULL);
        alcDestroyContext(context);
        alcCloseDevice(device);
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

