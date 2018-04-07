/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 *  Copyright (c) 2018 Grégory Van den Borre
 *
 *  More infos available: https://www.yildiz-games.be
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 *  documentation files (the "Software"), to deal in the Software without restriction, including without
 *  limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 *  of the Software, and to permit persons to whom the Software is furnished to do so,
 *  subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or substantial
 *  portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *  WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 *  OR COPYRIGHT  HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  SOFTWARE.
 *
 */

package be.yildizgames.module.audio.openal;

import be.yildizgames.common.exception.technical.NativeException;
import be.yildizgames.common.exception.technical.ResourceMissingException;
import be.yildizgames.common.file.FileResource;
import be.yildizgames.common.file.ResourcePath;
import be.yildizgames.common.geometry.Point3D;
import be.yildizgames.common.jni.Native;
import be.yildizgames.common.jni.NativePointer;
import be.yildizgames.common.libloader.NativeResourceLoader;
import be.yildizgames.common.logging.LogFactory;
import be.yildizgames.common.os.SystemUtil;
import be.yildizgames.module.audio.AudioEngine;
import be.yildizgames.module.audio.AudioFile;
import be.yildizgames.module.audio.SoundBuilder;
import be.yildizgames.module.audio.SoundCreationException;
import be.yildizgames.module.audio.SoundSource;
import jni.OpenAlSoundEngineNative;
import org.slf4j.Logger;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;

/**
 * OpenAL implementation for the audio engine.
 *
 * @author Grégory Van den Borre
 */
public final class OpenAlAudioEngine extends AudioEngine implements SoundBuilder, Native {

    private static final Logger LOGGER = LogFactory.getInstance().getLogger(OpenAlAudioEngine.class);

    /**
     * Object native pointer address.
     */
    private final NativePointer pointer;

    /**
     * List of existing buffers.
     */
    private final Map<String, ALBuffer> bufferList = new HashMap<>();

    private final List<ResourcePath> paths = new ArrayList<>();

    private boolean vfsAdded;

    /**
     * Simple constructor, load all libraries and initialize the engine.
     * @param loader Loader for the native libraries.
     * @throws AssertionError if loader is null.
     */
    private OpenAlAudioEngine(NativeResourceLoader loader) {
        super();
        assert loader != null;
        LOGGER.info("Initializing OpenAL audio engine...");
        if(SystemUtil.isWindows()) {
            loader.loadBaseLibrary("libphysfs", "libFLAC-8", "libsndfile-1", "OpenAL32");
        } else if(SystemUtil.isLinux()) {
            loader.loadLibrary("libphysfs", "libogg", "libFLAC", "libsndfile", "libopenal");
        }
        loader.loadLibrary("libyildizopenal");
        this.pointer = NativePointer.create(OpenAlSoundEngineNative.initialize());
        LOGGER.info("OpenAL audio engine initialized.");
    }

    /**
     * Create an openal audio engine.
     * @param loader Loader for the native libraries.
     * @return The created openal audio engine.
     * @throws AssertionError if loader is null.
     */
    public static OpenAlAudioEngine create(NativeResourceLoader loader) {
        return new OpenAlAudioEngine(loader);
    }

    private void setListenerPosition(final Point3D pos) {
        OpenAlSoundEngineNative.setListenerPosition(this.pointer.getPointerAddress(), pos.x, pos.y, pos.z);
    }

    private void setListenerOrientation(final Point3D dir) {
        OpenAlSoundEngineNative.setListenerOrientation(this.pointer.getPointerAddress(), dir.x, dir.y, dir.z);
    }

    @Override
    public void update() {
        this.setListenerPosition(this.listener.getAbsolutePosition());
        this.setListenerOrientation(this.listener.getAbsoluteDirection());
    }

    @Override
    public SoundSource createSound(final String file) {
        Optional<ResourcePath> path = this.paths
                .stream()
                .filter(p -> p.exists(file))
                .findFirst();
        String toLoad = path.map(r -> r.getPath().isEmpty() ? file : r.getPath() + File.separator + file).orElse(file);
        FileResource.FileType type = path.isPresent() ? FileResource.FileType.DIRECTORY : FileResource.FileType.VFS;
        if(type == FileResource.FileType.VFS && !this.vfsAdded) {
            throw new SoundCreationException("Trying to load a file from VFS while none had been mounted " +
                    "or trying to load a non existing file on file system:" + toLoad);
        }
        try {
            if (!this.bufferList.containsKey(toLoad)) {
                this.bufferList.put(toLoad, new ALBuffer(new AudioFile(type, toLoad)));
            }
            return this.bufferList.get(toLoad).createSource();
        } catch (NativeException e) {
            throw new SoundCreationException(e);
        }
    }

    @Override
    public OpenAlAudioEngine addResourcePath(ResourcePath path) {
        if(!new File(path.getPath()).exists()) {
            throw new ResourceMissingException(path.getPath() + " Cannot be found.");
        }
        if(path.getType() == FileResource.FileType.VFS) {
            OpenAlSoundEngineNative.addResourcePath(path.getPath());
            this.vfsAdded = true;
        } else if (path.getType() == FileResource.FileType.DIRECTORY){
            this.paths.add(path);
        }
        return this;
    }

    @Override
    protected void closeImpl() {
        OpenAlSoundEngineNative.close(this.pointer.getPointerAddress());
    }

    @Override
    public void delete() {
        OpenAlSoundEngineNative.delete(this.pointer.getPointerAddress());
        this.pointer.delete();
    }

    @Override
    public NativePointer getPointer() {
        return pointer;
    }
}
