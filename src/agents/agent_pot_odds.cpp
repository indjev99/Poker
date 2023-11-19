#include "agents/agent_pot_odds.h"
#include "deck.h"
#include "find_hand.h"

AgentPotOdds::AgentPotOdds(int version)
    : version(version)
    , rng(42)
{}

int AgentPotOdds::getAction()
{
    bool taken[NUM_CARDS] = {};

    for (Card card : table->sharedCards)
    {
        taken[card.id] = true;
    }

    for (Card card : selfHoleCards->cards)
    {
        taken[card.id] = true;
    }

    Deck deck(taken);

    std::vector<Card> sharedCards = table->sharedCards;
    HoleCards otherHoleCards;

    double potOdds = 0;

    for (int i = 0; i < NUM_TRIALS; ++i)
    {
        deck.shuffle(rng);

        sharedCards.resize(table->sharedCards.size());
        while ((int) sharedCards.size() < NUM_SHARED_CARDS)
        {
            sharedCards.push_back(deck.drawCard());
        }

        Hand selfHand = findBestHand({&sharedCards, &selfHoleCards->cards});

        bool isBest = true;
        int countDraws = 1;

        for (int j = 0; j < table->numActivePlayers - 1; ++j)
        {
            otherHoleCards.clear();
            for (int t = 0; t < NUM_HOLE_CARDS; ++t)
            {
                otherHoleCards.dealCard(deck.drawCard());
            }

            Hand otherHand = findBestHand({&sharedCards, &otherHoleCards.cards});
    
            if (otherHand > selfHand) isBest = false;
            else if (otherHand == selfHand) ++countDraws;
        }

        if (isBest) potOdds += 1.0 / countDraws / NUM_TRIALS;
    }

    int bestBet = FOLD_BET;
    double bestEV = 0;

    auto tryBet = [&](int bet)
    {
        int betCost = bet - table->playerBets[selfIdx];

        if (bet < table->currBet) return;
        if (bet > table->currBet && bet < table->minRaise) return;
        if (betCost > table->playerStacks[selfIdx]) return;

        int betPot = table->pot;
        for (int i = 0; i < table->numPlayers; ++i)
        {
            if (!table->playerActives[i]) continue;
            betPot += bet - table->playerBets[i];
        }

        double betEquity = betPot * potOdds;
        double EV = betEquity - betCost;

        if (EV > bestEV)
        {
            bestEV = EV;
            bestBet = bet;
        }
    };

    tryBet(table->currBet);

    if (table->currRound == 0 && table->currBet == table->bigBlind)
        tryBet(table->bigBlind * 5 / 2);

    if (table->currBet < table->pot / 3)
        tryBet(table->currBet + table->pot * 2 / 3);

    return bestBet;
}
