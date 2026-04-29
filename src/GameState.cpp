#include "GameState.hpp"
#include "Mechanism.hpp"
#include "GameData.hpp"

GameState::GameState() : status(Status::MAIN), Level(1) {}

void GameState::ChangePlaybackSpeed(int speed) {
    PlaybackSpeed = speed;
}

void GameState::Update() {
    if (status == Status::AM) {
        if(state.farm.Hour >= 18) {
            TransitionToNight();
        }
    }
    else if (status == Status::PM) {
        TickCounter += PlaybackSpeed;

        if (TickCounter >= 60) {
            TickCounter -= 60;

            NightElapsedMinutes += 1;
            state.farm.AddTime(1);

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
                                if (enemy.EnemyState == State::ALIVE && trap->InRange(enemy)) {
                                    enemy.TakeDamage(trap->Atk);
                                    trap->Timer = 0;
                                    // break; // 한 번에 한 명만 공격한다면 주석 제거 -> 이후 업데이트 시 범위 공격 등 추가
                                }
                            }
                        }
                    }
                }
            }
        }

        for (auto it = ActiveEnemies.begin(); it != ActiveEnemies.end();) {
            if (it->EnemyState == State::DEAD) {
                // state.AddMoney(); // 적 사망 시 돈 추가하고 싶으면 코드 추가 -> 이후 업데이트 시 있는 게 좋다면 추가
                it = ActiveEnemies.erase(it);
            }
            else if (it->EnemyState == State::ALIVE){
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
    state.farm.AddTime(GameData::ShoppingTimeCost);
    // TODO: 상점 UI 오픈 및 로직
}

void GameState::PlayMiniGame() {
    if (status != Status::AM) return;
    state.farm.AddTime(GameData::GamblingTimeCost);
    // TODO: 도박 로직 구현
}

void GameState::TransitionToNight() {
    status = Status::PM;

    // TODO: 밤이 왔음을 알리는 창 띄우기 + OK를 누를 때까지 아래 코드는 실행X

    state.farm.TriggerNightRandomEvent();
    NightElapsedMinutes = 0;
    night = SetNightType();

    int enemyCount = EnemyCount(Level);

    ActiveEnemies.clear();
    PendingEnemies.clear();

    for(int i = 0; i < enemyCount; i++) {
        EnemyType type = EnemyTypeSet(Level);
        int speed = EnemySpeed(Level, type);
        int cooldown;
        int hp;

        Enemy newEnemy(speed, type, cooldown, hp);
        newEnemy.SpawnDelay = SpawnDelay(night);
        PendingEnemies.push_back(newEnemy);
    }
}

void GameState::TransitionToDay() {
    status = Status::AM;
    Level++;

    // TODO: 낮으로 돌아올 때의 정산 처리 창 및 변수 초기화 과정 입력 + OK를 누를 때까지 아래 코드는 실행X

    state.farm.TriggerDayRandomEvent();

    // TODO: 가뭄 및 병충해로 인한 변경 과정 작성
}

void GameState::PlayBGM(Status currentStatus) {
    // TODO: Audio 재생 함수 구현. 상태에 따라 다른 음악 재생할 것.
}