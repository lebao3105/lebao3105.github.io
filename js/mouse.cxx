module;

#include <raylib.h>
#include <functional>
#include <cassert>
#include <string>
#include "macros.h"

export module MouseUtils;
import Utilities;

export Vector2 mousePos = { 0, 0 };

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

export enum class MouseState
{
    None,
    Hovered,
    Clicked,

    // "Toggled" is not a word here, it's for buttons
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

export struct UIButton {
protected:
    MouseState state = MouseState::None;

public:
    Rectangle bounds; //< For the button ONLY, EXCLUDING the label!
    std::function<void()> onClick;
    std::string label;

    void MainLoop() {
        HandleMouseEvents();
        Draw();
    }

    void HandleMouseEvents() {
        assert(onClick);
        assert(bounds.width > 0.f && bounds.height > 0.f);

        if (! IsMouseOverRect(bounds)) {
            state = MouseState::None;
            return;
        }

        else if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            state = MouseState::Hovered;
            return;
        }

        state = MouseState::Clicked;
        onClick();
    }

    void Draw() {
        assert(bounds.width > 0.f && bounds.height > 0.f);
        assert(bounds.x >= 0.f && bounds.y >= 0.f);
        assert(! label.empty());

        if (bounds.width == bounds.height) {
            TraceLog(LOG_WARNING, "Square button!?");
        }

        // Assuming that the mouse position is updated in the main loop,
        // before drawing ANYTHING. If that's not the case, fix it until
        // something funny happens;)

        if (! label.empty()) {
            const auto *cl = label.c_str();
            DrawText(cl, bounds.x - 10.f - MeasureText(cl, FONT_SZ(NORMAL)),
                     bounds.y, FONT_SZ(NORMAL), BLACK);
        }

        // For toggle buttons, only ToggleOn and ToggleOff are accepted.
        // There is no check about that for now, which may break the look-and-feel of the site.
        // However in HandleMouseEvents() states like Clicked are transformed into Toggle ones,
        // and under normal uses, it is enough.
        DrawRectangleRec(bounds, getButtonBackground(state));
    }
};

const std::string OnLabel = "On";
const std::string OffLabel = "Off";

export struct UISwitchButton : public UIButton
{
    void HandleMouseEvents() {
        UIButton::HandleMouseEvents();

        if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            state = state == MouseState::ToggledOn ?
                MouseState::ToggledOff : MouseState::ToggledOn;
            onClick();
        }
    }

    void Draw() {
        label = state == MouseState::ToggledOn ? OnLabel : OffLabel;
        UIButton::Draw();
        Rectangle bounds2 = {
            bounds.x + (state != MouseState::ToggledOn ? 40.f : 0.f),
            bounds.y,
            bounds.width / 2,
            bounds.height
        };
        DrawRectangleRec(bounds2, LIGHTGRAY);
    }

    bool IsToggledOn() const {
        return state == MouseState::ToggledOn;
    }
};
