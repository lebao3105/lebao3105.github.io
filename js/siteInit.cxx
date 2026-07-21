#include "utils.hxx"
#include "siteContent.hxx"
#include <emscripten/html5.h>
#include <emscripten/bind.h>

using namespace emscripten;

void onWindowPopState([[maybe_unused]] const emscripten::val &event) {
    addPageContent();
}

EMSCRIPTEN_BINDINGS(myAPI) {
    function("onWindowPopState", &onWindowPopState, return_value_policy::reference());
}

int main(void) {
    // Add page content
    addPageContent();
    
    window.call<void>("addEventListener",
        std::string("popstate"),
        val::module_property("onWindowPopState")
    );

    return 0;
}
