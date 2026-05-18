#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Enums.hpp"
#include "Enemy.hpp"
#include "GameState.hpp"
#include "Mechanism.hpp"
#include "GameData.hpp"
#include "Farm.hpp"
#include "Inventory.hpp"

class GameState {
public:
    Status status;
    Farm farm;
    Inventory inventory;

    int Level;
    int NightElapsedMinutes;
    int Money;
    NightType night;

    int PlaybackSpeed;
    int TickCounter;

    GameState();

    void Update();

    bool CanVisitShop();
    bool CanPlayMiniGame();

    void ChangePlaybackSpeed(int speed);

    void TransitionToNight();
    RandomEvent TransitionToDay();

    void PlayBGM(Status currentStatus);
    
    bool showInv = false;

    SeedType selectedSeed = SeedType::NONE; 
    TrapType selectedTrap = TrapType::NONE;

    int targetRow = -1;
    int targetCol = -1;
    bool wantToInstallTrap = false;
    bool wantToPlantSeed = false;

    void LoadAllTextures();

    sf::Texture houseTexture;
    sf::Texture slingshotTexture;
    sf::Texture DoorTexture;
    sf::Texture roadTexture;
    sf::Texture fieldTexture;
    sf::Texture outsideTexture;
    sf::Texture riceSeedTexture;
    sf::Texture potatoSeedTexture;
    sf::Texture carrotSeedTexture;
    sf::Texture cowTrapTexture;
    sf::Texture pigTrapTexture;
    sf::Texture horseTrapTexture;
    sf::Texture immatureRiceTexture;
    sf::Texture immaturePotatoTexture;
    sf::Texture immatureCarrotTexture;
    sf::Texture wateringCanTexture;
    sf::Texture clockTexture;
    sf::Texture matureRiceTexture;
    sf::Texture maturePotatoTexture;
    sf::Texture matureCarrotTexture;
    sf::Texture mainMenuBgTexture;
    sf::Texture newGameBtnTexture;
    sf::Texture exitBtnTexture;
    sf::Texture shopBgTexture;
    sf::Texture stoneTexture;
    sf::Texture rouletteTexture;
    sf::Texture thiefTexture;
};

GameState::GameState() : status(Status::MAIN), Level(1), Money(0) {}

void GameState::ChangePlaybackSpeed(int speed) {
    PlaybackSpeed = speed;
}

// IMPORTANT: 
// 시간이 추가되거나 버튼이 눌리면 이 함수 호출. 모든 Update 과정은 이 함수 내에서만 이루어질 것!!!!!!!
void GameState::Update() {
    if (status == Status::AM) {
        if(farm.Hour >= 18) TransitionToNight();
        else {
            farm.UpdateFarms();
            // 추가로 작성할 코드가 있다면, 이곳에 작성
        }
    }
    else if (status == Status::PM) {
        TickCounter += PlaybackSpeed;

        if (TickCounter >= 60) {
            TickCounter -= 60;

            NightElapsedMinutes += 1;
            farm.AddTime(1);

            farm.SpawnEnemies(NightElapsedMinutes);
            farm.UpdateTraps();
        }

        farm.UpdateEnemies(status, inventory);
        // farm.UpdateFarms(); 밤에도 작동시키고 싶으면 주석 제거

        if (farm.EnemiesEmpty()) TransitionToDay();
        else if (NightElapsedMinutes >= 720) TransitionToDay();
    }
}

bool GameState::CanVisitShop() {
    // TODO: 상점 버튼 누르면 이 함수 먼저 호출
    if (status != Status::AM) return false;
    farm.AddTime(GameData::ShoppingTimeCost);
    return true;
}

bool GameState::CanPlayMiniGame() {
    // TODO: 도박 버튼 누르면 이 함수 먼저 호출
    if (status != Status::AM) return false;
    farm.AddTime(GameData::GamblingTimeCost);
    return true;
}

void GameState::TransitionToNight() {
    // TODO: UI를 띄운 뒤, 버튼을 누르면 이 함수를 호출
    status = Status::PM;

    farm.TriggerNightRandomEvent();
    NightElapsedMinutes = 0;
    night = SetNightType();
    
    farm.AddEnemies(Level, night);
}

RandomEvent GameState::TransitionToDay() {
    // TODO: 낮으로 돌아올 때의 정산 처리 창 및 변수 초기화 과정 입력 + OK를 누르면 이 함수를 호출
    status = Status::AM;
    Level++;

    farm.TriggerDayRandomEvent();

    RandomEvent RandomEvent = RandomEvent::NONE;
    if (farm.IsDrought) RandomEvent = RandomEvent::DROUGHT;

    return RandomEvent; // TODO: 이 RandomEvent 값 return에 따라 UI에 뜨는 아이콘 추가
}

void GameState::PlayBGM(Status currentStatus) {
    // TODO: Audio 재생 함수 구현. 상태에 따라 다른 음악 재생할 것.
}

void GameState::LoadAllTextures() {
    if (!houseTexture.loadFromFile("assets/image/House.png")) {
        std::cerr << "Failed to load House.png" << std::endl;
    }
    if (!slingshotTexture.loadFromFile("assets/image/Slingshot.png")) {
        std::cerr << "Failed to load Slingshot.png" << std::endl;
    }
    if (!DoorTexture.loadFromFile("assets/image/Door.png")) {
        std::cerr << "Failed to load Door.png" << std::endl;
    }
    if (!roadTexture.loadFromFile("assets/image/Road.png")) {
        std::cerr << "Failed to load Road.png" << std::endl;
    }
    if (!fieldTexture.loadFromFile("assets/image/Field.png")) {
        std::cerr << "Failed to load Field.png" << std::endl;
    }
    if (!outsideTexture.loadFromFile("assets/image/Outside.png")) {
        std::cerr << "Failed to load Outside.png" << std::endl;
    }
    if (!riceSeedTexture.loadFromFile("assets/image/RiceShoot.png")) {
        std::cerr << "Failed to load RiceShoot.png" << std::endl;
    }
    if (!potatoSeedTexture.loadFromFile("assets/image/PotatoSeeds.png")) {
        std::cerr << "Failed to load PotatoSeeds.png" << std::endl;
    }
    if (!carrotSeedTexture.loadFromFile("assets/image/CarrotSeeds.png")) {
        std::cerr << "Failed to load CarrotSeeds.png" << std::endl;
    }
    if (!cowTrapTexture.loadFromFile("assets/image/Cow.png")) {
        std::cerr << "Failed to load Cow.png" << std::endl;
    }
    if (!pigTrapTexture.loadFromFile("assets/image/Pig.png")) {
        std::cerr << "Failed to load Pig.png" << std::endl;
    }
    if (!horseTrapTexture.loadFromFile("assets/image/Horse.png")) {
        std::cerr << "Failed to load Horse.png" << std::endl;
    }
    if (!immatureRiceTexture.loadFromFile("assets/image/ImmatureRice.png")) {
        std::cerr << "Failed to load ImmatureRice.png" << std::endl;
    }
    if (!immaturePotatoTexture.loadFromFile("assets/image/ImmaturePotato.png")) {
        std::cerr << "Failed to load ImmaturePotato.png" << std::endl;
    }
    if (!immatureCarrotTexture.loadFromFile("assets/image/ImmatureCarrot.png")) {
        std::cerr << "Failed to load ImmatureCarrot.png" << std::endl;
    }
    if (!matureRiceTexture.loadFromFile("assets/image/MatureRice.png")) {
        std::cerr << "Failed to load MatureRice.png" << std::endl;
    }
    if (!maturePotatoTexture.loadFromFile("assets/image/MaturePotato.png")) {
        std::cerr << "Failed to load MaturePotato.png" << std::endl;
    }
    if (!matureCarrotTexture.loadFromFile("assets/image/MatureCarrot.png")) {
        std::cerr << "Failed to load MatureCarrot.png" << std::endl;
    }
    if (!wateringCanTexture.loadFromFile("assets/image/WateringCan.png")) {
        std::cerr << "Failed to load WateringCan.png" << std::endl;
    }
    if (!clockTexture.loadFromFile("assets/image/Clock.png")) {
        std::cerr << "Failed to load Clock.png" << std::endl;
    }
    if (!mainMenuBgTexture.loadFromFile("assets/image/MainMenuBg.png")) {
        std::cerr << "Failed to load MainMenuBg.png" << std::endl;
    }
    if (!newGameBtnTexture.loadFromFile("assets/image/NewGame.png")) {
        std::cerr << "Failed to load NewGame.png" << std::endl;
    }
    if (!exitBtnTexture.loadFromFile("assets/image/Exit.png")) {
        std::cerr << "Failed to load Exit.png" << std::endl;
    }
    if (!shopBgTexture.loadFromFile("assets/image/ShopBg.png")) {
        std::cerr << "Failed to load ShopBg.png" << std::endl;
    }
    if (!stoneTexture.loadFromFile("assets/image/Stone.png")) {
        std::cerr << "Failed to load Stone.png" << std::endl;
    }
    if (!rouletteTexture.loadFromFile("assets/image/Roulette.png")) {
        std::cerr << "Failed to load Roulette.png" << std::endl;
    }
    if (!thiefTexture.loadFromFile("assets/image/Theif.png")) {
	std::cerr << "Failed to load Theif.png" << std::endl;
    }
}