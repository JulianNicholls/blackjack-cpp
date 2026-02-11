#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include "raylib.h"

// An RAII Window class that initialises and shuts down parts of Raylib.
// It's needed because things in Raylib require the window and other parts to be initialised first.

namespace CPPRaylib
{

struct Window
{
    Window(int _width, int _height, std::string_view title, bool audioNeeded = false)
        : width{_width}
        , height{_height}
    {
        ::InitWindow(width, height, std::string(title).c_str());

        if (audioNeeded)
        {
            ::InitAudioDevice();
        }

        ::SetTargetFPS(60); // Default
    }

    Window(const Window &other) = delete;
    Window(const Window &&other) = delete;
    Window &operator=(const Window &other) = delete;

    ~Window()
    {
        if (::IsAudioDeviceReady())
        {
            ::CloseAudioDevice();
        }

        ::CloseWindow();
    }

    int width;
    int height;
};

} // namespace CPPRaylib

#endif // WINDOW_H
