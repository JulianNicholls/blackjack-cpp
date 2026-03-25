#include <algorithm>
#include <random>

#include "card.h"
#include "deck.h"
#include "game.h"

std::random_device rd;
std::mt19937 mt(rd());

namespace Blackjack
{

// Construct a two-deck shoe
Deck::Deck()
{
    for (unsigned r = 1; r <= 13; ++r)
    {
        cards_.emplace_back(r, Suit::Clubs, "CardBackRed");
        cards_.emplace_back(r, Suit::Diamonds, "CardBackRed");
        cards_.emplace_back(r, Suit::Hearts, "CardBackRed");
        cards_.emplace_back(r, Suit::Spades, "CardBackRed");

        cards_.emplace_back(r, Suit::Clubs, "CardBackBlue");
        cards_.emplace_back(r, Suit::Diamonds, "CardBackBlue");
        cards_.emplace_back(r, Suit::Hearts, "CardBackBlue");
        cards_.emplace_back(r, Suit::Spades, "CardBackBlue");
    }

    std::shuffle(cards_.begin(), cards_.end(), mt);
}

Card Deck::deal()
{
    Card next = std::move(cards_.back());

    cards_.pop_back();

    return next;
}

} // namespace Blackjack
