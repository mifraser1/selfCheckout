cmake_minimum_required(VERSION 3.10)
project(selfCheckout)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
    src/main.cpp
)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Create executable
add_executable(selfCheckout ${SOURCES})

# Optional: Add any libraries or compiler flags here
target_compile_options(selfCheckout PRIVATE -Wall -Wextra -Wpedantic)
