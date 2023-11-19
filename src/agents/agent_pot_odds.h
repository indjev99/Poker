#pragma once

#include "agent.h"
#include "rng.h"

struct AgentPotOdds : Agent
{
    AgentPotOdds();

    int getAction() override;

    RNG rng;

    static constexpr int NUM_TRIALS = 50;
};
