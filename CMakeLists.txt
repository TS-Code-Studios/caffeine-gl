cmake_minimum_required(VERSION 3.31)
project(caffeine-gl)

set(CMAKE_CXX_STANDARD 17)
set(OpenGL_GL_PREFERENCE GLVND)

add_library(caffeine-gl STATIC
        src/game/BallClass.cpp
        src/game/BallClass.h
        src/game/Game.cpp
        src/game/Game.h
        src/game/GameLevel.cpp
        src/game/GameLevel.h
        src/game/GameObject.cpp
        src/game/GameObject.h
        src/gfx/ParticleGenerator.cpp
        src/gfx/ParticleGenerator.h
        src/gfx/ResourceManager.cpp
        src/gfx/ResourceManager.h
        src/gfx/Shader.cpp
        src/gfx/Shader.h
        src/gfx/SpriteRenderer.cpp
        src/gfx/SpriteRenderer.h
        src/gfx/stb.cpp
        src/gfx/stb_image.h
        src/gfx/Texture.cpp
        src/gfx/Texture.h
        src/glad.c
)

target_include_directories(caffeine-gl PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(caffeine-gl PUBLIC
    glad
    glfw
    OpenGL:GL
)