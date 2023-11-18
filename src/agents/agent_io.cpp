#include "agents/agent_io.h"
#include "names.h"

#include <iostream>

void AgentIO::handStarted()
{
    std::cout << std::endl;
    std::cout << "Hand started" << std::endl;
    std::cout << "Num players: " << table->numPlayers << std::endl;
    std::cout << "Small blind: " << table->bigBlind << std::endl;
    std::cout << "Big blind: " << table->bigBlind << std::endl;
    std::cout << "Buy in: " << table->buyIn << std::endl;
    std::cout << "Button: " << table->currDealer + 1 << std::endl;
    std::cout << std::endl;

    if (allHoleCards)
    {
        int idx = 0;
        for (const HoleCards& holeCards : *allHoleCards)
        {
            std::cout << "Player: " << idx + 1 << std::endl;
            std::cout << "Hole cards:";
            for (Card card : holeCards.cards)
            {
                std::cout << " " << cardName(card);
            }
            std::cout << std::endl;
            std::cout << std::endl;
            ++idx;
        }
    }
    else if (selfHoleCards)
    {
        std::cout << "Player: " << selfIdx + 1 << std::endl;
        std::cout << "Hole cards:";
        for (Card card : selfHoleCards->cards)
        {
            std::cout << " " << cardName(card);
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}

void AgentIO::handEndedFolds(int winner)
{
    std::cout << "Winner: " << winner + 1 << std::endl;
    std::cout << std::endl;
}

void AgentIO::handToEndShowdown(const std::vector<int>& players)
{
    std::cout << "Showdown starting" << std::endl;
    std::cout << std::endl;
}

void AgentIO::playerShowdownRevealed(int player, const HoleCards& holeCards, const Hand& hand)
{
    std::cout << "Player: " << player + 1 << std::endl;
    std::cout << "Hole cards:";
    for (Card card : holeCards.cards)
    {
        std::cout << " " << cardName(card);
    }
    std::cout << std::endl;
    std::cout << "Hand: " << handName(hand) << std::endl;
    std::cout << std::endl;
}

void AgentIO::handEndedShowdown(const std::vector<int>& winners, const Hand& hand)
{
    std::cout << "Winners:";
    for (int winner : winners)
    {
        std::cout << " " << winner + 1;
    }
    std::cout << std::endl;
    std::cout << "Hand: " << handName(hand) << std::endl;
    std::cout << std::endl;
}

void AgentIO::roundStarted()
{
    std::cout << "Shared cards:";
    for (Card card : table->sharedCards)
    {
        std::cout << " " << cardName(card);
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void AgentIO::roundEnded()
{
    std::cout << "Betting ended" << std::endl;
    std::cout << std::endl;
}

void AgentIO::playerToAct(int player)
{
    std::cout << "Player: " << player + 1 << std::endl;

    const HoleCards* holeCards = nullptr;
    if (allHoleCards) holeCards = &(*allHoleCards)[player];
    else if (selfHoleCards && player == selfIdx) holeCards = selfHoleCards;
    if (holeCards)
    {
        std::cout << "Hole cards:";
        for (Card card : holeCards->cards)
        {
            std::cout << " " << cardName(card);
        }
        std::cout << std::endl;
    }

    std::cout << "Stack: " << table->playerStacks[player] << std::endl;
    if (table->playerBets[player])
        std::cout << "Curr bet: " << table->playerBets[player] << std::endl;
    std::cout << "Pot: " << table->pot << std::endl;
    if (table->currBet)
        std::cout << "To call: " << table->currBet << std::endl;
    std::cout << "Min raise: " << table->minRaise << std::endl;

    oldPlayerBet = table->playerBets[player];
    oldBet = table->currBet;
}

void AgentIO::playerActed(int player, int bet)
{
    if (bet == FOLD_BET) std::cout << "Fold" << std::endl;
    else if (bet == oldPlayerBet) std::cout << "Check" << std::endl;
    else if (bet == oldBet) std::cout << "Call" << std::endl;
    else if (oldBet == 0) std::cout << "Bet: " << bet << std::endl;
    else std::cout << "Raise: " << bet << std::endl;
    std::cout << std::endl;
}

int AgentIO::getAction()
{
    int bet;
    std::cout << "Bet: ";
    std::cin >> bet;
    return bet;
}
