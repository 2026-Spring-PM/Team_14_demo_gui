# 🎮 Team14 Game

A C++ game project built with SDL/SFML, distributed via Docker with GUI support.

---

## 📋 Requirements

- [Docker](https://docs.docker.com/get-docker/)
- X11 display server (Linux) or XQuartz (macOS)

---

## 🚀 Getting Started

### 1. Pull the Image

```bash
docker pull ghcr.io/YOUR_GITHUB_ORG/team14_game:latest
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
  ghcr.io/YOUR_GITHUB_ORG/team14_game:latest
```

---

## 🛠️ Build & Push (For Developers)

### Build the Image

```bash
docker build -t team14_game:latest .
```

### Tag & Push to GitHub Container Registry

```bash
docker tag team14_game:latest ghcr.io/YOUR_GITHUB_ORG/team14_game:latest
docker push ghcr.io/YOUR_GITHUB_ORG/team14_game:latest
```

> **Note:** Replace `YOUR_GITHUB_ORG` with your actual GitHub organization or username.  
> You must be authenticated with `docker login ghcr.io` before pushing.

---

## 🖥️ Platform Notes

| OS | Display Setup |
|---|---|
| Linux | `xhost +local:docker` (X11 기본 지원) |
| macOS | [XQuartz](https://www.xquartz.org/) 설치 후 `xhost +localhost` |
| Windows | [VcXsrv](https://sourceforge.net/projects/vcxsrv/) 또는 WSL2 + X server |

---

## 📁 Project Structure

```
.
├── Dockerfile
├── src/          # C++ 소스 코드
├── assets/       # 게임 리소스 (이미지, 사운드 등)
└── README.md
```

---

## 👥 Team

**Team 14** — 2026 Software Project

---

## 📄 License

This project is for educational purposes.
