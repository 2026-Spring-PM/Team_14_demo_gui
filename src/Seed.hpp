#pragma once
#include <string>
#include "Enums.hpp"

class Seed {
public:
    std::string Name;
    int Price;
    int Value;
    int CoolDown;
    int Timer;
    int Humid;
    int HumidTimer;
    State FieldState;
    SeedType Type;

    Seed();
    Seed(std::string name, int price, int value, int cooldown, SeedType type);

    void UpdateHumid(bool isDrought);
    void UpdateTimer();
    void IsDead();
    bool IsGrown() const;

    void Render();
};