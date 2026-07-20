#pragma once

#include <string>
#include <emscripten/val.h>

extern emscripten::val document, window, location;

emscripten::val createElement(const std::string &name);
emscripten::val createTextNode(const std::string &content);
void setAttribute(emscripten::val what, const std::string &name, const std::string &value);
void appendChild(emscripten::val parent, const emscripten::val &child);
void trimString(std::string &str);
