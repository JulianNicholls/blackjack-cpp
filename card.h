#ifndef CARD_H
#define CARD_H

#include <string>
#include <string_view>

#include "raylib.h"

#include "resources.h"

namespace Blackjack
{
class Game;

enum class Suit
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
        unsigned rank,
        Suit suit,
        std::string_view backname,
        bool faceup = false,
        float width = Constants::CardWidth,
        float height = Constants::CardHeight);

    Card(const Card &other) = default;
    Card(Card &&other) = default;

    Card &operator=(const Card &other) = default;
    Card &operator=(Card &&other) = default;

    void draw(float x, float y) const;
    void draw(::Vector2 pos) const
    {
        return draw(pos.x, pos.y);
    };

    void flip()
    {
        faceup_ = true;
    }; // Flip up

    float width() const
    {
        return width_;
    }

    float height() const
    {
        return height_;
    }

    unsigned rank() const
    {
        return rank_;
    }

    unsigned value() const
    {
        return value_;
    }

    std::string suit_image_name() const;

    std::string to_string() const;

    static void set_game(const Game *game)
    {
        game_ = game;
    }

    friend void swap(Card &a, Card &b) noexcept;

  private:
    std::string rank_name() const;
    std::string suit_name() const;

    static const Game *game_;
    unsigned rank_;
    Suit suit_;
    unsigned value_;
    std::string backname_;
    bool faceup_;
    float width_;
    float height_;
};

} // namespace Blackjack

#endif // CARD_H
