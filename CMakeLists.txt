cmake_minimum_required(VERSION 3.20...4.0.2) 

project(soundboard)

set(CMAKE_CXX_STANDARD 17)

set(WINDOWKIT_VERSION 10) # folder folder version
set(WINDOWKIT_VERSION_UPDATE 10.0.19041.0) # sub folder folder version
set(WINDOW_BIT x64) # arm, arm64, x64, x86

add_definitions(-DUNICODE -D_UNICODE)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

# statically link MSVC runtime in thrift to being fully self-contained.
# this increases .exe size but guarantees working on all windows versions
# see https://cmake.org/cmake/help/latest/variable/CMAKE_MSVC_RUNTIME_LIBRARY.html
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")




include(FetchContent)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.5)
FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(raylib)


# Our Project
set(SOURCE_FILES
	src/hasMain.cpp
	src/raygui.h
    src/util.h
    )
 
 
    
#this organizes the VS project folder like the source tree folder
foreach(source IN LISTS source_list)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

 
add_executable(${PROJECT_NAME} 
  ${CPP_HEADER_FILES}
  ${CPP_SOURCE_FILES}
  ${SOURCE_FILES}
)


set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/RunFolder")
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} )

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)
