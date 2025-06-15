#!/usr/bin/env bash
set -e

PACKAGES=(
  autoconf
  automake
  libtool
  pkg-config
  build-essential
  libgl1-mesa-dev
  libx11-dev
  libexpat1-dev
  libsdl2-dev
  libglew-dev
  libpng-dev
  libgtest-dev
)

if [ "$EUID" -ne 0 ]; then
  sudo apt-get update
  sudo apt-get install -y "${PACKAGES[@]}"
else
  apt-get update
  apt-get install -y "${PACKAGES[@]}"
fi

