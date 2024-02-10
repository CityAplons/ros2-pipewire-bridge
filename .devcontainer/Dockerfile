FROM ros:humble-ros-base as base

RUN apt-get update && apt-get install -y \
    software-properties-common \
    build-essential \
    git \
    sudo \
    wget

RUN add-apt-repository ppa:pipewire-debian/pipewire-upstream
RUN apt-get update && apt-get install -y \
    pipewire \
    pipewire-alsa \
    alsa-utils \
    pipewire-jack \
    pipewire-pulse \
    pipewire-tests \
    pipewire-audio-client-libraries \
    gstreamer1.0-pipewire \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN adduser --uid 1000 --disabled-password --gecos '' ros2pipe
RUN adduser ros2pipe sudo
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

USER ros2pipe

ENV XDG_RUNTIME_DIR=/tmp
ENV PIPEWIRE_RUNTIME_DIR=/tmp
ENV PULSE_RUNTIME_DIR=/tmp

WORKDIR /home/ros2pipe
