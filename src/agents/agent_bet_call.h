#pragma once

#include "agent.h"

struct AgentBetCall : Agent
{
    int getAction() override
    {
        if (table->currBet == 0) return table->minRaise;
        else return table->currBet;
    }
};
