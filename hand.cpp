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

}
