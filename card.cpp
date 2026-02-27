#include "raylib.h"
#include <format>

#include "card.h"
#include "game.h"

namespace Blackjack
{

Card::Card(
    const Game &game,
    ::Vector2 pos,
    unsigned rank,
    Suit suit,
    std::string_view backname,
    bool faceup,
    float width,
    float height)
    : game_{game}
    , outline_{pos.x, pos.y, width, height}
    , rank_{rank}
    , suit_{suit}
    , backname_{backname}
    , faceup_{faceup}
{
    value_ = rank == 1 ? 11 : rank;
}

void Card::draw() const
{
    ::DrawRectangleRounded(outline_, 0.1f, 32, RAYWHITE);
    const ::Vector2 pos{outline_.x + 5, outline_.y + 5};

    if (faceup_)
    {
        const std::string text = "AS";
        const ::Color colour = BLACK;
        ::DrawTextEx(game_.font(), text.c_str(), pos, 36, 0, colour);
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
