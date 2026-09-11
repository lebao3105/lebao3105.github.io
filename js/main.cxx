#include RAYLIB_CXX_INCLUDE
#include <stdlib.h>
#include <filesystem>

#ifdef __EMSCRIPTEN__
#include <emscripten/html5.h>
// #include <emscripten/fetch.h>
#endif

import Utilities;
import Navigation;
import MouseUtils;

static size_t currentSectionIndex = 0;
constexpr auto title = "LEBAO3105'S WEBSITE";

void DrawTitleBarItem(const std::string &name, const int &idx, size_t &xOffset, const size_t yOffset)
{
    size_t titleWidth = ::MeasureText(name.c_str(), defaultFontSize);
    Rectangle btnBounds = { (float)xOffset, (float)yOffset, (float)titleWidth, defaultFontSize };
    const bool collisioncheck = IsMouseOverRect(btnBounds);

    DrawText(name.c_str(), xOffset, yOffset, defaultFontSize,
             collisioncheck ? RED :
             idx == currentSectionIndex ? BLACK : LIGHTGRAY);

    if (collisioncheck && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentSectionIndex = idx;
        PushHistory("/" + (name != "home" ? name : ""));
    }
    xOffset += titleWidth + 20;
}

// #ifdef __EMSCRIPTEN__
// Font NitroDSFont;
// #endif

void DrawTitleBar()
{
#ifdef __EMSCRIPTEN__
    constexpr auto dirPath = "/content";
#else
    constexpr auto dirPath = "content";
#endif

    size_t xOffset = defaultXMargin;
    constexpr size_t yOffset = defaultYMargin + 20;

    DrawText(title, defaultXMargin, defaultYMargin, 20, BLACK);

    int idx = 0;
    DrawTitleBarItem("home", idx, xOffset, yOffset);
    ++idx;

    for (const auto &entry : std::filesystem::directory_iterator{dirPath})
    {
        if (! entry.is_directory()) continue;

        const auto &name = entry.path().filename();
        DrawTitleBarItem(name.string(), idx, xOffset, yOffset);
        ++idx;
    }
}

void UpdateDrawFrame() {
    BeginDrawing();
        UpdateMousePosition();
        ClearBackground(
            #ifdef __EMSCRIPTEN__
            (Color) { 0, 0, 0, 0 }
            #else
            DARKGRAY // TODO: Actual platform dark mode support
            #endif
        );
        DrawTitleBar();
    EndDrawing();
}

int main(void) {
#ifdef __EMSCRIPTEN__
    const int screenWidth = document["documentElement"]["clientWidth"].as<int>();
    const int screenHeight = document["documentElement"]["clientHeight"].as<int>();
#else
    if (! ChangeDirectory(getenv("ROOT_DIR"))) {
        TraceLog(LOG_ERROR, "Failed to change directory to ROOT_DIR (errno=%d)", errno);
        return 1;
    }
    
    constexpr int screenWidth = 1024;
    constexpr int screenHeight = 768;
#endif
    
    // Required for even Web
    raylib::Window window(screenWidth, screenHeight, title);
    SetTargetFPS(60);
    
#ifdef __EMSCRIPTEN__
    // emscripten_fetch_attr_t attr;
    // emscripten_fetch_attr_init(&attr);
    // strcpy(attr.requestMethod, "GET");
    
    // attr.requestData = "Access-Control-Allow-Origin: https://unpkg.com";
    // attr.attributes = EMSCRIPTEN_FETCH_PERSIST_FILE |
    //                   EMSCRIPTEN_FETCH_APPEND |
    //                   EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    
    // attr.onsuccess = [](emscripten_fetch_t *fetch) {
    //     TraceLog(LOG_INFO, "Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);

    //     // The data is now available at fetch->data[0] through fetch->data[fetch->numBytes-1];
    //     NitroDSFont = LoadFontFromMemory(".ttf", (unsigned char*)fetch->data, fetch->numBytes, 32, nullptr, 250);
    //     SetTextureFilter(NitroDSFont.texture, TEXTURE_FILTER_POINT);

    //     emscripten_fetch_close(fetch);
    // };
    // attr.onerror = [](emscripten_fetch_t *fetch) {
    //     TraceLog(LOG_WARNING, "Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);
    //     emscripten_fetch_close(fetch);
    // };
    
    // emscripten_fetch(&attr, "https://unpkg.com/@spiritov/ds.css/dist/assets/fonts/nitrods-font.ttf");
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
    // UnloadFont(NitroDSFont);
#else
    while (! window.ShouldClose()) {
        UpdateDrawFrame();
    }
#endif

    // UnloadTexture(), CloseWindow() and maybe are called automatically.
    return 0;
}
