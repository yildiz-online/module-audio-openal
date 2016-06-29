mkdir src/main/scripts/linux64/build
cd src/main/scripts/linux64/build


cmake ../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_COLOR_MAKEFILE=on -DLIBRARY_OUTPUT_PATH="../../../../../target/classes/linux64" -G "Unix Makefiles"

make
rm -R *
