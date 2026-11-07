cmake_minimum_required(VERSION 3.31)
project(website LANGUAGES CXX VERSION 3.0)

if(CMAKE_GENERATOR STREQUAL "")
    set(CMAKE_GENERATOR "Ninja")
else()
    string(FIND CMAKE_GENERATOR "Makefile" MakefileSearch)
    message(STATUS "Checking if the generator is supported... ${MakefileSearch}")
    if (NOT MakefileSearch EQUAL -1)
        message(FATAL_ERROR "Use of Makefile is not supported!\n"
                            "Change CMAKE_GENERATOR to a supported value (Ninja, Visual Studio)")
    endif()
endif()

add_executable(website WIN32 src/main.cxx)

target_sources(website PRIVATE
    FILE_SET CXX_MODULES FILES
        src/utils.cxx
        src/siteContent.cxx
        src/mouse.cxx
        src/navigation.cxx
)

target_compile_definitions(website PRIVATE SITE_VERSION="${PROJECT_VERSION}")

if(NOT XREPO_PACKAGE_DISABLE)
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
    
    xrepo_package("raylib")
    xrepo_package("raylib-cpp")
    xrepo_package("md4c")
    xrepo_target_packages(website raylib raylib-cpp md4c)

    if (WASM)
        xrepo_package("emscripten")
        xrepo_target_packages(website emscripten)
    endif()

    target_compile_definitions(website PRIVATE RAYLIB_CXX_INCLUDE="raylib-cpp/raylib-cpp.hpp")
else()
    include(FetchContent)
    # raylib
    # For Vita, use a patched raylib 5.5 (no patched 6.0 atm)
    # (which is not handled here, users have to install that themselves)
    find_package(raylib QUIET)
    if (VITA)
        message(FATAL_ERROR "Raylib is NOT installed!")
    else()
        if (NOT raylib_FOUND)
            FetchContent_Declare(
                raylib
                GIT_REPOSITORY https://github.com/raysan5/raylib.git
                GIT_TAG 6.0
                GIT_SHALLOW 1
            )
            FetchContent_MakeAvailable(raylib)
        endif()
    endif()

    # raylib-cpp
    find_package(raylib_cpp QUIET)
    if (NOT raylib_cpp_FOUND)
        if (NOT DEFINED RAYLIB_CPP_VERSION)
            set(RAYLIB_CPP_VERSION v${raylib_VERSION})
        endif()
        FetchContent_Declare(
            raylib_cpp
            GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
            GIT_TAG ${RAYLIB_CPP_VERSION}
        )
        FetchContent_MakeAvailable(raylib_cpp)
    endif()

    # md4c
    FetchContent_Declare(
        md4c
        GIT_REPOSITORY https://github.com/mity/md4c.git
        GIT_TAG master
    )
    FetchContent_MakeAvailable(md4c)

    target_link_libraries(website PRIVATE raylib raylib_cpp md4c)
    target_compile_definitions(website PRIVATE RAYLIB_CXX_INCLUDE="raylib-cpp.hpp")
endif()

if(WASM)
    set_target_properties(website
        PROPERTIES
            OUTPUT_NAME                 "siteInit"
            SUFFIX                      ".js"
            RUNTIME_OUTPUT_DIRECTORY    "${CMAKE_SOURCE_DIR}/src/"
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
elseif(VITA)
    include("${VITASDK}/share/vita.cmake" REQUIRED)
    vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
    # The FILE directive lets you add additional files to the VPK, the syntax is
    # FILE src_path dst_path_in_vpk. In this case, we add the LiveArea paths.
    vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
        VERSION ${VITA_VERSION}
        NAME ${VITA_APP_NAME}
        FILE sce_sys/icon0.png sce_sys/icon0.png
        FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
        FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
        FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
    )
endif()
