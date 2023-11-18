#pragma once

#include "card.h"
#include "hand.h"

#include <vector>

Hand findBestHand(const std::vector<std::vector<Card>>& cardsLists);