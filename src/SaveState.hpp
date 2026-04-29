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