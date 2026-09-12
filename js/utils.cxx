module;

#include <raylib.h>
#include <string>
#include <cassert>
#include <algorithm>

#ifdef __EMSCRIPTEN__
#include <emscripten/val.h>
#endif

export module Utilities;

#ifdef __EMSCRIPTEN__
using namespace emscripten;

export val document = val::global("document");
export val window = val::global("window");

export val createElement(const std::string &name)
{
    assert(!name.empty());
    return document.call<val>("createElement", name);
}

export val createTextNode(const std::string &content)
{
    assert(!content.empty());
    return document.call<val>("createTextNode", content);
}

export void setAttribute(val what, const std::string &name, const std::string &value)
{
    assert(!name.empty());
    return what.call<void>("setAttribute", name, value);
}

export void appendChild(val parent, const val &child)
{
    return parent.call<void>("appendChild", child);
}
#endif

export void trimString(std::string &str)
{
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());
}

export constexpr size_t defaultXMargin = 60;
export constexpr size_t defaultYMargin = 10;
export constexpr float defaultFontSize = 48.f;
export const std::string emptyString{};
