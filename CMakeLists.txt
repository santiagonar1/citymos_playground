cmake_minimum_required(VERSION 3.29)
project(citymos_playground)

set(CMAKE_CXX_STANDARD 20)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

option(BUILD_TESTING "Build tests" ON)

enable_testing()

file(GLOB SOURCES
        src/*.cpp
)

file(GLOB MY_PUBLIC_HEADERS
        include/*.hpp
)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
        PRIVATE ${SOURCES})

# See: https://decovar.dev/blog/2021/03/08/cmake-cpp-library/#include-directories
target_include_directories(${PROJECT_NAME}
        PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

add_subdirectory(app)

if (BUILD_TESTING)
    add_subdirectory(tests)
else ()
    message(STATUS "Tests and benchmarks will not be compiled")
endif ()


