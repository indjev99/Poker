#include "table.h"
#include "dealer.h"
#include "agent.h"
#include "agents/agent_io.h"

#include <iostream>

int main()
{
    int numPlayers = 2;
    int bigBlind = 10;
    int buyIn = 200;

    Table table(numPlayers, bigBlind, buyIn);

    std::vector<Agent*> agents = {
        new AgentIO(),
        new Agent()
    };

    std::vector<Agent*> spectators = {};

    Dealer dealer(table, agents, spectators);

    while (true)
    {
        dealer.playHand();
    }

    return 0;
}
