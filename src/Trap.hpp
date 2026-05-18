#pragma once
#include <string>
#include <utility>
#include "Enums.hpp"
#include "Enemy.hpp"

class Trap {
public:
    std::string Name;
    int Price;
    int Atk;
    int CoolDown;
    int Timer;
    std::pair<int, int> Pos;
    std::pair<int, int> Range;
    TrapType Type;
    State TrapState;

    Trap();
    Trap(std::string name, int price, int atk, int cooldown, std::pair<int, int> Pos, std::pair<int, int> range, TrapType type);

    void UpdateTimer();
    void Attack(Enemy* enemy);
    void Breakdown();
    void FeedSeed();
    bool InRange(Enemy& enemy);
};

Trap::Trap() : Name(""), Price(0), Atk(0), CoolDown(0), Timer(0), Pos({0, 0}), Range({0,0}), Type(TrapType::NONE), TrapState(State::NONE) {}

Trap::Trap(std::string name, int price, int atk, int cooldown, std::pair<int, int> pos, std::pair<int, int> range, TrapType type)
    : Name(name), Price(price), Atk(atk), CoolDown(cooldown), Timer(0), Pos(pos), Range(range), Type(type), TrapState(State::ALIVE) {}

void Trap::UpdateTimer() {
    if (TrapState == State::ALIVE && Timer < CoolDown) Timer++;
}

void Trap::Attack(Enemy* enemy) {
    if (TrapState == State::DEAD || Timer < CoolDown) return;
    enemy->TakeDamage(Atk);
    Timer = 0;
}

void Trap::Breakdown() {
    TrapState = State::DEAD;
}

void Trap::FeedSeed() {
    // TODO: 인벤토리의 특정 농작물 소모 로직과 연계하여 작동 여부 활성화
}

bool Trap::InRange(Enemy& enemy) {
    // TODO: UI 구현후, 구현된 화면에 따라 범위에 들어오는 것을 체크
    return true;
}