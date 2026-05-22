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
      dealer_turn_phase_{0},
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
           .shadow = CPPRaylib::SHADOW}},
      replay_button_{
          {.pos = {320, 260},
           .size = Constants::SmallButtonSize,
           .bg_colour = GREEN,
           .text_colour = WHITE,
           .font = small_font_,
           .caption = "Play",
           .shadow = CPPRaylib::SHADOW}},
      exit_button_{
          {.pos = {440, 260},
           .size = Constants::SmallButtonSize,
           .bg_colour = BLUE,
           .text_colour = WHITE,
           .font = small_font_,
           .caption = "Exit",
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
    dealer_turn_phase_ = 0;

    state_ = GameState::INITIALISING;
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
        case 7: std::this_thread::sleep_for(500ms); break;

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

        case PLAYER_TURN: player_update(); break;

        case DEALER_TURN: dealer_update(); break;

        case COMPLETE: complete_update(); break;

        case EXIT: break;
    }
}

void Game::player_update()
{
    using enum GameState;

    if (hit_button_.update())
    {
        auto card = deck_.deal();

        card.flip();

        player_hand_.add(card);

        if (player_hand_.size() == 5 || player_hand_.value() > 21)
        {
            show_dealer();
        }
    }

    if (stand_button_.update())
    {
        show_dealer();
    }
}

void Game::dealer_update()
{
    if (dealer_turn_phase_ % 2 == 0)
    {
        std::this_thread::sleep_for(1s);
    }
    else
    {
        auto card = deck_.deal();
        card.flip();
        dealer_hand_.add(card);

        if (dealer_hand_.value() >= 17 || dealer_hand_.size() == 5)
        {
            state_ = GameState::COMPLETE;
        }
    }

    ++dealer_turn_phase_;
}

void Game::complete_update()
{
    if (replay_button_.update())
    {
        start();
    }

    if (exit_button_.update())
    {
        state_ = GameState::EXIT;
    }
}

void Game::show_dealer()
{
    dealer_hand_.show();
    show_dealer_value_ = true;

    dealer_turn_phase_ = 0;
    state_ = GameState::DEALER_TURN;
}

void Game::draw() const
{
    using namespace Constants;

    ::DrawRectangleGradientV(
        0, 0, Width, Height, ::Color{0, 120, 50, 255}, ::Color{0, 60, 30, 255});

    draw_playing();
    draw_buttons();

    if (state_ == GameState::COMPLETE)
        draw_complete();
}

void Game::draw_buttons() const
{
    hit_button_.draw();
    stand_button_.draw();
    split_button_.draw();
}

void Game::draw_playing() const
{
    using namespace Constants;

    dealer_hand_.draw(DealerRowStart);
    player_hand_.draw(PlayerRowStart);

    if (show_dealer_value_)
    {
        const auto value = dealer_hand_.value();

        ::DrawTextEx(
            large_font_,
            value <= 21 ? std::to_string(value).c_str() : "Bust",
            DealerValuePosition,
            48,
            1,
            WHITE);
    }

    const auto value = player_hand_.value();

    ::DrawTextEx(
        large_font_,
        value <= 21 ? std::to_string(value).c_str() : "Bust",
        PlayerValuePosition,
        48,
        1,
        WHITE);
}

void Game::draw_complete() const
{
    using namespace Constants;

    ::DrawRectangleRounded({145, 145, Width - 290, 210}, 0.1f, 64, ::Color(0, 0, 0, 128));
    ::DrawRectangleRounded({150, 150, Width - 300, 200}, 0.1f, 64, RAYWHITE);

    if (player_hand_ == dealer_hand_)
    {
        centre(window_, large_font_, "It's a tie", 170, 64, 0, DARKGREEN);
    }
    else
    {
        if (player_hand_ > dealer_hand_)
        {
            centre(window_, large_font_, "You won", 170, 64, 0, DARKGREEN);
        }
        else
        {
            centre(window_, large_font_, "You lost", 170, 64, 0, RED);
        }
    }
    draw_completion_buttons();
}

void Game::draw_completion_buttons() const
{
    replay_button_.draw();
    exit_button_.draw();
}

} // namespace Blackjack
