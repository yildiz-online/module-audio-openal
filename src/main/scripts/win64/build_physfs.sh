mkdir src/main/scripts/physicsFS/build
cd src/main/scripts/physicsFS/build


cmake ../ -DCMAKE_CXX_FLAGS="-fPIC" -DPHYSFS_ARCHIVE_SLB=FALSE -DPHYSFS_ARCHIVE_QPAK=FALSE -DPHYSFS_ARCHIVE_MVL=FALSE -DPHYSFS_ARCHIVE_WAD=FALSE -DPHYSFS_ARCHIVE_GRP=FALSE -DPHYSFS_ARCHIVE_7Z=FALSE -DPHYSFS_ARCHIVE_ZIP=FALSE -DPHYSFS_BUILD_TEST=FALSE -DPHYSFS_BUILD_SHARED=FALSE -DCMAKE_INSTALL_PREFIX="../release/win64/" -DLIBRARY_OUTPUT_PATH="" -DCMAKE_TOOLCHAIN_FILE=../../mingw-toolchain.cmake


make install
make clean

rm -R *



