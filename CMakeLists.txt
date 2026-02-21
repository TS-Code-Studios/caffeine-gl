cmake_minimum_required(VERSION 3.31)
project(caffeine_gl LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(OpenGL_GL_PREFERENCE GLVND)

add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(external/box2d)


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
        include/caffeine-gl/game/Transform.h
        include/caffeine-gl/game/Hitbox.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        box2d
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # For Windows cross-compiling with MinGW-w64
    target_link_libraries(${PROJECT_NAME} PUBLIC
            glfw
            opengl32
    )
else()
    # Native Linux build
    target_link_libraries(${PROJECT_NAME} PUBLIC
            glfw
            OpenGL::GL
    )
endif()