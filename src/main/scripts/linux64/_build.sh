cmake . \
-DCMAKE_MODULE_PATH=. \
-DCMAKE_BUILD_TYPE=Release \
-DLIBSNDFILE_INCLUDE_DIR="libsndfile/linux64/include/" \
-DLIBSNDFILE_LIBRARY="libsndfile/linux64/lib/libsndfile.so" \
-DOPENAL_INCLUDE_DIR="openal/linux64/include/AL" \
-DOPENAL_LIBRARY="openal/linux64/lib/libopenal.so" \
-DPHYSFS_INCLUDE_DIR="physicsfs/linux64/include" \
-DPHYSFS_LIBRARY="physicsfs/linux64/lib/libphysfs.so" \
-DLIBRARY_OUTPUT_PATH="../../../../target/classes/linux64" \
-G "Unix Makefiles"

make
r1=$?

cp openal/linux64/lib/libopenal.so ../../../../target/classes/linux64/libopenal.so
cp physicsfs/linux64/lib/libphysfs.so ../../../../target/classes/linux64/libphysfs.so
cp libsndfile/linux64/lib/libsndfile.so ../../../../target/classes/linux64/libsndfile.so
cp libsndfile/linux64/lib/libFLAC.so ../../../../target/classes/linux64/libFLAC.so
cp libsndfile/linux64/lib/libogg.so ../../../../target/classes/linux64/libogg.so
cp sndio/linux64/lib/libsndio.so ../../../../target/classes/linux64/libsndio.so

rm -R CMakeFiles
rm CMakeCache.txt
rm cmake_install.cmake
rm Makefile
rm -r libsndfile
rm -r openal
rm -r physicsfs
rm -r alsa

return $r1
