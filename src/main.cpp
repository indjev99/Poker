#include "table.h"
#include "dealer.h"
#include "agent.h"
#include "agents/agent_io.h"
#include "agents/agent_bet_call.h"

#include <iostream>
#include <iomanip>

int main()
{
    int numPlayers = 6;
    int bigBlind = 10;
    int buyIn = 2000;

    Table table(numPlayers, bigBlind, buyIn);

    std::vector<Agent*> agents = {
        new AgentBetCall(),
        new AgentBetCall(),
        new AgentBetCall(),
        new AgentBetCall(),
        new AgentBetCall(),
        new AgentBetCall()
    };

    std::vector<Agent*> spectators = {
        // new AgentIO()
    };

    Dealer dealer(&table, agents, spectators);

    int numHands = 0;

    while (true)
    {
        dealer.playHand();

        ++numHands;

        if (numHands % 10000 == 0)
        {
            std::cout << std::setw(4) << numHands / 1000 << "k" << ":";
            for (int pnl : table.playerPnls)
            {
                std::cout << " " << std::fixed << std::setprecision(2) << std::setw(7) << (double) pnl / numHands;
            }
            std::cout << std::endl;
        }
    }

    return 0;
}
