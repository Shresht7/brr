cmake_minimum_required(VERSION 3.10.0)

project(brr VERSION 0.1.0 LANGUAGES C)

add_executable(brr ./src/main.c ./src/typewriter.c ./src/cli.c ./src/helpers.c)

