cmake_minimum_required(VERSION 3.31)
project(website LANGUAGES CXX VERSION 3.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download xrepo.cmake if not exists in build directory.
if(NOT EXISTS "${CMAKE_BINARY_DIR}/xrepo.cmake")
    message(STATUS "Downloading xrepo.cmake from https://github.com/xmake-io/xrepo-cmake/")
    # mirror https://cdn.jsdelivr.net/gh/xmake-io/xrepo-cmake@main/xrepo.cmake
    file(DOWNLOAD "https://raw.githubusercontent.com/xmake-io/xrepo-cmake/main/xrepo.cmake"
                  "${CMAKE_BINARY_DIR}/xrepo.cmake"
                  TLS_VERIFY ON)
endif()

# Include xrepo.cmake so we can use xrepo_package function.
include(${CMAKE_BINARY_DIR}/xrepo.cmake)

if(XREPO_PLATFORM STREQUAL "wasm" OR PLATFORM STREQUAL "Web")
    set(WASM ON)
else()
    set(WASM OFF)
endif()

if (${XREPO_PACKAGE_DISABLE})
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
else()
    xrepo_package("raylib")
    xrepo_package("raylib-cpp")
    if (WASM)
        xrepo_package("emscripten")
    endif()
endif()

add_executable(website WIN32 js/main.cxx)

target_sources(website PRIVATE
FILE_SET CXX_MODULES FILES
    js/utils.cxx
    js/siteContent.cxx
    js/mouse.cxx
    js/navigation.cxx
)

if (${XREPO_PACKAGE_DISABLE})
    target_link_libraries(website PRIVATE raylib raylib_cpp)
    target_compile_definitions(website PRIVATE RAYLIB_CXX_INCLUDE="raylib-cpp.hpp")
else()
    xrepo_target_packages(website raylib raylib-cpp)
    if (WASM)
        xrepo_target_packages(website emscripten)
    endif()
    target_compile_definitions(website PRIVATE RAYLIB_CXX_INCLUDE="raylib-cpp/raylib-cpp.hpp")
endif()

if(WASM)
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
