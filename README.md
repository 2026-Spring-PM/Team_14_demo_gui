# Team14 Game

A C++ game project built with SDL/SFML, distributed via Docker with GUI support.

---

## Getting Started

### 1. Pull the Image
```
docker pull ghcr.io/2026-spring-pm/team_14/team14_project:0.1.0
```

### 2. Run the app
**Option A** - Run automatically:
```
bash scripts/docker_run.sh
```
This starts the container and immediately launches ```build/team14_game```.

**Option B** - Enter the container first, then run manually:
```
bash scripts/docker_run_shell.sh
```
This starts the container and drops you into a bash shell. From inside the container, you can run the app yourself:
```
./build/team14_game
```
---

## Game System

**(1) GUI**
- Implemented using a GUI system
- Play using Mouse (Maybe ESC key for pause)

**(2) Field**
- There are 2 kinds of fields
1. Seed Field
- You can place down seeds
- It can be grown and be selled

2. Animal Field
- You can place down Animals
- Animals will protect you from the thieves

**(3-1) Shop**
- Buy some seeds or animals from the Shop
- You can also buy some bullets
- If you're out of bullets when the thieves break-in, GAMEOVER

**(3-2) Mini-game in the Shop**
- Play a roulette game in the Shop by paying $10
- Who knows? You might win BIG

**(4) Night System**
- When the time is 18:00, the night starts
- Thieves would try to break in
- You should place down traps (or Animals) in the field to protect yourself
- 

**(5) Random Event**
- There are 3 Random Events. Events happen when the sun rises.
1. Pest
- Some crops die because of Pests

2. Drought
- Plants now dry 2x faster

3. Runaway
- Animals in the field have a chance to runaway

---

## Project Structure

```
.
├── assets/       # 게임 리소스 (이미지, 사운드 등)
├── scripts/      # Docker 실행용 스크립트
└── README.md
```

---

## Team

**Team 14** — 2026 Software Project

---
