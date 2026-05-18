#pragma once
#include <vector>
#include <cstdlib>

#include "Seed.hpp"
#include "Trap.hpp"
#include "Farm.hpp"
#include "Mechanism.hpp"
#include "Enemy.hpp"
#include "GameData.hpp"
#include "Inventory.hpp"

class Farm {
public:
    static const int ROWS = 77; // TODO: ROWS와 COLS를 UI에 맞게 수정. 아마 Trap과 Seed의 ROW와 COL이 다를 것이므로, 바꾸기.
    static const int COLS = 77;

    Seed* SeedField[ROWS][COLS];
    Trap* TrapField[ROWS][COLS];

    std::vector<Enemy> ActiveEnemies;
    std::vector<Enemy> PendingEnemies;

    int Day;
    int Hour;
    int Minute;

    bool IsDrought;
    bool IsPest;

    Farm();
    ~Farm();

    void AddTime(int minutes);
    bool PlantSeed(int r, int c, SeedType type);
    void WaterSeed(int r, int c);
    bool InstallTrap(int r, int c, TrapType type);

    void UpdateTraps();
    void UpdateFarms();
    void SpawnEnemies(int NightElapsedMinutes);
    void UpdateEnemies(Status &status, Inventory &inventory);
    void AddEnemies(int level, NightType night);

    bool EnemiesEmpty();
    void EnemiesClear();

    void TriggerDayRandomEvent();
    void TriggerNightRandomEvent();
};

Farm::Farm() : Day(1), Hour(6), Minute(0), IsDrought(false), IsPest(false) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            SeedField[i][j] = nullptr;
            TrapField[i][j] = nullptr;
        }
    }
}

Farm::~Farm() {
    for (int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if(SeedField[i][j]) delete SeedField[i][j];
            if (TrapField[i][j]) delete TrapField[i][j];
        }
    }
}

void Farm::AddTime(int minutes) {
    Minute += minutes;
    Hour += Minute / 60;
    Minute %= 60;
    Day += Hour / 24;
    Hour %= 24;
}

bool Farm::PlantSeed(int r, int c, SeedType type) {
    Seed *seed = SeedField[r][c];
    if (seed != nullptr) return false;

    auto it = GameData::SeedTable.find(type);
    if (it != GameData::SeedTable.end()) {
        const SeedData& data = it->second;

        seed = new Seed(data.Name, data.Price, data.Value, data.CoolDown, type); // TODO: 이 부분 Required C++ components의 다른 개념 (friend나 template 등)을 사용해서 재구현
        AddTime(GameData::InstallPlantTimeCost);
        return true;
    }
    return false;
}

void Farm::WaterSeed(int r, int c) {
    Seed *seed = SeedField[r][c];
    if (seed != nullptr) {
        seed->Water();
        AddTime(GameData::WateringTimeCost);
    }
}

bool Farm::InstallTrap(int r, int c, TrapType type) {
    Trap *trap = TrapField[r][c];
    if (trap != nullptr) return false;
    std::pair<int, int> pos = {r, c};

    auto it = GameData::TrapTable.find(type);
    if (it != GameData::TrapTable.end()) {
        const TrapData& data = it->second;

        trap = new Trap(data.Name, data.Price, data.Atk, data.CoolDown, pos, data.Range, type); // TODO: 마찬가지
        AddTime(GameData::InstallTrapTimeCost);
        return true;
    }
    return false;
}

void Farm::TriggerDayRandomEvent() {
    IsDrought = DroughtTrigger();

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            Seed *seed = SeedField[r][c];
            if (seed != nullptr && seed->FieldState == State::ALIVE) {
                if (PestTrigger()) seed->Kill();
            }
        }
    }
}

void Farm::TriggerNightRandomEvent() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            Trap *trap = TrapField[r][c];
            if (trap != nullptr && trap->TrapState == State::ALIVE) {
                if (TrapBreakTrigger()) trap->Breakdown();
            }
        }
    }
}

void Farm::UpdateTraps() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            Trap* trap = TrapField[r][c];
            if (trap != nullptr) trap->Attack(ActiveEnemies);
        }
    }
}

void Farm::UpdateFarms() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            Seed* seed = SeedField[r][c];
            if (seed != nullptr) {
                if (seed->FieldState == State::DEAD) {
                    delete seed;
                    seed = nullptr;
                } else seed->Update(IsDrought);
            }
        }
    }
}

void Farm::SpawnEnemies(int NightElapsedMinutes) {
    for (auto it = PendingEnemies.begin(); it != PendingEnemies.end();) {
        if (NightElapsedMinutes >= it->SpawnDelay) {
            ActiveEnemies.push_back(*it);
            it = PendingEnemies.erase(it);
        } else ++it;
    }
}

void Farm::AddEnemies(int Level, NightType night) {
    int enemycount = EnemyCount(Level);

    for(int i = 0; i < enemycount; i++) {
        EnemyType type = EnemyTypeSet(Level);
        int speed = EnemySpeed(Level, type);
        int cooldown;
        int hp;

        Enemy newEnemy(static_cast<float>(speed), 8.0f, type, cooldown, hp);
        newEnemy.SpawnDelay = SpawnDelay(night);
        PendingEnemies.push_back(newEnemy);
    }
}

void Farm::UpdateEnemies(Status &status, Inventory &inventory) {
    for (auto it = ActiveEnemies.begin(); it != ActiveEnemies.end();) {
        if (it->EnemyState == State::DEAD) {
            // AddMoney(); // 적 사망 시 돈 추가하고 싶으면 코드 추가 -> 이후 업데이트 시 있는 게 좋다면 추가
            it = ActiveEnemies.erase(it);
        }
        else if (it->EnemyState == State::ALIVE){
            if (it->Move(0.016f)) {
                inventory.Bullets--;
                if (inventory.Bullets < 0) {
                    status = Status::GAMEOVER;
                    return;
                }
                it = ActiveEnemies.erase(it);
            }
            else ++it;
        }
    }
}

bool Farm::EnemiesEmpty() {
    return PendingEnemies.empty() && ActiveEnemies.empty();
}

void Farm::EnemiesClear() {
    ActiveEnemies.clear();
    PendingEnemies.clear();
}