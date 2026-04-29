#pragma once
#include <map>
#include "Enums.hpp"

class Inventory {
public:
    std::map<SeedType, int> SeedCount;
    std::map<TrapType, int> TrapCount;
    int Bullets;

    Inventory();

    void AddSeed(SeedType type, int amount);
    bool UseSeed(SeedType type, int amount);

    void AddTrap(TrapType type, int amount);
    bool UseTrap(TrapType type, int amount);
};