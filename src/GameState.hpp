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

    sf::Texture houseTexture;
    sf::Texture slingshotTexture;
    sf::Texture DoorTexture;
    sf::Texture roadTexture;
    sf::Texture fieldTexture;
    sf::Texture outsideTexture;
};
