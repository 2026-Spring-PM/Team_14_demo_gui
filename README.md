# Team14 Game

A C++ game project built with SDL/SFML, distributed via Docker with GUI support.

## Getting Started

### 1. Pull the Image

```bash
docker pull ghcr.io/2026-spring-pm/team_14/team14_game:latest
```

### 2. Allow X11 Display Access

```bash
xhost +local:docker
```

### 3. Run the Game

```bash
docker run --rm \
  -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  ghcr.io/2026-spring-pm/team_14/team14_game:latest \
  /bin/bash
```

---

## Build & Push (For Developers)

### Git Submodule (Right After Download)

```bash
git submodule update --init --recursive
```

### Build the Image

```bash
cd docker
./docker_build.sh
```

### Tag & Push to GitHub Container Registry

```bash
docker tag team14_game:latest ghcr.io/2026-spring-pm/team_14/team14_game:latest
docker push ghcr.io/2026-spring-pm/team_14/team14_game:latest
```

> **Note:**
> You must be authenticated with `docker login ghcr.io` before pushing.

## Project Structure

```
.
├── Dockerfile
├── src/          # C++ 소스 코드
├── assets/       # 게임 리소스 (이미지, 사운드 등)
└── README.md
```

---

## Team

**Team 14** — 2026 Software Project

---
