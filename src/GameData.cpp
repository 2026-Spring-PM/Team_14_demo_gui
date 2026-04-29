#include "GameData.hpp"

const std::map<SeedType, SeedData> GameData::SeedTable = {
    // TODO: 기획에 맞춰 새 씨앗 수치 추가
    // {SeedType::Sunflower, {"SunFlower", 10, 20, 60}} 등  
};

const std::map<TrapType, TrapData> GameData::TrapTable = {
    // TODO: 기획에 맞춰 새 함정 수치 추가
    // {TrapType::Sheep, {"Sheep", 50, 10, 5, {1, 1}}} 등  
};

const std::map<EnemyType, EnemyData> GameData::EnemyTable = {
    // TODO: 기획에 맞춰 새 함정 수치 추가
    // {EnemyType::Bandit, {10, 100}} 등
};
