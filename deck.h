#ifndef DECK_H
#define DECK_H

#include <vector>

#include "card.h"

namespace Blackjack
{

class Deck
{
  public:
    Deck(const Game &game);

    Card deal();

  private:
    std::vector<Card> cards_;
};

} // namespace Blackjack

#endif // DECK_H
