add_executable(breakout Breakout.cpp Controller.cpp Ball.cpp Ball.h)
target_link_libraries(breakout ${SDL2_LIBRARIES})
