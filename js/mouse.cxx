module;

#include <raylib.h>
#include <functional>
#include <cassert>

import Utilities;
export module MouseUtils;

export void UpdateMousePosition()
{
    mousePos = GetMousePosition();
}

export bool IsMouseOverRect(const Rectangle &rect)
{
    return CheckCollisionPointRec(mousePos, rect);
}

export bool IsMouseLeftClickedOnRect(const Rectangle &rect)
{
    return IsMouseOverRect(rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

export enum class MouseState {
    None,
    Hovered,
    Clicked,
    ToggledOn,
    ToggledOff
};

constexpr Color getButtonBackground(MouseState state)
{
    switch (state) {
        case MouseState::None: return LIGHTGRAY;
        case MouseState::Hovered: return GRAY;
        case MouseState::Clicked: return DARKGRAY;
        case MouseState::ToggledOn: return GREEN;
        case MouseState::ToggledOff: return RED;
        default: return LIGHTGRAY;
    }
}

export struct Button {
    Rectangle bounds; //< For the button ONLY, EXCLUDING the label!
    MouseState state = MouseState::None;
    std::function<void()> onClick;
    std::string label;
    bool isASwitch;

    void HandleMouseEvents() {
        assert(onClick);
        assert(bounds.width > 0.f && bounds.height > 0.f);

        if ((! isASwitch) && (! IsMouseOverRect(bounds))) {
            state = MouseState::None;
            return;
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            state = isASwitch
                ? state == MouseState::ToggledOn
                    ? MouseState::ToggledOff
                    : MouseState::ToggledOn
                : MouseState::Clicked;
            onClick();
        }
        else if (! isASwitch)
            state = MouseState::Hovered;
    }

    void Draw() {
        assert(bounds.width > 0.f && bounds.height > 0.f);
        assert(bounds.x >= 0.f && bounds.y >= 0.f);

        if (bounds.width == bounds.height) {
            TraceLog(LOG_WARNING, "Square button!?");
        }

        // Assuming that the mouse position is updated in the main loop,
        // before drawing ANYTHING. If that's not the case, fix it until
        // something funny happens;)

        if (! label.empty()) {
            const auto cl = label.c_str();
            DrawText(cl, bounds.x - 10.f - MeasureText(cl, defaultFontSize), bounds.y, defaultFontSize, BLACK);
        }

        // For toggle buttons, only ToggleOn and ToggleOff are accepted.
        // There is no check about that for now, which may break the look-and-feel of the site.
        // However in HandleMouseEvents() states like Clicked are transformed into Toggle ones,
        // and under normal uses, it is enough.
        DrawRectangleRec(bounds, getButtonBackground(state));

        if (isASwitch) {
            Rectangle bounds2 = {
                bounds.x + (state != MouseState::ToggledOn ? 40.f : 0.f),
                bounds.y,
                bounds.width / 2,
                bounds.height
            };
            DrawRectangleRec(bounds2, LIGHTGRAY);
        }
    }
};