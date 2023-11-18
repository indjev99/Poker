#include "table.h"

#include <algorithm>
#include <cassert>

Table::Table(int numPlayers, int bigBlind, int buyIn, int startDealer)
    : numPlayers(numPlayers)
    , smallBlind(bigBlind / 2)
    , bigBlind(bigBlind)
    , buyIn(buyIn)
    , currDealer(startDealer)
    , playerPnls(numPlayers, 0)
    , playerStacks(numPlayers)
    , playerActives(numPlayers)
    , playerBets(numPlayers)
    , state(START_HAND)
{
    assert(numPlayers >= 2);
    assert(bigBlind > 0);
    assert(buyIn > 0);
    assert(startDealer >= 0 && startDealer < numPlayers);

    sharedCards.reserve(NUM_SHARED_CARDS);
}

void Table::startHand()
{
    assert(state == START_HAND);

    pot = 0;
    currRound = 0;
    lastAggressor = currDealer;
    numActivePlayers = numPlayers;
    std::fill(playerStacks.begin(), playerStacks.end(), buyIn);
    std::fill(playerActives.begin(), playerActives.end(), true);
    sharedCards.clear();

    state = START_ROUND;
}

void Table::endHandUpdatePnls()
{
    for (int i = 0; i < numPlayers; ++i)
    {
        playerPnls[i] += playerStacks[i] - buyIn;
    }

    currDealer = (currDealer + 1) % numPlayers;

    state = START_HAND;
}

void Table::endHandFolds()
{
    assert(state == END_HAND_FOLDS);

    playerStacks[currPlayer] += pot;

    endHandUpdatePnls();
}

void Table::endHandShowdown(std::vector<int>& winners)
{
    assert(state == END_HAND_SHOWDOWN);

    assert(!winners.empty());

    for (int winner : winners)
    {
        assert(winner >= 0 && winner < numPlayers);
        assert(std::count(winners.begin(), winners.end(), winner) == 1);
        assert(playerActives[winner]);
    }

    int remainingPot = pot;
    int remainingWinners = winners.size();

    for (int i = 0; i < numPlayers; ++i)
    {
        int player = (currDealer + 1 + i) % numPlayers;
        if (std::count(winners.begin(), winners.end(), player) == 1)
        {
            int win = (remainingPot + remainingWinners - 1) / remainingWinners;
            playerStacks[player] += win;
            remainingPot -= win;
            remainingWinners -= 1;
        }
    }

    endHandUpdatePnls();
}

int Table::nextActivePlayer(int player)
{
    do
    {
        player = (player + 1) % numPlayers;
    }
    while (!playerActives[player]);

    return player;
}

void Table::startRound()
{
    assert(state == START_ROUND);

    currBet = 0;
    std::fill(playerBets.begin(), playerBets.end(), 0);

    if (numPlayers == 2 && currRound == 0) currPlayer = currDealer;
    else currPlayer = nextActivePlayer(currDealer);

    if (currRound == 0)
    {
        minRaise = 0;
        state = ACT;
        act(smallBlind);
        state = ACT;
        act(bigBlind);
        minRaise = 2 * bigBlind;
    }
    else
    {
        minRaise = bigBlind;
    }

    lastRoundAggressor = currPlayer;

    if ((int) sharedCards.size() < NUM_CARDS_IN_ROUND[currRound]) state = DEAL_CARD;
    else state = ACT;
}

void Table::endRound()
{
    assert(state == END_ROUND);

    ++currRound;

    if (currRound < NUM_ROUNDS) state = START_ROUND;
    else state = END_HAND_SHOWDOWN;
}

void Table::dealCard(Card card)
{
    assert(state == DEAL_CARD);

    sharedCards.push_back(card);

    if ((int) sharedCards.size() < NUM_CARDS_IN_ROUND[currRound]) state = DEAL_CARD;
    else state = ACT;
}

void Table::act(int playerBet)
{
    assert(state == ACT);

    assert(playerBet == FOLD_BET || playerBet == currBet || playerBet >= minRaise);
    assert(playerBet - playerBets[currPlayer] <= playerStacks[currPlayer]);

    if (playerBet == FOLD_BET)
    {
        playerActives[currPlayer] = false;
        --numActivePlayers;
    }
    else
    {
        int extra = playerBet - playerBets[currPlayer];
        playerBets[currPlayer] = playerBet;
        playerStacks[currPlayer] -= extra;
        pot += extra;

        if (playerBet > currBet)
        {
            minRaise = 2 * playerBet - currBet;
            currBet = playerBet;
            lastRoundAggressor = currPlayer;
            lastAggressor = currPlayer;
        }
    }

    currPlayer = nextActivePlayer(currPlayer);

    if (numActivePlayers == 1) state = END_HAND_FOLDS;
    else if (currPlayer == lastRoundAggressor) state = END_ROUND;
    else state = ACT;
}
