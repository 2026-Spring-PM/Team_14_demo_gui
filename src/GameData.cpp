#include "GameData.hpp"

const std::map<SeedType, SeedData> GameData::SeedTable = {
    // TODO: 기획에 맞춰 새 씨앗 수치 추가
    // {SeedType::Sunflower, {"SunFlower", 10, 20, 60}} 등
    {SeedType::WHEAT,  {.Name = "밀",   .Price = 5,  .Value = 10, .CoolDown = 30}},
    {SeedType::POTATO, {.Name = "감자", .Price = 10, .Value = 20, .CoolDown = 60}},
    {SeedType::CARROT, {.Name = "당근", .Price = 20, .Value = 35, .CoolDown = 60}}
};

const std::map<TrapType, TrapData> GameData::TrapTable = {
    // TODO: 기획에 맞춰 새 함정 수치 추가
    // {TrapType::Sheep, {"Sheep", 50, 10, 5, {1, 1}}} 등
    {TrapType::COW,   {.Name = "소",   .Price = 40, .Atk = 10, .CoolDown = 5, .Range = {1, 1}}},
    {TrapType::PIG,   {.Name = "돼지", .Price = 50, .Atk = 10, .CoolDown = 5, .Range = {2, 2}}},
    {TrapType::HORSE, {.Name = "말",   .Price = 60, .Atk = 20, .CoolDown = 2, .Range = {1, 1}}}
};

const std::map<EnemyType, EnemyData> GameData::EnemyTable = {
    // TODO: 기획에 맞춰 새 함정 수치 추가
    // {EnemyType::Bandit, {10, 100}} 등
};
