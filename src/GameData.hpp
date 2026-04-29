#pragma once
#include <map>
#include <string>
#include <utility>
#include "Enums.hpp"

struct SeedData {
    std::string Name;
    int Price;
    int Value;
    int CoolDown;
};

struct TrapData {
    std::string Name;
    int Price;
    int Atk;
    int CoolDown;
    std::pair<int, int> Range;
};

struct EnemyData {
    int HP;
    int CoolDown;
};

class GameData {
public:
    static const std::map<SeedType, SeedData> SeedTable;
    static const std::map<TrapType, TrapData> TrapTable;
    static const std::map<EnemyType, EnemyData> EnemyTable;
    
    static const int ShoppingTimeCost = 10;
    static const int InstallPlantTimeCost = 5;
    static const int InstallTrapTimeCost = 10;
    static const int WateringTimeCost = 10;
    static const int GamblingTimeCost = 1;
};
