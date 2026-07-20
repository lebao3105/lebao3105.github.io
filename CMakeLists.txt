cmake_minimum_required(VERSION 3.31)
project(website LANGUAGES CXX VERSION 3.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python3)
set(PYTHON ${Python3_EXECUTABLE} CACHE STRING "Python path")
set(EMSCRIPTEN_ROOT $ENV{EMSDK}/upstream/emscripten CACHE STRING "Emscripten path")
set(CMAKE_TOOLCHAIN_FILE ${EMSCRIPTEN_ROOT}/cmake/Modules/Platform/Emscripten.cmake)

add_executable(website
    js/siteContent.cxx
    js/siteInit.cxx
    js/utils.cxx
)
set_target_properties(website
    PROPERTIES
        OUTPUT_NAME                 "siteInit"
        SUFFIX                      ".wasm"
        RUNTIME_OUTPUT_DIRECTORY    "$<CMAKE_SOURCE_DIR>/js/"
)
set(EMCC_ARGS
    -sMODULARIZE
    -sASSERTIONS
    -lembind
    --closure 0
    --emit-symbol-map
    --fwasm-exceptions
)
