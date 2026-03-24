#include "hand.h"

namespace Blackjack
{

void Hand::show()
{
    for (auto &c : cards_)
    {
        c.flip();
    }
}

unsigned Hand::value() const
{
    unsigned value = 0;
    unsigned aces = 0;

    for (size_t i = 0zu; i < cards_.size(); ++i)
    {
        value += cards_[i].value();

        if (cards_[i].rank() == 1)
        {
            ++aces;
        }
    }

    while (value > 21 && aces > 0)
    {
        value -= 10;
        --aces;
    }

    return value;
}

} // namespace Blackjack
