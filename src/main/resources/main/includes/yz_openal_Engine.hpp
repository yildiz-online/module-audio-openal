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

#ifndef _AL_ENGINE_H_
#define _AL_ENGINE_H_

#include <al.h>
#include <alc.h>
#include <yz_physfs_Wrapper.hpp>
#include "yz_openal_Exception.hpp"
#include "stdafx.h"

namespace yz {

namespace openal {
/**
 * Initialize the openAl context and manage the listener.
 * @author Van den Borre Grégory.
 */
class Engine {

public:

    /**
     * Full constructor initialize the openAl context.
     * @param deviceName Name of the device to use, optional parameter.
     */
    Engine(const char* deviceName = NULL) {
        LOG_FUNCTION
        ALCdevice* device = alcOpenDevice(deviceName);
        if (!device) {
            throw yz::openal::Exception("Unable to open audio device");
        }
        ALCcontext* context = alcCreateContext(device, NULL);
        if (!context) {
            alcCloseDevice(device);
            throw yz::openal::Exception("Unable to create the context.");
        }
        if (!alcMakeContextCurrent(context)) {
            alcMakeContextCurrent(NULL);
            alcDestroyContext(context);
            alcCloseDevice(device);
            throw yz::openal::Exception("Unable to activate the context.");
        }
        this->vfs = new yz::physfs::Wrapper();
    }

    /**
     * Destroy the context and close the device.
     */
    ~Engine() {
        LOG_FUNCTION
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
    inline void setListenerPosition(const float x, const float y, const float z) {
        LOG_FUNCTION
        alListener3f(AL_POSITION, x, y, z);
    }

    inline void registerVfsContainer(const std::string& path) {
        this->vfs->registerContainer(path);
    }

    private:

    yz::physfs::Wrapper* vfs;
};

}

}
#endif
