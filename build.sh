#! /usr/bin/sh


####################
# Variables
####################
PROJECT_ROOT_DIR=$(pwd)     # Project root directory


####################
# CMake
####################
cmake                                       \
    -DCMAKE_BUILD_TYPE=Release              \
    -S $PROJECT_ROOT_DIR                    \
    -B ${PROJECT_ROOT_DIR}/output/build


####################
# Make
####################
make --no-print-directory -C ${PROJECT_ROOT_DIR}/output/build -j4
