#pragma once

#include "card.h"
#include "config.h"

#include <vector>

enum TableState
{
    START_HAND,
    END_HAND_FOLDS,
    END_HAND_SHOWDOWN,
    START_ROUND,
    END_ROUND,
    DEAL_CARD,
    ACT,
};

constexpr int FOLD_BET = -1;

struct Table
{
    // config
    int numPlayers;
    int smallBlind;
    int bigBlind;
    int buyIn;

    // whole game
    int currDealer;
    std::vector<int> playerPnls;

    // per hand
    int pot;
    int currRound;
    int lastAggressor;
    int numActivePlayers;
    std::vector<int> playerStacks;
    std::vector<bool> playerActives;
    std::vector<Card> sharedCards;

    // per round
    int currPlayer;
    int currBet;
    int minRaise;
    int lastRoundAggressor;
    std::vector<int> playerBets;

    // state
    TableState state;

    Table(int numPlayers, int bigBlind, int buyIn, int startDealer = 0);
    void startHand();
    void endHandFolds();
    void endHandShowdown(std::vector<int>& winners);
    int nextActivePlayer(int player);
    void startRound();
    void endRound();
    void dealCard(Card card);
    void act(int playerBet);

private:

    void endHandUpdatePnls();
};
