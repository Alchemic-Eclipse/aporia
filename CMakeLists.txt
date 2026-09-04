cmake_minimum_required(VERSION 4.3)
project(aporia)

set(CMAKE_CXX_STANDARD 23)

find_package(raylib REQUIRED)

add_executable(aporia src/main.cpp
        src/DoublePendulum.cpp
        include/DoublePendulum.h
        include/EulerIntegrator.h
        src/EulerIntegrator.cpp
        src/renderer.cpp
        include/renderer.h
        include/Integrator.h
        include/RK4Integrator.h
        src/RK4Integrator.cpp)

target_link_libraries(aporia PRIVATE raylib)
