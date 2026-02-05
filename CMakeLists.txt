cmake_minimum_required(VERSION 3.20)
project(OpenGLProject LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find vcpkg dependencies
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

# add SCOPE library
add_subdirectory(libs/SCOPE)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.c)
file(GLOB_RECURSE HEADERS include/*.h include/*.hpp)

add_executable(OpenGLProject ${SOURCES} ${HEADERS})

target_include_directories(OpenGLProject PRIVATE "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(OpenGLProject PRIVATE
    SCOPE
    glfw
    glad::glad
    glm::glm
    imgui::imgui
    assimp::assimp
)
