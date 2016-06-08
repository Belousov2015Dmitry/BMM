cmake_minimum_required(VERSION 3.5)
project(BMM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

set(SOURCE_FILES main.c Matrix/Matrix.h Matrix/Matrix.c Experiment/Experiment.h Experiment/Experiment.c Helpers/Stack.h Helpers/Stack.c)
add_executable(BMM ${SOURCE_FILES})