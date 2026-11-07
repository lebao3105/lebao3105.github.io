module;

#include <array>
#include <fstream>
#include <string>

#include <raylib.h>
#include <md4c.h>
#include <cassert>

#include "macros.h"

export module SiteContent;
import Utilities;

#pragma region UI Elements

// Should be a base struct/class instead. TODO
export template <typename T>
concept UIElement = requires (T instance)
{
    // Renders the element, then returns the Y position suited to render another element.
    // The Y-position part is optional, but is very useful in cases like list items.
    { instance.Render(int /*posX*/(), int /*posY*/()) } -> std::convertible_to<size_t>;
    { instance.content } -> std::same_as<std::string>;
};

// export template <UIElement ... Ts>
// struct PendingWidgetStack
// {
// private:
//     std::vector<Ts...> stack;
    
// public:
//     std::string AssociatedLocation;

//     // Self-explanatory.
//     // Silently quits if v is not unique to the stack.
//     template <UIElement T>
//     void Add(const T &v) {
//         for (const auto &w : stack)
//             if (w == v)
//                 return;
//         stack.push_back(v);
//     }

//     void Clear() noexcept { stack.clear(); }

//     // Renders all pending widgets.
//     // If one's Render return 0 for the Y position, the next widget will be rendered
//     // using the supplied Y position. Otherwise, use that returned value.
//     void Render(size_t posX, size_t posY) {
//         size_t newY = posY;
//         for (auto &widget : stack)
//             newY = widget.Render(posX, newY == 0 ? posY : newY);
//     }
// };

export struct UIHeader
{
    uint8_t size;
    std::string content;

    size_t Render(int posX, int posY) {
        assert(size >= 1 && size <= 6);
        assert(!content.empty());

        const auto sz = FONT_SZ(TITLE1) - 2 * (size - 1);
        DrawText(content.c_str(), posX, posY, sz, BLACK);

        return sz + MARGIN_TYPE(NORMAL_Y);
    }
};

export template <size_t N> struct UIList
{
    std::array<std::string, N> items;

    size_t Render(int posX, int posY)
    {
        assert(N > 0 && ! items.empty());
        size_t tempY = 0;
        const int startX = posX + MARGIN_TYPE(LIST_ITEM_X);

        for (int i = 0; i < N; i++) {
            const auto &item = "\u2022 " + items[i];
            const auto *cl = item.c_str();
            TraceLog(LOG_DEBUG, cl);

            // TODO: Better multiple line support for items with
            // newlines (although not recommended)
            tempY += FONT_SZ(NORMAL) + MARGIN_TYPE(NORMAL_Y);
            DrawText(cl, startX, posY + tempY, FONT_SZ(NORMAL), BLACK);
        }

        return tempY;
    }
};

#pragma endregion

#pragma region Markdown parsing

int OnMDBlockEnter(MD_BLOCKTYPE type, void *detail, void *userData)
{
    switch (type)
    {
    case MD_BLOCK_HTML: // = raw HTML block, need an example
    case MD_BLOCK_DOC:  // = <body> in HTML
        break;
    }

    return 0;
}

int OnMDBlockLeave(MD_BLOCKTYPE type, void *detail, void *userData)
{
    switch (type)
    {
    case MD_BLOCK_HTML: // = raw HTML block, need an example
    case MD_BLOCK_DOC:  // = <body> in HTML
        break;
    }

    return 0;
}

int OnMDSpanEnter(MD_SPANTYPE type, void *detail, void *userData)
{
    return 0;
}

int OnMDSpanLeave(MD_SPANTYPE type, void *detail, void *userData)
{
    return 0;
}

int OnMDText(MD_TEXTTYPE type, const MD_CHAR *text, MD_SIZE size, void *userData)
{
    return 0;
}

void OnDebugLogCallback(const char *msg, [[maybe_unused]] void *userdata)
{
    TraceLog(LOG_DEBUG, "MD4C: %s\n", msg);
}

constexpr MD_PARSER parser = {
    0, // ABI version (reserved)
    MD_FLAG_COLLAPSEWHITESPACE |
    MD_FLAG_PERMISSIVEAUTOLINKS /* < needs testing */ |
    MD_FLAG_NOHTML |
    MD_FLAG_TABLES |
    MD_FLAG_STRIKETHROUGH |
    // MD_FLAG_LATEXMATHSPANS | MD_FLAG_SUPERSCRIPTS | MD_FLAG_SUBSCRIPTS |
    MD_FLAG_WIKILINKS |
    MD_FLAG_UNDERLINE /*|
    MD_FLAG_SPOILERS |
    MD_FLAG_FOOTNOTES*/ // < Not present yet
    ,
    OnMDBlockEnter,
    OnMDBlockLeave,
    OnMDSpanEnter,
    OnMDSpanLeave,
    OnMDText,
    OnDebugLogCallback,
    nullptr // reserved
};

static std::ifstream contentFile;

void ParseFile(std::string which)
{
    contentFile.open(which, std::ios::in | std::ios::trunc);
    assert(contentFile.is_open());
    
    const auto size = contentFile.tellg();
    std::string content(size, '\0');
    
    assert(contentFile.read(&content[0], size));
    md_parse(content.c_str(), size, &parser, nullptr);
}

#pragma endregion
