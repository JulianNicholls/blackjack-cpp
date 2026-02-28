#include "raylib.h"
#include <format>

#include "card.h"
#include "game.h"

namespace Blackjack
{

Card::Card(
    const Game &game,
    unsigned rank,
    Suit suit,
    std::string_view backname,
    bool faceup,
    float width,
    float height)
    : game_{game}
    , width_{width}
    , height_{height}
    , rank_{rank}
    , suit_{suit}
    , backname_{backname}
    , faceup_{faceup}
{
    value_ = rank == 1 ? 11 : rank;
}

void Card::draw(float x, float y) const
{
    ::DrawRectangleRounded({x, y, width_, height_}, 0.1f, 32, RAYWHITE);
    const ::Vector2 pos{x + 5, y + 5};

    using enum Suit;

    if (faceup_)
    {
        const ::Color colour = suit_ == Suit::Spades || suit_ == Suit::Clubs ? BLACK : RED;

        ::DrawTextEx(game_.font(), rank_name().c_str(), pos, 36, 0, colour);
        ::DrawTextureV(game_.images(suit_image_name()), {x + 25, y + 5}, WHITE);
    }
    else
    {
        ::DrawTextureV(game_.images(backname_), pos, WHITE);
    }
}

std::string Card::to_string() const
{
    return std::format("{} {}", rank_name(), suit_name());
}

std::string Card::suit_image_name() const
{
    return suit_name() + "-40";
}

std::string Card::suit_name() const
{
    switch (suit_)
    {
        using enum Suit;

        case Hearts: return "Hearts";
        case Diamonds: return "Diamonds";
        case Clubs: return "Clubs";
        case Spades: return "Spades";
    }
}

std::string Card::rank_name() const
{
    switch (rank_)
    {
        case 1: return "A";
        case 11: return "J";
        case 12: return "Q";
        case 13: return "K";

        default: return std::format("{}", rank_);
    }
}

} // namespace Blackjack
