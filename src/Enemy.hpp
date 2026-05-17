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

    Enemy()
    : Speed(0.0f), Pos(0.0f), CoolDown(0), Timer(0), HP(0), MaxHP(0), SpawnDelay(0), Ability(EnemyType::NONE), EnemyState(State::NONE) {};
    Enemy(float speed, float startPos, EnemyType ability, int cooldown, int hp)
    : Speed(speed), Pos(startPos), CoolDown(cooldown), Timer(0), HP(hp), MaxHP(hp), SpawnDelay(0), Ability(ability), EnemyState(State::ALIVE) {};

    void Move(float deltaTime) {
        if (EnemyState != State::ALIVE) return;
    
        Pos -= Speed * deltaTime; 

        if (Pos < 0.0f) {
            Pos = 0.0f;
            // TODO: 도둑이 집까지 도착 시. 총알 -1.
        }
    }

    void TakeDamage(int damage) {
        HP -= damage;
        if (HP <= 0) {
            HP = 0;
            EnemyState = State::DEAD;
        }
    }

    void Render() {
        // TODO : UI 렌더링 함수
    }
};