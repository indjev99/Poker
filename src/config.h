#pragma once

constexpr int NUM_RANKS = 13;
constexpr int NUM_SUITS = 4;
constexpr int NUM_CARDS = NUM_RANKS * NUM_SUITS;

constexpr int NUM_HAND_CARDS = 5;

constexpr int NUM_HOLE_CARDS = 2;
constexpr int NUM_SHARED_CARDS = 5;

constexpr int NUM_ROUNDS = 4;
constexpr int NUM_CARDS_IN_ROUND[NUM_ROUNDS] = {0, 3, 4, 5};
