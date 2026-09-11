cmake_minimum_required(VERSION 3.31)
project(website LANGUAGES CXX VERSION 3.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.0
        GIT_SHALLOW 1
    )
    FetchContent_MakeAvailable(raylib)
endif()

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    if (NOT DEFINED RAYLIB_CPP_VERSION)
        set(RAYLIB_CPP_VERSION v6.0.0)
    endif()
    include(FetchContent)
    FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG ${RAYLIB_CPP_VERSION}
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

add_executable(website WIN32 js/main.cxx)

target_sources(website PRIVATE
FILE_SET CXX_MODULES FILES
    js/siteContent.cxx
    js/mouse.cxx
    js/utils.cxx
    js/navigation.cxx
)

if(${PLATFORM} STREQUAL "Web")
    set_target_properties(website
        PROPERTIES
            OUTPUT_NAME                 "siteInit"
            SUFFIX                      ".js"
            RUNTIME_OUTPUT_DIRECTORY    "${CMAKE_SOURCE_DIR}/js/"
    )
    target_link_options(website PRIVATE
        -lembind
        -flto
        -fwasm-exceptions
        --preload-file "${CMAKE_SOURCE_DIR}/content@/content"
        --closure 1
        -sASYNCIFY=1
        -sASSERTIONS=1
        -sFETCH=1
        -sENVIRONMENT=web
        --emit-symbol-map
        
        # Required for using Raylib
        -sUSE_GLFW=3
        -sEXPORTED_FUNCTIONS=['_main','_malloc']
        -sEXPORTED_RUNTIME_METHODS=ccall
    )
endif()
include_directories(js)
target_link_libraries(website PRIVATE raylib raylib_cpp)

# Use this for cases where include folders do not match comparing
# to the XMake build system. One example is raylib-cpp.
target_compile_definitions(website PRIVATE RAYLIB_CXX_INCLUDE="raylib-cpp.hpp")
