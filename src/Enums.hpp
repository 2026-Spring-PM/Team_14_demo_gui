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

enum class NightType {
    NORMAL,
    EARLY,
    UNIFORM,
    LATE,
};

enum class SeedType {
    NONE,
    SEED1, SEED2, SEED3, // 👈 기존 UI에서 쓰던 기본 명칭
    WHEAT = SEED1, POTATO = SEED2, CARROT = SEED3 // 👈 정산창에서 쓸 별칭들!
};

enum class TrapType {
    NONE,
    ANIMAL1, ANIMAL2, ANIMAL3,
    COW = ANIMAL1, PIG = ANIMAL2, HORSE = ANIMAL3 
};
enum class EnemyType {
    NONE,
    ENEMY1,
    ENEMY2,
    // TODO: 이름 변경 및 추가
};
