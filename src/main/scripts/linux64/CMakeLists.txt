cmake_minimum_required (VERSION 2.8.6)
project (yildiz_native_openal)

set(CMAKE_CXX_FLAGS "-O2 -fPIC")

set(OPENAL "${CMAKE_SOURCE_DIR}/../openal-soft/release/linux64")
set(ALUT "${CMAKE_SOURCE_DIR}/../freealut/release/linux64")
set(PHYSFS "${CMAKE_SOURCE_DIR}/../physicsFS/release/linux64")

include_directories("${OPENAL}/include/AL")
include_directories("${ALUT}/include/AL")
include_directories("${PHYSFS}/include")

include_directories("/home/moussa/dev/tools/java-linux64/include")
include_directories("/home/moussa/dev/tools/java-linux64/include/linux")


file(
        GLOB_RECURSE
        source_files
        ${CMAKE_SOURCE_DIR}/../../c++/*.cpp
        ${CMAKE_SOURCE_DIR}/../../c++/*.c
        ${CMAKE_SOURCE_DIR}/../../includes/*.hpp
        ${CMAKE_SOURCE_DIR}/../../includes/*.h
)

add_library(yildizopenal SHARED ${source_files})

target_link_libraries(yildizopenal ${OPENAL}/lib/libopenal.so)
target_link_libraries(yildizopenal ${ALUT}/lib/libalut.so)
target_link_libraries(yildizopenal ${PHYSFS}/lib/libphysfs.a)
