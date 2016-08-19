cmake . -DCMAKE_MODULE_PATH=. -DCMAKE_BUILD_TYPE=Release -DCMAKE_COLOR_MAKEFILE=on -DLIBRARY_OUTPUT_PATH="../../../../target/classes/linux64" -G "Unix Makefiles"

make

rm -R CMakeFiles
rm CMakeCache.txt
rm cmake_install.cmake
rm Makefile
