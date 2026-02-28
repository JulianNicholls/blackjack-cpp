#ifndef HAND_H
#define HAND_H

#include <vector>

#include "raylib.h"

#include "card.h"

namespace Blackjack
{

class Hand
{
  public:
    Hand() = default;
    Hand(const Game &game)
    {
    }

    void add(const Card &c)
    {
        cards_.push_back(c);
    }

    void draw(::Vector2 pos) const
    {
        for (size_t idx = 0; idx < cards_.size(); ++idx)
        {
            const auto card = cards_[idx];

            card.draw(pos.x + idx * (card.width() + Constants::Margin), pos.y);
        }
    };

  private:
    std::vector<Card> cards_;
};

} // namespace Blackjack

#endif // HAND_H
