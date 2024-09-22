cmake_minimum_required(VERSION 3.10.0)

project(typwr VERSION 0.1.0 LANGUAGES C)

add_executable(typwr ./src/main.c ./src/typewriter.c ./src/cli.c)

