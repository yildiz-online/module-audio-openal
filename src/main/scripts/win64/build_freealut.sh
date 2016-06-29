cd src/main/scripts/freealut


CPPFLAGS="-I/home/moussa/dev/prj/module-audio-openal/src/main/script/win64/include"
LDFLAGS="-L/home/moussa/dev/prj/module-audio-openal/src/main/script/win64/lib"
export CPPFLAGS LDFLAGS

./autogen
./configure --host=x86_64-w64-mingw32
make
make install
make clean

mkdir ../../../../target/classes/win64
cp release/win64/lib/freealut.dll ../../../../target/classes/win64/freealut.dll



