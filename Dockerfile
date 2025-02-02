FROM ubuntu:22.04

# Install system dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    valgrind \
    xorg-dev\
    libglfw3-dev \
    libx11-dev \
    libxext-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxi-dev \
    zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

ENV TERM=xterm
ENV DISPLAY=host.docker.internal:0
ENV LIBGL_ALWAYS_INDIRECT=0

# Set working directory
WORKDIR /app

# Copy entire project including MLX42 submodule
COPY . .

# Build the project using your Makefile
RUN make

# Set default command to run the program
CMD ["./cub3d", "./assets/maps/t1.cub"]
