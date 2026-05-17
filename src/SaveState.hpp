#pragma once
#include "Farm.hpp"
#include "Inventory.hpp"

class SaveState {
public:
    int Money;
    Farm farm;
    Inventory inventory;

    SaveState();

    void AddMoney(int amount);
    bool SpendMoney(int amount);
    bool TakeDamage();
};

SaveState::SaveState() : Money(0) {}

void SaveState::AddMoney(int amount) {
    Money += amount;
}

bool SaveState::SpendMoney(int amount) {
    if(Money >= amount) {
        Money -= amount;
        return true;
    }
    return false;
}

bool SaveState::TakeDamage() {
    if (inventory.Bullets > 0) {
        inventory.Bullets--;
        return true;
    }
    return false;
}