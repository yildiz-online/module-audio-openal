cmake . -DCMAKE_BUILD_TYPE=Release -DCMAKE_COLOR_MAKEFILE=on -DLIBRARY_OUTPUT_PATH="../../../../target/classes/win64" -DCMAKE_TOOLCHAIN_FILE=mingw-toolchain.cmake

make

rm -R CMakeFiles
rm CMakeCache.txt
rm cmake_install.cmake
rm Makefile




