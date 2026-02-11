#include <algorithm>
#include <string>

#include "button.h"
#include "raylib.h"

namespace CPPRaylib
{

Button::Button(const ButtonSpec &spec)
    : bg_colour_{spec.bg_colour}
    , text_colour_{spec.text_colour}
    , hover_colour_{spec.hover_colour}
    , font_{spec.font}
    , caption_{spec.caption}
    , shadow_{spec.shadow}
{
    font_size_ = spec.font_size == AUTO ? 36 : spec.font_size;

    text_measure_ = ::MeasureTextEx(font_, caption_.c_str(), font_size_, 1);

    if (spec.size.x == AUTO)
    {
        // Use the text measure
        auto width = text_measure_.x + font_size_;
        auto height = text_measure_.y + font_size_ / 3.0f;

        // If it's too square, i.e. less than 16x9, shave the height a little
        if (width < height * 1.77f)
        {
            // Flood::log::debug("{} Button: {} x {} adjusted", caption_, width, height);
            height *= 0.9f;
        }

        size_ = {width, height};
    }
    else
    {
        size_ = spec.size;
    }

    // If the x or y position is negative, then it should be set so that the position is centred on that as a positive
    // value.
    pos_.x = spec.pos.x > 0 ? spec.pos.x : -spec.pos.x - size_.x / 2.0f;
    pos_.y = spec.pos.y > 0 ? spec.pos.y : -spec.pos.y - size_.y / 2.0f;
}

// Draw the button, highlighting it in the hover colour if it is hovered
void Button::draw() const
{
    const auto mouse_pos = ::GetMousePosition();
    auto bg = bg_colour_;
    const ::Rectangle rect{pos_.x, pos_.y, size_.x, size_.y};

    // Use the hover colour or lighten the background when hovered
    if (::CheckCollisionPointRec(::GetMousePosition(), rect))
    {
        bg = ::ColorIsEqual(hover_colour_, BLANK) ? ::ColorBrightness(bg_colour_, 0.2f) : hover_colour_;
    }

    if (shadow_)
    {
        const ::Rectangle shadow_rect{pos_.x + 4, pos_.y + 4, size_.x, size_.y};

        ::DrawRectangleRounded(
            shadow_rect, 0.5f, 64, ::Fade(::ColorBrightness(bg, -0.4f), std::min(bg_colour_.a / 255.0f, 0.5f)));
    }

    ::DrawRectangleRounded(rect, 0.5f, 64, bg);

    // The top need to be biased up a little because the text measure has a little more at the top than the bottom
    const auto left = pos_.x + (size_.x / 2.0f - text_measure_.x / 2.0f);
    const auto top = pos_.y + (size_.y / 2.0f - text_measure_.y / 2.2f);

    ::DrawTextEx(font_, caption_.c_str(), {left, top}, font_size_, 1, text_colour_);
}

// Return whether the button is pressed.
bool Button::update() const
{
    if (!::IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        return false;
    }

    const ::Rectangle rect{pos_.x, pos_.y, size_.x, size_.y};

    return ::CheckCollisionPointRec(::GetMousePosition(), rect);
}

} // namespace CPPRayLib
