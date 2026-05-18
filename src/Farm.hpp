#pragma once
#include <vector>
#include <cstdlib>

#include "Seed.hpp"
#include "Trap.hpp"
#include "Farm.hpp"
#include "Mechanism.hpp"
#include "Enemy.hpp"
#include "GameData.hpp"

class Farm {
public:
    static const int ROWS = 77; // TODO: ROWS와 COLS를 UI에 맞게 수정
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
    void UpdateEnemies();
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
    if (SeedField[r][c] != nullptr) return false;

    auto it = GameData::SeedTable.find(type);
    if (it != GameData::SeedTable.end()) {
        const SeedData& data = it->second;

        SeedField[r][c] = new Seed(data.Name, data.Price, data.Value, data.CoolDown, type);
        AddTime(GameData::InstallPlantTimeCost);
        return true;
    }
    return false;
}

void Farm::WaterSeed(int r, int c) {
    if (SeedField[r][c] != nullptr) {
        SeedField[r][c]->Humid = 100;
        AddTime(GameData::WateringTimeCost);
    }
}

bool Farm::InstallTrap(int r, int c, TrapType type) {
    if (TrapField[r][c] != nullptr) return false;
    std::pair<int, int> pos = {r, c};

    auto it = GameData::TrapTable.find(type);
    if (it != GameData::TrapTable.end()) {
        const TrapData& data = it->second;

        TrapField[r][c] = new Trap(data.Name, data.Price, data.Atk, data.CoolDown, pos, data.Range, type);
        AddTime(GameData::InstallTrapTimeCost);
        return true;
    }
    return false;
}

void Farm::TriggerDayRandomEvent() {
    IsDrought = DroughtTrigger();
    IsPest = PestTrigger();
}

void Farm::TriggerNightRandomEvent() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (TrapField[r][c] != nullptr && TrapField[r][c]->TrapState == State::ALIVE) {
                if (TrapBreakTrigger()) TrapField[r][c]->Breakdown();
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
            if (SeedField[r][c] != nullptr) {
                if (SeedField[r][c]->FieldState == State::DEAD) {
                    delete SeedField[r][c];
                    SeedField[r][c] = nullptr;
                }
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

void Farm::UpdateEnemies() {
    for (auto it = ActiveEnemies.begin(); it != ActiveEnemies.end();) {
        if (it->EnemyState == State::DEAD) {
            // state.AddMoney(); // 적 사망 시 돈 추가하고 싶으면 코드 추가 -> 이후 업데이트 시 있는 게 좋다면 추가
            it = ActiveEnemies.erase(it);
        }
        else if (it->EnemyState == State::ALIVE){
            it->Move(0.016f);

            if (it->Pos >= 100) { // TODO: UI에 따라 100이라는 숫자 조정
                if (!state.TakeDamage()) {
                    // status = Status::GAMEOVER; // TODO: FIX
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