#include "SaveState.hpp"

SaveState::SaveState() : Life(1), Money(0) {}

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