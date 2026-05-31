#pragma once
#include <string>
#include <utility>
#include <algorithm>
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

    void Attack(std::vector<Enemy> &ActiveEnemies);
    void UpdateTimer();
    void Breakdown();
    bool InRange(Enemy& enemy);

    friend class Farm;
};

Trap::Trap()
: Name(""), Price(0), Atk(0), CoolDown(0), Timer(0), Pos({0, 0}), Range({0,0}), Type(TrapType::NONE), TrapState(State::NONE) {}

Trap::Trap(std::string name, int price, int atk, int cooldown, std::pair<int, int> pos, std::pair<int, int> range, TrapType type)
: Name(name), Price(price), Atk(atk), CoolDown(cooldown), Timer(0), Pos(pos), Range(range), Type(type), TrapState(State::ALIVE) {}

void Trap::Attack(std::vector<Enemy> &ActiveEnemies) {
    UpdateTimer();
    if (Timer == CoolDown) {
        std::sort(ActiveEnemies.begin(), ActiveEnemies.end());
        for (auto& enemy : ActiveEnemies) {
            if (InRange(enemy)) {
                enemy.TakeDamage(Atk); // 범위 공격 시 하나만 공격하게 바꿈
                break;
            }
        }
        Timer = 0;
    }
}

void Trap::UpdateTimer() {
    if (TrapState == State::ALIVE && Timer < CoolDown) Timer++;
}

void Trap::Breakdown() {
    TrapState = State::DEAD;
}

bool Trap::InRange(Enemy& enemy) {
    // TODO: UI 구현후, 구현된 화면에 따라 범위에 들어오는 것을 체크
    return true;
}