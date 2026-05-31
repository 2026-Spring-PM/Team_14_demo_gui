#pragma once
#include <cmath>
#include <cstdlib>
#include "Enums.hpp"
#include "GameData.hpp"

inline int EnemyCount(int level) {
    return static_cast<int>(std::sqrt(level)) + 10;
}

inline EnemyType EnemyTypeSet(int level) {
    int randVal = std::rand() % 100;

    if (level <= 3) {
        if (randVal < 70) return EnemyType::ENEMY1;
        else return EnemyType::ENEMY2; // 기존 RAT에서 ENEMY2로 수정
    }
    else if (level <= 7) {
        if (randVal < 30) return EnemyType::ENEMY1;
        if (randVal < 85) return EnemyType::ENEMY2;
        else return EnemyType::ENEMY3;
    }
    else {
        if (randVal < 10) return EnemyType::ENEMY1;
        if (randVal < 50) return EnemyType::ENEMY2;
        else return EnemyType::ENEMY3;
    }
}

inline int EnemySpeed(int level, EnemyType type) {
    int baseSpeed = 10;
    
    switch (type) {
        case EnemyType::ENEMY1: baseSpeed = 15; break; 
        case EnemyType::ENEMY2: baseSpeed = 10; break;
        case EnemyType::ENEMY3: baseSpeed = 12; break;
        // 기존 RAT 케이스 삭제 완료
        default: break;
    }

    return baseSpeed + (level / 2);
}

inline int EnemyHealthPoint(int level, EnemyType type) {
    int baseHP = 10;

    auto it = GameData::EnemyTable.find(type);
    if (it != GameData::EnemyTable.end()) {
        baseHP = it->second.HP;
    }

    return baseHP + ((level - 1) * 5);
}

inline int EnemyCoolDown(int level, EnemyType type) {
    int baseCoolDown = 50;

    auto it = GameData::EnemyTable.find(type);
    if (it != GameData::EnemyTable.end()) {
        baseCoolDown = it->second.CoolDown;
    }

    int finalCoolDown = baseCoolDown - (level * 2);
    return finalCoolDown < 10 ? 10 : finalCoolDown;
}

inline int SpawnDelay(NightType type) {
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

inline NightType SetNightType() {
    int mode = std::rand() % 6;
    NightType type;

    switch (mode) {
        case 0:  type = NightType::EARLY; break;
        case 5:  type = NightType::LATE;  break;
        default: type = NightType::NORMAL; break;
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