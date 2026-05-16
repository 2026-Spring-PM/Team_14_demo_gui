#pragma once
#include "Enums.hpp"
#include "SaveState.hpp"
#include "Enemy.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class GameState {
public:
    Status status;
    SaveState state;

    std::vector<Enemy> ActiveEnemies;
    std::vector<Enemy> PendingEnemies;

    int Level;
    int NightElapsedMinutes;
    NightType night;

    int PlaybackSpeed;
    int TickCounter;

    GameState();

    void Update();
    void VisitShop();
    void PlayMiniGame();

    void ChangePlaybackSpeed(int speed);

    void TransitionToNight();
    void TransitionToDay();

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


};
