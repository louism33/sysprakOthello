cmake_minimum_required(VERSION 3.15)
project(AlexTheFriendlyAI C)

set(CMAKE_C_STANDARD 99)

add_executable(syprak-client main.c connector/connector.c thinker/thinker.c)