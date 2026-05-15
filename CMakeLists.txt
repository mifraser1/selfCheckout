cmake_minimum_required(VERSION 3.10)
project(SelfCheckoutProject CXX)

# 1. Automatically find all .cpp files in the src folder
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 2. Define the executable target using the found source files
add_executable(selfCheckout ${SOURCES})

# 3. Tell CMake where to look for your header (.h) files
target_include_directories(selfCheckout PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
