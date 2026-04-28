FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential cmake git \
    libfreetype6-dev libopenal-dev \
    libvorbis-dev libflac-dev \
    libudev-dev libgl1-mesa-dev \
    libx11-dev libxrandr-dev libxcursor-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git clone --branch 2.6.1 --depth 1 \
    https://github.com/SFML/SFML.git /tmp/sfml && \
    cmake -S /tmp/sfml -B /tmp/sfml/build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build /tmp/sfml/build -j$(nproc) && \
    cmake --install /tmp/sfml/build && \
    rm -rf /tmp/sfml

WORKDIR /app
COPY . .

RUN rm -rf build && \
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build -j$(nproc)

CMD ["./build/team14_game"]