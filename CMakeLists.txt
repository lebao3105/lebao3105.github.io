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
        SUFFIX                      ".js"
        RUNTIME_OUTPUT_DIRECTORY    "${CMAKE_SOURCE_DIR}/js/"
)
target_link_options(website PRIVATE
    -lembind
    -fwasm-exceptions
    -sASSERTIONS
    --preload-file "${CMAKE_SOURCE_DIR}/content@/content"
    --closure 0
    --emit-symbol-map
)
include_directories(js)
