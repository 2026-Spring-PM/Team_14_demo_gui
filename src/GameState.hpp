#pragma once
#include "Enums.hpp"
#include "SaveState.hpp"
#include "Enemy.hpp"
#include <vector>

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
};