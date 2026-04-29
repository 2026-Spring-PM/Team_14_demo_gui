#include "Farm.hpp"
#include "Mechanism.hpp"
#include "GameData.hpp"
#include <cstdlib>

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

void Farm::UpdateFields() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (SeedField[r][c] != nullptr) {
                if (SeedField[r][c]->FieldState == State::DEAD) {
                    delete SeedField[r][c];
                    SeedField[r][c] = nullptr;
                }
            }

            if (TrapField[r][c] != nullptr) {
                if (TrapField[r][c]->TrapState == State::DEAD) {
                    delete TrapField[r][c];
                    TrapField[r][c] = nullptr;
                }
            }
        }
    }
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