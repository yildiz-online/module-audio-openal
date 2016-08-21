cmake_minimum_required (VERSION 3.0.0)

project (yildiz_native_openal)

set(CMAKE_CXX_FLAGS "-O2 -fPIC")

find_package(OpenAL REQUIRED)
find_package(PhysFS REQUIRED)
find_package(Java REQUIRED)
find_package(JNI REQUIRED)
find_package(LibSndFile REQUIRED)

include_directories(${OpenAL_INCLUDE_DIRS})
include_directories(${PhysFS_INCLUDE_DIRS})
include_directories(${JNI_INCLUDE_DIRS})
include_directories(${JNI_INCLUDE_DIRS}/linux)
include_directories(${LibSndFile_INCLUDE_DIRS})

file(
        GLOB_RECURSE
        source_files
        ${CMAKE_SOURCE_DIR}/../../c++/*.cpp
        ${CMAKE_SOURCE_DIR}/../../c++/*.c
        ${CMAKE_SOURCE_DIR}/../../includes/*.hpp
        ${CMAKE_SOURCE_DIR}/../../includes/*.h
)

add_library(yildizopenal SHARED ${source_files})

target_link_libraries(yildizopenal ${OPENAL_LIBRARY})
target_link_libraries(yildizopenal ${PHYSFS_LIBRARY})
target_link_libraries(yildizopenal ${LIBSNDFILE_LIBRARY})
