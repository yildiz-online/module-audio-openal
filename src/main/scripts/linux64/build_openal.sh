mkdir src/main/scripts/openal-soft/build
cd src/main/scripts/openal-soft/build

cmake ../ -DCMAKE_C_FLAGS="-fPIC" -DCMAKE_BUILD_TYPE=Release -DCMAKE_COLOR_MAKEFILE=on -DCMAKE_INSTALL_PREFIX="../release/linux64/" -DLIBRARY_OUTPUT_PATH="" -G "Unix Makefiles"

make install
make clean

rm -R *

cd ..
mkdir ../../../../target/classes/linux64
cp release/linux64/lib/libopenal.so.1.17.2 ../../../../target/classes/linux64/libopenal.so



