#pragma once
#include <cmath>
#include <cstdlib>

#include "Enums.hpp"

// TODO: Enemy 함수 세부 구현 필요!
// EnemyType는 level이 올라감에 따라 어려운 적 많이 나오게
// EnemyType 및 level에 따라 및의 함수들은 다른 값을 return 하도록 만들기.

int EnemyCount(int level) {
    return static_cast<int>(std::sqrt(level)) + 10;
}

EnemyType EnemyTypeSet(int level) {
    return EnemyType::NONE;
}

int EnemySpeed(int level, EnemyType type) {
    return 1111; // TODO: 구현 (김진형)
}

int EnemyHealthPoint(int level, EnemyType type) {
    return 1111; // TODO: 구현 (김진형)
}

int EnemyCoolDown(int level, EnemyType type) {
    return 1111; // TODO: 구현 또는 빼기
}

int SpawnDelay(NightType type) {
    // TODO: EARLY와 LATE가 다른 분포를 따르도록 변경 (김진형)
    int delay = 0;

    switch (type) {
        case NightType::EARLY:
            delay = std::rand() % 301;
            break;
        case NightType::NORMAL:
            delay = std::rand() % 601;
            break;
        case NightType::LATE:
            delay = std::rand() % 301 + 300;
            break;
    }

    return delay;
}

NightType SetNightType() {
    int mode = std::rand() % 6;
    NightType type;

    switch (mode) {
        case 0:
            type = NightType::EARLY;
            break;
        case 5:
            type = NightType::LATE;
            break;
        default:
            type = NightType::NORMAL;
            break;
    }

    return type;
}

// TODO: 게임 테스트 후, 발생 확률 늘리거나 줄이기
bool DroughtTrigger() {
    int randVal = std::rand() % 100;
    if (randVal < 10) return true;
    else return false;
}

bool PestTrigger() {
    int randVal = std::rand() % 100;
    if (randVal < 20) return true;
    else return false;
}

bool TrapBreakTrigger() {
    int randVal = std::rand() % 100;
    if (randVal < 15) return true;
    else return false;
}