#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "raylib.h"

namespace Blackjack::Constants
{

inline constexpr auto WindowMargin = 40zu;
inline constexpr auto HandMargin = 60zu;
inline constexpr auto ButtonMargin = 30zu;
inline constexpr auto CardWidth = 250zu;
inline constexpr auto CardHeight = 350zu;

inline constexpr ::Vector2 PackPosition = {3 * WindowMargin + 2 * CardWidth, WindowMargin};
inline constexpr ::Vector2 DealerRowStart = {WindowMargin, WindowMargin};
inline constexpr ::Vector2 PlayerRowStart = {WindowMargin, 2 * WindowMargin + CardHeight};

inline constexpr ::Vector2 DealerValuePosition = {WindowMargin + HandMargin * 9, DealerRowStart.y};
inline constexpr ::Vector2 PlayerValuePosition = {WindowMargin + HandMargin * 9, PlayerRowStart.y};

inline constexpr ::Vector2 ButtonSize = {110, 60};

inline constexpr int Width = 2 * WindowMargin + CardWidth + HandMargin * 7 + ButtonSize.x;
inline constexpr int Height = WindowMargin * 3 + 2 * CardHeight;

inline constexpr ::Vector2 ButtonStart = {
    Width - (WindowMargin + ButtonSize.x),
    2 * WindowMargin + CardHeight};

} // namespace Blackjack::Constants

#endif // CONSTANTS_H
