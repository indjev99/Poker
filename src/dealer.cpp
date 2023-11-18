#include "dealer.h"
#include "find_hand.h"

#include <ctime>
#include <cassert>

#include <iostream>

Dealer::Dealer(Table* table, std::vector<Agent*>& agents, std::vector<Agent*>& spectators)
    : rng(time(nullptr))
    , table(table)
    , allHoleCards(table->numPlayers)
    , agents(agents)
{
    assert((int) agents.size() == table->numPlayers);

    int idx = 0;
    for (Agent* agent : agents)
    {
        agent->setTable(this->table);
        agent->setSelfIdxAndHoleCards(idx, &allHoleCards[idx]);
        agent->setAllHoleCards(nullptr);
        listeners.push_back(agent);
        ++idx;
    }

    for (Agent* spectator : spectators)
    {
        spectator->setTable(this->table);
        spectator->setSelfIdxAndHoleCards(-1, nullptr);
        spectator->setAllHoleCards(&allHoleCards);
        listeners.push_back(spectator);
    }
}

void Dealer::playHand()
{
    deck.shuffle(rng);

    for (HoleCards& holeCards : allHoleCards)
    {
        holeCards.clear();
        for (int i = 0; i < NUM_HOLE_CARDS; ++i)
        {
            holeCards.dealCard(deck.drawCard());
        }
    }

    table->startHand();

    for (Agent* listener : listeners)
    {
        listener->handStarted();
    }

    while (table->state != END_HAND_SHOWDOWN)
    {
        table->startRound();
        while (table->state == DEAL_CARD)
        {
            table->dealCard(deck.drawCard());
        }
    
        for (Agent* listener : listeners)
        {
            listener->roundStarted();
        }

        while (table->state == ACT)
        {
            int player = table->currPlayer;

            for (Agent* listener : listeners)
            {
                listener->playerToAct(player);
            }

            int bet = agents[player]->getAction();
            table->act(bet);

            for (Agent* listener : listeners)
            {
                listener->playerActed(player, bet);
            }
        }

        if (table->state == END_HAND_FOLDS)
        {
            int winner = table->currPlayer;
            table->endHandFolds();

            for (Agent* listener : listeners)
            {
                listener->handEndedFolds(winner);
            }

            return;
        }

        table->endRound();

        for (Agent* listener : listeners)
        {
            listener->roundEnded();
        }
    }

    std::vector<int> players;
    int currPlayer = table->lastAggressor;
    do
    {
        players.push_back(currPlayer);
        currPlayer = table->nextActivePlayer(currPlayer);
    }
    while (currPlayer != table->lastAggressor);

    for (Agent* listener : listeners)
    {
        listener->handToEndShowdown(players);
    }

    Hand maxHand;
    std::vector<int> winners;
    for (int player : players)
    {
        Hand hand = findBestHand({table->sharedCards, allHoleCards[player].cards});

        if (hand > maxHand)
        {
            maxHand = hand;
            winners.clear();
        }

        if (hand == maxHand)
        {
            winners.push_back(player);

            for (Agent* listener : listeners)
            {
                listener->playerShowdownRevealed(player, allHoleCards[player], hand);
            }
        }
    }

    table->endHandShowdown(winners);

    for (Agent* listener : listeners)
    {
        listener->handEndedShowdown(winners, maxHand);
    }
}
