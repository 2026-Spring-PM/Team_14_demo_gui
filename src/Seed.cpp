#include "Seed.hpp"

Seed::Seed() : Name(""), Price(0), Value(0), CoolDown(0), Timer(0), Humid(100), HumidTimer(0), Type(SeedType::NONE), FieldState(State::NONE) {}

Seed::Seed(std::string name, int price, int value, int cooldown, SeedType type)
    : Name(name), Price(price), Value(value), CoolDown(cooldown), Timer(0), Humid(100), HumidTimer(0), Type(type), FieldState(State::NONE) {}

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

void Seed::IsDead() {
    if(HumidTimer >= 30) FieldState = State::DEAD;
}

bool Seed::IsGrown() const {
    return Timer >= CoolDown;
}

void Render() {
    // TODO : 현재 Field State에 따라 렌더링 구현
}