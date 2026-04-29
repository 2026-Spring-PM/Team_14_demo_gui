#include "GameState.hpp"
#include "Mechanism.hpp"

GameState::GameState() : status(Status::Main), Level(1) {}

void GameState::Update() {
    if (status == Status::AM) {
        if(state.farm.Hour >= 18) {
            TransitionToNight();
        }
    }
    else if (status == Status::PM) {
        for (auto it = PendingEnemies.begin(); it != PendingEnemies.end();) {
            if (NightElapsedMinutes >= it->SpawnDelay) {
                ActiveEnemies.push_back(*it);
                it = PendingEnemies.erase(it);
            } else ++it;
        }

        for (int r = 0; r < state.farm.ROWS; r++) {
            for (int c = 0; c < state.farm.COLS; c++) {
                Trap* trap = state.farm.TrapField[r][c];
                
                if (trap != nullptr && trap->TrapState == State::ALIVE) {
                    trap->UpdateTimer();

                    if (trap->Timer >= trap->CoolDown) {
                        for (auto& enemy : ActiveEnemies) {
                            if (enemy.EnemyState == State::ALIVE) {
                                // TODO: 함정의 위치(r,c)와 적의 위치(Pos)를 계산해 사거리(Range) 내인지 판별하는 조건문 추가 필요
                                enemy.TakeDamage(trap->Atk);
                                trap->Timer = 0;
                                // break; // 한 번에 한 명만 공격한다면 주석 제거
                            }
                        }
                    }
                }
            }
        }

        for (auto it = ActiveEnemies.begin(); it != ActiveEnemies.end();) {
            if (it.EnemyState == State::DEAD) {
                // state.AddMoney(); // 적 사망 시 돈 추가하고 싶으면 코드 추가
                it = ActiveEnemies.erase(it);
            }
            else if (it.EnemyState == State::ALIVE){
                it->Move();

                if (it->Pos >= 100) { // TODO: UI 및 향후 구현에 따른 100이라는 숫자 조정
                    if (!state.TakeDamage()) {
                        status = Status::GAMEOVER;
                        return;
                    }
                    it = ActiveEnemies.erase(it);
                }
                else ++it;
            }
        }

        state.farm.UpdateFields();

        if (PendingEnemies.empty() && ActiveEnemies.empty()) TransitionToDay();
        else if (NightElapsedMinutes >= 720) TransitionToDay();
    }
}

void GameState::VisitShop() {
    if (status != Status::AM) return;
    state.farm.AddTime(TimeWaste::SHOPING);
    // TODO: 상점 UI 오픈 및 로직
}

void GameState::PlayMiniGame() {
    if (status != Status::AM) return;
    state.farm.AddTime(TimeWaste::GAMBLING);
    // TODO: 도박 로직 구현
}

void GameState::TransitionToNight() {
    status = Status::PM;
    state.farm.TriggerNightRandomEvent();
    NightElapsedMinutes = 0;
    night = SetNightType();

    int enemyCount = EnemyCount(Level);
    int enemySpeed = EnemySpeed(Level);

    ActiveEnemies.clear();
    PendingEnemies.clear();

    for(int i = 0; i < enemyCount; i++) {
        // TODO: 이후 적 종류 다양화 함수 구현하여 넣기.
        Enemy newEnemy(enemySpeed, EnemyType::Normal, 10, 100);
        newEnemy.SpawnDelay = SpawnDelay(night);
        PendingEnemies.push_back(newEnemy);
    }
}

void GameState::TransitionToDay() {
    status = Status::AM;
    Level++;

    state.farm.TriggerDayRandomEvent();
    // TODO: 낮으로 돌아올 때의 정산 처리 및 변수 초기화
}

void GameState::PlayBGM(Status currentStatus) {
    // TODO: Audio 재생 함수, 상태에 따라 다른 음악 재생할 것.
}