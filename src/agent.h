#pragma once

#include "table.h"
#include "hand.h"
#include "hole_cards.h"

struct Agent
{
    // for all
    const Table* table = nullptr;

    // for players
    int selfIdx = -1;
    const HoleCards* selfHoleCards = nullptr;

    // for spectators
    const std::vector<HoleCards>* allHoleCards = nullptr;

    void setTable(const Table* table)
    {
        this->table = table;
    }

    void setSelfIdxAndHoleCards(int selfIdx, const HoleCards* selfHoleCards)
    {
        this->selfIdx = selfIdx;
        this->selfHoleCards = selfHoleCards;
    }

    void setAllHoleCards(const std::vector<HoleCards>* allHoleCards)
    {
        this->allHoleCards = allHoleCards;
    }

    virtual void handStarted() {}

    virtual void handEndedFolds(int winner) {}
    virtual void handToEndShowdown(const std::vector<int>& players) {}
    virtual void playerShowdownRevealed(int player, const HoleCards& holeCards, const Hand& hand) {}
    virtual void handEndedShowdown(const std::vector<int>& winners, const Hand& hand) {}

    virtual void roundStarted() {}
    virtual void roundEnded() {}

    virtual void playerToAct(int player) {}
    virtual void playerActed(int player, int bet) {}

    virtual int getAction() { return FOLD_BET; }

    virtual ~Agent() = default;
};
