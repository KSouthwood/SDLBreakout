add_executable(breakout Breakout.cpp Controller.cpp Ball.cpp Ball.h TextureMap.cpp TextureMap.h Texture.cpp Texture.h Brick.cpp Brick.h Collisions.cpp Paddle.cpp Paddle.h FPS.cpp FPS.h Events.cpp)
target_link_libraries(breakout ${SDL2_LIBRARIES} SDL2_gfx)
