#include "utils.hxx"
#include <cassert>

using namespace emscripten;

val document = val::global("document");
val window = val::global("window");
val location = val::global("location");

val createElement(const std::string &name)
{
    assert(!name.empty());
    return document.call<val>("createElement", name);
}

val createTextNode(const std::string &content)
{
    assert(!content.empty());
    return document.call<val>("createTextNode", content);
}

void setAttribute(val what, const std::string &name, const std::string &value)
{
    assert(!name.empty());
    return what.call<void>("setAttribute", name, value);
}

void appendChild(val parent, const val &child)
{
    return parent.call<void>("appendChild", child);
}

void trimString(std::string &str)
{
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());
}
