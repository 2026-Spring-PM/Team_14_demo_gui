#pragma once

enum class State {
    NONE,
    ALIVE,
    DEAD
};

enum class SeedType {
    NONE,
    SEED1,
    SEED2,
    // TODO: 이후 추가
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
    // TODO: 이후 추가
};

enum class EnemyType {
    NONE,
    ENEMY1,
    ENEMY2,
    // TODO: 이후 추가
};

enum class Status {
    AM,
    PM,
    PAUSE,
    SHOP,
    GAMEOVER,
    MAIN
};