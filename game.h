#ifndef GAME_H
#define GAME_H

#include "raylib.h"

#include "button.h"
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "images.h"
#include "window.h"

namespace Blackjack
{

enum struct GameState
{
    INITIALISING,
    DEALING,
    PLAYER_TURN,
    DEALER_TURN,
    COMPARISON,
    CHOICE,
    EXIT
};

class Game
{
  public:
    Game(const CPPRaylib::Window &window);
    ~Game();

    void run();
    void update();
    void draw() const;

    const ::Font &small_font() const
    {
        return small_font_;
    };

    const ::Texture2D images(std::string_view name) const
    {
        return images_.at(name);
    }

  private:
    void start();
    void deal();
    void drawPlaying() const;
    void drawButtons() const;
    void drawComplete() const;
    void show_dealer();

    const CPPRaylib::Window &window_;
    GameState state_;
    const ::Font small_font_;
    const ::Font large_font_;
    CPPRaylib::ImageLoader images_;
    Hand player_hand_;
    Hand dealer_hand_;
    Deck deck_;

    CPPRaylib::Button hit_button_;
    CPPRaylib::Button stand_button_;
    CPPRaylib::Button split_button_;

    bool show_dealer_value_ = false;
    unsigned deal_phase_;
};

} // namespace Blackjack

#endif // GAME_H
