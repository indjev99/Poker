#pragma once

#include "card.h"
#include "rng.h"

#include <algorithm>

struct Deck
{
    int pos;
    int maxSize;
    Card cards[NUM_CARDS];

    Deck()
    {
        pos = 0;
        maxSize = NUM_CARDS;
        for (int id = 0; id < NUM_CARDS; ++id)
        {
            cards[id] = Card(id);
        }
    }

    Deck(bool taken[NUM_CARDS])
    {
        pos = 0;
        maxSize = 0;
        for (int id = 0; id < NUM_CARDS; ++id)
        {
            if (taken[id]) continue;
            cards[maxSize++] = Card(id);
        }
    }

    void shuffle(RNG& rng)
    {
        pos = 0;
        std::shuffle(cards, cards + maxSize, rng.generator);
    }

    constexpr Card drawCard()
    {
        return cards[pos++];
    }

    constexpr int size() const
    {
        return maxSize - pos;
    }
};
