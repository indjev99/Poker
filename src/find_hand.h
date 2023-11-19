#pragma once

#include "card.h"
#include "hand.h"

#include <vector>

Hand findBestHand(const std::vector<const std::vector<Card>*>& cardsLists);