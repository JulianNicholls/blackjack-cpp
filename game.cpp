#include <print>

#include "raylib.h"

#include "button.h"
#include "card.h"
#include "game.h"
#include "hand.h"
#include "images.h"
#include "resources.h"

namespace {

void centre(const CPPRaylib::Window &window, const ::Font &font,
            const std::string &text, float y, float size, float spacing,
            ::Color colour) {
  auto textsize = ::MeasureTextEx(font, text.c_str(), size, spacing);

  ::DrawTextEx(font, text.c_str(), {window.width / 2.0f - textsize.x / 2.0f, y},
               size, spacing, colour);
}

} // namespace

namespace Blackjack {

Game::Game(const CPPRaylib::Window &window)
    : window_{window}, state_{GameState::PLAYING},
      font_{LoadFontEx("../assets/BebasNeue-Regular.ttf", 36, nullptr, 0)},
      images_{CPPRaylib::ImageLoader{"../assets"}}, deck_{*this},
      hit_button_{{.pos = Constants::ButtonStart,
                   .size = Constants::ButtonSize,
                   .bg_colour = GREEN,
                   .text_colour = WHITE,
                   .font = font_,
                   .caption = "Hit Me",
                   .shadow = CPPRaylib::SHADOW}},
      stand_button_{
          {.pos = {Constants::ButtonStart.x, Constants::ButtonStart.y +
                                                 Constants::ButtonSize.y +
                                                 Constants::ButtonMargin},
           .size = Constants::ButtonSize,
           .bg_colour = BLUE,
           .text_colour = WHITE,
           .font = font_,
           .caption = "Stand",
           .shadow = CPPRaylib::SHADOW}},
      split_button_{
          {.pos = {Constants::ButtonStart.x,
                   Constants::ButtonStart.y + 2.0f * (Constants::ButtonSize.y +
                                                      Constants::ButtonMargin)},
           .size = Constants::ButtonSize,
           .bg_colour = BROWN,
           .text_colour = WHITE,
           .font = font_,
           .caption = "Split",
           .shadow = CPPRaylib::SHADOW}} {
  auto card1 = deck_.deal();
  auto card2 = deck_.deal();

  card1.flip();
  card2.flip();

  std::println("{}", card1.to_string());
  std::println("{}", card2.to_string());

  player_hand_.add(card1);
  player_hand_.add(card2);

  if (card1.rank() != card2.rank())
    split_button_.disable();

  auto card3 = deck_.deal();
  auto card4 = deck_.deal();

  card3.flip();

  std::println("{}", card3.to_string());
  std::println("{}", card4.to_string());

  dealer_hand_.add(card3);
  dealer_hand_.add(card4);
}

Game::~Game() {}

void Game::run() {
  while (!::WindowShouldClose() && state_ != GameState::COMPLETE) {
    update();

    ::BeginDrawing();

    draw();

    ::EndDrawing();
  }
}

void Game::update() {
  if (hit_button_.update()) {
    auto card = deck_.deal();

    card.flip();

    player_hand_.add(card);
  }

  if (stand_button_.update()) {
    dealer_hand_.show();
  }
}

void Game::draw() const {
  using namespace Constants;

  ::DrawRectangleGradientV(0, 0, Width, Height, ::Color{0, 120, 50, 255},
                           ::Color{0, 60, 30, 255});

  drawPlaying();

  hit_button_.draw();
  stand_button_.draw();
  split_button_.draw();
}

void Game::drawPlaying() const {
  using namespace Constants;

  dealer_hand_.draw(DealerRowStart);
  player_hand_.draw(PlayerRowStart);
}

void Game::drawComplete() const {
  centre(window_, font_, "Complete", Constants::Height / 2.0f, 36, 1, BLACK);
}

} // namespace Blackjack
