#ifndef CARD_H
#define CARD_H

#include <string>
#include <string_view>

#include "raylib.h"

#include "resources.h"

namespace Blackjack
{
class Game;

enum struct Suit
{
    Hearts,
    Diamonds,
    Clubs,
    Spades
};

class Card
{
  public:
    Card(
        const Game &game,
        ::Vector2 pos,
        unsigned rank,
        Suit suit,
        std::string_view backname,
        bool faceup = false,
        float width = Constants::CardWidth,
        float height = Constants::CardHeight);

    void draw() const;
    void flip();

    std::string suit_image_name() const;

    std::string to_string() const;

    void set_position(::Vector2 pos)
    {
        outline_.x = pos.x;
        outline_.y = pos.y;
    }

  private:
    std::string rank_name() const;
    std::string suit_name() const;

    const Game &game_;
    ::Rectangle outline_;
    unsigned rank_;
    Suit suit_;
    unsigned value_;
    std::string backname_;
    bool faceup_;
};

} // namespace Blackjack

#endif // CARD_H
