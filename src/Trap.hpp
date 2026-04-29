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

    void Render(); // TODO: UI 팀원이 작성할 렌더링 함수
};