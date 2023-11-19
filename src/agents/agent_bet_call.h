#pragma once

#include "agent.h"

struct AgentBetCall : Agent
{
    int getAction() override
    {
        if (table->currBet == 0 && table->minRaise - table->playerBets[selfIdx] <= table->playerStacks[selfIdx])
            return table->minRaise;
        else if (table->currBet - table->playerBets[selfIdx] <= table->playerStacks[selfIdx])
            return table->currBet;
        else
            return FOLD_BET;
    }
};
