#pragma once

#include "card.h"
#include "config.h"

#include <vector>

struct HoleCards
{
    std::vector<Card> cards;

    HoleCards()
    {
        cards.reserve(NUM_HOLE_CARDS);
    }

    void clear()
    {
        cards.clear();
    }

    void dealCard(Card card)
    {
        cards.push_back(card);
    }
};
