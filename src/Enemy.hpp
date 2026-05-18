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

    bool Move(float deltaTime);
    void TakeDamage(int damage);
};

Enemy::Enemy()
: Speed(0.0f), Pos(0.0f), CoolDown(0), Timer(0), HP(0), MaxHP(0), SpawnDelay(0), Ability(EnemyType::NONE), EnemyState(State::NONE) {};

Enemy::Enemy(float speed, float startPos, EnemyType ability, int cooldown, int hp)
: Speed(speed), Pos(startPos), CoolDown(cooldown), Timer(0), HP(hp), MaxHP(hp), SpawnDelay(0), Ability(ability), EnemyState(State::ALIVE) {};

bool Enemy::Move(float deltaTime) {
    if (EnemyState != State::ALIVE) return false;
    
    Pos -= Speed * deltaTime; 

    if (Pos <= 0) {
        Pos = 0;
        return true;
    }
    
    return false;
}

void Enemy::TakeDamage(int damage) {
    HP -= damage;

    if (HP <= 0) {
        HP = 0;
        EnemyState = State::DEAD;
    }
}