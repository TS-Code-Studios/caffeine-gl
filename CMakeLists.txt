cmake_minimum_required(VERSION 3.31)
project(caffeine_gl LANGUAGES C CXX)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(external/freetype)

if(UNIX AND NOT APPLE)
    set(OpenGL_GL_PREFERENCE GLVND)
endif()

find_package(OpenGL REQUIRED)

add_library(${PROJECT_NAME} STATIC
        include/caffeine-gl/base.hpp

        src/gfx/CaffeineShader.cpp
        include/caffeine-gl/gfx/CaffeineShader.hpp
        src/gfx/CaffeineTexture.cpp
        include/caffeine-gl/gfx/CaffeineTexture.hpp
        src/gfx/ResourceManager.cpp
        include/caffeine-gl/gfx/ResourceManager.hpp
        src/systems/CaffeineRenderingSystem.cpp
        include/caffeine-gl/systems/CaffeineRenderingSystem.hpp

        include/caffeine-gl/ui/CaffeineWindow.hpp
        src/ui/CaffeineWindow.cpp

        src/glad.c
        src/gfx/stb.cpp
        #include/caffeine-gl/game/CaffeineParticleGenerator.hpp
        include/caffeine-gl/components/CaffeineTransformComponent.hpp
        include/caffeine-gl/gfx/CaffeineMesh.hpp
        include/caffeine-gl/components/CaffeineMaterialComponent.hpp
        include/caffeine-gl/systems/CaffeineCollisionSystem.hpp
        src/systems/CaffeineCollisionSystem.cpp
        include/caffeine-gl/components/CaffeineColliderComponent.hpp
        include/caffeine-gl/gfx/TextRenderer.hpp
        src/gfx/TextRenderer.cpp
        include/caffeine-gl/game/CaffeineWorld.hpp
        src/game/CaffeineWorld.cpp
        include/caffeine-gl/game/ComponentPoolInterface.hpp
        include/caffeine-gl/game/ComponentPool.hpp
        include/caffeine-gl/components/CaffeineMeshComponent.hpp
        include/caffeine-gl/game/CaffeineEntity.hpp
        include/caffeine-gl/components/CaffeineRenderComponent.hpp
        include/caffeine-gl/components/CaffeineVelocityComponent.hpp
        include/caffeine-gl/systems/CaffeineVelocitySystem.hpp
        src/systems/CaffeineVelocitySystem.cpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        #external/freetype/include
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        glfw
        glm::glm
        OpenGL::GL
        freetype
)