#ifndef HAND_H
#define HAND_H

#include <vector>

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

    void draw() const;

  private:
    std::vector<Card> cards_;
};

} // namespace Blackjack

#endif // HAND_H
