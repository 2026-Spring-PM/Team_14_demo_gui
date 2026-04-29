#include "Farm.hpp"
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
    SeedField[r][c] = new Seed();
    AddTime(TimeWaste::SEEDSET);
    return true;
}

void Farm::WaterSeed(int r, int c) {
    if (SeedField[r][c] != nullptr) {
        SeedField[r][c]->Humid = 100;
        AddTime(TimeWaste::WATERING);
    }
}

bool Farm::InstallTrap(int r, int c, TrapType type) {
    if (TrapField[r][c] != nullptr) return false;
    TrapField[r][c] = new Trap();
    AddTime(TimeWaste::TRAPSET);
    return true;
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
    // TODO: 낮 이벤트 발생 로직 구현 (가뭄, 병충해)
}

void Farm::TriggerNightRandomEvent() {
    // TODO: 밤 이벤트 발생 로직 구현 (설치된 Trap 중 N개 Breakdown)
}