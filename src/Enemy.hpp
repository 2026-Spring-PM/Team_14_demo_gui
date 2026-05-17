#pragma once
#include "Enums.hpp"

class Enemy {
public:
    float Speed;
    float Pos;
    int CoolDown;
    int Timer;
    int HP;
    int MaxHP;
    int SpawnDelay;
    EnemyType Ability;
    State EnemyState;

    Enemy();
    Enemy(float speed, float startPos, EnemyType ability, int cooldown, int hp);

    void Move(float deltaTime);
    void TakeDamage(int damage);

    void Render();
};
