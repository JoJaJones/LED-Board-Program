cmake_minimum_required(VERSION 3.17)
project(LED_Board_Program)

set(CMAKE_CXX_STANDARD 14)

add_executable(LED_Board_Program main.cpp models/Model.cpp models/Model.hpp services/board_constants.hpp views/LEDDisplay.cpp views/LEDDisplay.hpp services/DataState.cpp services/DataState.hpp controllers/LEDBoardEngine.cpp controllers/LEDBoardEngine.hpp views/View.cpp views/View.hpp services/constants.hpp)
add_library(rgbmatrix STATIC lib/lib/bdf-font.cc lib/lib/content-streamer.cc lib/lib/framebuffer.cc lib/lib/gpio.cc lib/lib/graphics.cc
        lib/lib/hardware-mapping.c lib/lib/led-matrix.cc lib/lib/multiplex-mappers.cc lib/lib/options-initialize.cc
        lib/lib/pixel-mapper.cc lib/lib/thread.cc lib/lib/transformer.cc)

include_directories(lib/lib)
include_directories(lib/include)
include_directories(models)
include_directories(views)
include_directories(controllers)
include_directories(utils)
include_directories(services)

find_library(RBG_LED_LIBRARY rgbmatrix lib)
target_link_libraries(LED_Board_Program LINK_PUBLIC ${RGB_LED_LIBRARY})