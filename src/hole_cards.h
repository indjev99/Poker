#pragma once

#include "card.h"
#include "config.h"

#include <vector>

struct HoleCards
{
    std::vector<Card> cards;

    constexpr HoleCards()
    {
        cards.reserve(NUM_HOLE_CARDS);
    }

    constexpr void startHand()
    {
        cards.clear();
    }

    constexpr void dealCard(Card card)
    {
        cards.push_back(card);
    }
};
