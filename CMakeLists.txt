cmake_minimum_required(VERSION 3.31)
project(website LANGUAGES CXX VERSION 3.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(website
    js/siteContent.cxx
    js/siteInit.cxx
    js/utils.cxx
)
set_target_properties(website
    PROPERTIES
        OUTPUT_NAME                 "siteInit"
        SUFFIX                      ".wasm"
        RUNTIME_OUTPUT_DIRECTORY    "${CMAKE_SOURCE_DIR}/js/"
)
add_compile_options(
    -lembind
    -fwasm-exceptions
    -sMODULARIZE
    -sASSERTIONS
    --preload-file content@/content
    --closure 0
    --emit-symbol-map
)
include_directories(js)
