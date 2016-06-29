mkdir src/main/scripts/openal-soft/build
cd src/main/scripts/openal-soft/build

cmake ../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_COLOR_MAKEFILE=on -DCMAKE_INSTALL_PREFIX="../release/win64/" -DLIBRARY_OUTPUT_PATH="" -DCMAKE_TOOLCHAIN_FILE=../../mingw-toolchain.cmake

make install
make clean

rm -R *

cd ..
mkdir ../../../../target/classes/win64
cp release/win64/bin/OpenAL32.dll ../../../../target/classes/win64/libopenal.dll
