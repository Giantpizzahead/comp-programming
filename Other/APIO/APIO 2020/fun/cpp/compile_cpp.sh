#!/bin/bash

problem=fun

g++ -std=c++11 -Wall -Wextra -Wno-char-subscripts -fsanitize=address,undefined -D_GLIBCXX_DEBUG -g -o "${problem}" "grader.cpp" "${problem}.cpp" -O2 -lm
