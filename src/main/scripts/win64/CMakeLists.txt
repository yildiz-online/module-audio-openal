cmake_minimum_required (VERSION 2.8.6)
project (yildiz_native_openal)

set(CMAKE_CXX_FLAGS "-O2 -std=gnu++11")

find_package(OpenAL REQUIRED)
find_package(PhysFS REQUIRED)
find_package(LibSndFile REQUIRED)

include_directories(${OPENAL_INCLUDE_DIR})
include_directories(${PHYSFS_INCLUDE_DIR})
include_directories("java/include")
include_directories("java/include/win32")
include_directories(${LIBSNDFILE_INCLUDE_DIR})

set(CMAKE_SHARED_LINKER_FLAGS "-Xlinker --add-stdcall-alias")

file(
        GLOB_RECURSE
        source_files
        ${CMAKE_SOURCE_DIR}/../../c++/*.cpp
        ${CMAKE_SOURCE_DIR}/../../includes/*.hpp
        ${CMAKE_SOURCE_DIR}/../../includes/*.h
)

add_library(yildizopenal SHARED ${source_files})

target_link_libraries(yildizopenal ${CMAKE_SOURCE_DIR}/physicsfs/win64/lib/libphysfs.dll.a)
target_link_libraries(yildizopenal ${CMAKE_SOURCE_DIR}/openal/win64/lib/libOpenAL32.dll.a)
target_link_libraries(yildizopenal ${CMAKE_SOURCE_DIR}/libsndfile/win64/lib/liblibsndfile-1.dll.a)
