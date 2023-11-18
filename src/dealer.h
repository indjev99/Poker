#pragma once

#include "table.h"
#include "deck.h"
#include "hole_cards.h"
#include "hand.h"
#include "rng.h"
#include "agent.h"

struct Dealer
{
    RNG rng;

    Table* table;

    Deck deck;
    std::vector<HoleCards> allHoleCards;

    std::vector<Agent*> agents;
    std::vector<Agent*> listeners;

    Dealer(Table* table, std::vector<Agent*>& agents, std::vector<Agent*>& spectators);

    void playHand();
};
