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

Inventory::Inventory() : Bullets(0) {
    SeedCount[SeedType::NONE] = 0;
    TrapCount[TrapType::NONE] = 0;
}

void Inventory::AddSeed(SeedType type, int amount) {
    SeedCount[type] += amount;
}

bool Inventory::UseSeed(SeedType type, int amount) {
    if (SeedCount[type] >= amount) {
        SeedCount[type] -= amount;
        return true;
    }
    return false;
}

void Inventory::AddTrap(TrapType type, int amount) {
    TrapCount[type] += amount;
}

bool Inventory::UseTrap(TrapType type, int amount) {
    if (TrapCount[type] >= amount) {
        TrapCount[type] -= amount;
        return true;
    }
    return false;
}