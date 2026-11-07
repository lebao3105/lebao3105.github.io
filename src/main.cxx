#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <cassert>
#include RAYLIB_CXX_INCLUDE

#ifdef __EMSCRIPTEN__
#include <emscripten/html5.h>
// #include <emscripten/fetch.h>
#endif

#include "macros.h"

// Resolves WinMain not found error
#ifdef _MSC_VER
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

import Utilities;
import Navigation;
import MouseUtils;
import SiteContent;

#pragma region Pivot
static size_t currentSectionIndex = 0;
constexpr auto title = "LEBAO3105'S WEBSITE";

struct PivotItem
{
    uint8_t associatedIndex;
    std::string content;

    PivotItem() = delete;
    PivotItem(std::string text, uint8_t idx)
        : content(std::move(text)), associatedIndex(idx)
    {}
    
    size_t Render(const int posX, const int posY) {
        assert(!content.empty());

        const int titleWidth = ::MeasureText(content.c_str(), FONT_SZ(TITLE5));
        const Rectangle btnBounds = { (float)posX, (float)posY, (float)titleWidth, FONT_SZ(TITLE5) };
        const bool collisioncheck = IsMouseOverRect(btnBounds);

        DrawText(content.c_str(), posX, posY, FONT_SZ(TITLE5),
                 collisioncheck ? RED : associatedIndex == currentSectionIndex ? BLACK : LIGHTGRAY);

        if (collisioncheck && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentSectionIndex = associatedIndex;
            PushHistory("/" + (content != "home" ? content : ""));
        }

        return posX + titleWidth + 20;
    }
};

static std::vector<PivotItem> pivotItems {
    PivotItem ("home", 0)
};

void DrawTitleBar()
{
    size_t xOffset = MARGIN_TYPE(NORMAL_X);
    constexpr auto yOffset = MARGIN_TYPE(NORMAL_Y) + 20;

    DrawText(title, xOffset, MARGIN_TYPE(NORMAL_Y), 20, BLACK);
    
    for (auto &item : pivotItems) {
        xOffset = item.Render(xOffset, yOffset);
        TraceLog(LOG_DEBUG, "Start X position of the next pivot item: %zu", xOffset);
    }
}
#pragma endregion

void UpdateDrawFrame()
{
    #ifdef __EMSCRIPTEN__
    if (GetMouseWheelMove() > 0.f)
        Browser::window.call<void>("onscroll");
    #endif
    UpdateMousePosition();

    BeginDrawing();
    {
        ClearBackground(
            #ifdef __EMSCRIPTEN__
            (Color) { 0, 0, 0, 0 }
            #else
            DARKGRAY // TODO: Actual platform dark mode support
            #endif
        );
        DrawTitleBar();
    }
    EndDrawing();
}

int main(void) {
    SetTraceLogLevel(LOG_DEBUG);

#ifdef __EMSCRIPTEN__
    const unsigned screenWidth = Browser::document["documentElement"]["clientWidth"].as<int>();
    const unsigned screenHeight = Browser::document["documentElement"]["clientHeight"].as<int>();
#else
    const char *envvar = getenv("SITE_ROOT_DIR");
    if (! ChangeDirectory(envvar && strlen(envvar) > 0 ? envvar : "/content")) {
        TraceLog(LOG_ERROR, "Failed to change directory to SITE_ROOT_DIR (errno=%d)", errno);
        return 1;
    }
    
    constexpr unsigned screenWidth = 1024;
    constexpr unsigned screenHeight = 768;
#endif

    int idx = 1;
    for (const auto &entry : std::filesystem::directory_iterator{GetWorkingDirectory()})
    {
        if (! entry.is_directory()) continue;

        const auto &name = entry.path().filename();
        auto newItem = PivotItem( name.string(), idx );

        pivotItems.push_back(newItem);
        ++idx;
    }
    
    // Required for even Web
    raylib::Window window(screenWidth, screenHeight, title);
    SetTargetFPS(60);
    
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    while (! window.ShouldClose()) {
        UpdateDrawFrame();
    }
#endif

    // UnloadTexture(), CloseWindow() and maybe are called automatically.
    return 0;
}
