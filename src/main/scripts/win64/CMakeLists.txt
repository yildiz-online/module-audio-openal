cmake_minimum_required (VERSION 2.8.6)
project (yildiz_native_openal)

set(CMAKE_CXX_FLAGS "-O2")

set(PHYSFS "${CMAKE_SOURCE_DIR}/../physicsFS/release/win64")
set(OPENAL "${CMAKE_SOURCE_DIR}/../openal-soft/release/win64")

include_directories(/home/moussa/dev/tools/java-win64/include)
include_directories(/home/moussa/dev/tools/java-win64/include/win32)
include_directories(${OPENAL}/include/AL)
include_directories(${PHYSFS}/include)

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

target_link_libraries(yildizopenal ${PHYSFS}/lib/libphysfs.a
				   ${OPENAL}/lib/libOpenAL32.dll.a)



