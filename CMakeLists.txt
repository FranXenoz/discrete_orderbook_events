cmake_minimum_required(VERSION 3.10)
project(QuantSim)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Apple Silicon Optimizations
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

include_directories(include)

# --- EXECUTABLE 1: The Simulator ---
# We explicitly list the files that belong to the engine
add_executable(sim_engine src/main.cpp src/engine.cpp src/order_book.cpp)

# --- EXECUTABLE 2: The Data Generator ---
# We create a completely separate program just for generating data
add_executable(generate_data src/generate_data.cpp)