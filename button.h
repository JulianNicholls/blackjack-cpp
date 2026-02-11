#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <string_view>

#include "raylib.h"

namespace CPPRaylib
{

inline constexpr auto AUTO = 0;
inline constexpr auto SHADOW = true;
inline constexpr auto NO_SHADOW = false;

struct ButtonSpec
{
    ::Vector2 pos;
    ::Vector2 size;
    ::Color bg_colour;
    ::Color text_colour;
    ::Color hover_colour;
    ::Font font;
    std::size_t font_size;
    std::string_view caption;
    bool shadow;
};

class Button
{
  public:
    Button(const ButtonSpec &spec);

    void draw() const;
    bool update() const;

  private:
    ::Vector2 pos_;
    ::Vector2 size_;
    ::Color bg_colour_;
    ::Color text_colour_;
    ::Color hover_colour_;
    ::Font font_;
    float font_size_;
    std::string caption_;
    bool shadow_;
    ::Vector2 text_measure_;
};

} // namespace CPPRaylib

#endif // BUTTON_H
