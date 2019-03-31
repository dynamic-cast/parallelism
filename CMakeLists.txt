CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

PROJECT(threading LANGUAGES C CXX)
SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "-Wall --pedantic -pthread -g")

ADD_LIBRARY(lodepng STATIC
    ${PROJECT_SOURCE_DIR}/third_party/lodepng.cpp
)

ADD_LIBRARY(process STATIC
    ${PROJECT_SOURCE_DIR}/src/load.cpp
    ${PROJECT_SOURCE_DIR}/src/process.cpp
)

ADD_EXECUTABLE(main
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)

TARGET_LINK_LIBRARIES(process lodepng)
TARGET_LINK_LIBRARIES(main process)
