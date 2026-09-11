module;

#ifdef __EMSCRIPTEN__
#include <emscripten/val.h>
#endif

#include <algorithm>
import Utilities;
export module Navigation;

#ifndef __EMSCRIPTEN__
std::string _currentDocDir = "/";

export std::string getCurrentDocumentPath()
{
    return _currentDocDir;
}

export void PushHistory(std::string path) {
    _currentDocDir = path;
}
#else
using namespace emscripten;

val location = val::global("location");
val history = val::global("history");

export std::string getCurrentDocumentPath()
{
    return location["pathname"].as<std::string>();
}

export void PushHistory(std::string path) {
    history.call<void>("pushState", path, emptyString, path);
}
#endif

export bool IsATopLevelPage(std::string p) {
    return std::count(p.begin(), p.end(), '/');
}

export bool IsATopLevelPage() {
    return IsATopLevelPage(getCurrentDocumentPath());
}
