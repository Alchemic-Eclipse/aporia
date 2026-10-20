
cmake_minimum_required(VERSION 4.3)

if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "26.0" CACHE STRING
            "Minimum macOS version")
endif()

project(aporia LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib CONFIG REQUIRED)

set(APORIA_SOURCES
        src/main.cpp
        src/DoublePendulum.cpp
        include/DoublePendulum.h
        include/EulerIntegrator.h
        src/EulerIntegrator.cpp
        src/renderer.cpp
        include/renderer.h
        include/Integrator.h
        include/RK4Integrator.h
        src/RK4Integrator.cpp
        include/simulation.h
        src/simulation.cpp
        include/analysis.h
        src/analysis.cpp
        include/ExperimentSettings.h
        include/sonifier.h
        src/sonifier.cpp
)

if(APPLE)
    add_executable(aporia MACOSX_BUNDLE ${APORIA_SOURCES})
else()
    add_executable(aporia ${APORIA_SOURCES})
endif()

target_link_libraries(aporia PRIVATE raylib)

if(APPLE)
    set(RAYLIB_DYLIB
            "/opt/homebrew/lib/libraylib.6.2.0.dylib"
    )

    set(RAYLIB_BUNDLED_NAME "libraylib.6.2.0.dylib")

    set_target_properties(aporia PROPERTIES
            BUILD_RPATH "@executable_path/../Frameworks"
            INSTALL_RPATH "@executable_path/../Frameworks"
    )

    add_custom_command(TARGET aporia POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_BUNDLE_CONTENT_DIR:aporia>/Frameworks"

            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${RAYLIB_DYLIB}"
            "$<TARGET_BUNDLE_CONTENT_DIR:aporia>/Frameworks/"

            COMMAND /usr/bin/install_name_tool
            -change
            "${RAYLIB_DYLIB}"
            "@rpath/${RAYLIB_BUNDLED_NAME}"
            "$<TARGET_FILE:aporia>"
    )
endif()
