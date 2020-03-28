#! /usr/bin/env bash

GENERATOR=Ninja
#GENERATOR=Xcode

mkdir -p build
cd build
cmake .. -G "$GENERATOR"
ninja
