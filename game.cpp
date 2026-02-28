#include <print>

#include "raylib.h"

#include "card.h"
#include "game.h"
#include "hand.h"
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

namespace Blackjack
{

Game::Game(const CPPRaylib::Window &window)
    : window_{window}
    , state_{GameState::PLAYING}
    , font_{LoadFontEx("../assets/BebasNeue-Regular.ttf", 36, nullptr, 0)}
    , images_{CPPRaylib::ImageLoader{"../assets"}}
    , deck_{*this}
{
    auto card1 = deck_.deal();
    auto card2 = deck_.deal();

    card1.flip();
    card2.flip();

    std::println("{}", card1.to_string());
    std::println("{}", card2.to_string());

    hand_.add(card1);
    hand_.add(card2);
}

Game::~Game()
{
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
}

void Game::draw() const
{
    using namespace Constants;
    ::DrawRectangleGradientV(0, 0, Width, Height, ::Color{0, 100, 40, 255}, ::Color{0, 70, 30, 255});

    hand_.draw({CardRowStart.x, CardRowStart.y});
    //    ::DrawRectangleRounded({PackPosition.x, PackPosition.y, CardWidth, CardHeight}, 0.1f, 32, RAYWHITE);
    //    ::DrawTextureV(images_.at("CardBackRed"), {PackPosition.x + 5, PackPosition.y + 5}, WHITE);
    //
    //    ::DrawRectangleRounded({CardRowStart.x, CardRowStart.y, CardWidth, CardHeight}, 0.1f, 32, RAYWHITE);
    //    ::DrawTextureV(images_.at("CardBackBlue"), {CardRowStart.x + 5, CardRowStart.y + 5}, WHITE);
    //
    //    ::DrawRectangleRounded(
    //        {CardRowStart.x + CardWidth + Margin, CardRowStart.y, CardWidth, CardHeight}, 0.1f, 32, RAYWHITE);
    //    ::DrawTextEx(font_, "A", {CardRowStart.x + CardWidth + Margin + 5, CardRowStart.y + 5}, 50, 0, BLACK);
    //    ::DrawTextureV(images_.at("Spades-40"), {CardRowStart.x + CardWidth + Margin + 25, CardRowStart.y + 5},
    //    WHITE);
}

void Game::drawPlaying() const
{
}

void Game::drawComplete() const
{
    centre(window_, font_, "Complete", Constants::Height / 2.0f, 36, 1, BLACK);
}

}
