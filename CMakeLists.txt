cmake_minimum_required(VERSION 3.10)

project(Blink LANGUAGES CXX)

find_package(Qt5 COMPONENTS
    Core
    OpenGL
    REQUIRED
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -ftree-vectorize ")

add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME}
PRIVATE
    Source/Blink.cpp
    Source/Blink.hpp
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    Qt5::Core 
    Qt5::OpenGL
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
