#!/bin/bash

set -ex

# cc -Wall -Wextra -v -o main main.c src/*.c -lm
cc -Wall -Wextra -o main main.c src/*.c -lm -I./src
./main images/GS_team.jpg GS_team_grayscale.jpg
