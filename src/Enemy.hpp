#pragma once
#include "Enums.hpp"

class Enemy {
public:
    int Speed;
    int Pos;
    int CoolDown;
    int Timer;
    int HP;
    int SpawnDelay;
    EnemyType Ability;
    State EnemyState;

    Enemy();
    Enemy(int speed, EnemyType ability, int cooldown, int hp);

    void Move();
    void TakeDamage(int damage);

    void Render();
};