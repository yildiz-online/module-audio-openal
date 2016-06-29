cd src/main/scripts/freealut/


CPPFLAGS="-I/home/moussa/dev/prj/module-audio-openal/src/main/script/linux64/include"
LDFLAGS="-L/home/moussa/dev/prj/module-audio-openal/src/main/script/linux64/lib"
export CPPFLAGS LDFLAGS

./autoconf
./configure
make
make install
make clean

mkdir ../../../../target/classes/linux64
cp release/linux64/lib/freealut.so.0 ../../../../target/classes/linux64/freealut.so



