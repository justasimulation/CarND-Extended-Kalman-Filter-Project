project(ExtendedKF)

cmake_minimum_required (VERSION 3.5)

add_definitions(-std=c++0x)

set(sources src/main.cpp src/storage.h src/storage.cpp src/measurement_device.h src/measurement_device.cpp src/app.h src/app.cpp src/fusion_tracker.h src/fusion_tracker.cpp src/kalman_filter.cpp src/kalman_filter.h)

add_executable(ExtendedKF ${sources})
