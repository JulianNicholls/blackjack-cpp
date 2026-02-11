#include <format>

#include "raylib.h"

#include "game.h"
#include "images.h"
#include "resources.h"

namespace
{

void centre(
    const CPPRaylib::Window &window,
    const ::Font &font,
    const std::string &text,
    float y,
    float size,
    float spacing,
    ::Color colour)
{
    auto textsize = ::MeasureTextEx(font, text.c_str(), size, spacing);

    ::DrawTextEx(font, text.c_str(), {window.width / 2.0f - textsize.x / 2.0f, y}, size, spacing, colour);
}

}

namespace Flood
{

Game::Game(const CPPRaylib::Window &window)
    : window_{window}
    , state_{GameState::PLAYING}
    , font_{LoadFontEx("../assets/BebasNeue-Regular.ttf", 36, nullptr, 0)}
    , images_{CPPRaylib::ImageLoader{"../assets"}}
    , grid_{Constants::GridOrigin, Constants::Rows, Constants::Columns}
    , changeSound_{::LoadSound("../assets/change.mp3")}
    , moves_{0}
    , exit_button_{
          {.pos = {-245, Constants::Height / 2.0 + 70},
           .size = {CPPRaylib::AUTO, CPPRaylib::AUTO},
           .bg_colour = DARKBLUE,
           .text_colour = WHITE,
           .font = font_,
           .font_size = 36,
           .caption = "Exit",
           .shadow = CPPRaylib::SHADOW}}
{
}

Game::~Game()
{
    UnloadSound(changeSound_);
}

void Game::run()
{
    while (!::WindowShouldClose() && state_ != GameState::COMPLETE)
    {
        update();

        ::BeginDrawing();

        draw();

        ::EndDrawing();
    }
}

void Game::update()
{
    switch (state_)
    {
        using enum GameState;

        case PLAYING:
            if (grid_.update())
            {
                PlaySound(changeSound_);
                ++moves_;
            }

            if (grid_.complete())
            {
                state_ = SUCCESS;
            }
            break;

        case SUCCESS:
        case FAILURE:
            if (exit_button_.update())
                state_ = COMPLETE;
            break;

        case COMPLETE: break;
    }
}

void Game::draw() const
{
    ::DrawTextureV(images_.at("background"), {0, 0}, WHITE);

    switch (state_)
    {
        using enum GameState;

        case PLAYING: drawPlaying(); break;

        case FAILURE:
        case SUCCESS:
        case COMPLETE: drawComplete(); break;
    }
}

void Game::drawPlaying() const
{
    using namespace Constants;

    const auto moves = std::format("{} / 25", moves_);
    const auto elapsed = static_cast<int>(::GetTime());
    const auto time = std::format("Time {}:{:0>2}", elapsed / 60, elapsed % 60);
    const auto size = ::MeasureTextEx(font_, time.c_str(), 30, 1);
    const ::Vector2 timePos = {Width - (BorderSize * 4) - size.x, BorderSize + 7};

    ::DrawTextEx(font_, moves.c_str(), {BorderSize * 4, BorderSize + 7}, 30, 1, WHITE);
    ::DrawTextEx(font_, time.c_str(), timePos, 30, 1, WHITE);

    grid_.draw();
}

void Game::drawComplete() const
{
    centre(window_, font_, "Complete", Constants::Height / 2.0f, 36, 1, BLACK);

    exit_button_.draw();
}

void Game::say_click_to_continue() const
{
    centre(window_, font_, "Click to Continue", Constants::Height / 2.0f + 70, 36, 0, DARKBLUE);
}
}
