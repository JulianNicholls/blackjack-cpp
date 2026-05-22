#include <algorithm>
#include <random>

#include "card.h"
#include "deck.h"
#include "game.h"

std::random_device rd;
std::mt19937 mt(rd());

namespace Blackjack
{

Deck::Deck()
{
    fill_shoe();
}

// Construct a two-deck shoe
void Deck::fill_shoe()
{
    using enum Suit;

    for (unsigned r = 1; r <= 13; ++r)
    {
        cards_.emplace_back(r, Clubs, "CardBackRed");
        cards_.emplace_back(r, Diamonds, "CardBackRed");
        cards_.emplace_back(r, Hearts, "CardBackRed");
        cards_.emplace_back(r, Spades, "CardBackRed");

        cards_.emplace_back(r, Clubs, "CardBackBlue");
        cards_.emplace_back(r, Diamonds, "CardBackBlue");
        cards_.emplace_back(r, Hearts, "CardBackBlue");
        cards_.emplace_back(r, Spades, "CardBackBlue");
    }

    std::shuffle(cards_.begin(), cards_.end(), mt);
}

Card Deck::deal()
{
    if (cards_.size() == 0)
    {
        fill_shoe();
    }

    Card next = std::move(cards_.back());

    cards_.pop_back();

    return next;
}

} // namespace Blackjack
