#include "Mechanism.hpp"
#include <cmath>

// TODO: 아래의 모든 상수값은 테스트 후 괜찮은 수치로 조정 필요.

int EnemyCount(int level) {
    return static_cast<int>(std::sqrt(level)) + 10;
}

int EnemySpeed(int level) {
    return static_cast<int>(std::log(level + 1) * 2) + 1;
}

int SpawnDelay(NightType type) {
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