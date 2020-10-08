cmake_minimum_required(VERSION 3.17)
project(LED_Board_Program)

set(CMAKE_CXX_STANDARD 14)

# Tests
add_executable(Test_DataState
        tests/DataStateTests.cpp
        services/DataState.cpp)
add_executable(Test_RandomPixel
        tests/RandomPixelAnimTest.cpp
        services/DataState.cpp
        models/Model.cpp
        models/animations/Animation.cpp
        models/animations/RandomPixels.cpp)
add_executable(Test_GradualGradient
        tests/GradualGradientTests.cpp
        services/DataState.cpp models/Model.cpp
        models/animations/Animation.cpp
        models/animations/GradualGradient.cpp)
add_executable(Test_SimGeneral
        models/simulations/Simulation.cpp
        services/DataState.cpp models/Model.cpp)
add_executable(Test_AntBehavior
        models/simulations/langtons_ant/MoveBehavior.cpp
        models/simulations/langtons_ant/EdgeBehavior.cpp
        models/simulations/langtons_ant/TurnBehavior.cpp
        tests/AntBehaviorsUnitTestSuite.cpp)
add_executable(Test_AntGeneral
        models/simulations/langtons_ant/MoveBehavior.cpp
        models/simulations/langtons_ant/EdgeBehavior.cpp
        models/simulations/langtons_ant/TurnBehavior.cpp
        models/simulations/langtons_ant/Ant.cpp
        models/simulations/langtons_ant/BigAnt.cpp
        models/simulations/langtons_ant/AntDataService.cpp
        models/simulations/langtons_ant/AntFactory.cpp
        models/simulations/langtons_ant/BehaviorFactory.cpp)
add_executable(Test_BxFactory
        models/simulations/langtons_ant/MoveBehavior.cpp
        models/simulations/langtons_ant/TurnBehavior.cpp
        models/simulations/langtons_ant/EdgeBehavior.cpp
        models/simulations/langtons_ant/AntDataService.cpp
        models/simulations/langtons_ant/BehaviorFactory.cpp
        tests/BehaviorFactoryTests.cpp)
add_executable(quick_test
        models/simulations/langtons_ant/MoveBehavior.cpp
        models/simulations/langtons_ant/EdgeBehavior.cpp
        models/simulations/langtons_ant/TurnBehavior.cpp
        tests/quick_test.cpp)

#main executable
#add_executable(LED_Board_Program main.cpp models/Model.cpp models/Model.hpp services/board_constants.hpp views/LEDDisplay.cpp views/LEDDisplay.hpp services/DataState.cpp services/DataState.hpp controllers/LEDBoardEngine.cpp controllers/LEDBoardEngine.hpp views/View.cpp views/View.hpp services/constants.hpp tests/DataStateTests.cpp models/animations/Animation.cpp models/animations/Animation.hpp models/games/Game.cpp models/games/Game.hpp models/Position.cpp models/Position.hpp models/simulations/Simulation.cpp models/simulations/Simulation.hpp models/animations/RandomPixels.cpp models/animations/RandomPixels.hpp tests/RandomPixelAnimTest.cpp)
#add_library(rgbmatrix STATIC lib/lib/bdf-font.cc lib/lib/content-streamer.cc lib/lib/framebuffer.cc lib/lib/gpio.cc lib/lib/graphics.cc
#        lib/lib/hardware-mapping.c lib/lib/led-matrix.cc lib/lib/multiplex-mappers.cc lib/lib/options-initialize.cc
#        lib/lib/pixel-mapper.cc lib/lib/thread.cc lib/lib/transformer.cc)

include_directories(lib/lib)
include_directories(lib/include)
include_directories(models)
include_directories(views)
include_directories(controllers)
include_directories(utils)
include_directories(services)
include_directories(tests)

#find_library(RBG_LED_LIBRARY rgbmatrix lib)
#target_link_libraries(LED_Board_Program LINK_PUBLIC ${RGB_LED_LIBRARY})