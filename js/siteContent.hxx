#pragma once

#include <emscripten/val.h>
#include <string>

emscripten::val createSwitch(const std::string &name, const bool val);
void addPageContent();
