#pragma once

enum class State {
    NONE,
    ALIVE,
    DEAD
};

enum class Status {
    MAIN,
    AM,
    PM,
    PAUSE,
    SHOP,
    GAMEOVER,
    SETTLEMENT
};

enum class RandomEvent {
    NONE,
    DROUGHT,
};

enum class SeedType {
    NONE,
    SEED1,
    SEED2,
    SEED3,
    // TODO: 이름 변경 및 추가
};

enum class NightType {
    NORMAL,
    EARLY,
    UNIFORM,
    LATE,
};

enum class TrapType {
    NONE,
    ANIMAL1,
    ANIMAL2,
    ANIMAL3,
    // TODO: 이름 변경 및 추가
};

enum class EnemyType {
    NONE,
    ENEMY1,
    ENEMY2,
    // TODO: 이름 변경 및 추가
};
