#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <array>

#include "raylib.h"

namespace Blackjack::Constants
{

inline constexpr auto WindowMargin = 40zu;
inline constexpr auto HandMargin = 60zu;
inline constexpr auto CardWidth = 250zu;
inline constexpr auto CardHeight = 350zu;

inline constexpr ::Vector2 PackPosition = {3 * WindowMargin + 2 * CardWidth, WindowMargin};
inline constexpr ::Vector2 DealerRowStart = {WindowMargin, WindowMargin};
inline constexpr ::Vector2 PlayerRowStart = {WindowMargin, 2 * WindowMargin + CardHeight};

inline constexpr auto Width = WindowMargin * 6 + 5 * CardWidth;
inline constexpr auto Height = WindowMargin * 3 + 2 * CardHeight;

}

#endif // CONSTANTS_H
