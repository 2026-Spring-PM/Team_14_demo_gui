#include "Enemy.hpp"

Enemy::Enemy() : Speed(0.0f), Pos(0.0f), CoolDown(0), Timer(0), HP(0), MaxHP(0), SpawnDelay(0), Ability(EnemyType::NONE), EnemyState(State::NONE) {}

Enemy::Enemy(float speed, float startPos, EnemyType ability, int cooldown, int hp)
    : Speed(speed), Pos(startPos), CoolDown(cooldown), Timer(0), HP(hp), MaxHP(hp), SpawnDelay(0), Ability(ability), EnemyState(State::ALIVE) {}

void Enemy::Move(float deltaTime) {
    if (EnemyState != State::ALIVE) return;
    
    Pos -= Speed * deltaTime; 

    if (Pos < 0.0f) {
        Pos = 0.0f;
	// TODO: 도둑이 집까지 도착. 총알 -1.
    }
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
