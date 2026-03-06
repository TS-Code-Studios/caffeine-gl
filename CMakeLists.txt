cmake_minimum_required(VERSION 3.31)
project(caffeine_gl LANGUAGES C CXX)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
add_subdirectory(external/glm)

if(UNIX AND NOT APPLE)
    set(OpenGL_GL_PREFERENCE GLVND)
endif()

find_package(OpenGL REQUIRED)

add_library(${PROJECT_NAME} STATIC
        include/caffeine-gl/base.hpp

        include/caffeine-gl/game/CaffeineGame.hpp

        include/caffeine-gl/game/CaffeineGameObject.hpp

        src/gfx/Shader.cpp
        include/caffeine-gl/gfx/Shader.hpp
        src/gfx/Texture.cpp
        include/caffeine-gl/gfx/Texture.hpp
        src/gfx/ResourceManager.cpp
        include/caffeine-gl/gfx/ResourceManager.hpp
        src/gfx/Renderer.cpp
        include/caffeine-gl/gfx/Renderer.hpp
        #src/gfx/ParticleGenerator.cpp
        #include/caffeine-gl/gfx/ParticleGenerator.hpp

        include/caffeine-gl/ui/CaffeineWindow.hpp
        src/ui/CaffeineWindow.cpp

        src/glad.c
        src/gfx/stb.cpp
        include/caffeine-gl/game/CaffeineDrawable.hpp
        include/caffeine-gl/game/CaffeineMeshDrawable.hpp
        include/caffeine-gl/game/CaffeineText.hpp
        include/caffeine-gl/game/CaffeineParticleGenerator.hpp
        include/caffeine-gl/game/Transform.hpp
        src/game/Transform.cpp
        include/caffeine-gl/gfx/Mesh.hpp
        include/caffeine-gl/gfx/Material.hpp
        src/game/CaffeineMeshDrawable.cpp
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