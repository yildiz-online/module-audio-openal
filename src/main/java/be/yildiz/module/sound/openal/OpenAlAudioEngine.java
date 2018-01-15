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

package be.yildiz.module.sound.openal;

import be.yildiz.common.collections.Lists;
import be.yildiz.common.collections.Maps;
import be.yildiz.common.exeption.NativeException;
import be.yildiz.common.resource.FileResource.FileType;
import be.yildiz.common.resource.ResourcePath;
import be.yildiz.common.vector.Point3D;
import be.yildiz.module.sound.AudioEngine;
import be.yildiz.module.sound.Playlist;
import be.yildiz.module.sound.SoundBuilder;
import be.yildiz.module.sound.SoundSource;
import be.yildiz.module.sound.exception.SoundCreationException;
import be.yildizgames.common.nativeresources.Native;
import be.yildizgames.common.nativeresources.NativePointer;
import be.yildizgames.common.nativeresources.NativeResourceLoader;
import jni.OpenAlSoundEngineNative;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.File;
import java.util.List;
import java.util.Map;
import java.util.Optional;

/**
 * OpenAL implementation for the sound engine.
 *
 * @author Grégory Van den Borre
 */
public final class OpenAlAudioEngine extends AudioEngine implements SoundBuilder, Native {

    private static final Logger LOGGER = LoggerFactory.getLogger(OpenAlAudioEngine.class);

    /**
     * Object native pointer address.
     */
    private final NativePointer pointer;

    /**
     * List of existing buffers.
     */
    private final Map<String, ALBuffer> bufferList = Maps.newMap();

    private final List<ResourcePath> paths = Lists.newList();

    /**
     * Simple constructor, load all libraries and initialize the engine.
     * @param loader Loader for the native libraries.
     * @throws AssertionError if loader is null.
     */
    private OpenAlAudioEngine(NativeResourceLoader loader) {
        super();
        assert loader != null;
        LOGGER.info("Initializing OpenAL audio engine...");
        loader.loadBaseLibrary("libphysfs", "libsndfile-1", "OpenAL32");
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
    public Playlist createPlaylist(final String name) {
        return new Playlist(name, this);
    }

    @Override
    public SoundSource createSound(final String file) {
        Optional<ResourcePath> path = this.paths
                .stream()
                .filter(p -> p.exists(file))
                .findFirst();
        String toLoad = path.map(r -> r.getPath().isEmpty() ? file : r.getPath() + File.separator + file).orElse(file);
        FileType type = path.isPresent() ? FileType.DIRECTORY : FileType.VFS;
        try {
            if (!this.bufferList.containsKey(toLoad)) {
                this.bufferList.put(toLoad, new ALBuffer(toLoad, type));
            }
            return this.bufferList.get(toLoad).createSource();
        } catch (NativeException e) {
            throw new SoundCreationException(e);
        }
    }

    @Override
    public void addResourcePath(ResourcePath path) {
        if(path.getType() == FileType.VFS) {
            OpenAlSoundEngineNative.addResourcePath(path.getPath());
        } else if (path.getType() == FileType.DIRECTORY){
            this.paths.add(path);
        }
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