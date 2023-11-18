#pragma once

enum HandType
{
    NONE,
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    FIVE_OF_A_KIND
};

struct Hand
{
    HandType type = NONE;
    int tiebreak = -1;

    friend constexpr auto operator<=>(const Hand&, const Hand&) = default;
};
