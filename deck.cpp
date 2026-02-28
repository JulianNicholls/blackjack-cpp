#include "deck.h"
#include "card.h"
#include "game.h"

namespace Blackjack
{

Deck::Deck(const Game &game)
{
    for (unsigned r = 1; r <= 13; ++r)
    {
        cards_.emplace_back(game, r, Suit::Clubs, "CardBackRed");
        cards_.emplace_back(game, r, Suit::Diamonds, "CardBackRed");
        cards_.emplace_back(game, r, Suit::Hearts, "CardBackRed");
        cards_.emplace_back(game, r, Suit::Spades, "CardBackRed");

        cards_.emplace_back(game, r, Suit::Clubs, "CardBackBlue");
        cards_.emplace_back(game, r, Suit::Diamonds, "CardBackBlue");
        cards_.emplace_back(game, r, Suit::Hearts, "CardBackBlue");
        cards_.emplace_back(game, r, Suit::Spades, "CardBackBlue");
    }
}

Card Deck::deal()
{
    Card next = std::move(cards_.back());

    cards_.pop_back();

    return next;
}

} // namespace Blackjack
