#pragma once

#include "card.h"
#include "rng.h"

#include <algorithm>

struct Deck
{
    int pos;
    Card cards[NUM_CARDS];

    Deck(RNG& rng)
        : pos(0)
    {
        for (int id = 0; id < NUM_CARDS; ++id)
        {
            cards[id] = Card(id);
        }

        std::shuffle(cards, cards + NUM_CARDS, rng.generator);
    }

    constexpr Card drawCard()
    {
        return cards[pos++];
    }

    constexpr int size() const
    {
        return NUM_CARDS - pos;
    }
};
