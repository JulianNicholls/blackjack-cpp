#include <print>
#include <thread>

#include "raylib.h"

#include "button.h"
#include "card.h"
#include "game.h"
#include "hand.h"
#include "images.h"
#include "resources.h"

using namespace std::chrono_literals;

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

    ::DrawTextEx(
        font, text.c_str(), {window.width / 2.0f - textsize.x / 2.0f, y}, size, spacing, colour);
}

} // namespace

namespace Blackjack
{

Game::Game(const CPPRaylib::Window &window)
    : window_{window}, 
      state_{GameState::INITIALISING}, 
      deal_phase_{0},
      small_font_{LoadFontEx("../assets/BebasNeue-Regular.ttf", 36, nullptr, 0)},
      large_font_{LoadFontEx("../assets/BebasNeue-Regular.ttf", 48, nullptr, 0)},
      images_{CPPRaylib::ImageLoader{"../assets"}}, 
      hit_button_{{.pos = Constants::ButtonStart,
                   .size = Constants::ButtonSize,
                   .bg_colour = GREEN,
                   .text_colour = WHITE,
                   .font = small_font_,
                   .caption = "Hit Me",
                   .shadow = CPPRaylib::SHADOW}},
      stand_button_{
          {.pos = {Constants::ButtonStart.x, Constants::ButtonStart.y +
                                                 Constants::ButtonSize.y +
                                                 Constants::ButtonMargin},
           .size = Constants::ButtonSize,
           .bg_colour = BLUE,
           .text_colour = WHITE,
           .font = small_font_,
           .caption = "Stand",
           .shadow = CPPRaylib::SHADOW}},
      split_button_{
          {.pos = {Constants::ButtonStart.x,
                   Constants::ButtonStart.y + 2.0f * (Constants::ButtonSize.y +
                                                      Constants::ButtonMargin)},
           .size = Constants::ButtonSize,
           .bg_colour = BROWN,
           .text_colour = WHITE,
           .font = small_font_,
           .caption = "Split",
           .shadow = CPPRaylib::SHADOW}}
{
    Card::set_game(this);

    start();
}

Game::~Game()
{
}

void Game::start()
{
    dealer_hand_.clear();
    player_hand_.clear();
    deal_phase_ = 0;
}

void Game::deal()
{
    switch (deal_phase_)
    {
        case 0:
        case 4:
        {
            auto card = deck_.deal();
            card.flip();
            player_hand_.add(card);
            break;
        }

        case 2:
        {
            auto card = deck_.deal();
            card.flip();
            dealer_hand_.add(card);
            break;
        }

        case 6:
        {
            auto card = deck_.deal();
            dealer_hand_.add(card);
            break;
        }

        case 1:
        case 3:
        case 5:
        case 7: std::this_thread::sleep_for(250ms); break;

        case 8: state_ = GameState::PLAYER_TURN; break;
    }

    ++deal_phase_;
}

void Game::run()
{
    while (!window_.ShouldClose() && state_ != GameState::EXIT)
    {
        update();

        ::BeginDrawing();

        draw();

        ::EndDrawing();
    }
}

void Game::update()
{
    using enum GameState;

    switch (state_)
    {
        case INITIALISING:
            start();
            state_ = DEALING;
            break;

        case DEALING: deal(); break;

        case PLAYER_TURN:
            if (hit_button_.update())
            {
                auto card = deck_.deal();

                card.flip();

                player_hand_.add(card);
            }

            if (stand_button_.update())
            {
                show_dealer();
                state_ = DEALER_TURN;
            }
            break;

        case DEALER_TURN:
        case COMPARISON:
        case CHOICE:
        case EXIT: break;
    }
}

void Game::show_dealer()
{
    dealer_hand_.show();
    show_dealer_value_ = true;
}

void Game::draw() const
{
    using namespace Constants;

    ::DrawRectangleGradientV(
        0, 0, Width, Height, ::Color{0, 120, 50, 255}, ::Color{0, 60, 30, 255});

    drawPlaying();
    drawButtons();
}

void Game::drawButtons() const
{
    hit_button_.draw();
    stand_button_.draw();
    split_button_.draw();
}

void Game::drawPlaying() const
{
    using namespace Constants;

    dealer_hand_.draw(DealerRowStart);
    player_hand_.draw(PlayerRowStart);

    if (show_dealer_value_)
    {
        ::DrawTextEx(
            large_font_,
            std::to_string(dealer_hand_.value()).c_str(),
            DealerValuePosition,
            48,
            1,
            WHITE);
    }

    ::DrawTextEx(
        large_font_,
        std::to_string(player_hand_.value()).c_str(),
        PlayerValuePosition,
        48,
        1,
        WHITE);
}

void Game::drawComplete() const
{
    centre(window_, small_font_, "Complete", Constants::Height / 2.0f, 36, 1, BLACK);
}

} // namespace Blackjack
