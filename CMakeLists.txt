cmake_minimum_required(VERSION 3.31)
project(caffeine_gl LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)

add_library(${PROJECT_NAME} STATIC
        src/glad.c

        include/caffeine-gl/game/Game.h
        src/game/GameLevel.cpp
        include/caffeine-gl/game/GameLevel.h
        src/game/GameObject.cpp
        include/caffeine-gl/game/GameObject.h
        src/game/BallClass.cpp
        include/caffeine-gl/game/BallClass.h

        src/gfx/Shader.cpp
        include/caffeine-gl/gfx/Shader.h
        src/gfx/Texture.cpp
        include/caffeine-gl/gfx/Texture.h
        src/gfx/ResourceManager.cpp
        include/caffeine-gl/gfx/ResourceManager.h
        src/gfx/SpriteRenderer.cpp
        include/caffeine-gl/gfx/SpriteRenderer.h
        src/gfx/ParticleGenerator.cpp
        include/caffeine-gl/gfx/ParticleGenerator.h

        src/gfx/stb.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # For Windows cross-compiling with MinGW-w64
    target_link_libraries(${PROJECT_NAME} PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/libglfw3.a
            opengl32
    )
else()
    # Native Linux build
    target_link_libraries(${PROJECT_NAME} PUBLIC
            z
            minizip
            ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/libglfw3.a
            OpenGL::GL
            dl
            pthread
            wayland-client
            wayland-cursor
            wayland-egl
            xkbcommon
    )
endif()