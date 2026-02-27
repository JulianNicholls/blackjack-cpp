#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <array>

#include "raylib.h"

namespace Blackjack::Constants
{

inline constexpr auto Margin = 40zu;
inline constexpr auto CardWidth = 250zu;
inline constexpr auto CardHeight = 350zu;

inline constexpr ::Vector2 PackPosition = {3 * Margin + 2 * CardWidth, Margin};
inline constexpr ::Vector2 CardRowStart = {Margin, 2 * Margin + CardHeight};

inline constexpr auto Width = Margin * 6 + 5 * CardWidth;
inline constexpr auto Height = Margin * 3 + 2 * CardHeight;

}

#endif // CONSTANTS_H
