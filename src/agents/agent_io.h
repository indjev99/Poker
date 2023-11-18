#pragma once

#include "agent.h"

struct AgentIO : Agent
{
    void handStarted() override;

    void handEndedFolds(int winner) override;
    void handToEndShowdown(const std::vector<int>& players) override;
    void playerShowdownRevealed(int player, const HoleCards& holeCards, const Hand& hand) override;
    void handEndedShowdown(const std::vector<int>& winners, const Hand& hand) override;

    void roundStarted() override;
    void roundEnded() override;

    void playerToAct(int player) override;
    void playerActed(int player, int bet) override;

    int getAction() override;

    void printHoleCards(const HoleCards& holeCards);

    int oldPlayerBet = -1;
    int oldBet = -1;
};
