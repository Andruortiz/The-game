cmake_minimum_required(VERSION 3.0)
project(Thegame)

# Configuración del estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Agregar los archivos fuente del juego
set(SOURCES
        main.cpp
        juego.cpp
        jugador.cpp
        cmake-build-debug/dificultades.cpp
)

# Agregar el ejecutable
add_executable(juego_deletreo ${SOURCES})
add_executable(dificultades dificultades.cpp)