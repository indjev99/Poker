#include "names.h"

static std::string rankNames[NUM_RANKS] = {
    "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"
};

static std::string suitNames[NUM_SUITS] = {
    "d", "c", "h", "s"
};

std::string rankName(uint8_t rank)
{
    return rankNames[rank];
};

std::string suitName(uint8_t suit)
{
    return suitNames[suit];
};

std::string cardName(const Card& card)
{
    return rankName(card.rank()) + suitName(card.suit());
}

static std::string handTiebreakName(int tiebreak, int count)
{
    int lastPow = 1;
    for (int i = 0; i < count - 1; ++i)
    {
        lastPow *= NUM_RANKS;
    }

    std::string name = "";
    while (count-- > 0)
    {
        name += " ";
        name += rankName(tiebreak / lastPow);
        tiebreak %= lastPow;
        lastPow /= NUM_RANKS;
    }

    return name;
}

std::string handName(const Hand& hand)
{
    switch (hand.type)
    {
    case NONE:
        return "None";
        break;

    case HIGH_CARD:
        return "High Card" + handTiebreakName(hand.tiebreak, 5);
        break;

    case ONE_PAIR:
        return "One Pair" + handTiebreakName(hand.tiebreak, 4);
        break;

    case TWO_PAIR:
        return "Two Pair" + handTiebreakName(hand.tiebreak, 3);
        break;

    case THREE_OF_A_KIND:
        return "Three of a Kind" + handTiebreakName(hand.tiebreak, 3);
        break;

    case STRAIGHT:
        return "Straight" + handTiebreakName(hand.tiebreak, 1);
        break;

    case FLUSH:
        return "Flush" + handTiebreakName(hand.tiebreak, 5);
        break;

    case FULL_HOUSE:
        return "Full House" + handTiebreakName(hand.tiebreak, 2);
        break;

    case FOUR_OF_A_KIND:
        return "Four of a Kind" + handTiebreakName(hand.tiebreak, 2);
        break;

    case STRAIGHT_FLUSH:
        return "Straight Flush" + handTiebreakName(hand.tiebreak, 1);
        break;

    case FIVE_OF_A_KIND:
        return "Five of a Kind" + handTiebreakName(hand.tiebreak, 1);
        break;

    default:
        return "???";
    }
}
