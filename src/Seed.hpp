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

    void Update(bool isDrought);
    void UpdateHumid(bool isDrought);
    void UpdateTimer();
    void CheckDead();
    void Kill();
    bool IsGrown() const;

    void Water();

    friend class Farm;
};

Seed::Seed()
: Name(""), Price(0), Value(0), CoolDown(0), Timer(0), Humid(100), HumidTimer(0), Type(SeedType::NONE), FieldState(State::NONE) {}

Seed::Seed(std::string name, int price, int value, int cooldown, SeedType type)
: Name(name), Price(price), Value(value), CoolDown(cooldown), Timer(0), Humid(100), HumidTimer(0), Type(type), FieldState(State::NONE) {}

void Seed::Update(bool isDrought) {
    UpdateHumid(isDrought);
    UpdateTimer();
    CheckDead();
}

void Seed::UpdateHumid(bool isDrought) {
    int decrement = isDrought ? 2 : 1;
    Humid -= decrement;
    if (Humid < 0) Humid = 0;
    if (Humid == 0) HumidTimer += 10;
    else HumidTimer = 0;
}

void Seed::UpdateTimer() {
    if (Humid > 0) Timer++;
}

void Seed::CheckDead() {
    if(HumidTimer >= 30) FieldState = State::DEAD;
}

void Seed::Kill() {
    FieldState = State::DEAD;
}

bool Seed::IsGrown() const {
    return Timer >= CoolDown;
}

void Seed::Water() {
    Humid = 100;
}