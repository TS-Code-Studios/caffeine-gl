cmake_minimum_required(VERSION 3.31)
project(caffeine_gl LANGUAGES C CXX)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
add_subdirectory(external/glm)

if(UNIX AND NOT APPLE)
    set(OpenGL_GL_PREFERENCE GLVND)
endif()

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

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        glfw
        glm::glm
        OpenGL::GL
)