#include "find_hand.h"
#include "config.h"

Hand findBestHand(const std::vector<const std::vector<Card>*>& cardsLists)
{
    int countByRank[NUM_RANKS] = {};
    int countBySuit[NUM_SUITS] = {};
    int countBySuitRank[NUM_SUITS][NUM_RANKS] = {};

    for (const std::vector<Card>* cards : cardsLists)
    {
        for (Card card : *cards)
        {
            ++countByRank[card.rank()];
            ++countBySuit[card.suit()];
            ++countBySuitRank[card.suit()][card.rank()];
        }
    }

    auto findMaxStraight = [](int countByRank[NUM_RANKS])
    {
        int count = 0;
        for (int rank = NUM_RANKS - 1; rank >= 0; --rank)
        {
            count += (bool) countByRank[rank];
            if (rank + NUM_HAND_CARDS - 1 < NUM_RANKS)
            {
                if (count == NUM_HAND_CARDS) return rank + NUM_HAND_CARDS - 1 ;
                count -= (bool) countByRank[rank + NUM_HAND_CARDS];
            }
        }
        count += (bool) countByRank[NUM_RANKS - 1];
        if (count == NUM_HAND_CARDS) return NUM_HAND_CARDS - 2;
        return -1;
    };

    int maxStraightFlush = -1;
    for (int suit = 0; suit < NUM_SUITS; ++suit)
    {
        if (countBySuit[suit] < NUM_HAND_CARDS) continue;
        maxStraightFlush = std::max(maxStraightFlush, findMaxStraight(countBySuitRank[suit]));
    }

    if (maxStraightFlush >= 0) return {STRAIGHT_FLUSH, maxStraightFlush};

    int max4 = -1;
    int max3 = -1;
    int max2 = -1;
    int max22 = -1;
    int max1 = -1;
    int max12 = -1;
    int max13 = -1;
    int max14 = -1;
    int max15 = -1;

    for (int rank = NUM_RANKS - 1; rank >= 0; --rank)
    {
        if (countByRank[rank] >= 5) return {FIVE_OF_A_KIND, rank};
        else if (max4 == -1 && countByRank[rank] >= 4) max4 = rank;
        else if (max3 == -1 && countByRank[rank] >= 3) max3 = rank;
        else if (max2 == -1 && countByRank[rank] >= 2) max2 = rank;
        else if (max22 == -1 && countByRank[rank] >= 2) max22 = rank;
        else if (max1 == -1 && countByRank[rank] >= 1) max1 = rank;
        else if (max12 == -1 && countByRank[rank] >= 1) max12 = rank;
        else if (max13 == -1 && countByRank[rank] >= 1) max13 = rank;
        else if (max14 == -1 && countByRank[rank] >= 1) max14 = rank;
        else if (max15 == -1 && countByRank[rank] >= 1) max15 = rank;
    }

    if (max4 != -1) return {FOUR_OF_A_KIND, max4 * NUM_RANKS + std::max(std::max(max3, max2), max1)};
    if (max3 != -1 && max2 != -1) return {FOUR_OF_A_KIND, max3 * NUM_RANKS + max2};

    int maxFlush = -1;
    for (int suit = 0; suit < NUM_SUITS; ++suit)
    {
        if (countBySuit[suit] <= NUM_HAND_CARDS) continue;

        int flush = 0;
        int countInFlush = 0;
        for (int rank = NUM_RANKS - 1; rank >= 0 && countInFlush < NUM_HAND_CARDS; --rank)
        {
            if (!countBySuitRank[suit][rank]) continue;
            flush = flush * NUM_RANKS + rank;
            ++countInFlush;
        }

        maxFlush = std::max(maxFlush, flush);
    }

    if (maxFlush >= 0) return {FLUSH, maxFlush};

    int maxStraight = findMaxStraight(countByRank);
    if (maxStraight >= 0) return {STRAIGHT, maxStraight};

    if (max3 != -1) return {THREE_OF_A_KIND, (max3 * NUM_RANKS + max1) * NUM_RANKS + max12};
    if (max22 != -1) return {TWO_PAIR, (max2 * NUM_RANKS + max22) * NUM_RANKS + max1};
    if (max2 != -1) return {ONE_PAIR, ((max2 * NUM_RANKS + max1) * NUM_RANKS + max12) * NUM_RANKS + max13};
    return {HIGH_CARD, (((max1 * NUM_RANKS + max12) * NUM_RANKS + max13) * NUM_RANKS + max14) * NUM_RANKS + max15};
}
