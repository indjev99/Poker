#pragma once

#include "agent.h"
#include "rng.h"

struct AgentPotOdds : Agent
{
    AgentPotOdds(int version = 0);

    int getAction() override;

    int version;

    RNG rng;

    static constexpr int NUM_TRIALS = 50;
};
