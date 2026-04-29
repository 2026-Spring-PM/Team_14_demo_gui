#include "Trap.hpp"

Trap::Trap() : Name(""), Price(0), Atk(0), CoolDown(0), Timer(0), Range({0,0}), Type(TrapType::None), isBroken(false) {}

Trap::Trap(std::string name, int price, int atk, int cooldown, std::pair<int, int> range, TrapType type)
    : Name(name), Price(price), Atk(atk), CoolDown(cooldown), Timer(0), Range(range), Type(type), isBroken(false) {}

void Trap::UpdateTimer() {
    if (!isBroken && Timer < CoolDown) Timer++;
}

void Trap::Attack(Enemy *enemy) {
    if (isBroken || Timer < CoolDown) return;
    // TODO: Range 내의 적을 탐색하여 Atk만큼 체력 감소 구현
    Timer = 0; // 공격 후 쿨타임 초기화
}

void Trap::Breakdown() {
    isBroken = true;
}

void Trap::FeedSeed() {
    // TODO: 인벤토리의 특정 농작물 소모 로직과 연계하여 작동 여부 활성화
}