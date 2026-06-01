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

You can use VNC viewer to play the game.

```
http://localhost:8080/
```

**Option B** - Enter the container first, then run manually:
```
bash scripts/docker_run_shell.sh
```
This starts the container and drops you into a bash shell. From inside the container, you can run the app yourself
However, it may not work due to display bugs some OS has. Please only use it to navigate through /assets:
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
- Each crop has a different price : 5 / 10 / 20
- Each crop has a different selling price: 10 / 20 / 35
- Each crop takes a different time to grow : 30 / 60 / 60

2. Animal Field
- You can place down Animals
- Animals will protect you from the thieves
- Each crop has a different price : 40 / 50 / 60
- Each Animal has a different attack stat : 10 / 10 / 20
- Each Animal has a different range : 1x1 / 2x2 / 1x1

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
- Each day, thieves will be stronger, faster, and increase in number

**(5) Random Event**
- There are 3 Random Events. Events happen when the sun rises.
1. Pest
- Some crops die because of Pests

2. Drought
- Plants now dry 2x faster

3. Runaway
- Animals in the field have a chance to runaway

**(6) What is the goal?**
- SURVIVE AS LONG AS YOU CAN

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

**Team 14** — 2026 Programming Methodology Project

---
