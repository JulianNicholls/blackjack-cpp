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
    PLAYING,
    SUCCESS,
    FAILURE,
    COMPLETE
};

class Game
{
  public:
    Game(const CPPRaylib::Window &window);
    ~Game();

    void run();
    void update();
    void draw() const;

    const ::Font &font() const
    {
        return font_;
    };

    const ::Texture2D images(std::string_view name) const
    {
        return images_.at(name);
    }

  private:
    void drawPlaying() const;
    void drawComplete() const;

    const CPPRaylib::Window &window_;
    GameState state_;
    const ::Font font_;
    CPPRaylib::ImageLoader images_;
    Hand player_hand_;
    Hand dealer_hand_;
    Deck deck_;
};

}

#endif // GAME_H
