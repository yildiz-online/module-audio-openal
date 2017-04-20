cmake_minimum_required (VERSION 2.8.6)
project (yildiz_native_openal)

set(CMAKE_CXX_FLAGS "-O2 -std=gnu++11")

include_directories("openal/include")
include_directories("physfs/include")
include_directories("java/include")
include_directories("java/include/win32")
include_directories("libsndfile/include")

set(CMAKE_SHARED_LINKER_FLAGS "-Xlinker --add-stdcall-alias")

file(
        GLOB_RECURSE
        source_files
        ${CMAKE_SOURCE_DIR}/../../c++/*.cpp
        ${CMAKE_SOURCE_DIR}/../../c++/*.c
        ${CMAKE_SOURCE_DIR}/../../includes/*.hpp
        ${CMAKE_SOURCE_DIR}/../../includes/*.h
)

add_library(yildizopenal SHARED ${source_files})

target_link_libraries(yildizopenal ${CMAKE_SOURCE_DIR}/physfs/lib/libphysfs.dll.a)
target_link_libraries(yildizopenal ${CMAKE_SOURCE_DIR}/openal/lib/libOpenAL32.dll.a)
target_link_libraries(yildizopenal ${CMAKE_SOURCE_DIR}/libsndfile/lib/libsndfile-1.lib)


