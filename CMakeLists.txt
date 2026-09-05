cmake_minimum_required(VERSION 3.10)
project(SelfCheckoutProject CXX)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(selfCheckout ${SOURCES})

target_include_directories(selfCheckout PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
target_link_libraries(selfCheckout PRIVATE Threads::Threads)

target_compile_definitions(selfCheckout PRIVATE FRONTEND_DIR="${CMAKE_CURRENT_SOURCE_DIR}/selfCheckoutFrontend")