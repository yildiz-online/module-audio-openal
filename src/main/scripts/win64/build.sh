cmake . \
-DCMAKE_MODULE_PATH=. \
-DCMAKE_BUILD_TYPE=Release \
-DLIBSNDFILE_INCLUDE_DIR="libsndfile/win64/include/" \
-DLIBSNDFILE_LIBRARY="libsndfile/win64/lib/libsndfile.dll" \
-DOPENAL_INCLUDE_DIR="openal/win64/include/AL" \
-DOPENAL_LIBRARY="openal/win64/lib/libopenal.dll" \
-DPHYSFS_INCLUDE_DIR="physicsfs/win64/include" \
-DPHYSFS_LIBRARY="physicsfs/win64/lib/libphysfs.dll" \
-DLIBRARY_OUTPUT_PATH="../../../../target/classes/win64" \
-DCMAKE_TOOLCHAIN_FILE=mingw-toolchain.cmake

make
r1=$?

cp openal/win64/bin/OpenAL32.dll ../../../../target/classes/win64/OpenAL32.dll
cp physicsfs/win64/bin/libphysfs.dll ../../../../target/classes/win64/libphysfs.dll
cp libsndfile/win64/bin/libsndfile-1.dll ../../../../target/classes/win64/libsndfile-1.dll
cp libstdc++-6.dll ../../../../target/classes/win64/libstdc++-6.dll
cp libgcc_s_seh-1.dll ../../../../target/classes/win64/libgcc_s_seh-1.dll

rm -R CMakeFiles
rm CMakeCache.txt
rm cmake_install.cmake
rm Makefile
rm -r libsndfile
rm -r openal
rm -r physicsfs

return $r1
