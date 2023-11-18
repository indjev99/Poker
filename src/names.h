#pragma once

#include "card.h"
#include "hand.h"

#include <string>

std::string rankName(uint8_t rank);
std::string suitName(uint8_t suit);
std::string cardName(const Card& card);
std::string handName(const Hand& hand);
