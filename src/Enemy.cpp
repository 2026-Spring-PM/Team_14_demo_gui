#include "Enemy.hpp"

Enemy::Enemy() : Speed(0), Pos(0), CoolDown(0), Timer(0), HP(0), SpawnDelay(0), Ability(EnemyType::NONE), EnemyState(State::NONE) {}

Enemy::Enemy(int speed, EnemyType ability, int cooldown, int hp)
    : Speed(speed), Pos(0), CoolDown(cooldown), Timer(0), HP(hp), SpawnDelay(0), Ability(ability), EnemyState(State::ALIVE) {}

void Enemy::Move() {
    if (EnemyState != State::ALIVE) return;
    Pos += Speed;
}

void Enemy::TakeDamage(int damage) {
    HP -= damage;
    if (HP <= 0) {
        HP = 0;
        EnemyState = State::DEAD;
    }
}

void Enemy::Render() {
    // TODO : UI 렌더링 함수
}