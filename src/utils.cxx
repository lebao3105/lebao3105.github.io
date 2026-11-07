module;

#include <raylib.h>
#include <string>
#include <algorithm>
#include <vector>
#ifdef __EMSCRIPTEN__
#include <emscripten/val.h>
#endif

export module Utilities;

#ifdef __EMSCRIPTEN__
using namespace emscripten;

export class Browser
{
public:
    static const val document;
    static const val window;

    // TODO: Temporary reserved for future uses.
    // If there is none, they will be gone.

    static val HTMLCreateElement(const std::string &name)
    {
        assert(!name.empty());
        return document.call<val>("createElement", name);
    }

    static val HTMLCreateTextNode(const std::string &content)
    {
        assert(!content.empty());
        return document.call<val>("createTextNode", content);
    }
    
    static void HTMLSetAttribute(val what, const std::string &name, const std::string &value)
    {
        assert(!name.empty());
        return what.call<void>("setAttribute", name, value);
    }
    
    static void HTMLAppendChild(val parent, const val &child)
    {
        return parent.call<void>("appendChild", child);
    }

    Browser() = delete;
};

const val Browser::document = val::global("document");
const val Browser::window = val::global("window");

#endif

// From my other project, yedm

export void trimString(std::string &str)
{
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());
}

export const std::string emptyString{};

export std::vector<std::string>
splitStringBy(const std::string& from, const char delim)
{
    std::vector<std::string> result;
    splitStringBy(result, from, delim);
    return result;
}

export void
splitStringBy(std::vector<std::string> &vector,
    const std::string &from, const char delim)
{
    vector.clear();
    std::string::size_type start = 0;
    std::string::size_type end = from.find(delim);

    while (end != std::string::npos) {
        vector.push_back(from.substr(start, end - start));
        start = end + 1;
        end = from.find(delim, start);
    }

    vector.push_back(from.substr(start));
}

export bool
strContains(const std::string& str, const std::string& substr)
{
    return str.find(substr) != std::string::npos;
}

// TODO: Move

export enum class DefaultMargins : int
{
    NORMAL_X = 60,
    NORMAL_Y = 10,
    LIST_ITEM_X = 60 + 20,
    HEADERS_Y = 60 + 5
};

export enum class DefaultFontSizes : int
{
    NORMAL = 20,
    SMALL = 18,
    TITLE1 = 40,
    TITLE2 = 38,
    TITLE3 = 36,
    TITLE4 = 34,
    TITLE5 = 32,
    TITLE6 = 30,
};
