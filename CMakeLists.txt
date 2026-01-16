cmake_minimum_required(VERSION 3.20)
project(OpenGLProject LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Trouvez les dépendances vcpkg
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

# Ajoutez le submodule SCOPE
add_subdirectory(libs/SCOPE)

file(GLOB_RECURSE SOURCES main.cpp)
file(GLOB_RECURSE HEADERS include/*.h include/*.hpp)

add_executable(OpenGLProject ${SOURCES} ${HEADERS})

# Ajoutez les chemins d'inclusion pour le projet principal
target_include_directories(OpenGLProject PRIVATE "${PROJECT_SOURCE_DIR}/include")

# Liez les bibliothèques nécessaires
target_link_libraries(OpenGLProject PRIVATE
    SCOPE
    glfw
    glad::glad
    glm::glm
    imgui::imgui
    assimp::assimp
)
