cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)


include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(main src/main.cpp src/Entities/ball.cpp src/Entities/particles.cpp src/entity.cpp src/engine.cpp src/component.cpp src/Entities/fps-counter.cpp src/helperFunctions.cpp src/States/MenuGameState.cpp src/States/PlayGameState.cpp src/States/EditGameState.cpp src/UI/textButtons.cpp src/States/PlayAstroGameState.cpp src/Entities/ship.cpp src/Entities/weightValues.cpp) 

target_link_libraries(main PRIVATE SFML::Graphics)

find_package(Catch2 REQUIRED)

#add_executable(uniTest src/tests/test.cpp src/ball.cpp src/particles.cpp src/entity.cpp src/engine.cpp src/component.cpp src/fps-counter.cpp src/helperFunctions.cpp src/MenuGameState.cpp)

#target_link_libraries(uniTest PRIVATE SFML::Graphics Catch2::Catch2WithMain)
