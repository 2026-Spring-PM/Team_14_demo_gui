# Team14 Game

A C++ game project built with SDL/SFML, distributed via Docker with GUI support.

---

## Getting Started

### 1. Pull the Image
```
docker pull ghcr.io/2026-spring-pm/team_14/team14_project:0.1.0
```

### 2. Run the app
Option A - Run automatically:
```
bash scripts/docker_run.sh
```
This starts the container and immediately launches ```build/team14_game```.

Option B - Enter the container first, then run manually:
```
bash scripts/docker_run_shell.sh
```
This starts the container and drops you into a bash shell. From inside the container, you can run the app yourself:
```
./build/team14_game
```
---

## Game System

NOT DONE YET

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
