cmake_minimum_required(VERSION 3.20)
project(eliott-input VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 CONFIG REQUIRED)



add_library(eliott-input STATIC
    src/InputManager.cpp
)

if(PROJECT_IS_TOP_LEVEL)

find_package(doctest CONFIG REQUIRED)
add_executable(tests 
    tests/test-input.cpp
)



target_link_libraries(tests PRIVATE
    eliott-input
    doctest::doctest
)
endif()

target_include_directories(eliott-input PUBLIC
    include/
)

target_link_libraries(eliott-input PRIVATE
SDL3::SDL3
)