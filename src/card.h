#pragma once

#include "config.h"

#include <stdint.h>

struct Card
{
    uint8_t id;

    constexpr Card(uint8_t id = -1)
        : id(id)
    {}

    constexpr Card(uint8_t rank, uint8_t suit)
        : id(rank * NUM_SUITS + suit)
    {}

    constexpr uint8_t rank() const
    {
        return id / NUM_SUITS;
    }

    constexpr uint8_t suit() const
    {
        return id % NUM_SUITS;
    }
};
