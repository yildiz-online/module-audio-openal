cmake . -DCMAKE_BUILD_TYPE=Release -DCMAKE_COLOR_MAKEFILE=on -DLIBRARY_OUTPUT_PATH="../../../../target/classes/win64" -DCMAKE_TOOLCHAIN_FILE=mingw-toolchain.cmake

make

rm -R CMakeFiles
rm CMakeCache.txt
rm cmake_install.cmake
rm Makefile

cp libsndfile/bin/libsndfile-1.dll ../../../../target/classes/win64/libsndfile-1.dll
cp openal/bin/soft_oal.dll ../../../../target/classes/win64/libopenal.dll
cp physfs/bin/libphysfs.dll ../../../../target/classes/win64/libphysfs.dll