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
import be.yildiz.common.log.Logger;
import be.yildiz.common.nativeresources.Native;
import be.yildiz.common.nativeresources.NativePointer;
import be.yildiz.common.nativeresources.NativeResourceLoader;
import be.yildiz.common.resource.FileResource.FileType;
import be.yildiz.common.resource.ResourcePath;
import be.yildiz.common.vector.Point3D;
import be.yildiz.module.sound.Playlist;
import be.yildiz.module.sound.SoundBuilder;
import be.yildiz.module.sound.SoundEngine;
import be.yildiz.module.sound.SoundSource;
import jni.OpenAlSoundEngineNative;

import java.io.File;
import java.util.List;
import java.util.Map;
import java.util.Optional;

/**
 * OpenAL implementation for the sound engine.
 *
 * @author Grégory Van den Borre
 */
public final class OpenAlSoundEngine extends SoundEngine implements SoundBuilder, Native {

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
     */
    public OpenAlSoundEngine(NativeResourceLoader nativeResourceLoader) {
        super();
        Logger.info("Initializing OpenAL audio engine...");
        nativeResourceLoader.loadBaseLibrary("libgcc_s_sjlj-1", "libstdc++-6", "libphysfs", "libsndfile-1", "OpenAL32");
        nativeResourceLoader.loadLibrary("libyildizopenal");
        this.pointer = NativePointer.create(OpenAlSoundEngineNative.initialize());
        Logger.info("OpenAL audio engine initialized.");
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
        String toLoad = path.map(r -> r.getPath() + File.separator + file).orElse(file);
        FileType type = path.isPresent() ? FileType.VFS : FileType.DIRECTORY;
        if(!this.bufferList.containsKey(toLoad)) {
            this.bufferList.put(toLoad, new ALBuffer(toLoad, type));
        }
        return this.bufferList.get(toLoad).createSource();
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
