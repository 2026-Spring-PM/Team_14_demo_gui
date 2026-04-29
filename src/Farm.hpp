#pragma once
#include <vector>
#include "Seed.hpp"
#include "Trap.hpp"

class Farm {
public:
    static const int ROWS = 77; // TODO : 기획에 맞게 수정
    static const int COLS = 77;

    Seed* SeedField[ROWS][COLS];
    Trap* TrapField[ROWS][COLS];

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
    void UpdateFields();

    void TriggerDayRandomEvent();
    void TriggerNightRandomEvent();

    void RenderFarm();
};