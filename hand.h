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
    Hand(const Hand &other) = delete;

    void clear()
    {
        cards_.clear();
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

            card.draw(pos.x + idx * Constants::HandMargin, pos.y);
        }
    };

    unsigned int value() const;
    void show();
    size_t size() const
    {
        return cards_.size();
    }

    bool operator==(const Hand &other) const
    {
        const auto left = value();
        const auto right = other.value();

        return (left <= 21 && right <= 21 && size() != 5 && other.size() != 5 && left == right);
    }

    bool operator>(const Hand &other) const
    {
        const auto left = value();
        const auto right = other.value();

        if (right > 21)
        { // Other is bust, this is greater
            return true;
        }

        return left <= 21 && (left > right || size() == 5);
    }

  private:
    std::vector<Card> cards_;
};

} // namespace Blackjack

#endif // HAND_H
